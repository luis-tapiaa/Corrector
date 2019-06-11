#pragma once

#define TAMTOKEN 50
#define NUMPALABRAS 50000


void	Diccionario(
		char *	szNombre,
		char	szPalabras[][TAMTOKEN],
		int		iEstadisticas[],
		int &	iNumElementos);

void	ClonaPalabras(
		char *	szPalabraLeida,
		char	szPalabrasSugeridas[][TAMTOKEN],
		int &	iNumSugeridas);

void	ListaCandidatas(
		char	szPalabrasSugeridas[][TAMTOKEN],
		int		iNumSugeridas,
		char	szPalabras[][TAMTOKEN],
		int		iEstadisticas[],
		int		iNumElementos,
		char	szListaFinal[][TAMTOKEN],
		int		iPeso[],
		int	&	iNumLista);

int		Buscar(
		char *	szPalabra,
		char	szPalabras[][TAMTOKEN],
		int		iNumElementos);

void	Limpiar(
		char *	szPalabra);