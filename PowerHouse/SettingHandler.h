#ifndef setting_handler_header
#define setting_handler_header 1

typedef struct{
	char key [250],
		value [250];
}setting;

// Returns the number of settings
extern int GetSettingsCount();

// Sets the path to the settings file, use NULL for default 
extern void SetSettingPath(const char* path);

// Inserts or updates the key value pair in the settings file
extern void UpsertSetting(const char* key, const char* value);

// Test if the setting exists in the settings set
extern int HasSetting(const char* key);

// Get the setting from setting set
extern const setting GetSetting(const char* key);

// Get all settings - in case you want to do custom filtering
extern const setting * GetAllSettings(void);

extern void RemoveSetting(const char* key);


#endif // !setting_handler_header
