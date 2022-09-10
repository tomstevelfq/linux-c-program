#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
    // if(argc!=2){
    //     printf("usage: %s <filename>\n",argv[0]);
    //     exit(1);
    // }
    // FILE* file=fopen(argv[1],"r");
    // if(file==NULL){
    //     perror("file open");
    //     exit(1);
    // }
    // fseek(file,0,SEEK_END);
    // printf("file length is %ld\n",ftell(file));
    FILE *file=fopen("zerofile.txt","w+");
    if(file==NULL){
        perror("file open");
        exit(1);
    }
    fseek(file,1024*1024,SEEK_SET);
    fputc('\0',file);
    printf("%ld\n",ftell(file));
    fclose(file);
    return 0;
}