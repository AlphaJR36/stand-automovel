#ifndef UTILITY_H
#define UTILITY_H

void clearScreen();
void hideInput(char *input, int maxLength);
void showLoginSuccessAnimation();
int isAdminUser(char *username);

void setConsoleColor(int color);
void error(const char *message);
void warning(const char *message);
void success(const char *message);

void lineBreak(int count);
void printCentered(const char *str, int totalWidth);

#endif
