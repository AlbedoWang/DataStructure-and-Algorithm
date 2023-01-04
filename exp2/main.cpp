//
//  main.cpp
//  DSA_2
//
//  Created by 健 on 2022/10/2.
//

#include <iostream>
#include <cstdio>
#include <math.h>
#include <stack>
#include <string>
#include <vector>
#include "Precede.hpp"
#include "Polynomial.hpp"
using namespace std;

bool IsOperation(char c){
    bool flag = false;
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#')
        flag = true;
    return flag;
}

int Operate(int a, char c, int b){
    if(c=='+') return a+b;
    if(c=='-') return a-b;
    if(c=='*') return a*b;
    if(c=='/') return a/b;
    return 0;
}

Polynomial PolyOperate(Polynomial &Pa, char theta, Polynomial &Pb){
    if(theta=='+'){
        Add_Poly(Pa, Pb);
        return Pa;
    }
    if(theta=='-'){
        Minus_Poly(Pa, Pb);
        Sort_Poly(Pa);
        return Pa;
    }
    if(theta=='*') return Mult_Poly(Pa, Pb);
    if(theta=='/') return Div_Poly(Pa, Pb);
    return NULL;
}

/*int EvaluateExpression(string expr){
    stack<char> SOP;
    stack<int> SVAL;
    SOP.push('#');
    expr[expr.length()] = '#';
    char tmp[2]; int i = 0; char c = expr[i++];
    while(c!='#'||SOP.top()!='#'){
        if(!IsOperation(c)){
            tmp[0] = c; tmp[1] = '\0';
            SVAL.push(atoi(tmp));
            c = expr[i++];
        }
        else switch(Precede(SOP.top(), c)){
            case '<': SOP.push(c); c = expr[i++]; break;
            case '=': SOP.pop(); c = expr[i++]; break;
            case '>': char theta = SOP.top(); SOP.pop();
                int b = SVAL.top(); SVAL.pop();
                int a = SVAL.top(); SVAL.pop();
                SVAL.push(Operate(a, theta, b)); break;
        }
    }
    expr[expr.length()] = '\0';
    return SVAL.top();
}*/

bool IsOperation(string expr){
    bool flag = false;
    if(expr.compare("+")==0||expr.compare("-")==0||expr.compare("*")==0||expr.compare("/")==0||expr.compare("^")==0||expr.compare("sin")==0||expr.compare("cos")==0||expr.compare("ln")==0||expr.compare("tan")==0||expr.compare("#")==0||expr.compare("(")==0||expr.compare(")")==0)
        flag = true;
    return flag;
}

double EvaluateExpression(vector<string> expr){
    stack<string> SOP;
    stack<double> SVAL;
    SOP.push("#");
    int i = 0;
    string tmp = expr[i++];
    while(tmp.compare("#")!=0||SOP.top().compare("#")!=0){
        if(!IsOperation(tmp)){
            double numd = stod(tmp);
            SVAL.push(numd);
            tmp = expr[i++];
        }
        else switch(Prec(SOP.top(), tmp)){
            case '<':
                SOP.push(tmp);
                tmp = expr[i++];
                break;
            case '=':
                SOP.pop();
                tmp = expr[i++];
                break;
            case '>':
                string theta = SOP.top();
                SOP.pop();
                if(OP_Sort(theta)==1){
                    double numtmp = SVAL.top(); SVAL.pop();
                    SVAL.push(SiOperation(numtmp, theta));
                }
                if(OP_Sort(theta)==2){
                    double num2;
                    if(!SVAL.empty())
                        num2 = SVAL.top();
                    else{
                        cout<<"ERROR";
                        exit(0);
                    }
                    double num1;
                    if(!SVAL.empty())
                        num1 = SVAL.top();
                    else{
                        cout<<"ERROR";
                        exit(0);
                    }
                    if(!SVAL.empty())
                        SVAL.pop();
                    else{
                        cout<<"ERROR";
                        exit(0);
                    }
                    if(!SVAL.empty())
                        SVAL.pop();
                    else{
                        cout<<"ERROR";
                        exit(0);
                    }
                    SVAL.push(BiOperation(num1, theta, num2));
                }
                break;
        }
    }
    if(SOP.top()!="#") {
        cout<<"ERROR";
        exit(0);
    }
    return SVAL.top();
}

void Input(vector<Polynomial> &P){
    while(1){
        cout<<"Polynomial Number:";
        int num;
        cin>>num;
        if(num == -1) break;
        cout<<"\nInput Polynomial:"<<endl;
        int expn; double coef;
        LNode* Pa = new LNode;
        Init_Poly(Pa);
        while(1){
            cin>>coef;
            if(coef == 0) break;
            cin>>expn;
            Cin_Poly(Pa, expn, coef, Init_num);
        }
        P.push_back(Pa);
    }
}

Polynomial EvaluatePoly(vector<Polynomial> P, string expr){
    stack<Polynomial> SPOLY;
    stack<char> SOP;
    int i = 0;
    //LNode* ptmp = P[i++];
    SOP.push('#');
    expr[expr.length()] = '#';
    char tmp[2]; char c = expr[i++];
    while(c!='#'||SOP.top()!='#'){
        if(!IsOperation(c)){
            tmp[0] = c; tmp[1] = '\0';
            SPOLY.push(P[atoi(tmp)]);
            c = expr[i++];
        }
        else switch(Precede(SOP.top(), c)){
            case '<': SOP.push(c); c = expr[i++]; break;
            case '=': SOP.pop(); c = expr[i++]; break;
            case '>': char theta = SOP.top(); SOP.pop();
                LNode* b = SPOLY.top(); SPOLY.pop();
                LNode* a = SPOLY.top(); SPOLY.pop();
                SPOLY.push(PolyOperate(a, theta, b)); break;
        }
    }
    expr[expr.length()] = '\0';
    return SPOLY.top();
}

int main(int argc, const char * argv[]) {
    vector<string> expr;
    string tmp;
    cout<<"Choose Function:";
    int fun;
    cin>>fun;
    if(fun==1){
        cout<<"Input Expression (end with '#'):"<<endl;
        cout<<"(Please type blank between each operation and number)"<<endl;
        while(tmp!="#"){
            cin>>tmp;
            expr.push_back(tmp);
        }
        cout<<"Calculation Result:"<<EvaluateExpression(expr)<<endl;
    }
    else if(fun==2){
        vector<Polynomial> P;
        Input(P);
        cout<<"Input Expression:"<<endl;
        string pexpr;
        cin>>pexpr;
        Print_Poly(EvaluatePoly(P, pexpr));
    }
    else exit(0);
}
