#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int pow(int base, int exp)
{
	int i;
	long long int res = 1;

	for (i = 0; i<exp; i++)
	{
		res = base * res;
	}

	return res;
}

void split(char *num, char *whole, char *decimal)
{
	int i, j;

	for (i = 0; (num[i] != '.') && (num[i] != 0); i++) {
		whole[i] = num[i];
	}
	whole[i] = 0;
	
	if (num[i] == '.')
	{
		j = 0;
		for (i = i + 1; num[i] != 0; i++) {
			decimal[j] = num[i];
			j++;
		}
		decimal[j] = 0;
	}
	else
	{
		decimal[0] = 0;
	}
}

void fromBase2(FILE *fOut, char *srcNumber)
{
	int i, num;
	char whole[61], decimal[61];
	
	split(srcNumber, whole, decimal);

	long double resWhole = 0.0;

	int wholeLength = strlen(whole);
	for (i = 0; whole[i] != '\0'; i++)
	{
		num = whole[i] - '0';
		resWhole += num * pow(2, wholeLength - i - 1);
	}

	int decLength = strlen(decimal);
	long double resDecimal = 0.0;
	if (decLength != 0)
	{
		long double decimalTemp = 0.0;

		for (i = 0; decimal[i] != '\0'; i++)
		{
			decimalTemp = decimal[i] - '0';
			if (decimalTemp != 0)
			{
				resDecimal += decimalTemp / pow(2, i + 1);
			}
		}
	}

	char buffer[64];
	sprintf(buffer, "%.16Lf", resDecimal);

	for (i = 0; i<15; i++) { buffer[i] = buffer[i + 2]; }
	buffer[15] = 0;
	fprintf(fOut, "10 %.0Lf.%s\n", resWhole, buffer);
}

void fromBase10(FILE *fOut, char *srcNumber)
{
	int i, j, num, exp;
	char whole[64], decimal[64];

	split(srcNumber, whole, decimal);

	int wholeLength = strlen(whole);
	int decimalLength = strlen(decimal);

	long long int rem = 0;
	for (i = 0; i < wholeLength; i++)
	{
		num = whole[i] - '0';
		rem = rem * 10 + num;
	}

	exp = 1;
	while (rem / 2 != 0) {
		rem /= 2;
		exp++;
	}
	rem = 0;

	for (i = 0; i < wholeLength; i++)
	{
		num = whole[i] - '0';
		rem = rem * 10 + num;
	}

	char result[128];

	for (i = 0; i < exp; i++)
	{
		num = rem / pow(2, exp - i - 1);
		rem = rem % pow(2, exp- i - 1);
		result[i] = 48 + num;
	}

	if (decimalLength != 0)
	{
		long double decRem, decNum;
		decRem = 0.0;

		result[i] = '.';
		i++;
		for (j = 0; j < decimalLength; j++)
		{
			decNum = decimal[j] - '0';
			if (decNum != 0) {
				decRem += decNum / pow(10, j + 1);
			}
		}
		for (j = 0; j<30; j++) {
			decRem *= 2;
			if (decRem >= 1)
			{
				num = 1;
				decRem -= 1;
			}
			else
			{
				num = 0;
			}
			result[i] = 48 + num;
			i++;
		}
	}
	else
	{
		result[i] = '.';
		i++;
		for (j = 0; j<30; j++) {
			result[i] = '0';
			i++;
		}
	}
	result[i] = 0;

	fprintf(fOut, "2 %s\n", result);
}

void F6303(FILE *fIn, FILE *fOut)
{
	int system;
	char number[256];

	fscanf(fIn, "%d %s", &system, &number);

	if (system == 2)
	{
		fromBase2(fOut, number);
	}
	else if (system == 10)
	{
		fromBase10(fOut, number);
	}
}

int main()
{
	FILE *fIn;
	FILE *fOut;

	fIn = fopen("be.txt", "r");
	if (fIn == NULL)
	{
		return 1;
	}

	fOut = fopen("ki.txt", "w");
	if (fOut == NULL)
	{
		fclose(fIn);

		return 1;
	}

	F6303(fIn, fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}