cmake_minimum_required (VERSION 3.8)

project ("ClegineEditor" VERSION 1.0.1)

set(SOURCE_ROOT "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_ROOT "${PROJECT_SOURCE_DIR}/include")

set(CORE_ROOT "${SOURCE_ROOT}/Core")
set(RENDERER_ROOT "${SOURCE_ROOT}/Renderer")
set(SCENE_ROOT "${SOURCE_ROOT}/Scene")

# use file(GLOB_RECUSE) cause am lazy
file(GLOB_RECURSE CLEGINE_INCLUDE_FILES 
    "${INCLUDE_ROOT}/CECS/*.hpp"
    "${INCLUDE_ROOT}/ImGUI/*.hpp"
    "${INCLUDE_ROOT}/ImGUI/*.cpp"
    "${INCLUDE_ROOT}/stb/*.hpp"
    "${INCLUDE_ROOT}/GLAD/glad.c"
)

# use file(GLOB_RECUSE) cause am lazy
file(GLOB_RECURSE CLEGINE_SOURCE_FILES
    "${CORE_ROOT}/*.hpp"
    "${CORE_ROOT}/*.cpp"

    "${RENDERER_ROOT}/*.hpp"
    "${RENDERER_ROOT}/*.cpp"

    "${SCENE_ROOT}/*.hpp"
    "${SCENE_ROOT}/*.cpp"

    "${SOURCE_ROOT}/*.hpp"
    "${SOURCE_ROOT}/*.cpp"
)

add_executable(${PROJECT_NAME} ${CLEGINE_INCLUDE_FILES} ${CLEGINE_SOURCE_FILES} "src/Renderer/Framebuffer.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} PRIVATE opengl32.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/libs/glfw3.lib")

# Enable memory checking
target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)

# Add /MP to Compile Options
set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_OPTIONS "/MP")
# Add /debug:fastline to Link Options
set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_OPTIONS "/debug:fastlink")
# Add /incremental to Link Options
set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_OPTIONS "/incremental")

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED OFF
        CXX_EXTENSIONS OFF
)