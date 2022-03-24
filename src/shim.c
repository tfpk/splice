#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

static ssize_t (*real_read)(int, void*, size_t) = NULL;
char *start_delimiter = NULL;
char *end_delimiter = NULL;

void __attribute__((constructor)) initialize(void) {
    real_read = dlsym(RTLD_NEXT, "read");
    if (real_read == NULL) {
        printf("Could not find read syscall.");
        exit(255);
    }

    start_delimiter = getenv("SPLICE_START_DELIMITER");
    end_delimiter = getenv("SPLICE_END_DELIMITER");

    if (start_delimiter == NULL || *start_delimiter == '\0') {
        start_delimiter = "\033[31;1;4m";
    }
    if (end_delimiter == NULL || *end_delimiter == '\0') {
        end_delimiter = "\033[0m";
    }
}

ssize_t read(int fd, void *buf, size_t count) {
    ssize_t real_size = real_read(fd, buf, count);

    if (fd != 0 || real_size == 0) {
        return real_size;
    }

    write(1, start_delimiter, strlen(start_delimiter));
    write(1, buf, real_size - 1);
    write(1, end_delimiter, strlen(end_delimiter));
    write(1, "\n", 1);


    return real_size;

}
