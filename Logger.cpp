// Logger.cpp: implementation of the Logger class.
//
//////////////////////////////////////////////////////////////////////

#include "Logger.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
 * Constructor del Objeto de Logeo.
 */
Logger::Logger()
{
	strcpy(CTLF,"\r\n");
	pfLog=NULL;

}

/*
 * Setea el nombre del arhivo de logueo.
 *
 * @param	sFileName		char *		Nombre del archivo.
 */
void Logger::SetLogFile(char *sFileName) {
	if ((pfLog=fopen(sFileName,"wb+"))==NULL) {
		cerr << "No se puede generar el log.... Se mostrará en pantalla.\n"; 
	}
}

/*
 * Agrega un mensaje al log.
 *
 * @param	sMessage		char *		Mensaje
 */
void Logger::log(char * message) {
	if (pfLog==NULL)
		cout << message;
	else
		if ((fwrite(message,sizeof(char),strlen(message),pfLog))==0) {
			cerr << "No se puede escribir en el log." << endl;
		}
}

/*
 * Genera una salida de datos al log.
 *
 * Se utiliza este operador de streams, debido a que es claro y 
 * permite concatenar las llamadas para pasarle diferentes parámetros.
 *
 * message					Cadena a grabar en el log.
 */
Logger Logger::operator<<(char * message) {
	log(message);

	return *this;
}

/*
 * Genera una salida de un entero al log.
 *
 * iValue					Valor a grabar en log.
 */
Logger Logger::operator<<(int iValue) {
	log(iValue);

	return *this;
}

void Logger::flush() {
	if (pfLog!=NULL) {
		fflush(pfLog);
	}
}

/*
 * Agrega un valor numérico al log.
 *
 * @param	ld			long double		Dato numérico a loguear.
 */
void Logger::log(long double ld) {
	char *message;
	message = new char[50];
	sprintf(message,"%8.0f",(float)ld);
	log(message);
	delete [] message;
}



/*
 * Cierra el archivo de logueo.
 */
void Logger::close() {
	if (pfLog!=NULL)
		fclose(pfLog);
}

Logger::~Logger()
{
}

/*
 * Graba en log una secuencía de '-' como separador.
 *
 */
void Logger::Delimiter()
{
	Reply("-",80);
	log("\n");
}

void Logger::Reply(char *sValue, int iTimes)
{
	for (int _i=0;_i<iTimes;_i++) {
		log(sValue);
	}
}


void Logger::abort(char * sAbortCause)
{
	log("PROCESO ABORTADO:");
	log("\n");
	log(sAbortCause);

}

char * Logger::GetTimeStamp(char *aux)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	sprintf (aux,"%02ld/%02ld/%02ld %02ld:%02ld:%02ld",st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);

	return aux;
}

/*
 * Setea el nombre del arhivo de logueo.
 *
 * @param	sFileName		char *		Nombre del archivo.
 * @param	sMode			char *		Modo de apertura.
 */
void Logger::SetLogFile(char *sFileName, char *sMode) {
	if ((pfLog=fopen(sFileName,sMode))==NULL) {
		cerr << "No se puede generar el log.... Se mostrará en pantalla.\n"; 
	}
}
