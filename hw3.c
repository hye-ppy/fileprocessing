#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#pragma warning (disable:4996)
int count;
int node_count = 1;
struct TrieNode {
	struct TrieNode *children[10];
	int address;
	bool isEndOfWord;
};
struct TrieNode *getNode(void) {
	struct TrieNode *pNode = NULL;


	pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

	if (pNode) {
		pNode->isEndOfWord = false;
		for (int i = 0; i < 10; i++) {
			pNode->children[i] = NULL;
		}
	}
	return pNode;
}
void insert(struct TrieNode *root, const int *key) {
	int level;
	//int length = sizeof(key);
	int index;
	struct TrieNode *pCrawl = root;
	for (level = 0; level < 4; level++) {
		index = key[level];
		if (!pCrawl->children[index]) {
			pCrawl->children[index] = getNode();
			if (level != 3) {
				node_count++;
			}
		}
		pCrawl = pCrawl->children[index];
	}
	pCrawl->address = key[4];
	pCrawl->isEndOfWord = true;
}
void search(struct TrieNode *root, const int *key, FILE *output) {
	int level;
	//int length = sizeof(key);
	int index;
	struct TrieNode *pCrawl = root;
	for (level = 0; level < 4; level++) {
		index = key[level];
		
		if (!pCrawl->children[index]) {
			break;
			//return false;
		}
		pCrawl = pCrawl->children[index];
	}
	if (pCrawl != NULL && pCrawl->isEndOfWord) {
		pCrawl = root;
		for (level = 0; level < 4; level++) {
			index = key[level];
			fprintf(output,"%d", index);
			pCrawl = pCrawl->children[index];
		}
		if (pCrawl->address / 1000 != 0) {
			fprintf(output, " %d %d", count, pCrawl->address);
			fprintf(output, "\n");
		}
		else if (pCrawl->address / 100 != 0) {
			fprintf(output, " %d 0%d", count, pCrawl->address);
			fprintf(output, "\n");
		}
		else if (pCrawl->address / 10 != 0) {
			fprintf(output, " %d 00%d", count, pCrawl->address);
			fprintf(output, "\n");
		}
		else {
			fprintf(output, " %d 000%d", count, pCrawl->address);
			fprintf(output, "\n");
		}
	}
	else {
		fprintf(output, "no\n");
	}
	//return (pCrawl != NULL && pCrawl->isEndOfWord);

}

