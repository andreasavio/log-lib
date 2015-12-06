#pragma once

#include <memory>
#include <mutex>


namespace log_lib {
namespace detail {

template <typename StreamPtr>
using stream_ptr_to_element = typename std::pointer_traits<StreamPtr>::element_type;

template <typename Char, typename CharTraits = std::char_traits<Char>>
class stream_writer_base {
public:
    using char_type   = Char;
    using char_traits = CharTraits;
    using string_type = std::basic_string<char_type, char_traits>;

    virtual ~stream_writer_base() {}

    virtual void write(const string_type& str) = 0;
};

//!
//! \brief  Wraps a data stream and synchronizes write operations.
//!
//! The stream must have the following type traits:
//! - `char_type`
//! - `traits_type`
//!
//! The following type must be well-defined:
//! \code
//! std::basic_string<char_type, char_traits>
//! \endcode
//!
//! Also, there must be an `operator<<` which takes a string type as defined above and writes it
//! to the stream.
//!
template <typename StreamPtr>
class stream_writer : public stream_writer_base<
    typename stream_ptr_to_element<StreamPtr>::char_type,
    typename stream_ptr_to_element<StreamPtr>::traits_type
> {
    using stream_ptr  = StreamPtr;
    using stream      = stream_ptr_to_element<stream_ptr>;
    using char_type   = typename stream::char_type;
    using char_traits = typename stream::traits_type;
    using base        = stream_writer_base<char_type, char_traits>;

public:
    //!
    //! \brief  Constructor. Requires a pointer to a data stream.
    //!
    stream_writer(stream_ptr p) :
        m_stream(std::move(p))
    {}

    //!
    //! \brief  Writes a log message to the wrapped stream. The operation is thread safe.
    //!
    void write(const typename base::string_type& str) override {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        if (m_stream) *m_stream << str;
    }

private:
    stream_ptr           m_stream;
    std::recursive_mutex m_mutex;
};

template <typename StreamPtr>
auto make_stream_writer(StreamPtr p) -> std::unique_ptr<stream_writer<StreamPtr>> {
    using stream_ptr = stream_writer<StreamPtr>;
    return std::unique_ptr<stream_ptr>(new stream_ptr(std::move(p)));
}

} // namespace detail
} // namespace log_lib
