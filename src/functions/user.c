#include <stdio.h>
#include <string.h>

#include "../include/user.h"

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
    printf("Limite de usuários atingido.\n");
    return;
  }

  User newUser;
  printf("Digite o username: ");
  fgets(newUser.username, 50, stdin);
  newUser.username[strcspn(newUser.username, "\n")] = '\0';

  printf("Digite a senha: ");
  fgets(newUser.password, 50, stdin);
  newUser.password[strcspn(newUser.password, "\n")] = '\0';

  users[*count] = newUser;
  (*count)++;
  printf("Usuário registrado com sucesso!\n");
}

void saveUsers(User users[], int count)
{
  FILE *file = fopen(FILENAME_USERS, "w");
  if (file == NULL)
  {
    printf("Erro ao abrir arquivo para salvar usuários.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s,%s\n", users[i].username, users[i].password);
  }

  fclose(file);
}

void loadUsers(User users[], int *count)
{
  FILE *file = fopen(FILENAME_USERS, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir arquivo para carregar usuários.\n");
    return;
  }

  while (fscanf(file, "%49[^,],%49[^\n]\n", users[*count].username, users[*count].password) == 2)
  {
    (*count)++;
  }

  fclose(file);
}
