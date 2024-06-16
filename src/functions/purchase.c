#include <stdio.h>
#include <string.h>

#include "../include/purchase.h"
#include "../include/utility.h"
#include "../include/header.h"

void listPurchases(char purchases[][5][50], int count)
{
  headerShowPurchaseHistory();
  lineBreak(2);

  if (count == 0)
  {
    error("Não há compras realizadas.");
    return;
  }

  printf("Histórico de Compras:\n");

  for (int i = 0; i < count; i++)
  {
    printf("Utilizador: %s, Modelo: %s, Marca: %s, Ano: %s, Preço: %s\n",
           purchases[i][0], purchases[i][1], purchases[i][2], purchases[i][3], purchases[i][4]);
  }
}

void savePurchases(char purchases[MAX_PURCHASES][5][50], int count)
{
  FILE *file = fopen(FILENAME_PURCHASES, "w");
  if (file == NULL)
  {
    error("Erro ao abrir o arquivo de compras.");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%s:%s:%s:%s:%s\n", purchases[i][0], purchases[i][1], purchases[i][2], purchases[i][3], purchases[i][4]);
  }

  fclose(file);
}

void loadPurchases(char purchases[MAX_PURCHASES][5][50], int *count)
{
  FILE *file = fopen("purchases.txt", "r");
  if (file == NULL)
  {
    return;
  }

  char line[250];
  while (fgets(line, sizeof(line), file))
  {
    sscanf(line, "%[^:]:%[^:]:%[^:]:%[^:]:%s", purchases[*count][0], purchases[*count][1], purchases[*count][2], purchases[*count][3], purchases[*count][4]);
    (*count)++;
  }

  fclose(file);
}
