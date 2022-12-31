#include <Renderer/Framebuffer.hpp>
#include "Framebuffer.hpp"

namespace Clegine {
	Framebuffer::Framebuffer() { }

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &Id);
		glDeleteTextures(1, &imageId);

		LOG_DEBUG("Framebuffer terminated for processId={0} threadId={1}",
			GetCurrentProcessId(), std::this_thread::get_id());
	}

	void Framebuffer::Create(GLuint _width, GLuint _height, GLenum format1, GLenum format2) {
		width = _width;
		height = _height;

		glViewport(0, 0, width, height);

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

	void Framebuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, Id);
	}

	void Framebuffer::UnBind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}