# Comunincação cliente-servidor com entraga ordenada em udp 
<br />
 
 
# Funcionamento

Para que a entrega ordenada aconteça primeiro pegamos a mensagem a ser enviada e separamos em pacotes menores com 24bits cada, para assim ser enviado ao servidor, que ao receber retorna uma mensagem de confirmação para que seja enviado o próximo pacote, assim continuamente até que o cliente sinalize que todos os pacotes já foram enviados, mantendo assim sua ordenção.
<br />

![](Diagramas/diagram1.jpg)

Exemplo client enviando "ola tudo bem ?" como mensagem.


![](Diagramas/exemplo.jpg)


 <br />
 <br />
 
 
 
# Utilização
 
## iniciar server
 <br />

* Abra o terminal
* Navegue até a pasta do projeto
* Execute o comando ./server
  
<br />
 
 
## iniciar client
<br /> 
 
* Abra o terminal(Obs: Diferente do anterior)
* Navegue até a pasta do projeto
* Execute o comando ./client
* Insira a mensagem a ser enviada
 <br />
 
# Resultado final
 
## Server
 <br />

No terminal do servidor será mostrado em ordem de chegada os dados de cada pacote, bem como a notificação de que a mensagem de confirmação foi enviada.
 
 <br />

## Client

<br />

No terminal do client será mostrado em ordem de envio o numero e os dados de cada pacote, bem como a mensagem de confirmação recebida do servidor.

 <br />
 
  
 
 