#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void displayOptions(char *progname){

  printf("%s ip1.port1 ip2.port2 slaves [resultinreturn]\r\n if resultinreturn is set nothing is printed, result is in return value \r\nexample: %s 192.168.1.1.2332 192.168.1.2.80 3\r\n",progname,progname);

}


int main(int argc, char **argv)
{
  unsigned int s;
  unsigned int ip1,ip2,port1,port2;
  unsigned int p[6];
  char resultinreturn = 0;
 
  if(argc<4){
    displayOptions(argv[0]);
    return 0;
  }

  if(argc>4){
    resultinreturn = argv[4][0]-'0';
  }

  if(sscanf(argv[1],"%u.%u.%u.%u.%u",&p[0],&p[1],&p[2],&p[3],&port1) != 5){
    printf("format error\r\n");
    displayOptions(argv[0]);
    return 0;
  }
  ip1 = ((unsigned int)p[0]<<(3*8))+((unsigned int)p[1]<<(2*8))+((unsigned int)p[2]<<(1*8))+((unsigned int)p[3]<<(0*8));

  if(sscanf(argv[2],"%u.%u.%u.%u.%u",&p[0],&p[1],&p[2],&p[3],&port2) != 5){
    printf("format error\r\n");
    displayOptions(argv[0]);
    return 0;
  }  
  ip2 = ((unsigned int)p[0]<<(3*8))+((unsigned int)p[1]<<(2*8))+((unsigned int)p[2]<<(1*8))+((unsigned int)p[3]<<(0*8));


  s  = (unsigned int)strtol(argv[3], (char **)NULL,0);

  if(!resultinreturn){
    printf("((%d xor %d) xor ((",port1,port2);
    printf("%u.%u.%u.%u",(ip1>>(8*3))&0xFF,(ip1>>(8*2))&0xFF,(ip1>>(8*1))&0xFF,(ip1>>(8*0))&0xFF);
    printf("xor");
    printf("%u.%u.%u.%u)",(ip2>>(8*3))&0xFF,(ip2>>(8*2))&0xFF,(ip2>>(8*1))&0xFF,(ip2>>(8*0))&0xFF);
    printf("AND 0xFFFF)) mod %d",s);
    printf("=");
    printf("%d",((port1^port2)^((ip1^ip2)&0xFFFF))%s); 
    printf("\r\n");
    return 0;
  }else{
    return ((port1^port2)^((ip1^ip2)&0xFFFF))%s;
  }
}
