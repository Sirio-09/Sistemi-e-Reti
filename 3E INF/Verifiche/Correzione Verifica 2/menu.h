#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct
{
    char name[MAX_LENGTH];
    char description[MAX_LENGTH];
} MenuDish;

// define struct MenuItem
typedef struct
{
    char menu_name[MAX_LENGTH];
    int dish_index;
    float dish_price_eur;
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
    printf("1 - Print current dishes count\n");
    printf("2 - Get average dish price\n");
    printf("3 - Print a menu\n");
    printf("4 - Add a new dish\n");

    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > 4)
    {
        return -1;
    }

    return choice;
}

/**
 * doOperation takes the number representing a choice and
 * executes the corresponding operation.
 * @param choice The user choice
 * @returns -1 on any error, 0 on successful operation.
 */
int doOperation(int choice)
{
    char menu_name[MAX_LENGTH];

    switch (choice)
    {
        case 1:
            int dishes_count = getCurrentDishesCount();
            if (dishes_count == -1)
            {
                return -1;
            }

            printf("Ci sono %d piatti\n", dishes_count);
            break;
        case 2:
        {
            printf("Inserisci il nome del menu: ");
            scanf("%s\n", menu_name);

            float avg_dish_price = avgDishPrice(menu_name);
            if (avg_dish_price == -1)
            {
                return -1;
            }

            printf("Il prezzo medio è %f EUR\n", avg_dish_price);
            break;
        }
        case 3:
            printf("Inserisci il nome del menu: ");
            scanf("%s\n", menu_name);

            return printMenu(menu_name);
        case 4:
            MenuDish dish;
            printf("Inserisci il nome del piatto: ");
            scanf("%s\n", dish.name);
            printf("Inserisci la descrizione del piatto: ");
            scanf("%s\n", dish.description);

            return addNewDish(dish);    
        default:
            return -1;
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
    if (fp == NULL)
    {
        return -1;
    }

    int count = 0;

    while (!feof(fp))
    {
        MenuDish temp;
        fscanf(fp, "%s %s\n", temp.name, temp.description);

        count++;
    }

    fclose(fp);

    return count;
}

/**
 * avgDishPrice returns the average price of the dishes in the menu.
 * @returns The average price of the dishes in the menu.
 */
float avgDishPrice(char menu[MAX_LENGTH])
{
    FILE *fp = fopen("menu.txt", "r");
    if (fp == NULL)
    {
        return -1;
    }

    float sum_prices = 0;
    int dishes_in_menu = 0;

    while (!feof(fp))
    {
        MenuItem item;
        fscanf(fp, "%s %d %f\n", item.menu_name, &item.dish_index, &item.dish_price_eur);

        if (strcmp(item.menu_name, menu) == 0)
        {
            // lo consideriamo per la media
            sum_prices += item.dish_price_eur;
            dishes_in_menu++;
        }
    }

    fclose(fp);

    return sum_prices / dishes_in_menu;
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
    FILE *menu_txt = fopen("menu.txt", "r");
    if (menu_txt == NULL)
    {
        return -1;
    }

    int count = 0;
    while (!feof(menu_txt))
    {
        MenuItem item;
        fscanf(menu_txt, "%s %d %f\n", item.menu_name, &item.dish_index, &item.dish_price_eur);

        if (strcmp(item.menu_name, name) == 0)
        {
            // questa menù entry è da stampare
            FILE *dishes_txt = fopen("dishes.txt", "r");
            if (dishes_txt == NULL)
            {
                fclose(menu_txt);

                return -1;
            }

            MenuDish dish;
            // scarto n - 1 righe che non mi servono
            for (int i = 0; i < item.dish_index; i++)
            {
                fscanf(dishes_txt, "%s %s\n", dish.name, dish.description);
            }

            // leggo la riga che mi interessa
            fscanf(dishes_txt, "%s %s\n", dish.name, dish.description);
            count++;

            printf("Piatto N°%d - %s\n", count, dish.name);
            printf("Descrizione:\n");
            printf("  %s\n", dish.description);
            printf("Prezzo: %f EUR\n", item.dish_price_eur);

            fclose(dishes_txt);
        }
    }

    fclose(menu_txt);

    return 0;
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
    if (fp == NULL)
    {
        return -1;
    }

    fprintf(fp, "%s %s\n", dish.name, dish.description);

    fclose(fp);

    return 0;
}