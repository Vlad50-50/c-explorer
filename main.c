#include <stdio.h>
#include <windows.h>

void listFiles(const char *directory) {
    WIN32_FIND_DATA findFileData;
    SYSTEMTIME sysTime;
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "%s\\*", directory);
    HANDLE hFind = FindFirstFile(path, &findFileData);

    if(hFind == INVALID_HANDLE_VALUE){
        printf("Invalid file handle. Err: %u\n", GetLastError());
    }
    else {
        printf("Files in %s:\n", directory);
        do {
            const char *name = findFileData.cFileName;
            FILETIME dateOfCreation = findFileData.ftCreationTime;
            FileTimeToSystemTime(&findFileData.ftCreationTime, &sysTime);

            if(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0){
                    printf("[DIR]%s | %s | %02d/%02d/%04d %02d:%02d:%02d \n", directory, name,
                        sysTime.wDay, 
                        sysTime.wMonth, 
                        sysTime.wYear,
                        sysTime.wHour,
                        sysTime.wMinute, 
                        sysTime.wSecond);
                }
            }
            else {
                printf("     %s | %s | %02d/%02d/%04d %02d:%02d:%02d \n", directory, name, 
                    sysTime.wDay, 
                    sysTime.wMonth, 
                    sysTime.wYear,
                    sysTime.wHour,
                    sysTime.wMinute, 
                    sysTime.wSecond);
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
}

int main(){
    const char addr[120];
    while(1){
        printf("Enter the addres of directory: (exemple : ../ , ./): ");
        scanf("%s", &addr);
        
        listFiles(addr);
    }
    

    return 0;
}