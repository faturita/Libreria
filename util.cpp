// util.cpp: Libreria de funciones generales.
//
//////////////////////////////////////////////////////////////////////

#include "util.h"


/***********************************************************************
 *
 * Potencia de un numero (simil al pow del C pero devuelve un long double)
 */
long double pow2( int base, int potencia ) //long double
{
    long double rta = 1; //long double
    int i;
    
    for (i=1; i <= potencia; i++)

        rta = ( rta * base );

    return rta;
} //fin pow2


/***********************************************************************
 *
 * Convierte de comp. a long double y sino devuelve gcNOTCONVERT
 *
 * Nota: Para que ande este hijo de puta hay que leer un unsigned char
 *      o poner la opcion del compilador /J (para que los char por default
 *      sean unsigned)
 *
 *
 */
long double __stdcall HexToDec ( char * szVarRead , long iLenVar ) //long double
{

  long double rta = 0;
  long double aux1;
  long double aux2;
  char pbyte;
  char blanco;
  int  p;
  int  i;

  pbyte  = szVarRead[0] >> 7;       // shift de 7 posiciones del primer byte
  blanco = pbyte        >> 1;       // crea una byte con todos los bit en 0

  if ( pbyte != blanco )            // si el primer bit del primer byte es 1

     for (i=0; i < iLenVar; i++)    // hace el complemento a 1 de cada byte
                                    // del parametro de entrada
          szVarRead[i] = ~ szVarRead[i];
 
  for (i=0; i < iLenVar; i++)        // convierte de hex a dec
  {
    p = ( (iLenVar - (i+1))  * 2 );  // potencia
    
    aux1 = pow2(16, p);              // eleva
    
    aux2 = (int)szVarRead[i] * aux1; // multiplica
    
    rta = rta + aux2;                // acumula
  }

  if ( pbyte != blanco )             // si el primer bit del primer byte es 1
  
      return rta * -1;               // el resultado es negativo
  else
  
      return rta;

}

/**********************************************************************
 * 
 * Realiza ++ sobre un número representado en un char.
 *
 * Elimina la necesidad de reconvertir de un tipo al otro, sumando 
 * directamente sobre el char *
 * No es necesario que se especifique un valor con solo números, sino
 * que los caracteres son descartados y se toman solo los valores numéricos
 * como parte del número de derecha a izquierda.
 *
 *
 * @param	OUT	sName			Valor que debe contener algún número
 *
 */
void SumChars(char * sName) {
	unsigned int _iLen=strlen(sName);
	char _cAcumulator=0;
	int _j;
	
	for (_j=_iLen-1;_j>=0;_j--) {
		if (sName[_j]>='0' && sName[_j]<='9') {
			sName[_j]=sName[_j]+1;
			if (sName[_j]>57) {
				_cAcumulator=+1;
				sName[_j]='0';
			} 
			break;
		}

	}
	
	for (int _i=_j-1;_i>=0;_i--) {
		if (sName[_i]>='0' && sName[_i]<='9') {
			
			if (_cAcumulator>0) {
				sName[_i]=sName[_i]+_cAcumulator;
				_cAcumulator=0;
			}

			if (sName[_i]>57) {
				_cAcumulator=+1;
				sName[_i]=sName[_i]-57+47;
			} 
			else {
			break;
			}
		}
	}
	// sName Modified
}


/**
 * DEPRECATED
 */
long   GetValue(char * sName, int iPositions) {
	long  _iAcumulator=0;

	for (unsigned int i=0;i<strlen(sName);i++) {
		if (sName[i]>='0' && sName[i]<='9')
			_iAcumulator+=((sName[i]-48)*(long)pow((double)10,iPositions--));
	}

	return (_iAcumulator);
}

/*********************************************************************
 * Devuelve el largo de un archivo en el filesystems
 * 
 * @param sFileName		Nombre del archivo.
 * @return				Devuelve en bytes el tamaño del archivo
 *
 */
int GetFileLength(char *sFileName) {
	int fd=open(sFileName,_A_NORMAL);
	int value=filelength(fd);
	close(fd);
	return(value);
}

/*********************************************************************
 * 
 * Devuelve la cantidad de espacio usuario disponible en bytes en la unidad
 * especificada en drive.
 *
 * iDrive debe ser el número correspondiente a la unidad, según el orden
 * que le asigne windows.
 *
 * @param	iDrive			Ordinal del drive a testear.
 * @return					Cantidad en bytes de espacio disponible.
 */
int GetDiskFree (int iDrive) {
	_diskfree_t dt;
	_getdiskfree(iDrive,&dt); // try 3
	return (dt.avail_clusters * dt.sectors_per_cluster * dt.bytes_per_sector);
}

