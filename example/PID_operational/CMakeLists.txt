set(example_name "PID_operational")


add_executable(${example_name} main.cpp)
target_link_libraries(${example_name}
        conpt::conpt
        )
