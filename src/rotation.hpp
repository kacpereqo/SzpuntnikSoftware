#ifndef ROTATION_HPP
#define ROTATION_HPP

struct Rotation
{
    float x = 1;
    float y = 91;
    float z = 21;

    void updateRotation();
};

#endif

/*

    yaw
     | y
     |
     |
     |          x
    /------------ pitch
   /
  /
 /  z
roll

*/