#pragma once

int main(int argc, char* argv[]);
void menu(int);
void PrintStartArguments(int argc, char* argv[]);
void SetLogfile();
void SetDatasource();

int logfile_set = 1,
	datasource_set = 1;

enum MainState {
	OK,
	Start,
	StartError,
	UnknownError,
} main_state;


void SetLogfile() {}
void SetDatasource() {}
