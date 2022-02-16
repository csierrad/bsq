#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct Map
{
	int rows;
	int cols;

	char full;
	char empty;

	char obs;
	int nobs;
	int **obs_coord;
} map_t;

//valid_map.c
int first_line(char *src);
int diff_char(char *src);
int check_length(char *src);
int check_map(char *src);

//define_map.c
int get_cols(char *src);
int number_obs(char *src);
int **read_map(char *src);
void initialize_map(map_t *b, char *src);
void print_map(int max_size, int *res_coord, map_t b, char *src);

//check_square.c
int check_borders(int coord[2], int size, map_t b);
int valid_square(int coord[2], int size, map_t b);

#endif