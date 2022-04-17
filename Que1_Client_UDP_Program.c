#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 800

int main()
{
	int p, value;

	struct sockaddr_in serveradd;

	p = socket(AF_INET, SOCK_DGRAM, 0);
	if(p < 0)
	{
		perror("socket: ");
		exit(1);
	}

	bzero(&serveradd, sizeof(serveradd));
	serveradd.sin_family = AF_INET;
	serveradd.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveradd.sin_port = htons(PORT);

	connect(p, (struct sockaddr *) &serveradd, sizeof(serveradd));
	
	printf("...............Client Connecting To Server...............\n\n");


	while(1)
	{
		char buffer[100];
		int n;

		printf("Enter The Message  Send To On Server : \n");
		gets(buffer);
		send(p, buffer, strlen(buffer), 0);
		printf("Data Sent To The Server \n");
        n = recv(p, buffer, sizeof(buffer), 0);
		
		if(n < 0)
		{
			perror("recv: ");
			exit(4);
		}
		printf("Received The Data From Server : %s\n", buffer);		
	}	

	close(p);
	return 0;
}