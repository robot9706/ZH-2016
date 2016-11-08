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
		return (c - 'A') + 10;
	}
	else if (c >= 'a' && c <= 'z')
	{
		return (c - 'a') + 10;
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

	return 'a' + (num - 10);
}

int F6302(FILE* fIn, FILE* fOut)
{
	int sourceSystem;
	int targetSystem;
	char number[128];
	char dir[3];

	fscanf(fIn, "%d%2c%d %s", &sourceSystem, &dir, &targetSystem, &number);

	if (dir[0] == '<' && dir[1] == '-')
	{
		int temp = sourceSystem;
		sourceSystem = targetSystem;
		targetSystem = temp;
	}

	if (sourceSystem != 10 && targetSystem != 10)
	{
		return 0;
	}
	if (sourceSystem < 2 || sourceSystem > 36)
	{
		return 0;
	}
	if (targetSystem < 2 || targetSystem > 36) 
	{
		return 0;
	}

	unsigned long long int base10 = 0;

	int x;
	unsigned long long int exponent = 1;
	for (x = strlen(number) - 1; x >= 0; x--)
	{
		char c = number[x];
		int placeValue = getCharValue(c);
		if (placeValue == -1 || !isNumValidForSystem(placeValue, sourceSystem))
		{
			return 0;
		}

		base10 += placeValue * exponent;

		exponent *= sourceSystem;
	}

	if (sourceSystem == 10)
	{
		char newNum[200];
		int index = 0;
		while (base10 != 0)
		{
			unsigned long long int div = base10 / targetSystem;
			unsigned long long int rem = base10 % targetSystem;

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
	}
	else
	{
		fprintf(fOut, "%llu\n", base10);
	}

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

	if (!F6302(fIn, fOut))
	{
		fprintf(fOut, "HIBA\n");
	}

	fclose(fIn);
	fclose(fOut);

	return 0;
}
