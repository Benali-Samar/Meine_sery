
#ifndef SERY_H
#define SERY_H

#include <stddef.h> 
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <poll.h>

int init_sery(int fd);
void cleanup_sery(int fd);
int open_sery(const char *port);
ssize_t read_from_sery(int fd, unsigned char *buffer, size_t size);
ssize_t write_to_sery(int fd, const unsigned char *buffer, size_t size);

#endif
