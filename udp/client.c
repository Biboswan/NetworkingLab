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
struct sockaddr_in serv;

void *receiveThread() {
	char buffer[MAXLINE];
	int n,len;
	while(1) {
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&serv, &len);
		if(n==-1) continue;
		buffer[n] = '\0';
		printf("Servo: %s\n",buffer);
	}
}

void *sendThread() {
	char msg[100];
	while(1) {
		scanf("%s\n",msg);		
		sendto(sockfd, (char *)msg, strlen(msg), MSG_CONFIRM, (struct sockaddr *)&serv, sizeof(serv));
	}
}

int main() {
	pthread_t thread_id1, thread_id2;
		
	printf("VeChat\n");

	if (sockfd = socket(AF_INET, SOCK_DGRAM,0)<0) 	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&serv, 0, sizeof(serv));

	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	serv.sin_addr.s_addr = INADDR_ANY;
	pthread_create(&thread_id2,NULL,sendThread,NULL);
	pthread_create(&thread_id1,NULL,receiveThread,NULL);
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	close(sockfd);
	return 0;
}
