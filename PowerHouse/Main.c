#include <stdio.h>

#include "Main.h"

/* 
Code start - keep clean
*/

int main(int argc, char *argv[])
{
	main_state = Start;

	PrintStartArguments(argc, argv);

	// Handle start arguments
	SetLogfile();
	SetDatasource();
	if (logfile_set && datasource_set)
		main_state = OK;
	else
		return StartError;

	menu(0);

	printf("Hello world!");
	return 0;
}

void PrintStartArguments(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("Argument [%d]: %s \n", i, argv);
	}
}

void menu(int current_menu) {
	return;
}
