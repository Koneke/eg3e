#include <stdarg.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

void eprintf(char* buf, const char* fmt, int argCount, ...)
{
	if (0 == argCount)
	{
		strcpy(buf, fmt);
		return;
	}

	void* args[argCount];
	va_list va;

	va_start(va, argCount);
	{
		for (int i = 0; i < argCount; i++)
		{
			args[i] = va_arg(va, void*);
		}
	}
	va_end(va);

	const char* f = fmt;

	while (*f)
	{
		if ('%' == *f)
		{
			char peek = *(f + 1);
			if (peek < '0' || peek > '9') { *buf = *f; f++; continue; } // leave party early

			f++;
			const char* end = f;
			while (*end >= '0' && *end <= '9') { end++; } // find first non-digit

			int arg;
			int len = end - f; // end is the first non-digit, i.e. the format char
			char *tempbuf = malloc((len + 1) * sizeof(char));
			{
				memset(tempbuf, 0, (len + 1));
				memcpy(tempbuf, f, len); // clone [f end)
				sscanf(tempbuf, "%u", &arg); // scanf the arg number from [f end)
			}
			free(tempbuf);

			tempbuf = malloc(2 * sizeof(char)); // temporary fmtstringbuffer, always 2 chars
			{
				sprintf(tempbuf, "%%" "%c", *end); // create our fmtstring for sprintf
				int written = sprintf(buf, tempbuf, args[arg]); // print straight into buf
				*(buf + written) = *(end + 1); // write next char, replacing the \0 from sprintf
				buf += written; // move buf ptr up so we don't overwrite our stuff

				f = end; // set f to point to the format char, f is then auto incd at the end of the whileloop
			}
			free(tempbuf);
		}
		else
		{
			*buf = *f;
			*buf++;
		}

		f++;
	}

	*buf = '\0';
}
