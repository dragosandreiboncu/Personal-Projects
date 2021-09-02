#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "helpers.h"
#pragma pack(push,1)
typedef struct list
{
	char elem[50];
	struct list *next;
} List;

int contain_list(List *head, char *x)
{
	List *buf = head;
	while(buf != NULL)
	{
		if(strcmp(buf->elem, x) == 0)
		{
			return 1;
		}
		buf = buf->next;
	}
	return 0;
}
List* add_list(List *head, char *x)
{
	if(contain_list(head, x) == 1)
	{
		return head;
	}
	if(head == NULL)
	{
		head = (List*)malloc(sizeof(List));
		head->next = NULL;
		strcpy(head->elem, x);
		return head;
	}
	List *buf = head;
	while(buf->next != NULL)
	{
		buf = buf->next;
	}
	buf->next =  (List*)malloc(sizeof(List));
	buf->next->next = NULL;
	strcpy(buf->next->elem, x);
	return head;
}
List* delete_list(List *head, char *x)
{
	if(head == NULL)
	{
		return head;
	}
	List *buf = head;
	if(strcmp(buf->elem, x) == 0)
	{
		buf = head->next;
		free(head);
		return buf;
	}
	while(buf->next != NULL)
	{
		if(strcmp(buf->next->elem, x) == 0) {
			buf->next = buf->next->next;
			free(buf->next);
			break;
		}
		buf = buf->next;
	}
	return head;
}




typedef struct 
{
	char topic[50];
	unsigned char data_type;
	char content[1500];
} UDP_message;


typedef struct
{
	char ID[10];
	List *preferences;
} Subscriber;
#pragma pack(pop)


