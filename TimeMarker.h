// TimeMarker.h: interface for the TimeMarker class.
//
//
//	Clase para el Manejo de Temporizadores.
//
//  Permite la implementación de un temporizador por polling para realizar
//  acciones que dependan del tiempo
//
//
//
//
//	@Date		Agosto	2001
//
//	@Reviews
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMEMARKER_H__68B19183_8BF8_11D5_AAEC_00508B366140__INCLUDED_)
#define AFX_TIMEMARKER_H__68B19183_8BF8_11D5_AAEC_00508B366140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <time.h>
#include <string.h>


#define FILENAMESIZE	255				// Tamaño máximo para los nombres de archivos.


class TimeMarker  
{
private:
	/**
	 * Marca de tiempo
	 */
	time_t iTimeMark;
	/**
	 * Rango de tiempo contra la marca
	 */
	time_t iTimeRange;

public:
	/**
	 * Setea el Rango de Tiempo de Tolerancia (el tamaño del temporizador)
	 * @param iTimeRange		Cantidad de segundos de intervalo.
	 */
	void SetTimeRange(time_t iTimeRange);
	/**
	 * Devuelve true cuando se produjo un cambio mayor al rango de
	 * tolerancia seteado.
	 */
	bool HasChanged();
	/**
	 * Reinicia el Temporizador.
	 */
	void Set();
	/**
	 * Devuelve un char *  con una cadena representativa de la hora y 
	 * día del sistema.
	 * @param OUT		sAux		Puntero a char donde se almacena la cadena
	 */
	void GetTimeMark(char * sAux);
	/**
	 * Dado un string base, devuelve otro string con la marca de tiempo concatenada
	 * al final, y le agrega al final de toda la cadena sFinalString.
	 *
	 * Esta función es muy util para setear nombres de archivos.
	 *
	 * @param	OUT sBufferString	char *  donde se obtiene el string generado.
	 * @param	sBaseString			String base a concatenar.
	 * @param	sFinalString		String a concatenar al final.
	 */
	void SetDatedString(char *sBufferString, char *sBaseString,char *sFinalString);
	TimeMarker();
	virtual ~TimeMarker();

};

#endif // !defined(AFX_TIMEMARKER_H__68B19183_8BF8_11D5_AAEC_00508B366140__INCLUDED_)
