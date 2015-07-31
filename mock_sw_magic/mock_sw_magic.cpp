// mock_sw_magic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>  
using namespace std;
#define BUFSIZE 4096
#define VARNAME TEXT("TNS_ADMIN")

int _tmain(int argc, _TCHAR* argv[])
{
    LPTSTR lpszVariable; 
    LPTCH lpvEnv; 
 
	//--------------------------------------------------------------

    // Get a pointer to the environment block. 
 
    lpvEnv = GetEnvironmentStrings();

    // If the returned pointer is NULL, exit.
    if (lpvEnv == NULL)
    {
        printf("GetEnvironmentStrings failed (%d)\n", GetLastError()); 
        return 0;
    }
	 // Variable strings are separated by NULL byte, and the block is 
    // terminated by a NULL byte. 

    lpszVariable = (LPTSTR) lpvEnv;

    while (*lpszVariable)
    {
        _tprintf(TEXT("%s\n"), lpszVariable);
        lpszVariable += lstrlen(lpszVariable) + 1;
    }
    FreeEnvironmentStrings(lpvEnv);



	//--------------------------------------------------------------
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
	wcout << L"Retried value:" << wstr << endl;


	//--------------------------------------------------------------
	//Check if input from file redirection
	HANDLE hStdin; 
	// Get the standard input handle. 
	//https://msdn.microsoft.com/en-us/library/windows/desktop/ms685035%28v=vs.85%29.aspx
 
    hStdin = GetStdHandle(STD_INPUT_HANDLE); 
	DWORD fdwSaveOldMode;
	GetConsoleMode(hStdin, &fdwSaveOldMode); 
	cout << "fdwSaveOldMode:" << fdwSaveOldMode << endl;
	cout << "fdwSaveOldMode & ENABLE_LINE_INPUT:" << (fdwSaveOldMode & ENABLE_LINE_INPUT ) << endl;
		
	if ((fdwSaveOldMode & ENABLE_LINE_INPUT ) == 0)
	{
	  string s;
	  while( !cin.eof() ) {
         getline(cin, s);
		 cout << s << endl;
     }
	}

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

  
   //--------------------------------------------------------------

	std::ofstream ofs ("D:\\Data.DEV\\GIS-VegetationSpanReport\\VEGETATION_SPANS_REPORT.txt", std::ofstream::out);
	ofs << "lorem ipsum";
	ofs.close();
   return 0;
}

