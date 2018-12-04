# Comunincação cliente-servidor com entraga ordenada em udp 
<br />
 
 
# Funcionamento

    Para que a entrega ordenada acontece primerio pegamos a mensagem a ser enviada e separamos em pacotes menos com 24bits cada, para assim ser enviado ao servidor, que ao receber retorna uma mensagem de confirmação para que seja enviado o proximo pacote mantendo assim sua ordenção.



 <br />
 <br />
 
 
 
# Utilização
 
## iniciar server
 <br />
* Abra o terminal
* navegue até a pasta do projeto
* execute o comando ./server
<br />
 
 
## iniciar client
<br /> 
 
* Abra o terminal(Obs: Diferente do anterior)
* navegue até a pasta do projeto
* execute o comando ./client
* Insira a mensagem a ser enviada
 <br />
 
# Resultado final
 
## Server
 <br />

No terminal do servidor será mostrado em ordem de chegada os dados de cada pacote, bem como a mensagem de que a mensagem de confirmação foi enviada.
 
 <br />

## Client

<br />
No terminal do client será mostrado em ordem de envio o numero e os dados de cada pacote, bem como a mensagem de confirmação recebida do servidor.
 <br />
 
  
 
 