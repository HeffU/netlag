/**********************************************************************
bitsquid foundation
Copyright(C) 2012 Bitsquid AB

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation
files(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and / or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions :

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************/

#pragma once

#include "collection_types.h"
#include "array.h"

#include <string.h>
#include <stdio.h>

#include "snprintf_msvc.h"

namespace foundation
{
	/// Functions for operating on an Array<char> as a stream of characters,
	/// useful for string formatting, etc.
	namespace string_stream
	{
		typedef Array<char> Buffer;

		/// Dumps the item to the stream using a default formatting.
		Buffer & operator<<(Buffer &b, char c);
		Buffer & operator<<(Buffer &b, const char *s);
		Buffer & operator<<(Buffer &b, float f);
		Buffer & operator<<(Buffer &b, int32_t i);
		Buffer & operator<<(Buffer &b, uint32_t i);
		Buffer & operator<<(Buffer &b, uint64_t i);

		/// Uses printf to print formatted data to the stream.
		Buffer & printf(Buffer &b, const char *format, ...);

		/// Pushes the raw data to the stream.
		Buffer & push(Buffer &b, const char *data, uint32_t n);

		/// Pads the stream with spaces until it is aligned at the specified column.
		/// Can be used to column align data. (Assumes each char is 1 space wide,
		/// i.e. does not work with UTF-8 data.)
		Buffer & tab(Buffer &b, uint32_t column);

		/// Adds the specified number of c to the stream.
		Buffer & repeat(Buffer &b, uint32_t count, char c);

		/// Returns the stream as a C-string. There will always be a \0 character
		/// at the end of the returned string. You don't have to explicitly add it
		/// to the buffer.
		const char *c_str(Buffer &b);
	}

	namespace string_stream_internal
	{
		using namespace string_stream;

		template <typename T>
		inline Buffer &printf_small(Buffer &b, const char *fmt, const T &t)
		{
			char s[32];
			snprintf(s, 32, fmt, t);
			return (b << s);
		}
	}

	namespace string_stream
	{
		inline Buffer & operator<<(Buffer &b, char c)
		{
			array::push_back(b, c);
			return b;
		}

		inline Buffer & operator<<(Buffer &b, const char *s)
		{
			return push(b, s, strlen(s));
		}

		inline Buffer & operator<<(Buffer &b, float f)
		{
			return string_stream_internal::printf_small(b, "%g", f);
		}

		inline Buffer & operator<<(Buffer &b, int32_t i)
		{
			return string_stream_internal::printf_small(b, "%d", i);
		}

		inline Buffer & operator<<(Buffer &b, uint32_t i)
		{
			return string_stream_internal::printf_small(b, "%u", i);
		}

		inline Buffer & operator<<(Buffer &b, uint64_t i)
		{
			return string_stream_internal::printf_small(b, "%01llx", i);
		}

		inline Buffer & push(Buffer &b, const char *data, uint32_t n)
		{
			unsigned int end = array::size(b);
			array::resize(b, end + n);
			memcpy(array::begin(b) + end, data, n);
			return b;
		}

		inline const char *c_str(Buffer &b)
		{
			// Ensure there is a \0 at the end of the buffer.
			array::push_back(b, '\0');
			array::pop_back(b);
			return array::begin(b);
		}
	}
}