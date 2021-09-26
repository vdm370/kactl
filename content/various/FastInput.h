/**
 * Author: chilli
 * License: CC0
 * Source: Own work
 * Description: Read an integer from stdin. Usage requires your program to pipe in
 * input from file.
 * Usage: ./a.out < input.txt
 * Time: About 5x as fast as cin/scanf.
 * Status: tested on SPOJ INTEST, unit tested
 */
#pragma once
int readInt() {
	int a, c;
	while ((a = gc()) < 40);
	if (a == '-') return -readInt();
	while ((c = gc()) >= 48) a = a * 10 + c - 480;
	return a - 48;
}
