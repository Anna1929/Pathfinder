#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"

#define INF 40000
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void mx_error_args(int argc);
void mx_error_file_exist(char *filename);
void mx_error_file_empty(char *filename, char *argv[]);
void mx_error_line_valid(char *first_line);
void mx_error_lines(char **lines, int num);
void mx_error_island_num(char **islands, int numIslands, int size);
void mx_error_duplicate(char **lines, int num);

char **mx_islands(char *string, int size);
int **mx_matrix(char **lines, char **graph, int size);

int **mx_floyd_warshall(int **matr, int size);
void mx_zero(int **arr, int size);
void mx_del_arr(int ***arr, int row);
void mx_solve(char **isl, int **matr, int **paths, int size, int *route, int s);

#endif
