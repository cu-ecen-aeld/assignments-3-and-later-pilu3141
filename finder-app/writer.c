#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if the required arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Error: Incorrect number of arguments. Usage: %s <writefile> <writestr>\n", argv[0]);
        return 1;
    }

    // Extract the arguments
    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Open syslog
    openlog(argv[0], LOG_PID | LOG_CONS, LOG_USER);

    // Open the file for writing
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        syslog(LOG_ERR, "Error: Failed to create file '%s'", writefile);
        perror("open");
        closelog();
        return 1;
    }

    // Write the string to the file
    ssize_t bytes_written = write(fd, writestr, strlen(writestr));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Error: Failed to write to file '%s'", writefile);
        perror("write");
        close(fd);
        closelog();
        return 1;
    }

    // Close the file
    close(fd);

    // Log the write operation
    syslog(LOG_DEBUG, "Writing '%s' to '%s'", writestr, writefile);

    // Close syslog
    closelog();

    return 0;
}
