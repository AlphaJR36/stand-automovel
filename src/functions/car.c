#include <stdio.h>
#include <string.h>

#include "../include/car.h"
#include "../include/utility.h"

#define FILENAME_CARS "cars.txt"

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
    printf("Carro não encontrado.\n");
  }
}

void removeCar(Car cars[], int *count)
{
  if (*count == 0)
  {
    printf("Nenhum carro disponível para remover.\n");
    return;
  }

  char removeModel[50];
  printf("Digite o modelo do carro que deseja remover: ");
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
      printf("Carro removido com sucesso.\n");
      found = 1;
      break;
    }
  }

  if (!found)
  {
    printf("Carro não encontrado.\n");
  }
}

void buyCar(Car cars[], int *count, char *username)
{
  if (*count == 0)
  {
    printf("Nenhum carro disponível para compra.\n");
    return;
  }

  char buyModel[50];
  printf("Digite o modelo do carro que deseja comprar: ");
  fgets(buyModel, 50, stdin);
  buyModel[strcspn(buyModel, "\n")] = '\0';

  int found = 0;
  for (int i = 0; i < *count; i++)
  {
    if (strcmp(cars[i].model, buyModel) == 0)
    {
      printf("Compra realizada com sucesso!\n");
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
    printf("Carro não encontrado.\n");
  }
}

void saveCars(Car cars[], int count)
{
  FILE *file = fopen(FILENAME_CARS, "w");
  if (file == NULL)
  {
    printf("Erro ao abrir arquivo para salvar carros.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s,%s,%d,%.2f\n", cars[i].model, cars[i].brand, cars[i].year, cars[i].price);
  }

  fclose(file);
}

void loadCars(Car cars[], int *count)
{
  FILE *file = fopen(FILENAME_CARS, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir arquivo para carregar carros.\n");
    return;
  }

  while (fscanf(file, "%49[^,],%49[^,],%d,%f\n", cars[*count].model, cars[*count].brand, &cars[*count].year, &cars[*count].price) == 4)
  {
    (*count)++;
  }

  fclose(file);
}
