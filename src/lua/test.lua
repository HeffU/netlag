--[[*******************************************************************
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
*	test.lua - work in progress test file
*******************************************************************--]]

print("Lua testing:")

print("Loading FFI:")
local ffi = require("ffi")
ffi.cdef[[
int printf(const char *fmt, ...);
]]
ffi.C.printf("FFI %s!\n", "loaded")

ffi.cdef[[
unsigned long long hash_murmur64
		(const unsigned char *str, unsigned int len);
]]
print("murmur64('lua'): ", ffi.C.hash_murmur64("lua", 3))

print("Testing logging system..")
ffi.cdef[[
int log_write(const char* message, ...);
]]
ffi.C.log_write("[LUA] %s!\n", "log test")

print("Testing done.")


