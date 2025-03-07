#include "xbox.h"
#include <libevdev-1.0/libevdev/libevdev.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define XBOX_DEVICE_FILE "/dev/input/event13"

//open Xbox controller device file
struct libevdev* openXboxController(struct libevdev *xbox) {
    //open Xbox controller device file
    int device = open(XBOX_DEVICE_FILE, O_RDONLY);
    if (device < 0) {
        perror("Failed to open Xbox controller:");
        exit(EXIT_FAILURE);
    }

    //init libevdev
    int status = libevdev_new_from_fd(device, &xbox);
    if (status < 0) {
        perror("Failed to init libevdev:");
        close(device);
        return xbox;
    }

    //print device name
    printf("%s connected\n", libevdev_get_name(xbox));

    return xbox;
}

//close Xbox controller device file
void closeXboxController(struct libevdev *xbox) {
    libevdev_free(xbox);
}

