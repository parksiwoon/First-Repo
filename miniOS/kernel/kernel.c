#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "system.h"
void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");
   
    char *input;

    while(1) {
        // readline을 사용하여 입력 받기
        printf("현재 사용 가능한 커맨드는 다음과 같습니다. \n\t minisystem | uppercase | fork | ipc | rr\n");
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input,"exit") == 0) {
            break;
        }

        else if (strcmp(input, "uppercase") == 0){
            uppercase(); // 새로운 추가함수 자리
        }

        else if(strcmp(input, "fork")==0){
            readline("start fork fuction");
            fork_test();
        }

        else if(strcmp(input,"ipc")==0){
            ipc_test();
        }

        else if(strcmp(input,"rr")==0){
            rr();
        }

        else if (strcmp(input,"minisystem") == 0){
            minisystem(); //minisystem 커맨드
        }
        else system(input);
    }

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
