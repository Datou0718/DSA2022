#include <stdio.h>
#include <string.h>

int main(void){
    char str[15];
    strcpy(str, "characteristic");
    int num[15];
    for(int i = 0; i < 14; i++){
        num[i] = str[i] - 'a';
    }
    int cnt = 0;
    for(int i = 0; i < 12; i++){
        int ans = ((num[i]*2+num[i+1])*2+num[i+2])%12;
        if(ans == 10)
            cnt++;
    }
    printf("%d", cnt);
}