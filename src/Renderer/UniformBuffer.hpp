#ifndef CLEGINE_GRAPHICS_UNIBUFF_HPP
#define CLEGINE_GRAPHICS_UNIBUFF_HPP

#include <EntryPoint.hpp>
#include <Core/Logger.hpp>

namespace Clegine {
	/* Begin Uniform Buffer 1 Dimension (Vector1 in GLM) */
	struct UniformBuffer1D : public Singleton<UniformBuffer1D> {
		void SetInt(GLuint programId, const GLchar* locName, GLint value) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform1i(location, value);
		}

		void SetFloat(GLuint programId, const GLchar* locName, GLfloat value) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform1f(location, value);
		}

		void SetDouble(GLuint programId, const GLchar* locName, GLdouble value) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform1d(location, value);
		}
	};
	/* End of Uniform Buffer 1 Dimension */

	/* Begin Uniform Buffer 2 Dimension (Vector2 in GLM) */
	struct UniformBuffer2D : public Singleton<UniformBuffer2D> {
		void SetInt(GLuint programId, const GLchar* locName, GLint val1, GLint val2) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform2i(location, val1, val2);
		}

		void SetFloat(GLuint programId, const GLchar* locName, GLfloat val1, GLfloat val2) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform2f(location, val1, val2);
		}

		void SetDouble(GLuint programId, const GLchar* locName, GLdouble val1, GLdouble val2) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform2d(location, val1, val2);
		}
	};
	/* End of Uniform Buffer 2 Dimension */

	/* Begin Uniform Buffer 3 Dimension (Vector3 in GLM) */
	struct UniformBuffer3D : public Singleton<UniformBuffer3D> {
		void SetInt(GLuint programId, const GLchar* locName, GLint val1, GLint val2, GLint val3) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform3i(location, val1, val2, val3);
		}

		void SetFloat(GLuint programId, const GLchar* locName, GLfloat val1, GLfloat val2, GLfloat val3) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform3f(location, val1, val2, val3);
		}

		void SetDouble(GLuint programId, const GLchar* locName, GLdouble val1, GLdouble val2, GLdouble val3) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform3d(location, val1, val2, val3);
		}
	};
	/* End of Uniform Buffer 2 Dimension */

	/* Begin Uniform Buffer 4 Dimension (Vector4 (if exist) in GLM) */
	struct UniformBuffer4D : public Singleton<UniformBuffer4D> {
		void SetInt(GLuint programId, const GLchar* locName, 
			GLint val1, GLint val2, GLint val3, GLint val4) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform4i(location, val1, val2, val3, val4);
		}

		void SetFloat(GLuint programId, const GLchar* locName, 
			GLfloat val1, GLfloat val2, GLfloat val3, GLfloat val4) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform4f(location, val1, val2, val3, val4);
		}

		void SetDouble(GLuint programId, const GLchar* locName, 
			GLdouble val1, GLdouble val2, GLdouble val3, GLdouble val4) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniform4d(location, val1, val2, val3, val4);
		}
	};
	/* End of Uniform Buffer 4 Dimension */

	/* Begin Uniform Buffer Matrix 4x4 (mat4 in GLM) */
	struct UniformBufferMatrix4x4 : public Singleton<UniformBufferMatrix4x4> {
		void Set(GLuint programId, const GLchar* locName, const glm::mat4& mat) {
			GLint location = glGetUniformLocation(programId, locName);
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
		}
	};
	/* End of Uniform Buffer Matrix 4x4 */
}
#endif // CLEGINE_GRAPHICS_UNIBUFF_HPP
