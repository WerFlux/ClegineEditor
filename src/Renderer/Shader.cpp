#include <Renderer/Shader.hpp>

namespace Clegine {
	void Shader::ReadFromRuntime(const char* vertexSrc, const char* fragmentSrc) {
		map[GL_VERTEX_SHADER] = vertexSrc;
		map[GL_FRAGMENT_SHADER] = fragmentSrc;
	}

	void Shader::Reset() {
		map.clear();
	}

	GLuint Shader::Compile() {
		GLint isCompiled = {};
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		GLuint programId = glCreateProgram();

		const GLchar* vertexSources = map[GL_VERTEX_SHADER];
		const GLchar* fragmentSources = map[GL_FRAGMENT_SHADER];
		glShaderSource(vertexShader, 1, &vertexSources, nullptr);
		glShaderSource(fragmentShader, 1, &fragmentSources, nullptr);

		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(vertexShader, length, &length, &infoLog[0]);
			glDeleteShader(vertexShader);
			LOG_WARNING("Fail when compiling Vertex shader (programId={0}): {1}",
				programId, infoLog.data());
		}

		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(fragmentShader, length, &length, &infoLog[0]);
			glDeleteShader(fragmentShader);
			LOG_WARNING("Fail when compiling Fragment shader (programId={0}): {1}",
				programId, infoLog.data());
		}

		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);
		glLinkProgram(programId);
		glGetProgramiv(programId, GL_LINK_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint length;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> infoLog(length);
			glGetProgramInfoLog(programId, length, &length, &infoLog[0]);
			LOG_WARNING("Fail when linking program (Id={0}): {1}", 
				programId, infoLog.data());
			glDeleteProgram(programId);
		}

		glDetachShader(programId, vertexShader);
		glDetachShader(programId, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		Reset();
		return programId;
	}
}