int main(int argc, char *argv[]) {
	
	int socket_UDP;
	int socket_TCP, new_socket_TCP;

	struct sockaddr_in TCP_address, new_TCP_address;
	struct sockaddr_in UDP_address;


	UDP_message message;

	fd_set read_fd;
	fd_set buffer_fd;	
	FD_ZERO(&read_fd);
	FD_ZERO(&buffer_fd);

	int out1, out2;
	socklen_t UDP_address_size = sizeof(UDP_address);

	socket_TCP = socket(PF_INET, SOCK_STREAM, 0);
	socket_UDP = socket(AF_INET, SOCK_DGRAM, 0);
	
	// Setare struct sockaddr_in pentru a asculta pe portul respectiv
	memset((char *) &TCP_address, 0, sizeof(TCP_address));
	TCP_address.sin_family = AF_INET;
	TCP_address.sin_port = htons(atoi(argv[1]));
	TCP_address.sin_addr.s_addr = INADDR_ANY;

	UDP_address.sin_family = AF_INET;
	UDP_address.sin_port = htons(atoi(argv[1]));
	UDP_address.sin_addr.s_addr = INADDR_ANY;

	out1 = bind(socket_UDP, (struct sockaddr*) &UDP_address, sizeof(struct sockaddr_in));
	DIE(out1 < 0, "bind");
	out1 = bind(socket_TCP, (struct sockaddr *) &TCP_address, sizeof(struct sockaddr_in));
	DIE(out1 < 0, "bind");
	
	out1 = listen(socket_TCP, 10);
	DIE(out1 < 0, "listen");

	FD_SET(socket_TCP, &read_fd);
	FD_SET(socket_UDP, &read_fd);



	Subscriber *subscribers = NULL;

	int *visited = NULL;
	char buffer[1500];
	int fd_limit = socket_TCP;

    while (1) {

    	subscribers = realloc(subscribers, (fd_limit + 1) * sizeof(Subscriber));
    	visited = realloc(visited, (fd_limit + 1) * sizeof(int));

		buffer_fd = read_fd;
		out1 = select(fd_limit + 1, &buffer_fd, NULL, NULL, NULL);
		DIE(out1 < 0, "select");
		
		for (int i = 0; i <= fd_limit; i++) 
		{
			if (FD_ISSET(i, &buffer_fd)) 
			{
				// Noii useri TCP sunt acceptati in aplicatie
				if (i == socket_TCP) 
				{
					socklen_t new_TCP_address_size = sizeof(new_TCP_address);
					new_socket_TCP = accept(socket_TCP, (struct sockaddr *) &new_TCP_address,
														&new_TCP_address_size);
					DIE(new_socket_TCP < 0, "accept");

					FD_SET(new_socket_TCP, &read_fd);
					if (new_socket_TCP > fd_limit) 
					{
						fd_limit = new_socket_TCP;
					}
				}


				// Primeste informatii de la UDP
				else if (i == socket_UDP)
				{
					// Primeste informatii de la UDP
					int message_read = recvfrom(socket_UDP, &message, sizeof(UDP_message), 0,
												(struct sockaddr*) &UDP_address, &UDP_address_size);
					DIE(message_read < 0, "read");
					if (strstr(message.topic, "exit")) 
					{
						break;
					}
					// Mesaj de forma: IP:PORT client_UDP - topic - tip_date - valoare mesaj
					char message_for_subscriber[1650];

					if (message.data_type == 0)
					{
						int sign = message.content[0];
						if ( sign == 0 ) 
						{
							sign--;
						}
						uint32_t *buf = (uint32_t *)&message.content[1];
						sprintf(message_for_subscriber, "%s:%d - %s - %s - %d\n", inet_ntoa(UDP_address.sin_addr),
								ntohs(UDP_address.sin_port), message.topic, "INT", sign * (-1) * ntohl(*buf));
					}
					else if (message.data_type == 1)
					{
						uint16_t *buf = (uint16_t *)&message.content;
						sprintf(message_for_subscriber, "%s:%d - %s - %s - %.2f\n", inet_ntoa(UDP_address.sin_addr),
								ntohs(UDP_address.sin_port), message.topic, "SHORT-REAL", ntohs(*buf) / 100.0);
					}
					if (message.data_type == 2)
					{
						int sign = message.content[0];
						if ( sign == 0 ) 
						{
							sign--;
						}
						uint32_t *nr = (uint32_t *)&message.content[1];
						uint8_t *comma = (uint8_t *)&message.content[5];
						float float_divide = (float)(ntohl(*nr));
						for (int i = 0; i < *comma; i++) 
						{
							float_divide = float_divide * 0.1;
						}
						sprintf(message_for_subscriber, "%s:%d - %s - %s - %.4f\n", inet_ntoa(UDP_address.sin_addr),
								ntohs(UDP_address.sin_port), message.topic,
								"FLOAT", (float)(sign) * (float)(-1) * float_divide);
					}
					else if (message.data_type == 3)
					{
						sprintf(message_for_subscriber, "%s:%d - %s - %s - %s\n", inet_ntoa(UDP_address.sin_addr),
								ntohs(UDP_address.sin_port), message.topic,
								"STRING", message.content);
					}
					// printf("%s", message_for_subscriber);  // printeaza in server postarile userilor UDP
					for (int k = 0; k <= fd_limit; k++) 
					{

						if (contain_list(subscribers[k].preferences, message.topic) == 1)
						{
							out2 = send(k, message_for_subscriber, strlen(message_for_subscriber) - 1, 0);
            				DIE(out2 < 0, "send");
						}
					}
				}

				// Userii TCP interactioneaza cu aplicatia
				else 
				{
					memset(buffer, 0, BUFLEN);
					out2 = recv(i, buffer, sizeof(buffer), 0);
					DIE(out2 < 0, "recv");

					if (out2 == 0) 
					{
						printf("Client %s disconnected.\n", subscribers[i].ID);
						close(i);
						FD_CLR(i, &read_fd);
					} 
					else 
					{
						if (visited[i] != 1) 
						{
							// Primeste ID-ul ca mesaj + mesajul cu New client va fii afisat doar odata
							strncpy(subscribers[i].ID, buffer, 10);
							subscribers[i].preferences = NULL;
							printf("New client %s, connected from %s:%d. \n", subscribers[i].ID,
								inet_ntoa(new_TCP_address.sin_addr), ntohs(new_TCP_address.sin_port));
							visited[i] = 1;
						}
						else
						{
							char **buffer_command = NULL;
							int k = 0;
   							char *token = strtok(buffer, " ");
  							while (token != NULL) 
  							{
  								buffer_command = realloc(buffer_command, (k + 1) * sizeof(char*));
      							buffer_command[k] = malloc(50 * sizeof(char));
  								strncpy(buffer_command[k], token, strlen(token));
  								k++;
      							token = strtok(NULL, " ");
   							}
   							if (strcmp(buffer_command[0], "subscribe") == 0)
   							{
   								char *notification1 = NULL;
   								notification1 = malloc(strlen(buffer_command[1]) * sizeof(char));
   								strncpy(notification1, buffer_command[1], strlen(buffer_command[1]) - 3 + k);
   								subscribers[i].preferences = add_list(subscribers[i].preferences, notification1);
   								printf("Client %s subscribed to %s.\n", subscribers[i].ID, notification1);

   								char notification2[100];
   								strcpy(notification2, "You subscribed to ");
   								strncat(notification2, notification1, strlen(buffer_command[1]) - 3 + k);
   								strcat(notification2, ".");
   								out2 = send(i, notification2, strlen(buffer_command[1]) + 18, 0);
   														// 18 este dimensiunea stringului: You subscribed to
            					DIE(out2 < 0, "send");
	
   							}
   							if (strcmp(buffer_command[0], "unsubscribe") == 0)
   							{
   								char *notification1 = NULL;
   								notification1 = malloc(strlen(buffer_command[1]) * sizeof(char));
   								strncpy(notification1, buffer_command[1], strlen(buffer_command[1]) - 1);
   								subscribers[i].preferences = delete_list(subscribers[i].preferences, notification1);
   								printf("Client %s unsubscribed from %s.\n", subscribers[i].ID, notification1);

   								char notification2[100];
   								strcpy(notification2, "You unsubscribed from ");
   								strncat(notification2, notification1, strlen(buffer_command[1]) - 1);
   								strcat(notification2, ".");
   								out2 = send(i, notification2, strlen(buffer_command[1]) + 22, 0);
   													// 22 este dimensiunea stringului: You unsubscribed from
            					DIE(out2 < 0, "send");
   							}
						}
					}
				}
			}
		}
	}

	close(socket_UDP);
	close(socket_TCP);
	return 0;
}
