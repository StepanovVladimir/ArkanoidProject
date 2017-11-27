add_executable(arkanoid_2 main.cpp platform.cpp platform.h ball.cpp ball.h text.cpp text.h)

target_include_directories(arkanoid_2 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(arkanoid_2 PUBLIC cxx_std_17)
target_compile_definitions(arkanoid_2 PRIVATE SFML_STATIC)

target_link_libraries(arkanoid_2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})