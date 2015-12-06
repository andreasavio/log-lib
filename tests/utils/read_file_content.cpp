#include "read_file_content.hpp"

#include <fstream>


namespace log_lib {
namespace tests {

auto read_file_content(const std::string &filepath) -> std::string {
    std::ifstream file(filepath);
    std::string   content(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
    return content;
}

} // namespace tests
} // namespace log_lib