/*********************************************************************
 *
 * Devuelve true cuando cChar es un caracter de ascii mayor a 31.
 *
 * @param	cChar		Caracter a evaluar.
 * @return				Devuelve true o false
 */
bool isCharacter(char cChar) {
	return (cChar>=32);
}

/**********************************************************************
 * 
 * Toma el nombre en sFullFileName y lo divide en el patname que almacena
 * en sPathName y el nombre del archivo, que guarda en sFileName
 *
 * Su uso principal es para obtener el nombre de un archivo o el directorio
 * en donde se encuentra en base al path completo del archivo.
 *
 * @param	sFullFileName		Path completo del archivo.
 * @param	OUT sPathName		Path de la locación del archivo.
 * @param	OUT sFileName		Nombre del archivo.
 */
void SplitPathName(const char *sFullFileName,char *sPathName,char *sFileName) {
	
	using namespace std;

	string s(sFullFileName);
	
	int iSlashIndex=s.find_last_of("\\",s.length());
	
	strcpy(sPathName,s.substr(0,iSlashIndex+1).c_str());
	strcpy(sFileName,s.substr(iSlashIndex+1,s.length()).c_str());

}


/**********************************************************************
 * 
 * Renombra un archivo especifico, copiandolo con su nombre con un prefijo,
 * chequeando que los tamaños sean iguales y luego eliminando la copia
 * original.
 *
 * @param sFullFileName		Nombre + Path completo del archivo.
 * @param sPrefix			Prefijo a agregar al archivo.
 */
int RenameAddPrefix(char *sFullFileName,char *sPrefix) {
	char _sFileName[FILENAMESIZE];
	char _sPathName[FILENAMESIZE];
	char _sAuxFileName[FILENAMESIZE];
	
	SplitPathName(sFullFileName,_sPathName,_sFileName);
	
	strcpy(_sAuxFileName,_sPathName);
	strcat(_sAuxFileName,sPrefix);
	strcat(_sAuxFileName,_sFileName);
	
	BOOL bResult=CopyFile(sFullFileName,_sAuxFileName,true);
		
	if ( (bResult) && (GetFileLength(sFullFileName)==GetFileLength(_sAuxFileName)) ) {
		// La copia ha sido aparentemente exitosa.
		if (!remove(sFullFileName)) {
			return NOOK;
		}
		else {
			return OK;
		}
	}
	else {
		return NOOK;
	}
}

void swap(char *sString1, char *sString2)
{
	char sAux[276];
	strcpy(sAux, sString1);
	strcpy(sString1, sString2);
	strcpy(sString2, sAux);
}

