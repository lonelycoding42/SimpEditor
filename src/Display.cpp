#include"../include/Display.h"

Display::Display()
{
    //更改窗口标题并获取窗口句柄
    SetConsoleTitleW(L"SimpEditor");
    this->myconsole=GetStdHandle(STD_OUTPUT_HANDLE);
    
    //获取窗口大小
    //因为没有搞懂新版控制台如何更改大小，而旧控制台虽然可以更改大小，但是又神必的不能使用ANSI码控制，遂放弃更改大小
    CONSOLE_SCREEN_BUFFER_INFO tmp;
	GetConsoleScreenBufferInfo(this->myconsole,&tmp);
    this->cols=tmp.dwSize.X;
    this->lines=tmp.dwSize.Y;

    //要求输入文件名
    /**
     * 图形化界面的需求，目前不需要
     * cursor_pos.X=(cols-25)/2;
     * cursor_pos.Y=(lines-3)/2;
     * mycursor.Moveto(cursor_pos,this->myconsole);
    **/
//    while(1)
//    {
        cursor_pos.X=(cols-25)/2;
        cursor_pos.Y=(lines-3)/2;
        mycursor.Moveto(cursor_pos,this->myconsole);
        printf("Please Input File's Name:");
        int n=0,maxx=100;
        char ch=getchar();
        doc_name=new char[100];
        while(ch!='\n')
        {
            if(n+1>=maxx)
            {
                maxx*=2;
                char* tmp_doc_name=doc_name;
                doc_name=new char[maxx];
                strcpy(doc_name,tmp_doc_name);
                delete [] tmp_doc_name;
            }
            doc_name[n]=ch;
            n++;
            ch=getchar();
        }
        n--;
        if(!n)
        {
            printf("Input Nothing!\n");
            // continue;
        }
        SetConsoleTitle(doc_name);
        // break;
//    }

    printf("%s",doc_name);

    /**
     * 图形化Bash界面
     * //设置窗口大小
     * COORD newBuffersize={51,21};
     * SMALL_RECT newWindowSize={0,0,50,20};
     * SetConsoleWindowInfo(this->myconsole,TRUE,&newWindowSize);
     * SetConsoleScreenBufferSize(this->myconsole,newBuffersize);
     * //选择窗口大小
     * this->cursor_pos={10,6};
     * mycursor.Moveto(this->cursor_pos,this->myconsole);
     * printf("Please choose the window size");
     * this->cursor_pos={16,8};
     * mycursor.Moveto(this->cursor_pos,this->myconsole);
     * printf("20*80     30*120");
     * this->cursor_pos={16,10};
     * mycursor.Moveto(this->cursor_pos,this->myconsole);
     * printf("40*160    50*200");
     * system("pause");
     * newBuffersize={21,11};
     * newWindowSize={20,10};
     * SetConsoleWindowInfo(this->myconsole,TRUE,&newWindowSize);
     * SetConsoleScreenBufferSize(this->myconsole,newBuffersize);
    **/
}