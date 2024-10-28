#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>


#ifndef _TEST_H_
#define _TEST_H_

//每行语句的最长长度
#define SEN_LEN 400 

#define ERROR 0

struct list_node
{
    list_node* ahead;
    char sentence[SEN_LEN];
    list_node* after;
};

//创建链表节点
list_node* ask_for_node(char* sentence);

//在链表尾部添加一个节点
void node_append(list_node** top_node, char* sentence);

//删除链表尾部的节点
void endnode_delete(list_node** top_node);

//在指定节点之后插入一个节点
void insert_node_after(list_node** top_node, list_node* pos, char* sentence);

//在指定节点之前插入一个节点
list_node* insert_node_before(list_node** top_node, list_node* pos, char* sentence);

//删除一个指定的节点
list_node* delete_node(list_node** top_node, list_node* pos);

//销毁链表
void distory_list(list_node** top_node);

typedef struct int_array
{
    int array_len;
    int array[SEN_LEN];
}int_array;

//生成前缀函数
int_array prefix_function(char* s);

//KMP算法
int_array find_occurrences(char* text, char* pattern);

//读取修改写入文件和修改缓存区操作
class text_buffer{
public:
    int line;//行数
    int char_num;//字符数
    list_node** top_node;

    // SL_list* top_sentense; //第一行语句
    // SL_list* end_sentense; //最后一行语句

    //构造函数
    text_buffer();
    //析构函数 
    ~text_buffer();
    //读取文件函数
    int load_file(char* file_name);
    //file_name 要打开的文件名
    //将文本内容以链表形式载入，一行为一个链表
    //返回end_sentence 即最后一行语句

    
    //写入文件函数
    int save_file(char* file_name);


    //查找短语函数
    int_array seek_phrase(char* phrase, list_node* node);
    
    //替换短语函数
    bool rpls_phrase(char* r_phrase,  //替换的短语
                     char* rd_phrase, //被替换的短语
                     list_node* node
                     );

};

#endif