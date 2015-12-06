#pragma once


namespace log_lib {
namespace detail {

//!
//! \brief  Helper struct to retrieve the type traits char_type and char_traits from a logger.
//!
template <typename Logger>
struct logger_traits {
    using char_type   = typename Logger::char_type;
    using char_traits = typename Logger::char_traits;
};

} // namespace detail
} // namespace log_lib
