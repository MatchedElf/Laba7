#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* dtoa(double num, int npos, int nfr)
{

	if( (npos <= 0) || (nfr < 0) ) return NULL;

	int i;

	int count = 0;

	int start = 0;

	int num1 = fabs(num);

	char* str;

	str = (char*)calloc(npos, sizeof(char));

	long double drob;

	drob = fabs(num) - (int)fabs(num);

	if ( (num < 0) && ( (nfr != 0) || (drob * 10 >= 5) || (num1 < -1) ) )
	{

		str[0] = '-';

		count++;

		start = 1;
	}

	if (num1 > 0)
	{
		while (num1 > 0)
		{
			count++;

			num1 /= 10;
		}
	}
	else count++;

	num1 = fabs(num);

	if ( ( (npos != count) & (nfr == 0) ) || (npos != (count + nfr + 1) ) & (nfr > 0) )
	{
		free(str);

		return NULL;
	}

	for (i = count - 1; i >= start; i--)
	{
		str[i] = (num1 % 10) + '0';

		num1 /= 10;
	}


	if (nfr != 0)
	{
		str[count] = ',';

		for (i = count + 1; i < npos; i++)
		{
			drob *= 10;

			str[i] = (int)drob + '0';

			drob -= (int)drob;
		}

	}

	drob *= 10;

	for (int i = 0; i < npos + 1; i++) printf("%c", str[i]);

	if ( ((int)drob >= 5) & (nfr > 0) )
	{
		if (str[npos - 1] == '9')
		{
			str[npos - 1] = '0';

			str[npos - 2]++;

			for (i = npos - 2; i > count; i--)
			{
				if (str[i] == ':')
				{
					str[i] = '0';

					str[i - 1]++;
				}
				else
				{
					//str[i]++;

					break;
				}
			}
		}
		else
		{
			str[npos - 1]++;
		}
	}

	if (str[count] == '-')
	{
		str[count] = ',';

		str[count - 1]++;
	}

	if ((int)drob >= 5)
	{
		if (nfr == 0)
		{
			if (str[npos - 1] == '9')
			{
				str[npos - 1] = '0';

				if( (npos - 1) != start) str[npos - 2]++;

				for (i = count - 1; i >= start; i--)
				{
					if (str[i] == ':')
					{
						str[i] = '0';

						if (i != start) str[i - 1]++;
					}
					else
					{
						//if (nfr == 0) str[i]++;

						if(str[i - 1] != ':') break;
					}
				}
			}
			else str[npos - 1]++;
		}
		else
		{
			for (i = count - 1; i >= start; i--)
			{
				if (str[i] == ':')
				{
					str[i] = '0';

					if (i != start) str[i - 1]++;
				}
				else break;
			}
		}
	}

	if ( (str[start] == '0') && ((int)num != 0) )
	{
		str = (char*)realloc(str, (npos + 1) * sizeof(char));

		str[start] = '1';

		for (i = start + 1; i <= npos; i++)
		{
			str[i] = '0';

			if (i == count + 1) str[i] = ',';
		}
	}

	printf("\ncount = %d start = %d drob = %d %lf\n", count, start,(int)drob, drob);

	return str;

}

int main()
{
	char* str;

	double num;

	int npos;

	int nfr;

	printf("Enter the number\n");
	scanf("%lf", &num);

	printf("Enter the number of all signs\n");
	scanf("%d", &npos);

	printf("Enter the number of signs after ','\n");
	scanf("%d", &nfr);

	str = dtoa(num, npos, nfr);

	if (str == NULL)
	{
		printf("Error");

		free(str);

		return 0;
	}

	for (int i = 0; i < npos; i++) printf("%c", str[i]);

	free(str);

	return 0;
}
