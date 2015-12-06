#pragma once

#include <ostream>

#define DEFINE_SEVERITY_LEVEL_LOG(severity, str)                 \
    inline std::basic_ostream<char>& operator<<                  \
        (std::basic_ostream<char>& stream, const severity&) {    \
        stream << str;                                           \
        return stream;                                           \
    }                                                            \
                                                                 \
    inline std::basic_ostream<wchar_t>& operator<<               \
        (std::basic_ostream<wchar_t>& stream, const severity&) { \
        stream << str;                                           \
        return stream;                                           \
    }

namespace log_lib {
namespace severity {

//!
//! \brief  Custom type associated with the DEBUG log tag.
//!
struct debug_t {};

//!
//! \brief  Custom type associated with the INFO log tag.
//!
struct info_t  {};

//!
//! \brief  Custom type associated with the WARN log tag.
//!
struct warn_t  {};

//!
//! \brief  Custom type associated with the ERROR log tag.
//!
struct error_t {};

//!
//! \brief  Custom type associated with the FATAL log tag.
//!
struct fatal_t {};

DEFINE_SEVERITY_LEVEL_LOG(debug_t, "DEBUG: ")
DEFINE_SEVERITY_LEVEL_LOG(info_t,  "INFO:  ")
DEFINE_SEVERITY_LEVEL_LOG(warn_t,  "WARN:  ")
DEFINE_SEVERITY_LEVEL_LOG(error_t, "ERROR: ")
DEFINE_SEVERITY_LEVEL_LOG(fatal_t, "FATAL: ")

namespace {

debug_t debug;
info_t  info;
warn_t  warn;
error_t error;
fatal_t fatal;

} // namespace anonymous
} // namespace severity
} // namespace log_lib
