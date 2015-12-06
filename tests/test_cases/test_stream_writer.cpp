#include <log_lib/stream_writer.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <memory>


TEST(stream_writer, shared_ptr) {
    const auto log_msg = "Test writer shared out";

    auto stream_shared = std::make_shared<std::ostringstream>();
    log_lib::detail::stream_writer<decltype(stream_shared)> sw(stream_shared);
    sw.write(std::string(log_msg));

    EXPECT_EQ(stream_shared->str(), log_msg);
}

TEST(stream_writer, unique_ptr) {
    const auto log_msg = "Test writer unique out";

    std::unique_ptr<std::ostringstream> stream_unique(new std::ostringstream());
    auto buffer_handle = stream_unique->rdbuf();

    log_lib::detail::stream_writer<decltype(stream_unique)> sw(std::move(stream_unique));
    sw.write(log_msg);

    EXPECT_EQ(buffer_handle->str(), log_msg);
}

TEST(stream_writer, naked_ptr) {
    const auto log_msg = "Test writer naked out";

    std::unique_ptr<std::ostringstream> stream_naked(new std::ostringstream());
    log_lib::detail::stream_writer<decltype(stream_naked.get())> sw(stream_naked.get());
    sw.write(log_msg);

    EXPECT_EQ(stream_naked->str(), log_msg);
}
