#include"../include/Cursor.h"

bool Cursor::Moveto(COORD pos,HANDLE myhandle)
{
    bool sta=SetConsoleCursorPosition(myhandle,pos);
    return sta;
}