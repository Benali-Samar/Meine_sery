
#include "sery.h"

int open_sery(const char *port)
{
    int fd = open(port, O_RDWR);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    return fd;
}



ssize_t read_from_sery(int fd, unsigned char *buffer, size_t size)
{
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN; // Check for data to read
    int timeout = 100;      // Timeout in milliseconds
    int ret = poll(fds, 1, timeout);
    if (ret == -1)
    {
        perror("poll() failed");
        cleanup_sery(fd);
        return -1;
    }
    else if (ret == 0)
    {
        printf("Timeout reached. No data available.\n");
        return 0; // No data available, return 0 bytes read
    }
    else
    {
        if (fds[0].revents & POLLIN)
        {
            printf("Data is available for reading.\n");
            ssize_t bytes_read = read(fd, buffer, size);
            if (bytes_read < 0)
            {
                perror("Error reading from serial port");
                cleanup_sery(fd);
                return -1;
            }
            else if (bytes_read == 0)
            {
                printf("No more data available. Closing connection.\n");
            }
            else
            {
                printf("Bytes read: %zd\n", bytes_read);
                printf("Data read: ");
                for (ssize_t i = 0; i < bytes_read; ++i)
                {
                    printf("%c", buffer[i]); 
                }
                printf("\n");
            }
            return bytes_read;
        }
    }
    return 0; // Default return 0 bytes read
}

ssize_t write_to_sery(int fd, const unsigned char *buffer, size_t size)
{
    ssize_t bytes_written = write(fd, buffer, size);
    if (bytes_written < 0)
    {
        perror("Error writing to serial port");
        cleanup_sery(fd);
        return -1;
    }
    return bytes_written;
}

int init_sery(int fd)
{
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0)
    {
        perror("Error in tcgetattr");
        close(fd);
        return 1;
    }
    cfsetospeed(&tty, B115200); // Set baud rate
    cfsetispeed(&tty, B115200);
    tty.c_cflag |= (CLOCAL | CREAD); // Enable receiver and set local mode
    tty.c_cflag &= ~PARENB;          // No parity bit
    tty.c_cflag &= ~CSTOPB;          // One stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;   // 8 bits per byte
    tty.c_cc[VMIN] = 0;   // Minimum number of characters to read
    tty.c_cc[VTIME] = 10; // Timeout in deciseconds
    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        perror("Error in tcsetattr");
        close(fd);
        return 1;
    }
}

void cleanup_sery(int fd)
{
    close(fd);
}