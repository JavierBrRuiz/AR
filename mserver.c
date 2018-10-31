# include <sys/types.h>
# include <sys/socket.h>
# include <sys/wait.h>
# include <netinet/in.h>
# include <netdb.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# define FICHERO  "mserver.log"
# define HEAD     "head.html"
# define TAIL     "tail.html"

static void usage(char *name) //En caso de falta de argumentos llama a usage(argv[0])
{
   fprintf(stderr, "%s: Uso %s <port>\n", name, name);
   exit (1);
}

static void ChildHasDied(int num) //Si el hijo muere, la funcion SIGNAL lo detecta, si devuelve SIG_ERR ha habido un error con el proceso hijo
{
int   status;
pid_t pid;

   pid = wait(&status);
   if (signal(SIGCHLD, ChildHasDied) == SIG_ERR)
      fprintf(stderr, "Error al dar de alta la accion.\n");
   return;
}

static void FinishAction(int num) //Si la funcion signal devuelve SIG_ERR ha habido un error al intentar finalizar el programa
{
   fprintf(stderr, "Programa finalizado correctamente.\n\n");
   exit(0);
}
/*
Funcion principal del servidor, recibe el nuevo socket creado para la conexion con el cliente 
devuelto por la funcion net_slisten, la cual recibe un puerto, crea la estructura
sockaddr_in del servidor con el puerto y AF_INET, crea un primer socket para el servidor, 
lo bindea y llama a la funcion listen, que prepara al servidor para recibir conexiones,
en este caso, 4. crea un bucle infinito, en el cual se acepta una primera conexion, 
devolviendo el nuevo socket que habilita la misma, y despues en el mismo bucle, hace fork
para que los procesos hijo puedan atender otras 3 
----------------------------------------------------------------------------------------------------

la funcion net_server, una vez recibido el socket que habilita la conexion con el cliente
hace los siguiente:
    -Abre mserver.log
    -Lee del cliente y guarda lo leido en cadena
    -Printea el formato(no el buffer), mediante len(la funcion no se lo que hace)
    -Si se abre correctamente el fichero(mserver.log) printea formato y cadena.....	ESTO LO HACE EN UN BUCLE DO WHILE
----------------------------------------------------------------------------------------------------
    -Cierra el archivo y abre HEAD.html
    -En un bucle while va leyendo el archivo y mandandoselo al cliente hasta que acaba de leer
 	-Cierra HEAD y abre mserver.log, lo lee y lo manda al cliente tambien
	-Cierra y hace lo mismo con cadena y cierra el socket.
	
*/
static void net_server(int sock) 
{
# define BUFF_LEN 8192
int   len;
char  formato[BUFF_LEN];
char  cadena[BUFF_LEN];
FILE *fp = NULL;

   fp = fopen(FICHERO, "w");
   len = fcntl(sock, F_SETFD, O_NDELAY | O_NONBLOCK);

   do
   {
      len = read(sock, cadena, BUFF_LEN);
      sprintf(formato, "%%%d.%ds", len, len);
      if (fp)
        {
         fprintf(fp, formato, cadena);
         printf(formato, cadena);
        }
      else
         printf(formato, cadena);
    }while (len == BUFF_LEN);
   fclose(fp);

   fp = fopen(HEAD, "r");
   if (fp)
     {
      while(fgets(cadena, sizeof(cadena), fp) != NULL)
         write(sock, cadena, strlen(cadena));
      }
   fclose(fp);


   fp = fopen(FICHERO, "r");
   if (fp)
     {
      while(fgets(cadena, sizeof(cadena), fp) != NULL)
         write(sock, cadena, strlen(cadena));
     }
   fclose(fp);

   fp = fopen(TAIL, "r");
   if (fp)
     {
      while(fgets(cadena, sizeof(cadena), fp) != NULL)
         write(sock, cadena, strlen(cadena));
     }
   fclose(fp);

   close(sock);
}

static int net_slisten(short port)
{
int sock, new_sock;
struct sockaddr_in sin, from;
unsigned int len = sizeof(from);
int OptVal = 1;
int OptSize = sizeof(OptVal);

   bzero((char *) &sin, sizeof (sin));
   sin.sin_family = AF_INET;
   sin.sin_port = htons(port);

   sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (sock < 0)
      exit(-1);

   if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
      (char *)&OptVal, OptSize) < 0) exit(-3);

   if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) exit(-2);

   listen (sock, 4);
   for (;;)
   {
      len = sizeof(from);
      new_sock = accept(sock, (struct sockaddr *)&from, &len);
      if (new_sock < 0)
      {
         if (errno == EINTR) 
            continue;
         exit(-4);
      }

      switch (fork())
      {
         case -1:           /* ¿error? */
            exit(-5);

         case 0:            /* proceso hijo */
            close(sock);
            return(new_sock);

         default:           /* proceso padre */
            close(new_sock);
      }
   }
}

int main(int argc, char **argv)
{
int sock;
short port;

   if (signal(SIGTERM, FinishAction) == SIG_ERR)
      fprintf(stderr, "Error al dar de alta la accion.\n");

   if (signal(SIGCHLD, ChildHasDied) == SIG_ERR)
      fprintf(stderr, "Error al dar de alta la accion.\n");

   if (argc != 2) usage(argv[0]);
   port = atoi(argv[1]);
   sock = net_slisten(port);

   if (sock == -1)
   {
     perror("mserver_http: net_slisten falló.");
     exit(1);
   }
   net_server(sock);
   return 0;
}
