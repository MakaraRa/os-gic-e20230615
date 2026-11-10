#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[256];

    // Open the file for reading
    int fd = open("output.txt", O_RDONLY);

    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(2, err, sizeof("Error opening file\n") - 1);
        return 1;
    }

    // Read and display the file contents
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);
    }

    if (bytesRead < 0) {
        const char *err = "Error reading file\n";
        write(2, err, sizeof("Error reading file\n") - 1);
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    return 0;
}
