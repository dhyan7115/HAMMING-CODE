#include<stdio.h>
#include<math.h>
int calculateParity(int pos,int code[],int n){
    int parity = 0;
    for(int i=1;i<=n;i++){
        if(i&pos){
            parity ^= code[i];
        }
    }
    return parity;
}
int main(){
    int n;
    printf("Enter the Number of Bits : ");
    scanf("%d",&n);
    char arr[n];
    printf("Enter the Message : ");
    scanf("%s",arr);
    int r = 0;
    while(pow(2,r)<(r+n+1)){
        r++;
    }
    printf("Number of Redundant Bits : %d\n",r);
    int total = r+n;
    int codeword[total+1];
    for(int i=1,j=0;i<=total;i++){
        if((i&(i-1))==0){
            codeword[i] = 0;
        }
        else{
            codeword[i] = arr[j++]-'0';
        }
    }
    for(int i=0;i<r;i++){
        int pos = 1<<i;
        codeword[pos] = calculateParity(pos,codeword,total);
    }
    printf("Codeword to be Sent : ");
    for(int i=total;i>0;i--){
        printf("%d",codeword[i]);
    }
    printf("\n");
    char received[total+1];
    printf("Enter the Codeword Received : ");
    scanf("%s",received);
    int code[total+1];
    for(int i=total;i>0;i--){
        code[i] = received[total-i]-'0';
    }
    int errorPos = 0;
    for(int i=0;i<r;i++){
        int pos = 1<<i;
        int parity = calculateParity(pos,code,total);
        if(parity){
            errorPos += pos;
        }
    }
    if(errorPos){
        printf("Error at Position %d\n",errorPos);
    }
    else{
        printf("No Error Found\n");
    }
    return 0;
}