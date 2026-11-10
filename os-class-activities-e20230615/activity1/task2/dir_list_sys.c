#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main() {
    char buffer[512];

    DIR *dir = opendir(".");

    if (dir == NULL) {
        const char *err = "Error opening directory\n";
        write(2, err, strlen(err));
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    // Print the header using write()
    const char *header = "Filename                       Size (bytes)\n";
    write(1, header, strlen(header));

    const char *separator = "------------------------------ ----------\n";
    write(1, separator, strlen(separator));

    // Read each directory entry
    while ((entry = readdir(dir)) != NULL) {

        if (stat(entry->d_name, &fileStat) == 0) {

            // Format filename and file size
            int len = snprintf(
                buffer,
                sizeof(buffer),
                "%-30s %10ld\n",
                entry->d_name,
                fileStat.st_size
            );

            // Display formatted information
            if (len > 0 && len < sizeof(buffer)) {
                write(1, buffer, len);
            }
        }
    }

    closedir(dir);

    return 0;
}
