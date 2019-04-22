#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080
#define MAXLINE 1024

int sockfd;
struct sockaddr_in cln;

void *receiveThread() {
	char buffer[MAXLINE];
	int n,len;
	while(1) {
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cln, &len);
        if(n==-1) continue;
		buffer[n] = '\0';
		printf("Cliento: %s\n",buffer);
	}
}

void *sendThread() {
	char msg[100];
	while(1) {
		scanf("%s\n",msg);		
		sendto(sockfd, (char *)msg, strlen(msg), MSG_CONFIRM, (struct sockaddr *)&cln, sizeof(cln));
	}
}

int main() {
	pthread_t thread_id1, thread_id2;
    struct sockaddr_in servaddr;

	printf("VeChat\n");

	if (sockfd = socket(AF_INET, SOCK_DGRAM,0)<0) 	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cln, 0, sizeof(cln)); 
    
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)) == -1 ) { 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	pthread_create(&thread_id1,NULL,receiveThread,NULL);
	pthread_create(&thread_id2,NULL,sendThread,NULL);
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	close(sockfd);
	return 0;
}
