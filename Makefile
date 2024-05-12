
CC = gcc
SRCS = sery.c main.c
TARGET = Meine_serial

# Object files
OBJS = $(SRCS:.c=.o)

# All targets depend on the object files
.PHONY: all clean

all: $(TARGET)

# Compile
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c 
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
