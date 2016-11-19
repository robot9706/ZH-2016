#include <stdio.h>
#include <string.h>
#include <stdint.h>

void F6306(FILE *fIn, FILE *fOut)
{
	int mode;
	int columns;
	int key[10];
	char input[201];

	fscanf(fIn, "%d %d", &mode, &columns);
	int i;
	for (i = 0; i < columns; i++)
	{
		fscanf(fIn, "%d", &key[i]);
	}

	fscanf(fIn, "%s", &input);

	int inputLength = strlen(input);
	int rows = inputLength / columns;

	int j;
	if (mode == 1) //Encode
	{
		for (j = 0; j < rows; j++)
		{
			for (i = 0; i < columns; i++)
			{
				int index = key[i] - 1;

				char c = input[j * columns + index];
				fprintf(fOut, "%c", c);
			}
		}

		fprintf(fOut, "\n");
	}
	else if (mode == 2) //Decode
	{
		char output[201];

		int s = 0;
		for (j = 0; j < rows; j++)
		{
			for (i = 0; i < columns; i++)
			{
				int index = key[i] - 1;

				output[j * columns + index] = input[s];
				s++;
			}
		}

		output[s] = '\0';

		fprintf(fOut, "%s\n", output);
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

	F6306(fIn, fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
