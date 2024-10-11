# RGL - OpenGL Wrapper

RGL is a lightweight and easy-to-use OpenGL wrapper developed for personal projects and experimentation with OpenGL functionalities. This wrapper streamlines the setup and use of OpenGL, allowing you to focus on rendering and visualizing graphics without diving deep into the complexities of OpenGL's API.  

### Features

- Simplified OpenGL setup
- Basic rendering functionality
- Easy-to-use C interface for quick integration# RGL  

## Usage

Create only **one** additional C/C++ file:
```c
#define _RGL_IMPLEMENTATION_
#include "rgl.h"
```
After that use the "rgl.h" file as a common header file. If you want to use the wrapper within one translation unit add also:
```c
#define RGL_STATIC
```
before including the file so every function becomes static by default.

**Remark**: You can also use another OpenGL loader. In my case I use GLAD, but you can use something like GLEW or load the functions by yourself. Also do not forget to initialize your OpenGL loader library, or nothing will work.

## License

[MIT](https://mit-license.org/)