int ExecBkgnd(char *sProcess, char *sCommandLine)
{
	
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);

    // Start the child process. 
    if( !CreateProcess( NULL, // No module name (use command line). 
        sProcess, // Command line. 
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        CREATE_NEW_PROCESS_GROUP,                // No creation flags. 
        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
    {
        return 1;
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );


	if (pi.hProcess == NULL)
		return 1;

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
	
	return 0;
}

int WaitProcess(PROCESS_INFORMATION pi, DWORD dwMilliSeconds)
{
	DWORD dwExitCode=1;
    
	if (pi.hProcess == NULL)
		return 1;
	
	DWORD dwRetValue = WaitForSingleObject( pi.hProcess, dwMilliSeconds );
		
	if (dwRetValue==WAIT_TIMEOUT) {
		// Timeout expired, lo parto al medio.
		if (!TerminateProcess(pi.hProcess,1))
			return 1;
	} 

    if (!GetExitCodeProcess(pi.hProcess,&dwExitCode))
		return 1;
		
	// Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

	return dwExitCode;
}

int ExecAsyncBkgnd(PROCESS_INFORMATION &pi, char *sProcess)
{
	STARTUPINFO si;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);

    // Start the child process. 
    if( !CreateProcess( NULL, // No module name (use command line). 
        sProcess, // Command line. 
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        CREATE_NEW_PROCESS_GROUP,                // No creation flags. 
        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
    {
        return 1;
    }

 	if (pi.hProcess == NULL)
		return 1;

 	return 0;
}

int ExecBkgndTimeout(char *sProcess, DWORD dwMilliSeconds)
{
	DWORD dwExitCode=1;
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);

    // Start the child process. 
    if( !CreateProcess( NULL, // No module name (use command line). 
        sProcess, // Command line. 
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        CREATE_NEW_PROCESS_GROUP,                // No creation flags. 
        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
    {
        return 1;
    }

    // Wait until child process exits.
    DWORD dwRetValue = WaitForSingleObject( pi.hProcess, dwMilliSeconds );
		
	if (dwRetValue==WAIT_TIMEOUT) {
		// Timeout expired, lo parto al medio.
		if (!TerminateProcess(pi.hProcess,1))
			return 1;
	} 

	if (pi.hProcess == NULL)
		return 1;

    if (!GetExitCodeProcess(pi.hProcess,&dwExitCode))
		return 1;
		
	// Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

	return dwExitCode;
}
/*************************************************************************** 
 * Lee los parámetros de la línea de comando devolviendo el dato
 * para ese parámetro.
 *
 * argc				Cantidad de argumentos de la línea de comando.
 * argv				Array de cadenas con los parámetros de la línea
 *					de comando.
 * pcOpcion			Modificador a buscar en la línea de comandos.
 */
char * TomarParametros(int argc, char* argv[], char pcOpcion[])
{
	char *pcValor;

	for (int i=0;i<argc;i++) {
		pcValor = strstr(argv[i],pcOpcion);
		
		// Si encontró el parámetro y el mismo tiene algun valor
		if ((pcValor!=NULL) && strlen(pcValor)>strlen(pcOpcion) )
			return pcValor+strlen(pcOpcion);
	}

	// No encontró nada.
	return NULL;	
}

/******************************************************************************
 * Permite devolver un parámetro leído de la línea de comando numérico, 
 * con la posibilidad de que si el mismo no es encontrado se devuelve un 
 * valor por default.
 *
 * argc				Cantidad de parámetros en cmdline.
 * argv				Array de cadenas de cmdline.
 * pcOpcion			Modificador a buscar.
 * iDefault			Valor entero a devolver si no se encuentra pcOpcion.
 */
int TomarParametros(int argc, char* argv[], char pcOpcion[], int iDefault)
{
	char *pcValor = TomarParametros(argc,argv,pcOpcion);

	if (pcValor==NULL)
		return iDefault;
	else
		return atoi(pcValor);
}

/******************************************************************************
 *
 * Devuelve verdadero si hay espacio suficiente en el directorio
 * especificado para poder concatenar los dos archivos especificados.
 *
 * @param	sDirectory		Directorio de trabajo.
 * @param	sFile1			Archivo a concatenar.
 * @param	sFile2			Archivo a concatenar.
 *
 *****************************************************************************/
BOOL CheckDiskSpace(char sDirectory[276],char sFile1[276], char sFile2[276])
{
	ULARGE_INTEGER l1;
	ULARGE_INTEGER l2;
	ULARGE_INTEGER l3;


	if (!GetDiskFreeSpaceEx(sDirectory,&l1,&l2,&l3))
		return true;

	DWORD iLength=GetFileLength(sFile1)+GetFileLength(sFile2);
	
	// Aca se compara que entre en el espacio siempre y cuando la cantidad
	// de bytes libres en el servidor no supere la precisión el DWORD.
	if ( l3.LowPart <= iLength && l3.HighPart == 0)
		return false;

	return true; 
}

/****************************************************************************** 
 *
 * Concatena el archivo sCorteBase con sCorteSeg en el directorio
 * sDirectory.
 *
 * @param		sDirectory			Directorio de trabajo.
 * @param		sCorteBase			Corte al que le concatena el otro corte.
 * @param		sCorteSeg			Corte a concatenar.
 * @return							0 ok, 1 error.
 *
 *****************************************************************************/
int Concatenar(char (*sFile)[276], int iCantidad, char sDestFile[276])
{
	// Copio el corte base mas el cortes seg a un corte final,
	// para luego comparar los tamaños de los tres archivos,
	// luego eliminar el base, eliminar el seg, y renombrar el 
	// auxiliar a seg.
	
	// Copio el base mas el seg a 
	char *sCmdShell;
	int iFileLength=0;

	sCmdShell = new char[276*(iCantidad+1)];
		
	strcpy(sCmdShell,"cmd /c copy /b ");

	for (int i=0; i<iCantidad; i++) {
		strcat(sCmdShell, "\"");
		strcat(sCmdShell, sFile[i]);
		strcat(sCmdShell, "\"");
		
		iFileLength+=GetFileLength(sFile[i]);
		if (i+1<iCantidad)
			strcat(sCmdShell, "+");
	}

	strcat(sCmdShell, " ");
	strcat(sCmdShell, sDestFile);
	
	if (iCantidad == 0)
		return 1;

	// Verifica si tiene espacio en el disco para concatenar los archivos.
	//if (!CheckDiskSpace(sDirectory,sFullCorteBase,sFullCorteSeg))
	//{
	//	SendLog ("No hay espacio suficiente en disco para procesar los archivos.");
	//	return 1;
	//}

	//printf (sCmdShell);
	//MessageBox(0,sCmdShell,"Alerta",MB_OK);
	// Ejecuta el cmd con la concatenación.

	if ( ExecBkgnd(sCmdShell,NULL)==1 )
	{
		return 1;
	}
	
	// Comprueba los tamaños
	if ( (iFileLength)!=GetFileLength(sDestFile))
	{
		return 1;
	}

	return 0;
}
