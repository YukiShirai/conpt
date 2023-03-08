set(example_name "PID_joint")


add_executable(${example_name} main.cpp)
target_link_libraries(${example_name}
        conpt::conpt
        )
