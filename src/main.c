#include "header.h"


int main(int argc, char *argv[])
{
	map_t m;
	int i, j, aux = 1, size = 1, max_size = 0;
	int coord[2];
	int res_coord[2] = {-1, -1};

	while (aux < argc)
	{
		if (!check_map(argv[aux]))
		{
			write(1, "map error\n", 10);
		}
		else
		{
			initialize_map(&m, argv[aux]);

			for (j = 0; j < m.rows; j++)
			{
				for (i = 0; i < m.cols; i++)
				{
					size = max_size;
					coord[0] = i;
					coord[1] = j;
					while (valid_square(coord, size, m))
					{
						size++;
					}

					if ((size - 1) > max_size)
					{
						max_size = size - 1;
						res_coord[0] = coord[0];
						res_coord[1] = coord[1];
					}
				}
			}

			print_map(max_size, res_coord, m, argv[aux]);
		}

		// Esta útlima condición hace que no se escriba el salto de línea después del último tablero
		if(aux < argc - 1)
			write(1, "\n", 1);
		aux++;
	}

	return (0);
}