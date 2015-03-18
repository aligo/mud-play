void MudErrorToNSLog(char * formatString, ...);
void MudWarningToNSLog(char * formatString, ...);
void MudInfoToNSLog(char * formatString, ...);

#define mud_error(...)    MudErrorToNSLog(__VA_ARGS__)
#define mud_warning(...)  MudWarningToNSLog(__VA_ARGS__)
#define mud_info(...)  MudInfoToNSLog(__VA_ARGS__)
