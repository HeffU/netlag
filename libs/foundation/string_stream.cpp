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

#include "string_stream.h"

#include <stdarg.h>

namespace foundation 
{
	namespace string_stream
	{
		Buffer & printf(Buffer &b, const char *format, ...)
		{
			va_list args;
			
			va_start(args, format);
			int n = vsnprintf(NULL, 0, format, args);
			va_end(args);

			uint32_t end = array::size(b);
			array::resize(b, end + n + 1);
			
			va_start(args, format);
			vsnprintf(array::begin(b) + end, n + 1, format, args);
			va_end(args);
			
			array::resize(b, end + n);

			return b;
		}

		Buffer & tab(Buffer &b, uint32_t column)
		{
			uint32_t current_column = 0;
			uint32_t i = array::size(b) - 1;
			while (i != 0xffffffffu && b[i] != '\n' && b[i] != '\r') {
				++current_column;
				--i;
			}
			if (current_column < column)
				repeat(b, column - current_column, ' ');
			return b;
		}

		Buffer & repeat(Buffer &b, uint32_t count, char c)
		{
			for (uint32_t i=0; i<count; ++i)
				array::push_back(b, c);
			return b;
		}
	}
}