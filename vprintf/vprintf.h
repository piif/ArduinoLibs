/**
 * copyright Christian Lefebvre 2016, released under LGPL
 */

#ifndef VPRINTF_H
#define VPRINTF_H

#include <stdarg.h>

typedef void (*writeCharFunc)(char c);

int gvprintf(writeCharFunc writeChar, char *fmt, va_list ap);

#endif
