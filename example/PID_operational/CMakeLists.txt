set(example_name "PID_operational")

set(example_name_PD "PD_test")

set(example_name_rrt "rrt_test")

set(example_rrt "rrt")

set(example_LQR "lqr")

set(example_value "value-iter")

set(example_ekf "ekf")

set(example_different_kin "diff_kin")

set(example_error_test "error_test")

set(example_BD "BD")
set(example_cpp "cpp")

add_executable(${example_name} main.cpp)
target_link_libraries(${example_name}
        conpt::conpt
        )
        add_executable(${example_name_PD} test_controller.cpp)
        target_link_libraries(${example_name_PD}
                conpt::conpt
                )
add_executable(${example_name_rrt} RRT_original.cpp)
target_link_libraries(${example_name_rrt}
conpt::conpt)



add_executable(${example_rrt} RRT.cpp)
target_link_libraries(${example_rrt}
conpt::conpt)

add_executable(${example_LQR} LQR.cpp)
target_link_libraries(${example_LQR}
conpt::conpt)

add_executable(${example_value} value_iteration.cpp)
target_link_libraries(${example_value}
conpt::conpt)

add_executable(${example_ekf} EKF.cpp)
target_link_libraries(${example_ekf}
conpt::conpt)

add_executable(${example_different_kin} different_kin.cpp)
target_link_libraries(${example_different_kin}
conpt::conpt)

add_executable(${example_error_test} error_test.cpp)
target_link_libraries(${example_error_test}
conpt::conpt)

add_executable(${example_BD} BD.cpp)
target_link_libraries(${example_BD}
conpt::conpt)

add_executable(${example_cpp} study_CPP.cpp)
target_link_libraries(${example_cpp}
conpt::conpt)