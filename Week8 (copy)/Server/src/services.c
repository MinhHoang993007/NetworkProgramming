#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/services.h"
#include "../inc/accountSystem.h"

accessPermit* logedIn = NULL;
int logedInCount = 0;

int init(char* inputFile) {
  if(openInputStream(inputFile) == IO_ERROR) {
    printf("Cann\'t read input file!\n");
    exit(0);
  } else return 0;
}

void accountRegister () {
  // 1. read data from keyboard
  userNameType newUserName;
  passwordType password;

  printf ("Username: ");
  scanf ("%s", newUserName);
  getchar();

  // 2. check ifExist
  if(isExistUserName(newUserName) == ACCOUNT_NOT_EXIST) {
    printf ("Password: ");
    scanf ("%s", password);
    getchar();

    // 3. add to user list. status = idle
    newAccount(newUserName, password, IDLE);
    printf("Successful registration. Activation required.");
  storeAccountDataToFile(outputFilePath);
    printf("\n");
    if(PRINT_DB == 1) printDB();

  } else {
    printf ("Account existed\n");
    return;
  }
}

void activate (userNameType userName, passwordType password) {
  int res;
  account* account_activate = getAccount (userName, password, &res);
  if(account_activate != NULL) {
    activateAccount(account_activate);
    if(PRINT_DB == 1) printDB();
  }
}

int logIn (char* IP, userNameType userName, passwordType password) {
  int res;
  account* logInAccount = getAccount (userName, password, &res);
  printf("Res code: %d\n", res);
  if(logInAccount == NULL)
    {
      printf("Error: Login error\n");
      return res;
    }


  if(logedInCount == 0) {
    logedIn = (accessPermit*)malloc(sizeof(accessPermit));
    logedInCount++;

  } else {
    logedIn = realloc(logedIn, sizeof(accessPermit)*(logedInCount+1));
    logedInCount++;
  }

  strcpy(logedIn[logedInCount-1].userName, logInAccount->userName);
  strcpy(logedIn[logedInCount-1].IP, IP);

  printf("Hello %s\n", logedIn[logedInCount-1].userName);
  if(PRINT_LOGEDIN == 1) printLogedInAccount();

  res = LOGIN_SUCCESS;
  return res;
}

int isLogedIn (char* IP) {
  if(logInInfoGet(IP) == NULL)
    return NOT_LOGED_IN;
  else return LOGED_IN;
}

void freeLogIn() {
free(logedIn);
}

accessPermit* logInInfoGet(char* IP) {
  if(logedIn == NULL) return NULL;

  for(int i = 0; i < logedInCount; i++) {
    if(strcmp(logedIn[i].IP, IP) == 0)
      return  &logedIn[i];
  }
  return NULL;
}

void search () {
  // 1. read data from keyboard
  userNameType userName;
  passwordType password;

  printf ("Username: ");
  scanf ("%s", userName);
  getchar();

  if(isExistUserName(userName) == ACCOUNT_NOT_EXIST) {
    printf ("Cannot find account\n");
    return;
  }

  account* accountAccess = getAccountByUserName(userName);

  if(accountAccess->status == BLOCKED) {
    printf ("Account is blocked");
    printf("\n");
  } else if(accountAccess->status == IDLE) {
    printf ("Account is not activated");
    printf("\n");
  } else if(accountAccess->status == ACTIVE) {
    printf ("Account is active");
    printf("\n");
  }
}

void changePass (char* IP, passwordType newPassword) {
  logedIn = logInInfoGet(IP);

  account* accountAccess = getAccountByUserName(logedIn->userName);

  accountChangePass(accountAccess, newPassword);

  /*
    passwordType password;
    int checkPassRes = checkPassword(accountAccess, password);

    if(checkPassRes == PASS_CORRECT) {
    accountChangePass(accountAccess, newPassword);

    if(PRINT_DB == 1) printDB();

    printf ("Password is changed");
    printf("\n");
    } else {
    if(checkPassRes == PASS_INCORRECT)
    printf ("Current password is incorrect, please try again\n");
    else if(checkPassRes == ACCOUNT_BLOCKED)
    printf ("Account is blocked\n");
    }*/
}

void signOut (char* IP) {
  accessPermit* logedIn = logInInfoGet(IP);

  printf ("Goodbye %s", logedIn->userName);
  printf("\n");

  for(int i=0; i < logedInCount; i++) {
    if(strcmp(logedIn[i].IP, IP) == 0) {
      for(int j = i+1; j < logedInCount; j++)
	logedIn[j-1] = logedIn[j];
      logedInCount--;
      logedIn = realloc(logedIn, sizeof(accessPermit)*logedInCount);

      if(PRINT_LOGEDIN == 1) printLogedInAccount();
      break;
    }
  }
}

void printLogedInAccount() {
  printf ("---------------------------------");
  printf("\n");
  printf ("ACCOUNT LOGED IN:");
  printf("\n");
  printf("\n");
  for(int i=0; i < logedInCount; i++) {
    printf ("%s\n", logedIn[i].IP);
    printf ("\t%s\n", logedIn[i].userName);
  }
  printf ("---------------------------------");
  printf("\n");
}
