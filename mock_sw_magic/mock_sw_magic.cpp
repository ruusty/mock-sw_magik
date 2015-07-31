// mock_sw_magic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>  

using namespace std;




string getEnv(const char *varname)
{

	string rv;
	rv.empty();

   char *pValue;
   size_t len;
   errno_t err = _dupenv_s( &pValue, &len, varname );
   printf("getEnv (%s ==> %s)\n",varname,pValue); 
   if ( err == 0 )    rv = string(pValue);
   free( pValue );
   return rv;
}


int _tmain(int argc, _TCHAR* argv[])
{	
	USES_CONVERSION;
    LPTSTR lpszVariable; 
    LPTCH lpvEnv; 
 
	//--------------------------------------------------------------
	//_wdupenv_s
    //_dupenv_s
	 string JobName = getEnv("POSH_JobName");
	 string JobReportPath = getEnv("POSH_JobReportPath");
	 bool isRedirectedStdin = GetFileType(GetStdHandle(STD_INPUT_HANDLE)) != FILE_TYPE_CHAR;

	 cout << "isRedirectedStdin " << (isRedirectedStdin?"True":"False") << " JobName " << JobName << " JobReportPath " << JobReportPath << endl;
	 //--------------------------------------------------------------
	 if (isRedirectedStdin && JobReportPath.length() > 0) {
     	std::ofstream ofs (JobReportPath, std::ofstream::out);
		ofs << "isRedirectedStdin " << (isRedirectedStdin?"True":"False") << " JobName " << JobName << " JobReportPath " << JobReportPath << endl;
        string s;
	     while( !cin.eof() ) {
			getline(cin, s);
			ofs << s << endl;
		 }
		ofs.close();
	 }

	lpvEnv = GetEnvironmentStrings();

    // If the returned pointer is NULL, exit.
    if (lpvEnv == NULL)
    {
        printf("GetEnvironmentStrings failed (%d)\n", GetLastError()); 
        return 1;
    }
	// Variable strings are separated by NULL byte, and the block is 
    // terminated by a NULL byte. 

    lpszVariable = (LPTSTR) lpvEnv;
	typedef std::basic_string<TCHAR, std::char_traits<TCHAR>> tstring;
	if ( JobReportPath.length() > 0) {
		 std::ofstream ofs (JobReportPath, std::ofstream::out |std::ofstream::app);
		string s;

		while (*lpszVariable)
		{
			ofs << string(W2A(lpszVariable)) << endl;
			lpszVariable += lstrlen(lpszVariable) + 1;
		}
		FreeEnvironmentStrings(lpvEnv);

		ofs.close();
	 }


	 //-----------------------------------------------
    // Get a pointer to the environment block. 
 
    lpvEnv = GetEnvironmentStrings();


    // If the returned pointer is NULL, exit.
    if (lpvEnv == NULL)
    {
        printf("GetEnvironmentStrings failed (%d)\n", GetLastError()); 
        return 1;
    }
	// Variable strings are separated by NULL byte, and the block is 
    // terminated by a NULL byte. 

    lpszVariable = (LPTSTR) lpvEnv;
	typedef std::basic_string<TCHAR, std::char_traits<TCHAR>> tstring;

    while (*lpszVariable)
    {
        //_tprintf(TEXT("%s\n"), lpszVariable);
		cout << string(W2A(lpszVariable)) << endl;
        lpszVariable += lstrlen(lpszVariable) + 1;
    }
    FreeEnvironmentStrings(lpvEnv);


/*
	//--------------------------------------------------------------
	#define BUFSIZE 4096
    #define VARNAME TEXT("TNS_ADMIN")
	DWORD dwRet, dwErr;
	LPTSTR pszOldVal; 
	BOOL fExist; 
	pszOldVal = (LPTSTR) malloc(BUFSIZE*sizeof(TCHAR));
    if(NULL == pszOldVal)
    {
        printf("Out of memory\n");
        return FALSE;
    }

	dwRet = GetEnvironmentVariable(VARNAME, pszOldVal, BUFSIZE);
	if(0 == dwRet)
    {
        dwErr = GetLastError();
        if( ERROR_ENVVAR_NOT_FOUND == dwErr )
        {
            printf("Environment variable does not exist.\n");
            fExist=FALSE;
        }
    }
    else if(BUFSIZE < dwRet)
    {
        pszOldVal = (LPTSTR) realloc(pszOldVal, dwRet*sizeof(TCHAR));   
        if(NULL == pszOldVal)
        {
            printf("Out of memory\n");
            return FALSE;
        }
        dwRet = GetEnvironmentVariable(VARNAME, pszOldVal, dwRet);
        if(!dwRet)
        {
            printf("GetEnvironmentVariable failed (%d)\n", GetLastError());
            return FALSE;
        }
        else fExist=TRUE;
    }
    else fExist=TRUE;
	if (fExist == TRUE )
	{
		_tprintf(TEXT("%s=%s\n"), VARNAME, pszOldVal);
		//cout << pszOldVal <<endl;
	}
	typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstring;

	tstring wstr=tstring(pszOldVal);
	wcout << VARNAME <<L" value:" << wstr << endl;
*/

   //--------------------------------------------------------------
   LPWSTR *szArglist;
   int nArgs;
   int i;

   szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
   if( NULL == szArglist )
   {
      wprintf(L"CommandLineToArgvW failed\n");
      return 1;
   }
   else for( i=0; i<nArgs; i++) printf("%d: %ws\n", i, szArglist[i]);

// Free memory allocated for CommandLineToArgvW arguments.
   LocalFree(szArglist);

  

   return 0;
}

