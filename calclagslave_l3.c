#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void displayOptions(char *progname){

  printf("%s port1 port2 ip1 ip2 slaves \r\n example: %s 80 12123 192.168.1.1 192.168.1.2 3\r\n",progname,progname);

}


int main(int argc, char **argv)
{
  unsigned int s;
  unsigned int ip1,ip2,port1,port2;
  unsigned char p[6];
 
  if(argc<6){
    displayOptions(argv[0]);
    return 0;
  }

  port1 = (unsigned int)strtol(argv[1], (char **)NULL,0);
  port2 = (unsigned int)strtol(argv[2], (char **)NULL,0);

  if(sscanf(argv[3],"%u.%u.%u.%u",&p[0],&p[1],&p[2],&p[3]) != 4){
    printf("format error\r\n");
    displayOptions(argv[0]);
    return 0;
  }
  ip1 = ((unsigned int)p[0]<<(3*8))+((unsigned int)p[1]<<(2*8))+((unsigned int)p[2]<<(1*8))+((unsigned int)p[3]<<(0*8));

  if(sscanf(argv[4],"%u.%u.%u.%u",&p[0],&p[1],&p[2],&p[3]) != 4){
    printf("format error\r\n");
    displayOptions(argv[0]);
    return 0;
  }  
  ip2 = ((unsigned int)p[0]<<(3*8))+((unsigned int)p[1]<<(2*8))+((unsigned int)p[2]<<(1*8))+((unsigned int)p[3]<<(0*8));


  s  = (unsigned int)strtol(argv[5], (char **)NULL,0);

  printf("((%d xor %d) xor ((",port1,port2);
  printf("%u.%u.%u.%u",(ip1>>(8*3))&0xFF,(ip1>>(8*2))&0xFF,(ip1>>(8*1))&0xFF,(ip1>>(8*0))&0xFF);
  printf("xor");
  printf("%u.%u.%u.%u)",(ip2>>(8*3))&0xFF,(ip2>>(8*2))&0xFF,(ip2>>(8*1))&0xFF,(ip2>>(8*0))&0xFF);
  printf("AND 0xFFFF)) mod %d",s);
  printf("=%d\r\n",((port1^port2)^((ip1^ip2)&0xFFFF))%s); 
}
