#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
int checkNumber(char *string, int len)
{
	if(len > 1 && string[0] == 48) 
	{
		return 1;
	}
	for(int i = 0; i < len; i++)
	{
		if(string[i] < 48 || string[i] > 57)
		{
			return 1;
		}
	}
	return 0;
}


int main(int argc, char *argv[])
{
    char *response;
    char *message;
    char *cookie = NULL;
    char *token = NULL;

    char *host = "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com";
    char *payload_type = "application/json";
    int port = 8080;

    char command[50];
    while(1)
	{
		int sockfd = open_connection("3.8.116.10", port, AF_INET, SOCK_STREAM, 0);
	    scanf("%s", command);
	    // Register
	    if(strcmp(command, "register") == 0)
	    {
	    	char **informations = NULL;
	    	informations = malloc(2 * sizeof(char*));
	    	informations[0] = malloc(150 * sizeof(char));
	    	informations[1] = malloc(150 * sizeof(char));
	    	printf("username=");
	    	scanf("%s", informations[0]);
	    	printf("password=");
	    	scanf("%s", informations[1]);
		    message = compute_post_request(host, "/api/v1/tema/auth/register", payload_type, informations, NULL, NULL);
		    printf("%s\n", message);
		    send_to_server(sockfd, message);
		    response = receive_from_server(sockfd);
		    if(strstr(response, "Bad Request"))
		    {
		    	printf("Username %s is already taken.\n\n", informations[0]);
		    }
		    else
		    {
		    	printf("Register succesfully.\n\n");
		    }
		    free(informations[0]);
		    free(informations[1]);
		    free(informations);
		}
	    // Login
	    else if(strcmp(command, "login") == 0)
	    {
	    	char **informations = NULL;
	    	informations = malloc(2 * sizeof(char*));
	    	informations[0] = malloc(150 * sizeof(char));
	    	informations[1] = malloc(150 * sizeof(char));
	    	printf("username=");
	    	scanf("%s", informations[0]);
	    	printf("password=");
	    	scanf("%s", informations[1]);
		    message = compute_post_request(host, "/api/v1/tema/auth/login", payload_type, informations, NULL, NULL);
		    printf("%s\n", message);
		    send_to_server(sockfd, message);
		    response = receive_from_server(sockfd);
		    if(strstr(response, "Credentials are not good"))
		    {
		    	printf("Wrong password.\n\n");
		    }
		    else if(strstr(response, "No account with this username"))
		    {
		    	printf("There is no account with username %s.\n\n", informations[0]);
		    }
		    else
		    {
		    	cookie = strstr(response,"connect.sid=");
		    	cookie = strtok(cookie, ";");
		    	printf("You have logged in succesfully.\n\n");
		    }
		    free(informations[0]);
		    free(informations[1]);
		    free(informations);
		}
		// Logout
		else if(strcmp(command, "logout") == 0)
		{
			if(cookie == NULL)
			{
				printf("You are not logged in yet.\n\n");
			}
			else
			{
				message = compute_get_request(host, "/api/v1/tema/auth/logout", NULL, cookie);
	    		printf("%s", message);
	    		send_to_server(sockfd, message);
	    		response = receive_from_server(sockfd);
		    	printf("You have logged out succesfully.\n\n");
		    	cookie = NULL;
		    	token = NULL;
			}
		}
		// Enter library
		else if(strcmp(command, "enter_library") == 0)
		{
			if(cookie == NULL)
			{
				printf("You are not logged in yet.\n\n");
			}
			else
			{
				message = compute_get_request(host, "/api/v1/tema/library/access", NULL, cookie);
	    		printf("%s", message);
	    		send_to_server(sockfd, message);
	    		response = receive_from_server(sockfd);
	    		char *buf1 = strstr(response, "token"); 
			    char *buf2 = strtok(buf1, "\""); 
			    while (strcmp(buf2, ":")) 
			    {  
			        buf2 = strtok(NULL, "\""); 
			    }
			    buf2 = strtok(NULL, "\"");
			    token = buf2;
	    		printf("You have received access to the the library.\n\n");
	    		
			}
		}
		// Get books
		else if(strcmp(command, "get_books") == 0)
		{
			if(token == NULL)
			{
				printf("You have no acces to the library.\n\n");
			}
			else
			{
				message = compute_get_request(host, "/api/v1/tema/library/books", token, NULL);
	    		printf("%s", message);
	    		send_to_server(sockfd, message);
	    		response = receive_from_server(sockfd);
	    		char *list = strstr(response,"[");
	    		printf("%s\n\n", list);
			}
		}
		// Get book
		else if(strcmp(command, "get_book") == 0)
		{
			if(token == NULL)
			{
				printf("You have no acces to the library.\n\n");
			}
			else
			{
				char url[50], id[15];
				printf("id=");
				scanf("%s", id);
				if(checkNumber(id, strlen(id)))
		    	{
		    		printf("id must be a natural number.\n\n");
		    	}
		    	else
		    	{
					strcpy(url, "/api/v1/tema/library/books/");
					strcat(url, id);
					message = compute_get_request(host, url, token, NULL);
		    		printf("%s", message);
		    		send_to_server(sockfd, message);
		    		response = receive_from_server(sockfd);
		    		if(strstr(response, "No book was found"))
		    		{
		    			printf("This book doesn't exist.\n\n");
		    		}
		    		else
		    		{
		    			char info[1000];
		    			char *book_info = strstr(response,"\"title\"");
		    			book_info = strtok(book_info, "]");
		    			sprintf(info, "{\"id\":\"%s\",%s", id, book_info);
		    			printf("%s\n\n", info);
		    		}
		    	}
			}
		}
		// Add book
	    else if(strcmp(command, "add_book") == 0)
	    {
	    	if(token == NULL)
			{
				printf("You have no acces to the library.\n\n");
			}
			else
			{
		    	char **book_info = NULL;
		    	book_info = malloc(5 * sizeof(char*));
		    	for(int i = 0; i <= 4; i++) 
		    	{
		    		book_info[i] = malloc(150 * sizeof(char));
		    	}
		    	printf("title=");
		    	scanf("%s", book_info[0]);
		    	printf("author=");
		    	scanf("%s", book_info[1]);
		    	printf("genre=");
		    	scanf("%s", book_info[2]);
		    	printf("publisher=");
		    	scanf("%s", book_info[3]);
		    	printf("page_count=");
		    	scanf("%s", book_info[4]);
		    	if(checkNumber(book_info[4], strlen(book_info[4])))
		    	{
		    		for(int i = 0; i <= 4; i++) 
		    		{
		    			free(book_info[i]);
		    		}
				    free(book_info);
		    		printf("page_count must be a natural number.\n\n");
		    	}
		    	else
		    	{
				    message = compute_post_request(host, "/api/v1/tema/library/books", payload_type, NULL, book_info, token);
				    printf("%s\n", message);
				    send_to_server(sockfd, message);
				    response = receive_from_server(sockfd);
				    if(strstr(response, "error")) 
				    {
				    	printf("Couldn't add book.\n\n");
				    }
				    else 
				    {
				    	printf("Book added succesfully.\n\n");
				    }
				    for(int i = 0; i <= 4; i++) 
			    	{
			    		free(book_info[i]);
			    	}
				    free(book_info);
				}
			}
		}
		// Delete book
	    else if(strcmp(command, "delete_book") == 0)
	    {
			if(token == NULL)
			{
				printf("You have no acces to the library.\n\n");
			}
			else
			{
				char url[50], id[15];
				printf("id=");
				scanf("%s", id);
				if(checkNumber(id, strlen(id)))
		    	{
		    		printf("id must be a natural number.\n\n");
		    		continue;
		    	}
		    	else
		    	{
					strcpy(url, "/api/v1/tema/library/books/");
					strcat(url, id);
					message = compute_delete_request(host, url, token);
		    		printf("%s", message);
		    		send_to_server(sockfd, message);
		    		response = receive_from_server(sockfd);
		    		if(strstr(response, "No book was deleted"))
		    		{
		    			printf("This book doesn't exist.\n\n");
		    		}
		    		else
		    		{
		    			printf("Book deleted succesfully\n\n");
		    		}
		    	}
			}
		}
		// Exit
		else if(strcmp(command, "exit") == 0)
		{
			printf("Exiting...\n");
			close(sockfd);
			token = NULL;
			cookie = NULL;
			return 0;
		}
		// Wrong command
		else
		{
			printf("Unknown command \"%s\"\n\n", command);
		}
	}

    return 0;
}
