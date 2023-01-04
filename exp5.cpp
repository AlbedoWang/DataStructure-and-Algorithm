//
//  main.cpp
//  DSA_5
//
//  Created by 健 on 2022/11/23.
//

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

typedef int ElemType;

typedef struct {
    ElemType *r;
    int len;
} SqTable;

void InitList(SqTable &L, int len) {
    // 0号单元不用
    L.r = (ElemType*)malloc((len+1)*sizeof(ElemType));
    L.len = len;
}

void CopyList(SqTable L, SqTable &newL) {
    newL.r = (ElemType*)malloc((L.len+1)*sizeof(ElemType));
    newL.len = L.len;
    memcpy(newL.r, L.r, (L.len+1)*sizeof(ElemType));
}

// 求一个整数的p次方
int intpow(int n, unsigned int p) {
    int res = 1;
    for (unsigned int i=0; i<p; ++i)
        res *= n;
    return res;
}

// 生成一个随机整数，其取值范围是[0, bound]
int randb(int bound) {
    int r = 0;
    unsigned int power = 0;
    do {
        r *= RAND_MAX;
        r += rand(); ++power;
    } while (intpow(RAND_MAX, power) < bound);
    return r % (bound+1);
}

// 随机打乱一个数组
void RandomShuffleList(SqTable L) {
    ElemType* array = L.r + 1; int n = L.len;
    for (int i=n-1; i>0; --i) {
        int j = randb(i); // 0<=j<=i
        ElemType tmp = array[i]; array[i] = array[j]; array[j] = tmp;
    }
}

// 验证顺序
string Prove(SqTable L){
    for(int i = 0; i < L.len; i++)
        if(L.r[i] > L.r[i+1]) return "FALSE";
    return "Correct!";
}

// 冒泡排序
void BubbleSort1(SqTable &L){
    int i, j;
    bool change = true;
    ElemType temp;
    for(i = L.len; i > 2 && change; i--){
        change = false;
        for(j = 1; j < i-1; ++j)
            if(L.r[j] > L.r[j+1]){
                temp = L.r[j+1];
                L.r[j+1] = L.r[j];
                L.r[j] = temp;
                change = true;
            }
    }
}
void BubbleSort(SqTable &L){
    int i, j;
    ElemType temp;
    for(i = 0; i < L.len; i++)
        for(j = 0; j < L.len-i; j++)
            if(L.r[j] > L.r[j+1]){
                temp = L.r[j];
                L.r[j] = L.r[j+1];
                L.r[j+1] = temp;
            }
}

//选择排序
void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void selection_sort(int arr[], int len)
{
    int i,j;
    for (i = 0 ; i < len - 1 ; i++) {
        int min = i;
        for (j = i + 1; j < len; j++) {    //  遍历未排序的元素
            if (arr[j] < arr[min]) {  //  找到目前最小值
                min = j;   // 记录最小值
            }
        }
        swap(&arr[min], &arr[i]);    //做交换
    }
}

// 快速排序
int Partition(SqTable &L, int low, int high){
    int pivotloc = low;
    ElemType temp = L.r[pivotloc];
    while(low < high){
        while(low < high && L.r[high] >= temp) --high;
        L.r[low] = L.r[high];
        while(low < high && L.r[low] <= temp) ++low;
        L.r[high] = L.r[low];
    }
    L.r[low] = temp;
    return low;
}
void QSort(SqTable &L, int low, int high){
    if(low < high){
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc-1);
        QSort(L, pivotloc+1, high);
    }
}
void QuickSort(SqTable &L){
    QSort(L, 1, L.len);
}

//插入排序
void InsertSort(SqTable &L){
    for (int i = 1; i <= L.len; i++){
        int key = L.r[i];
        int j = i-1;
        for(;j >= 0 && key < L.r[j]; j--)
            L.r[j+1] = L.r[j];
        L.r[j+1] = key;
    }
}

