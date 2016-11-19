#include <stdio.h>
#include <string.h>
#include <stdint.h>

void F6305(FILE *fIn, FILE *fOut)
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
		for (i = 0; i < columns; i++)
		{
			int index = key[i] - 1;

			for (j = 0; j < rows; j++)
			{
				char c = input[j * columns + index];

				fprintf(fOut, "%c", c);
			}
		}

		fprintf(fOut, "\n");
	}
	else if (mode == 2) //Decode
	{
		int s = 0;

		char output[201];

		for (i = 0; i < columns; i++)
		{
			int index = key[i] - 1;

			for (j = 0; j < rows; j++)
			{
				char c = input[s];
				s++;
				output[j * columns + index] = c;
			}
		}
		output[s] = '\0';

		fprintf(fOut, "%s\n", output);;
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

	F6305(fIn, fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
