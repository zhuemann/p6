///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019-2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
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
#include <string.h>
#include <stdlib.h>
#include <time.h>

//global variables for how to long to dleay and a coutner
int delay = 3;
int USR1counter = 0;

//handles the SIGUR1 signal
void handler_SIGUSR1() {
    printf("SIGUSR1 caught!\n");
    USR1counter++;

}
//handles the interupt signal or control c
void handler_SIGINT() {
    
    printf("SIGINT received.\n");
    printf("%s%d%s", "SIGUSR1 was received ",USR1counter, " times. Exiting now.\n");
    exit(0);
    
}

//handles the alarma signal and sets up another alaram of 3 sec
void handler_SIGALRM() {

    printf("PID: ");
    printf("%d",getpid());
    printf("%s", " | Current Time: "); 
    //error handling
    time_t seconds = time(NULL);
    if (seconds == -1) {
	printf("error getting time");
	exit(1);
    }
    
    printf("%s", ctime(&seconds));
    //sets antoher alarm
    alarm(delay);
}

/*
 *Sets up the signals and then sets up a sigle alarm.
 *The alarm signal will set up another onc so it will be
 *a repeated bit of code that will just keep going print
 *the pid every 3 seconds until the inevitable heat of the 
 *the universe. 
 */
int main() {
    //bassic print statements so user knows what is being output
    printf("Pid and time will be printed every 3 seconds.\n");
    printf("Enter ^C to end the program.\n");

    //sets up signal handler for SIGALARM
    struct sigaction sa;
    memset(&sa,0,sizeof(sa));
    sa.sa_handler = handler_SIGALRM;
    //checks for valid sigaction setup
    if (sigaction(SIGALRM, &sa, NULL) != 0) {
        printf("Error binding sigalrm handler\n");
        exit(1);
    }
    //sets up signal handler for usr1
    struct sigaction USR1;
    memset(&USR1,0,sizeof(USR1));
    USR1.sa_handler = handler_SIGUSR1;
    //checks for valid sigaction setup
    if (sigaction(SIGUSR1, &USR1, NULL) != 0) {
        printf("Error binding sigUSR1 handler\n");
        exit(1);
    }
    //sets up signal handler for control c
    struct sigaction sig_int;
    memset(&sig_int,0,sizeof(sig_int));
    sig_int.sa_handler = handler_SIGINT;
    //checks for valid sigaction setup
    if (sigaction(SIGINT, &sig_int, NULL) != 0) {
        printf("Error binding singal interupt handler\n");
        exit(1);
    }
    //calls alarma the first time
    alarm(delay);
    //infinite loop so program rums and alarms can repeart as neededd
    while (1) {
    }
}
