#ifndef PURCHASE_H
#define PURCHASE_H

#define MAX_PURCHASES 100
#define FILENAME_PURCHASES "purchases.txt"

void listPurchases(char purchases[][5][50], int count);
void savePurchases(char purchases[MAX_PURCHASES][5][50], int count);
void loadPurchases(char purchases[MAX_PURCHASES][5][50], int *count);

#endif
