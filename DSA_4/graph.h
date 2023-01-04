//
//  graph.h
//  Graph_Practice
//
//  Created by 健 on 2022/11/23.
//

#ifndef graph_h
#define graph_h

#include <iostream>
#include <limits.h>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include "graph.h"
using namespace std;

const int INFINITY = INT_MAX;
const int MAX_VERTEX_NUM = 25;
typedef enum{DG, DN, UDG, UDN}GraphKind;
typedef int VertexType;
typedef int ArcType;
typedef int WeighType;

typedef struct{
    VertexType vexs[MAX_VERTEX_NUM];
    ArcType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
} MGraph;

void InitGraph(MGraph &G){
    for(int i = 0; i < MAX_VERTEX_NUM; i++)
        for(int j = 0; j < MAX_VERTEX_NUM; j++){
            G.arcs[i][j] = INFINITY;
            G.arcs[i][i] = 0;
        }
    ifstream data("dist.txt"); //待读取文件的目录
    vector<int> res;
    string line;
    while (getline(data, line)) {
        stringstream ss; //输入流
        ss << line; //向流中传值
        if (!ss.eof()) {
            int temp;
            while (ss >> temp) //提取int数据
                res.push_back(temp); //保存到vector
        }
    }
    int arcnum = 0;
    G.vexnum = 25;
    for(int i = 0; i < res.size(); i =  i + 3){
        G.arcs[res[i]][res[i+1]] = res[i+2];
        G.arcs[res[i+1]][res[i]] = res[i+2];
        arcnum++;
    }
    G.arcnum = arcnum;
}

void InitP(int P[][MAX_VERTEX_NUM]){
    for(int i = 0; i < MAX_VERTEX_NUM; i++)
        for(int j = 0; j < MAX_VERTEX_NUM; j++)
            P[i][j] = -1;
}

string City(int n){
    switch (n) {
        case 0:
            return "Haerbin";
        case 1:
            return "Changchun";
        case 2:
            return "Shenyang";
        case 3:
            return "Dalian";
        case 4:
            return "Tianjin";
        case 5:
            return "Beijing";
        case 6:
            return "Huhehaote";
        case 7:
            return "Xuzhou";
        case 8:
            return "Zhengzhou";
        case 9:
            return "Xi'an";
        case 10:
            return "Lanzhou";
        case 11:
            return "Xi'ning";
        case 12:
            return "Wulumuqi";
        case 13:
            return "Shanghai";
        case 14:
            return "Wuhan";
        case 15:
            return "Chengdu";
        case 16:
            return "Nanchang";
        case 17:
            return "Zhuzhou";
        case 18:
            return "Guiyang";
        case 19:
            return "Kunming";
        case 20:
            return "Fuzhou";
        case 21:
            return "Liuzhou";
        case 22:
            return "Guangzhou";
        case 23:
            return "Nanning";
        case 24:
            return "Shenzhen";
        default:
            break;
    }
    return 0;
}

#endif /* graph_h */
