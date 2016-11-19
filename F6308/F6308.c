#include <stdio.h>
#include <string.h>
#include <stdint.h>

void F6308(FILE *fIn, FILE *fOut)
{
	char mode;
	char key[101];
	char input[201];

	fscanf(fIn, "%c:%s", &mode, &key);
	fscanf(fIn, "%s", &input);

	int keyLength = strlen(key);

	char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
	int alphabetLength = strlen(alphabet);

	int inputLength = strlen(input);

	int i;
	int j;

	if (mode == 'E') //Encode
	{
		for (i = 0; i < inputLength; i++)
		{
			char inputChar = input[i];

			int keyPos = i % keyLength;
			int shift = key[keyPos] - 'A';

			int pos = 0;
			for (j = 0; j < alphabetLength; j++)
			{
				if (alphabet[j] == inputChar)
				{
					pos = j;
					break;
				}
			}

			pos += shift;

			fprintf(fOut, "%c", alphabet[pos % alphabetLength]);
		}

		fprintf(fOut, "\n");
	}
	else if (mode == 'D') //Decode
	{
		for (i = 0; i < inputLength; i++)
		{
			char inputChar = input[i];

			int keyPos = i % keyLength;
			int shift = key[keyPos] - 'A';

			int pos = 0;
			for (j = 0; j < alphabetLength; j++)
			{
				if (alphabet[j] == inputChar)
				{
					pos = j;
					break;
				}
			}

			pos -= shift;
			if (pos < 0)
			{
				pos = (-pos) % alphabetLength;

				pos = alphabetLength - pos;
			}

			fprintf(fOut, "%c", alphabet[pos % alphabetLength]);
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

	F6308(fIn, fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
