#include <stdio.h>
#include <string.h>

#include "../include/purchase.h"
#include "../include/utility.h"

#define FILENAME_PURCHASES "purchases.txt"

void listPurchases(char purchases[][5][50], int count)
{
  if (count == 0)
  {
    error("Não há compras realizadas.\n");
    return;
  }

  printf("Histórico de Compras:\n");
  for (int i = 0; i < count; i++)
  {
    printf("Utilizador: %s, Modelo: %s, Marca: %s, Ano: %s, Preço: %s\n", purchases[i][0], purchases[i][1], purchases[i][2], purchases[i][3], purchases[i][4]);
  }
}

void savePurchases(char purchases[][5][50], int count)
{
  FILE *file = fopen(FILENAME_PURCHASES, "w");
  if (file == NULL)
  {
    error("Abrir ficheiro para guardar compras.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s,%s,%s,%s,%s\n", purchases[i][0], purchases[i][1], purchases[i][2], purchases[i][3], purchases[i][4]);
  }

  fclose(file);
}

void loadPurchases(char purchases[][5][50], int *count)
{
  FILE *file = fopen(FILENAME_PURCHASES, "r");
  if (file == NULL)
  {
    error("Abrir ficheiro para carregar compras.\n");
    return;
  }

  while (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]\n", purchases[*count][0], purchases[*count][1], purchases[*count][2], purchases[*count][3], purchases[*count][4]) == 5)
  {
    (*count)++;
  }

  fclose(file);
}
