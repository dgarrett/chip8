add_executable(chip8
    chip.cpp
    chip.h
    main.cpp
    util.h
    video.cpp
)

target_link_libraries(chip8 PRIVATE imgui SDL2::SDL2 SDL2::SDL2main)