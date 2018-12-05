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
	char conf[5]; 
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
        
        strcpy(msg, "");
        

        while(1){
            int len, n; 
            char pac[5];
            char verf;

            n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                        MSG_WAITFORONE, ( struct sockaddr *) &cliaddr, 
                        &len); 
            buffer[n] = '\0'; 

            verf = buffer[0];
            
            int cont = 0;

            for(cont = 1; cont <= strlen(buffer); cont++){
                pac[cont-1] = buffer[cont];
            }

            printf("verificacao = %c", verf);
            
            if(verf == 'f'){
                printf("Conexao encerrada.\n"); 
                printf("\n\n Mensagem = %s.\n", msg); 

                printf("\n************************************\n"); 
                
                break;
                
            }else if(verf == 'q'){
                printf("\n\nEncerrando\n\n");
                return 0;
            }else if (verf == 'c'){
                


                printf("\n\nClient : %s\n", pac); 
                strcat(msg,pac);

                strcpy(conf, "c");

                int x = strlen(conf);
                sendto(sockfd, (const char *)conf, x, 
                    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                        len); 
                printf("Confirmação enviada.\n"); 
                printf("\n____________________________________\n"); 

            }else if(verf == 'r'){
                
                msg[strlen(msg) - strlen(pac)] = '\0';

                printf("\n\nClient : %s\n", pac); 
                strcat(msg,pac);

                strcpy(conf, "c");

                int x = strlen(conf);
                sendto(sockfd, (const char *)conf, x, 
                    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                        len); 
                printf("Confirmação enviada | Mensagem re-renviada.\n"); 
                printf("\n____________________________________\n"); 


            }

        }
    }
	return 0; 
} 
