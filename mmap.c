#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *msg = "Hello using mmap!";
    int fd = open("mmapfile.txt", O_RDWR | O_CREAT, 0666);
    ftruncate(fd, 1024);

    char *map = (char*) mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (fork() == 0) {
        sleep(1);
        printf("Child read: %s\n", map);
        munmap(map, 1024);
        close(fd);
    } else {
        strcpy(map, msg);
        printf("Parent wrote to file using mmap.\n");
        munmap(map, 1024);
        close(fd);
    }

    return 0;
}
