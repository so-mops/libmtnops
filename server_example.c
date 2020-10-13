/**********************************************
*Title: server_example.c
*Author: Chris Johnson
*date 10/5/20
*Description: this is a barebones example of how
*	to use the libmtnops server functions
*
**********************************************/

#include <stdio.h>
#include "libmtnops.h" //you have to include this guy


int main()
{
//this must be done first.  This inits the server
server_init(5750, "MTNOPS",  "TEST");


//this starts the server
//this does not return unless the server crashes
server_entry();



}


// To use the NG server lib you must create the functions server_ext_command() and server_ext_request()
//  these are called by the server software.  This is where you handle your server stuff
// and return OK or NOK
int server_ext_command(TCS_MESSAGE *new_message)
{
printf("got a command!!\n");
printmessage(new_message);

return OK;
}

int server_ext_request(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message)
{

printf("got a request!!\n");
printmessage(new_message);

sprintf(ret_message->cmdArgs[0], "RET0"); 
sprintf(ret_message->cmdArgs[1], "RET1"); 
sprintf(ret_message->cmdArgs[2], "RET2"); 
sprintf(ret_message->cmdArgs[3], "RET3"); 
sprintf(ret_message->cmdArgs[4], "RET4"); 
sprintf(ret_message->cmdArgs[5], "RET5"); 

return OK;
}




