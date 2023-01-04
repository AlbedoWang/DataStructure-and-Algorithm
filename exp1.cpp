//
//  main.cpp
//  DSA_1
//
//  Created by 健 on 2022/9/29.
//

#include <iostream>
#include <math.h>
using namespace std;

#define Init_num 1
#define Add_num 2

typedef struct ElemType{
    int expn;
    double coef;
} ElemType;

typedef struct LNode{
    ElemType data;
    LNode* next;
}* Polynomial;

void Init_Poly(Polynomial& P){
    P = NULL;
}

bool IsEmpty_Poly(Polynomial P){
    //判断多项式是否为空（空返回0，非空1）
    bool flag = true;
    if(!P) flag = false;
    return flag;
}

void Print_Poly(Polynomial P){
    //打印多项式
    LNode* pf = P;
    while(pf){
        if(fabs(pf->data.coef)<1e-9){
            pf = pf->next;
            continue;
        }
        cout<<pf->data.coef<<"x^"<<pf->data.expn;
        if(pf->next&&pf->next->data.coef>=0)
            cout<<"+";
        pf = pf->next;
    }
}

void Sort_Poly(Polynomial& P){
    //去除多项式中系数为0的项
    LNode* pd = P;
    if(!IsEmpty_Poly(P)) return;
    while(pd){
        if(fabs(pd->data.coef)<=1e-9){
            LNode* pf = P;
            if(fabs(pf->data.coef)<=1e-9){
                P = pf->next;
                delete pf;
            }
            else{
                while(pf->next!=pd) pf = pf->next;
                pf->next = pd->next;
                delete pd;
            }
        }
        pd = pd->next;
    }
}

void Cin_Poly(Polynomial& P, int expn, double coef, int func){
    //向多项式中添加单一项
    LNode* temp = P;
    if(!IsEmpty_Poly(P)){
        LNode* pnew = new LNode;
        pnew->data.coef = coef;
        pnew->data.expn = expn;
        pnew->next = P;
        P = pnew;
        return;
    }
    while(temp){
        if(temp->data.expn>=expn) break;
        temp = temp->next;
    }
    if(temp){
        if(temp->data.expn==expn){
            switch (func) {
                case Init_num:
                    temp->data.coef = coef;
                    break;
                case Add_num:
                    temp->data.coef += coef;
                    break;
                default:
                    break;
            }
        }
        else{
            LNode* pnew = new LNode;
            pnew->next = temp->next;
            temp->next = pnew;
            pnew->data.coef = temp->data.coef;
            pnew->data.expn = temp->data.expn;
            temp->data.coef = coef;
            temp->data.expn = expn;
        }
    }
    else{
        temp = P;
        while(temp->next) temp = temp->next;
        LNode* pnew = new LNode;
        temp->next = pnew;
        pnew->data.coef = coef;
        pnew->data.expn = expn;
        pnew->next = NULL;
    }
}

void Add_Poly(Polynomial& Pa, Polynomial Pb){
    LNode* pf = Pb;
    while(pf){
        Cin_Poly(Pa, pf->data.expn, pf->data.coef, Add_num);
        pf = pf->next;
    }
    Sort_Poly(Pa);
}

void Minus_Poly(Polynomial& Pa, Polynomial& Pb){
    LNode* pf = Pb;
    while(pf){
        Cin_Poly(Pa, pf->data.expn, -1.0*pf->data.coef, Add_num);
        pf = pf->next;
    }
    Sort_Poly(Pa);
}

Polynomial Copy_Poly(Polynomial& P){
    //多项式复制
    LNode* pnew = new LNode;
    LNode* pf = P,* head = pnew;
    while(pf){
        pnew->data.coef = pf->data.coef;
        pnew->data.expn = pf->data.expn;
        LNode* temp = new LNode;
        if(!pf->next)
            break;
        pnew->next = temp;
        pnew = pnew->next;
        pf = pf->next;
    }
    pnew->next = NULL;
    return head;
}


Polynomial mult_Poly(Polynomial& P, int expn, double coef){
    //单一项与多项式相乘，返回结果多项式
    LNode* pf = P;
    LNode* head = pf;
    while(pf){
        pf->data.coef *= coef;
        pf->data.expn += expn;
        pf = pf->next;
    }
    return head;
}

Polynomial Mult_Poly(Polynomial& Pa, Polynomial Pb){
    //多项式相乘
    LNode* pf = Pb;
    LNode* newPoly = new LNode;
    Init_Poly(newPoly);
    while(pf){
        LNode* copy_a = Copy_Poly(Pa);
        Add_Poly(newPoly, mult_Poly(copy_a, pf->data.expn, pf->data.coef));
        pf = pf->next;
    }
    return newPoly;
}

Polynomial Div_Poly(Polynomial& Pa, Polynomial Pb){
    //多项式相除
    double delta_c; int delta_e;
    LNode* newPoly = new LNode;
    //LNode* head = newPoly;
    Init_Poly(newPoly);
    while(Pa){
        LNode* pa = Pa,* pb = Pb;
        while(pa->next) pa = pa->next;
        while(pb->next) pb = pb->next;
        if(pa->data.expn < pb->data.expn)
            break;
        delta_c = pa->data.coef/pb->data.coef;
        delta_e = pa->data.expn - pb->data.expn;
        Cin_Poly(newPoly, delta_e, delta_c, Add_num);
        LNode* Copy_b = Copy_Poly(Pb);
        LNode* delta_poly = mult_Poly(Copy_b, delta_e, -1.0*delta_c);
        Add_Poly(Pa, delta_poly);
        Sort_Poly(Pa);
    }
    Sort_Poly(Pa);
    Sort_Poly(Pb);
    return newPoly;
}

