#include "../include/Display.h"

/**
 * 该版本SimpEditor为未完成版，只能实现基础功能，带Bash图形化的版本在没有ddl的日子再写
**/

int main()
{
    char test1[100] = "abcdabcd\r\n";
    char test2[100] = "ab";
    // printf("%s\n%s\n\n", test1, test2);

    // text_buffer myTEXT;
    int_array my_arr =  prefix_function(test1);
    for (int i = 0; i < my_arr.array_len; i++)
    {
        printf("%d ", my_arr.array[i]);
    }
    
    // myTEXT.load_file("test");
    // myTEXT.save_file("test");

    // int* arr = find_occurrences(test1, test2);
    // for (int i = 0; i < 2; i++)
    // {
    //     printf("%d\n", arr[i]);
    // }
    
}
