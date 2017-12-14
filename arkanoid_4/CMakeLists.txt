add_executable(arkanoid_4 main.cpp platform.cpp platform.h ball.cpp ball.h text.cpp text.h blocks.cpp  blocks.h)

target_include_directories(arkanoid_4 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(arkanoid_4 PUBLIC cxx_std_17)
target_compile_definitions(arkanoid_4 PRIVATE SFML_STATIC)

target_link_libraries(arkanoid_4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})