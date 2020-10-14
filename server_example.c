/**********************************************
*Title: server_example.c
*Author: Chris Johnson
*date 10/5/20
*Description: this is a barebones example of how
*	to use the libmtnops server functions
*
**********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libmtnops.h" //you have to include this guy


static int SERVER_PORT;
static char SERVER_SYSID[10];
static char SERVER_TELID[10];




int main()
{

configure("libmtnops.conf");

//this must be done first.  This inits the server
//server_init(5750, "MTNOPS",  "TEST");
server_init(SERVER_PORT, SERVER_TELID,  SERVER_SYSID);


//this starts the server
//this does not return unless the server crashes
server_entry();



}


//to configure you just have to parse your own keywords and set your variables
//this function is called by libmtnops when you call configure();
int config_ext_parse(char words[MAX_ARGS][ARG_LEN])
{
int x = 0;
	printf("made it\n");
	 if (strcmp(words[0], "SERVER_PORT") == 0)
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


// To use the NG server lib you must create the functions server_ext_command() and server_ext_request()
//  these are called by the server software.  This is where you handle your server stuff
// and return OK or NOK
int server_ext_command(TCS_MESSAGE *new_message)
{
printf("got a command!!\n");
printmessage(new_message);
	if (strcmp(new_message->cmdArgs[0], "TEST") == 0)
		{
		printf("doing some commanded thing!!!\n");

		}
	else
		{
		//always return NOK if you don't have the keyword 
		return NOK;
		}

return OK;
}

int server_ext_request(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message)
{

printf("got a request!!\n");
printmessage(new_message);
	if (strcmp(new_message->cmdArgs[0], "ALL") == 0)
		{
		sprintf(ret_message->cmdArgs[0], "RET0"); 
		sprintf(ret_message->cmdArgs[1], "RET1"); 
		sprintf(ret_message->cmdArgs[2], "RET2"); 
		sprintf(ret_message->cmdArgs[3], "RET3"); 
		sprintf(ret_message->cmdArgs[4], "RET4"); 
		sprintf(ret_message->cmdArgs[5], "RET5"); 

		}
	else
		{
		//always return NOK if you don't have the keyword 
		return NOK;
		}

return OK;
}




