//
//  encrypt.c
//  hw4
//
//  Created by Zhen Yang on 2/28/16.
//
//

#include <stdio.h>
#include "tablecheck.c"
int hex_to_bin(char c){
    if(c<='9'&&c>='0'){
        return c-'0';
    }
    return c-'a'+10;
}
void leftshift(int* a){
    int i=0,temp=a[0];
    for(i=0;i<27;i++){
        a[i]=a[i+1];
    }
    a[27]=temp;
}
void print_hex_from_bin(int* a,int len){
    int i=0,temp;
    unsigned char c=0;
    for(i=0;i<len/4;i++){
        temp=a[i*4]*8+a[i*4+1]*4+a[i*4+2]*2+a[i*4+3];
        
        if(temp<10&&temp>-1)
            c='0'+temp;
        else if(temp<16&&temp>9)
            c='a'+(temp-10);
     
        fprintf(stderr,"%c",c);
    }
}
void print_char_from_bin(int* a,int len){
    int i=0;
    char c;
    for(i=0;i<len/8;i++){
        c=a[i*8]*128+a[i*8+1]*64+a[i*8+2]*32+a[i*8+3]*16+a[i*8+4]*8+a[i*8+5]*4+a[i*8+6]*2+a[i*8+7];
            printf("%c",c);
    }
}
void arrya_hex_to_bin(char* ppharse,int *key,int len){//hexstring to binary string
    int i,temp;
    for(i=0;i<len;i++){
        temp=hex_to_bin(ppharse[i]);
        key[i*4+3]=temp%2;
        temp/=2;
        key[i*4+2]=temp%2;
        temp/=2;
        key[i*4+1]=temp%2;
        temp/=2;
        key[i*4]=temp%2;
    }
}
void array_hex_to_bin(unsigned char* ppharse,unsigned int *key,int len,int rem){//char string to binary string
    unsigned int i,temp;
    //if(len!=8) fprintf(stderr,"%d %d",len,rem);
    for(i=0;i<len;i++){
        //if(len!=8) fprintf(stderr,"?");
        temp=ppharse[i];
        key[i*8+7]=temp%2;
        temp/=2;
        key[i*8+6]=temp%2;
        temp/=2;
        key[i*8+5]=temp%2;
        temp/=2;
        key[i*8+4]=temp%2;
        temp/=2;
        key[i*8+3]=temp%2;
        temp/=2;
        key[i*8+2]=temp%2;
        temp/=2;
        key[i*8+1]=temp%2;
        temp/=2;
        key[i*8]=temp%2;
    }
    for(i=len;i<len+rem;i++){
        //fprintf(stderr,"!");
        key[i*8+7]=0;
        temp/=2;
        key[i*8+6]=0;
        temp/=2;
        key[i*8+5]=0;
        temp/=2;
        key[i*8+4]=0;
        temp/=2;
        key[i*8+3]=0;
        temp/=2;
        key[i*8+2]=0;
        temp/=2;
        key[i*8+1]=0;
        temp/=2;
        key[i*8]=0;
    }
}
void key_schedule(char* ppharse,char* PC1,char* V,char* PC2,int K[16][48]){
    int key[64]={0};
    int C0[28],D0[28];
    int i=0,j,temp;
    arrya_hex_to_bin(ppharse,key,16);
    fprintf(stderr,"(C0,D0)=");
    for(i=0;i<28;i++){
        C0[i]=key[PC1[i]-1];
        
    }
    print_hex_from_bin(C0,28);
    for(i=0;i<28;i++){
        D0[i]=key[PC1[28+i]-1];
    }
    print_hex_from_bin(D0,28);
    fprintf(stderr,"\n");
    for(i=1;i<=16;i++){
        
        
        //ci=ci-1 <-- vi
        //Di=Di-1 <-- vi
        if (V[i-1]==1) {//  <--1
            leftshift(C0);
            leftshift(D0);
        }
        else{//  <--2
            leftshift(C0);
            leftshift(D0);
            leftshift(C0);
            leftshift(D0);
        }
        fprintf(stderr,"(C%d,D%d)=",i,i);
        print_hex_from_bin(C0,28);
        print_hex_from_bin(D0,28);
        
        
        //ki <- PC2(Ci,Di)
        fprintf(stderr,"\nk%d=",i);
        for(j=0;j<48;j++){
            temp=PC2[j]-1;
            if(temp<28)
            K[i-1][j]=C0[temp];
            else
            K[i-1][j]=D0[temp-28];
            
        }
        
        print_hex_from_bin(K[i-1],48);
        fprintf(stderr,"\n");
    }
    
}
void inverse(char* IP,char* IP1){
    int i;
    for(i=0;i<64;i++){
        IP1[IP[i]-1]=i+1;
    }
}
void encrypt(char *s,FILE* f,FILE* p,int decrypt){
    char PC1[56]={0};
    char PC2[48]={0};
    unsigned char input[8]={0};
    char V[16]={0};
    int K[16][48];
    char IP[64]={0};
    char IP1[64]={0};
    unsigned int m[64]={0};
     int L0[32]={0},R0[32]={0};
    int i=0,j,k,temp,c,r;
    char E[48]={0};
    char S[8][64];
    char P[32];
     int Rtemp[48]={0};
    char T[32]={0};
    char fun[32]={0};
    int output[64]={0};
    int outtemp[64]={0};
    int cc;
    int flag=0;
    int count=0;
    //fseek(f,0,SEEK_SET);
    
    if(tablecheck(f,PC1,V,PC2,IP,E,S,P)==false){
        fprintf(stderr,"malformed tablefile\n");
        return;
    }
    if(s[0]!='0'){
        fprintf(stderr,"malformed key\n");
        return;
    }
    key_schedule(s,PC1,V,PC2,K);
    while((cc=fgetc(p))!=EOF){
        
            input[count]=cc;
        
        
            count++;
        
            if (count==8) {
                
                    array_hex_to_bin(input,m,8,0);


                
                for(i=0;i<32;i++){
                    L0[i]=m[IP[i]-1];//  IP (m1m2...m64)
                }
                
                for(i=32;i<64;i++){
                    R0[i-32]=m[IP[i]-1];
                }
                if (flag==0) {
                    fprintf(stderr,"(L0,R0)=");
                    print_hex_from_bin(L0,32);
                    print_hex_from_bin(R0,32);
                    fprintf(stderr,"\n");
                }
                
                for(i=0;i<16;i++){
                    for(j=0;j<48;j++)
                    {
                        if(decrypt==0){
                        Rtemp[j]=(R0[E[j]-1]+K[i][j])%2;//  E(Ri-1)+ki
                        }else{
                            
                            Rtemp[j]=(R0[E[j]-1]+K[15-i][j])%2;
                        }
                        
                    }
                    
                    for(j=0;j<8;j++){
                        r=Rtemp[j*6]*2+Rtemp[j*6+5];//r and c
                        c=0;
                        temp=8;
                        for(k=1;k<5;k++){
                            
                            c+=Rtemp[j*6+k]*temp;
                            temp/=2;
                        }
                        temp=S[j][r*16+c];// Sbox
                        T[j*4+3]=temp%2;
                        temp/=2;
                        T[j*4+2]=temp%2;
                        temp/=2;
                        T[j*4+1]=temp%2;
                        temp/=2;
                        T[j*4]=temp%2;
                    }
                    for(j=0;j<32;j++){
                        fun[j]=T[P[j]-1];//P permutation
                    }
                    for(j=0;j<32;j++){
                        Rtemp[j]=(L0[j]+fun[j])%2;//L0 +
                    }
                    if (flag==0) {
                        fprintf(stderr,"(L%d,R%d)=",i+1,i+1);
                        
                        print_hex_from_bin(R0,32);
                        print_hex_from_bin(Rtemp,32);
                        fprintf(stderr,"\n");
                    }
                    if(i!=15){
                        for(j=0;j<32;j++){
                            L0[j]=R0[j];
                        }
                        for(j=0;j<32;j++){
                            R0[j]=Rtemp[j];
                        }
                    }
                }
                inverse(IP,IP1);
                for(i=0;i<64;i++){
                    if(i<32)
                        outtemp[i]=Rtemp[i];
                    else
                        outtemp[i]=R0[i-32];
                }
                
                
                for(i=0;i<64;i++){
                    output[i]=outtemp[IP1[i]-1];
                    
                }
                
                
                print_char_from_bin(output,64);
                
                flag=1;
                count=0;
            }

    }
    if(count>0){
        
        array_hex_to_bin(input,m,count,8-count);
        
        for(i=0;i<32;i++){
            L0[i]=m[IP[i]-1];//  IP (m1m2...m64)
        }
        
        for(i=32;i<64;i++){
            R0[i-32]=m[IP[i]-1];
        }
        if (flag==0) {
            fprintf(stderr,"(L0,R0)=");
            print_hex_from_bin(L0,32);
            print_hex_from_bin(R0,32);
            fprintf(stderr,"\n");
        }
        
        for(i=0;i<16;i++){
            for(j=0;j<48;j++)
            {
                if(decrypt==0){
                    Rtemp[j]=(R0[E[j]-1]+K[i][j])%2;//  E(Ri-1)+ki
                }else{
                    
                    Rtemp[j]=(R0[E[j]-1]+K[15-i][j])%2;
                }
                
            }
            
            for(j=0;j<8;j++){
                r=Rtemp[j*6]*2+Rtemp[j*6+5];//r and c
                c=0;
                temp=8;
                for(k=1;k<5;k++){
                    
                    c+=Rtemp[j*6+k]*temp;
                    temp/=2;
                }
                temp=S[j][r*16+c];// Sbox
                T[j*4+3]=temp%2;
                temp/=2;
                T[j*4+2]=temp%2;
                temp/=2;
                T[j*4+1]=temp%2;
                temp/=2;
                T[j*4]=temp%2;
            }
            for(j=0;j<32;j++){
                fun[j]=T[P[j]-1];//P permutation
            }
            for(j=0;j<32;j++){
                Rtemp[j]=(L0[j]+fun[j])%2;//L0 +
            }
            if (flag==0) {
                fprintf(stderr,"(L%d,R%d)=",i+1,i+1);
                
                print_hex_from_bin(R0,32);
                print_hex_from_bin(Rtemp,32);
                fprintf(stderr,"\n");
            }
            if(i!=15){
                for(j=0;j<32;j++){
                    L0[j]=R0[j];
                }
                for(j=0;j<32;j++){
                    R0[j]=Rtemp[j];
                }
            }
        }
        inverse(IP,IP1);
        for(i=0;i<64;i++){
            if(i<32)
                outtemp[i]=Rtemp[i];
            else
                outtemp[i]=R0[i-32];
        }
        
        
        for(i=0;i<64;i++){
            output[i]=outtemp[IP1[i]-1];
            
        }
        
        
        print_char_from_bin(output,64);


    }
    return;

}



