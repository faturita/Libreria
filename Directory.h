//
// Directory
//
// Clase para visualización de directorios.
//
// Utiliza la libreria Shlwapi.lib
//
// Permite acceder a un directorio y recorrer su contenido, trabajando
// sobre los archivos particulares.
//
// Versión:	2.0
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTORY_H__76F61853_9AE9_11D5_AAEE_00508B366140__INCLUDED_)
#define AFX_DIRECTORY_H__76F61853_9AE9_11D5_AAEE_00508B366140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <Shlwapi.h>
#include <direct.h> 

#include "util.h"

#define INITIALSIZE 256
#define NOMORE		"NOMORE"

using  namespace std;

struct PATHNAMETYPE {
	char sName[256];
};


class Directory  
{
public:
	int GetSize();
	int GetFileList(char (*sFile)[276]);
	char * Next();
	void Refresh();
	void Load(char *sPathName);
	void Load(char *sFileName, char *sWildCard);
	char * GetPathName();
	void Set(char *sPathName);
	void SortFiles();
	Directory();
	virtual ~Directory();

private:
	int iTotalSize;
	PATHNAMETYPE *asFileList;
	int iSize;
	int iIndex;
	char sPathName[256];
	char sWildCard[256];
};


#endif // !defined(AFX_DIRECTORY_H__76F61853_9AE9_11D5_AAEE_00508B366140__INCLUDED_)
