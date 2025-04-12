add_executable(hashmap_v1_test 
hashmap_v1_test.cpp)

add_executable(hashmap_v2_test 
hashmap_v2_test.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()