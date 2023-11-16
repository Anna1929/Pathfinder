#include "../inc/pathfinder.h"

int **mx_floyd_warshall(int **matr, int size) {
	int **res = (int **)malloc(size * size * sizeof(int *));
    
	for (int i = 0; i < size; i++) {
		res[i] = (int *)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++) {
			res[i][j] = matr[i][j];
		}
	}

	for(int k = 0 ; k < size; k++) {
		for(int i = 0 ; i < size; i++) {
			for(int j = 0 ; j < size; j++) {
				if(i != j && res[i][k] != INF && res[k][j] != INF) {
					if(res[i][j] == INF){
						res[i][j] = res[i][k] + res[k][j];
					} else {
						res[i][j] = MIN(res[i][j], res[i][k] + res[k][j]);
					}
				}
			}
		}
	}
	mx_zero(res, size);
	return res;
}


