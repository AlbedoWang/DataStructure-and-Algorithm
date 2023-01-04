//
//  main.cpp
//  DSA_3
//
//  Created by 健 on 2022/10/28.
//
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;
const int MaxSize = 10000;
typedef struct wordcnt
{
    char ch;
    int cnt=0;
}Count;

typedef struct NumCount
{
    Count count[MaxSize];
    int length=0;
}NumCount;

typedef struct HTree
{
    char data;
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef struct HCode
{
    char data;
    char* str;
}*HuffmanCode;

void ReadData(char *source);  // 读入文件
void WordCount(char *data,NumCount *paraCnt); // 统计次数
void Show(NumCount *paraCnt);   // 展示次数
void CreateHuffmanTree(HuffmanTree &HT,int length,NumCount cntarray);  // 创建哈夫曼树
void select(HuffmanTree HT,int top,int *s1,int *s2);  // 选择权重最小的两个节点
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int length);  // 创建哈夫曼编码
void Encode(char *data,HuffmanCode HC,int length);  // 将读入的文件编码，写到txt文件
void Decode(HuffmanTree HT,int length);  //读入编码文件，解码

void ReadData(string &str){
    ifstream file;
    file.open("stdio.h", ios_base::in);
    if(!file.is_open())
        cout<<"FAIL"<<endl;
    else cout<<"OK"<<endl;
    stringstream s;
    s<<file.rdbuf();
    str = s.str();
    file.close();
}

void ReadCode(string &str){
    ifstream file;
    file.open("Encode.txt", ios_base::in);
    if(!file.is_open())
        cout<<"FAIL"<<endl;
    else cout<<"OK"<<endl;
    stringstream s;
    s<<file.rdbuf();
    str = s.str();
    file.close();
}


void WordCount(string data,NumCount* paraCnt)
{
    int flag;
    int len = (int)data.length();
    for(int i=0; i<len; ++i)
    {
        flag = 0;
        for(int j=0; j<paraCnt->length;++j)
        {
            if(data[i]==paraCnt->count[j].ch)
            {
                ++paraCnt->count[j].cnt;
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            paraCnt->count[paraCnt->length].ch = data[i];
            ++paraCnt->count[paraCnt->length].cnt;
            ++paraCnt->length;
        }
    }
}

void Show(NumCount* paraCnt)
{
    cout<<"the length is "<<paraCnt->length<<endl;
    for(int i = 0;i < paraCnt->length;++i)
    {
        cout<<"The character "<<paraCnt->count[i].ch<<"  appears  "<<paraCnt->count[i].cnt<<endl;
    }
    cout<<endl;
}

void CreateHuffmanTree(HuffmanTree &HT,int length,NumCount cntarray)
{
    if(length<=1)
    printf("ERROR!!!\r\n");

    int s1,s2;
    int m = length*2-1;
    HT = new HTNode[m+1];
    for(int i = 1;i <= m;++i)
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    
    for(int i = 1;i <= length;++i)
    {
        HT[i].data = cntarray.count[i-1].ch;
        HT[i].weight = cntarray.count[i-1].cnt;
    }
    
    for(int i = length + 1;i <= m; ++i)
    {
        select(HT,i-1,&s1,&s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void select(HuffmanTree HT,int top,int* s1,int* s2)
{
    int min = INT_MAX;
    for(int i = 1;i <= top;++i)
    {
        if(HT[i].weight < min && HT[i].parent == 0)
        {
            min = HT[i].weight;
            *s1 = i;
        }
    }
    
    min = INT_MAX;
    for(int i = 1;i <= top;++i)
    {
        if(HT[i].weight < min && i != *s1 && HT[i].parent == 0)
        {
            min = HT[i].weight;
            *s2 = i;
        }
    }
}

void CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int length)
{
    HC = new HCode[length+1];
    char *cd = new char[length];
    cd[length-1] = '\0';
    int c,f,start;
    for(int i = 1;i <= length;++i)
    {
        start = length-1;  // start表示编码在临时空间内的起始下标，由于是从叶子节点回溯，所以是从最后开始
        c = i;
        f = HT[c].parent;
        while(f != 0)
        {
            --start;  // 由于是回溯，所以从临时空间的最后往回计
            if(HT[f].lchild == c)
                cd[start] = '0';
            else
                cd[start] = '1';
            c = f;
            f = HT[c].parent;
        }
        HC[i].str = new char[length-start];  //编码空间大小是length-start
        HC[i].data = HT[i].data;
        strcpy(HC[i].str,&cd[start]);
    }
    delete[] cd;
}

void Encode(string data,HuffmanCode HC,int length)
{
    ofstream outfile;
    outfile.open("Encode.txt");
    for(int i = 0;i < data.length();++i)
    {
        for(int j = 1;j <= length;++j)
        {
            if(data[i] == HC[j].data)
            {
                outfile<<HC[j].str;
            }
        }
    }
    outfile.close();
    cout<<"the code txt has been written"<<endl;
    cout<<endl;
}

void Decode(HuffmanTree HT,int length)
{
    char codetxt[MaxSize*length];
    ifstream infile;
    infile.open("Encode.txt");
    infile.getline(codetxt,MaxSize*length);
    infile.close();
    
    ofstream outfile;
       outfile.open("Decode.txt");
    
    int root = 2*length-1;  // 从根节点开始遍历
    for(int i = 0;i < strlen(codetxt);++i)
    {
        if(codetxt[i] == '0') root = HT[root].lchild;  //为0表示向左遍历
        else if(codetxt[i] == '1') root = HT[root].rchild; //为1表示向右遍历
        if(HT[root].lchild == 0 && HT[root].rchild == 0)
            // 如果已经是叶子节点，输出到输出文件中，然后重新回到根节点
        {
            outfile<<HT[root].data;
            root = 2*length-1;
        }
    }
    outfile.close();
    cout<<"the output txt has been written"<<endl;
    cout<<endl;
}

void PrintBiTree1(HuffmanTree T, int p, int type, int level) {
    int i;
    if (p == 0) return;
    PrintBiTree1(T, T[p].rchild, 2, level+1);
    switch (type) {
        case 0:
            printf("%c\n", T[p].data);
            break;
        case 1:
            for (i = 0; i < level; i++)
                printf("\t");
            printf("\\ %c\n", T[p].data);
            break;
        case 2:
            for (i = 0; i < level; i++)
                printf("\t");
            printf("/ %c\n", T[p].data);
            break;
    }
    PrintBiTree1(T, T[p].lchild, 1,  level+1);
}

int main(int argc, char** argv) {
    string data;
    NumCount Cntarray;
    ReadData(data);  // 读入数据
    double len_0 = (double)data.length();
    WordCount(data,&Cntarray);  // 统计次数
    Show(&Cntarray); //可以查看每个单词出现的对应次数
    HuffmanTree tree;
    CreateHuffmanTree(tree,Cntarray.length,Cntarray);  // 建树
    HuffmanCode code;
    CreateHuffmanCode(tree,code,Cntarray.length);  // 创建编码
    PrintBiTree1(tree, 2*Cntarray.length-1, 0, 0);
    Encode(data,code,Cntarray.length);  // 生成编码文件
    string Code;
    ReadCode(Code);
    double len_1 = (double)Code.length();
    double rate = len_1/(8*len_0);
    cout<<"Encoding rate is "<<rate<<endl;
    Decode(tree,Cntarray.length);  // 解码
    return 0;
}
