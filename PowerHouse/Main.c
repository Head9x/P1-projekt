#include "stdincludes.h"

#include "Main.h"
#include "Menu.h"
#include "appliance.h"
#include "csvRead.h"



/* 
Code start - keep clean
*/

int main(int argc, char *argv[])
{
	main_state = Start;

	printf("Hello world!\n");
	PrintStartArguments(argc, argv);

	// Handle start arguments
	SetLogfile();
	SetDatasource();
	if (logfile_set && datasource_set)
		main_state = OK;
	else
		return StartError;

	run_menu(menu_start);

	return 0;
}

void PrintStartArguments(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("Argument [%d]: %s \n", i, argv[i]);
	}
}

void run_menu (int startup_menu) {
	MenuID = startup_menu;
	while (MenuID != menu_end)
	{
		exec_menu(MenuID);
	}
}
