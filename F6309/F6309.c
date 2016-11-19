#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define bool int
#define true 1
#define false 0

#define ALPHABET_LENGTH 26
#define UPPERCASE_SHIFT ('a' - 'A')

bool isUppercase(char c)
{
	int i = c - 'A';

	return (i >= 0 && i < ALPHABET_LENGTH);
}

void F6309(FILE *fIn, FILE *fOut)
{
	char key[27];
	char mode;
	char input[256];

	fscanf(fIn, "%s\n", &key);
	fscanf(fIn, "%c", &mode);
	fscanf(fIn, "%s", &input);

	int inputLength = strlen(input);

	int i, j;

	int keyLength = strlen(key);
	for (i = 0; i < keyLength; i++)
	{
		if (isUppercase(key[i]))
			key[i] = key[i] + UPPERCASE_SHIFT;
	}

	if (mode == 'K') //Encode
	{
		for (i = 0; i < inputLength; i++)
		{
			char inChar = input[i];
			int idx = -1;
			bool uppercase = true;

			idx = inChar - 'A';
			if (idx < 0 || idx > ALPHABET_LENGTH - 1)
			{
				uppercase = false;
				idx = inChar - 'a';
			}

			char codeChar = key[idx];
			if (uppercase)
				codeChar -= UPPERCASE_SHIFT;

			fprintf(fOut, "%c", codeChar);
		}

		fprintf(fOut, "\n");
	}
	else if (mode == 'D') //Decode
	{
		for (i = 0; i < inputLength; i++)
		{
			char inChar = input[i];
			bool uppercase = isUppercase(inChar);
			if (uppercase)
				inChar += UPPERCASE_SHIFT;

			int alphabetIndex = 0;
			for (j = 0; j < keyLength; j++)
			{
				if (key[j] == inChar)
				{
					alphabetIndex = j;
					break;
				}
			}

			char decChar = 'a' + alphabetIndex;
			if (uppercase)
				decChar -= UPPERCASE_SHIFT;

			fprintf(fOut, "%c", decChar);
		}

		fprintf(fOut, "\n");
	}
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

	F6309(fIn, fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
