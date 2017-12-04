add_executable(arkanoid_3 main.cpp platform.cpp platform.h ball.cpp ball.h text.cpp text.h blocks.cpp  blocks.h)

target_include_directories(arkanoid_3 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(arkanoid_3 PUBLIC cxx_std_17)
target_compile_definitions(arkanoid_3 PRIVATE SFML_STATIC)

target_link_libraries(arkanoid_3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})