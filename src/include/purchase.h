#ifndef PURCHASE_H
#define PURCHASE_H

#define MAX_PURCHASES 100

void listPurchases(char purchases[][5][50], int count);
void savePurchases(char purchases[][5][50], int count);
void loadPurchases(char purchases[][5][50], int *count);

#endif
