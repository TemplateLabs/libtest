#ifndef LIBTEST_EXCEPTION_H
#define LIBTEST_EXCEPTION_H

#include <exception>

namespace test
{
    class exception : public std::exception
    {
	std::string	_filename;
	unsigned	_linenumber;
	std::string	_message;

    public:
	exception(const std::string& filename, const unsigned linenumber, const std::string& message) : _filename(filename), _linenumber(linenumber), _message(message) {}
	exception(const exception&) = default;
	virtual ~exception() noexcept {}

	const std::string& filename()	const { return _filename; }
	unsigned linenumber()		const { return _linenumber; }
	const std::string& message()	const { return _message; }
    };
}

#endif	// LIBTEST_EXCEPTION_H
