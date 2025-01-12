set(ASSEMBLER_SRC
        include/emitter.h
        include/parser.h

        src/emitter.cpp
        src/parser.cpp
        src/assembler.cpp
)

add_executable(HASM_ASSEMBLER ${ASSEMBLER_SRC})
