/**********************************************
*Title: client_example.c
*Author: Chris Johnson
*date 10/5/20
*Description: this is a barebones example of how
*	to use the libmtnops client functions
*
**********************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libmtnops.h"

//these stubs MUST be here for the client
int server_ext_request(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message){return(0);}
int server_ext_command(TCS_MESSAGE *new_message){return(0);}

static char SERVER_TELID[10];
static int SERVER_PORT;
static char SERVER_SYSID[10];
static char SERVER_NET_ADDR[16];

//to configure you just have to parse your own keywords and set your variables
//this function is called by libmtnops when you call configure();
int config_ext_parse(char words[MAX_ARGS][ARG_LEN])
{
int x = 0;
	printf("made it\n");
	if (strcmp(words[0], "SERVER_NET_ADDR") == 0)
		{
		sprintf(SERVER_NET_ADDR, "%s", words[1]);
		}
	else if (strcmp(words[0], "SERVER_PORT") == 0)
		{
		SERVER_PORT = atoi(words[1]);
		}
	else if (strcmp(words[0], "SERVER_TELID") == 0)
		{
		sprintf(SERVER_TELID, "%s", words[1]);
		}
	else if (strcmp(words[0], "SERVER_SYSID") == 0)
		{
		sprintf(SERVER_SYSID, "%s", words[1]);
		}
	else
		return NOK;
	
return OK;	
}

int main()
{
TCS_MESSAGE new, ret;
memset(&new, 0, sizeof(TCS_MESSAGE));
memset(&ret, 0, sizeof(TCS_MESSAGE));

configure("libmtnops.conf");

//client_init("localhost", 5750, "MTNOPS", "TEST");
client_init(SERVER_NET_ADDR, SERVER_PORT, SERVER_TELID, SERVER_SYSID);


sprintf(new.cmdArgs[0], "TEST ");
sprintf(new.cmdArgs[1], "ARG1");
sprintf(new.cmdArgs[2], "ARG2");
sprintf(new.cmdArgs[3], "ARG3");
client_command(&new, &ret, 123);
printmessage(&ret);

sleep(1);

memset(&new, 0, sizeof(TCS_MESSAGE));
memset(&ret, 0, sizeof(TCS_MESSAGE));
//client_init("localhost", 5750, "MTNOPS", "TEST");


sprintf(new.cmdArgs[0], "ALL");

client_request(&new, &ret, 124);
printmessage(&ret);






}
