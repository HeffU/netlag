/**********************************************************************
netlag - Shenanigans in Virtual Reality
Copyright(C) 2014 Rasmus Egerö <heff@heff.se>

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/
***********************************************************************
*	hashing.h - Various hashing functions
**********************************************************************/
#pragma once

namespace netlag
{
	namespace utilities
	{
		// Dan Bernstein's djb2 hash
		// [http://www.cse.yorku.ca/~oz/hash.html]

		unsigned long djb2hash(unsigned char *str) {
			unsigned long hash = 5381;
			int c;

			while (c = *str++) {
				hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
			}
			return hash;
		}
	}
}