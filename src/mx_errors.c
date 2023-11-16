#include "../inc/pathfinder.h"

void mx_error_args(int argc) {
	if (argc != 2) {
		mx_printerr("usage: ./pathfinder [filename]\n");
		exit(0);
	}
}

void mx_error_file_exist(char *filename) {
	if (open(filename, O_RDONLY) < 0) {
		mx_printerr("error: file ");
		mx_printerr(filename);
		mx_printerr(" does not exist\n");
		exit(0);
	}
}

void mx_error_file_empty(char *filename, char *argv[]) {
	if (mx_strlen(filename) == 0) {
		mx_printerr("error: file ");
		mx_printerr(argv[1]);
		mx_printerr(" is empty\n");
		exit(0);
	}
}

void mx_error_line_valid(char *first_line) {
	for (int i = 0; first_line[i]; i++) {
		if (!mx_isdigit(first_line[i])) {
			mx_printerr("error: line 1 is not valid\n");
			exit(0);
		}
	}
}


static int is_valid_line(char *line) {
	int j = 0;

	while (mx_isalpha(line[j++])) {}
	if (j == 1 || line[j - 1] != '-') return 0;

	while (mx_isalpha(line[j++])) {}
	if (line[j - 1] != ',') return 0;

	while (mx_isdigit(line[j++])) {}

	return (line[j - 1] == '\0');
}

void mx_error_lines(char **lines, int num) {
	for (int i = 1; i < num; i++) {
		if (!is_valid_line(lines[i])) {
			mx_printerr("error: line ");
			mx_printerr(mx_itoa(i + 1));
			mx_printerr(" is not valid\n");
			exit(0);
		}
	}
}

void mx_error_island_num(char **islands, int numIslands, int size) {
	int count = 0;
	
	for (int i = 0; i < numIslands; i++) {
		if (islands[i][0] != ' ') {
			count++;
		}
	}
	if (count != size) {
		mx_del_strarr(&islands);
		mx_printerr("error: invalid number of islands\n");
		exit(0);
	}  
}

void mx_error_duplicate(char **lines, int num) {
	char **str = (char **)malloc((num + 1) * sizeof(char *));
	
	for (int i = 0; i < num; i++) {
		str[i] = mx_strndup(lines[i], mx_get_char_index(lines[i], ','));
	}
	str[num] = NULL;

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (str[j][0] == '\0' || j == i) {
				continue;
			}
			if (mx_strcmp(str[i], str[j]) == 0) {
				mx_printerr("error: duplicate bridges\n");
				exit(0);
			}    
		}
	}
	mx_del_strarr(&str);
}


