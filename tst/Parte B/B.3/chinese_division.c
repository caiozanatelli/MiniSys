#include <stdlib.h>
#include <stdio.h>

// Calculate the remainder through Chinese Division Algorithm
int chineseDivision(int n, int d) {
	int currDivisor = d;
	
	while (n >= currDivisor) {
		while (currDivisor < n) {
			currDivisor = currDivisor << 1;
		}
		
		if (currDivisor > n) {
			currDivisor = currDivisor >> 1;
		}
	
		n = n - currDivisor;
		currDivisor = d; 
	}
	
	return n;
}

int main() {
	int n, d;

	scanf("%d %d", &n, &d);
	printf("%d\n\n", chineseDivision(n, d));
	
	return 0;	
}
