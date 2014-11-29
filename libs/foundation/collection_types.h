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

#include "types.h"
#include "memory_types.h"

/// All collection types assume that they are used to store POD objects. I.e. they:
///
/// * Don't call constructors and destructors on elements.
/// * Move elements with memmove().
///
/// If you want to store items that are not PODs, use something other than these collection
/// classes.
namespace foundation
{
	/// Dynamically resizable array of POD objects.
	template<typename T> struct Array
	{
		Array(Allocator &a);
		~Array();
		Array(const Array &other);
		Array &operator=(const Array &other);
		
		T &operator[](uint32_t i);
		const T &operator[](uint32_t i) const;

		Allocator *_allocator;
		uint32_t _size;
		uint32_t _capacity;
		T *_data;
	};

	/// A double-ended queue/ring buffer.
	template <typename T> struct Queue
	{
		Queue(Allocator &a);

		T &operator[](uint32_t i);
		const T &operator[](uint32_t i) const;

		Array<T> _data;
		uint32_t _size;
		uint32_t _offset;
	};

	/// Hash from an uint64_t to POD objects. If you want to use a generic key
	/// object, use a hash function to map that object to an uint64_t.
	template<typename T> struct Hash
	{
	public:
		Hash(Allocator &a);
		
		struct Entry {
			uint64_t key;
			uint32_t next;
			T value;
		};

		Array<uint32_t> _hash;
		Array<Entry> _data;
	};
}