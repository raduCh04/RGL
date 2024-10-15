#pragma once

#include "glad.h"

typedef struct vbo
{
    GLuint id;
    GLint type;
    GLboolean dynamic;
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
    GLboolean valid;
} shader;

typedef struct texture
{
    GLuint id;
    GLint width;
    GLint height;
} texture;

#ifndef RGLDEF
    #ifdef RLG_STATIC
        #define RGLDEF static
    #else
        #define RGLDEF extern
    #endif
#endif

//vbo functions

RGLDEF vbo vbo_create(GLint type, GLboolean dynamic);

RGLDEF void vbo_bind(vbo self);

RGLDEF void vbo_unbind(vbo self);

RGLDEF void vbo_delete(vbo self);

RGLDEF void vbo_buffer(vbo self, void *data, GLuint64 offset, GLuint64 count);

//vao functions

RGLDEF vao vao_create();

RGLDEF void vao_bind(vao self);

RGLDEF void vao_unbind(vao self);

RGLDEF void vao_delete(vao self);

RGLDEF void vao_attrib(vao self, vbo vbo, GLuint index,
                GLint size, GLenum type,
                GLsizei stride, GLuint64 offset);


//shader functions

RGLDEF shader shader_create(const char *vs_data, const char *fs_data, GLuint64 count);

RGLDEF void shader_bind(shader self);

RGLDEF void shader_unbind(shader self);

RGLDEF void shader_delete(shader self);

RGLDEF void shader_set_bool(shader self, const char *name, GLboolean value);

RGLDEF void shader_set_int(shader self, const char *name, GLint value);

RGLDEF void shader_set_float(shader self, const char *name, GLfloat value);

RGLDEF void shader_set_matrix4fv(shader self, const char *name, GLfloat *value);

//texture functions

//TODO: implement
RGLDEF texture texture_create(const char *data, GLint width, GLint height);

//TODO: Add uniforms
#define _RGL_IMPLEMENTATION_
#ifdef _RGL_IMPLEMENTATION_
inline RGLDEF vbo vbo_create(GLint type, GLboolean dynamic)
{
    vbo result = {
        .dynamic = dynamic,
        .type = type,
    };
    glGenBuffers(1, &result.id);

    return result;
}

//vbo functions

inline RGLDEF void vbo_bind(vbo self)
{
    glBindBuffer(self.type, self.id);
}

inline RGLDEF void vbo_unbind(vbo self)
{
    glBindBuffer(self.type, 0);
}

inline RGLDEF void vbo_delete(vbo self)
{
    glDeleteBuffers(1, &self.id);
}

inline RGLDEF void vbo_buffer(vbo self, void *data, GLuint64 offset, GLuint64 count)
{
    vbo_bind(self);
    glBufferData(GL_ARRAY_BUFFER, count - offset, data, self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

//vao functions

inline RGLDEF vao vao_create()
{
    vao result = {0};
    glGenVertexArrays(1, &result.id);    
    return result;
}

inline RGLDEF void vao_bind(vao self)
{
    glBindVertexArray(self.id);
}

inline RGLDEF void vao_unbind(vao self)
{
    glBindVertexArray(0);
}

inline RGLDEF void vao_delete(vao self)
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

//shader functions
/*NOTE: vs_data and fs_data are binary data from alread read file
* meaning you have to load the data with your own read API
* shader.valid is for checking if the program was compiled successfully
*/
RGLDEF shader shader_create(const char *vs_data, const char *fs_data, GLuint64 count)
{
    shader result = {0};

    result.vs_id = glCreateShader(GL_VERTEX_SHADER);
    result.fs_id = glCreateShader(GL_FRAGMENT_SHADER);

    //TODO: Add compilation status
    glShaderSource(result.vs_id, 1, &vs_data, (void *)0);
    glCompileShader(result.vs_id);

    //TODO: Add compilation status
    glShaderSource(result.fs_id, 1, &fs_data, (void *)0);
    glCompileShader(result.fs_id);

    //TODO: Add compilation status
    result.id = glCreateProgram();
    glAttachShader(result.id, result.vs_id);
    glAttachShader(result.id, result.fs_id);
    glLinkProgram(result.id);
}

inline RGLDEF void shader_bind(shader self)
{
    glUseProgram(self.id);
}

inline RGLDEF void shader_unbind(shader self)
{
    glUseProgram(0);
}

RGLDEF void shader_delete(shader self)
{
    glDeleteProgram(self.id);
    glDeleteShader(self.vs_id);
    glDeleteShader(self.fs_id);
}

inline RGLDEF void shader_set_bool(shader self, const char *name, GLboolean value)
{
    glUniform1i(glGetUniformLocation(self.id, name), (GLint)value);
}

inline RGLDEF void shader_set_int(shader self, const char *name, GLint value)
{
    glUniform1i(glGetUniformLocation(self.id, name), value);
}

inline RGLDEF void shader_set_float(shader self, const char *name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(self.id, name), value);
}

inline RGLDEF void shader_set_matrix4fv(shader self, const char *name, GLfloat *value)
{
    glUniformMatrix4fv(glGetUniformLocation(self.id, name), 1, GL_FALSE, value);
}

#endif