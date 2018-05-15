#include "OPN.h"


int drob(int x) {
	int n = 1;
	while ((x /= 10) > 0) n++;
	return n;
}

int prior(char v)
{
	switch (v)
	{

	case '(': return 1;
	case '+':
	case '-': return 2;
	case '*':
	case '/': return 3;
	case 'e': return 5;
	case ',': return 4;
	}
}

bool is_op(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == 'e' || c == ',';
}

bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

void opn(char *a, char *out)
{
	stack <char> S;
	int i = 0, j = 0;

	for (; a[i] != '\0'; ++i)
	{
		if (is_digit(a[i]))
		{
			out[j] = a[i];
			++j;
		}
		else
		{
			if (j != 0 && out[j - 1] >= '0' && out[j - 1] <= '9')
			{
				out[j] = '_';
				++j;
			}

			if (is_op(a[i]))
			{
				if (S.empty() || prior(S.top()) < prior(a[i]))
				{
					S.push(a[i]);
				}
				else
				{
					while (!S.empty() && (prior(S.top()) >= prior(a[i])))
					{
						out[j++] = S.top();
						S.pop();
					}
					S.push(a[i]);
				}
			}
			else
			{
				if (a[i] == '(')
				{
					S.push(a[i]);
				}
				else
				{
					if (a[i] == ')')
					{
						if (S.empty() || S.top() == '(')
						{
							cout << "Error!";
							_getch();
							exit(1);
						}
						else
						{
							while (S.top() != '(')
							{
								out[j] = S.top();
								S.pop();
								j++;
							}
						}
						S.pop();
					}
				}
			}
		}
	}
	while (!S.empty())
	{
		if (S.top() == '(')
		{
			cout << "Error!";
			_getch(); exit(1);
		}
		else
		{
			out[j] = S.top();
			S.pop();
			j++;
		}
	}
}
float Calc(char *out)
{
	int j = 0, c = 0; float r1 = 0, r2 = 0;

	stack <float> S;
	char num[16];
	char* pEnd = nullptr;
	while (out[j] != '\0')
	{
		if (out[j] == '_') {
			++j;
			continue;
		}
		if (out[j] >= '0' && out[j] <= '9')
		{
			long iNum = strtol(&out[j], &pEnd, 10);
			S.push(iNum);
			j += pEnd - &out[j];
		}
		else
		{
			if (is_op(out[j]))
			{
				r1 = S.top(); S.pop();
				r2 = S.top(); S.pop();
				switch (out[j])
				{
				case ',': S.push(r2 + (r1 * pow(0.1, drob(r1)))); break;
				case 'e': S.push(r2*pow(10, r1)); break;
				case '+': S.push(r2 + r1); break;
				case '-': S.push(r2 - r1); break;
				case '*': S.push(r2*r1); break;
				case '/': S.push(r2 / r1); break;
				}
			}
			++j;
		}
	}
	return (S.top());
}