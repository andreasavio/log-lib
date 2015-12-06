#pragma once

#include <vector>

#include <log_lib/recorder.hpp>
#include <log_lib/severity_levels.hpp>
#include <log_lib/stream_writer.hpp>


namespace log_lib {

//!
//! \brief  Bundles together a number of data streams and writes log messages to them.
//!
//! To record a log message, `base_recorder` instantiates a temporary `recorder` object. When `recorder` is
//! destroyed, it writes the log message back to `base_logger`, which in turn propagates it to the data streams.
//!
template <typename Char, typename CharTraits = std::char_traits<Char>>
class base_logger {
public:
    using char_type   = Char;
    using char_traits = CharTraits;

private:
    using this_type     = base_logger<char_type, char_traits>;
    using recorder      = detail::recorder<this_type>;
    using string_type   = typename recorder::string_type;
    using stream_writer = std::shared_ptr<detail::stream_writer_base<char_type, char_traits>>;

public:
    //!
    //! \brief  Constructor. Takes a list of pointers to data streams.
    //!
    //! Example:
    //! \code
    //! std::unique_ptr<std::ofstream> file_stream("file.txt")
    //! std::base_logger<char> lg(std::move(file_stream), &std::cout);
    //! \endcode
    //!
    //! Log messages written to `base_logger` will be propagated to each stream.
    //!
    template <typename... StreamPtrs>
    base_logger(StreamPtrs... streams) :
        m_writers({ detail::make_stream_writer(std::move(streams))... })
    {}

    //!
    //! \brief  Instantiates a recorder and returns it.
    //!
    //! Upon destruction, the recorder will write its buffer to the logger.
    //!
    //! Example:
    //! \code
    //! std::base_logger<char> lg(&std::cout);
    //! lg() << "LOG MESSAGE"; // Prints "LOG MESSAGE" to std::cout
    //! \endcode
    //!
    auto operator()() -> recorder { return { *this }; }

private:
    std::vector<stream_writer> m_writers;

    friend class detail::recorder<this_type>;

    //!
    //! \brief  Propagates a log entry to the data streams.
    //!
    void write(const string_type& str) {
        for (auto& writer : m_writers) writer->write(str);
    }
};

using logger  = base_logger<char>;
using wlogger = base_logger<wchar_t>;

} // namespace log_lib

#define LOG_DEBUG(logger) logger() << log_lib::severity::debug << __FILE__ << " " << __LINE__ << " "
#define LOG_INFO(logger)  logger() << log_lib::severity::info  << __FILE__ << " " << __LINE__ << " "
#define LOG_WARN(logger)  logger() << log_lib::severity::warn  << __FILE__ << " " << __LINE__ << " "
#define LOG_ERROR(logger) logger() << log_lib::severity::error << __FILE__ << " " << __LINE__ << " "
#define LOG_FATAL(logger) logger() << log_lib::severity::fatal << __FILE__ << " " << __LINE__ << " "
