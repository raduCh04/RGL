#pragma once

#include "glad.h"

#include <stdbool.h>

typedef struct shader
{
    GLuint id;
    GLuint vs_id;
    GLuint fs_id;
    bool valid;
} shader;

shader shader_create(char *vs_data, char *fs_data, GLuint64 count);

void shader_bind(shader self);

void shader_unbind(shader self);

void shader_delete(shader self);

//TODO: Add uniforms