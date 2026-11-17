// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/electron/TransitionEnergyBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace electron {

void wrapTransitionEnergyBlock( python::module& module, python::module& ) {
  
  // type aliases
  using Block = njoy::ACEtk::electron::TransitionEnergyBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(
  
    module,
    "TransitionEnergyBlock",
    "The electron EKT block with the transition energy data\n\n"
    "This block is part of el and el03 formats.\n\n"
    "The TransitionEnergyBlock class contains 2 or 4 data points:\n"
    "  - The K edge energy below which no electron induced relaxation will\n"
    "    occur (EDG)\n"
    "  - The K x-ray or Auger electron emission energy (EEK)\n"
    "  - The (2) bremsstrahlung extrapolation transition points (NEL != 3)\n"
  );
  
  // wrap the block
  block
  .def(
  
    python::init< std::vector< double > >(),
    python::arg( "values" ),
    "Initialize the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    values    the transition energy values (4 for el, 2 for el03)"
  )
  .def_property_readonly(
  
    "EDG",
    &Block::EDG,
    "The K edge energy"
  )
  .def_property_readonly(
  
    "k_edge_energy",
    &Block::kEdgeEnergy,
    "The K edge energy"
  )
  .def_property_readonly(
  
    "EEK",
    &Block::EEK,
    "The K x-ray or Auger electron emission energy"
  )
  .def_property_readonly(
  
    "k_xray_emission_energy",
    &Block::kXrayEmissionEnergy,
    "The K x-ray or Auger electron emission energy"
  )
  .def_property_readonly(
  
    "upper_bremsstrahlung_transition_energy",
    &Block::upperBremsstrahlungTransitionEnergy,
    "The upper bremsstrahlung extrapolation transition energy"
  )
  .def_property_readonly(
  
    "lower_bremsstrahlung_transition_energy",
    &Block::lowerBremsstrahlungTransitionEnergy,
    "The lower bremsstrahlung extrapolation transition energy"
  );
  
  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

}  // electron namespace
