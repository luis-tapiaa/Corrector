#include "stdafx.h"
#include "Diccionario.h"
#include <string>

char	ALFABETO[33] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
			'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
			't', 'u', 'v', 'w', 'x', 'y', 'z', 160, 130, 161,
			162, 163, 164, 0 };


void	Diccionario(
		char *	szNombre,
		char	szPalabras[][TAMTOKEN],
		int		iEstadisticas[],
		int &	iNumElementos)
{
	char	szAux[TAMTOKEN];

	FILE * fp;
	fp = fopen(szNombre, "r");

	if (fp != NULL)
	{
		while (!feof(fp) && iNumElementos < NUMPALABRAS)
		{
			szAux[0] = '\0';
			fscanf(fp, "%s", szAux);
			Limpiar(szAux);
			int res = Buscar(szAux, szPalabras, iNumElementos);
			if (res != -1)
			{
				iEstadisticas[res] ++;
			}
			else
			{
				int a = iNumElementos - 1;
				while (a >= 0 && strcmp(szPalabras[a], szAux) > 0)
				{
					strcpy(szPalabras[a + 1], szPalabras[a]);
					iEstadisticas[a + 1] = iEstadisticas[a];
					a --;
				}			
				strcpy(szPalabras[a + 1], szAux);
				iEstadisticas[a + 1] = 1;
				iNumElementos ++;
			}
		}
	}
	else
	{
		printf("** No se puede abrir el archivo **");
	}
}

void	ClonaPalabras(
		char *	szPalabraLeida,
		char	szPalabrasSugeridas[][TAMTOKEN],
		int &	iNumSugeridas)
{
	int		length = strlen(szPalabraLeida);
	char	szAux[TAMTOKEN];
	register int i;
	
	for (i = 0; i < length; i++)
	{
		strcpy(szAux, szPalabraLeida);
		szAux[i] = '\0';
		strncat(szAux, &szPalabraLeida[i + 1], length);
		strcpy(szPalabrasSugeridas[iNumSugeridas++], szAux);
	}

	for (i = 0; i < length - 1; i++)
	{
		strcpy(szAux, szPalabraLeida);
		char temp = szAux[i];
		szAux[i] = szAux[i + 1];
		szAux[i + 1] = temp;
		strcpy(szPalabrasSugeridas[iNumSugeridas++], szAux);
	}

	for (i = 0; i < length; i++)
	{
		strcpy(szAux, szPalabraLeida);
		for (int j = 0; j < 32; j++) {
			szAux[i] = ALFABETO[j];
			strcpy(szPalabrasSugeridas[iNumSugeridas++], szAux);
		}		
	}

	for (i = 0; i < length + 1; i++)
	{
		strcpy(szAux, szPalabraLeida);
		szAux[i] = '\0';
		strcat(szAux, " ");
		strncat(szAux, &szPalabraLeida[i], length);
		for (int j = 0; j < 32; j++) {
			szAux[i] = ALFABETO[j];
			strcpy(szPalabrasSugeridas[iNumSugeridas++], szAux);
		}
	}
}

void	ListaCandidatas(
		char	szPalabrasSugeridas[][TAMTOKEN],
		int		iNumSugeridas,
		char	szPalabras[][TAMTOKEN],
		int		iEstadisticas[],
		int		iNumElementos,
		char	szListaFinal[][TAMTOKEN],
		int		iPeso[],
		int	&	iNumLista)
{
	register int i;

	for (i = 0; i < iNumSugeridas; i++)
	{
		int res = Buscar(szPalabrasSugeridas[i], szPalabras, iNumElementos);
		if (res != -1) {
			int is = Buscar(szPalabrasSugeridas[i], szListaFinal, iNumLista);			
			if (is == -1) {
				int a = iNumLista - 1;
				while (a >= 0 && strcmp(szListaFinal[a], szPalabrasSugeridas[i]) > 0)
				{
					strcpy(szListaFinal[a + 1], szListaFinal[a]);
					iPeso[a + 1] = iPeso[a];
					a--;
				}
				strcpy(szListaFinal[a + 1], szPalabrasSugeridas[i]);
				iPeso[a + 1] = iEstadisticas[res];
				iNumLista++;
			}
		}
	}
}

int		Buscar(
		char *	szPalabra,
		char	szPalabras[][TAMTOKEN],
		int		iNumElementos)
{
	int		iMitad;
	int		iInferior;
	int		iSuperior;
	int		iContador;

	register int i;

	iInferior = 0;
	iSuperior = iNumElementos;
	iContador = iNumElementos;

	while (iInferior <= iSuperior && iContador != 0)
	{
		iMitad = (iInferior + iSuperior) / 2;
		int res = strcmp(szPalabras[iMitad], szPalabra);
		if (res == 0)
			return iMitad;
		else if (res > 0)
			iSuperior = iMitad - 1;
		else
			iInferior = iMitad + 1;

		iContador /= 2;
	}
	return -1;
}

void	Limpiar(
		char *	szPalabra)
{
	int		length = strlen(szPalabra);
	int		iTam = 0;
	char 	szAux[TAMTOKEN];
	//int		especial[] = {-31, -23, -19, -13, -6, -4, -15};

	register int i;

	for (i = 0; i < length; i++)
	{
		char c = tolower(szPalabra[i]);
		if (c >= 97 && c <= 122)
		{
			szAux[iTam++] = c;
		}		
	}
	szAux[iTam] = '\0';
	strcpy(szPalabra, szAux);
}