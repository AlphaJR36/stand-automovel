#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#include "components/header.c"

typedef struct
{
  char model[50];
  char brand[50];
  int year;
  float price;
} Car;

typedef struct
{
  char username[50];
  char password[50];
} User;

#define MAX_CARS 100
#define MAX_USERS 10
#define MAX_PURCHASES 100
#define FILENAME_CARS "cars.txt"
#define FILENAME_USERS "users.txt"
#define FILENAME_PURCHASES "purchases.txt"

void addCar(Car cars[], int *count);
void listCars(Car cars[], int count);
void searchCar(Car cars[], int count);
void removeCar(Car cars[], int *count);
void buyCar(Car cars[], int *count, char *username);
void clearScreen();
void saveCars(Car cars[], int count);
void loadCars(Car cars[], int *count);
void saveUsers(User users[], int count);
void loadUsers(User users[], int *count);
void savePurchases(char purchases[][5][50], int count);
void loadPurchases(char purchases[][5][50], int *count);
void listPurchases(char purchases[][5][50], int count);
int authenticateUser(User users[], int count, char *username, char *password);
void registerUser(User users[], int *count);
void hideInput(char *str, int max);
void generateInvoice(char *username, Car car);
void showLoginSuccessAnimation();
int isAdminUser(char *username);

int main()
{
  system("chcp 65001");
  system("cls");

  Car cars[MAX_CARS];
  User users[MAX_USERS];
  char purchases[MAX_PURCHASES][5][50];
  int carCount = 0;
  int userCount = 0;
  int purchaseCount = 0;
  int option;
  char username[50];
  char password[50];
  int authenticated = 0;
  int exitProgram = 0;

  loadCars(cars, &carCount);
  loadUsers(users, &userCount);
  loadPurchases(purchases, &purchaseCount);

  while (!exitProgram)
  {
    authenticated = 0;
    while (!authenticated && !exitProgram)
    {
      clearScreen();
      printf("Login do Sistema de Stand de Automóveis\n");
      printf("1. Login\n");
      printf("2. Registrar\n");
      printf("3. Sair\n");
      printf("Escolha uma opção: ");
      scanf("%d", &option);
      getchar();

      clearScreen();

      if (option == 1)
      {
        printf("Digite seu username: ");
        fgets(username, 50, stdin);
        username[strcspn(username, "\n")] = '\0';
        printf("Digite sua senha: ");
        hideInput(password, 50);

        if (strcmp(username, "root") == 0 && strcmp(password, "admin") == 0)
        {
          authenticated = 1;
          showLoginSuccessAnimation();
        }
        else if (authenticateUser(users, userCount, username, password))
        {
          authenticated = 1;
          showLoginSuccessAnimation();
        }
        else
        {
          printf("Autenticação falhou. Tente novamente.\n");
          printf("Pressione Enter para continuar...");
          getchar();
        }
      }
      else if (option == 2)
      {
        registerUser(users, &userCount);
        saveUsers(users, userCount);
      }
      else if (option == 3)
      {
        exitProgram = 1;
        break;
      }
      else
      {
        printf("Opção inválida! Tente novamente.\n");
        printf("Pressione Enter para continuar...");
        getchar();
      }
    }

    while (authenticated && !exitProgram)
    {
      clearScreen();
      header();
      printf("\n\nSistema de Stand de Automóveis\n");

      if (isAdminUser(username))
      {
        printf("1. Adicionar novo carro\n");
        printf("2. Listar todos os carros\n");
        printf("3. Buscar carro por modelo\n");
        printf("4. Remover carro\n");
        printf("5. Comprar carro\n");
        printf("6. Listar histórico de compras\n");
        printf("7. Terminar sessão\n");
      }
      else
      {
        printf("1. Listar todos os carros\n");
        printf("2. Buscar carro por modelo\n");
        printf("3. Comprar carro\n");
        printf("4. Listar histórico de compras\n");
        printf("5. Terminar sessão\n");
      }

      printf("Escolha uma opção: ");
      scanf("%d", &option);
      getchar();

      clearScreen();

      if (isAdminUser(username))
      {
        switch (option)
        {
        case 1:
          addCar(cars, &carCount);
          break;
        case 2:
          listCars(cars, carCount);
          break;
        case 3:
          searchCar(cars, carCount);
          break;
        case 4:
          removeCar(cars, &carCount);
          break;
        case 5:
          if (carCount > 0)
          {
            buyCar(cars, &carCount, username);
            snprintf(purchases[purchaseCount][0], 50, "%s", username);
            snprintf(purchases[purchaseCount][1], 50, "%s", cars[carCount].model);
            snprintf(purchases[purchaseCount][2], 50, "%s", cars[carCount].brand);
            snprintf(purchases[purchaseCount][3], 50, "%d", cars[carCount].year);
            snprintf(purchases[purchaseCount][4], 50, "%.2f", cars[carCount].price);
            purchaseCount++;
          }
          else
          {
            printf("Não há carros disponíveis para compra.\n");
          }
          break;
        case 6:
          listPurchases(purchases, purchaseCount);
          break;
        case 7:
          saveCars(cars, carCount);
          savePurchases(purchases, purchaseCount);
          printf("Terminando sessão e salvando dados...\n");
          authenticated = 0;
          break;
        default:
          printf("Opção inválida! Tente novamente.\n");
        }
      }
      else
      {
        switch (option)
        {
        case 1:
          listCars(cars, carCount);
          break;
        case 2:
          searchCar(cars, carCount);
          break;
        case 3:
          if (carCount > 0)
          {
            buyCar(cars, &carCount, username);
            snprintf(purchases[purchaseCount][0], 50, "%s", username);
            snprintf(purchases[purchaseCount][1], 50, "%s", cars[carCount].model);
            snprintf(purchases[purchaseCount][2], 50, "%s", cars[carCount].brand);
            snprintf(purchases[purchaseCount][3], 50, "%d", cars[carCount].year);
            snprintf(purchases[purchaseCount][4], 50, "%.2f", cars[carCount].price);
            purchaseCount++;
          }
          else
          {
            printf("Não há carros disponíveis para compra.\n");
          }
          break;
        case 4:
          listPurchases(purchases, purchaseCount);
          break;
        case 5:
          saveCars(cars, carCount);
          savePurchases(purchases, purchaseCount);
          printf("Terminando sessão e salvando dados...\n");
          authenticated = 0;
          break;
        default:
          printf("Opção inválida! Tente novamente.\n");
        }
      }
      printf("Pressione Enter para continuar...");
      getchar();
    }
  }

  return 0;
}

