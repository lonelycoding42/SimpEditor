#include"../include/Display.h"

Display::Display(LPCWSTR title)
{
    //更改窗口标题并获取窗口句柄
    SetConsoleTitleW(title);
    this->myconsole=GetStdHandle(STD_OUTPUT_HANDLE);
    
    //选择窗口大小
    COORD newBuffersize={51,21};
    SMALL_RECT newWindowSize={0,0,50,20};
    SetConsoleWindowInfo(this->myconsole,TRUE,&newWindowSize);
    SetConsoleScreenBufferSize(this->myconsole,newBuffersize);
    COORD pos_set={3,};
    // mycursor.Moveto();
    printf("Please choose the window size\n");
    
}