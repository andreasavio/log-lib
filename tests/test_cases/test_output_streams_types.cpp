#include <log_lib/logger.hpp>
#include <utils/read_file_content.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <sstream>


TEST(output_streams, std_cout) {
    const auto log_msg = "Test std::cout log";

    // Redirect std::cout to cout_redirect
    std::ostringstream cout_redirect;
    auto cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(cout_redirect.rdbuf());

    log_lib::logger lg(&std::cout);
    lg() << log_msg;

    // Reset original std::cout buffer
    std::cout.rdbuf(cout_buf);

    EXPECT_EQ(cout_redirect.str(), log_msg);
}

TEST(output_streams, file) {
    const auto file_path = "log_file.txt";
    const auto log_msg   = "Test file log";

    remove(file_path);
    {
        std::unique_ptr<std::ofstream> stream(new std::ofstream(file_path));
        log_lib::logger lg(std::move(stream));
        lg() << log_msg;
    }

    EXPECT_EQ(log_lib::tests::read_file_content(file_path), log_msg);
}
