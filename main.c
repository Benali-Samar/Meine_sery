// main.c

#include "sery.h"

int main() {
    const char *port = "/dev/mine_sery"; 
    int fd = open_sery(port);
    init_sery(fd);



    unsigned char data_to_write[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    ssize_t bytes_written = write_to_sery(fd, data_to_write, sizeof(data_to_write));
    if (bytes_written == -1) {
        perror("Error writing to serial port");
        cleanup_sery(fd);
        return 1;
    }
    printf("Bytes written: %zd\n", bytes_written);


    unsigned char data_read[256]; 
    ssize_t bytes_read = read_from_sery(fd, data_read, sizeof(data_read));
    if (bytes_read == -1) {
        perror("Error reading from serial port");
        cleanup_sery(fd);
        return 1;
    }

    cleanup_sery(fd);
    return 0;
}

