/*############################################################################
#  Title: ngclient.c
#  Author: C. Johnson
#  Date: 12/2/12
#  Description: Contains a set of client side commands specific for communicating with
#	a TCS-NG server
#
#############################################################################*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* close */
#include "libmtnops.h"


static char REMOTE_TELID[10] = "NADA";
static int REMOTE_PORT = 5750;
static char REMOTE_SYSID[10] = "NADA";
static char REMOTE_NET_ADDR[16] = "192.168.1.1";


//#define MAX_MSG 1500
int indiNetErr(char *in);

  struct sockaddr_in localAddr, servAddr;
  struct hostent *h;
  static int sd=0, rc=0, initialized=0;

#define mydev              "TCS-NG-INDI"





/*############################################################################
#  Title: ng_send()
#  Author: C. Johnson
#  Date: 12/2/12
# Args:  TCS_MESSAGE *new_message: message to be sent
#	TCS_MESSAGE *ret_message: message returned from server
#  Description: sends and receives data using the TCS-NG protocol
#
#	10/12/20: modified to take TCS-MESSAGE structs rather than strings - cj
#
#############################################################################*/
int ng_send(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message)
{
char data[MAX_MSG];
char term = '\n';
char preamble[100];


client_init(REMOTE_NET_ADDR, REMOTE_PORT, REMOTE_TELID, REMOTE_SYSID);




 memset(data, 0, MAX_MSG);
  gen_string(new_message, data);
  printf("sending: %s\n", data);

 
  rc = connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
  if(rc<0) {
    indiNetErr("cannot connect ");
    return(1);
  }
    rc = send(sd, data, strlen(data) + 1, 0);
    
    if(rc<0) {
	indiNetErr("cannot send data ");
      close(sd);
      return(1);
    
       }
 memset(data, 0, MAX_MSG);

    if (recv(sd,&data,sizeof(data),0) == -1)
      		{
		indiNetErr("recv error");
		return(1);
      		}
    //printf("got: %s\n", data);
    close(sd);

  parse_line(ret_message, &data);
//strcpy(output, &data[strlen(preamble)]);
      

return 0;
}

/*############################################################################
#  Title: initialize()
#  Author: C. Johnson
#  Date: 12/2/12
#  Args:  name=name or IP address of TCS-NG server 
#	port=port on server to talk to
#	telid: telescope id of server
#	
#  Description: Initializes the network stack to talk to a TCS-NG 
#  server
#
#############################################################################*/
int client_init(char *name, int port, char *telid, char *sysid)
{
char out[50];

printf("before init: %s %i %s %s\n", REMOTE_NET_ADDR, REMOTE_PORT, REMOTE_TELID, REMOTE_SYSID);


sprintf(REMOTE_NET_ADDR, "%s", name);
REMOTE_PORT = port;
sprintf(REMOTE_TELID, "%s", telid);
sprintf(REMOTE_SYSID, "%s", sysid);

      
h = gethostbyname(name);
  if(h==NULL) {
    sprintf(out, "unknown host '%s'\n",name);
	indiNetErr(out);
    return 1;
  }
    
  servAddr.sin_family = h->h_addrtype;
  memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  servAddr.sin_port = htons(port);

  /* create socket */
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd<0) {
    indiNetErr("cannot open socket ");
    return 1;
  }

  /* bind any port number */
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(0);
  
  rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
  if(rc<0) {
    printf("cannot bind port TCP %u\n",port);
    indiNetErr("error ");
    return 1;
  }

initialized=1;
return 0;
}

/*############################################################################
#  Title: ng_request()
#  Author: C. Johnson
#  Date: 12/2/12
#  Args:  TCS_MESSAGE *new_message: message to be sent
#	TCS_MESSAGE *ret_message: message returned from server
#	int seq: 
#  Description: sends a request to the TCS and populates a structure with the return
#
#	10/12/20: modified to take TCS-MESSAGE structs rather than strings - cj
#
#############################################################################*/
int client_request(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message, int seq)
{
char type[] = "REQUEST";
int err;

sprintf(new_message->telID, "%s", REMOTE_TELID);
sprintf(new_message->sysID, "%s", REMOTE_SYSID);
new_message->pID = seq;
sprintf(new_message->cmd, "REQUEST");
err = ng_send(new_message, ret_message);

return 0;

}

/*############################################################################
#  Title: ng_request()
#  Author: C. Johnson
#  Date: 12/2/12
#  Args:  TCS_MESSAGE *new_message: message to be sent
#	TCS_MESSAGE *ret_message: message returned from server
#	int seq: 
#  Description: sends a request to the TCS and populates a structure with the return
#
#	10/12/20: modified to take TCS-MESSAGE structs rather than strings - cj
#
#############################################################################*/
int client_command(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message, int seq)
{
char type[] = "COMMAND";
int err;
sprintf(new_message->telID, "%s", REMOTE_TELID);
sprintf(new_message->sysID, "%s", REMOTE_SYSID);
new_message->pID = seq;
sprintf(new_message->cmd, "COMMAND");
err = ng_send(new_message, ret_message);

return 0;

}


/*############################################################################
#  Title: ngatof()
#  Author: C. Johnson
#  Date: 12/2/12
#  Args:  in=char ptr to input string containing ascii degrees in "D:M:S.s"
#	out=float describing degrees.
#  Description: converts an ascii "D:M:S.s" string to a float "D.d"
#
#############################################################################*/
int ngatof(char *in, double *out)
{
double H, M, S;
sscanf(in, "%lf:%lf:%lf", &H, &M, &S);
*out = H + (M/60) + (S/3600);
return 0;
}

/*############################################################################
#  Title: ngdegtoa()
#  Author: C. Johnson
#  Date: 12/2/12
#  Args:  in=char ptr to input string containing ascii degrees in NG format
#	out=char ptr to ouput string containing ascii degrees in DD:MM:SS.ss
#  Returns: always returns 0	
#  Description: converts the NG style DMS string to a ':' delimited string
#
#############################################################################*/
int ngdegtoa(char *in, char *out)
{
char temp[20];
int iH, iM, iS, is;
double M, S, s;
sscanf(in, "%i.%i", &iH, &is);
sprintf(temp, "%06i", iH);
sscanf(temp, "%2i%2i%2i", &iH, &iM, &iS);
sprintf(out, "%02i:%02i:%02i.%2i", iH, iM, iS, is);
return 0;
}

/*############################################################################
#  Title: indiNetErr()
#  Author: C. Johnson
#  Date: 9/2/15
#  Args:  in=char ptr to input string containing eror
#	
#  Returns: always returns 0	
#  Description: converts the NG style DMS string to a ':' delimited string
#
#############################################################################*/
int indiNetErr(char *in)
{
char buff[50];
sprintf(buff, "NET:%s", in);
//IDMessage(mydev, buff);
return 0;
}



