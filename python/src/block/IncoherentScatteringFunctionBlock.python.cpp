// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/IncoherentScatteringFunctionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapIncoherentScatteringFunctionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::IncoherentScatteringFunctionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "IncoherentScatteringFunctionBlock",
    "The photoatomic JINC block with the incoherent scattering function values\n\n"
    "The IncoherentScatteringFunctionBlock class contains the scattering functions\n"
    "tabulated on a fixed grid of the recoil electron momentum (in inverse\n"
    "angstroms)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "values" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self       the block\n"
    "    values     the incoherent scattering function values"
  )
  .def_property_readonly(

    "NM",
    [] ( const Block& self ) { return self.NM(); },
    "The number of values"
  )
  .def_property_readonly(

    "number_values",
    [] ( const Block& self ) { return self.numberValues(); },
    "The number of values"
  )
  .def_property_readonly(

    "momentum",
    [] ( const Block& self ) { return self.momentum(); },
    "The electron recoil momentum values"
  )
  .def_property_readonly(

    "values",
    [] ( const Block& self ) -> DoubleRange
       { return self.values(); },
    "The incoherent scattering function values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
