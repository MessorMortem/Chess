
#include "Conversion.h"

int convertLetter(char oldletter)
{
	if (oldletter == 'a' || oldletter == 'A')
	{
		return 0;
	}
	
	else if (oldletter == 'b' || oldletter == 'B')
	{
		return 1;
	}
	
	else if (oldletter == 'c' || oldletter == 'C')
	{
		return 2;
	}
	
	else if (oldletter == 'd' || oldletter == 'D')
	{
		return 3;
	}
	
	else if (oldletter == 'e' || oldletter == 'E')
	{
		return 4;
	}
	
	else if (oldletter == 'f' || oldletter == 'F')
	{
		return 5;
	}
	
	else if (oldletter == 'g' || oldletter == 'G')
	{
		return 6;
	}

	else if (oldletter == 'h' || oldletter == 'H')
	{
		return 7;
	}

	else 
	{
		return 10;
	}

}

int convertNumber(int oldnumber)
{
	return 8 - oldnumber;
}
