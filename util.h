#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Map>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <math.h>
#include <windows.h>
#include <direct.h>


#define OK				1
#define NOOK			0
#define FILENAMESIZE	255



/**
 * Funciones Varias para manejo de número computacionales.
 * 
 * @date	06-08-01
 */

/*
 * Devuelve el valor en formato double del computacional codificado
 * en el buffer de entrada.
 *
 * @param	szVarRead			Buffer con los datos a considerar.
 * @param	iLenVar				Longitud del dato.
 * @return						Devuelve el valor convertido.
 */
long double __stdcall HexToDec ( char * szVarRead , long iLenVar );
/*
 * Eleva base a potencia.
 *
 * @param	base				Base del exponente. Valor a elevar.
 * @param	potencia			Potencia
 * @return						Devuelve base elevado a la potencia.
 */
long double pow2( int base, int potencia );
long GetValue(char *sName,int iPositions);
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
void SumChars(char *sName);
/*********************************************************************
 * Devuelve el largo de un archivo en el filesystems
 * 
 * @param sFileName		Nombre del archivo.
 * @return				Devuelve en bytes el tamaño del archivo
 *
 */
int GetFileLength(char *sFileName);
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
int GetDiskFree (int iDrive);
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
void SplitPathName(const char *sFullFileName,char *sPathName,char *sFileName);
/**********************************************************************
 * 
 * Renombra un archivo especifico, copiandolo con su nombre con un prefijo,
 * chequeando que los tamaños sean iguales y luego eliminando la copia
 * original.
 *
 * @param sFullFileName		Nombre + Path completo del archivo.
 * @param sPrefix			Prefijo a agregar al archivo.
 */
int RenameAddPrefix(char *sFileName,char *sPrefix);
/*********************************************************************
 *
 * Devuelve true cuando cChar es un caracter de ascii mayor a 31.
 *
 * @param	cChar		Caracter a evaluar.
 * @return				Devuelve true o false
 */
bool isCharacter(char cChar);
/**********************************************************************
 * 
 * Intercambia las dos cadenas entre si.
 *
 * @param	sString1	Cadena1
 * @param	sString2	Cadena2
 */
void swap(char *sString1, char *sString2);
/***********************************************************************
 *
 * Ejecuta el proceso especificado en sProcess.
 * 
 * El proceso a ejecutar debe ser un binario.
 *
 * @param		sProcess		Binario a ejecutar.
 * Return						0 si completó correctamente, 1 en caso 
 *								de error.	
 */
int ExecBkgnd(char *sProcess,char *sCommand);
int WaitProcess(PROCESS_INFORMATION pi, DWORD dwMilliSeconds);
int ExecAsyncBkgnd(PROCESS_INFORMATION &pi, char *sProcess);
int ExecBkgndTimeout(char *sProcess, DWORD dwMilliSeconds);

/************************************************************************
 * Busca el valor que acompaña al modificador pcOpcion en la cmdline, y
 * lo devuelve.
 *
 * Formato de cada modificador "{modif}valor"
 *
 * @param		argc			Cantidad de argumentos
 * @param		argv			Array con los parámetros a modificar.
 * @param		pcOpcion		Modificador a buscar.
 * Return						Valor del modificador.
 */
char * TomarParametros(int argc, char* argv[], char pcOpcion[]);
/************************************************************************
 * Busca el valor que acompaña al modificador pcOpcion en la cmdline, y
 * lo devuelve.  Si no lo encuentra devuelve el valor especificado por
 * defecto.
 *
 * Formato de cada modificador "{modif}valor"
 *
 * @param		argc			Cantidad de argumentos
 * @param		argv			Array con los parámetros a modificar.
 * @param		pcOpcion		Modificador a buscar.
 * @param		iDefault		Valor a devolver por default.
 * Return						Valor del modificador.
 */
int TomarParametros(int argc, char* argv[], char pcOpcion[], int iDefault);

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
BOOL CheckDiskSpace(char sDirectory[276],char sFile1[276], char sFile2[276]);
int Concatenar(char (*sFiles)[276], int iCantidad, char sDestFile[276]);