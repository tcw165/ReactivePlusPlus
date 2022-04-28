#pragma once

#include <rpp/observables/member_overload.hpp>

namespace rpp::details
{
struct publish_tag;
}
namespace rpp::operators
{
/**
 * \copydoc rpp::details::member_overload::publish
 */
template<typename ...Args>
auto publish() requires details::is_header_included<details::publish_tag, Args...>;
} // namespace rpp::operators

namespace rpp::details
{
template<constraint::decayed_type Type, typename SpecificObservable>
struct member_overload<Type, SpecificObservable, publish_tag>
{
    /**
    * \brief converts ordinary observable to Connectable Observable with help of rpp::subjects::publish_subject
    * \details Connectable observable is common observable, but actually it starts emissions of items only after call "connect", "ref_count" or any other available way. Also it uses subject to multicast values to subscribers
    *
    * \snippet publish.cpp publish
    *
    * \see https://reactivex.io/documentation/operators/publish.html
    *
    * \return new specific_observable with the publish operator as most recent operator.
    * \warning #include <rpp/operators/publish.h>
    * \ingroup operators
    */
    template<typename ...Args>
    auto publish() const& requires is_header_included<publish_tag, Args...>
    {
        return publish_impl(*static_cast<const SpecificObservable*>(this));
    }

    template<typename ...Args>
    auto publish() && requires is_header_included<publish_tag, Args...>
    {
        return publish_impl(std::move(*static_cast<SpecificObservable*>(this)));
    }

private:
    template<constraint::decayed_same_as<SpecificObservable> TThis>
    static auto publish_impl(TThis&& observable);
};
} // namespace rpp::details