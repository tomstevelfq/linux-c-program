#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int  main(){
    FILE* file=fopen("test.txt","r");
    char s[256];
    char *ss=fgets(s,5,file);
    printf("%s\n",ss);
    return 0;
}