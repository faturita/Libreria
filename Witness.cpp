// Witness.cpp: implementation of the Witness class.
//
//////////////////////////////////////////////////////////////////////

#include "Witness.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Witness::~Witness()
{

}

void Witness::Register(char *sNewValue)
{
	Set(WITNESSKEY,sNewValue);
	Save();
}

char * Witness::Recover()
{
	Load();
	return (Get(WITNESSKEY));

}

Witness::Witness(char * sFileName) : PropertyStore(sFileName) 
{
	bEnabled=(G_ALLOWWITNESS);
}

bool Witness::Match(char *sCmpValue)
{
	if (!bEnabled)
		return true;
	
	if (strcmpi(Recover(),EMPTYVALUE)) {
		if (!strcmpi(Get(WITNESSKEY),sCmpValue)) {
			return true;
		} else {
			return false;
		}
	} 
	else {
		return true;
	}
}

void Witness::Enable()
{
	bEnabled=true;
}

void Witness::Disable()
{	
	bEnabled=false;
}
