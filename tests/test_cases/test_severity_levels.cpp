#include <log_lib/logger.hpp>

#include <gtest/gtest.h>

#include <sstream>


TEST(severity_levels , log_debug) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    lg() << log_lib::severity::debug << "Message";
    EXPECT_EQ(stream.str(), "DEBUG: Message");
}

TEST(severity_levels, log_info) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    lg() << log_lib::severity::info << "Message";
    EXPECT_EQ(stream.str(), "INFO:  Message");
}

TEST(severity_levels, log_warn) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    lg() << log_lib::severity::warn << "Message";
    EXPECT_EQ(stream.str(), "WARN:  Message");
}

TEST(severity_levels, log_error) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    lg() << log_lib::severity::error << "Message";
    EXPECT_EQ(stream.str(), "ERROR: Message");
}

TEST(severity_levels, log_fatal) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    lg() << log_lib::severity::fatal << "Message";
    EXPECT_EQ(stream.str(), "FATAL: Message");
}
