
int main(int argc, char* argv[]);
void run_menu(int);

void PrintStartArguments(int argc, char* argv[]);
void SetSettingsFile(int argc, char* argv[]);
void SetDatasource();

int logfile_set = 1,
	datasource_set = 1;

enum MainState {
	OK,
	Start,
	StartError,
	UnknownError,
} main_state;

void SetDatasource() {} // not implemented
