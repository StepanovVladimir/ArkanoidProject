add_executable(arkanoid_5 main.cpp platform.cpp platform.h ball.cpp ball.h text.cpp text.h blocks.cpp blocks.h backgraund.cpp backgraund.h bonuses.cpp bonuses.h)

target_include_directories(arkanoid_5 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(arkanoid_5 PUBLIC cxx_std_17)
target_compile_definitions(arkanoid_5 PRIVATE SFML_STATIC)

target_link_libraries(arkanoid_5 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})