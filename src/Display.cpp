#include"../include/Display.h"

char takein()
{
    char ch=getchar();
    if(ch>='A'&&ch<='Z')
    {
        ch=ch-'A'+'a';
    }
    return ch;
}

Display::Display()
{
    //更改窗口标题并获取窗口句柄
    SetConsoleTitleW(L"SimpEditor");
    this->myconsole=GetStdHandle(STD_OUTPUT_HANDLE);
    
    //获取窗口大小
    //因为没有搞懂新版控制台如何更改大小，而旧控制台虽然可以更改大小，但是又神必的不能使用ANSI码控制，遂放弃更改大小
    // CONSOLE_SCREEN_BUFFER_INFO tmp;
	// GetConsoleScreenBufferInfo(this->myconsole,&tmp);
    // this->cols=tmp.dwSize.X;
    // this->lines=tmp.dwSize.Y;

    //要求输入文件名
    /**
     * 图形化界面的需求，目前不需要
     * cursor_pos.X=(cols-25)/2;
     * cursor_pos.Y=(lines-3)/2;
     * mycursor.Moveto(cursor_pos,this->myconsole);
    **/
    doc_name=new char[SEN_LEN];
    memset(doc_name,0,SEN_LEN*sizeof(char));
    while(1)
    {
        //出于相同的理由被注释
        // cursor_pos.X=(cols-25)/2;
        // cursor_pos.Y=(lines-3)/2;
        // mycursor.Moveto(cursor_pos,this->myconsole);
        
        //输入文件名
        printf("Please Input File's Name: ");
        int n=0,maxx=SEN_LEN;
        char ch=getchar();
        while(ch!='\n')
        {
            if(n+1>=maxx)
            {
                maxx*=2;
                char* tmp_doc_name=doc_name;
                doc_name=new char[maxx];
                memset(doc_name,0,SEN_LEN*sizeof(char));
                strcpy(doc_name,tmp_doc_name);
                delete [] tmp_doc_name;
            }
            doc_name[n]=ch;
            n++;
            ch=getchar();
        }
        n--;
        if(n<0)
        {
            printf("Input Nothing!\n");
            continue;
        }
        //将标题设置为文件名
        SetConsoleTitle(doc_name);
        //读取文件
        if(!mytext_buffer.load_file(doc_name))
        {
            printf("Error Open File\n");
            memset(doc_name,0,SEN_LEN*sizeof(char));
            continue;
        }
        break;
    }
    printf("> ");
    //测试功能端口
    // printf("%s",doc_name);

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

bool Display::view_file()
{
    list_node* myLine=(*mytext_buffer.top_node);
    // printf("%d\n",mytext_buffer.line);
    for(int i=1;i<=mytext_buffer.line;i++)
    {
        if(myLine==NULL) break;
        printf("%s",myLine->sentence);
        myLine=myLine->after;
    }
    return TRUE;
}

bool Display::insert_file()
{
    int line=0;
    //得到插入的行数(在某行之后插入)
    while(1)
    {
        printf("After Which Line To Insert(0 to insert before the first line): ");
        if(!scanf("%d",&line)||line>mytext_buffer.line||line<0)
        {
            while(getchar()!='\n');
            printf("Invalid Line Number\n");
            line=0;
            continue;
        }
        printf("Content To Insert: \n");
        break;
    }
    //获取要插入的内容
    int n=0,c=0;
    char* insert_inf=new char[SEN_LEN];
    memset(insert_inf,0,SEN_LEN*sizeof(char));
    char ch=getchar();
    while(ch=='\n')
    {
        c++;
        if(c==2)
        {
            insert_inf[0]='\n';
            goto Next_Move;
        }
        ch=getchar();
    }
    insert_inf[n++]=ch;
    while(ch!='\n')
    {
        ch=getchar();
        insert_inf[n++]=ch;
    }
    Next_Move:
    list_node* Mynode=(*mytext_buffer.top_node);
    for(int i=1;i<line;i++)
    {
        Mynode=Mynode->after;
    }
    //插入至缓冲区文本中
    if(!line)
    {
        (*mytext_buffer.top_node)=insert_node_before(mytext_buffer.top_node,Mynode,insert_inf);
    }
    else insert_node_after(mytext_buffer.top_node,Mynode,insert_inf);
    mytext_buffer.line++;
    mytext_buffer.char_num+=strlen(insert_inf);
    delete [] insert_inf;
    return TRUE;
}

bool Display::delete_file()
{
    while(1)
    {
        printf("Which Line To Delete: ");
        int line=0;
        if(!scanf("%d",&line)||line>mytext_buffer.line||line<0)
        {
            while(getchar()!='\n');
            printf("Invalid Line Number\n");
            line=0;
            continue;
        }
        list_node* Myline=(*mytext_buffer.top_node);
        for(int i=1;i<line;i++)
        {
            Myline=Myline->after;
        } 
        mytext_buffer.line--;
        mytext_buffer.char_num-=strlen(Myline->sentence);
        (*mytext_buffer.top_node)=delete_node(mytext_buffer.top_node,Myline);
        break;
    }
    return TRUE;
}

bool Display::find_file()
{
    while(1)
    {
        printf("Inuput Phrase To Find: ");
        char* find_inf=new char[SEN_LEN];
        fgets(find_inf,SEN_LEN,stdin);
        find_inf[strlen(find_inf)-1]=0;
        list_node* myLine=(*mytext_buffer.top_node);
        while(myLine!=NULL)
        {
            int_array myArray=mytext_buffer.seek_phrase(find_inf,myLine);
            int c=0;
            for(int i=0;i<strlen(myLine->sentence);i++)
            {
                if(!myArray.array_len) break;
                if(i>=myArray.array[c])
                {
                    printf("\x1b[0;7m");
                }
                if(i>myArray.array[c]+strlen(find_inf)-1)
                {
                    printf("\x1b[7;0m");
                    if(c<myArray.array_len)
                    {
                        c++;
                    }
                }
                printf("%c",myLine->sentence[i]);
            }
            printf("\x1b[7;0m");
            myLine=myLine->after;
        }
        break;
    }
    return TRUE;
}

bool Display::save_file()
{
    if(!mytext_buffer.save_file(doc_name))
    {
        return FALSE;
    }
    return TRUE;
}

bool Display::resave_file()
{
    char* resave_name=new char[SEN_LEN];
    memset(resave_name,0,SEN_LEN*sizeof(char));
    while(1)
    {
        //输入文件名
        printf("Please Input File's Name: ");
        int n=0,maxx=SEN_LEN;
        char ch=getchar();
        while(ch!='\n')
        {
            if(n+1>=maxx)
            {
                maxx*=2;
                char* tmp_doc_name=resave_name;
                resave_name=new char[maxx];
                memset(resave_name,0,SEN_LEN*sizeof(char));
                strcpy(resave_name,tmp_doc_name);
                delete [] tmp_doc_name;
            }
            resave_name[n]=ch;
            n++;
            ch=getchar();
        }
        n--;
        if(n<0)
        {
            printf("Input Nothing!\n");
            continue;
        }
        //保存文件
        if(!mytext_buffer.save_file(resave_name))
        {
            delete [] resave_name;
            return FALSE;
        }
        delete [] resave_name;
        return TRUE;
    }
}

bool Display::reload()
{
    memset(doc_name,0,SEN_LEN*sizeof(char));
    while(1)
    {
        //输入文件名
        printf("Please Input File's Name: ");
        int n=0,maxx=SEN_LEN;
        char ch=getchar();
        while(ch!='\n')
        {
            if(n+1>=maxx)
            {
                maxx*=2;
                char* tmp_doc_name=doc_name;
                doc_name=new char[maxx];
                memset(doc_name,0,SEN_LEN*sizeof(char));
                strcpy(doc_name,tmp_doc_name);
                delete [] tmp_doc_name;
            }
            doc_name[n]=ch;
            n++;
            ch=getchar();
        }
        n--;
        if(n<0)
        {
            printf("Input Nothing!\n");
            continue;
        }
        //将标题设置为文件名
        SetConsoleTitle(doc_name);
        //销毁旧链表并读取文件
        mytext_buffer.line=0; mytext_buffer.char_num=0;
        distory_list(mytext_buffer.top_node);
        if(!mytext_buffer.load_file(doc_name))
        {
            printf("Error Open File\n");
            memset(doc_name,0,SEN_LEN*sizeof(char));
            continue;
        }
        break;
    }
    return TRUE;
}

void Display::show_data()
{
    printf("Line: %d\n",mytext_buffer.line);
    printf("Character: %d\n",mytext_buffer.char_num);
}

bool Display::replace_line()
{
    int line=0;
    //得到替换的行数
    while(1)
    {
        printf("Which Line To Repalce: ");
        if(!scanf("%d",&line)||line>mytext_buffer.line||line<0)
        {
            while(getchar()!='\n');
            printf("Invalid Line Number\n");
            line=0;
            continue;
        }
        printf("Content To Replace: \n");
        break;
    }
    //获取要替换的内容
    int n=0,c=0;
    char* replace_inf=new char[SEN_LEN];
    memset(replace_inf,0,SEN_LEN*sizeof(char));
    char ch=getchar();
    while(ch=='\n')
    {
        c++;
        if(c==2)
        {
            replace_inf[0]='\n';
            goto Next_Move;
        }
        ch=getchar();
    }
    replace_inf[n++]=ch;
    while(ch!='\n')
    {
        ch=getchar();
        replace_inf[n++]=ch;
    }
    Next_Move:
    list_node* Mynode=(*mytext_buffer.top_node);
    for(int i=1;i<line;i++)
    {
        Mynode=Mynode->after;
    }
    //替换至缓冲区文本中
    mytext_buffer.char_num+=strlen(replace_inf)-strlen(Mynode->sentence);
    mytext_buffer.rpls_phrase(replace_inf,Mynode->sentence,Mynode);
    delete [] replace_inf;
    return TRUE;
}

bool Display::replace_string()
{
    //获取要被替换的内容
    printf("Content To Be replaced: ");
    int n=0,c=0;
    char* replaced_inf=new char[SEN_LEN];
    memset(replaced_inf,0,SEN_LEN*sizeof(char));
    char ch=getchar();
    while(ch=='\n')
    {
        c++;
        if(c==2)
        {
            replaced_inf[0]='\n';
            goto Next_Move_0;
        }
        ch=getchar();
    }
    replaced_inf[n++]=ch;
    while(ch!='\n')
    {
        ch=getchar();
        replaced_inf[n++]=ch;
    }
    // printf("%s",replaced_inf);
    Next_Move_0:
    replaced_inf[--n]=0;
    //获取替换为的内容
    printf("Content To replace: ");
    n=0,c=0;
    char* replace_inf=new char[SEN_LEN];
    memset(replace_inf,0,SEN_LEN*sizeof(char));
    ch=getchar();
    while(ch=='\n')
    {
        c++;
        if(c==2)
        {
            replace_inf[0]='\n';
            goto Next_Move_1;
        }
        ch=getchar();
    }
    replace_inf[n++]=ch;
    while(ch!='\n')
    {
        ch=getchar();
        replace_inf[n++]=ch;
    }
    // printf("%s",replace_inf);
    Next_Move_1:
    replace_inf[--n]=0;
    //替换至缓冲区文本中
    list_node* Mynode=(*mytext_buffer.top_node);
    for(int i=1;i<=mytext_buffer.line;i++)
    {
        int_array myArray=mytext_buffer.seek_phrase(replaced_inf,Mynode);
        mytext_buffer.char_num+=myArray.array_len*(strlen(replace_inf)-strlen(replaced_inf));
        mytext_buffer.rpls_phrase(replace_inf,replaced_inf,Mynode);
        Mynode=Mynode->after;
    }
    delete [] replaced_inf;
    delete [] replace_inf;
    return TRUE;
}

void Display::help()
{
printf("h  - Help\n");
printf("v  - View file contents\n");
printf("i  - Insert a new line after the current line\n");
printf("d  - Delete a specified line\n");
printf("f  - Find a specified phrase\n");
printf("rl - Replace a specified line\n");
printf("rs - Replace a specified phrase\n");
printf("m  - Display statistics (number of lines and characters)\n");
printf("s  - Save file\n");
printf("a  - Save file as\n");
printf("c  - Reload a new file\n");
printf("q  - Quit SimpEditor\n");
}
