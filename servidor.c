/* servidor.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#define STDOUT 1
#define SERV_ADDR (IPPORT_RESERVED+1)

int main()
{
int rval;
int sock,length,msgsock; //(Socket del servidor, alguna longitud, socket creado por accept(), usador para establecer la conexion con el cliente)
struct sockaddr_in server, client;//Estructura generica de sockets con la informacion de estos
char buf[1024];//El servidor lee los caracteres de la conexion socket en este buffer

sock=socket(AF_INET, SOCK_STREAM,0); //Creamos identificador para el socket

if (sock<0)
  {
    perror("No hay socket de escucha");
    exit(1);
  }

server.sin_family=AF_INET; //Dominio predeterminado para la estructura de sockaddr
server.sin_addr.s_addr=htonl(INADDR_ANY);//se pasa la direccion INADDR_ANY una vez pasada de ordenacion del host a ordenacion de la red (htonl) al parametro addr de la estructura
server.sin_port = htons(SERV_ADDR); //Lo mismo que la linea anterior pero con el puerto

if (bind(sock,(struct sockaddr *)&server, sizeof(server))<0)//Enlaza el conector a una direccion, aqui lo enlaza con la direccion de la maquina actual y con el puerto donde se ejecutara el socket
//Conversion de sockaddr_in a sock_addr 
  {
    perror("Direccion no asignada");
    exit(1);
  }
length = sizeof(client);
listen(sock,1); //El proceso queda a la "escucha de conexiones, el segundo argumento es el numero de conexiones que pueden esperar mientras que el proceso opera con una conexion en concreto"
while (1)
 {
  /*Estará bloqueado esperando petición de conexión*/


  msgsock = accept(sock, (struct sockaddr *)&client, &length);//Se bloquea el proceso esperando una conexion, esto crea nuevo descriptor de fichero o socket
  // para establecer las conexiones, escribir, leer etc con el cliente.

  if (msgsock==-1)
     perror("Conexion no aceptada");
  else
    do
     {
      /*Me dispongo a leer datos de la conexion*/
      memset(buf,0,sizeof(buf));
      rval=read(msgsock,buf,1024);

      if (rval<0)
        perror("Mensaje no leído");
      else
        write(STDOUT,buf,rval);
      }
     while (rval>0);
   printf ("\nPuerto cliente: %hu", /*ntohs(*/client.sin_port/*)*/);
   printf ("\nIP cliente: %s", (char*)inet_ntoa(/*ntohl(*/client.sin_addr.s_addr))/*)*/;
   printf("\nConexion cerrada\n");
   close(msgsock);
  }
exit(0);
}
