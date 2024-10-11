#include "vao.h"

vao vao_create()
{
    vao result = {0};
    glGenVertexArrays(1, &result.id);    
    return result;
}

void vao_bind(vao self)
{
    glBindVertexArray(self.id);
}

void vao_unbind(vao self)
{
    glBindVertexArray(0);
}

void vao_delete(vao self)
{
    glDeleteVertexArrays(1, &self.id);
}

void vao_attrib(vao self, vbo vbo, GLuint index, GLint size, GLenum type, GLsizei stride, GLuint64 offset)
{
    vao_bind(self);
    vbo_bind(vbo);

    switch (type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV: {
            glVertexAttribIPointer(index, size, type, stride, (void *)offset);
        } break;
        default: {
            glVertexAttribPointer(index, size, type, GL_FLOAT, stride, (void *)offset);
        } break;
    }
    glEnableVertexAttribArray(index);
}
