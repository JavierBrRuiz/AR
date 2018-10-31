/* cliente.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#define SERV_ADDR (IPPORT_RESERVED+1)
#define DATA "##--##--##----***----##--##--##"

int main (int argc, char *argv[])
{
 int sock;
 struct sockaddr_in server; //Estructura generica de sockets mas especifica
 struct hostent *hp;
 char hostname[256];

 if (argc<2)
    {
      printf("Uso: %s como nombre de host\n",argv[0]);
      exit(1);
    }
sock=socket(AF_INET,SOCK_STREAM,0); //Socket() crea un socket y devuelve un entero que sirve de identificacion del socket (dominio, tipo, protocolo)
// sock se utilizara para conectarse, recibir conexiones, enviar y recibir datos etc...

if (sock<0)
   {
     perror("No se ha podido crear el socket");
     exit(1);
   }
server.sin_family =AF_INET; //Se asigna al parametro sin_family de la estructura sockaddr_in el dominio que se utilizara
hp=gethostbyname(argv[1]); //hp recibe una estructura hostent con los datos del host, nombre, alias, longitud etc...

if (hp==0)
   {
     fprintf(stderr, "%s: No conozco ese computador\n",argv[1]);
     exit(2);
   } 
memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);//se copia en sin_addr de la estructura sockaddr_in la direccion ip del host obtenida de la estructura hostent o HP
server.sin_port = htons (SERV_ADDR);//El puerto debe estar en el orden de bytes de la red de ahi el uso de htons//hton-s s = short type
 
if (connect(sock, (struct sockaddr *)&server, sizeof(server))<0)//Solicita el establecimiento de una conexion TCP, inicia la conexion con el servidor remoto (y el socket del servidor, creado por accept)
   {
     perror("La conexion no sido aceptada");
     exit(1);
   }

 if (write(sock,DATA, strlen(DATA)+1)<0) //Manda al servidor DATA que es lo que queremos escribir, el read() del servidor se bloquea hasta que el cliente usa write. y viceversa
    perror("No he podido escribir el mensaje");
 strcpy(hostname, "\nCliente: ");
 strcat(hostname, hp->h_name);
 if (write(sock, hostname, strlen(hostname)+1)<0)
    perror("No se ha conseguido mandar el nombre del cliente");
 close(sock); // se cierra el socket
 exit(0);
}
