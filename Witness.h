// Witness.h: interface for the Witness class.
//
//
// Clase para manejar archivos testigos para controles de ejecución.
//
// Permite crear un archivo de testigo con el cual poder realizar 
// recuperaciones de ejecución y para controlar los pasos realizados.
// Soporte para ejecuciones transaccionales.
//
//
// Versión:		1.0
// Fecha:		Agosto	2001
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WITNESS_H__828BC685_8D87_11D5_AAED_00508B366140__INCLUDED_)
#define AFX_WITNESS_H__828BC685_8D87_11D5_AAED_00508B366140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PropertyStore.h"

#define		WITNESSKEY			"witness"		// Nombre por el que se busca la clave en el archivo testigo.
#define		G_ALLOWWITNESS		true			// True valida contra el testigo.


class Witness : private PropertyStore  
{
public:
	void Disable();
	void Enable();
	bool Match(char * sCmpValue);
	Witness(char * sFileName) ;
	char * Recover();
	void Register(char * sNewValue);
	virtual ~Witness();

private:
	bool bEnabled;
};

#endif // !defined(AFX_WITNESS_H__828BC685_8D87_11D5_AAED_00508B366140__INCLUDED_)
