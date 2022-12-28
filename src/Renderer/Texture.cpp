#include <Renderer/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Clegine {
    Texture::Texture(GLuint _width, GLuint _height, GLenum format1, GLenum format2) : 
		width(_width), height(_height), internalFormat(format1), dataFormat(format2) {

        glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);
    }
	
	Texture::Texture(const char* path) {
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();

		std::unique_ptr<char[]> buffer(new char[size]);

		file.seekg(0, std::ios::beg);
		file.read(buffer.get(), size);

		int _width, _height, channels = 0;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data;
		data = stbi_load_from_memory(
			reinterpret_cast<stbi_uc*>(buffer.get()), 
			static_cast<int>(size), 
			&_width, 
			&_height, 
			&channels, 0);
		if (!data) { 
			LOG_ERROR("Failed when loading image from file: {0}", path);
			LOG_WARNING("Failure reason: {0}", stbi_failure_reason());
			return;		
		}

		width = _width;
		height = _height;
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		} else if(channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		ASSERT(internalFormat & dataFormat, "Image format not supported! (data and internal image format is not match)");

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &id);
	}

	void Texture::SetData(void* data, GLuint size) {	
		uint32_t bpp = dataFormat == GL_RGBA ? 4 : 3;
		uint32_t expectedSize = width * height * bpp;

		ASSERT(size == expectedSize, "Data must be entire texture!");

		glBindTexture(GL_TEXTURE_2D, id);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Bind() {
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::UnBind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}