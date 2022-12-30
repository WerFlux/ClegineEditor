#include <Renderer/Framebuffer.hpp>
#include "Framebuffer.hpp"

namespace Clegine {
	Framebuffer::Framebuffer(GLuint _width, GLuint _height, GLenum format1, GLenum format2) :
		width(_width), height(_height) 
	{
		glGenFramebuffers(1, &Id);
		glBindFramebuffer(GL_FRAMEBUFFER, Id);

		glGenTextures(1, &imageId);
		glBindTexture(GL_TEXTURE_2D, imageId);
		glTexImage2D(GL_TEXTURE_2D, 0, format1, width, height, 0, format2, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, imageId, 0);
		ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &Id);
		glDeleteTextures(1, &imageId);
	}

	void Framebuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, Id);
		glViewport(0, 0, width, height);
	}

	void Framebuffer::UnBind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}