set(VM_SRC
        include/memory.h
        include/state.h
        include/vm.h

        src/memory.cpp
        src/state.cpp
        src/vm.cpp
)

add_executable(HASM_VM ${VM_SRC})
target_include_directories(HASM_VM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(HASM_VM PRIVATE isa)