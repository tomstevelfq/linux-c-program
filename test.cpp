#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
using namespace std;

int main(int argc,char **argv){
	cout<<argc<<endl;
	for(int i=0;i<argc;i++){
		cout<<argv[i]<<endl;
	}
	exit(-1);
}
