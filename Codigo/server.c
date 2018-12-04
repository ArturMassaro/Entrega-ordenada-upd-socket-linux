// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
    char msg[100];
	char *conf = "c"; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
    while(1){

        while(1){
            int len, n; 
            n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                        MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                        &len); 
            buffer[n] = '\0'; 
            
            if(strcmp(buffer, "f") == 0){
                printf("Conexao encerrada.\n"); 
                printf("\n\n Mensagem = %s.\n", msg); 

                printf("\n************************************\n"); 
                
                break;
                
            }else if(strcmp(buffer, "enc") == 0){
                printf("\n\nEncerrando\n\n");
                return 0;
            }else{
                


                printf("\n\nClient : %s\n", buffer); 
                strcat(msg,buffer);

                int x = strlen(conf);
                sendto(sockfd, (const char *)conf, x, 
                    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                        len); 
                printf("Confirmação enviada.\n"); 
                printf("\n____________________________________\n"); 

            }

        }
    }
	return 0; 
} 
