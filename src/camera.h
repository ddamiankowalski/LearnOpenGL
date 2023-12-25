#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float YAW = 0.0f;
const float PITCH =  0.0f;
const float MOVEMENT_SPEED = 0.5f;
const float ROTATE_SPEED = 0.05f;
const float MOUSE_SENSITIVITY = 0.1f;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
    public:
        glm::vec3 Position;

        float Radius; 
        float YawAngle;
        float PitchAngle;
        
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        {
            Position = position;

            Radius = 10.0f;
            YawAngle = 0.0f;
            PitchAngle = 0.0f;

            ProcessKeyboard(Camera_Movement::BACKWARD);
        }

        void ProcessKeyboard(Camera_Movement direction)
        {
            switch(direction) {
                case FORWARD:
                    PitchAngle += ROTATE_SPEED;
                    break;
                case BACKWARD:
                    PitchAngle -= ROTATE_SPEED;
                    break;
                case LEFT:
                    YawAngle -= ROTATE_SPEED;
                    break;
                case RIGHT:
                    YawAngle += ROTATE_SPEED;
            }

            findPitchMinMax();

            float x = Radius * cos(YawAngle) * cos(PitchAngle);
            float z = Radius * sin(YawAngle) * cos(PitchAngle);
            float y = Radius * sin(PitchAngle);

            Position = glm::vec3(x, y, z);
        }

    private:
        void findPitchMinMax()
        {
            if(PitchAngle > 1)
                PitchAngle = 1;

            if(PitchAngle < 0)
                PitchAngle = 0;
        }
};

#endif