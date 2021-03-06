// Implementação do lado do cliente do modelo cliente-servidor UDP
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/time.h>
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

	// Criando o descritor de arquivo de soquete 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Preenchendo informações do servidor
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	//servaddr.sin_addr.s_addr = inet_addr("192.168.100.121");
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    
	struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Error");
    }


    printf("\n\ninforme a mensagem: ");
    gets(str);

    int len2 = strlen(str);

    int i = 0;
    char msg[50];
    char aux[2];
    strcpy(msg,"");


    int pacotes = 0, ultPacote = -1;

    int erros = 0;

    // Percorre toda a mensagem
    for(i = 0; i < len2; i++){


        // Verifica se é o final da mensagem
        if(i == len2 - 1){
            aux[0] = str[i];
            aux[1] = '\0';
            strcat(msg, aux);

            


                int n, len; 
                char msgEnvia[5], aux[5];
                
                // insere o caracter de verificação

                if(ultPacote == pacotes){
                    aux[0] = 'r';
                    aux[1] = '\0';
                }else{
                    aux[0] = 'c';
                    aux[1] = '\0';
                }

                strcpy(msgEnvia, aux);
                strcat(msgEnvia, msg);

                //Envia os dados dados

                sendto(sockfd, (const char *)msgEnvia, strlen(msgEnvia), 
                    MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                        sizeof(servaddr)); 
                
                ultPacote = pacotes;

                printf("\n____________________________________\n"); 
                printf("\nPacote %d.\n", pacotes); 
                    
                //Recebe a confirmação do servidor
                n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                            0, (struct sockaddr *) &servaddr, 
                            &len); 



                //  caso timeout
                if(n == -1){
                    printf("Confirmação nao recebida");
                    msg[strlen(msg)-1] = '\0';
                    
                    erros++;
                    i = i -2;

                    if(erros == 10){
                        break;
                    }

                }else{
                    //buffer[n] = '\0'; 

                    if(buffer[0] == 'c'){
                        printf("Server : %s\n", buffer); 


                        
                        printf("Dado: %s \n", msg);
                        strcpy(msg, "");
                        i--;
                        pacotes++;
                        break;
                    }else{
                        printf("ERRO");
                    }
                }

        // quando completar um pacote de 3 caracteres
        }else if(strlen(msg) == 3){

                

                int n, len; 
                char msgEnvia[5], aux[5];

                if(ultPacote == pacotes){
                    aux[0] = 'r';
                    aux[1] = '\0';
                }else{
                    aux[0] = 'c';
                    aux[1] = '\0';
                }

                strcpy(msgEnvia, aux);
                strcat(msgEnvia, msg);

                //Envia dados
                sendto(sockfd, (const char *)msgEnvia, strlen(msgEnvia), 
                    MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                        sizeof(servaddr)); 
                
                ultPacote = pacotes;

                printf("\n____________________________________\n"); 
                printf("\nPacote %d.\n", pacotes); 


                //recebe confirmação    
                n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                            0, (struct sockaddr *) &servaddr, 
                            &len); 




                // Caso timeout
                if(n == -1){
                    printf("Confirmação nao recebida");
                    msg[strlen(msg)-1] = '\0';
                    
                    erros++;
                    i = i -2;

                    if(erros == 10){
                        break;
                    }

                }else{
                    //buffer[n] = '\0'; 

                    if(buffer[0] == 'c'){
                        printf("Server : %s\n", buffer); 


                        
                        printf("Dado: %s \n", msg);
                        strcpy(msg, "");
                        i--;
                        pacotes++;
                        
                    }else{
                        printf("ERRO");
                    }
                }

                
                
            // agrupa o Pacote
            }else{
                aux[0] = str[i];
                aux[1] = '\0';
                strcat(msg, aux);            
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
	printf("Conexao encerrada \n"); 
    printf("\n************************************\n"); 


	close(sockfd); 
	return 0; 
} 
