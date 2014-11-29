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

#include "murmur_hash.h"

namespace foundation
{
	uint64_t murmur_hash_64(const void * key, uint32_t len, uint64_t seed)
	{
		const uint64_t m = 0xc6a4a7935bd1e995ULL;
		const uint32_t r = 47;

		uint64_t h = seed ^ (len * m);

		const uint64_t * data = (const uint64_t *)key;
		const uint64_t * end = data + (len/8);

		while(data != end)
		{
			#ifdef PLATFORM_BIG_ENDIAN
				uint64 k = *data++;
				char *p = (char *)&k;
				char c;
				c = p[0]; p[0] = p[7]; p[7] = c;
				c = p[1]; p[1] = p[6]; p[6] = c;
				c = p[2]; p[2] = p[5]; p[5] = c;
				c = p[3]; p[3] = p[4]; p[4] = c;
			#else
				uint64_t k = *data++;
			#endif

			k *= m;
			k ^= k >> r;
			k *= m;
			
			h ^= k;
			h *= m;
		}

		const unsigned char * data2 = (const unsigned char*)data;

		switch(len & 7)
		{
		case 7: h ^= uint64_t(data2[6]) << 48;
		case 6: h ^= uint64_t(data2[5]) << 40;
		case 5: h ^= uint64_t(data2[4]) << 32;
		case 4: h ^= uint64_t(data2[3]) << 24;
		case 3: h ^= uint64_t(data2[2]) << 16;
		case 2: h ^= uint64_t(data2[1]) << 8;
		case 1: h ^= uint64_t(data2[0]);
				h *= m;
		};
		
		h ^= h >> r;
		h *= m;
		h ^= h >> r;

		return h;
	}
}