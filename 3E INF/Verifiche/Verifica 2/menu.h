#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100

// define struct MenuDish
typedef struct
{
    char dishes[MAX_LENGTH];
    char description[MAX_LENGTH];

} MenuDish;

// define struct MenuItem
typedef struct
{
    char type[MAX_LENGTH];
    int indexMenu;
    float price;

} MenuItem;

// PROTOTYPES
int createMenu();
int doOperation();
int getCurrentDishesCount();
float avgDishPrice();
int printMenu(char name[MAX_LENGTH]);
int addNewDish(MenuDish dish);

/**
 * createMenu creates a user menù with the following options:
 * 1 - Print current dishes count
 * 2 - Get average dish price
 * 3 - Print a menu
 * 4 - Add a new dish
 * @returns If the choice if it is valid, -1 otherwise.
 */
int createMenu()
{
    int choice;

    printf("1 - Print current dishes count");
    printf("2 - Get average dish price");
    printf("3 - Print a menu");
    printf("4 - Add a new dish");

    scanf("%d", &choice);

    if(choice > 0 && choice < 5){
        return choice;
    }
    else{
        return -1;
    }
}

/**
 * doOperation takes the number representing a choice and
 * executes the corresponding operation.
 * @param choice The user choice
 * @returns -1 on any error, 0 on successful operation.
 */
int doOperation(int choice)
{
    MenuItem tempItem;
    MenuDish tempDish;

    char name[MAX_LENGTH];
    int currentDishes;

    switch(choice)
    {
    case 1:
        currentDishes = getCurrentDishesCount();
        return currentDishes;
        break;
    case 2:
        printf("Inserisci il menu: ");
        name[MAX_LENGTH] = scanf("%s", tempItem.type);
        float price = avgDishPrice(name);
        return price;
    case 3:

        printf("Inserire il nome del piatto: ");
        name[MAX_LENGTH] = scanf("%s", tempDish.dishes);
        printMenu(name);
        break;
    case 4:
        printf("Inserisci il piatto: ");
        scanf("%s", tempDish.dishes);
        printf("Inserisci la descrizione: ");
        scanf("%s", tempDish.description);
        addNewDish(tempDish);
        break;
    default:
        return -1;
        break;
    }
    return 0;



}

/**
 * getCurrentDishesCount returns the number of dishes in the menu,
 * by reading the "dishes.txt" file.
 * @returns The number of dishes in the menu.
 */
int getCurrentDishesCount()
{
    FILE *fp = fopen("dishes.txt", "r");

    if(fp == NULL){
        return -1;
    }

    MenuDish temp;
    int n = 0;

    while(!feof(fp)){
        fscanf(fp, "%s %s", temp.dishes, temp.description);
        n++;
    }

    fclose(fp);
    return n;
}

/**
 * avgDishPrice returns the average price of the dishes in the menu.
 * @returns The average price of the dishes in the menu.
 */
float avgDishPrice(char menu[MAX_LENGTH])
{
    FILE *fp = fopen("menu.txt", "r");

    if(fp == NULL){
        return -1;
    }

    int i = 0;
    float sum = 0;

    char name[MAX_LENGTH];
    int index;
    int price;



    while(!feof(fp)){
        fscanf(fp, "%s %d %f", name, index, price);

        if(strcmp(menu, name) == 0){
            sum += price;
            i++;
        }
    }

    fclose(fp);
    return sum/i;
}

/**
 * printMenu prints the menu with the given name.
 *
 * Each item is printed with the following format:
 * Piatto N°<item number> - <dish name>
 * Descrizione:
 *   <dish description>
 * Prezzo: <dish price> EUR
 *
 * Example:
 * Piatto N°1 - Caesar_Salad
 * Descrizione:
 * Romaine_lettuce_with_Caesar_dressing_croutons_and_Parmesan_cheese
 * Prezzo: 9.50 EUR
 * @param name The name of the menu to print.
 * @returns -1 if the menu does not exist, 0 otherwise.
 */
int printMenu(char name[MAX_LENGTH])
{
    return -1;
}

/**
 * addNewDish adds a new dish to the menu, as the last dish, in the dishes.txt file.
 * Should not add the dish if it already exists.
 * @param dish The dish to add.
 * @returns -1 if the dish already exists, 0 otherwise.
 */
int addNewDish(MenuDish dish)
{
    FILE *fp = fopen("dishes.txt", "a");

    if(fp == NULL){
        return -1;
    }

    fprintf(fp, "%s %s", dish.dishes, dish.description);

    fclose(fp);
    return 0;
}
