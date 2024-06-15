#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "components/header.c"

#include "include/car.h"
#include "include/user.h"
#include "include/purchase.h"
#include "include/utility.h"

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
      headerLogin();
      printf("\n\n1. Entrar\n");
      printf("2. Criar uma conta\n");
      printf("3. Sair\n\n");
      printf("Escolha uma opção: ");
      scanf("%d", &option);
      getchar();

      clearScreen();

      if (option == 1)
      {
        headerSignIn();
        lineBreak(2);
        printf("Introduza o nome de utilizador: ");
        fgets(username, 50, stdin);
        username[strcspn(username, "\n")] = '\0';
        printf("Introduza a palavra-passe: ");
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
          lineBreak(2);
          error("Nome de utilizador ou palavra-passe incorretos.\n");
          printf("Pressione ENTER para continuar...");
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
        error("Opção inválida! Tente novamente.\n");
        printf("Pressione ENTER para continuar...");
        getchar();
      }
    }

    while (authenticated && !exitProgram)
    {
      clearScreen();
      header();

      if (isAdminUser(username))
      {
        printf("\n\n1. Adicionar novo carro\n");
        printf("2. Exibir todos os carros\n");
        printf("3. Procurar carro pelo modelo\n");
        printf("4. Remover carro\n");
        printf("5. Ver histórico de compras\n");
        printf("6. Terminar sessão\n\n");
      }
      else
      {
        printf("\n\n1. Listar todos os carros\n");
        printf("2. Procurar carro pelo modelo\n");
        printf("3. Comprar carro\n");
        printf("4. Terminar sessão\n\n");
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
          listPurchases(purchases, purchaseCount);
          break;
        case 6:
          saveCars(cars, carCount);
          savePurchases(purchases, purchaseCount);
          success("A sessão foi terminada.\n");
          authenticated = 0;
          break;
        default:
          error("Opção inválida! Tente novamente.\n");
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
            snprintf(purchases[purchaseCount][1], 50, "%s", cars[carCount - 1].model);
            snprintf(purchases[purchaseCount][2], 50, "%s", cars[carCount - 1].brand);
            snprintf(purchases[purchaseCount][3], 50, "%d", cars[carCount - 1].year);
            snprintf(purchases[purchaseCount][4], 50, "%.2f", cars[carCount - 1].price);
            purchaseCount++;
          }
          else
          {
            warning("Não há carros disponíveis para compra.\n");
          }
          break;
        case 4:
          saveCars(cars, carCount);
          savePurchases(purchases, purchaseCount);
          success("A sessão foi terminada.\n");
          authenticated = 0;
          break;
        default:
          error("Opção inválida! Tente novamente.\n");
        }
      }
      printf("Pressione ENTER para continuar...");
      getchar();
    }
  }

  return 0;
}
