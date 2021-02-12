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
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // SOCKET CONFIG
    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // CONNECTION
    cout << "client connecting..\n";
    if (connect(sock, (sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Cant Connect");
        exit(-1);
    }
    cout << "connected.\n";

    // LOGIC
    char buffer[BUFFER_SIZE];

    char *filename = "SocialMedia.png";

    ifstream file(filename, ios::binary);

    while (!file.eof())
    {
        file.read(buffer, BUFFER_SIZE);
        write(sock, buffer, BUFFER_SIZE);
    }

    write(sock, "FILE_END", BUFFER_SIZE);

    cout << "file sent.";

    file.close();

    return 0;
}