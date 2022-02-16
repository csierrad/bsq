#include "header.h"


// Comprueba si el cuadrado que se genera en el punto con coordenadas coord y de tamaño size se genera por completo dentro del tablero (return 1) o si por el contrario parte de este sale por fuera (return 0)
int check_borders(int coord[2], int size, map_t m)
{
	if ((coord[0] + size) <= m.cols && (coord[1] + size) <= m.rows)
	{
		return (1);
	}

	return (0);
}


// Comprueba si el cuadrado de lado size interfiere con algún obstáculo. El parámetro coord son las coordenadas que se van a utilizar para colocar la esquina superior izquierda del cuadrado. Si el cuadrado cabe devuelve 1, de lo contrario 0.
int valid_square(int coord[2], int size, map_t m)
{
	int i = 0;

	for (i = 0; i < m.nobs; i++)
	{
		if (m.obs_coord[i][0] >= coord[0] && m.obs_coord[i][1] >= coord[1] && m.obs_coord[i][0] < coord[0] + size && m.obs_coord[i][1] < coord[1] + size)
		{
			return (0);
		}
	}
	if (!check_borders(coord, size, m))
		return (0);

	return (1);
}