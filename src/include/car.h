#ifndef CAR_H
#define CAR_H

#define MAX_CARS 100

typedef struct
{
  char model[50];
  char brand[50];
  int year;
  float price;
} Car;

void addCar(Car cars[], int *count);
void listCars(Car cars[], int count);
void searchCar(Car cars[], int count);
void removeCar(Car cars[], int *count);
void buyCar(Car cars[], int *count, char *username);
void saveCars(Car cars[], int count);
void loadCars(Car cars[], int *count);

#endif
