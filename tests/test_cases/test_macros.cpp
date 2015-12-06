#include <log_lib/logger.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <regex>


TEST(macros, debug) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    LOG_DEBUG(lg) << "Message";
    EXPECT_TRUE(std::regex_match(stream.str(), std::regex{ "^DEBUG: .*test_macros.cpp 12 Message$" }));
}

TEST(macros, info) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    LOG_INFO(lg) << "Message";
    EXPECT_TRUE(std::regex_match(stream.str(), std::regex{ "^INFO:  .*test_macros.cpp 19 Message$" }));
}

TEST(macros, warn) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    LOG_WARN(lg) << "Message";
    EXPECT_TRUE(std::regex_match(stream.str(), std::regex{ "^WARN:  .*test_macros.cpp 26 Message$" }));
}

TEST(macros, error) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    LOG_ERROR(lg) << "Message";
    EXPECT_TRUE(std::regex_match(stream.str(), std::regex{ "^ERROR: .*test_macros.cpp 33 Message$" }));
}

TEST(macros, fatal) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    LOG_FATAL(lg) << "Message";
    EXPECT_TRUE(std::regex_match(stream.str(), std::regex{ "^FATAL: .*test_macros.cpp 40 Message$" }));
}
