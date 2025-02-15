//                   ReactivePlusPlus library
// 
//           Copyright Aleksey Loginov 2022 - present.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           https://www.boost.org/LICENSE_1_0.txt)
// 
//  Project home: https://github.com/victimsnino/ReactivePlusPlus

#pragma once

#include <rpp/subscribers/constraints.hpp>
#include <rpp/operators/details/subscriber_with_state.hpp>
#include <rpp/subscriptions/composite_subscription.hpp>

#include <memory>
#include <mutex>

namespace rpp::details
{
struct forwarding_on_next_under_lock
{
    template<typename T, typename TSerializationPrimitive>
    void operator()(T&& v, const auto& subscriber, const std::shared_ptr<TSerializationPrimitive>& primitive) const
    {
        std::lock_guard lock{*primitive};
        subscriber.on_next(std::forward<T>(v));
    }
};

struct forwarding_on_error_under_lock
{
    template<typename TSerializationPrimitive>
    void operator()(const std::exception_ptr&                       err,
                    const auto&                                     subscriber,
                    const std::shared_ptr<TSerializationPrimitive>& primitive) const
    {
        std::lock_guard lock{*primitive};
        subscriber.on_error(err);
    }
};

struct forwarding_on_completed_under_lock
{
    template<typename TSerializationPrimitive>
    void operator()(const auto& subscriber, const std::shared_ptr<TSerializationPrimitive>& primitive) const
    {
        std::lock_guard lock{*primitive};
        subscriber.on_completed();
    }
};

template<typename TSerializationPrimitive, constraint::subscriber TSub>
auto make_serialized_subscriber(TSub&&                                          subscriber,
                                const std::shared_ptr<TSerializationPrimitive>& primitive)
{
    auto sub = subscriber.get_subscription();
    return create_subscriber_with_state<utils::extract_subscriber_type_t<std::decay_t<TSub>>>(std::move(sub),
                                                                                              forwarding_on_next_under_lock{},
                                                                                              forwarding_on_error_under_lock{},
                                                                                              forwarding_on_completed_under_lock{},
                                                                                              std::forward<TSub>(subscriber),
                                                                                              primitive);
}
} // namespace rpp::details
