#include <log_lib/logger.hpp>

#include <gtest/gtest.h>

#include <sstream>


struct custom_type {};

std::ostream& operator<<(std::ostream& stream, const custom_type&) {
    stream << "This is a custom type";
    return stream;
}

TEST(custom_type, log) {
    std::ostringstream stream;
    log_lib::logger lg(&stream);
    lg() << custom_type();
    EXPECT_EQ(stream.str(), "This is a custom type");
}
