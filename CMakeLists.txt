cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Gardener VERSION 0.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Gardener main.cpp config.cpp)
# timer.cpp pump.cpp gardener.cpp)

# Link against wiringPi
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(Gardener ${WIRINGPI_LIBRARIES})

configure_file(GardenerConfig.h.in GardenerConfig.h)

target_include_directories(Gardener PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS Gardener DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/GardenerConfig.h"
        DESTINATION include
        )
