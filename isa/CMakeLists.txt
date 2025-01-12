set(ISA_SRC
        include/instructions.h
        include/opcodes.h
        include/types.h
)

add_library(isa INTERFACE)
target_include_directories(isa INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)