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

void F6310(FILE *fIn, FILE *fOut)
{
	char key[27];
	char input[201];

	fscanf(fIn, "%s", &key);
	fscanf(fIn, "%s", &input);

	char mode = (isUppercase(input[0]) ? 'D' : 'K');
	char keyMode = (isUppercase(key[0]) ? 'K' : 'D');

	int keyLength = strlen(key);
	int inputLength = strlen(input);

	int i, j;

	if (mode == 'K') //Encode
	{
		if (keyMode == 'D')
		{
			char keyCopy[27];
			for (i = 0; i < 26; i++)
			{
				keyCopy[i] = key[i];
			}

			for (i = 0; i < 26; i++)
			{
				char findChar = (i + 'a');
				for (j = 0; j < 26; j++)
				{
					if (keyCopy[j] == findChar)
					{
						key[i] = (j + 'A');

						break;
					}
				}
			}
		}

		for (i = 0; i < inputLength; i++)
		{
			fprintf(fOut, "%c", key[input[i] - 'a']);
		}
	}
	else if (mode == 'D') //Decode
	{
		if (keyMode == 'K')
		{
			char keyCopy[27];
			for (i = 0; i < 26; i++) {
				keyCopy[i] = key[i];
			}

			for (i = 0; i < 26; i++)
			{
				char findChar = (i + 'A');
				for (j = 0; j < 26; j++)
				{
					if (keyCopy[j] == findChar)
					{
						key[i] = (j + 'a');

						break;
					}
				}
			}
		}

		for (i = 0; i < inputLength; i++)
		{
			fprintf(fOut, "%c", key[input[i] - 'A']);
		}
	}

	fprintf(fOut, "\n");
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

	F6310(fIn, fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
