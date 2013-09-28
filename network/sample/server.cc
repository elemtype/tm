#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>//for sockaddr_in
#include <arpa/inet.h>//for socket
#include <iostream>
using namespace std;
int main()
{
 int fd=socket(AF_INET,SOCK_DGRAM,0);
 if(fd==-1)
 {
 perror("socket create error!\n");
 exit(-1);
 }
 printf("socket fd=%d\n",fd);


 struct sockaddr_in addr;
 addr.sin_family=AF_INET;
 addr.sin_port=htons(8000);
 addr.sin_addr.s_addr=inet_addr("127.0.0.1");


 int r;
 r=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
 if(r==-1)
 {
 printf("Bind error!\n");
 close(fd);
 exit(-1);
 }
 printf("Bind successfully.\n");
 
 char buf[255];
 struct sockaddr_in from;
 socklen_t len;
 len=sizeof(from);
 while(1)
 {
 r=recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&from,&len);
 if(r>0)
 {
 buf[r]=0;
 printf("The message received for %s is :%s\n",inet_ntoa(from.sin_addr),buf);
 }
 else
 {
 break;
 }
 string s = "GoodBye.";
   int status=sendto(fd,s.c_str(),r,0,(struct sockaddr*)&from,sizeof(from)); 
 if(status==-1)
 {
   break;
 }
 }
 close(fd);
 return 0;
}
