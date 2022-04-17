#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8000

int main()
{
	int p, value, acf;

	struct sockaddr_in serveradd, clientadd;
	socklen_t clintlen;

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
    value = bind(p, (struct sockaddr *) &serveradd, sizeof(serveradd));
	if(value < 0)
	{
		perror("bind: ");
		exit(2);
	}

	listen(p, 5);

	acf = accept(p, (struct sockaddr *) &clientadd, &clintlen);
	if(acf < 0)
	{
		perror("accept: ");
		exit(3);
	}
	printf("Client Connected\n");

	while(1)
	{
		char buffer[100];
		int n;

		n = recv(acf, buffer, sizeof(buffer), 0);
		if(n < 0)
		{
			perror("recv: ");
			exit(4);
		}
		printf("Revceived Data From The Client : %s\n", buffer);
        for(int i=0; i<n; i++)
		{
			if(buffer[i] >= 'a' && buffer[i] <= 'z')
				buffer[i] -= 32;
			else 
				buffer[i] += 32;
		}

		send(acf, buffer, strlen(buffer), 0);
		printf("Data Sended To The Client\n");
	}	

	close(p);
	return 0;
}