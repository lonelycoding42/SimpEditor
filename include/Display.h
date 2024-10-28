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
    bool insert_file();                                 //插入文件内容
    bool delete_file();                                 //删除文件内容
    bool find_file();                                   //查找文件内容
    bool save_file();                                   //保存文件
    bool resave_file();                                 //文件另存为
    bool reload();                                      //重新读入
    void show_data();                                   //统计
    bool replace_line();                                //替换行
    bool replace_string();                              //替换字符串

protected:
    Cursor mycursor;                                    //光标子类
    text_buffer mytext_buffer;                          //缓冲区子类
};