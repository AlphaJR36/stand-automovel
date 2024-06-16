#include <stdio.h>
#include <string.h>

#include "../include/car.h"
#include "../include/utility.h"
#include "../include/header.h"

#define FILENAME_CARS "cars.txt"

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
      printf("Modelo: %s, Marca: %s, Ano: %d, Preço: €%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);
      found = 1;
      break;
    }
  }

  if (!found)
  {
    error("O carro não foi encontrado.\n");
  }
}

void removeCar(Car cars[], int *count)
{
  headerRemoveCar();
  lineBreak(2);

  if (*count == 0)
  {
    error("Nenhum carro está disponível para remover.\n");
    return;
  }

  char removeModel[50];
  printf("Insira o modelo do carro que deseja remover: ");
  fgets(removeModel, 50, stdin);
  removeModel[strcspn(removeModel, "\n")] = '\0';

  int found = 0;
  for (int i = 0; i < *count; i++)
  {
    if (strcmp(cars[i].model, removeModel) == 0)
    {
      for (int j = i; j < *count - 1; j++)
      {
        cars[j] = cars[j + 1];
      }
      (*count)--;
      success("O carro foi removido.\n");
      found = 1;
      break;
    }
  }

  if (!found)
  {
    error("O carro não encontrado.\n");
  }
}

void buyCar(Car cars[], int *count, char *username)
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
      success("A compra foi realizada!\n");
      for (int j = i; j < *count - 1; j++)
      {
        cars[j] = cars[j + 1];
      }
      (*count)--;
      found = 1;
      break;
    }
  }

  if (!found)
  {
    error("O carro não foi encontrado.\n");
  }
}

void saveCars(Car cars[], int count)
{
  FILE *file = fopen(FILENAME_CARS, "w");
  if (file == NULL)
  {
    error("Abrir o arquivo para guardar os carros.\n");
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
  FILE *file = fopen(FILENAME_CARS, "r");
  if (file == NULL)
  {
    error("Abrir o arquivo para carregar os carros.\n");
    return;
  }

  while (fscanf(file, "%49[^,],%49[^,],%d,%f\n", cars[*count].model, cars[*count].brand, &cars[*count].year, &cars[*count].price) == 4)
  {
    (*count)++;
  }

  fclose(file);
}
