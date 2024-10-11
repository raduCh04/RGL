#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "glad.h"

typedef struct vbo
{
    GLuint id;
    GLint type;
    bool dynamic;
} vbo;

typedef struct vao
{
    GLuint id;
} vao;

typedef struct shader
{
    GLuint id;
    GLuint vs_id;
    GLuint fs_id;
    bool valid;
} shader;

#ifndef RGLDEF
    #ifdef RLG_STATIC
        #define RGLDEF static
    #else
        #define RGLDEF extern
    #endif
#endif

RGLDEF vbo vbo_create(GLint type, bool dynamic);

RGLDEF void vbo_bind(vbo self);

RGLDEF void vbo_unbind(vbo self);

RGLDEF void vbo_delete(vbo self);

RGLDEF void vbo_buffer(vbo self, void *data, GLuint64 offset, GLuint64 count);

RGLDEF vao vao_create();

RGLDEF void vao_bind(vao self);

RGLDEF void vao_unbind(vao self);

RGLDEF void vao_delete(vao self);

RGLDEF void vao_attrib(vao self, vbo vbo, GLuint index,
                GLint size, GLenum type,
                GLsizei stride, GLuint64 offset);


RGLDEF shader shader_create(char *vs_data, char *fs_data, GLuint64 count);

RGLDEF void shader_bind(shader self);

RGLDEF void shader_unbind(shader self);

RGLDEF void shader_delete(shader self);

//TODO: Add uniforms
#ifdef _RGL_IMPLEMENTATION_
RGLDEF vbo vbo_create(GLint type, bool dynamic)
{
    vbo result = {
        .dynamic = dynamic,
        .type = type,
    };
    glGenBuffers(1, &result.id);

    return result;
}

RGLDEF void vbo_bind(vbo self)
{
    glBindBuffer(self.type, self.id);
}

RGLDEF void vbo_unbind(vbo self)
{
    glBindBuffer(self.type, 0);
}

RGLDEF void vbo_delete(vbo self)
{
    glDeleteBuffers(1, &self.id);
}

RGLDEF void vbo_buffer(vbo self, void *data, GLuint64 offset, GLuint64 count)
{
    vbo_bind(self);
    glBufferData(GL_ARRAY_BUFFER, count - offset, data, self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

RGLDEF vao vao_create()
{
    vao result = {0};
    glGenVertexArrays(1, &result.id);    
    return result;
}

RGLDEF void vao_bind(vao self)
{
    glBindVertexArray(self.id);
}

RGLDEF void vao_unbind(vao self)
{
    glBindVertexArray(0);
}

RGLDEF void vao_delete(vao self)
{
    glDeleteVertexArrays(1, &self.id);
}

RGLDEF void vao_attrib(vao self, vbo vbo, GLuint index, GLint size, GLenum type, GLsizei stride, GLuint64 offset)
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

/*NOTE: vs_data and fs_data are binary data from alread read file
* meaning you have to load the data with your own read API
* shader.valid is for checking if the program was compiled successfully
*/
RGLDEF shader shader_create(char *vs_data, char *fs_data, GLuint64 count)
{
    shader result = {0};

    result.vs_id = glCreateShader(GL_VERTEX_SHADER);
    result.fs_id = glCreateShader(GL_FRAGMENT_SHADER);

    //TODO: Add compilation status
    glShaderSource(result.vs_id, 1, &vs_data, NULL);
    glCompileShader(result.vs_id);

    //TODO: Add compilation status
    glShaderSource(result.fs_id, 1, &fs_data, NULL);
    glCompileShader(result.fs_id);

    //TODO: Add compilation status
    result.id = glCreateProgram();
    glAttachShader(result.id, result.vs_id);
    glAttachShader(result.id, result.fs_id);
    glLinkProgram(result.id);
}

RGLDEF void shader_bind(shader self)
{
    glUseProgram(self.id);
}

RGLDEF void shader_unbind(shader self)
{
    glUseProgram(0);
}

RGLDEF void shader_delete(shader self)
{
    glDeleteProgram(self.id);
    glDeleteShader(self.vs_id);
    glDeleteShader(self.fs_id);
}

#endif