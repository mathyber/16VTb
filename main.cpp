#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

char numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };

int charToNumber(char mychar) {
	switch (mychar) {
		case char('0') :
			return 0;
		case char('1') :
			return 1;
		case char('2') :
			return 2;
		case char('3') :
			return 3;
		case char('4') :
			return 4;
		case char('5') :
			return 5;
		case char('6') :
			return 6;
		case char('7') :
			return 7;
		case char('8') :
			return 8;
		case char('9') :
			return 9;
		default :
			return -1;
	}
}

bool isInNumbers(char lexem) {
	for (int i = 0; i < sizeof(numbers); i++) {
		if (lexem == numbers[i]) {
			return true;
		}
	}
	return false;
}

int parseLexem(char lexem) {
	if (lexem == char('+')) {
		return 10;
	}
	else
	if (lexem == char('-')) {
		return 11;
	}
	else 
	if (isInNumbers(lexem)) {
		return charToNumber(lexem);
	}
	else {
		return -1;
	}
}

class Lexer {
protected:
	string expression;
public:
	Lexer(string _expression) {
		expression = _expression;
	}

	bool isNumber(int value) {
		return value >= 0 && value <= 9;
	}

	bool isSimpleNumber(int value) {
		return value / 10 >= 1;
	}

	int calculateTemp(int temp, int curr, int next) {
		if (isNumber(next)) {
			if (isSimpleNumber(temp)) {
				return temp * 10 + next;
			}
			else {
				return temp + curr * 10 + next;
			}
		}
		if (temp == 0) {
			return temp + curr;
		}
		return temp;
	}


	int eval() {
		int result = 0;
		int temp = 0;
		int op;

		for (int i = 0; i < expression.size(); i++) {
			int curr = parseLexem(expression[i]);
			int next = parseLexem(expression[i + 1]);

			if (curr == -1) {
				continue;
			}
			else if (isNumber(curr)) {
				temp = calculateTemp(temp, curr, parseLexem(expression[i + 1]));
				continue;
			}
			else if (curr == 11 || curr == 10) {
				result += temp;
				temp = next;
				op = curr;

				while (!isNumber(parseLexem(expression[i + 1]))) {
					i++;
					temp = parseLexem(expression[i + 1]);
				}

				for (i;  isNumber(parseLexem(expression[i + 1])); i++) {
					curr = parseLexem(expression[i]);
					next = parseLexem(expression[i + 1]);
					
					 if (isNumber(curr)) {
						if (isNumber(next)) {
							if (isSimpleNumber(temp)) {
								temp = temp * 10 + next;
								continue;
							} else {
								temp = curr * 10 + next;
								continue;
							}
						}
					} 
				}

				if (op == 11) {
					result -= temp;
				}
				else if (op == 10) {
					result += temp;
				}
				temp = 0;
				continue;
			}
			else {
				continue;
			}
		}
		return result;
	}
};

int main()
{
	string expression;
	cout << "Enter expression? ";
	getline(cin, expression);
	cout << "Your expression is: " << expression << endl;

	Lexer lex(expression);

	cout << "result is: " << lex.eval() << endl;
	system("pause");
}