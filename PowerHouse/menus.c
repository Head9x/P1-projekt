#include <stdio.h>
#include <stdlib.h>

#define MENU_MAX_COUNT 20 // maximum amount of menus possible in total
#define MENU_SUBMENU_MAX_AMOUNT 17
#define MENU_NAME_MAX_LENGTH 50
#define MENU_DESCRIPTION_MAX_LENGTH 200
#define MENU_HELP_MAX_LENGTH 200

typedef enum MENU
{
    menu_start,
    menu_time,
    menu_carbon,
    menu_get24hStatus
} MENU;

int running = 1;
int MenuID = menu_start;

typedef struct menu
{
    enum MENU ID;                                  // Unique ID
    int subMenuCount;                              // Amount of sub menus
    enum MENU subMenus[MENU_SUBMENU_MAX_AMOUNT];   // Array of sub menus
    char name[MENU_NAME_MAX_LENGTH];               // Menu name
    char description[MENU_DESCRIPTION_MAX_LENGTH]; // Menu description
    char help[MENU_HELP_MAX_LENGTH];               // Menu help

} menu;

menu menus[MENU_MAX_COUNT] = {
    {menu_start, 2, {menu_time, menu_carbon, menu_get24hStatus}, "Start menu", "start menu description here", "start menu help here"},
    {menu_time, 2, {}, "Time menu", "time menu description here", "time menu help here"},
    {menu_carbon, 2, {}, "Carbon menu", "carbon menu description here", "carbon menu help here"},
};

// prototypes
int print_menu(int);
int exec_menu(int);
int start_function();
int time_function();
int carbon_function();
char standardScan();

int main(void)
{
    exec_menu(menu_start);
    while (running)
    {
        exec_menu(MenuID);
    }
    return 0;
}

int print_menu(int MenuID)
{
    //printf("===== New menu ===========================\n"); // Debug, swap to clear terminal
    printf("\e[1;1H\e[2J"); // Clear Terminal
    printf("Welcome to the %s\n", menus[MenuID].name);
    printf("------------------------------------------\n");
    printf("%s\n", menus[MenuID].description);
    printf("------------------------------------------\n");
    printf("You have the following options, press the corresponding key to continue\n\n");
    for (int i = 0; i < menus[MenuID].subMenuCount; i++)
    {
        printf("%c. - %s\n", 'a' + i, menus[menus[MenuID].subMenus[i]].name);
    };
    printf("\n");
    // printf("r. - Return\n"); //Not implemented
    printf("s. - Start menu\n");
    printf("q. - Quit\n");
}

int exec_menu(int MenuID)
{
    switch (MenuID)
    {
    case menu_start:
        start_function();
        break;

    case menu_time:
        time_function();
        break;

    case menu_carbon:
        carbon_function();
        break;

        // default:
        // break;
    }
}

int start_function()
{
    print_menu(menu_start);

    switch (standardScan())
    {
    case 'a':
        exec_menu(menu_time);
        break;

    case 'b':
        exec_menu(menu_carbon);
        break;

    case 'c':
        printf("\nget24hStatus not implemented\n");
        break;



        //  default:
        //    break;
    }
}

int time_function()
{
    print_menu(menu_time);

    switch (standardScan())
    {
    case 'a':
        break;

    case 'b':
        break;

        //  default:
        //    break;
    }
}

int carbon_function()
{
    print_menu(menu_carbon);

    switch (standardScan())
    {
    case 'a':
        break;

    case 'b':
        break;

        //  default:
        //    break;
    }
}

char standardScan()
{
    char scan;
    scanf(" %c", &scan);

    switch (scan)
    {
    /*case 'r': //Standard case return to previous menu, not implemented
              //returnMenu();
              break; */
    case 's': // Standard case goto start menu
        exec_menu(menu_start);
        break;
    case 'q': // Standard case quit program
        printf("\n-----ENDING PROGRAM-----\n");
        running = 0;
        break;
    }
    return scan;
}