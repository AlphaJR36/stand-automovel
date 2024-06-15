#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "../include/utility.h"

void clearScreen()
{
  system("cls");
}

void hideInput(char *input, int maxLength)
{
  int i = 0;
  char ch;

  while (i < maxLength - 1)
  {
    ch = _getch();

    if (ch == '\r')
    {
      break;
    }
    else if (ch == '\b')
    {
      if (i > 0)
      {
        printf("\b \b");
        i--;
      }
    }
    else
    {
      input[i++] = ch;
      printf("*");
    }
  }

  input[i] = '\0';
}

void showLoginSuccessAnimation()
{
  lineBreak(2);
  setConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  printf("Autenticação bem-sucedida!");
  Sleep(700);
  printf("!");
  Sleep(700);
  printf("!");
  Sleep(700);
  setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reseta para a cor padrão
  lineBreak(1);
}

int isAdminUser(char *username)
{
  return strcmp(username, "root") == 0;
}

void setConsoleColor(int color)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void error(const char *message)
{
  setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
  printf("ERRO: %s\n", message);
  setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void warning(const char *message)
{
  setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  printf("ALERTA: %s\n", message);
  setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void success(const char *message)
{
  setConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  printf("SUCESSO: %s\n", message);
  setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void lineBreak(int count)
{
  for (int i = 0; i < count; i++)
  {
    printf("\n");
  }
}

void printCentered(const char *str, int totalWidth)
{
  int strLen = strlen(str);
  int spaces = (totalWidth - strLen) / 2;

  for (int i = 0; i < spaces; ++i)
  {
    putchar(' ');
  }

  printf("%s", str);
}