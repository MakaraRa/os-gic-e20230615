#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *text = "Hello from Operating Systems class!\n";

    // Create or open the file for writing
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(2, err, sizeof("Error opening file\n") - 1);
        return 1;
    }

    // Write content into the file
    ssize_t bytes = write(fd, text, sizeof("Hello from Operating Systems class!\n") - 1);

    if (bytes < 0) {
        const char *err = "Error writing file\n";
        write(2, err, sizeof("Error writing file\n") - 1);
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    // Print confirmation
    const char *msg = "File created successfully!\n";
    write(1, msg, sizeof("File created successfully!\n") - 1);

    return 0;
}
