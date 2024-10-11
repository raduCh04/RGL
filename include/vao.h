#pragma once

#include "glad.h"
#include "vbo.h"

typedef struct vao
{
    GLuint id;
} vao;

vao vao_create();

void vao_bind(vao self);

void vao_unbind(vao self);

void vao_delete(vao self);

void vao_attrib(vao self, vbo vbo, GLuint index,
                GLint size, GLenum type,
                GLsizei stride, GLuint64 offset);
