//
// Copyright (c) 2022 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/http_proto
//

#ifndef BOOST_HTTP_PROTO_BODY_SOURCE_HPP
#define BOOST_HTTP_PROTO_BODY_SOURCE_HPP

#include <boost/http_proto/string_view.hpp>
#include <boost/http_proto/error_types.hpp>
#include <boost/buffers/source.hpp>
#include <new>

namespace boost {
namespace http_proto {

struct media_type_tag {};

//-----------------------------------------------

class BOOST_SYMBOL_VISIBLE
    body
    : public buffers::source
{
public:
    virtual ~body() = 0;

    virtual
    std::uint64_t const*
    content_length() const noexcept
    {
        return nullptr;
    }

    virtual
    string_view
    media_type() const noexcept = 0;

    virtual
    void
    rewind() = 0;

    virtual
    result<void>
    seek(std::uint64_t offset) = 0;
};

//-----------------------------------------------

template<class Source>
class BOOST_SYMBOL_VISIBLE
    source_body
    : public body
{
    static_assert(
        buffers::is_source<Source>::value,
        "Type requirements not met.");

    Source s_;

    Source&
    get() noexcept
    {
        return *reinterpret_cast<
            Source*>(s_);
    }

    Source const&
    get() const noexcept
    {
        return *reinterpret_cast<
            Source const*>(s_);
    }

public:
    template<class Source_>
    explicit
    source_body(
        Source_&& f)
        : f_(std::forward<Source_>(f))
    {
    }

    std::uint64_t const*
    content_length() const noexcept
    {
        return get().size();
    }

    string_view
    media_type() const noexcept override
    {
        return tag_invoke(
            media_type_tag{}, get());
    }

    void
    rewind()
    {
        get().rewind();
    }

    // ??
    result<void>
    seek(std::uint64_t offset);

private:
    results
    on_read(
        buffers::mutable_buffer b) override
    {
        return get().read(b);
    }

    results
    on_read(
        buffers::mutable_buffer_span bs) override
    {
        return get().read(bs);
    }
};

} // http_proto
} // boost

#endif
