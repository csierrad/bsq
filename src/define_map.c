#include "functions.h"


// Calcula el ancho del tablero
int get_cols(char *src)
{
	char c;
	int i = 0, eof = 1;
	int fd = open(src, O_RDONLY);

	// Leer los primeros 6 caracteres para llegar al primero de la primera fila (No he encontrado otra manera mejor ¿¿¿¿read(fd, NULL, 5)??? <- Esto no funciona)
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);

	while (c != 10 && eof)
	{
		i++;
		eof = read(fd, &c, 1);
	}

	close(fd);

	return (i);
}


// Calcula el número de obstaculos que hay en el mapa
int number_obs(char *src)
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
int **read_map(char *src)
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


// Llama a las funciones definidas anteriormente y inicializa un struct de tipo map_t
void initialize_map(map_t *m, char *src)
{
	char c;
	int fd = open(src, O_RDONLY);
	// No se por qué al guardar la variable de tipo char en rows que es de tipo entero no se hace correctamente y da un número que no corresponde con la posición del carácter en la tabla ascii.
	read(fd, &c, 1);
	read(fd, &m->empty, 1);
	read(fd, &m->obs, 1);
	read(fd, &m->full, 1);
	close(fd);

	m->rows = c - '0';
	m->cols = get_cols(src);
	m->nobs = number_obs(src);
	m->obs_coord = read_map(src);
}


//Imprime el mapa resultado
void print_map(int max_size, int *res_coord, map_t m, char *src)
{
	int i = -1, j = 0, k = 0, aux = 0, eof = 1;
	char c;
	int fd = open(src, O_RDONLY);

	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);

	while (eof)
	{
		eof = read(fd, &c, 1);
		i++;

		if (c == 10)
		{
			i = -1;
			j++;
		}
		if (eof)
		{
			if (res_coord[0] == i && (res_coord[1] + aux) == j && aux < max_size)
			{
				k = 0;
				while (k < max_size - 1 && aux < max_size)
				{
					write(1, &m.full, 1);
					eof = read(fd, &c, 1);
					k++;
					i++;
				}
				write(1, &m.full, 1);
				aux++;
			}
			else
			{
				write(1, &c, 1);
			}
		}
	}

	close(fd);

	return;
}