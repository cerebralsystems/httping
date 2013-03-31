/* Released under GPLv2 with exception for the OpenSSL library. See license.txt */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

char last_error[4096] = { 0 };

void error_exit(char *format, ...)
{
	va_list ap;

char *p = NULL;
*p = 1;

	va_start(ap, format);
	(void)vfprintf(stderr, format, ap);
	va_end(ap);

	fprintf(stderr, "\n\nerrno=%d which means %s (if applicable)\n", errno, strerror(errno));

	exit(1);
}

void set_error(const char *fmt, ...)
{
	int buffer_size = sizeof last_error;

	if (last_error[0])
		fprintf(stderr, "%s\n", last_error);

	va_list ap;

	va_start(ap, fmt);
	if (vsnprintf(last_error, sizeof last_error, fmt, ap) >= buffer_size)
		error_exit("Error message '%s' truncated", last_error);
	va_end(ap);
}

void clear_error()
{
	last_error[0] = 0x00;
}

char * get_error()
{
	return last_error;
}
