set(example_name "PID_operational")

set(example_name_PD "PD_test")

add_executable(${example_name} main.cpp)
target_link_libraries(${example_name}
        conpt::conpt
        )
        add_executable(${example_name_PD} test_controller.cpp)
        target_link_libraries(${example_name_PD}
                conpt::conpt
                )
