#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */

int main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n,counter=1;
  	char  	str[MAXLINE],oldname[1024],newname[1024];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

  	FILE *fptr1;
  	WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用

	  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

	   	//指定 socket 的 IP 位址和 port number
	   	serv.sin_family      = AF_INET;
	   	serv.sin_addr.s_addr = 0;
	   	serv.sin_port        = htons(5678);	// 指定 IPPORT_ECHO 為 echo port


	    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

	   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態

	   	cli_len = sizeof(cli);


		printf("server: waiting for client\n");

		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

	while(1)
	{
		printf("請輸入被寫入的檔案名稱： \n ");
	   	gets(oldname);
		fptr1=fopen(oldname,"w");

	   if( fptr1!=NULL)
	   {
		while( 1 ) {

			    n=recv(cli_sd, str, MAXLINE, 0);
			    sleep(1);


				str[n]='\0';
			    printf("[%d] recv:%s  (size:%d) \n",counter,str,n);

				fputs(str,fptr1);

			    counter++;

			     if (str[strlen(str)-1]==EOF){
					puts("file end");
			    	break;
				}
				}
				fclose(fptr1);

	   	}//end if

	}


	    closesocket(cli_sd);
	   	closesocket(serv_sd);

	   	WSACleanup();
   	system("pause");
   	return 0;
}
