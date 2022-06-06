// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/CoherentFormFactorBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapCoherentFormFactorBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::CoherentFormFactorBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "CoherentFormFactorBlock",
    "The photoatomic JCOH block with the coherent form factors\n\n"
    "The CoherentFormFactorBlock class contains coherent form factors that are\n"
    "used to modify the differential Thomson cross sectiontabulated on a fixed\n"
    "grid of the recoil electron momentum transfer (in inverse angstroms)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "integrated" ), python::arg( "factors" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self          the block\n"
    "    integrated    the integrated form factor values\n"
    "    factors       the form factor values"
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
    &Block::momentum,
    "The electron recoil momentum values"
  )
  .def_property_readonly(

    "integrated_form_factors",
    [] ( const Block& self ) -> DoubleRange
       { return self.integratedFormFactors(); },
    "The integrated form factor values"
  )
  .def_property_readonly(

    "form_factors",
    [] ( const Block& self ) -> DoubleRange
       { return self.formFactors(); },
    "The form factor values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
