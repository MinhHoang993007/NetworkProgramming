#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include "accountSystem.h"
#define WRONG_ACTIVECODE_BLOCK_COUNT_DOWN 3
#define WRONG_PASS_BLOCK_COUNT_DOWN 3
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/menu.h"
#include "../inc/accountSystem.h"

int menu(char* inputFile);
void printMenu ();
void accountRegister ();
void activate ();
void logIn  ();
int isLogedIn (char* userName);
account* accessAcc ();
void search ();
void changePass ();
void signOut ();

#endif
