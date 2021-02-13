#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <stdio.h>
 
#define PORT 2080
 
main()
{
	int sock1,sock2, clength,valread;
	sock1 =  socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serv,cli;
 
	//struct sockaddr_in server,client;

    memset(&serv,0,sizeof(serv));
    memset(&cli,0,sizeof(cli));

	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sock1,(struct sockaddr *)&serv, sizeof(serv));
	listen(sock1,10);
	clength = sizeof(cli);
	int i=0;

	char buf[50];
	sock2 = accept(sock1,(struct sockaddr *)&cli,&clength);
	printf("\n Client Connected\n");
	printf("Waiting for file from client\n");
	//sleep(4);
	FILE* fp = fopen("server.txt","r");
	while(1){
		//bzero(buf,sizeof(buf));
		valread=read(sock2,buf,50);
		if(strcmp(buf,"end_of_file")==0)
		{
			break;
		}
		fprintf(fp,"%s",buf);
	}
	printf("File successfully recieved from client.\n");
	fclose(fp);
	return 0;
}
