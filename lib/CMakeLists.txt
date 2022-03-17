add_subdirectory(fmt)

add_library(imgui OBJECT
    imgui/imconfig.h
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_internal.h
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_opengl3.h
    imgui/backends/imgui_impl_opengl3_loader.h
    imgui/backends/imgui_impl_sdl.cpp
    imgui/backends/imgui_impl_sdl.h
    imgui/misc/cpp/imgui_stdlib.cpp
    imgui/misc/cpp/imgui_stdlib.h
    imgui/misc/freetype/imgui_freetype.cpp
    imgui/misc/freetype/imgui_freetype.h
)

target_link_libraries(imgui PRIVATE "-framework CoreFoundation" "-framework OpenGl")

target_link_libraries(imgui PRIVATE Freetype::Freetype SDL2::SDL2)
target_include_directories(imgui PUBLIC imgui imgui/backends)