void Integ_Poly(Polynomial& P, double bot, double top){
    //多项式积分
    LNode* pf = P;
    while(pf){
        pf->data.expn += 1;
        pf->data.coef *= 1/(double)pf->data.expn;
        pf = pf->next;
    }
    double sum_top = 0, sum_bot = 0;
    pf = P;
    while(pf){
        sum_bot += pf->data.coef*pow(bot,(double)pf->data.expn);
        sum_top += pf->data.coef*pow(top,(double)pf->data.expn);
        pf = pf->next;
    }
    double sum = sum_top - sum_bot;
    cout<<"Integral Polynomial:";
    Print_Poly(P);
    cout<<"+C"<<endl<<"Integral conclusion:"<<sum;
}

void MinDiv_Poly(Polynomial& Pa, Polynomial& Pb){
    //求多项式的最大公约式与最小公倍式
    LNode* pa = Pa,* pb = Pb,* temp;
    LNode* Pmult = Mult_Poly(Pa, Pb);
    while(pa&&pb){
        Div_Poly(pa, pb);
        Sort_Poly(pa);
        if(!(pa&&pb)) break;
        temp = pa;
        pa = pb;
        pb = temp;
        cout<<"Pa:";
        Print_Poly(Pa);
        cout<<endl<<"Pb:";
        Print_Poly(Pb);
        cout<<endl;
    }
    LNode* Pchoice = Pa;//选择Pa与Pb中非空的一个多项式（即最大公约式）
    if(fabs(Pchoice->data.coef)<1e-9) Pchoice = Pb;
    LNode* Pdiv = Div_Poly(Pmult, Pchoice);
    cout<<endl<<"Minimum Common Multiple:";
    Print_Poly(Pdiv);
    cout<<endl;
}

void Des_Poly(Polynomial& P){
    //摧毁多项式
    LNode* p = P;
    while(p){
        LNode* pd = p;
        p = p->next;
        delete pd;
    }
}

void Function(){
    cout<<"Functions:"<<endl;
    cout<<"1,Print Polynomials"<<endl;
    cout<<"2,Add Polynomials(Pa + Pb)"<<endl;
    cout<<"3,Minus Polynomials(Pa - Pb)"<<endl;
    cout<<"4,Multiply Polynomials(Pa * Pb)"<<endl;
    cout<<"5,Divide Polynomials(Pa / Pb)"<<endl;
    cout<<"6,Integral Polynomial(Pa or Pb)"<<endl;
    cout<<"7,Minimal Divide Polynomials(Euclidean Division)"<<endl;
    cout<<"8,Destroy Polynomials"<<endl;
}

int main(int argc, const char * argv[]) {
    cout<<"Put in Polynomial A:"<<endl;
    int expn; double coef;
    LNode* Pa = new LNode;
    LNode* Pb = new LNode;
    Init_Poly(Pa); Init_Poly(Pb);
    while(1){
        cin>>coef;
        if(coef == 0) break;
        cin>>expn;
        Cin_Poly(Pa, expn, coef, Init_num);
    }
    cout<<"Put in Polynomial B:"<<endl;
    while(1){
        cin>>coef;
        if(coef == 0) break;
        cin>>expn;
        Cin_Poly(Pb, expn, coef, Init_num);
    }
    cout<<"Pa:";
    Print_Poly(Pa);
    cout<<endl<<"Pb:";
    Print_Poly(Pb);
    cout<<endl;
    while(1){
        cout<<endl;
        Function();
        int fun_num = 0;
        cout<<endl<<"Type in function number:";
        cin>>fun_num;
        switch (fun_num) {
            case 1:
                Print_Poly(Pa);
                cout<<endl;
                Print_Poly(Pb);
                break;
            case 2:
                Add_Poly(Pa, Pb);
                Print_Poly(Pa);
                cout<<endl;
                Print_Poly(Pb);
                break;
            case 3:
                Minus_Poly(Pa, Pb);
                Print_Poly(Pa);
                cout<<endl;
                Print_Poly(Pb);
                break;
            case 4:{
                cout<<"Polynomial:";
                Print_Poly(Mult_Poly(Pa, Pb));
                break;
            }
            case 5:{
                LNode* div = Div_Poly(Pa, Pb);
                cout<<"conclusion:";
                Print_Poly(Pa);
                cout<<endl<<"Rest:";
                Print_Poly(div);
                break;
            }
            case 6:{
                cout<<"Type in Polynomial(1 or 2):";
                int choice = 0;
                cin>>choice;
                LNode* pc;
                switch (choice) {
                    case 1:
                        pc = Pa;
                        break;
                    case 2:
                        pc = Pb;
                        break;
                    default:
                        cout<<"ERROR";
                        return 0;
                        break;
                }
                cout<<"Put in Bot and Top:";
                double bot, top;
                cin>>bot;
                cin>>top;
                Integ_Poly(pc, bot, top);
                break;
            }
            case 7:
                MinDiv_Poly(Pa, Pb);
                cout<<"Polynomial A:";
                Print_Poly(Pa);
                cout<<endl<<"Polynomial B:";
                Print_Poly(Pb);
                break;
            case 8:
                Des_Poly(Pa);
                Des_Poly(Pb);
                break;
            default:
                exit(0);
                break;
        }
    }
    return 0;
}
