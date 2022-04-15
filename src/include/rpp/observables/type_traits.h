//                  ReactivePlusPlus library
//
//          Copyright Aleksey Loginov 2022 - present.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/victimsnino/ReactivePlusPlus
//

#pragma once

#include <rpp/observables/fwd.h>

#include <type_traits>

namespace rpp::utils
{
namespace details
{
    template<typename T>
    T extract_observable_type(const virtual_observable<T>&);
} // namespace details

template<typename T>
using extract_observable_type_t = decltype(details::extract_observable_type(std::declval<std::decay_t<T>>()));
} // namespace rpp::utils