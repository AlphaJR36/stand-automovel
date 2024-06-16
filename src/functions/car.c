#include <stdio.h>
#include <string.h>

#include "../include/car.h"
#include "../include/utility.h"
#include "../include/purchase.h"
#include "../include/header.h"

void addCar(Car cars[], int *count)
{
  if (*count < MAX_CARS)
  {
    Car newCar;

    headerAddNewCar();
    lineBreak(2);
    printf("Insira o modelo do carro: ");
    fgets(newCar.model, 50, stdin);
    newCar.model[strcspn(newCar.model, "\n")] = '\0';

    printf("Insira a marca do carro: ");
    fgets(newCar.brand, 50, stdin);
    newCar.brand[strcspn(newCar.brand, "\n")] = '\0';

    printf("Insira o ano do carro: ");
    scanf("%d", &newCar.year);
    getchar();

    printf("Insira o preço do carro (em euros): ");
    scanf("%f", &newCar.price);
    getchar();

    cars[*count] = newCar;
    (*count)++;
    success("O carro foi adicionado!\n");

    saveCars(cars, *count);
  }
  else
  {
    warning("O limite de carros foi atingido.\n");
  }
}

void listCars(Car cars[], int count)
{
  headerShowCars();
  lineBreak(2);

  if (count == 0)
  {
    warning("Não há carros disponíveis.\n");
    return;
  }

  printf("Todos os carros disponíveis:\n\n");
  for (int i = 0; i < count; i++)
  {
    printf("Modelo: %s, Marca: %s, Ano: %d, Preço: €%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);
  }
}

void searchCar(Car cars[], int count)
{
  headerFindByModel();
  lineBreak(2);

  if (count == 0)
  {
    warning("Não há carros disponíveis para pesquisa.\n");
    return;
  }

  char searchModel[50];
  printf("Insira o modelo do carro que deseja procurar: ");
  fgets(searchModel, 50, stdin);
  searchModel[strcspn(searchModel, "\n")] = '\0';

  int found = 0;
  for (int i = 0; i < count; i++)
  {
    if (strcmp(cars[i].model, searchModel) == 0)
    {
      printf("Carro encontrado - Modelo: %s, Marca: %s, Ano: %d, Preço: €%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);
      found = 1;
      break;
    }
  }

  if (!found)
  {
    error("Nenhum carro encontrado com esse modelo.\n");
  }
}

void removeCar(Car cars[], int *count)
{
  headerRemoveCar();
  lineBreak(2);

  if (*count == 0)
  {
    warning("Não há carros disponíveis para remoção.\n");
    return;
  }

  char model[50];
  printf("Insira o modelo do carro a ser removido: ");
  fgets(model, 50, stdin);
  model[strcspn(model, "\n")] = '\0';

  int found = 0;
  for (int i = 0; i < *count; i++)
  {
    if (strcmp(cars[i].model, model) == 0)
    {
      for (int j = i; j < *count - 1; j++)
      {
        cars[j] = cars[j + 1];
      }
      (*count)--;
      found = 1;
      success("O carro foi removido!\n");

      saveCars(cars, *count);
      break;
    }
  }

  if (!found)
  {
    error("Nenhum carro encontrado com esse modelo.\n");
  }
}

void buyCar(Car cars[], int *count, char purchases[][5][50], int *purchaseCount, char *username)
{
  headerBuyCar();
  lineBreak(2);

  if (*count == 0)
  {
    warning("Nenhum carro está disponível para compra.\n");
    return;
  }

  char buyModel[50];
  printf("Insira o modelo do carro que deseja comprar: ");
  fgets(buyModel, 50, stdin);
  buyModel[strcspn(buyModel, "\n")] = '\0';

  int found = 0;
  for (int i = 0; i < *count; i++)
  {
    if (strcmp(cars[i].model, buyModel) == 0)
    {
      printf("Carro encontrado - Modelo: %s, Marca: %s, Ano: %d, Preço: €%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);

      // Confirmar se deseja comprar o carro
      printf("Deseja comprar este carro? (S/N): ");
      char choice;
      scanf(" %c", &choice);
      getchar(); // Consumir o caractere newline pendente no buffer

      if (choice == 'S' || choice == 's')
      {
        success("A compra foi realizada!\n");

        // Adicionar informações da compra ao histórico
        snprintf(purchases[*purchaseCount][0], 50, "%s", username);
        snprintf(purchases[*purchaseCount][1], 50, "%s", cars[i].model);
        snprintf(purchases[*purchaseCount][2], 50, "%s", cars[i].brand);
        snprintf(purchases[*purchaseCount][3], 50, "%d", cars[i].year);
        snprintf(purchases[*purchaseCount][4], 50, "%.2f", cars[i].price);
        (*purchaseCount)++;

        // Remover o carro do array de carros
        for (int j = i; j < *count - 1; j++)
        {
          cars[j] = cars[j + 1];
        }
        (*count)--;
      }
      else
      {
        printf("Compra cancelada.\n");
      }

      found = 1;
      break;
    }
  }

  if (!found)
  {
    error("O carro não foi encontrado.\n");
  }

  saveCars(cars, *count);
  savePurchases(purchases, *purchaseCount);
}

void saveCars(Car cars[], int count)
{
  FILE *file = fopen("cars.txt", "w");
  if (file == NULL)
  {
    error("Erro ao abrir o arquivo de carros.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s:%s:%d:%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);
  }

  fclose(file);
}

void loadCars(Car cars[], int *count)
{
  FILE *file = fopen("cars.txt", "r");
  if (file == NULL)
  {
    return;
  }

  char line[200];
  while (fgets(line, sizeof(line), file))
  {
    sscanf(line, "%[^:]:%[^:]:%d:%f", cars[*count].model, cars[*count].brand, &cars[*count].year, &cars[*count].price);
    (*count)++;
  }

  fclose(file);
}
