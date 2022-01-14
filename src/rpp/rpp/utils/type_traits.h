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

#include <rpp/fwd.h>

namespace rpp::utils
{
template<typename>
struct extract_subscriber_type;

template<typename Type>
struct extract_subscriber_type<subscriber<Type>>
{
    using type = Type;
};

template<typename Type>
struct extract_subscriber_type : public extract_subscriber_type<std::decay_t<Type>>{};

template<typename T>
using extract_subscriber_type_t = typename extract_subscriber_type<T>::type;

template<typename T>
struct is_observer : std::false_type{};

template<typename T>
struct is_observer<rpp::observer<T>> : std::true_type{};

template<typename T>
constexpr bool is_observer_v = is_observer<T>::value;
} // namespace rpp::utils