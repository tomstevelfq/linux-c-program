/* 
io  iput && output  输入和输出  一切的基础
io就是文件，  Linux系统一切都是文件   io非常重要和基础
stdio   标准io  sysio  系统调用io  
标准Io  跨平台    系统调用io 平台相关
在两种io都能用的情况下  优先使用标准io   优点  跨平台  性能高

stdio:
    fopen();    fopen()创建的文件权限   umask   打开模式   r r+  w w+  a a+   r+ 和 w+的区别是是否创建文件
    fopen创建的文件权限 0666 & ~umask
    fdopen()   打开描述符
    freopen()   重定向
    fclose();
    fgetc();
    fgets(char*,int size,FILE*)   最多读取size-1个
    fputc();
    fread();  二进制
    fwrite(); 二进制

    fseek()
    ftell()
    rewind()

    fflush()

perror()   和 strerror()两个显示错误信息的函数
man   1:显示系统命令  2：显示系统调用   3：显示语言函数库  7；显示相关细节和杂项机制

socket返回的文件描述符可以被fdopen()当作文件流打开，所以一切socket接收发送问题可以转化成流的读写问题

缓冲区  行缓冲  全缓冲  无缓冲   
行缓冲： 换行时刷新   满了时刷新 强制刷新
全缓冲： 满了时刷新  强制刷新
无缓冲： stderr 立即刷新

getline()函数  完整地取得一行的函数
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>

int main(){
    char* str=NULL;
    size_t siz=0;
    FILE* file=fopen("test.txt","r");
    getline(&str,&siz,file);
    puts(str);
    free(str);
    return 0;
}