void addCar(Car cars[], int *count)
{
  if (*count < MAX_CARS)
  {
    Car newCar;
    printf("Digite o modelo do carro: ");
    fgets(newCar.model, 50, stdin);
    newCar.model[strcspn(newCar.model, "\n")] = '\0';

    printf("Digite a marca do carro: ");
    fgets(newCar.brand, 50, stdin);
    newCar.brand[strcspn(newCar.brand, "\n")] = '\0';

    printf("Digite o ano do carro: ");
    scanf("%d", &newCar.year);
    getchar();

    printf("Digite o preço do carro (em euros): ");
    scanf("%f", &newCar.price);
    getchar();

    cars[*count] = newCar;
    (*count)++;
    printf("Carro adicionado com sucesso!\n");
  }
  else
  {
    printf("Limite de carros atingido.\n");
  }
}

void listCars(Car cars[], int count)
{
  if (count == 0)
  {
    printf("Nenhum carro disponível.\n");
    return;
  }

  printf("Lista de Carros Disponíveis:\n");
  for (int i = 0; i < count; i++)
  {
    printf("Modelo: %s, Marca: %s, Ano: %d, Preço: €%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);
  }
}

void searchCar(Car cars[], int count)
{
  if (count == 0)
  {
    printf("Nenhum carro disponível.\n");
    return;
  }

  char searchModel[50];
  printf("Digite o modelo do carro que deseja buscar: ");
  fgets(searchModel, 50, stdin);
  searchModel[strcspn(searchModel, "\n")] = '\0';

  printf("Resultados da Busca:\n");
  for (int i = 0; i < count; i++)
  {
    if (strstr(cars[i].model, searchModel) != NULL)
    {
      printf("Modelo: %s, Marca: %s, Ano: %d, Preço: €%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);
    }
  }
}

void removeCar(Car cars[], int *count)
{
  if (*count == 0)
  {
    printf("Nenhum carro disponível para remover.\n");
    return;
  }

  char model[50];
  printf("Digite o modelo do carro que deseja remover: ");
  fgets(model, 50, stdin);
  model[strcspn(model, "\n")] = '\0';

  for (int i = 0; i < *count; i++)
  {
    if (strcmp(cars[i].model, model) == 0)
    {
      for (int j = i; j < *count - 1; j++)
      {
        cars[j] = cars[j + 1];
      }
      (*count)--;
      printf("Carro removido com sucesso!\n");
      return;
    }
  }
  printf("Carro não encontrado.\n");
}

void buyCar(Car cars[], int *count, char *username)
{
  if (*count == 0)
  {
    printf("Nenhum carro disponível para compra.\n");
    return;
  }

  char model[50];
  printf("Digite o modelo do carro que deseja comprar: ");
  fgets(model, 50, stdin);
  model[strcspn(model, "\n")] = '\0';

  for (int i = 0; i < *count; i++)
  {
    if (strcmp(cars[i].model, model) == 0)
    {
      generateInvoice(username, cars[i]);
      for (int j = i; j < *count - 1; j++)
      {
        cars[j] = cars[j + 1];
      }
      (*count)--;
      printf("Compra realizada com sucesso!\n");
      return;
    }
  }
  printf("Carro não encontrado.\n");
}

void clearScreen()
{
  system("cls || clear");
}

void saveCars(Car cars[], int count)
{
  FILE *file = fopen(FILENAME_CARS, "w");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de carros para escrita.\n");
    return;
  }
  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s;%s;%d;%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);
  }
  fclose(file);
}

