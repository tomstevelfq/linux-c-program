#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
using namespace std;

//使用 getc  putc
void copy1(const char* srcpath,const char* destpath){
    FILE *src=fopen(srcpath,"r");
    if(src==NULL){
        perror("src file open");
        exit(1);
    }
    FILE *dest=fopen(destpath,"w+");
    if(dest==NULL){
        fclose(src);
        perror("dest file open");
        exit(1);
    }
    char ch;
    while((ch=getc(src))!=EOF){
        putc(ch,dest);
    }
    fclose(src);
    fclose(dest);
}

//使用fgets()   fputs()
void copy2(const char* srcname,const char* destname){
    FILE* src=fopen(srcname,"r");
    if(src==NULL){
        perror("src file open");
        exit(1);
    }
    FILE* dest=fopen(destname,"w+");
    if(dest==NULL){
        fclose(src);
        perror("dest file open");
        exit(1);
    }
    char buff[10];
    while(fgets(buff,8,src)!=NULL){
        fputs(buff,dest);
    }
    fclose(src);
    fclose(dest);
}

//使用 fread()   fwrite()
void copy3(const char* srcname,const char* destname){
    FILE* src=fopen(srcname,"r");
    if(src==NULL){
        perror("src file open");
        exit(1);
    }
    FILE* dest=fopen(destname,"w+");
    if(dest==NULL){
        fclose(src);
        perror("dest file open");
        exit(1);
    }
    char buff[8];
    int ret;
    do{
        ret=fread(buff,1,8,src);
        fwrite(buff,1,ret,dest);
    }while(ret==8);
    fclose(src);
    fclose(dest);
}


int main(int argc,char *argv[]){
    if(argc!=3){
        printf("usage:%s <srcfile> <destfile>",argv[0]);
        exit(1);
    }
    copy3(argv[1],argv[2]);
    return 0;
}