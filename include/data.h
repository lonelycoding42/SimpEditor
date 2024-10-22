#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string>

//每行语句的最长长度
#define SEN_LEN 400 

#define SAVE 0
#define SAVE_AS 1

//用于存储句子的双向链表
struct SL_list{
    SL_list* ahead;  //前向指针
    char* sentense;  //文件语句 
    int sen_len;     //句长
    SL_list* after;  //后向指针
    // static int node_num; //链节数
};

//插入一个链节
int insert(SL_list* ahead_node, SL_list* after_node, char* sentence);
//在末尾添加一个链节
int append(SL_list* ahead_node, char* sentense);

struct pos{
    SL_list* line;
    int* char_pos;
};


//读取修改写入文件和修改缓存区操作
class text_buffer{
public:
    int line;//行数
    int char_num;//字符数
    SL_list* top_sentense; //第一行语句
    SL_list* end_sentense; //最后一行语句

    //构造函数
    text_buffer();
    //析构函数 
    ~text_buffer();
    //读取文件函数
    SL_list* load_file(char* file_name);
    //file_name 要打开的文件名
    //将文本内容以链表形式载入，一行为一个链表
    //返回end_sentence 即最后一行语句
    
    //写入文件函数
    int save_file(char* file_name, int mode);
    //查找短语函数
    pos seek_phrase(char* phrase, SL_list* node);
    //替换短语函数
    bool rpls_phrase(char* r_phrase,  //替换的短语
                     char* rd_phrase, //被替换的短语
                     SL_list* node,
                     int char_pos
                     );

};

