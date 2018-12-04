// Client side implementation of UDP client-server model 
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
	char str[MAXLINE] = "Olá tudo bem com voce ?"; 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	


    printf("\n\ninforme a mensagem: ");
    gets(str);

    int len2 = strlen(str);

    int i = 0;
    char msg[50];
    char aux[2];
    strcpy(msg,"");


    int pacotes = 0;

    for(i = 0; i < len2; i++){
        if(i == len2 - 1){
            aux[0] = str[i];
            aux[1] = '\0';
            strcat(msg, aux);

            //Envia dados

            int n, len; 
            
            sendto(sockfd, (const char *)msg, strlen(msg), 
                MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                    sizeof(servaddr)); 
            printf("\n____________________________________\n"); 

            printf("\nPacote final enviado | total = %d.\n", pacotes); 
                
            n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                        MSG_WAITALL, (struct sockaddr *) &servaddr, 
                        &len); 
            buffer[n] = '\0'; 
            printf("Server : %s\n", buffer); 

            printf("Dado: %s \n", msg);
            strcpy(msg, "");
        }else{
            if(strlen(msg) == 3){

                //Envia dados

                int n, len; 
            
                sendto(sockfd, (const char *)msg, strlen(msg), 
                    MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                        sizeof(servaddr)); 
                printf("\n____________________________________\n"); 
                printf("\nPacote %d.\n", pacotes); 
                    
                n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                            MSG_WAITALL, (struct sockaddr *) &servaddr, 
                            &len); 
                buffer[n] = '\0'; 
                printf("Server : %s\n", buffer); 


                
                printf("Dado: %s \n", msg);
                strcpy(msg, "");
                i--;
                pacotes++;

            }else{
                aux[0] = str[i];
                aux[1] = '\0';
                strcat(msg, aux);            
            }
        }

    }









	int n, len; 
	
	sendto(sockfd, (const char *)"f", strlen("f"), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
    
    printf("\n____________________________________\n"); 

	printf("\nMensagem final enviada.\n"); 
		
	/*n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	buffer[n] = '\0'; */
	printf("Conexao encerrada\n"); 
    printf("\n************************************\n"); 


	close(sockfd); 
	return 0; 
} 
