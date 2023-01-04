//
//  Precede.hpp
//  DSA_2
//
//  Created by 健 on 2022/10/7.
//

#ifndef Precede_hpp
#define Precede_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

char Precede(char c1, char c2){
    if(c1 == '+'||c1 == '-'){
        switch (c2) {
            case '+':
                return '>';
            case '-':
                return '>';
            case '*':
                return '<';
            case '/':
                return '<';
            case '(':
                return '<';
            case ')':
                return '>';
            case '#':
                return '>';
            default:
                break;
        }
    }
    if(c1 == '*'||c1 == '/'){
        switch (c2) {
            case '+':
                return '>';
            case '-':
                return '>';
            case '*':
                return '>';
            case '/':
                return '>';
            case '(':
                return '<';
            case ')':
                return '>';
            case '#':
                return '>';
            default:
                break;
        }
    }
    if(c1 == '('){
        switch (c2) {
            case '+':
                return '<';
            case '-':
                return '<';
            case '*':
                return '<';
            case '/':
                return '<';
            case '(':
                return '<';
            case ')':
                return '=';
            default:
                break;
        }
    }
    if(c1 == ')'){
        switch (c2) {
            case '+':
                return '>';
            case '-':
                return '>';
            case '*':
                return '>';
            case '/':
                return '>';
            case ')':
                return '>';
            case '#':
                return '>';
            default:
                break;
        }
    }
    if(c1 == '#'){
        switch (c2) {
            case '+':
                return '<';
            case '-':
                return '<';
            case '*':
                return '<';
            case '/':
                return '<';
            case '(':
                return '<';
            case '#':
                return '=';
            default:
                break;
        }
    }
    return 0;
}

char Prec(string c1, string c2){
    if(c1.compare("+")==0||c1.compare("-")==0){
        if(c2.compare("+")==0||c2.compare("-")==0||c2.compare(")")==0||c2.compare("#")==0)
            return '>';
        if(c2.compare("*")==0||c2.compare("/")==0||c2.compare("(")==0||c2.compare("sin")==0||c2.compare("cos")==0||c2.compare("tan")==0||c2.compare("ln")==0||c2.compare("^")==0)
            return '<';
    }
    if(c1.compare("*")==0||c1.compare("/")==0){
        if(c2.compare("+")==0||c2.compare("-")==0||c2.compare(")")==0||c2.compare("#")==0)
            return '>';
        if(c2.compare("*")==0||c2.compare("/")==0||c2.compare("(")==0||c2.compare("sin")==0||c2.compare("cos")==0||c2.compare("tan")==0||c2.compare("ln")==0||c2.compare("^")==0)
            return '<';
    }
    if(c1.compare("(")==0||c1.compare("#")==0){
        if(c2.compare(")")==0) return '=';
        return '<';
    }
    if(c1.compare(")")==0)
        return '>';
    if(c1.compare("sin")==0||c1.compare("cos")==0||c1.compare("tan")==0||c1.compare("ln")==0||c1.compare("^")==0){
        if(c2.compare("+")==0||c2.compare("-")==0||c2.compare(")")==0||c2.compare("#")==0||c2.compare("*")==0||c2.compare("/")==0)
            return '>';
        if(c2.compare("(")==0||c2.compare("sin")==0||c2.compare("cos")==0||c2.compare("tan")==0||c2.compare("ln")==0||c2.compare("^")==0)
            return '<';
    }
    if(c1.compare("#")==0){
        if(c2.compare("#")==0) return '=';
        else return '<';
    }
    return '=';
}

double BiOperation(double num1, string c, double num2){
    double sum = 0;
    if(c.compare("+")==0) sum = num1 + num2;
    if(c.compare("-")==0) sum = num1 - num2;
    if(c.compare("*")==0) sum = num1 * num2;
    if(c.compare("/")==0) sum = num1 / num2;
    if(c.compare("^")==0) sum = pow(num1, num2);
    return sum;
}

double SiOperation(double num, string c){
    double sum = 0;
    if(c.compare("sin")==0) sum = sin(num);
    if(c.compare("cos")==0) sum = cos(num);
    if(c.compare("tan")==0) sum = tan(num);
    if(c.compare("ln")==0) sum = log(num);
    return sum;
}

int OP_Sort(string c){
    if(c.compare("+")==0||c.compare("-")==0||c.compare("*")==0||c.compare("/")==0||c.compare("^")==0)
        return 2;
    if(c.compare("sin")==0||c.compare("cos")==0||c.compare("tan")==0||c.compare("ln")==0)
        return 1;
    return 0;
}

#endif /* Precede_hpp */
