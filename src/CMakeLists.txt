add_executable(hashmap_generic_test 
hashmap_generic_test.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()