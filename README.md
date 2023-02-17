# CONPT (CONtact-rich trajectory oPTimization)
C++/python codes for contact-implicit trajectory optimization for locomotion and manipulation.

# Dependencies
- Ubuntu 20.04+
- CMake 3.15+
- Python 3.6+
- C++11
- pybind11
- Eigen3
- casadi (SHA "402fe583f0d3cf1fc77d1e1ac933f75d86083124"). Note that when you build casadi from source, make sure you do `cmake -DWITH_IPOPT=true`.
- [param](https://github.com/YukiShirai/param), originally from [here](https://github.com/kaityo256/param)
- [matplotlib-cpp](https://github.com/lava/matplotlib-cpp). Note that please install this package in your (native) environment.


# Build and Installation
- The easiest way to install is through CMake. We first install the dependencies: 
```
sudo apt-get install python3-dev cmake libeigen3-dev
```
- Then, you need to install [casadi](https://casadi.sourceforge.net/v1.3.0/api/html/d3/def/chapter2.html) and [param](https://github.com/YukiShirai/param). For param installation, see [this](https://github.com/YukiShirai/param).
- For casadi, you can also follow [this](https://casadi.sourceforge.net/v1.3.0/api/html/d3/def/chapter2.html). Note that if you are interested in using optimization solvers such as gurobi, which are not compiled as a default CMake setting of casadi, you need to recompile casadi. Or you can simply run the following commands:
```
git clone https://github.com/casadi/casadi.git
cd casadi; mkdir build; cd build
cmake ..
cmake --build .
sudo make install
```

- Finally, we are ready to build and install ContactRichOpt. To do that, like how we installed casadi, we use CMake as follows:
```
git clone https://github.com/YukiShirai/ContactRichOpt.git
cd casadi; mkdir build; cd build
cmake ..
cmake --build .
sudo make install
```
- and that's it! Note that if your CMake project complains during your `cmake ..` like:
```
/usr/bin/ld: cannot find -lContactRichOpt
```
- then check where your `libContactRichOpt.so` was installed. It can be `/usr/local/lib`. If that's the case, crate symbolic link as follows:
```
sudo ln -s /usr/local/lib/libContactRichOpt.so /usr/lib/libContactRichOpt.so
```

# Usage for your project in python (under construction)
conpt supports python binding, pyconpt, through pybind11. 
1. Set up virtual environment in `conpt/build`: 
```
sudo pip3 install virtualenv
virtualenv -p /usr/bin/python3 env
source env/bin/activate
pip install numpy
```

2. After you finish installing conpt from source, pyconpt should be ready to be used. For example, 
```
from pyconpt import opt

cartpole = opt.CartPole()
```


# Usage for your project in C++ (under construction)
The easiest way is using CMake. 
1. To call ContactRichOpt in your CMake project, you can do as follows:
```
find_package(ContactRichOpt REQUIRED)

target_link_libraries(BINARY_NAME
	                    PUBLIC
		                  ContactRichOpt)
```
2. Then, in your c++ code, 
```
#include "conpt/CartPole.h"
```


# TODO
- [] support other toy problems
- [] support python bindings using pybind11. 
- [] support mixed-integer programming through gurobi
- [] support stochastic optimization such as chance-constrained optimization.
- [] integrate with simulator such as pybullet / drake. 
- [] support MPC
- [] support bilevel optimization
- [] improve customizability. user should be able to add any constraints through main.cpp. 


# Citation
```
@misc{shirai2023ContactRichOpt,
  author = {Yuki Shirai},
  title = {libContactRichOpt},
  year = {2023},
  publisher = {GitHub},
  journal = {GitHub repository},
  howpublished = {\url{https://github.com/YukiShirai/ContactRichOpt}}
}
```

# Contact
If you have any questions, feel free to ask questions via issues or email. 

[@YukiShirai](https://github.com/YukiShirai) (yukishirai4869@g.ucla.edu)

# Acknowledgements
[@ColinTogashi](https://github.com/ColinTogashi) for discussion about CMake and pybind11.

# Reference
[1] [Y. Shirai, D. K. Jha, A. U. Raghunathan, D. Romeres, "Chance-Constrained Optimization in Contact-Rich Systems
for Robust Manipulation", ACC2023](https://arxiv.org/pdf/2203.02616.pdf)

[2] [A. U. Raghunathan, D. K. Jha and D. Romeres, "PyROBOCOP: Python-based Robotic Control & Optimization Package for Manipulation", ICRA2022](https://ieeexplore.ieee.org/document/9812069)

[3] [Y. Shirai, D. K. Jha, A. U. Raghunathan and D. Romeres, "Robust Pivoting: Exploiting Frictional Stability Using Bilevel Optimization", ICRA2022](https://ieeexplore.ieee.org/document/9811812)

[4] [Y. Shirai et al., "Simultaneous Contact-Rich Grasping and Locomotion via Distributed Optimization Enabling Free-Climbing for Multi-Limbed Robots", IROS2022](https://ieeexplore.ieee.org/document/9981579)

[5] [Y. Shirai, X. Lin, Y. Tanaka, A. Mehta and D. Hong, "Risk-Aware Motion Planning for a Limbed Robot with Stochastic Gripping Forces Using Nonlinear Programming", IEEE Robotics and Automation Letters, 2020](https://ieeexplore.ieee.org/abstract/document/9113247)
