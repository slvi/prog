#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in server;
	char buf[21];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], &server.sin_addr);

	connect(sockfd, (const struct sockaddr *)&server, sizeof(server));

	memset(buf, '\0', sizeof(buf));
	recv(sockfd, buf, sizeof(buf), 0);

	printf("Coordinator : %s\n", buf);

	printf("Attempting transaction...\n");
	sleep(2);
	printf("Writing to undo log and redo log\n");
	sleep(1);
	
	printf("Was transaction successful? : ");
	scanf("%s", buf);
	send(sockfd, buf, strlen(buf),0);

	memset(buf, '\0', sizeof(buf));
	recv(sockfd, buf, sizeof(buf), 0);

	printf("Coordinator : %s\n", buf);

	if (!strcmp(buf, "Commit"))
	{
		printf("Completing transaction...\n");
		sleep(1);
		printf("Locks released. Transaction complete.\n");
	}
	else
	{
		printf("Undoing transaction...\n");
		sleep(1);
		printf("Transaction undone.\n");
	}

	send(sockfd, "Done", strlen(buf), 0);

	printf("Acknowledgemnt sent.\n");

	close(sockfd);

	return 0;
}
