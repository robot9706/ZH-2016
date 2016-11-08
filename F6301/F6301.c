#include <stdio.h>
#include <string.h>

int getCharValue(char c)
{
	if (c >= '0' && c <= '9') 
	{
		return c - '0';
	}
	else if (c >= 'A' && c <= 'Z') 
	{
		return c - 'A' + 10;
	}
	else if (c >= 'a' && c <= 'z')
	{
		return c - 'a' + 10;
	}
	
	return -1;
}

int isNumValidForSystem(int num, int system) 
{
	return (num < system);
}

char valueToChar(int num) 
{
	if (num < 10)
		return '0' + num;
	
	return 'A' + (num - 10);
}

int F6301(FILE* fIn, FILE* fOut) 
{
	int originalSys;
	int targetSys;
	char number[128];

	fscanf(fIn, "%d %d %s", &originalSys, &targetSys, &number);

	if (originalSys < 2 || originalSys > 36)
	{
		return 0;
	}

	if (targetSys < 2 || targetSys > 36)
	{
		return 0;
	}

	unsigned long long int base10 = 0;


	int x;
	int exponent = 1;
	for (x = strlen(number) - 1; x >= 0; x--)
	{
		char c = number[x];
		int placeValue = getCharValue(c);
		if (placeValue == -1 || !isNumValidForSystem(placeValue, originalSys))
		{
			return 0;
		}

		base10 += placeValue * exponent;

		exponent *= originalSys;
	}


	char newNum[200];
	int index = 0;
	while (base10 != 0) 
	{
		unsigned long long int div = base10 / targetSys;
		unsigned long long int rem = base10 % targetSys;

		newNum[index] = valueToChar(rem);
		index++;

		base10 = div;
	}

	newNum[index] = '\0';

	int len = strlen(newNum);

	for (x = len - 1; x >= 0; x--) 
	{
		fprintf(fOut, "%c", newNum[x]);
	}
	fprintf(fOut, "\n");

	return 1;
}

int main()
{
	FILE* fIn = fopen("be.txt", "r");
	if (fIn == NULL)
	{
		return 1;
	}

	FILE* fOut = fopen("ki.txt", "w");
	if (fOut == NULL)
	{
		fclose(fIn);

		return 1;
	}

	if (!F6301(fIn, fOut))
	{
		fprintf(fOut, "HIBA\n");
	}

	fclose(fIn);
	fclose(fOut);

    return 0;
}

