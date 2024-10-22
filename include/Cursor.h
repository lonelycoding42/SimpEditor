#include<windows.h>

class Cursor
{
public:
    COORD pos_now;                                      //光标位置

    Cursor();                                        //初始化光标
    Cursor(COORD pos);                               //传入光标位置进行初始化
    bool Moveto(COORD pos,HANDLE myhandle);          //移动至指定位置
    COORD WhereIs();                                 //查询光标位置
};