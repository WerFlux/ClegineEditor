#ifndef CLEGINE_RENDERER_TEXTURE_HPP
#define CLEGINE_RENDERER_TEXTURE_HPP

#include <EntryPoint.hpp>
#include <Core/Logger.hpp>
#include <fstream>

namespace Clegine {
    class Texture {
    public:
        Texture(GLuint _width, GLuint _height, GLenum format1, GLenum format2);
        Texture(const char* path);

        ~Texture();

        void SetData(void* data, GLuint size);
        void Bind();
        void UnBind();

        inline GLuint GetWidth() const noexcept { return width; }
        inline GLuint GetHeight() const noexcept { return height; }
        inline GLuint GetID() const noexcept { return id; }
    private:
        GLuint width, height;
        GLuint id;
        GLenum internalFormat, dataFormat;
    };
}
#endif // CLEGINE_RENDERER_TEXTURE_HPP