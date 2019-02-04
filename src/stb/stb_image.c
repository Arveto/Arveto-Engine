#define STBI_ASSERT(x) before the #include to avoid using assert.h.
And #define STBI_MALLOC, STBI_REALLOC, and STBI_FREE to avoid using malloc,realloc,free

#define STBI_ASSERT(x)
#define STBI_MALLOC
#define STBI_REALLOC
#define STBI_FREE
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
