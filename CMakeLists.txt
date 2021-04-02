cmake_minimum_required(VERSION 3.10)

# set the project name
project(opengl_experiment VERSION 0.1)

#specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_SAND "Use main provided opengl implementation" ON)

configure_file(opengl_experiment_config.h.in opengl_experiment_config.h)



if(USE_SAND)
    add_subdirectory(sand)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/sand")
endif()

# add the executable
add_executable(opengl_experiment main.cpp)

target_link_libraries(opengl_experiment PUBLIC ${EXTRA_LIBS})

# configuration files should be added for target include directories
target_include_directories(opengl_experiment PUBLIC
                        "${PROJECT_BINARY_DIR}"
                        ${EXTRA_INCLUDES}
                        )

#install(TARGETS opengl_experiment DESTINATION bin)
#install(FILES "${PROJECT_BINARY_DIR}/opengl_experiment_config.h" DESTINATION include)