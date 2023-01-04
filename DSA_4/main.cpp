//
//  main.cpp
//  DSA_4
//
//  Created by 健 on 2022/11/23.
//

#include <iostream>
#include <limits.h>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include "graph.h"
using namespace std;

void Dijkstra1(MGraph G, int v0, int *D, int P[][MAX_VERTEX_NUM]){
    int S[MAX_VERTEX_NUM] = {0};
    for(int i = 0; i < G.vexnum; i++){
        D[i] = G.arcs[v0][i];
        if(D[i] != INFINITY){
            P[i][0] = v0; P[i][1] = i; P[i][2] = -1;
        }
        S[v0] = 1;
        D[v0] = 0;
        int min, j, k = 0, w;
        for(i = 1; i < G.vexnum; i++){
            min = INFINITY;
            for(j = 0; j < G.vexnum; j++)
                if(!S[j] && D[j] < min){
                    min = D[j]; k = j;
                }
            S[k] = 1;
            for(j = 0; j < G.vexnum; j++)
                if(!S[j] && D[k] + G.arcs[k][j] < D[j]){
                    D[j] = D[k] + G.arcs[k][j];
                    for(w = 0; P[k][w] != -1; w++)
                        P[j][w] = P[k][w];
                    P[j][w] = j; P[j][w+1] = -1;
                }
        }
    }
}

int getWeight(MGraph G, int v0, int i){
    return G.arcs[v0][i];
}

void Dijkstra(MGraph G, int v0, int D[MAX_VERTEX_NUM], int P[][MAX_VERTEX_NUM]) {
    int min, k = -1, w;
    int S[MAX_VERTEX_NUM] = {0};
    for (int i = 0; i < G.vexnum; i++) {
        D[i] = getWeight(G, v0, i);
        if (D[i] != INFINITY) {
            P[i][0] = v0; P[i][1] = i; P[i][2] = -1;
        }
    }
    S[v0] = 1;
    D[v0] = 0;
    for (int i = 1; i < G.vexnum; i++) {
        min = INFINITY;
        for (int j = 0; j < G.vexnum; j++) {
            if (!S[j] && D[j] < min) {min = D[j]; k = j;}
        }
        if (k == -1) return;
        S[k] = 1;
        for (int j = 0; j < G.vexnum; j++) {
            if (!S[j] && getWeight(G, k, j) != INFINITY && D[k] + getWeight(G, k, j) < D[j]) {
                D[j] = D[k] + getWeight(G, k, j);
                for (w = 0; P[k][w] != -1; w++) P[j][w] = P[k][w];
                P[j][w] = j; P[j][w+1] = -1;
            }
        }
    }
}

void DeleteCity(MGraph &G, int v0){
    int i;
    for(i = 0; i < G.vexnum; i++){
        G.arcs[v0][i] = INFINITY;
        G.arcs[i][v0] = INFINITY;
    }
    G.arcs[v0][v0] = 0;
}

int main(int argc, const char * argv[]) {
    MGraph G;
    InitGraph(G);
    int D[MAX_VERTEX_NUM];
    int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {0};
    while(1){
        cout<<"Delete City?";
        int choice = 0;
        cin>>choice;
        if(choice){
            int v0;
            cout<<"City:";
            cin>>v0;
            DeleteCity(G, v0);
        }
        else break;
    }
    InitP(P);
    for(int i = 0; i < MAX_VERTEX_NUM; i++) D[i] = INFINITY;
    Dijkstra(G, 2, D, P);
    cout<<"SHENYANG - XI'AN: "<<D[9]<<endl<<"Route: ";
    for(int i = 0; P[9][i] != -1; i++)
        cout<<City(P[9][i])<<" ";
    cout<<endl;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) D[i] = INFINITY;
    InitP(P);
    Dijkstra(G, 6, D, P);
    cout<<"HUHEHAOTE - CHENGDU: "<<D[15]<<endl<<"Route: ";
    for(int i = 0; P[15][i] != -1; i++)
        cout<<City(P[15][i])<<" ";
    cout<<endl;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) D[i] = INFINITY;
    InitP(P);
    Dijkstra(G, 13, D, P);
    cout<<"SHANGHAI - WULUMUQI: "<<D[12]<<endl<<"Route: ";
    for(int i = 0; P[12][i] != -1; i++)
        cout<<City(P[12][i])<<" ";
    cout<<endl;
    return 0;
}
