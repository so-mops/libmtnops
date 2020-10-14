/**********************************************
*Title: configure.c
*Author: Chris Johnson
*date 10/30/14
*Description: Configuration system.  Inits
*	required values to safe defaults then
*	proceeds to read a config file.
*
**********************************************/
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "libmtnops.h"


#define KEYWORD 0
#define VALUE 1
//#define ARG1 1
//#define ARG2 2
#define FIELD_LEN 40
#define MIN_FIELDS 2
#define MAX_FIELDS 100
int server_ix = 0;


void initDefault();


/**********************************************
*Title: configure
*Author: Chris Johnson
*date 10/30/14
*Description: system config
*
*ARGS:  
*
*Returns: OK = 1
*	  NOK(NOT OK) = 0
*
**********************************************/
int configure(char *filename)
{
FILE *fp;
char line[MAX_ARG_SZ];
char *search = " \t";
char *token;
char words[MAX_ARGS][ARG_LEN];
int wordctr=0, linectr=0, port;
char *wordptr;
	printf("Configuration Starting:\n");
	//open config file..  return NOK if file can't be opened
	fp=fopen(filename, "r");
	if(fp == NULL)
		{
		return NOK;
		}
	//read each line
	while( fgets(line,1024,fp) ) 
		{
		memset(words, 0, MAX_ARG_SZ);
		
		
		linectr++;
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		wordctr=0;
		//start strtok and find first word in line
        	wordptr=strtok(line, search);
		//skip lines beginning with '#'
		if(wordptr!=NULL)
			{
			if(wordptr[0] == '#'){continue;}
			}  
		//look at each additional word  		
		while (wordptr != NULL)
			{
			//if the word begins with '#', skip
			if(wordptr[0] == '#'){break;}
			//stuff the rest of the words in the array
			//and increment the counter
			sprintf(words[wordctr], "%s", wordptr);
    			wordctr++;
			if (wordctr>=MAX_FIELDS){break;}
			wordptr=strtok(NULL, search);
			}
		//Parse the known keywords
		if (wordctr < MIN_FIELDS)
			{
			printf("invalid line: not enough fields -- \" %s \" -- ignoring\n", line);
			}
		else
			{
			printf("%s\n",words[0] );
			config_ext_parse(words);
			}
		memset(line, 0, MAX_ARG_SZ);
		
	
		}//end "while( fgets..."
	printf("Configuration Done!\n");
	return OK;

}


/**********************************************
*Title: initDefault
*Author: Chris Johnson
*date 10/30/14
*Description: initialize default values
*
*ARGS:  
*
*Returns: 
*
**********************************************/
void initDefault()
{
int ix;

/*	SERVER_PORT = 5750;
	sprintf(TELESCOPE_ID, "%s", "TCSNG");
	


	for (ix=1; ix<10; ix++)
		{
		servers[ix].sysid[0]='\0';
		}*/



}


