#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stdafx.h"
#include <time.h>
#include <stdlib.h>

int n; /* Then number of nodes */
int dist[16][16]; /* dist[i][j] is the length of the edge between i and j if
				  it exists, or 0 if it does not */

void printDist() {
	int i, j;
	printf(" ");
	for (i = 0; i < n; ++i)
		printf("%4c", 'A' + i);
	printf("\n");
	for (i = 0; i < n; ++i) {
		printf("%4c", 'A' + i);
		for (j = 0; j < n; ++j)
			printf("%4d", dist[i][j]);
		printf("\n");
	}
	printf("\n");
}

/*
floyd_warshall()

after calling this function dist[i][j] will the the minimum distance
between i and j if it exists (i.e. if there's a path between i and j)
or 0, otherwise
*/
void floyd_warshall() {
	int i, j, k;
	for (k = 0; k < n; ++k) {
		printDist();
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				/* If i and j are different nodes and if
				the paths between i and k and between
				k and j exist, do */
				if ((dist[i][k] * dist[k][j] != 0) && (i != j))
					/* See if you can't get a shorter path
					between i and j by interspacing
					k somewhere along the current
					path */
					if ((dist[i][k] + dist[k][j] < dist[i][j]) ||
						(dist[i][j] == 0))
						dist[i][j] = dist[i][k] + dist[k][j];
	}
	printDist();
}
void vvodM(void) {
	int t;
	printf("vvedite matr: \n");
	printf("n=");
	scanf("%d", &n);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++) {
			//t=rand()%10;
			if (i != j)
				dist[i][j] = dist[j][i] = rand() % 10; //(t || i!=j) ? t : infinity;
		}
}

int main(int argc, char *argv[]) {
	vvodM();

	floyd_warshall();

	return 0;
}
