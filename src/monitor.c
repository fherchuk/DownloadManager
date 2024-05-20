#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void MonitorDirectory(const char *directory);

int main()
{
    const char *directory = "E:\\downloads";
    printf("Monitoring directory: %s\n", directory);
    MonitorDirectory(directory);
    return 0;
}

void MonitorDirectory(const char *directory)
{
    HANDLE hDir;
    char buffer[1024];
    DWORD bytesReturned;

    // Create a directory handle
    hDir = CreateFile(directory,
                      FILE_LIST_DIRECTORY,
                      FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                      NULL,
                      OPEN_EXISTING,
                      FILE_FLAG_BACKUP_SEMANTICS,
                      NULL);

    if (hDir == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error opening directory: %s\n", directory);
        return;
    }

    while (1)
    {
        // Wait for changes in the directory
        if (ReadDirectoryChangesW(hDir,
                                  buffer,
                                  sizeof(buffer),
                                  TRUE,
                                  FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_SECURITY,
                                  &bytesReturned,
                                  NULL,
                                  NULL))
        {
            char *ptr = buffer;
            FILE_NOTIFY_INFORMATION *pNotify;
            do
            {
                pNotify = (FILE_NOTIFY_INFORMATION *)ptr;

                // Display the name of the file that was added
                if (pNotify->Action == FILE_ACTION_ADDED)
                {
                    char fileName[MAX_PATH];
                    int len = WideCharToMultiByte(CP_UTF8, 0, pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR), fileName, MAX_PATH, NULL, NULL);
                    fileName[len] = '\0';
                    printf("New file added: %s\n", fileName);
                    system("bash scripts/init.sh");
                }

                // Move to the next change notification entry
                ptr += pNotify->NextEntryOffset;
            } while (pNotify->NextEntryOffset != 0);
        }
        else
        {
            fprintf(stderr, "Error reading directory changes\n");
            break;
        }
    }

    CloseHandle(hDir);
}
