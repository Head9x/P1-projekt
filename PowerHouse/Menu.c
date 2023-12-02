#include "stdincludes.h"

#include "Menu.h"

#define MENU_MAX_COUNT 200 // maximum amount of menus possible in total
#define MENU_SUBMENU_MAX_AMOUNT 17
#define MENU_NAME_MAX_LENGTH 50
#define MENU_DESCRIPTION_MAX_LENGTH 200
#define MENU_HELP_MAX_LENGTH 200

int running = 1;
int previousMenu = -1;

typedef struct menu_item
{
    // Unique ID
    enum MENU ID;                                  
    char key;
    int subMenuCount;                              // Amount of sub menus
    enum MENU subMenus[MENU_SUBMENU_MAX_AMOUNT];   // Array of sub menus
    char name[MENU_NAME_MAX_LENGTH];               // Menu name
    char description[MENU_DESCRIPTION_MAX_LENGTH]; // Menu description
    char help[MENU_HELP_MAX_LENGTH];               // Menu help

} menu_item;

/* Array of all menus 
*  Has to be in the same order as enum MENU
*/
menu_item menus[MENU_MAX_COUNT] = {
    {menu_start, 's', 5, {menu_appliance, menu_data_print, menu_time, menu_carbon, menu_graph}, "Start menu", "start menu description here", "start menu help here"},
    {menu_appliance, 'a', 3, { menu_appliance_print, menu_appliance_upsert, menu_appliance_remove,}, "Appliance menu", "Interact with your current appliances", "help"},
    {menu_data_print, 'p', 0, {0}, "Print data", "print data description", "print data help"},
    {menu_graph, 'g', 0, {0}, "Draw Graph", "Draws a test graph", "Graph Help"},
    {menu_time, 't', 0, {0}, "Time menu", "time menu description here", "time menu help here"},
    {menu_carbon, 'c', 0, {0}, "Carbon menu", "carbon menu description here", "carbon menu help here"},

    {menu_appliance_print, 'p', 0, {0}, "Print appliances", "Print all current appliances", "help"},
    {menu_appliance_upsert, 'u', 0, {0}, "Set appliance", "Set or insert a new appliance", "help"},
    {menu_appliance_remove, 'r', 0, {0}, "Remove appliance", "Remove on of your current appliances", "help"},

};

/* Array of menu functions. A menu function is called if the corresponding menu does not have any submenues.
*  Has to be in the same order as enum MENU, 0 can be used as nullptr to pad the array.
*/
void (*functions[MENU_MAX_COUNT])(void) = {
    0,
    0,
    &data_print_function,
    &graph_draw,
    0,
    0,

    &appliance_print_function,
    &appliance_upsert_function,
    &appliance_remove_function,

};

#if 0
int main(void)
{
    exec_menu(menu_start);
    while (running)
    {
        exec_menu(MenuID);
    }
    return 0;
}
#endif // 0

void clear_terminal() {
    #if _WIN32
    system("@cls||clear");
    #else
    printf("\e[1;1H\e[2J"); // Clear Terminal
    #endif
}

int print_menu(int MenuID)
{
    menu_item current_menu = menus[MenuID];

//clear_terminal();
    printf("Welcome to the %s\n", current_menu.name);
    printf("------------------------------------------\n");
    printf("%s\n", current_menu.description);
    printf("------------------------------------------\n");
    printf("You have the following options, press the corresponding key to continue\n\n");

    for (int i = 0; i < current_menu.subMenuCount; i++)
    {
        printf("%c. - %s\n", menus[current_menu.subMenus[i]].key , menus[current_menu.subMenus[i]].name);
    };
    printf("\n");
    printf("s. - Start menu\n");
    printf("q. - Quit\n");

    return 1;
}

int exec_menu(int MenuID)
{
    int currentMenu = MenuID;
    while (running)
    {
        menu_item current = menus[currentMenu];

        if (current.subMenuCount == 0) // this is an action
        {
            functions[currentMenu](); // execute function
            if (previousMenu != -1) {
                currentMenu = previousMenu; // Return to the previous menu
                previousMenu = -1; // Reset previousMenu after returning
            }
        }
        else
        {
            print_menu(currentMenu);
            char next_menu = standardScan();

            switch (next_menu)
            {
            case 's': // Standard case goto start menu
                currentMenu = menu_start;
                break;
            case 'q': // Standard case quit program
                printf("\n-----ENDING PROGRAM-----\n");
                running = 0;
                break;
            default:
                for (int i = 0; i < current.subMenuCount; i++)
                {
                    if (menus[current.subMenus[i]].key == next_menu)
                    {
                        previousMenu = currentMenu; // Store the current menu as the previous menu
                        currentMenu = current.subMenus[i];
                        break;
                    }
                }
            }
        }
    }

    return 0;
}


char standardScan()
{
    char scan;

    scanf(" %c", &scan);

    return scan;
}
