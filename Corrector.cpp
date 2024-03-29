// Corrector.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Diccionario.h"
#include <string>

int main()
{
	char	szNombre[50];
	char	szPalabras[NUMPALABRAS][TAMTOKEN];
	int		iEstadisticas[NUMPALABRAS];
	int		iNumElementos = 0;
	int		iNumSugeridas;
	char	szPalabraLeida[TAMTOKEN];
	char	szPalabrasSugeridas[3300][TAMTOKEN];
	char	szListaFinal[3300][TAMTOKEN];
	int		iPeso[3300];
	int		iNumLista;

	register int i;

	for (i = 0; i < NUMPALABRAS; i++)
		iEstadisticas[i] = 0;

	strcpy(szNombre, "dnquijote.txt");
	//printf("Archivo para el diccionario: ");
	//scanf("%s", szNombre);

	printf("Cargando ...\n\n");

	Diccionario(szNombre, szPalabras, iEstadisticas, iNumElementos);

	printf("\nDiccionario Cargado!!! \n\n");

/*
	for (i = 0; i < iNumElementos; i++)
		printf("%-12s %i\n", szPalabras[i], iEstadisticas[i]);
*/

	printf("Numero de palabras: %i\n", iNumElementos);
	
	do
	{
		printf("Palabra ('q' para salir): ");
		scanf("%s", szPalabraLeida);

		iNumLista = 0;
		iNumSugeridas = 0;
		ClonaPalabras(szPalabraLeida, szPalabrasSugeridas, iNumSugeridas);

		/*
		for (i = 0; i < iNumSugeridas; i++)
			printf("%-12s\n", szPalabrasSugeridas[i]);
		*/

		ListaCandidatas(szPalabrasSugeridas, iNumSugeridas, szPalabras, iEstadisticas, iNumElementos, szListaFinal, iPeso, iNumLista);

		
		for (i = 0; i < iNumLista; i++)
			printf("%-12s %i\n", szListaFinal[i], iPeso[i]);
		

	}
	while (strcmp(szPalabraLeida, "q") != 0);

    return 0;
}

