#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[1024];
    ssize_t bytesRead;

    // Open source file for reading
    int src = open("result.txt", O_RDONLY);
    if (src < 0) {
        const char *err = "Error: cannot open result.txt\n";
        write(2, err, sizeof("Error: cannot open result.txt\n") - 1);
        return 1;
    }

    // Create or open destination file
    int dst = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst < 0) {
        const char *err = "Error: cannot create copyresult.txt\n";
        write(2, err, sizeof("Error: cannot create copyresult.txt\n") - 1);
        close(src);
        return 1;
    }

    // Copy content
    while ((bytesRead = read(src, buffer, sizeof(buffer))) > 0) {
        write(dst, buffer, bytesRead);
    }

    // Close both files
    close(src);
    close(dst);

    const char *msg = "File copied successfully!\n";
    write(1, msg, sizeof("File copied successfully!\n") - 1);

    return 0;
}
