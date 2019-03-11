#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

int main() {

 char stream[100], d[100];
 int c1=0,i=0,j=0;
 int sid=socket(AF_INET, SOCK_STREAM,0);
 struct sockaddr_in s,c;
 s.sin_family=AF_INET;
 s.sin_port=htons(1236);
 inet_aton("127.0.0.1", &s.sin_addr);
 bind(sid, (struct sockaddr*)&s, sizeof(s));
 listen(sid, 1);
 int l =sizeof(c);
 int cid=accept(sid, (struct sockaddr*)&c, &l);
 int n=read(cid, stream, sizeof(stream));
 for(i=0;stream[i]!='\0';i++) {
 	if (stream[i]=='0') {
 		c1=0;
 		d[j++]='0';
 	} else if(stream[i] == '1') {
 		c1++;
 		d[j++]='1';
 		if (c1==5) {
 			d[j++]='0';
 			c1=0;
 		}
 	}
}
 	d[i]='\0';
 	write(cid,d,strlen(d)+1);
 	close(cid);
 	close(sid);
 	return 0;
}
