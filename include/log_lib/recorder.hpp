#pragma once

#include <sstream>

#include <log_lib/traits.hpp>


namespace log_lib {
namespace detail {

//!
//! \brief  Records a log message and dumps it back to the parent logger upon destruction.
//!
template <typename Logger>
class recorder : public std::basic_ostringstream<
    typename logger_traits<Logger>::char_type,
    typename logger_traits<Logger>::char_traits
> {
    using logger      = Logger;
    using char_type   = typename logger_traits<logger>::char_type;
    using char_traits = typename logger_traits<logger>::char_traits;

public:
    using string_type = typename std::basic_string<char_type, char_traits>;

    //!
    //! \brief  Constructor. Requires a parent logger.
    //!
    recorder(logger& lg)     : m_logger(lg)           {}
    recorder(recorder&& rhs) : m_logger(rhs.m_logger) {}

    //!
    //! \brief  Destructor. Dumps the internal buffer to the parent logger.
    //!
   ~recorder() override {
        m_logger.write(this->str());
    }

private:
    logger& m_logger;
};

} // namespace detail
} // namespace log_lib
