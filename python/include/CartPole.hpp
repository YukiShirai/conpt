#pragma once

#include <pybind11/pybind11.h> // pybind11 base library

#include "conpt/TO_base.h"
#include "conpt/CartPole.h"


namespace py = pybind11;

void init_opt(py::module &m){
    py::module opt = m.def_submodule("opt", "set up for trajectory optimization");

    // create pybind class
    py::class_<conpt::TO_base>(opt, "TOBase"); // You cannot create instance for this base class since this is abstract class. 
    py::class_<conpt::CartPole, conpt::TO_base>(opt, "CartPole") // for derived class, you need to specify the base class as well when defining class through pybind11.
    .def(py::init<>())
    // .def("talk", &conpt::CartPole::Talk)
    ;
}