#include <stdio.h>
#include <string.h>
#include <winsock.h>
#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024],newname[1024],oldname[1024],end[2]={EOF,'\0'};
   char c;
   WSADATA 		wsadata;
   int counter=1;
   FILE *fptr1;
   char ch;
   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�

   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   //���s�u�@�ǳơA�]�t��g sockaddr_in ���c (serv) �C
   //���e���Gserver �� IP ��}�Aport number �����C
   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server

   while(1)
   {
   	printf("�п�J�QŪ���ɮצW�١G \n ");
   	gets(oldname);

   	fptr1=fopen(oldname,"r");
   if( fptr1!=NULL)
   {

	   	while( (ch=getc(fptr1))!=EOF)
	   {

	   str[0]=ch;
	   //str[1]='\0';
	   send(sd, str, 1, 0);
	   printf("[%d] send: %c \n" ,counter,str[0]);
	   //sleep(1);
	   counter++;
	    }//end while
	    send(sd,end,2,0);
		printf("�����ɮ� %s �ǰe\n",oldname);
		fclose(fptr1);

   }//end if
   }
   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�
   system("pause");

   return 0;
}