// 希尔排序
void ShellSortSub(SqTable &L, int dk){
    for (int i = dk+1; i <= L.len; ++i) {
        if (L.r[i] < L.r[i-dk]) {
            ElemType tmp = L.r[i];
            int j;
            for (j = i-dk; tmp < L.r[j] && j >= 1; j -= dk)
                L.r[j+dk] = L.r[j];
            L.r[j + dk] = tmp;
        }
    }
}
void ShellSort(SqTable &L){
    vector<int> incr;
    int l = L.len;
    while(l > 1){
        l = l/2 + 1;
        incr.push_back(l);
    }
    for(int i = 0; i < incr.size(); ++i)
        ShellSortSub(L, incr[i]);
}

// 堆排序
void HeapAdjust(SqTable &L, int s, int m){
    ElemType temp = L.r[s];
    for(int i = 2*s; i <= m; i *= 2){
        if (i<m && L.r[i]<L.r[i+1]) ++i;
        if (temp >= L.r[i]) break; // 已经找到合适的位置
        L.r[s] = L.r[i]; s = i; // 与孩子换位
    }
}
void HeapSort(SqTable &L){
    int i; ElemType tmp;
    for (i=L.len/2; i>0; --i)
        HeapAdjust(L, i, L.len); // 构造初始大顶堆
    for (i=L.len; i>1; --i) {
        tmp = L.r[i];
        L.r[i] = L.r[1];
        L.r[1] = tmp; // 将最大的关键字放到L.r[i]
        HeapAdjust(L, 1, i-1); // 对L.r[1..i-1]调用筛选法重新调整为堆
    }
}

// 归并排序
void Merge(ElemType* Rs, ElemType* Rt, int s, int m, int t) {
    // 已知Rs[s..m]和Rs[m+1..t]都是有序表，将它们归并存储到Rt[s..t]
    int i,j,k;
    for (i=s, j=m+1, k=s; i<=m && j<=t; ++k) {
        if (Rs[i] <= Rs[j]) Rt[k] = Rs[i++];
        else Rt[k] = Rs[j++];
    }
    for (; i<=m; ++i, ++k) Rt[k] = Rs[i];
    for (; j<=t; ++j, ++k) Rt[k] = Rs[j];
}
void MSort(ElemType* Rs, ElemType* Rt, int low, int high) {
    if (low < high) {
        int mid = (low+high)/2;
        MSort(Rs, Rt, low, mid); MSort(Rs, Rt, mid+1, high);
        Merge(Rs, Rt, low, mid, high);
        for (int i=low; i<=high; ++i) Rs[i] = Rt[i];
    }
}
void MergeSort(SqTable &L) {
    ElemType* tmp = new ElemType[L.len+1];
    MSort(L.r, tmp, 1, L.len);
    delete []tmp;
}

int main(int argc, const char * argv[]) {
    int N = 50000;
    SqTable L;
    InitList(L, N);
    for (int i = 1; i <= N; ++i) L.r[i] = i;
    RandomShuffleList(L);
    clock_t begin, end;
    
    //冒泡排序
    SqTable L1;
    CopyList(L, L1);
    begin = clock(); // 计时器开始
    BubbleSort(L1);
    end = clock(); // 计时器结束
    cout<<Prove(L1)<<endl;
    printf("BubbleSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);
    
    //快速排序
    SqTable L2;
    CopyList(L, L2);
    begin = clock(); // 计时器开始
    QuickSort(L2);
    end = clock(); // 计时器结束
    cout<<Prove(L2)<<endl;
    printf("QuickSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);
    
    //希尔排序
    SqTable L3;
    CopyList(L, L3);
    begin = clock();
    InsertSort(L3);
    //selection_sort(L3.r, L3.len);
    end = clock();
    cout<<Prove(L3)<<endl;
    printf("InsertSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);

    //堆排序
    SqTable L4;
    CopyList(L, L4);
    begin = clock();
    HeapSort(L4);
    end = clock();
    cout<<Prove(L4)<<endl;
    printf("HeapSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);
    
    //归并排序
    SqTable L5;
    CopyList(L, L5);
    begin = clock();
    MergeSort(L5);
    end = clock();
    cout<<Prove(L5)<<endl;
    printf("MergeSort time: %g seconds\n", (float)(end-begin)/CLOCKS_PER_SEC);
    
    return 0;
}
