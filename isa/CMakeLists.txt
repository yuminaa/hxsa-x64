set(ISA_SRC
        include/instructions.h
        include/opcodes.h
        include/types.h
        src/instructions.cpp
)

add_library(isa STATIC ${ISA_SRC})
target_include_directories(isa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)