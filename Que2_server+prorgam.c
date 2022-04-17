#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

void handleClient(int connfd)
{
	int n;
	char buffer[200];

	n = read(connfd, buffer, 200);
	buffer[n] = '\0';

	printf("Data Record From The Client : %s\n",buffer);
	printf("\nRequested Handled By The Server: %d\n",getpid());
	write(connfd, "Good bye", 8);

	printf("\nData Sended To The Client\n");
        exit(0);
}

int main()
{
	int sockfd, connfd, sockfd;
	pid_t childpid;

	socklen_t clilen;
	struct sockaddr_in clientaddr, servderadd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("sock: ");
		exit(1);
	}

	bzero(&servderadd, sizeof(servderadd));
	servderadd.sin_family = AF_INET;
	servderadd.sin_addr.s_addr = htonl(INADDR_ANY); 
	servderadd.sin_port = htons(8000); 
	sockfd = bind(sockfd, (struct sockaddr *) &servderadd, sizeof(servderadd));
	if(sockfd < 0)
	{
		perror("bind: ");
		exit(2);
	}

	listen(sockfd, 5);

	while(1)
	{
		char s_buf[200];
		char r_buf[200];
		pid_t p;

		int n;

		clilen = sizeof(clientaddr);
		connfd = accept(sockfd, (struct sockaddr *) &clientaddr, &clilen);
		printf("Client Connected\n");
		
		p = fork();
		if(p == 0)
		{
			close(sockfd);
			handleClient(connfd);
		}
		close(connfd);
	}
	return 0;
}