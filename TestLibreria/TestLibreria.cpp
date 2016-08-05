#include "..\PropertyStore.h"
#include "..\Directory.h"
#include "..\Logger.h"


void main2() 
{
	printf ("Testeador de Librerias.\n");
	
	try {
		PropertyStore ps("archivo.ini.txt");
		ps.Load();
		
		ps.Set("nombre","valor1");

		ps.Save();

	} catch (char *d) {
		printf ("Error:%s",d);
	}
	
	exit(0);
}

void main()
{
	Directory dd;
	printf ("Directory :");
	dd.Load("C:\\","*.txt");
	char *sFileName;
	
	sFileName = dd.Next();

	if (sFileName!=NULL)
		printf (sFileName);

	//ExecBkgnd("cmd /c echo hola >a.txt",NULL);
}


void maind()
{
	/*Logger logs;
	char aux[256];
	logs.SetLogFile("prueba1.log");
	logs.log(32);
	logs.log("hola que tal\n");
	logs << logs.CTLF << logs.GetTimeStamp(aux) <<":logging info....";
	logs.Reply("10",10);
	logs.flush();
	logs.Delimiter();
	logs.abort("Está todo mal.....\n");
	logs.close();*/

	char (*sDestFile)[276];

	Directory dd;
	dd.Load("C:\\Archivos de Programa\\","*.txt");

	int icantidad;
	sDestFile = new char[dd.GetSize()][276];
	icantidad = dd.GetFileList(sDestFile);

	//Concatenar(sDestFile,icantidad,"superprueba.log");
}

// This is risky.
int main_5()
{
	PROCESS_INFORMATION pi;
	
	ExecAsyncBkgnd(pi,"C:\\WINNT\\system32\\Cmd.exe");

	Sleep(5000);

	printf ("Async print\n");

	WaitProcess(pi,30000);
	
	return 0;
}