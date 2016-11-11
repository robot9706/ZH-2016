#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef long long int ull;

int lnko(int a, int b)
{
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;

	while (a != b)
	{
		if (a > b)
			a -= b;
		else if (b > a)
			b -= a;
	}

	return a;
}

int F6304(FILE* fIn, FILE* fOut)
{
	int64_t  szamlalo1 = 0;
	int64_t  nevezo1 = 0;
	int64_t  szamlalo2 = 0;
	int64_t  nevezo2 = 0;
	char muv;

	fscanf(fIn, "%lld:%lld%c%lld:%lld", &szamlalo1, &nevezo1, &muv, &szamlalo2, &nevezo2);
	
	if (nevezo1 == 0 || nevezo2 == 0)
	{
		return 0;
	}

	int64_t szamlaloEr = 0;
	int64_t nevezoEr = 0;
	
	if (nevezo1 < 0)
	{
		nevezo1 *= -1;
		szamlalo1 *= -1;
	}
	if (nevezo2 < 0)
	{
		nevezo2 *= -1;
		szamlalo2 *= -1;
	}

	switch (muv)
	{
	case '+':
		if (nevezo1 != nevezo2)
		{
			nevezoEr = nevezo1 * nevezo2;
			szamlalo1 = (nevezoEr / nevezo1) * szamlalo1;
			szamlalo2 = (nevezoEr / nevezo2) * szamlalo2;

			szamlaloEr = szamlalo1 + szamlalo2;
		}
		else
		{
			nevezoEr = nevezo1;
			szamlaloEr = szamlalo1 + szamlalo2;
		}
		break;
	case '-':
		if (nevezo1 != nevezo2)
		{
			nevezoEr = nevezo1 * nevezo2;
			szamlalo1 = (nevezoEr / nevezo1) * szamlalo1;
			szamlalo2 = (nevezoEr / nevezo2) * szamlalo2;

			szamlaloEr = szamlalo1 - szamlalo2;
		}
		else
		{
			nevezoEr = nevezo1;
			szamlaloEr = szamlalo1 - szamlalo2;
		}
		break;
	case '*':
		szamlaloEr = szamlalo1 * szamlalo2;
		nevezoEr = nevezo1 * nevezo2;
		break;
	case '/':
		szamlaloEr = szamlalo1 * nevezo2;
		nevezoEr = nevezo1 * szamlalo2;
		break;
	}

	if (szamlaloEr == 0)
	{
		nevezoEr = 1;
	}
	else
	{
		int e = lnko(szamlaloEr, nevezoEr);
		szamlaloEr /= e;
		nevezoEr /= e;
	}

	if (nevezoEr < 0)
	{
		szamlaloEr *= -1;
		nevezoEr *= -1;
	}

	fprintf(fOut, "%d:%d\n", szamlaloEr, nevezoEr);

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

	if (!F6304(fIn, fOut))
	{
		fprintf(fOut, "HIBA\n");
	}

	fclose(fIn);
	fclose(fOut);

	return 0;
}
