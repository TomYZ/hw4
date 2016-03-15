//
//  tablecheck.c
//  hw4
//
//  Created by Zhen Yang on 2/27/16.
//
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
bool tablecheck(FILE *table,char* PC1,char* V,char* PC2,char* IP,char *E,char S[8][64],char *PP){
    // check whether IP is a permutation of 1-64
    int P[64];
    int i=0,j=0,k;
    int temp=0,t1=0,t2=0;
    char* buf=(char*)malloc(256);
    fgets(buf,256,table);
    buf+=2;
    for (i=0; i<64; i++) {//initialize IP permutation table to 0
        P[i]=0;
    }
    //printf("IP: ");
    for (i=0; i<64; i++) {
        temp=atoi(buf+1);//printf("%d,",temp);
        if(IP!=NULL){
            IP[i]=temp;
        }
        if(P[temp-1]==0){
            P[temp-1]=1;
        }else{
            fprintf(stderr,"IP is not valid\n");
            return false;// repeat, IP is not a permutation
        }
        if(temp>9){
            buf+=3;
        }else{
            buf+=2;
        }
    }
    //printf("\n");
    
    
    //check whether E is valid
    fgets(buf,256,table);
    buf+=1;
    for (i=0; i<48; i++) {//initialize  table to 0
        P[i]=0;
    }
    //printf("E: ");
    for (i=0; i<48; i++) {
        temp=atoi(buf+1);//printf("%d,",temp);
        if (E!=NULL) {
            E[i]=temp;
        }
        if(P[temp-1]==2){
            fprintf(stderr,"E is not valid\n");
            return false;
        }else{
            P[temp-1]++;
        }
        if(temp>9){
            buf+=3;
        }else{
            buf+=2;
        }
    }
    //printf("\n");
    temp=0;
    for (i=0; i<32; i++) {
        temp+=P[i];
    }
    if(temp!=48){
        fprintf(stderr,"E is not valid\n");
        return false;
    }
    
    
    //check whether P is a permutation of 1-32
    fgets(buf,256,table);
    buf+=1;
    for (i=0; i<32; i++) {
        P[i]=0;
    }
    //printf("P: ");
    for (i=0; i<33; i++) {
        temp=atoi(buf+1);
        if(i==32){
        if (temp!=0) {
            fprintf(stderr,"P is not valid\n");
            return false;
        }
        }else{
        if (PP!=NULL) {
            PP[i]=temp;
        }
        if(P[temp-1]==0){
            P[temp-1]=1;
        }else{
            fprintf(stderr,"P is not valid\n");
            return false;// repeat, P is not a permutation
        }
        
        if(temp>9){
            buf+=3;
        }else{
            buf+=2;
        }
        }
    }

    //printf("\n");
    
    
    //check whether S# is a 4 permutation of 1-16
    for(k=0;k<8;k++){
    fgets(buf,256,table);
    buf+=2;//printf("S%d: ",k);
    for(j=0;j<4;j++){
        for (i=0; i<16; i++) {
            P[i]=0;
        }
        for (i=0; i<16; i++) {
            temp=atoi(buf+1);//printf("%d,",temp);
            if (S!=NULL) {
                S[k][j*16+i]=temp;
            }
            if(P[temp]==0){
                P[temp]=1;
            }else{
                fprintf(stderr,"S%d is not valid\n",i+1);
                return false;
            }
            if(temp>9){
                buf+=3;
            }else{
                buf+=2;
            }
        }
        //printf("\n");
    }
    }
    
    //check whether V has 16 values which is 1 or 2 and the total 1 is 4 the total 2 is 12
    fgets(buf,256,table);
    buf+=1;
    //printf("V: ");
    t1=0;
    t2=0;
    for (i=0; i<16; i++) {
        temp=atoi(buf+1);
        //printf("%d,",temp);
        if (V!=NULL) {
            V[i]=temp;
        }
        
        if(temp>2){
            fprintf(stderr,"V is not valid\n");
            return false;
        }
        if(temp==1){
            t1++;
        }
        if(temp==2){
            t2++;
        }
        if(temp>9){
            buf+=3;
        }else{
            buf+=2;
        }

    }
    //printf("\n");
    if(t1!=4||t2!=12){
        fprintf(stderr,"V is not valid\n");
        return false;
    }
    
    
    //check whether PC1 is a permutation of 1-64 which is removed by 8 numbers, PC1 has 56 numbsers
    fgets(buf,256,table);
    buf+=3;
    //printf("PC1: ");
    for (i=0; i<64; i++) {
        P[i]=0;
    }
    for (i=0; i<56; i++) {
        temp=atoi(buf+1);//printf("%d,",temp);
        if(PC1!=NULL){
            PC1[i]=temp;
        }
        
        if(P[temp-1]==0&&(temp%8!=0)){
            P[temp-1]=1;
        }else{
            fprintf(stderr,"PC1 is not valid\n");
            return false;
        }
        if(temp>9){
            buf+=3;
        }else{
            buf+=2;
        }
    }
    //printf("\n");
    t1=0;
    for (i=0; i<64; i++) {
        if(P[i]==0){
            t1++;
        }
    }
    if(t1!=8){fprintf(stderr,"PC1 is not valid\n");
        return false;}
    
    
    
    //check whether PC2 is a permutation of 1-56 which is removed by 8 numbers, PC2 has 48 numbers
    fgets(buf,256,table);
    buf+=3;
    //printf("PC2: ");
    for (i=0; i<56; i++) {
        P[i]=0;
    }
    for (i=0; i<48; i++) {
        temp=atoi(buf+1);//printf("%d,",temp);
        if (PC2!=NULL) {
            PC2[i]=temp;
            
        }
        if(P[temp-1]==0){
            P[temp-1]=1;
        }else{
            fprintf(stderr,"PC2 is not valid\n");
            return false;
        }
        if(temp>9){
            buf+=3;
        }else{
            buf+=2;
        }
    }
    //printf("\n");
    t1=0;
    for (i=0; i<56; i++) {
        if(P[i]==0){
            t1++;
        }
    }
    if(t1!=8){
        fprintf(stderr,"PC2 is not valid\n");
    return false;
    }
    
    fseek(table,0,SEEK_SET);
    return true;
}
