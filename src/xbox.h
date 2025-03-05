#ifndef XBOX_H
#define XBOX_H

struct libevdev* openXboxController(struct libevdev *xbox);
void closeXboxController(struct libevdev *xbox);

#endif //XBOX_H
