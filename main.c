#include <stdio.h>
#include <windows.h>

void listFiles(const char *directory) {
    WIN32_FIND_DATA findFileData;
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
            if(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0){
                    printf("[DIR] %s\\%s\n", directory, name);
                }
            }
            else {
                printf("    %s\\%s\n", directory, name);
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
}

int main(){
    listFiles("./");
    return 0;
}