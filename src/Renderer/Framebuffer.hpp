#ifndef CLEGINE_RENDERER_FRAMEBUFFER_HPP
#define CLEGINE_RENDERER_FRAMEBUFFER_HPP

#include <EntryPoint.hpp>
#include <Renderer/Texture.hpp>

namespace Clegine {
	class Framebuffer {
	private:
		/* Do not allow creating Framebuffer instance without arguments */
		Framebuffer() = delete;
		/* Do not allow too copy other Framebuffer */
		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;
	public:
		Framebuffer(GLuint _width, GLuint _height, GLenum format1, GLenum format2);
		~Framebuffer();

		void Bind();
		void UnBind();

		/* Get Framebuffer Image (Texture) ID */
		inline GLuint GetImageID() const noexcept { return imageId; }
		/* Get Framebuffer generated ID */
		inline GLuint GetID() const noexcept { return Id; }
	private:
		GLuint width, height;
		GLuint imageId;
		GLuint Id;
	};
}

#endif // CLEGINE_RENDERER_FRAMEBUFFER_HPP
