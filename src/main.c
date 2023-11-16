#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {
	mx_error_args(argc);
	mx_error_file_exist(argv[1]);
    
	char *str = mx_file_to_str(argv[1]);
	mx_error_file_empty(str, argv);
   
	char **lines = mx_strsplit(str, '\n');
	int count = 0;
	
	while (lines[count]) {
		count++;
	}
	
	mx_error_line_valid(lines[0]);
	mx_error_lines(lines, count);
	mx_error_duplicate(lines, count);

	int size = mx_atoi(lines[0]);
	char **islands = mx_islands(str, size);
	int **matrix = mx_matrix(lines, islands, size);

	int **paths = mx_floyd_warshall(matrix, size);
	int *route = (int *)malloc((size + 1) * sizeof(int));
	int steps = 1;
    
	mx_solve(islands, matrix, paths, size, route, steps);

	mx_strdel(&str);
	mx_del_strarr(&lines);
	mx_del_strarr(&islands);
	mx_del_arr(&matrix, size);
	mx_del_arr(&paths, size);
	free(route);
	return 0;
}


