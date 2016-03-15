//
//  hw4.c
//  hw4
//
//  Created by Zhen Yang on 2/27/16.
//
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "encrypt3.c"


int main(int argc,char *argv[]){
    FILE * f;
    FILE * m;
    
    //char *s="0123456789abcdef";
    if (argc<3) {
        fprintf(stderr,"malformed command\n");
        return 0;
    }else{
        if (strcmp(argv[1],"tablecheck")==0) {//tablecheck
            f=fopen(argv[2]+3,"r");
            if(f==NULL){
                fprintf(stderr,"can not open file\n");
                return 0;
            }
            if(tablecheck(f,NULL,NULL,NULL,NULL,NULL,NULL,NULL)==false){//only for tablechek, not for retreive data
                fprintf(stderr,"malformed tablefile\n");
                return 0;
            }
            fclose(f);
        }else if(strcmp(argv[1],"encrypt")==0){
            if (argc<4) {
                fprintf(stderr,"malformed command\n");
            }else{
                f=fopen(argv[3]+3,"rb");
                if (argc==4) {
                    encrypt(argv[2]+3,f,stdin,0);
                }else{
                    m=fopen(argv[4],"rb");
                    if(m==NULL){
                        fprintf(stderr,"can not open inputfile\n");
                        return 0;
                    }
                    
                    encrypt(argv[2]+3,f,m,0);
                    fclose(m);
                }
                fclose(f);
                
            }
        }else if(strcmp(argv[1],"decrypt")==0){//decrypt using encrypt function
            if (argc<4) {
                fprintf(stderr,"malformed command\n");
                
            }else{
                f=fopen(argv[3]+3,"rb");
                if (argc==4) {
                    encrypt(argv[2]+3,f,stdin,1);
                }else{
                    m=fopen(argv[4],"rb");
                    encrypt(argv[2]+3,f,m,1);
                    fclose(m);
                }
                fclose(f);
            }
        }else if(strcmp(argv[1],"encrypt3")==0){//encrypt decrypt encrypt
            if (argc<4) {
                fprintf(stderr,"malformed command\n");
            }else{
                f=fopen(argv[3]+3,"rb");
                if (argc==4) {
                    encrypt3(argv[2]+3,f,stdin,0);
                }else{
                    m=fopen(argv[4],"rb");
                    
                    encrypt3(argv[2]+3,f,m,0);
                    
                    
                    fclose(m);
                }
                fclose(f);
                
            }

//            system("./hw4 encrypt -k=1596369d5aa56235 -t=f0 f32 > 32.in");
//            system("./hw4 decrypt -k=5453ae44101c2614 -t=f0 32.in > 33.in");
//            system("./hw4 encrypt -k=c729a00607319591 -t=f0 33.in");
        }else if(strcmp(argv[1],"decrypt3")==0){
            if (argc<4) {
                fprintf(stderr,"malformed command\n");
            }else{
                f=fopen(argv[3]+3,"rb");
                if (argc==4) {
                    encrypt3(argv[2]+3,f,stdin,1);
                }else{
                    m=fopen(argv[4],"rb");
                    encrypt3(argv[2]+3,f,m,1);
                    fclose(m);
                }
                fclose(f);
                
            }
        }else{
            fprintf(stderr,"malformed command\n");
        }
    }
    return 0;
}
