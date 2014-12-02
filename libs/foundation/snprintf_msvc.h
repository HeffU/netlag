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

#if defined(_MSC_VER)
	#include <stdarg.h>
	#include <stdio.h>

	inline int vsnprintf_compat(char* buffer, size_t size, const char* format, va_list args)
	{
		int result = -1;
		if (size > 0)
			result = _vsnprintf_s(buffer, size, _TRUNCATE, format, args);
		if (result == -1)
			return _vscprintf(format, args);
	
		return result;	
	}

	inline int snprintf_compat(char* buffer, size_t size, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		int result = vsnprintf_compat(buffer, size, format, args);
		va_end(args);
		return result;
	}

	#define snprintf snprintf_compat
	#define vsnprintf vsnprintf_compat
#endif