# RGL  
An only header OpenGL wrapper for personal use

## Usage

Create only **one** additional C/C++ file:
```c
#define _RGL_IMPLEMENTATION_
#include "rgl.h"
```
After that use the "rgl.h" file as a common header file.

Remark: You can also use another OpenGL loader. In my case I use GLAD, but you can use
something like GLEW or load the functions by yourself. Also do not forget to initialize your OpenGL loader library, or nothing will work.
