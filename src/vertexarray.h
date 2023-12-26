#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "glad.h"

class VertexArray
{
    public:
        unsigned int ID;

        VertexArray()
        {
            glGenVertexArrays(1, &ID);
        }

        void bind()
        {
            glBindVertexArray(ID);
        }

        unsigned int createVBO(float *vert, unsigned int vertSize)
        {
            unsigned int vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertSize, vert, GL_STATIC_DRAW);

            return vbo;
        }
};

#endif