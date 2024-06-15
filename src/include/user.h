#ifndef USER_H
#define USER_H

#define MAX_USERS 100

typedef struct
{
  char username[50];
  char password[50];
} User;

int authenticateUser(User users[], int count, char *username, char *password);
void registerUser(User users[], int *count);
void saveUsers(User users[], int count);
void loadUsers(User users[], int *count);

#endif
