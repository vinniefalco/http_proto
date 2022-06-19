//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/http_proto
//

// Test that header file is self-contained.
#include <boost/http_proto/response_view.hpp>

#include "test_suite.hpp"

namespace boost {
namespace http_proto {

class response_view_test
{
public:
    void
    run()
    {
    }
};

TEST_SUITE(
    response_view_test,
    "boost.http_proto.response_view");

} // http_proto
} // boost

