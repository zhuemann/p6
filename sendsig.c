///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019-2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        sendsig.c
// Semester:         CS 354 Spring 2020
//
// Author:           Zach Huemann
// Email:            zhuemann@wisc.eddu
// CS Login:         huemann
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////


#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

/*
 *Takes in arguements for -i and -u and sends the repsetive signals
 *to the input pid number given as arguement 1 and 2
 */
int main( int argc, char *argv[] ) {
   
    //checks to make sure we have the correct number of arguments
    if( argc > 3 ) {
        printf("Too many arguments.\n");
        exit(1);
    } 
    if (argc < 2) {
        printf("not enough arguments.\n");
	exit(1);
    }
    
    //sets up the pid argument for kill
    char pid[20];
    strcpy(pid,argv[2]);
    //string to number conversion
    int pidNum = atoi(pid);

    //sends the sigint command to pidnum if -i arguement used
    if (strcmp(argv[1], "-i") == 0) {
	//sends the signal to the program
        kill( pidNum, SIGINT );
    }
    //sends the sigusr1 signal to pid if -u aruement is used
    else if (strcmp(argv[1], "-u" ) == 0) {
	//sends the signal to the program
	kill( pidNum, SIGUSR1 );
    }

    else {
        printf("invalid input command to send signal\n");
	exit(1);
    }


    return 0;

}
