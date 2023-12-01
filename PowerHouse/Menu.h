#if 0
#pragma once
#endif

#define MENUHEADER

// MENU enum, each MENU type represent a menu action - some actions will themselves have submenus 
typedef enum MENU
{
    menu_start,
    menu_appliance,
    menu_data_print,
    
    menu_time,
    menu_carbon,

    menu_appliance_print,
    menu_appliance_upsert,
    menu_appliance_remove,

    menu_end
} MENU;


static MENU MenuID = menu_start;

// prototype functions
int print_menu(int);
int exec_menu(int);
char standardScan();

void appliance_print_function(void);
void appliance_upsert_function(void);
void appliance_remove_function(void);

void data_print_function(void);
