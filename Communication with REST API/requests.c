#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *token,
                            char *cookie)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    sprintf(line, "GET %s HTTP/1.1", url);

    compute_message(message, line);
    sprintf(line, "Host: %s", host);
    compute_message(message,line);
    if(cookie != NULL) 
    {
        sprintf(line, "Cookie: %s;", cookie);
        compute_message(message, line);
    }
    if(token != NULL)
    {
        sprintf(line, "Authorization: Bearer %s", token);
        compute_message(message, line);
    }
    compute_message(message, "");
    return message;
}



char *compute_post_request(char *host, char *url, char* content_type, char **body_data1,
                         char **body_data2, char *token)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *info = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    sprintf(info, "POST %s HTTP/1.1", url);
    compute_message(message, info);
    
    sprintf(info, "Host: %s", host);
    compute_message(message, info);
    if(token != NULL)
    {
        sprintf(info, "Authorization: Bearer %s", token);
        compute_message(message, info);
    }

    sprintf(info, "Content-Type: %s", content_type);
    compute_message(message, info);

    if(body_data1 != NULL) 
    {
        strcpy(body_data_buffer, "{\n");
        strcat(body_data_buffer, "\t\"username\":\"");
        strcat(body_data_buffer, body_data1[0]);
        strcat(body_data_buffer, "\",\n");
        strcat(body_data_buffer, "\t\"password\":\"");
        strcat(body_data_buffer, body_data1[1]);
        strcat(body_data_buffer, "\"\n");
        strcat(body_data_buffer, "}");
    }
    else if(body_data2 != NULL)
    {
        strcpy(body_data_buffer, "{\n");
        strcat(body_data_buffer, "\t\"title\":\"");
        strcat(body_data_buffer, body_data2[0]);
        strcat(body_data_buffer, "\",\n");
        strcat(body_data_buffer, "\t\"author\":\"");
        strcat(body_data_buffer, body_data2[1]);
        strcat(body_data_buffer, "\",\n");
        strcat(body_data_buffer, "\t\"genre\":\"");
        strcat(body_data_buffer, body_data2[2]);
        strcat(body_data_buffer, "\",\n");
        strcat(body_data_buffer, "\t\"page_count\":\"");
        strcat(body_data_buffer, body_data2[4]);
        strcat(body_data_buffer, "\",\n");
        strcat(body_data_buffer, "\t\"publisher\":\"");
        strcat(body_data_buffer, body_data2[3]);
        strcat(body_data_buffer, "\"\n");
        strcat(body_data_buffer, "}");
    }

    sprintf(info, "Content-Length: %ld", strlen(body_data_buffer));
    compute_message(message, info);


    compute_message(message, "");
    memset(info, 0, LINELEN);
    compute_message(message, body_data_buffer);


    free(info);
    return message;
}


char *compute_delete_request(char *host, char *url, char *token)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    sprintf(line, "DELETE %s HTTP/1.1", url);

    compute_message(message, line);
    sprintf(line, "Host: %s", host);
    compute_message(message,line);

    if(token != NULL)
    {
        sprintf(line, "Authorization: Bearer %s", token);
        compute_message(message, line);
    }
    compute_message(message, "");
    return message;
}
