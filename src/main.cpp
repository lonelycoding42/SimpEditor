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
            
            break;
        
        default:
            break;
        }
    }
    system("pause");
}
