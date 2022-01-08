#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char src[] = "input.txt";

typedef struct Board
{
	int rows;
	int cols;

	char full;
	char empty;

	char obs;
	int nobs;
	int **obs_coord;
} board;

// Calcula el ancho del tablero
int get_cols()
{
	char c;
	int i = 0;
	int fd = open(src, O_RDONLY);

	// Leer los primeros 6 caracteres para llegar al primero de la primera fila (No he encontrado otra manera mejor ¿¿¿¿read(fd, NULL, 5)??? <- Esto no funciona)
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);

	while (c != 10)
	{
		i++;
		read(fd, &c, 1);
	}

	close(fd);

	return (i);
}

// Calcula el número de obstaculos que hay en el mapa
int number_obs()
{
	int i = 0, eof = 1;
	char c, obs;
	int fd = open(src, O_RDONLY);

	// Leer los primeros 6 caracteres para llegar al primero de la primera fila (No he encontrado otra manera mejor ¿¿¿¿read(fd, NULL, 5)??? <- Esto no funciona)
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &obs, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);

	while (eof)
	{
		if (c == obs)
		{
			i++;
		}
		eof = read(fd, &c, 1);
	}

	close(fd);

	return (i);
}

// Devuelve un array de la forma array[n][2] con las coordenadas x e y de cada obstaculos
int **read_map()
{
	int aux, i = 0, j = 0, k = 0, eof = 1;
	char obs, c;

	int fd = open(src, O_RDONLY);

	// Leemos los primeros 5 carácteres del input para llegar al tablero
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &obs, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);

	// Guardar espacio para el array de dos dimensiones que constiene las coordenadas x e y de los obstaculos
	int **obs_coord;
	obs_coord = (int **)malloc(number_obs(src) * sizeof(int *));
	for (aux = 0; aux < number_obs(src); aux++)
		obs_coord[aux] = (int *)malloc(2 * sizeof(int));

	while (eof != 0)
	{
		i = 0;
		eof = read(fd, &c, 1);

		while (c != 10 && eof != 0)
		{
			if (c == obs)
			{
				obs_coord[k][0] = i;
				obs_coord[k][1] = j;
				k++;
			}
			i++;
			eof = read(fd, &c, 1);
		}
		j++;
	}

	close(fd);

	return (obs_coord);
}

// Comprueba si el cuadrado que se genera en el punto con coordenadas coord y de tamaño size se genera por completo dentro del tablero (return 1) o si por el contrario parte de este sale por fuera (return 0)
int check_borders(int coord[2], int size, board b)
{
	if ((coord[0] + size) <= b.cols && (coord[1] + size) <= b.rows)
	{
		return (1);
	}

	return (0);
}

// Comprueba si el cuadrado de lado size interfiere con algún obstáculo. El parámetro coord son las coordenadas que se van a utilizar para colocar la esquina superior izquierda del cuadrado. Si el cuadrado cabe devuelve 1, de lo contrario 0.
int check_square(int coord[2], int size, board b)
{
	int i = 0;

	for (i = 0; i < b.nobs; i++)
	{
		if (b.obs_coord[i][0] >= coord[0] && b.obs_coord[i][1] >= coord[1] && b.obs_coord[i][0] < coord[0] + size && b.obs_coord[i][1] < coord[1] + size)
		{
			return (0);
		}	
	}
	if (!check_borders(coord, size, b))
		return (0);

	return (1);
}

void initialize_board(board *b)
{
	char c;
	int fd = open(src, O_RDONLY);
	// No se por qué al guardar la variable de tipo char en rows que es de tipo entero no se hace correctamente y da un número que no corresponde con la posición del carácter en la tabla ascii.
	read(fd, &c, 1);
	read(fd, &b->empty, 1);
	read(fd, &b->obs, 1);
	read(fd, &b->full, 1);
	close(fd);

	b->rows = c - '0';
	b->cols = get_cols();
	b->nobs = number_obs();
	b->obs_coord = read_map();
}

int main()
{
	board b;
	int i, j, size = 1, max_size = 0;
	int coord[2];
	int res_coord[2] = {-1, -1};

	initialize_board(&b);

	for (j = 0; j < b.rows; j++)
	{
		for (i = 0; i < b.cols; i++)
		{
			size = max_size;
			coord[0] = i;
			coord[1] = j;
			while (check_square(coord, size, b))
			{
				size++;
			}

			if ((size - 1) > max_size)
			{
				max_size = size - 1;
				res_coord[0] = coord[0];
				res_coord[1] = coord[1];
			}
			printf("[%d, %d] -> max_size: %d\n", i, j, max_size);
		}
	}
	printf("res: [%d, %d] -> max_size: %d\n", res_coord[0], res_coord[1], max_size);

	return 0;
}