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
*	logging.h - Various logging functions
**********************************************************************/
#pragma once

#include "logging.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <mutex>

char logfile[50];
std::mutex mutex;

// Blocks on multithreaded access, might cause slowdowns
// but allows us to log from lua.
int log_internal(const char* message, va_list argptr)
{
	mutex.lock();
	FILE* file = fopen(logfile, "a");
	if (!file) {

		return -1;
	}
	vfprintf(file, message, argptr);
	fprintf(file, "\n");
	fclose(file);
	mutex.unlock();

#ifdef NETLAG_DEBUG
	vfprintf(stdout, message, argptr);
#endif

	return 0;
}

int netlag::utilities::log_start()
{
	logfile[0] = '\0'; // empty in case logger is used multiple times.
	strcpy(logfile, "[netlag]-");
	time_t now = time(NULL);
	char* date = ctime(&now);
	strcat(logfile, date);
	// Remove the trailing newline from ctime
	size_t ln = strlen(logfile) - 1;
	if (logfile[ln] == '\n')
		logfile[ln] = '\0';
	// Replace illegal chars from ctime:
	char* pch;
	pch = strchr(logfile, ':');
	while (pch != NULL)
	{
		*pch = '_';
		pch = strchr(pch + 1, ':');
	}
	strcat(logfile, ".log");

	FILE* file = fopen(logfile, "ab+");
	if (!file) {
		// error handling
		return -1;
	}
	fprintf(file, "[LOG] logging started. local time %s", date);
	fclose(file);

	return 0;
}

int netlag::utilities::log_stop()
{
	time_t now = time(NULL);
	char* date = ctime(&now);
	FILE* file = fopen(logfile, "a");
	if (!file) {
		// error handling
		return -1;
	}
	fprintf(file, "[LOG] logging stopped. local time %s", date);
	fclose(file);

	return 0;
}

int netlag::utilities::log(const char* message, ...) {
	int result;
	va_list argptr;
	va_start(argptr, message);
	result = log_internal(message, argptr);
	va_end(argptr);
	return result;
}

extern "C" {

	__declspec(dllexport) int log_start()
	{
		return netlag::utilities::log_start();
	}

	__declspec(dllexport) int log_stop()
	{
		return netlag::utilities::log_stop();
	}

	__declspec(dllexport) int log_write(const char* message, ...)
	{
		int result;
		va_list argptr;
		va_start(argptr, message);
		result = log_internal(message, argptr);
		va_end(argptr);
		return result;
	}
}