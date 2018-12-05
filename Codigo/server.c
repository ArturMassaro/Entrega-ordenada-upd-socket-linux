// Implementação do lado do servidor do modelo cliente-servidor UDP
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
	
	// Criando o descritor de arquivo de soquete 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Preenchendo informações do servidor
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Ligue o socket com o endereço do servidor
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


            //recebe dado
            n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                        MSG_WAITFORONE, ( struct sockaddr *) &cliaddr, 
                        &len); 
            buffer[n] = '\0'; 

            verf = buffer[0];
            
            int cont = 0;


            // Separa mensagem e verificador
            for(cont = 1; cont <= strlen(buffer); cont++){
                pac[cont-1] = buffer[cont];
            }

            printf("verificacao = %c", verf);
            

            //caso seja final
            if(verf == 'f'){
                printf("Conexao encerrada.\n"); 
                printf("\n\n Mensagem = %s.\n", msg); 

                printf("\n************************************\n"); 
                
                break;
                
            //caso seja para encerrar aplicação
            }else if(verf == 'q'){
                printf("\n\nEncerrando\n\n");
                return 0;

            //caso seja um pacote
            }else if (verf == 'c'){
                


                printf("\n\nClient : %s\n", pac); 
                strcat(msg,pac);

                strcpy(conf, "c");

                int x = strlen(conf);
                //Manda confirmação
                sendto(sockfd, (const char *)conf, x, 
                    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                        len); 
                printf("Confirmação enviada.\n"); 
                printf("\n____________________________________\n"); 

            // Caso seja pacote repetido
            }else if(verf == 'r'){
                
                //verifica se já existe esse pacote 
                if(strstr(msg, pac) != NULL){
                    msg[strlen(msg) - strlen(pac)] = '\0';
                }
                printf("\n\nClient : %s\n", pac); 
                strcat(msg,pac);

                strcpy(conf, "c");

                int x = strlen(conf);

                // Envia confirmação
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
