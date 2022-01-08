#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char src[] = "input.txt";

//REVISAR TODAS LAS LLAMADAS A LAS FUNCIONES CON EL PARÁMETRO SRC 


// Calcula el ancho del tablero
int get_cols(char src[])
{
	int i = 0;
	char c;
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
int number_obs(char src[])
{
	char c;
	int eof = 1;
	int i = 0;
	int fd = open(src, O_RDONLY);
	char obs;

	// Leer los primeros 6 caracteres para llegar al primero de la primera fila (No he encontrado otra manera mejor ¿¿¿¿read(fd, NULL, 5)??? <- Esto no funciona)
	{
		read(fd, &c, 1);
		read(fd, &c, 1);
		read(fd, &obs, 1);
		read(fd, &c, 1);
		read(fd, &c, 1);
		read(fd, &c, 1);
	}

	while (eof)
	{
		eof = read(fd, &c, 1);
		if (c == obs)
		{
			i++;
		}
	}

	close(fd);
	return(i);
}

// Devuelve un array de la forma array[n][2] con las coordenadas x e y de cada obstaculos
// QUITAR VARIBALES INUTILES!!!!!
int **read_map(char src[])
{
	int i = 0;
	int j = 0;
	int k = 0;
	int aux;
	int filas;
	int cols = get_cols(src);
	int eof = 1;
	char vacio;
	char obs;
	char lleno;
	char c;

	int fd = open(src, O_RDONLY);
	read(fd, &c, 1);
	filas = c - '0';
	read(fd, &vacio, 1);
	read(fd, &obs, 1);
	read(fd, &lleno, 1);
	read(fd, &c, 1);

	//Guardar espacio para el array de dos dimensiones que constiene las coordenadas x e y de los obstaculos
	int **obs_coord;
	obs_coord = (int **)malloc(number_obs(src) * sizeof(int *));
	for(aux = 0; aux < number_obs(src); aux++)
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
	
	//Leer las coordenadas

	/* for(aux = 0; aux < number_obs(src); aux++)
	{
		printf("obs_coord[%d][0]: %d\n", aux, obs_coord[aux][0]);
		printf("obs_coord[%d][1]: %d\n\n", aux, obs_coord[aux][1]);
		
	} */
	
	close(fd);

	return(obs_coord);
}


//Comprueba si el cuadrado que se genera en el punto con coordenadas coord y de tamaño size se genera por completo dentro del tablero (return 1) o si por el contrario parte de este sale por fuera (return 0)
int check_borders(int *coord, int size)
{
	int fd = open(src, O_RDONLY);
	int cols = get_cols(src);
	int rows;
	read(fd, &rows, 1);
	rows = rows - '0';
	close(fd);

	if((coord[0] + size) <= cols && (coord[1] + size) <= rows)
	{
		return(1);
	}

	return(0);
}


// Comprueba si el cuadrado de lado size interfiere con algún obstáculo. El parámetro coord son las coordenadas que se van a utilizar para colocar la esquina superior izquierda del cuadrado. Si el cuadrado cabe devuelve 1, de lo contrario 0.
int check_square(int *coord, int size, int **obs_coord, int nobs)
{
	int i = 0;

	for(i = 0; i < nobs; i++)
	{
		if(obs_coord[i][0] >= coord[0] && obs_coord[i][1] >= coord[1] && obs_coord[i][0] < coord[0] + size && obs_coord[i][1] < coord[1] + size)
		{
			return (0);
		}
	}
	if(!check_borders(coord, size))
	{
		return(0);
	}

	return (1);
}


int main()
{
	// Cuidado con el archivo
	int **obs_coord = read_map(src);
	int nobs = number_obs(src);
	int coord[2];
	int size = 1;
	int max_size = 1;
	int res_coord[2];
	int i;
	int j;
	int rows;
	int fd = open(src, O_RDONLY);
	read(fd, &rows, 1);
	rows = rows - '0';
	close(fd);

	//printf("%d\n", check_square(coord, 5, obs_coord, nobs));

	for(j = 0; j < rows; j++)
	{
		for(i = 0; i < get_cols(src); i++)
		{
			coord[0] = i;
			coord[1] = j;
			while(check_square(coord, size, obs_coord, nobs))
			{
				size++;
			}
			
		}
	}
	

	return 0;
}