add_executable(arkanoid_1 main.cpp)

target_include_directories(arkanoid_1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(arkanoid_1 PUBLIC cxx_std_17)
target_compile_definitions(arkanoid_1 PRIVATE SFML_STATIC)

target_link_libraries(arkanoid_1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})