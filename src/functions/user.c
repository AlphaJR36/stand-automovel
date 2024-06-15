#include <stdio.h>
#include <string.h>

#include "../include/user.h"
#include "../include/utility.h"
#include "../include/header.h"

#define FILENAME_USERS "users.txt"

int authenticateUser(User users[], int count, char *username, char *password)
{
  for (int i = 0; i < count; i++)
  {
    if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
    {
      return 1;
    }
  }
  return 0;
}

void registerUser(User users[], int *count)
{
  if (*count >= MAX_USERS)
  {
    warning("Limite de utilizadores atingido.\n");
    return;
  }

  User newUser;

  headerSignUp();
  lineBreak(2);
  printf("Introduza o nome de utilizador: ");
  fgets(newUser.username, 50, stdin);
  newUser.username[strcspn(newUser.username, "\n")] = '\0';

  for (int i = 0; i < *count; i++)
  {
    if (strcmp(users[i].username, newUser.username) == 0)
    {
      lineBreak(1);
      error("O nome de utilizador já esta em uso.");
      printf("Pressione ENTER para continuar...");
      getchar();
      return;
    }
  }

  printf("Introduza a palavra-passe: ");
  hideInput(newUser.password, 50);

  users[*count] = newUser;
  (*count)++;
  lineBreak(2);
  success("O utilizador foi criado.");
  printf("Pressione ENTER para continuar...");
  getchar();

  saveUsers(users, *count);
}

void saveUsers(User users[], int count)
{
  FILE *file = fopen(FILENAME_USERS, "w");
  if (file == NULL)
  {
    error("Abrir ficheiro para guardar utilizadores.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s:%s\n", users[i].username, users[i].password);
  }

  fclose(file);
}

void loadUsers(User users[], int *count)
{
  FILE *file = fopen(FILENAME_USERS, "r");
  if (file == NULL)
  {
    error("Abrir ficheiro para carregar utilizadores.\n");
    return;
  }

  while (fscanf(file, "%49[^:]:%49[^\n]\n", users[*count].username, users[*count].password) == 2)
  {
    (*count)++;
  }

  fclose(file);
}
