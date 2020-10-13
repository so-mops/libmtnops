/*############################################################################
#  Title: libmtnops.h
#  Author: C. Johnson
#  Date: 10/12/20
#  Description: Contains a set of commands specific for communicating with
#	a TCS-NG client and server.  Unified from older independent headers
#
#############################################################################*/

#define OK 0
#define NOK 1
#define MAX_MSG 1500

//data structures
#define MAX_ARGS 100
#define ARG_LEN 40
#define MAX_ARG_SZ (MAX_ARGS*ARG_LEN) 
typedef char ARG_ARRAY[MAX_ARGS][ARG_LEN];

typedef struct
{
char telID[ARG_LEN];
char sysID[ARG_LEN];
unsigned short int pID;
char cmd[ARG_LEN];
ARG_ARRAY cmdArgs;
}TCS_MESSAGE;

/////////////////////////// ngclient stuff ////////////////////////////////
int client_command(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message, int seq);
int client_request(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message, int seq);
int client_init(char *name, int port, char *telid, char *sysid);



/////////////////////////// ngserver stuff ////////////////////////////////
void server_entry();
void server_init(int port, char *telid, char *sysid);
extern int server_ext_request(TCS_MESSAGE *new_message, TCS_MESSAGE *ret_message);
extern int server_ext_command(TCS_MESSAGE *new_message);
void printmessage(TCS_MESSAGE *new_message);
void gen_string(TCS_MESSAGE *ret_message, char *out_string);
int parse_line(TCS_MESSAGE *new_message, char *line);

//message identifiers
/*#define TELID_ERR       "TELID ERROR"
#define SYSID_ERR       "SYSID ERROR"
#define CMD_REQ "REQUEST"
#define CMD_CMD "COMMAND"
#define CMD_SUCCESS "OK"
#define CMD_REQ_SUCCESS "OK"
#define CMD_ERR "ERROR"
#define CMD_UNKNOWN "UNKNOWN_CMD"
#define CMD_REQ_ERR "REQUEST_ERROR"
#define CMD_CMD_ERR "COMMAND_ERROR"
#define NODATA "NULL"*/



/////////////////////////// config stuff ////////////////////////////////
int configure(char *filename);
void initDefault();
