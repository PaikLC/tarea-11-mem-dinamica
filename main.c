
#define SIG_INTER_ABAJO 168

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <locale.h>

/* ---- Funciones para crear la matriz ----*/
void liberarMatriz2D(void **matriz, int filas)
{
    //Liberar la memoria asignada a cada una de las filas
    for(int i = 0; i < filas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

void **crearMatriz2D(int filas, int col, size_t tamElem)
{
    void **p = NULL;
    
    // Asignamos la matriz de punteros (filas)
    if((p = (void **)malloc(filas * sizeof(void *))) != NULL) 
    {
        // Asignamos las columnas
        for(int i = 0; i < filas; i++)
        {
            p[i] = malloc(col * tamElem);
            if(p[i] == NULL)
            {
                // Liberar las filas que se han creado
                liberarMatriz2D(p, i);
                return NULL;
            }
            memset(p[i], 0, col * tamElem);
        }
    }
    
    return p;
}

/* ---- Funciones para la Entrada/Salida de datos ---- */
void datoEntrada( char *str, int* ptr )
{
	fflush(stdin);
	printf("\n%s", str);
	while ((scanf_s("%d", ptr) == 0) || (*ptr < 0))
	{
		printf("\t\tColoque un numero valido!");
		printf("%s", str);
		fflush(stdin);
	}
}

/* ---- Funcion para corroborar los argumentos ---- */
int datosVerificar(char *param)	// -f || /f es para las filas, -c || /c es para las columnas
{
	if (param[0] == '-' || param[0] == '/')
	{
		switch(param[1])
		{
			case 'f':
				return 0;
			case 'c':
				return 1;
			case 'v':
				return 2;
		}
	}
	return -1;
}

int main( int argc, char* argv[] )
{
	setlocale(0, "es-Mx");
    int **datos = NULL, filas = 0, columnas = 0, valorL = 0; // La matriz de datos
    
	if( argc != 1)
	{
		int i = 1, valor = 0;
		do
		{
			valor = datosVerificar(argv[i]);
			i++;
			switch(valor)
			{
				case 0:
					printf("Filas: %s\n", argv[i]);
					filas = atoi(argv[i]);
					break;
				case 1:
					printf("Columnas: %s\n", argv[i]);
					columnas = atoi(argv[i]);
					break;
				case 2:
				    valorL = atoi(argv[i]);
					printf("Valor de la matriz: %d\n", valor);
					break;
				
				default:
					printf("Error: No se reconoce \"%s\"", argv[i - 1]);
					printf("\n\t -f: Filas\n\t-c: Columnas\n\t-v: Valor de llenado");
					return -1;
					break;
			}
			i++;
		}while((valor != -1) && (argc != i));
	}
	else
	{
		//printf("\n%cCuantas filas quiere ingresar?", SIG_INTER_ABAJO);
		datoEntrada("\n¨Cuantas filas quiere ingresar? ", &filas);
		datoEntrada("\n¨Cuantas columnas? ", &columnas);
		datoEntrada("\nColoque el numero a llenar en la matriz: ", &valorL);
	}
	
	datos = (int **)crearMatriz2D(filas, columnas, sizeof(int));
	
	for(int i = 0; i < filas; i++)
	{
		printf("%d -. ", i);
		for(int j = 0; j < columnas; j++)
		{
			datos[i][j] = valorL;
			printf(" %d ", datos[i][j]);
		}
		printf("\n");
	}
	liberarMatriz2D((void **)datos, filas);
    system("pause");
	return 0;
}