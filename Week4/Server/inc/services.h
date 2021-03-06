#ifndef __SERVICES_H__
#define __SERVICES_H__

#include <stdio.h>
#include "accountSystem.h"

#define WRONG_ACTIVECODE_BLOCK_COUNT_DOWN 3
#define WRONG_PASS_BLOCK_COUNT_DOWN 3

#define PRINT_LOGEDIN 1

#define LOGED_IN 60
#define NOT_LOGED_IN 61

typedef struct _accessPermit {
 char* IP;
 userNameType userName;
}accessPermit;

extern int logedInCount;

int init(char* inputFile);
void accountRegister ();
account* getAccount (userNameType userName, passwordType password, int *res);
void activate (userNameType userName, passwordType password);
int logIn (char* IP, userNameType userName, passwordType password);
int isLogedIn (char* IP);
accessPermit* logInInfoGet(char* IP);
void search ();
void changePass (char* IP);
void signOut (char* IP);
void printLogedInAccount();

#endif
