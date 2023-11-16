#include "../inc/pathfinder.h"

static void mx_print_edge(void) {
	for (int i = 0; i < 40; i++) {
		mx_printchar('=');
	}
	mx_printchar('\n');
}

static void mx_path(char **islands, int *route) {
	mx_printstr(islands[route[1]]);
	mx_printstr(" -> ");
	mx_printstr(islands[route[0]]);
	mx_printstr("\n");
}

static void mx_route(int count, int *route, char **islands) {
	if (count > 2) {
		for (int i = 1; i < count + 1; i++) {
			mx_printstr(islands[route[i]]);
			if (i < count) {
				mx_printstr(" -> ");
			}

		}
	} else {
		mx_printstr(islands[route[1]]);
	        mx_printstr(" -> ");
		mx_printstr(islands[route[0]]);
	}
	mx_printchar('\n');
}

static void mx_distance(int count, int *route, int **matr, int **paths) {
	if (count > 2) {
		for (int i = 1; i < count; i++) {
			int temp = matr[route[i]][route[i + 1]];
			mx_printint(temp);

			if (i < count - 1) {
				mx_printstr(" + ");
			}
		}
		mx_printstr(" = ");
		mx_printint(paths[route[0]][route[1]]);
	} else {
		mx_printint(paths[route[0]][route[1]]);
	}
	mx_printchar('\n');
}

static void process_path(char **isl, int **matr, int **paths, int *route, int s) {
	mx_print_edge();
	mx_printstr("Path: "); 
	mx_path(isl, route);
	mx_printstr("Route: ");
	mx_route(s, route, isl);
	mx_printstr("Distance: ");
	mx_distance(s, route, matr, paths);
	mx_print_edge();
}

static void print(char **isl, int **matr, int **paths, int size, int *route, int s) {
	int start = route[0];
	int end = route[s];

	for (int i = 0; i < size; i++) {
		if((matr[end][i] == paths[end][start] - paths[i][start]) && i != route[s]) {
			s++;
			route[s] = i;
			print(isl, matr, paths, size, route, s);
			s--;
		}
	}
	if (route[s] != start) return;
	process_path(isl, matr, paths, route, s);
}

void mx_solve(char **isl, int **matr, int **paths, int size, int *route, int s) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			route[1] = i;
			route[0] = j;
			print(isl, matr, paths, size, route, s);
		}
	}
}


