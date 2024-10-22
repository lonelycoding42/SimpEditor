#include "../include/data.h"

// SL_list::SL_list(char* sentence){
//     this->ahead = NULL;
//     this->after = NULL;
//     strcpy(this->sentense, sentence);
// }

int insert(SL_list* ahead_node, SL_list* after_node, char* sentence){
    SL_list* app_node = (SL_list*)malloc(sizeof(SL_list));
    app_node->ahead = ahead_node;
    ahead_node->after = app_node;

    app_node->after = after_node;
    after_node->ahead = app_node;

    strcpy(app_node->sentense, sentence);    
    return 0;
}

int append(SL_list* a_node, char* sentense){

    //确保是在尾部添加
    SL_list* ahead_node = a_node;
    while (a_node->after!=nullptr) a_node = a_node->after;

    SL_list* app_node = (SL_list*)malloc(sizeof(SL_list));
    app_node->ahead = ahead_node;
    ahead_node->after = app_node;

    app_node->after = nullptr;
    return 0;
}

int remove(SL_list* rm_node){
    //确保链节是最后一个
    SL_list* node = rm_node;
    while (node->after!=nullptr) node = node->after;

    node->ahead->after = nullptr;
    return 0;
}

text_buffer::text_buffer(){
    line = 0;
    char_num = 0;
}

SL_list* text_buffer::load_file(char* file_name){
    FILE* file = fopen(file_name, "r");
    SL_list* node = top_sentense;
    while (fgets(node->sentense, SEN_LEN, file))
    {
        line++;
        char_num+=strlen(node->sentense);
        
        SL_list* nx_node = (SL_list*)malloc(sizeof(SL_list));
        nx_node->ahead = node;
        node->after = nx_node;
        node = nx_node;
    }

    end_sentense = node;
    fclose(file);
    return node;
}

int text_buffer::save_file(char* file_name, int mode){
    FILE* file = fopen(file_name, "w");
    SL_list* node = top_sentense;
    while (node!=nullptr)
    {
        fwrite(node->sentense, sizeof(node->sentense), 1, file);
        node = node->after;
    }
    fclose(file);

    return 0;
}

//生成前缀函数
int* prefix_function(char* s) {
    int n = (int)strlen(s);
    int  pi[n];
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

//KMP算法
int* find_occurrences(char* text, char* pattern) {
    char* cur;
    sprintf(cur, "%s%s%s", pattern, '#', text);
    int sz1 = strlen(text), sz2 = strlen(pattern);
    int* v;
    int* lps = prefix_function(cur);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++) 
        if (lps[i] == sz2) *(v++) = i-2*sz2;   
    
    *v = 0;
    return v;
}

pos text_buffer::seek_phrase(char* phrase, SL_list* node){
    // SL_list* node = top_sentense;
    // pos pos_array;
    // for (int i = 0; i<line; i++)
    // {
    //     pos_array[i].line = node;
    //     pos_array[i].char_pos = find_occurrences(node->sentense, phrase);
    //     node = node->after;
    // }
    // return pos_array;
    pos pos_info;
    pos_info.line = node;
    pos_info.char_pos = find_occurrences(node->sentense, phrase);
    return pos_info;
}

bool text_buffer::rpls_phrase(char* r_phrase, char* rd_phrase, SL_list* node, int char_pos){
    pos mypos = seek_phrase(rd_phrase, node);
    char* temp;
    strncpy(temp, node->sentense, char_pos-1);
    sprintf(temp, "%d%d%d", temp, r_phrase, node->sentense+char_pos+strlen(rd_phrase));
    // SL_list* node = top_sentense;
    // pos* pos_array;
    // char* temp;
    // for (int i = 0; i<line; i++)
    // {
    //     pos_array[i].line = node;
    //     pos_array[i].char_pos = find_occurrences(node->sentense, rd_phrase);
        

    //     node = node->after;
    // }
    
    // return pos_array;
}