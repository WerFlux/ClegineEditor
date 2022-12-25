#ifndef CLEGINE_GRAPHICS_SHADER_HPP
#define CLEGINE_GRAPHICS_SHADER_HPP

#include <Core/Logger.hpp>

#include <unordered_map>

namespace Clegine {
	class Shader {
	public:
		Shader() = default;
		~Shader() = default;

		void ReadFromRuntime(const char* vertexSrc, const char* fragmentSrc);

		void Reset();

		GLuint Compile();
	private:
		std::unordered_map<GLenum, const char*> map;
	};
}

#endif // CLEGINE_GRAPHICS_SHADER_HPP
