#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void displayOptions(char *progname){

  printf("%s mac1 mac2 slaves [resultinreturn]\r\n if resultinreturn is set, nothing will be printed. Result will be in returnvalue\\r\n\r\nexample: %s 00:01:02:03:04:05 02:03:04:05:06:07 3\r\n",progname,progname);

}

void stringtolower(char *string)
{
   int i;

   for(i=0;i<strlen(string);i++)
   {
      string[i] = tolower(string[i]);
   }

}

int main(int argc, char **argv)
{
  unsigned int s;
  unsigned long long m1,m2;
  unsigned char p[6];
  char string[100];
  int sizeofll = sizeof(m1);
  char answerinreturn = 0;
 
  if(sizeofll < 6){
    printf("longlong to small on this system to contain a macaddress");
    return 0;
  }

  if(argc<4){
    displayOptions(argv[0]);
    return 0;
  }

 if(argc>4 ){
   answerinreturn=argv[4][0]-'0';
 }

  strcpy(string,argv[1]);
  stringtolower(string); 

  if(sscanf(string,"%02x:%02x:%02x:%02x:%02x:%02x",&p[0],&p[1],&p[2],&p[3],&p[4],&p[5]) != 6){
    printf("format error\r\n");
    displayOptions(argv[0]);
    return 0;
  }

   m1 = ((unsigned long long)p[0]<<(5*8))+((unsigned long long)p[1]<<(4*8))+((unsigned long long)p[2]<<(3*8))+((unsigned long long)p[3]<<(2*8))+((unsigned long long)p[4]<<(1*8))+((unsigned long long)p[5]<<(0*8));


  strcpy(string,argv[2]);
  stringtolower(string);

  if(sscanf(string,"%02x:%02x:%02x:%02x:%02x:%02x",&p[0],&p[1],&p[2],&p[3],&p[4],&p[5]) != 6){
    printf("format error\r\n");
    displayOptions(argv[0]);
    return 0;
  }
  m2 = ((unsigned long long)p[0]<<(5*8))+((unsigned long long)p[1]<<(4*8))+((unsigned long long)p[2]<<(3*8))+((unsigned long long)p[3]<<(2*8))+((unsigned long long)p[4]<<(1*8))+((unsigned long long)p[5]<<(0*8));

  s  = (unsigned int)strtol(argv[3], (char **)NULL,0);

  if(!answerinreturn)
  {
    printf("%02X:%02X:%02X:%02X:%02X:%02X",(m2>>(5*8))&0xFF,(m2>>(4*8))&0xFF,(m2>>(3*8))&0xFF,(m2>>(2*8))&0xFF,(m2>>(1*8))&0xFF,(m2>>(0*8))&0xFF);
    printf(" xor ");
    printf("%02X:%02X:%02X:%02X:%02X:%02X",(m1>>(5*8))&0xFF,(m1>>(4*8))&0xFF,(m1>>(3*8))&0xFF,(m1>>(2*8))&0xFF,(m1>>(1*8))&0xFF,(m1>>(0*8))&0xFF); 
    printf(" mod %d = ",s);
    printf("%d",(m1^m2)%s); 
    printf("\r\n");
    return 0;
  }else{
    return (m1^m2)%s;
  }
}
