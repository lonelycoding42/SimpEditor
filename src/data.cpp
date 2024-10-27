#include "../include/data.h"

// SL_list::SL_list(char* sentence){
//     this->ahead = NULL;
//     this->after = NULL;
//     strcpy(this->sentense, sentence);
// }

list_node* ask_for_node(char* sentence){
    list_node* new_node = (list_node*)malloc(sizeof(list_node));
    if (new_node == nullptr)
    {
        perror("malloc error\n");
        exit(-1);
    }

    strcpy(new_node->sentence, sentence);
    new_node->after = nullptr;
    new_node->ahead = nullptr;
    return new_node;
}

void node_append(list_node** top_node, char* sentence){
    list_node* new_node = ask_for_node(sentence);
    if (*top_node==nullptr)
        *top_node = new_node;
    
    else{
        list_node* cur = *top_node;
        while (cur->after)
            cur = cur->after;
        cur->after = new_node;
        new_node->ahead = cur;
    }
    return;
}

void endnode_delete(list_node** top_node){
    if (top_node==nullptr||*top_node==nullptr) return;

    if((*top_node)->after==nullptr){
        free(*top_node);
        *top_node = nullptr;
        return;
    }
    
    list_node* cur = *top_node;
    list_node* nxt = (*top_node)->after;
    while (nxt->after!=nullptr)
    {
        nxt = nxt->after;
        cur = nxt;
    }
    
    cur->after = nullptr;
    free(nxt);
    nxt = nullptr;
    return;
}

//指定节点后面加入一个节点
void insert_node_after(list_node** top_node, list_node* pos, char* sentence){
    list_node* new_node = ask_for_node(sentence);
    if(pos->after == nullptr){
        pos->after = new_node;
        new_node->ahead = pos;
        return;
    }
    pos->after->ahead = new_node;
    new_node->after = pos->after;
    
    pos->after = new_node;
    new_node->ahead = pos;

    return;
}

//在指定节点之前插入一个节点
void insert_node_before(list_node** top_node, list_node* pos, char* sentence){
    list_node* new_node = ask_for_node(sentence);
    if (*top_node == pos)
    {
        pos->ahead = new_node;
        new_node->after = pos;
    }else{
        pos->ahead->after = new_node;
        new_node->ahead = pos->ahead;

        pos->ahead = new_node;
        new_node->after = pos;
    }
    return;
}

//删除指定节点
void delete_node(list_node** top_node, list_node* pos){
    //如果删除头节点
    if(*top_node == pos){
        *top_node = (*top_node)->after;
        (*top_node)->ahead = nullptr;
        free(pos);
        pos = nullptr;
    }else{
        pos->ahead->after = pos->after;
        if(pos->after!=nullptr)
            pos->after->ahead = pos->ahead;
        
        free(pos);
        pos = nullptr;
    }
}

//销毁链表
void distory_list(list_node** top_node){
    while (top_node)
    {   
        list_node* nxt = (*top_node)->after;
        free(*top_node);
        *top_node = nxt;
    }
    return;
}

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
    *top_node = nullptr;
    // *bottom_node = *top_node;
}

text_buffer::~text_buffer(){
    distory_list(top_node);
    printf("kill text_buffer\n");
    return;
}

void text_buffer::load_file(char* file_name){
    //这里开销有点大，想想怎么优化
    FILE* fp = fopen(file_name, "r");
    // list_node** cur = top_node;
    char buf[SEN_LEN];
    while (fgets(buf, SEN_LEN, fp)){
        
        // printf("%s", buf);
        node_append(top_node, buf);
        // *cur = (*cur)->after;
        line++;
        char_num+=strlen(buf);
    }
        
    // *bottom_node = (*cur);
    return;
}


int text_buffer::save_file(char* file_name, int mode){
    FILE* file = fopen(file_name, "w");
    list_node** node = top_node;
    while (node!=nullptr)
    {   
        // printf("%s", (*node)->sentence);
        fwrite((*node)->sentence, sizeof((*node)->sentence), 1, file);
        *node = (*node)->after;
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
    printf("%s\n", cur);
    int sz1 = strlen(text), sz2 = strlen(pattern);
    int* v;
    int* vp = v;
    int* lps = prefix_function(cur);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++){
        if (lps[i] == sz2){
            printf("%d\n", i-2*sz2);
            *(v++) = i-2*sz2;     
        } 
    }
    *v = 0;
    return vp;
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
    // pos mypos = seek_phrase(rd_phrase, node);
    char* temp;
    strncpy(temp, node->sentense, char_pos-1);
    sprintf(temp, "%d%d%d", temp, r_phrase, 
            node->sentense+char_pos+strlen(rd_phrase));
    strcpy(node->sentense, temp);
    return true;
}