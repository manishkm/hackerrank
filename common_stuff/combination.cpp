//finding and printing cobination of nCr
#include <iostream>

using namespace std;

void print_arr(int arr[], int size) {
	static int count = 0;
	printf("%d-\t", count++);
	for (int i = 0; i < size-1; i++) {
		printf("%d-", arr[i]);
	}
	printf("%d\n", arr[size-1]);
}

void combination(int s, int n, int r, int comb_arr[], int p, int input[]) {
	for (int i = s; i <= (n - (r-p) ); i++) {
		comb_arr[p] = input[i];
		if (p == (r - 1)) {
			print_arr(comb_arr, r);
		}
		else {
			combination(i+1, n, r, comb_arr, p + 1,input);
		}
	}
}

int main() {
	int n = 5;
	int r = 3;
	int comb_arr[5];
	int input[] = { 1,2,3,4,5 };
	combination(0, n, 2, comb_arr, 0, input);
	return 0;
}