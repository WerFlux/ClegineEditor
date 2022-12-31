#ifndef CLEGINE_RENDERER_FRAMEBUFFER_HPP
#define CLEGINE_RENDERER_FRAMEBUFFER_HPP

#include <EntryPoint.hpp>
#include <Renderer/Texture.hpp>

namespace Clegine {
	class Framebuffer : public Singleton<Framebuffer>{
	public:
		Framebuffer();
		~Framebuffer();

		void Create(GLuint _width, GLuint _height, GLenum format1, GLenum format2);
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
