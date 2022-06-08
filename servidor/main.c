/*
Projeto integrado - Sistema de detecção de ocupação

Servidor que roda em background e escuta por pacotes que indiquem que o usuário faz 

*/

#include <windows.h>
#include <winuser.h>
#include <stdio.h>

/*#pragma comment( lib, "user32.lib" )*/


void main()
{
    // Lock the workstation.
    if( !LockWorkStation() ){
        fprintf (stderr, "LockWorkStation failed with %d\n", GetLastError());
    }
}