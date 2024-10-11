#include "shader.h"

#include <stddef.h>

/*NOTE: vs_data and fs_data are binary data from alread read file
* meaning you have to load the data with your own read API
* shader.valid is for checking if the program was compiled successfully
*/
shader shader_create(char *vs_data, char *fs_data, GLuint64 count)
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

void shader_bind(shader self)
{
    glUseProgram(self.id);
}

void shader_unbind(shader self)
{
    glUseProgram(0);
}

void shader_delete(shader self)
{
    glDeleteProgram(self.id);
    glDeleteShader(self.vs_id);
    glDeleteShader(self.fs_id);
}
