/**********************************************
*Title: client_example.c
*Author: Chris Johnson
*date 10/5/20
*Description: this is a barebones example of how
*	to use the libmtnops client functions
*
**********************************************/

#include <stdio.h>
#include "libmtnops.h"

//these stubs MUST be here for the client
int server_ext_request(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message){return(0);}
int server_ext_command(TCS_MESSAGE *new_message){return(0);}


int main()
{
TCS_MESSAGE new, ret;
memset(&new, 0, sizeof(TCS_MESSAGE));
memset(&ret, 0, sizeof(TCS_MESSAGE));



client_init("localhost", 5750, "MTNOPS", "TEST");


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


sprintf(new.cmdArgs[0], "TEST ");

client_request(&new, &ret, 124);
printmessage(&ret);






}
