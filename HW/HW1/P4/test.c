#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isop(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        return 1;
    return 0;
}
int type(char c){
    if(c == '+')
        return 1;
    else if(c == '-')
        return 2;
    else if(c == '*')
        return 3;
    else if(c == '/')
        return 4;
    else if(c == '%')
        return 5;   
    return 0;
}
long long int divide(long long int a, long long int b){
    if(((a > 0 && b < 0) || (a < 0 && b > 0)) && a % b != 0){
        return (a/b-1);
    }
    else
        return (a/b);
}
long long int multi(long long int a, long long int b, int flag){
    switch(flag){
        case 1:
            a *= b;
            break;
        case 2:
            a = divide(a, b);
            break;
        case 3:
            a %= b;
            break;
    }
    return a;
}
long long int add(long long int ans, long long int mul, long long int cur, int add_flag, int mul_flag){
    //先乘除後加減
    mul = multi(mul, cur, mul_flag);
    if(add_flag == 1){
        ans += mul;
    }
    else if(add_flag == -1){
        ans -= mul;
    }
    return ans;
}

long long int main(void){
    long long int ans = 0,cur = 0, mul = 1;
    int op = -1;
    char c;
    //要用flag分開不然會爆炸 ex:4-13/3=
    int add_flag = 1; //flag for + and -    1 for +, -1 for -
    int mul_flag = 1; //flag for *, / and % 1 for *, 2 for /, 3 for %
    while(scanf("%c", &c) != EOF){
        if(c == ' ' || c == '\n'){
            return 0;
        }
        if(c == ')'){
            ans = add(ans, mul, cur, add_flag, mul_flag);
            return ans;
        }
        if(c == '('){
            cur = main();
        }
        if(c == '='){
            cur = add(ans, mul, cur, add_flag, mul_flag);
            printf("Print: %lld\n", cur);
            ans = 0;
            mul = 1;
            add_flag = 1;
            mul_flag = 1;
        }
        if(isdigit(c)){
            cur = cur*10 + c - '0';
        }
        if(isop(c)){
            op = type(c);
            switch(op){
                case 1:
                    ans = add(ans, mul, cur, add_flag, mul_flag);
                    mul = 1;
                    cur = 0;
                    mul_flag = 1;
                    add_flag = 1; 
                    break;
                case 2:
                    ans = add(ans, mul, cur, add_flag, mul_flag);
                    mul = 1;
                    cur = 0;
                    mul_flag = 1;
                    add_flag = -1; 
                    break;
                case 3:
                    mul = multi(mul, cur, mul_flag);
                    cur = 0;
                    mul_flag = 1;
                    break; 
                case 4:
                    mul = multi(mul, cur, mul_flag);
                    cur = 0;
                    mul_flag = 2;
                    break;
                case 5:
                    mul = multi(mul, cur, mul_flag);
                    cur = 0;
                    mul_flag = 3;
                    break;
            }
        }
    }
    return 0;
}
