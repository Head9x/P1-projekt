#include "stdincludes.h"

#include "Main.h"
#include "Menu.h"
#include "appliance.h"
#include "csvRead.h"
#include "SettingHandler.h"

#include "pbPlots/pbPlots.h"
#include "pbPlots/supportLib.h"

#include "examples.h"


/* 
Code start - keep clean
*/

int main(int argc, char *argv[])
{
	main_state = Start;

	printf("Hello world!\n");
	PrintStartArguments(argc, argv);

	// Handle start arguments
	SetSettingsFile(argc, argv);
	SetDatasource();
	if (logfile_set && datasource_set)
		main_state = OK;
	else
		return StartError;
	
	//for (int i = 1; i <= 4; i++) run_pbplot_example(i);

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
	exec_menu(MenuID);
}

void SetSettingsFile(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-s") != 0) 
			continue;
		
		if (i + 1 == argc) 
			break; // missing second argument, TODO: we could provide a warning in the console

		SetSettingPath(argv[i + 1]);
		return;
	}

	SetSettingPath(NULL);
}