int main() {
	FILE *input, *output;

	input = fopen("hw4.inp", "rt");
	output = fopen("hw4.out", "wt");

	int irecord[100000][6];
	int record[100000][5];
	char a, b, c, d;
	int i;
	int temp;
	int index;
	int ex;

	int copy[4];
	int check = 0;
	int print[3];
	bool noo = true;

	for (i = 0; ; i++) {//입력받기
		fscanf(input, "%c%1d%1d%1d%1d%c%d%c%c", &a, &irecord[i][0], &irecord[i][1], &irecord[i][2], &irecord[i][3], &b, &irecord[i][4], &c, &d);
		if (d == '\n') break;
	}
	for (int x = i; x > 0; x--) {//레코드 정렬
		for (int y = 0; y < x; y++) {
			for (int z = 0; z < 4; z++) {
				if (irecord[y][z] > irecord[y + 1][z]) {
					for (int p = 0; p < 5; p++) {
						temp = irecord[y][p];
						irecord[y][p] = irecord[y + 1][p];
						irecord[y + 1][p] = temp;
					}
					break;
				}
				else if (irecord[y][z] < irecord[y + 1][z]) {
					break;
				}
			}
		}
	}
	count = 0;
	for (int x = 0; x <= i; x++) {
		if (x == 0) {
			for (int y = 0; y < 3; y++) {
				print[y] = irecord[x][y];
			}
		}
		for (int y = 0; y < 3; y++) {
			if (print[y] == irecord[x][y]) {
				if (y == 2) {
					count++;
					irecord[x][5] = count;
				}
			}
			else {
				for (int z = 0; z < 3; z++) {
					print[z] = irecord[x][z];
				}
				count = 1;
				irecord[x][5] = count;
				break;
			}
		}
	}

	struct TrieNode *root = getNode();

	for (int x = 0; x <= i; x++) {//트라이 만들기
		insert(root, irecord[x]);
	}
	fprintf(output,"%d\n", node_count);

	while (1) {
		check = 0;//와일드 카드
		for (int x = 0; x < 5; x++) {//입력
			if (x != 4) {
				fscanf(input,"%c", &b);
				if (b == '*') {
					copy[x] = 10;
					x = 3;
					check = 1;
				}
				else copy[x] = b - 48;
			}
			else {
				fscanf(input, "%c", &a);
			}
		}
		/*for (int o = 0; o < 4; o++) {
			printf("%d ", copy[o]);
		}
		printf("\n");*/
		if (check == 1) {//와일드 카드 있을때	
			for (int p = 0; p <= i;p++) {//옮기기
				for (int q = 0; q < 5; q++) {
					record[p][q] = irecord[p][q];
				}
			}
			for (int p = 0; p < 4; p++) {
				if (copy[p] != 10) {//출력할 수 있는 배열 만들기
					index = 0;
					if (p == 0) {
						for (int q = 0; q <= i; q++) {
							if (copy[p] == record[q][p]) {
								for (int r = 0; r < 5; r++) {
									record[index][r] = record[q][r];
								}
								index++;
							}
						}
						ex = index;
					}
					else {//출력할 수 있는 배열 만들기
						for (int q = 0; q < ex; q++) {
							if (copy[p] == record[q][p]) {
								for (int r = 0; r < 5; r++) {
									record[index][r] = record[q][r];
								}
								index++;
							}
						}
					}
					/*for (int g = 0; g < index; g++) {//출력
						for (int q = 0; q < 5; q++) {
							printf("%d ", record[g][q]);
						}
					printf("\n");
					}
					printf("\n");*/
				}
				else if (copy[p] == 10) {//출력
					if (p == 0) {
						count = 0;
						for (int x = 0; x <= i; x++) {
							if (x == 0) {
								for (int y = 0; y < 3; y++) {
									print[y] = record[x][y];
								}
							}
							for (int y = 0; y < 3; y++) {
								if (print[y] == record[x][y]) {
									if (y == 2) {
										count++;
									}
								}
								else {
									for (int z = 0; z < 3; z++) {
										print[z] = record[x][z];
									}
									count = 1;
									break;
								}
							}
							for (int y = 0; y < 5; y++) {
								if (record[x][y] / 1000 != 0) {
									if (y != 4) {
										fprintf(output, "%d", record[x][y]);
									}
									else {
										fprintf(output, " %d %d ", count, record[x][y]);
									}

								}
								else if (record[x][y] / 100 != 0) {
									if (y != 4) {
										fprintf(output, "%d", record[x][y]);
									}
									else {
										fprintf(output, " %d 0%d ", count, record[x][y]);
									}

								}
								else if (record[x][y] / 10 != 0) {
									if (y != 4) {
										fprintf(output, "%d", record[x][y]);
									}
									else {
										fprintf(output, " %d 00%d ", count, record[x][y]);
									}

								}
								else {
									if (y != 4) {
										fprintf(output, "%d", record[x][y]);
									}
									else {
										fprintf(output, " %d 000%d ", count, record[x][y]);
									}
								}
							}
							
						}
						fprintf(output, "\n");
					}
					else {
						count = 0;
						for (int x = 0; x < index; x++) {
							if (x == 0) {
								for (int y = 0; y < 3; y++) {
									print[y] = record[x][y];
								}
							}
							for (int y = 0; y < 3; y++) {
								if (print[y] == record[x][y]) {
									if (y == 2) {
										count++;
									}
								}
								else {
									for (int z = 0; z < 3; z++) {
										print[z] = record[x][z];
									}
									count = 1;
									break;
								}
							}
							for (int y = 0; y < 5; y++) {
								if (record[x][y] / 1000 != 0) {
									if (y != 4) {
										fprintf(output, "%d", record[x][y]);
									}
									else {
										fprintf(output, " %d %d ", count, record[x][y]);
									}

								}
								else if (record[x][y] / 100 != 0) {
									if (y != 4) {
										fprintf(output, "%d", record[x][y]);
									}
									else {
										fprintf(output, " %d 0%d ", count, record[x][y]);
									}

								}
								else if (record[x][y] / 10 != 0) {
									if (y != 4) {
										fprintf(output, "%d", record[x][y]);
									}
									else {
										fprintf(output, " %d 00%d ", count, record[x][y]);
									}

								}
								else {
									if (y != 4) {
										fprintf(output, "%d", record[x][y]);
									}
									else {
										fprintf(output, " %d 000%d ", count, record[x][y]);
									}
								}
							}
						}
						fprintf(output, "\n");
					}
					break;//와일드카드 끝내기
				}
				if (index == 0) {//찾는게 없단 소리
					fprintf(output, "no\n");
					break;
				}
				else continue;
			}
		}
		else {//없을때
			for (int p = 0; p <= i; p++) {
				for (int q = 0; q < 4; q++) {
					if (copy[q] == irecord[p][q]) {
						if (q == 3) {
							count = irecord[p][5];
						}
					}
				}
			}
			search(root, copy, output);
		}
		
		if (a == '\n') break;
	}
	fprintf(output, "*");

	fclose(input);
	fclose(output);
}
