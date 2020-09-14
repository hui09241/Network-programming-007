#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define MAXLINE 1024    /* �r��w�İϪ��� */

int main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n,counter=1;
  	char  	str[MAXLINE],oldname[1024],newname[1024];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

  	FILE *fptr1;
  	WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�

	  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

	   	//���w socket �� IP ��}�M port number
	   	serv.sin_family      = AF_INET;
	   	serv.sin_addr.s_addr = 0;
	   	serv.sin_port        = htons(5678);	// ���w IPPORT_ECHO �� echo port


	    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

	   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A

	   	cli_len = sizeof(cli);


		printf("server: waiting for client\n");

		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

	while(1)
	{
		printf("�п�J�Q�g�J���ɮצW�١G \n ");
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