void loadCars(Car cars[], int *count)
{
  FILE *file = fopen(FILENAME_CARS, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de carros para leitura.\n");
    return;
  }
  while (fscanf(file, "%49[^;];%49[^;];%d;%f\n", cars[*count].model, cars[*count].brand, &cars[*count].year, &cars[*count].price) != EOF)
  {
    (*count)++;
  }
  fclose(file);
}

void saveUsers(User users[], int count)
{
  FILE *file = fopen(FILENAME_USERS, "w");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de usuários para escrita.\n");
    return;
  }
  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s;%s\n", users[i].username, users[i].password);
  }
  fclose(file);
}

void loadUsers(User users[], int *count)
{
  FILE *file = fopen(FILENAME_USERS, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de usuários para leitura.\n");
    return;
  }
  while (fscanf(file, "%49[^;];%49[^\n]\n", users[*count].username, users[*count].password) != EOF)
  {
    (*count)++;
  }
  fclose(file);
}

void savePurchases(char purchases[][5][50], int count)
{
  FILE *file = fopen(FILENAME_PURCHASES, "w");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de compras para escrita.\n");
    return;
  }
  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s;%s;%s;%s;%s\n", purchases[i][0], purchases[i][1], purchases[i][2], purchases[i][3], purchases[i][4]);
  }
  fclose(file);
}

void loadPurchases(char purchases[][5][50], int *count)
{
  FILE *file = fopen(FILENAME_PURCHASES, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de compras para leitura.\n");
    return;
  }
  while (fscanf(file, "%49[^;];%49[^;];%49[^;];%49[^;];%49[^\n]\n", purchases[*count][0], purchases[*count][1], purchases[*count][2], purchases[*count][3], purchases[*count][4]) != EOF)
  {
    (*count)++;
  }
  fclose(file);
}

void listPurchases(char purchases[][5][50], int count)
{
  if (count == 0)
  {
    printf("Nenhuma compra realizada.\n");
    return;
  }

  printf("Histórico de Compras:\n");
  for (int i = 0; i < count; i++)
  {
    printf("Usuário: %s, Modelo: %s, Marca: %s, Ano: %s, Preço: €%s\n", purchases[i][0], purchases[i][1], purchases[i][2], purchases[i][3], purchases[i][4]);
  }
}

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
  printf("Digite um username: ");
  fgets(newUser.username, 50, stdin);
  newUser.username[strcspn(newUser.username, "\n")] = '\0';

  printf("Digite uma senha: ");
  hideInput(newUser.password, 50);

  users[*count] = newUser;
  (*count)++;
  printf("Usuário registrado com sucesso!\n");
}

void hideInput(char *str, int max)
{
  int i = 0;
  char ch;
  while ((ch = getch()) != 13 && i < max - 1)
  {
    if (ch == 8)
    {
      if (i > 0)
      {
        i--;
        printf("\b \b");
      }
    }
    else
    {
      str[i++] = ch;
      printf("*");
    }
  }
  str[i] = '\0';
  printf("\n");
}

void generateInvoice(char *username, Car car)
{
  printf("Gerando fatura para %s...\n", username);
  printf("Carro comprado: %s %s (%d) - €%.2f\n", car.brand, car.model, car.year, car.price);
}

void showLoginSuccessAnimation()
{
  printf("Login bem-sucedido!");
  for (int i = 0; i < 3; i++)
  {
    printf(".");
    Sleep(500);
  }
  printf("\n");
}

int isAdminUser(char *username)
{
  return strcmp(username, "root") == 0;
}
