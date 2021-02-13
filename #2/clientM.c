#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <stdio.h>
 
#define PORT 2080
 
main()
{
	int sock1;
	sock1 =  socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serv;
 
	//struct sockaddr_in client;
    memset(&serv,0,sizeof(serv));

	serv.sin_port = htons(PORT);
	//printf("%x %x\n",PORT,htons(PORT));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("client connecting\n");
	connect(sock1, (struct sockaddr *)&serv,sizeof(serv));
	char buf[50];
	printf("Uploading file to server\n");
	//sleep(3);
	FILE* fp = fopen("client.txt","r");
	while(!feof(fp)){
		//bzero(buf,sizeof(buf));
		fread(buf,sizeof(char),50,fp);
		write(sock1,buf,50);
	}
	write(sock1,"end_of_file",50);
	printf("File Successfully uploaded to Server\n");
	fclose(fp);
}
