#include <sys/types.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
#define PORT 2021
#define BUFFER_SIZE 2048

int main(int argc, char const *argv[])
{
    int sock1, sock2, clength;
    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv, cli;

    // sockaddr_in server,client;

    memset(&serv, 0, sizeof(serv));
    memset(&cli, 0, sizeof(cli));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sock1, (sockaddr *)&serv, sizeof(serv));
    listen(sock1, 5);
    cout << "listening\n";
    int i = 0;

    socklen_t client_len = sizeof(cli);

    char buffer[BUFFER_SIZE];
    sock2 = accept(sock1, (sockaddr *)&cli, &client_len);

    printf("\n Client Connected\n");
    printf("recieving Files from Cleint\n");

    ofstream file("image.png", ios::binary);
    while (true)
    {
        //bzero(buf,sizeof(buf));
        // fread(buffer, sizeof(char), BUFFER_SIZE, fp);

        read(sock2, buffer, BUFFER_SIZE);
        if (strcmp(buffer, "FILE_END") == 0)
        {
            break;
        }
        file.write(buffer, BUFFER_SIZE);
    }
    file.close();
    return 0;

    return 0;
}