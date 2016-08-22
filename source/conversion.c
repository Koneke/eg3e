#define numbersStart 0xa1
#define alphabetStart 0xbb

char charHexValue[0xff] = {
	[numbersStart] =
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	[alphabetStart] =
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

unsigned char charToHex(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return 26 + alphabetStart + (c - 'a');
	}

	if (c >= 'A' && c <= 'Z')
	{
		return alphabetStart + (c - 'A');
	}

	if (c >= '0' && c <= '9')
	{
		return numbersStart + (c - '0');
	}

	return ' ';
}

char hexToChar(unsigned char x)
{
	if (x == 0x00) return ' ';

	if (x == 0xff) return '~';

	if (x >= numbersStart && x <= numbersStart + 10)
	{
		return '0' + (x - numbersStart);
	}

	if (x >= alphabetStart)
	{
		if (x <= alphabetStart + 26)
			return 'A' + (x - alphabetStart);
		else if (x <= alphabetStart + 26 + 26)
			return 'a' + (x - alphabetStart);
		else
			return '.';
	}

	return '.';
}

void stringToHex(char* string, unsigned char* out)
{
	while (*string)
	{
		*out = charToHex(*string);
		string++;
		out++;
	}
}

void hexToString(unsigned char* hex, int length, char* out)
{
	while (length--)
	{
		*out = hexToChar(*hex);
		hex++;
		out++;
	}
}
