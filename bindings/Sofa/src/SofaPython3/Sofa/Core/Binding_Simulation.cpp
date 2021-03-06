#include "Binding_Simulation.h"

#include <sofa/simulation/Simulation.h>
using sofa::simulation::Simulation;

#include <SofaSimulationGraph/DAGSimulation.h>
using sofa::simulation::graph::DAGSimulation;

using sofa::simulation::Node;
using namespace pybind11::literals;

namespace sofapython3
{

void moduleAddSimulation(py::module &m)
{
  if(!sofa::simulation::getSimulation())
    sofa::simulation::setSimulation(new DAGSimulation());

  py::module singleRuntime = m.def_submodule("Simulation");
  singleRuntime.def("print", [](Node* n){ sofa::simulation::getSimulation()->print(n); });
  singleRuntime.def("animate", [](Node* n, SReal dt=0.0){ sofa::simulation::getSimulation()->animate(n, dt); });
  singleRuntime.def("init", [](Node* n){ sofa::simulation::getSimulation()->init(n); });
  singleRuntime.def("reset", [](Node* n){ sofa::simulation::getSimulation()->reset(n); });
  singleRuntime.def("load", [](const std::string name){ return sofa::simulation::getSimulation()->load(name.c_str());});
  singleRuntime.def("unload", [](Node* n){ sofa::simulation::getSimulation()->unload(n); });
}


} /// namespace sofapython3
