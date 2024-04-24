// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace photoatomic {

void wrapIncoherentScatteringFunctionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::photoatomic::IncoherentScatteringFunctionBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "IncoherentScatteringFunctionBlock",
    "The photoatomic JINC block with the incoherent scattering function\n\n"
    "The IncoherentScatteringFunctionBlock class contains one of the following\n"
    "representations of the scattering function:\n"
    "  - 21 scattering function values using a fixed momentum grid (mcplib version)\n"
    "  - tabulated momentum and scattering function values (eprdata version)\n\n"
    "The interface abstracts away the distinction between the two representations.\n\n"
    "The recoil electron momentum transfer values are given in inverse angstroms."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double > >(),
    python::arg( "values" ),
    "Initialise the block using the mcplib representation\n\n"
    "Arguments:\n"
    "    self       the block\n"
    "    values     the incoherent scattering function values (21 in total)"
  )
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "momentum" ), python::arg( "values" ),
    "Initialise the block using the eprdata representation\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    momentum    the momentum values"
    "    values      the incoherent scattering function values"
  )
  .def_property_readonly(

    "NM",
    &Block::NM,
    "The number of values"
  )
  .def_property_readonly(

    "number_values",
    &Block::numberValues,
    "The number of values"
  )
  .def_property_readonly(

    "momentum",
    [] ( const Block& self ) -> DoubleRange
       { return self.momentum(); },
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

} // photoatomic namespace
