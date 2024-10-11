#include "vbo.h"

vbo vbo_create(GLint type, bool dynamic)
{
    vbo result = {
        .dynamic = dynamic,
        .type = type,
    };
    glGenBuffers(1, &result.id);

    return result;
}

void vbo_bind(vbo self)
{
    glBindBuffer(self.type, self.id);
}

void vbo_unbind(vbo self)
{
    glBindBuffer(self.type, 0);
}

void vbo_delete(vbo self)
{
    glDeleteBuffers(1, &self.id);
}

void vbo_buffer(vbo self, void *data, GLuint64 offset, GLuint64 count)
{
    vbo_bind(self);
    glBufferData(GL_ARRAY_BUFFER, count - offset, data, self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
