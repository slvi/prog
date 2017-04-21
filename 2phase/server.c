#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

struct client
{
	int i;
	pthread_t thread;
	int newsockfd;
	char message[11];
};

void *phase1(void *argp)
{
	struct client *ptr = argp;
	char buf[21] = {'\0'};	

	printf("Sending query to commit to Cohort#%d\n", ptr->i);
	send(ptr->newsockfd, "Commit?", strlen("Commit?"), 0);

	recv(ptr->newsockfd, buf, sizeof(buf), 0);
	
	strcpy(ptr->message, buf);
}

void *phase2(void *argp)
{
	struct client *ptr = argp;
	char buf[21] = {'\0'};	

	printf("Sending Consensus to Cohort#%d\n", ptr->i);
	send(ptr->newsockfd, ptr->message, strlen(ptr->message), 0);

	recv(ptr->newsockfd, buf, sizeof(buf), 0);

	strcpy(ptr->message, buf);
}

int main(int argc, char **argv)
{
	int sockfd, i, n = atoi(argv[2]);
	char decision[11];
	struct client clients[n];
	struct sockaddr_in server;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (const struct sockaddr *)&server, sizeof(server));
	
	listen(sockfd, 5);

	printf("Waiting for cohorts...\n");
	for(i = 0; i < n; i++)
	{
		clients[i].i = i;
		clients[i].newsockfd = accept(sockfd, NULL, NULL);
		printf("Cohort #%d connected.\n", i);
	}
	close(sockfd);
	printf("Cluster alive.\n");

	for(i = 0; i < n; i++)
		pthread_create(&(clients[i].thread), NULL, phase1, &clients[i]);

	for(i = 0; i < n; i++)
		pthread_join(clients[i].thread,NULL);

	strcpy(decision, "Commit");
	for(i = 0; i < n; i++)
	{
		if(!strcmp(clients[i].message, "No"))
		{
			strcpy(decision, "Rollback");
			break;
		}
	}
	for(i = 0; i < n; i++)
		strcpy(clients[i].message, decision);

	for(i = 0; i < n; i++)
		pthread_create(&(clients[i].thread), NULL, phase2, &clients[i]);

	for(i = 0; i < n; i++)
	{
		pthread_join(clients[i].thread, NULL);

		printf("Client #%d : %s\n", i, clients[i].message);
		close(clients[i].newsockfd);
	}

	if(!strcmp(decision, "Commit"))
		printf("Transaction complete.\n");
	else
		printf("Transaction undone.\n");;

	return 0;
}
