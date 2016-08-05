// TimeMarker.cpp: implementation of the TimeMarker class.
//
//////////////////////////////////////////////////////////////////////

#include "TimeMarker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TimeMarker::TimeMarker()
{

}

TimeMarker::~TimeMarker()
{

}


void TimeMarker::SetTimeRange(time_t iTimeRange) {
	TimeMarker::iTimeRange=iTimeRange;
}


/**
 * Devuelve true cuando se produjo un cambio mayor que iTimeRange en 
 * el tiempo del sistema.
 *
 * Chequear que pasa cuando cambia el día...
 */
bool TimeMarker::HasChanged() {
	time_t _iCurrentTimeMark;
	time(&_iCurrentTimeMark);
	if ((_iCurrentTimeMark-iTimeMark)<iTimeRange) {
		return false;

	} else {
		return true;
	}

}
	
void TimeMarker::Set() {
	time(&iTimeMark);
}

void TimeMarker::SetDatedString(char *sBufferString, char *sBaseString,char *sFinalString)
{
		char *_sDate=new char[FILENAMESIZE];
		strcpy(_sDate,"");
		
		strcpy(sBufferString,sBaseString);
		
		GetTimeMark(_sDate);
		strcat(sBufferString,_sDate);
		strcat(sBufferString,sFinalString);
				
		delete []_sDate;
}

void TimeMarker::GetTimeMark(char * sBuff) {
	char * _sDateChar;
	char * _sTimeChar;
	char * _sAux;
	

	_sTimeChar = new char[FILENAMESIZE];
	_sDateChar = new char[FILENAMESIZE];
	_sAux	   = new char[FILENAMESIZE];

	_strdate(_sDateChar);
	_strtime(_sTimeChar);
	
	

	strcpy(_sAux,"");
	strcat(_sAux,strcat (strcat(_sDateChar,"_"),strcat(_sTimeChar,"_")));

	int _iIndex=0;

	for (int i=0;i<FILENAMESIZE;i++) {
		if ( (_sAux[i]!='/') && (_sAux[i]!=':') && (_sAux[i]!='_') ) {
			sBuff[_iIndex++]=_sAux[i];
		}
	}

	delete []_sTimeChar;
	delete []_sDateChar;
	delete []_sAux;
}
	