#include"../include/Cursor.h"

Cursor::Cursor()
{
    this->pos_now.X=0,this->pos_now.Y=0;
}

Cursor::Cursor(COORD pos)
{
    this->pos_now=pos;
}

bool Cursor::Moveto(COORD pos,HANDLE myhandle)
{
    bool sta=SetConsoleCursorPosition(myhandle,pos);
    if(sta)
    {
        this->pos_now=pos;
    }
    return sta;
}

COORD Cursor::WhereIs()
{
    return this->pos_now;
}