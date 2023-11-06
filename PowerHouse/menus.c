#include <stdio.h>
#include <stdlib.h>

#define MENU_MAX_COUNT 20 // maximum amount of menus possible in total
#define MENU_SUBMENU_MAX_AMOUNT 20
#define MENU_NAME_MAX_LENGTH 50
#define MENU_DESCRIPTION_MAX_LENGTH 200
#define MENU_HELP_MAX_LENGTH 200

typedef enum MENU
{
    start,
    time,
    carbon,
} MENU;

int currentMenu = start;

typedef struct menu
{
    enum MENU menuID;                              // Unique ID
    int subMenuCount;                              // Amount of sub menus
    enum MENU subMenus[MENU_SUBMENU_MAX_AMOUNT];   // Array of sub menus
    char name[MENU_NAME_MAX_LENGTH];               // Menu name
    char description[MENU_DESCRIPTION_MAX_LENGTH]; // Menu description
    char help[MENU_HELP_MAX_LENGTH];               // Menu help

} menu;

menu menus[MENU_MAX_COUNT] = {
    {start, 5, {time, carbon}, "start menu", "start menu description here", "start menu help here"},
    {time, 5, {}, "Time menu", "time menu description here", "time menu help here"},
    {carbon, 5, {}, "carbon menu", "carbon menu description here", "carbon menu help here"},
};

int print_menu(int); // prototype
int scan_menu(int);  // prototype

int main(void)
{
    print_menu(start);
}

int print_menu(int MenuID)
{
    currentMenu = MenuID;
    printf("===== New menu ===========================\n"); // Debug, swap to clear terminal
    //printf("\e[1;1H\e[2J"); // Clear Terminal
    printf("Welcome to the %s\n", menus[MenuID].name);
    printf("------------------------------------------\n");
    printf("%s\n", menus[MenuID].description);
    printf("------------------------------------------\n");
    printf("You have the following options, press the corresponding key to continue\n\n");
    for (int i; i < menus[MenuID].subMenuCount; i++)
    {
        printf("%c. - %s\n\n", 'a' + i, menus[menus[MenuID].subMenus[i]].name);
    };
    printf("n");
}

int scan_menu(int MenuID)
{

}