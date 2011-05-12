#include "stdio.h"
#include "internal_shell.h"
#include "../drivers/video.h"
#include "../drivers/keyboard.h"

void putchar(char c)
{
	if (c == '\n')
		newLine();
	else if (c != 0 )
	{
		putChar(c);
		putC(c);
	}
}

char getchar()
{
	char c;
	while((c = getC()) != '\n') putchar(c);
	putchar(c);
	return c;
}

double atof(char*string) {
	int sign = 1;
	int decount = 0;
	int i = 0;
	double result = 0.0;
	double decimals = 0.1;

	while (string[i] != '\0') {
		if (string[i] == '.') {
			decount = 1;
			i++;
		} else {
			if (!decount) {
				if (string[i] == '-') {
					i++;
					sign = -1;
				} else {
					result = result * 10 + (string[i] - ASCIICERO);
					i++;
				}
			} else {
				result = result + decimals * (string[i] - ASCIICERO);
				decimals /= 10;
				i++;
			}
		}
	}
	return result * sign;
}
int atoi(char* string) {

	int i = 0;
	int result = 0;
	int sign = 1;

	while (string[i] != '\0') {
		if (string[i] == '-') {
			sign = -1;
			i++;
		}
		result = result * 10 + (string[i] - ASCIICERO);
		i++;
	}
	return result * sign;

}

void ftoa(float number, char* answ) {

	char ascii0 = ASCIICERO;
	int pos = 0;
	int decimal = 6;

	char sign = FALSE;
	if (number < 0) {
		sign = number < 0 ? TRUE : FALSE;
		number *= -1;
	}
	answ[pos++] = '\0';

	if ((int) number == 0) {
		answ[pos++] = '0';
	}
	/*
	 * This is used to get a integer number.
	 *
	 */
	number *= 1000000;
	number = (int) number;
	while (decimal) {
		answ[pos++] = (int) number % 10 + ASCIICERO;
		number /= 10;
		decimal--;
	}
	answ[pos++] = '.';
	while ((int) number != 0) {
		answ[pos++] = (int) number % 10 + ASCIICERO;
		number /= 10;

	}

	/*
	 * This is because when it get out of the whie it has been divide per 10, one more time
	 */
	number *= 10;
	if (sign == TRUE)
		answ[pos++] = '-';

	internalswap(answ, pos - 1);

}

void itoa(int number, char* answ) {

	int pos = 0;

	char sign = FALSE;
	if (number < 0) {
		sign = number < 0 ? TRUE : FALSE;
		number *= -1;
	}

	answ[pos++] = '\0';
	if (number == 0)
		answ[pos++] = ASCIICERO;
	else {
		while (number != 0) {
			answ[pos++] = (number % 10) + ASCIICERO;
			number /= 10;
		}
		if (sign == TRUE)
			answ[pos++] = '-';
	}
		internalswap(answ, pos - 1);
}

