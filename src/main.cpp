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
            if(!MyDisplay.insert_file())
            {
                printf("Error Insert File\n");
            }
            break;
        case 'd':
            if(!MyDisplay.delete_file())
            {
                printf("Error Delete File\n");
            }
            break;
        default:
            printf("No Such Commands, Input 'h' for help\n");
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
