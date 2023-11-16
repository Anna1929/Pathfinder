#include "../inc/pathfinder.h"

static int mx_index(char **arr, char *str) {
	for (int i = 0; arr[i]; i++) {
		if (mx_strcmp(arr[i], str) == 0) {
			return i;
		}
	}
	return -1;
}

char **mx_islands(char *string, int size) {
	char *str = mx_strdup(string);
	int count = 0;
	char **islands = (char **)malloc((size + 1) * sizeof(char *));

	for (int i = 0; i < mx_strlen(str); i++) {
		if (str[i] == '-' || str[i] == ',' || str[i] == '\n') {
			str[i] = ' ';
		}
		if (mx_isdigit(str[i])) {
			str[i] = ' ';
		}
	}

	char *without_spaces = mx_del_extra_spaces(str);
	char **lines = mx_strsplit(without_spaces, ' ');
	while (lines[count]) {
		count++;
	}
	for (int i = 0, j = 1; i < count; i += 2, j++) {
		if(mx_strcmp(lines[i], lines[i + 1]) == 0) {
			mx_printerr("error: line ");
			mx_printerr(mx_itoa(j + 1));
			mx_printerr(" is not valid\n");
			exit(0);
		}
	}
	int k = 0;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			if (lines[j][0] == ' ' || j == i) {
				continue;
			}
			if (mx_strcmp(lines[i], lines[j]) == 0) {
				lines[j][0] = ' ';
			}
		}
		if(mx_isalpha(lines[i][0])) {
			islands[k] = mx_strdup(lines[i]);
			k++;
		}
	}
	islands[size] = NULL;
	mx_error_island_num(lines, count, size);

	mx_strdel(&str);
	mx_strdel(&without_spaces);
	mx_del_strarr(&lines);
	
	return islands;
}


static char **mx_path_print(char *line) {
	char **arr = (char **)malloc(4 * sizeof(char *));
	
	for (int i = 0; i <= 3; i++) {
		arr[i] = NULL;
	}
	
	arr[0] = mx_strndup(line, mx_get_char_index(line, '-'));
	line += mx_get_char_index(line, '-') + 1;
	arr[1] = mx_strndup(line, mx_get_char_index(line, ','));
	line += mx_get_char_index(line, ',') + 1;
	arr[2] = mx_strndup(line, mx_get_char_index(line, '\n'));

	return arr;
}

int **mx_matrix(char **lines, char **graph, int size) {
	int **matr = (int **) malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++) {
		matr[i] = (int *)malloc(size * sizeof(int));
	}
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			matr[i][j] = INF;
		}
	}
	for (int i = 1; lines[i]; i++) {
		char **temp = mx_path_print(lines[i]);

		if (mx_atoi(temp[2]) >= __INT_MAX__) {
			mx_printerr("error: sum of bridges lengths is too big\n");
			exit(0);
		}
		
		int a = mx_index(graph, temp[0]);
		int b = mx_index(graph, temp[1]);
		
		matr[a][b] = mx_atoi(temp[2]);
		matr[b][a] = mx_atoi(temp[2]);
		mx_del_strarr(&temp);
	}
	return matr;
}


