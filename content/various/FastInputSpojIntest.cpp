//#include "FastInput.h" 
//#pragma once
#include<cstdio>
int readInt() {
	int a, c;
	while ((a = getchar_unlocked()) < 40);
	if (a == '-') return -readInt();
	while ((c = getchar_unlocked()) >= 48) a = a * 10 + c - 480;
	return a - 48;
}

int main() {
    int n, k;
    n = readInt(); k = readInt();
    int res = 0;
    for(int i=0; i<n; ++i) {
      int t = readInt();
      res += (t % k == 0);
    } 
    printf("%d\n", res);
}
