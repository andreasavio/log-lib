#include <log_lib/logger.hpp>

#include <gtest/gtest.h>

#include <sstream>


TEST(multiple_streams, log) {
    const auto log_msg = "Multiple streams";

    std::ostringstream stream_1, stream_2;
    log_lib::logger lg(&stream_1, &stream_2);
    lg() << log_msg;

    EXPECT_EQ(stream_1.str(), log_msg);
    EXPECT_EQ(stream_2.str(), log_msg);
}
