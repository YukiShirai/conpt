set(example_name "SlipBox")


add_executable(${example_name} main.cpp)

target_link_libraries(${example_name}
	PUBLIC
        ContactRichOpt
        param
        casadi
        Eigen3::Eigen
        )

