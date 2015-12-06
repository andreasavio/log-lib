#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <log_lib/logger.hpp>


struct custom_element {
    static const std::string log_msg;
};

const std::string custom_element::log_msg{ "This is a custom element" };

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& stream, const custom_element&) {
    stream << custom_element::log_msg;
    return stream;
}

int main(int argc, char **argv) {
    using namespace std;

    unique_ptr<std::ofstream> file(new ofstream("demo_log_file.txt"));
    auto lg = make_shared<log_lib::logger>(&cout, move(file));

    auto worker_1 = [lg] {
        auto& logger = *lg;
        for (size_t i = 0; i < 100; ++i) LOG_DEBUG(logger) << "Thread 1, log " << i << std::endl;
    };

    auto worker_2 = [lg] {
        auto& logger = *lg;
        for (size_t i = 0; i < 100; ++i) LOG_DEBUG(logger) << "Thread 2, log " << i << std::endl;
    };

    thread th_1(move(worker_1));
    thread th_2(move(worker_2));

    th_1.join();
    th_2.join();

    return 0;
}
