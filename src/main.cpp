#include "../include/Display.h"

/**
 * 该版本SimpEditor为未完成版，只能实现基础功能，带Bash图形化的版本在没有ddl的日子再写
**/

int main()
{
    Display MyDisplay;
    char ch=takein();
    while(ch!='q')
    {
        switch (ch)
        {
        //展示当前文件内容
        case 'v':
            if(!MyDisplay.view_file())
            {
                printf("Error View File\n");
            }
            break;
        //插入某一行
        case 'i':
            while(ch!='\n')
            {
                ch=takein();
            }
            if(!MyDisplay.insert_file())
            {
                printf("Error Insert File\n");
            }
            else
            {
                printf("Succese Insert\n");
            }
            break;
        //删除某一行
        case 'd':
            if(!MyDisplay.delete_file())
            {
                printf("Error Delete File\n");
            }
            else
            {
                printf("Succese Delete\n");
            }
            break;
        //查找相关短语
        case 'f':
            while(ch!='\n')
            {
                ch=takein();
            }
            if(!MyDisplay.find_file())
            {
                printf("Error Find File\n");
            }
            break;
        //保存文件
        case 's':
            if(!MyDisplay.save_file())
            {
                printf("Error Save File\n");
            }
            else
            {
                printf("Succese Save File\n");
            }
            break;
        //另存为
        case 'a':
            while(ch!='\n')
            {
                ch=takein();
            }
            if(!MyDisplay.resave_file())
            {
                printf("Error Resave File\n");
            }
            else
            {
                printf("Succese Resave File\n");
            }
            break;
        //重新读入
        case 'c':
            while(ch!='\n')
            {
                ch=takein();
            }
            if(!MyDisplay.reload())
            {
                printf("Error Reload File\n");
            }
            else
            {
                printf("Succese Reload File\n");
            }
            break;
        //统计
        case 'm':
            MyDisplay.show_data();
            break;
        //帮助
        case 'h':
            MyDisplay.help();
            break;
        //替换
        case 'r':
            ch=takein();
            if(ch=='l')
            {
                while(ch!='\n')
                {
                    ch=takein();
                }
                if(!MyDisplay.replace_line())
                {
                    printf("Error Replace Line\n");
                }
                printf("Succese Rplace\n");
                break;
            }
            else if(ch=='s')
            {
                while(ch!='\n')
                {
                    ch=takein();
                }
                if(!MyDisplay.replace_string())
                {
                    printf("Error Replace String\n");
                }
                printf("Succese Rplace\n");
                break;
            }
        //非法命令
        default:
            printf("No Such Command, Input 'h' for help\n");
            break;
        }
        while(ch!='\n')
        {
            ch=takein();
        }
        printf("> ");
        ch=takein();
    }
    system("pause");
}
