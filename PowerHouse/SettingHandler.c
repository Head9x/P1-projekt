#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SettingHandler.h"

#define MAX_NUMBER_OF_SETTINGS 250

static char* _path = "settings.txt";
static int number_of_settings = 0;
static setting settings[MAX_NUMBER_OF_SETTINGS];

// Sets the path to the settings file, use NULL for default 
void SetSettingPath(const char* path)
{
    number_of_settings = 0;
	_path = path == NULL ? "settings.txt" : path;

    FILE* file = fopen(_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open or locate settings.txt!\n");
        exit(EXIT_FAILURE);
    }

    char delimiter1[] = " ";
    char delimiter2[] = "\n";
    char line[1024];
    char* token = NULL;
    size_t len = 1024;

    while (fgets(line, len, file) != NULL)
    {
        if (number_of_settings >= MAX_NUMBER_OF_SETTINGS) break;

        strcpy(settings[number_of_settings].key, strtok(line, delimiter1));
        strcpy(settings[number_of_settings++].value, strtok(NULL, delimiter2));
    }

    fclose(file);
}

void SettingWriteAll()
{
    FILE* file = fopen(_path, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open or locate settings.txt!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < number_of_settings; i++) 
    {
        fprintf(file, "%s %s\n", settings[i].key, settings[i].value);
    }

    fclose(file);
}

void SettingAppend(setting new_value) 
{
    FILE* file = fopen(_path, "a");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open or locate settings.txt!\n");
        exit(EXIT_FAILURE);
    }

    settings[number_of_settings++] = new_value;
    fprintf(file, "%s %s\n", new_value.key, new_value.value);

    fclose(file);
}

// Finds and returns the index of the setting matching by key, or returns -1 if not found.
int SettingFind(const char* key)
{
    for (int i = 0; i < number_of_settings; i++)
    {
        if (strcmp(settings[i].key, key) == 0)
            return i;
    }
    return -1;
}

// Inserts or updates the key value pair in the settings file
void UpsertSetting(const char* key, const char* value)
{
    int setting_index = SettingFind(key);
    if (setting_index > -1) // update
    {
        strcpy(settings[setting_index].value, value);
        SettingWriteAll();
    }
    else // insert
    {
        if (number_of_settings >= MAX_NUMBER_OF_SETTINGS) exit(EXIT_FAILURE);

        strcpy(settings[number_of_settings].key, key);
        strcpy(settings[number_of_settings].value, value);

        SettingAppend(settings[number_of_settings++]);
    }
}

// Test if the setting exists in the settings set
int HasSetting(const char* key)
{
    return SettingFind(key) > -1;
}

// Get the setting from setting set
const setting GetSetting(const char* key)
{
    auto setting _setting = { NULL, NULL };

    int setting_index = SettingFind(key);
    if (setting_index <= -1)
         return _setting; // return null setting

    return settings[setting_index];
}

// Get all settings - in case you want to do custom filtering
const setting* GetAllSettings(void)
{
    return settings;
}

void RemoveSetting(const char* key)
{
    int setting_index = SettingFind(key);
    if (setting_index <= -1)
        return;

    for (int i = setting_index + 1; i < number_of_settings; i++)
    {
        settings[i - 1] = settings[i];
    }
    number_of_settings--;
    SettingWriteAll();
}
