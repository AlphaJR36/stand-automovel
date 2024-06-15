#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../include/utility.h"

void clearScreen()
{
  system("cls");
}

void hideInput(char *input, int maxLength)
{
  int i = 0;
  char ch;
  while (i < maxLength - 1 && (ch = _getch()) != '\r')
  {
    input[i++] = ch;
    printf("*");
  }
  input[i] = '\0';
}

void showLoginSuccessAnimation()
{
  printf("\n\nAutenticação bem-sucedida!\n");
  printf("Pressione Enter para continuar...");
  getchar();
}

int isAdminUser(char *username)
{
  return strcmp(username, "root") == 0;
}
