#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


char src[] = "input.txt";

// Comprueba que en la primera fila hay un número (asumo que el número solamente puede ser de 1 cifra ya que si colocasemos como carácter vacío un número no habría forma de distinguir cual es el número y cual el carácter) al que le siguen 3 carácteres imprimibles y después un salto de línea
int first_line(char *src)
{
	int fd = open(src, O_RDONLY);
	char c;
	int aux = 0, i = 0;
	

	read(fd, &c, 1);
	if(c >= '0' && c <= '9')
		aux++;
	

	while (i < 3)
	{
		if (c > 31)
			aux++;
		i++;
		read(fd, &c, 1);
	}

	read(fd, &c, 1);
	if(c == 10)
		aux++;
	
	close(fd);

	if(aux == 5)
		return (1);
	
	return (0);
}

// Comprueba que los carácteres de la primera fila son distintos entre si
int diff_char(char *src)
{
	int fd = open(src, O_RDONLY);
	int aux = 0;
	char c1, c2, c3;

	read(fd, &c1, 1);
	read(fd, &c1, 1);
	read(fd, &c2, 1);
	read(fd, &c3, 1);
	
	close(fd);

	if(c1 != c2 && c1 != c3 && c2 != c3)
		return(1);

	return(0);
}


int check_length(char *src)
{
	char characters[2];
	char c;
	int rows, length = 0, eof = 1, aux = 0;
	int fd = open(src, O_RDONLY);

	read(fd, &c, 1);
	rows = c - '0';
	read(fd, &characters[0], 1);
	read(fd, &characters[1], 1);
	read(fd, &c, 1);
	read(fd, &c, 1);
	read(fd, &c, 1);	 //Leemos primer caracter del tablero

	while(eof)
	{
		aux++;

		//Comprobamos que el carácter que se lee es alguno de los carácteres de la cabecera
		if(c != characters[0] && c != characters[1] && c != 10)
		{
			return(0);
		}

		if(c == 10)
		{
			rows--;
			if(length == 0)
			{
				length = aux;
			}
			if(length != aux)
			{
				return (0);
			}
			aux = 0;
		}
		eof = read(fd, &c, 1);
	}
	close(fd);

	//Comprobar que las líneas coinciden con las líneas que se indican al principio
	if(rows != 0)
	{
		return(0);
	}

	//Comprobar que hay al menos un carácter en el tablero
	if(length == 1)
	{
		return(0);
	}

	return (1);
}

int main()
{
	
	printf("%d\n", check_length(src)); 

	return (0);
}