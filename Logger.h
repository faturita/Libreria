// Logger.h: interface for the Logger class.
//
//	Clase para el Manejo del Loggeo
//
//  Permite realizar un loggin precario e informativo.
//  
//
//	@Date		Agosto	2001
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGGER_H__266323FC_8B35_11D5_AAEB_00508B366140__INCLUDED_)
#define AFX_LOGGER_H__266323FC_8B35_11D5_AAEB_00508B366140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <Windows.h>

using  namespace std;

class Logger  
{
private:
	/*
	 * Puntero del Archivo de loggeo.
	 */
	FILE *pfLog;
public:
	void SetLogFile(char *sFileName, char *sMode);
	char CTLF[3];
	char * GetTimeStamp(char * aux);
	/*
	 * Genera un mensaje de interrupci�n en el log.
	 *
	 * Adem�s por las caracter�sticas de este mensaje, se realiz�
	 * un vac�ado del buffer del archivo de log.
	 * @param	sAborCause		Descripci�n del mensaje
	 */
	void abort(char * sAbortCause);
	/*
	 * Repite alg�n mensaje iTimes veces en el archivo de log.
	 * @param sValue		Mensaje a repetir.
	 * @param iTimes		Cantidad de repeticiones.
	 */
	void Reply(char * sValue, int iTimes);
	/*
	 * Genera un delimitado en el archivo de log.
	 */
	void Delimiter();
	/*
	 * Setea el nombre del archivo de loggeo.
	 * @param	sFileName		Nombre del archivo.
	 */
	void SetLogFile(char *sFileName);
	/*
	 * Manda al buffer de loggeo un mensaje.
	 */
	void log(char * message);
	/*
	 * Manda al buffer de loggeo un valor num�rico.
	 */
	void log(long double ld);
	/*
	 * Cierra el archivo de log.
	 */
	void close();
	/*
	 * Vac�a el buffer del log.
	 */
	void flush();
	/*
	 * Outstream para log.
	 */
	Logger operator<<(char * message);
	/* 
	 * Outstream para num�ricos
	 */
	Logger operator<<(int iValue);
	/*
	 * Constructor 
	 */
	Logger();
	virtual ~Logger();

};

#endif // !defined(AFX_LOGGER_H__266323FC_8B35_11D5_AAEB_00508B366140__INCLUDED_)
