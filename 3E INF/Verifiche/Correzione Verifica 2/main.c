#include <stdio.h>

#include "menu.h"

int main()
{
  printf("Select an operation:\n");
  int choice = createMenu();

  if (choice < 0 || choice > 4)
  {
    printf("ERRORE: SCELTA NON VALIDA\n");
    return -1;
  }

  return doOperation(choice);
}