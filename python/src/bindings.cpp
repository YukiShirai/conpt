
#include <pybind11/pybind11.h>


#include "CartPole.hpp"

namespace py = pybind11;

// Create a python module
PYBIND11_MODULE(pyconpt, m) { // first argument is python name of module. MUST MATCH TARGET NAME IN CMAKELISTS.TXT (Case sensitive)
    // Pass in the reference to the module to create each submodule
    init_opt(m);
};
