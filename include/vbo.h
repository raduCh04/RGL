#pragma once

#include <stdbool.h>

#include "glad.h"

typedef struct vbo
{
    GLuint id;
    GLint type;
    bool dynamic;
} vbo;

vbo vbo_create(GLint type, bool dynamic);

void vbo_bind(vbo self);

void vbo_unbind(vbo self);

void vbo_delete(vbo self);

void vbo_buffer(vbo self, void *data, GLuint64 offset, GLuint64 count);