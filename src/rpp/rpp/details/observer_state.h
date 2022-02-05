// MIT License
// 
// Copyright (c) 2021 Aleksey Loginov
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <functional>

namespace rpp::details
{
template<typename Type>
class observer_state
{
    using Decayed = std::decay_t<Type>;

    template<typename T>
    static constexpr bool is_type_v = std::is_same_v<T, Type>;

public:
    template<typename OnNext, typename OnError, typename OnCompleted>
    observer_state(OnNext&& on_next, OnError&& on_error, OnCompleted&& on_completed)
        : m_on_next{std::forward<OnNext>(on_next)}
        , m_on_err{std::forward<OnError>(on_error)}
        , m_on_completed{std::forward<OnCompleted>(on_completed)} {}

    template<typename U>
    void on_next(U&& val) const
    {
        static constexpr bool s_is_expect_forwardable = is_type_v<Decayed>   || is_type_v<const Decayed> || is_type_v<const Decayed&>;
        static constexpr bool s_is_expect_ref         = is_type_v<Decayed&>;
        static constexpr bool s_is_expect_rvalue_ref  = is_type_v<Decayed&&> || is_type_v<const Decayed&&>;
        if constexpr (s_is_expect_forwardable)
        {
            m_on_next(std::forward<U>(val));
        }
        else if constexpr (s_is_expect_ref)
        {
            if constexpr (std::is_same_v<U, Decayed&> || std::is_same_v<U, Decayed>)
                m_on_next(val);
            else
            {
                Decayed temp{std::forward<U>(val)};
                m_on_next(temp);
            }
        }
        else if constexpr (s_is_expect_rvalue_ref)
        {
            if constexpr (std::is_lvalue_reference_v<U>)
                m_on_next(Decayed{val});
            else
                m_on_next(std::forward<U>(val));
        }
        else
            static_assert(!s_is_expect_forwardable && !s_is_expect_ref && !s_is_expect_rvalue_ref, "Some unsupported type detected!");
    }

    void on_error(const std::exception_ptr err) const
    {
        m_on_err(err);
    }

    void on_completed() const
    {
        m_on_completed();
    }

private:
    std::function<void(Type)>               m_on_next{}; // std::function makes extra move/copy sometimes.
    std::function<void(std::exception_ptr)> m_on_err{};
    std::function<void()>                   m_on_completed{};
};
} // namespace rpp::details
