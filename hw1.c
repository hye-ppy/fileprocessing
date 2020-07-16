#include<stdio.h>
#pragma warning (disable:4996)
//void shellSort(int s[], int size, FILE *output);
void mergeSort(int a[], int b[], int a_size, int b_size, FILE *output);
void intervalSort(int a[], int begin, int end, int interval);
void shellSort(int a[], int size, FILE *output);
int main() {
	FILE *input, *output;

	input = fopen("hw1.inp", "rt");
	output = fopen("hw1.out", "wt");

	int a[100], b[100], i;
	char c;
	int a_size, b_size;

	for (i = 0;; i++) {
		fscanf(input, "%d%c", &a[i], &c);
		if (c == '\n') break;
	}
	a_size = i + 1;
	shellSort(a, a_size, output);

	for (i = 0;; i++) {
		fscanf(input, "%d%c", &b[i], &c);
		if (c == '\n') break;
	}
	b_size = i + 1;

	shellSort(b, b_size, output);

	mergeSort(a, b, a_size, b_size, output);
	
	fclose(input);
	fclose(output);
}
void intervalSort(int a[], int begin, int end, int interval) {
	int i, j, item;
	for (i = begin + interval; i <= end ; i += interval) {
		item = a[i];
		for (j = i - interval; j >= begin&&item < a[j]; j -= interval) {
			a[j + interval] = a[j];
		}
		a[j + interval] = item;
	}
}
void shellSort(int a[], int size, FILE *output) {
	int i, interval;
	interval = size / 2;
	while (interval >= 1) {
		for (i = 0; i < interval; i++) {
			intervalSort(a, i, size - 1, interval);
		}
		for (int t = 0; t < size; t++) fprintf(output, "%d ", a[t]);
		fprintf(output, "\n");
		interval = interval / 2;
	}
}
/*void shellSort(int s[], int size, FILE *output) {
	int interval, temp, k;
	interval = size / 2;
	while (interval >= 1) {
		for (int i = 0; i < interval; i++) {
			for (int j = interval+i; j < size; j += interval) {				
				temp = s[j];
				printf("%d  ->", s[j]);
				for (k = j - interval; j >= i && temp < s[k]; k -= interval) {
					s[k + interval] = s[k];
					printf("%d  ", s[k]);
				}
				s[k + interval] = temp;
				if (s[j - interval] > s[j]) {
					printf("%d %d %d %d\n", s[j - interval], s[j],j,interval);
					temp = s[j - interval];
					s[j - interval] = s[j];
					s[j] = temp;
				}
			}
		}
		for (int i = 0; i < size; i++) {
			fprintf(output, "%d ", s[i]);
		}
		fprintf(output, "\n");
		interval /= 2;
	}
}*/
void mergeSort(int a[], int b[], int a_size, int b_size, FILE *output) {
	int s[200];
	int i = 0, j = 0, k = 0;
	while (i < a_size && j < b_size) {
		if (a[i] <= b[j]) {
			s[k] = a[i];
			i++;
			k++;
		}
		else {
			s[k] = b[j];
			j++;
			k++;
		}
	}
	if (j == b_size) {
		for (int x = i; x < a_size; x++, k++) {
			s[k] = a[x];
		}
	}
	else if (i == a_size) {
		for (int x = j; x < b_size; x++, k++) {
			s[k] = b[x];
		}
	}
	for (int i = 0; i < a_size + b_size; i++) {
		fprintf(output, "%d ", s[i]);
	}
	fprintf(output, "\n*");
}