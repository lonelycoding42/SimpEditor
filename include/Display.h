#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include"Cursor.h"
#include"data.h"

char takein();

class Display
{
public:
    int lines,cols;                                     //当前窗口尺寸
    char* doc_name;                                     //查看的文件名
    HANDLE myconsole;                                   //当前窗口的句柄

    // COORD cursor_pos;                                   //光标位置

    Display();                                          //初始化函数时获取窗口句柄并设置窗口尺寸
    bool view_file();                                   //查看文件内容
protected:
    Cursor mycursor;                                    //光标子类
    text_buffer mytext_buffer;                          //缓冲区子类
};