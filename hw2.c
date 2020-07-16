#include<stdio.h>
#include<math.h>
#pragma warning (disable:4996)
int main() {
	FILE *input, *output;

	input = fopen("hw2.inp", "rt");
	output = fopen("hw2.out", "wt");

	double a, num;
	int m, int_num, result;
	int n[100] = { 0 };
	char t;

	fscanf(input, "%d", &m);
	fscanf(input, "%lf", &a);
	for (int i = 0;; i++) {
		fscanf(input, "%lf%c", &num, &t);
		
		result = (int)num;

		num *= a;
		int_num = (int)(round(num * 100));
		num = (int_num % 100);
		num *= pow(10, -2);
		num *= m;
		int_num = (int)num;
		//printf("%d ", int_num);
		int temp;
		temp = int_num;
		while (1) {
			if (n[int_num] == 0) {
				n[int_num] = result;
				break;
			}
			else
				int_num++;	
			if (temp == int_num) break;
			if (int_num == (int)m) int_num = 0;
		}		
		if (t == '\n') break;
	}
	for (int i = 0; i < (int)m; i++) {
		if (n[i] != 0) {
			fprintf(output, "[%d,%d]\n", i, n[i]);
		}
	}
	fprintf(output, "*");
	

	fclose(input);
	fclose(output);
}