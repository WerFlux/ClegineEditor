#include <Renderer/OrthoCamera.hpp>

namespace Clegine {
	void OrthoCamera::SetProjection(float left, float right, float bottom, float top) {
		projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}
}