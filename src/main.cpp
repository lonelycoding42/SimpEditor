#include "../include/Display.h"
#include "../include/data.h"
// #include "../include/Cursor.h"

int main( )
{
    char test1[100] = "abcdabcd";
    char test2[100] = "ab";
    printf("%s\n%s\n\n", test1, test2);

    text_buffer myTEXT;
    myTEXT.load_file("test.txt");
    // int* arr = find_occurrences(test1, test2);
    // for (int i = 0; i < 2; i++)
    // {
    //     printf("%d\n", arr[i]);
    // }
    
}
