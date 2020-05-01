///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019-2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        division.c
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


int successCounter = 0;
/**
 *The handler for the floating point expcetion
 */
void handler_SIGFPE() {
    
    printf("Error: a division by 0 operation was attempted.\n");
    printf("%s%d%s","Total number of operations successfully completed: ",successCounter,"\n");
    printf("The program will be terminated.\n");	
    exit(0);
}
/*
 *The handler for signal interupt or control c
 */
void handler_SIGINT() {
    printf("\n");
    printf("%s%d%s","Total number of operations successfully completed: ",successCounter,"\n");
    printf("The program will be terminated.\n");
    exit(0);

}
/*
 *The part of the calculator that will be reapted
 *and is called again and again in main function
 *until it is exited by diving by zero or control c
 *
 */
void repeatedDivision() {
    //bassic print statements so user knows what to input
    printf("Enter first integer: ");
    //creates buffer of length 100
    char buf1[100];
    fgets(buf1, 100, stdin);
    int num1 = atoi(buf1);

    printf("Enter second integer: ");
    //creates buffer of length 100
    char buf2[100];
    fgets(buf2, 100, stdin);
    int num2 = atoi(buf2);
    //does the division to be printed
    int quotient = num1/num2;
    int remainder = num1%num2;
    //prints teh information as the website asks
    printf("%d%s%d%s%d%s%d%s",num1," / ", num2, " is ", quotient, " with a remainder of ", remainder,"\n");
    //incrementes the succesfull division counters
    successCounter++;
   
}

/*
 *The main function that sets up the signals and then
 *inside a while loop, it calls the reapted division
 *
 */
int main() {

    //sets up signal handler for floating point expcetion
    struct sigaction fpe;
    memset(&fpe,0,sizeof(fpe));
    fpe.sa_handler = handler_SIGFPE;
    //checks for valid sigaction setup
    if (sigaction(SIGFPE, &fpe, NULL) != 0) {
        printf("Error binding sigFPE handler\n");
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

    //infinite loop that calls repeatedDivision so the only way out is by
    //a signal input
    while (1) {
        repeatedDivision();
    }
    //calls main recurisvely

    return 0;
}

