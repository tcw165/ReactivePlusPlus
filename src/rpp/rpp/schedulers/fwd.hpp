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

#include <chrono>
#include <optional>

namespace rpp::schedulers::details
{
struct scheduler_tag {};
struct worker_tag {};
} // namespace rpp::schedulers::details

namespace rpp::schedulers
{
using clock_type = std::chrono::steady_clock;
using time_point = clock_type::time_point;
using duration = std::chrono::nanoseconds;
using optional_duration = std::optional<duration>;

class immediate;
class trampoline;
using current_thread = trampoline;

class new_thread;
class run_loop;
} // namespace rpp::schedulers
