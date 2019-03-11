/* Write a C program to implement TCP Socket. Client will take a bit stream from user, send it to server.
Server will implement bit stuffing and send the stream back to client. Client will print it.*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

int main() {
char stream[100];
	struct sockaddr_in s;
    int cid=socket(AF_INET, SOCK_STREAM,0);
    s.sin_family=AF_INET;
    s.sin_port=htons(1236);
    inet_aton("127.0.0.1", &s.sin_addr);
    connect(cid, (struct sockaddr*)&s, sizeof(s));
    printf("Enter bit stream\n");
    fgets(stream,100,stdin);
    write(cid, stream, strlen(stream)+1);
    int l=read(cid,stream, sizeof(stream));
    puts(stream);
    close(cid);
    return 0;
}
	
