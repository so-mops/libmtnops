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
#define ARG1 1
#define ARG2 2
#define MAXFIELDS 3
#define MINFIELDS 2
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
char line[80];
char *search = " \t";
char *token;
char words[MAXFIELDS][50];
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
			if (wordctr>=MAXFIELDS){break;}
			wordptr=strtok(NULL, search);
			}
		//Parse the known keywords
		if (wordctr < MINFIELDS)
			{
			//printf("invalid line: not enough fields -- \" %s \" -- ignoring\n", line);
			}
		/*else if (strcmp(words[KEYWORD], "PORT") == 0)
			{
			printf("listening port = %s\n", words[VALUE]);
			sscanf(words[VALUE], "%i", &SERVER_PORT);
			}
		else if (strcmp(words[KEYWORD], "TELID") == 0)
			{
			printf("Telescope ID = %s\n", words[VALUE]);
			sprintf(TELESCOPE_ID, "%s", words[VALUE]);
			}*/
		else
			{
			printf("unrecognized keyword: %s -- ignoring\n", words[KEYWORD]);
			}
	
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


