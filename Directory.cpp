// Directory.cpp: implementation of the Directory class.
//
//////////////////////////////////////////////////////////////////////

#include "Directory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Directory::Directory()
{
	iTotalSize = INITIALSIZE;
	asFileList = new PATHNAMETYPE[iTotalSize];
}

Directory::~Directory()
{
	delete [] asFileList;
}

void Directory::Set(char *sPathName)
{
	strcpy(Directory::sPathName,sPathName);
}

char * Directory::GetPathName()
{
	return sPathName;
}

void Directory::Load(char *sPathName)
{
	Load(sPathName,"*");
}

void Directory::SortFiles()
{
	for (int i=0;i<iSize-1;i++) {
		for (int j=0;j<iSize-1;j++) {
			if ( strcmp(asFileList[j].sName,asFileList[j+1].sName)>0 )
				swap(asFileList[j].sName, asFileList[j+1].sName);
		}
	}
}

void Directory::Load(char *sPathName, char *sWildCard)
{
	char sAuxPathName[275];

	strcpy(Directory::sPathName,sPathName);

	if (!PathIsDirectory(sPathName)) {
		cerr << sPathName << ": no es directorio.\n";
		return;
	}

	if (sWildCard==NULL)
		strcpy(Directory::sWildCard,"*");
	else
		strcpy(Directory::sWildCard,sWildCard);

	strcpy(sAuxPathName,sPathName);
	strcat(sAuxPathName,"\\");
	strcat(sAuxPathName,Directory::sWildCard);

	WIN32_FIND_DATA lpFindFileData;

	// Limpio el buffer de errores de este thread.
	SetLastError(0);
	
	// Lleva los controles a cero (no hay archivos encontrados)
	iSize=0;iIndex=0;
	
	HANDLE hl1= FindFirstFile(sAuxPathName,&lpFindFileData);
	
	if (hl1==INVALID_HANDLE_VALUE)
		return;
	
	while (GetLastError()!=ERROR_NO_MORE_FILES) {

		if (lpFindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) {

			strcpy(asFileList[iSize++].sName,lpFindFileData.cFileName);
			if (iSize==iTotalSize) {
				PATHNAMETYPE *asAuxFileList = new PATHNAMETYPE[iTotalSize*2];
				for (int i=0;i<iTotalSize;i++) {
					asAuxFileList[i]=asFileList[i];
				}
				delete [] asFileList;
				asFileList=asAuxFileList;
				iTotalSize=iTotalSize*2;
			}

		}
		
		FindNextFile(hl1,&lpFindFileData);
	}

	// Ordeno los nombres de archivos.
	SortFiles();

	// Limpio el buffer de errores de este thread.
	SetLastError(0);

}

/*void Directory::Load(char *sPathName)
{
	char sAuxShellPathName[275];
	strcpy(sAuxShellPathName,"cmd /c dir ");
	strcat(sAuxShellPathName,sPathName);
	strcat(sAuxShellPathName," /b /o:n");


	strcpy(Directory::sPathName,sPathName);
	if (!PathIsDirectory(sPathName)) {
		cerr << sPathName << ": no es directorio.\n";
		return;
	}


	FILE *pf=_popen(sAuxShellPathName,"r");

	char data[256];

	if (pf==NULL) {
		cerr << "No se pudo abrir el pipe al directorio.\n";
		return;
	}
	iSize=0;
	fgets(data,256,pf);
	while (!feof(pf)) {
		if (strlen(data)>1) {
			if (data[strlen(data)-1]=='\n')
				data[strlen(data)-1]='\0'; // El nombre tiene un \n al final.
			//strcpy(asFileList[iSize].sName,sPathName);
			//strcat(asFileList[iSize].sName,"\\");
			strcpy(asFileList[iSize++].sName,data);
			if (iSize==iTotalSize) {
				PATHNAMETYPE *asAuxFileList = new PATHNAMETYPE[iTotalSize*2];
				for (int i=0;i<iTotalSize;i++) {
					asAuxFileList[i]=asFileList[i];
				}
				delete [] asFileList;
				asFileList=asAuxFileList;
				iTotalSize=iTotalSize*2;
			}
			fgets(data,256,pf);
		}
	}

	iIndex=0;		
	fclose(pf);
}
*/

void Directory::Refresh()
{
	Load(sPathName);
}

char * Directory::Next()
{
	if (iIndex==iSize) {
		return NULL;
	}

	return (asFileList[iIndex++].sName);
}

int Directory::GetFileList(char (*sFile)[276])
{
	char aux[276];
	char *sFilename;
	int i=0;
	
	while ( (sFilename=Next())!=NULL) {
		strcpy(aux,sPathName);
		strcat(aux,sFilename);
		strcpy(sFile[i],aux);
		i++;
	}

	return iSize;
}

int Directory::GetSize()
{
	return iSize;
}
