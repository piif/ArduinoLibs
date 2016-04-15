vprintf lib
=====

Author
-----

Christian Lefebvre : christian underscore lefebvre at laposte dot net

Released under LGPL


Intro
-----
This library defines a generic reduced printf like function :
"Generic" because it take a "write single char" function as argument, thus let the caller define its own low level function to display chars. Then, it can be used to send strings to serial, or to a LCD display, i2c debug interface or whatever you think of
"Reduced" because it implements only a subset of posix printf formats.

Description
-----
The prototype of the main function is :

    int gvprintf(writeCharFunc writeChar, char *fmt, va_list ap);

The "writeCharFunc" argument is a function to pass as an argument to delegate "send one char" action
"fmt" is a format string, containing %... constructions
"va_list" argument is to nest this function into a user defined one this a "..." argument

Formats
-----
Following formats are defined :

  *  %c : expects a char and displays it as a char
  *  %s : expects a char* and displays it as a string
  *  %S : expects a PROGMEM char* and displays it as a string
  *  %d : expects a int and displays it has decimal signed value
  *  %u : expects a int and displays it has decimal unsigned value
  *  %x : expects a int and displays it has hexadecimal unsigned value
  *  %b : expects a int and displays it has binary unsigned value
  *  %% : prints a single '%'

d, u, x and b formats can be prefixed by 1, 2 or 4 to specify argument is 1, 2 or 4 bytes width
For example, "%4x" format with 0x1234 argument displays "1234", but "%2x" display "34"
Default is 2 (sizeof int) on arduino

Example
-----
Let define a basic writeChar function :

	void writeChar(char c) {
		Serial.write(c);
	}

Then, simply define a user function :

	int printString(char *fmt, ...) {
		va_list ap;
		va_start(ap, fmt);
		return gvprintf(writeChar, fmt, ap);
	}

That's all ! now, caller can do :

	printString("Here is %dst %s\n", 1, "example");

And output on serial console will be

	Here is 1st example
