#ifndef CLEGINE_ENTRYPOINT_HPP
#define CLEGINE_ENTRYPOINT_HPP

// Fuck off WINAPI
#pragma warning(disable: 4005 26495)

#include <string>
#include <vector>
#include <functional>
#include <memory>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <ImGUI/imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <ImGUI/imgui_impl_opengl3.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_internal.h>

#include <Core/Common.hpp>
#include <Core/Assert.hpp>
#include <Core/Singleton.hpp>

#endif // CLEGINE_ENTRYPOINT_HPP