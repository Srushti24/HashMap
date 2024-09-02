ADD_EXECUTABLE(HashMap main.cpp)

ADD_LIBRARY(Map
hashmap.cpp
)

target_link_libraries(HashMap PUBLIC Map)