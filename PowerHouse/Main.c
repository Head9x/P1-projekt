#include "stdincludes.h"

#include "Main.h"
#include "Menu.h"
#include "appliance.h"
#include "csvRead.h"
#include "SettingHandler.h"

#include "pbPlots/pbPlots.h"
#include "pbPlots/supportLib.h"

/* 
Code start - keep clean

Handles startup arguments
Then starts the menu - where the real processing starts
*/

int main(int argc, char *argv[])
{
	// Handle start arguments
	handle_exe_arguments(argc, argv);

	if (!(settings_set && datasource_set))
		return 1;

	run_menu(menu_start);

	return 0;
}

void run_menu (int startup_menu) {
	MenuID = startup_menu;
	exec_menu(MenuID);
}

void handle_exe_arguments(int argc, char* argv[]) 
{
	struct argument {
		char* input;
		char* help;
	};

	struct argument argument_types[] = {
		{"h", "Help! list potential arguments"},
		{"-d", "Sets data source file path as < -d datasource_path > or < -d datasource_path --h > if the csv file has header row"},
		{"-s", "Sets setting file path as < -s setting_path >"}
	};

	// Process arguments
	int has_next_argument;
	for (int i = 0; i < argc; i++)
	{
#if _DEBUG
		printf("Argument [%d]: %s \n", i, argv[i]);
#endif
		has_next_argument = !(i+1 >= argc);
		if (strcmp(argv[i], argument_types[0].input) == 0) // help
		{
			for (int j = 0; j < 3; j++) {
				printf("%s \t %s \n", argument_types[j].input, argument_types[j].help);
			}

			return;
		}
		else if (strcmp(argv[i], argument_types[1].input) == 0) // datasource
		{
#if _DEBUG
			printf("Found argument \"-d\" and %s. \n", has_next_argument ? "has next argument" : "is missing next argument");
#endif
			if (!has_next_argument) {
				printf("Missing data source path following %s argument.\n", argument_types[1].input);
				return;
			}
			
			SetCSVPath(argv[i + 1], (i + 2 < argc) && strcmp(argv[i + 2], "--h"));
			datasource_set = 1;
		}
		else if (strcmp(argv[i], argument_types[2].input) == 0) // settings
		{
#if _DEBUG
			printf("Found argument \"-s\" and %s. \n", has_next_argument ? "has next argument" : "is missing next argument");
#endif
			if (!has_next_argument) 
			{
				printf("Missing settings path following %s argument. \n", argument_types[2].input);
				return;
			}
			
			SetSettingPath(argv[i + 1]);
			settings_set = 1;
		}
	}

	// Handle missing arguments with default values
	if (!settings_set)
	{
		SetSettingPath(NULL);
		settings_set = 1;
	}

	if (!datasource_set)
	{
		SetCSVPath(NULL, true);
		datasource_set = 1;
	}
}
