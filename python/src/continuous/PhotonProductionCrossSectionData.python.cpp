// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/PhotonProductionCrossSectionData.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotonProductionCrossSectionData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotonProductionCrossSectionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotonProductionCrossSectionData",
    "Photon production cross section data from the SIGP block "
    "for a single reaction"
  );

  // wrap the block
  block
  .def(

    python::init< std::size_t, std::vector< double > >(),
    python::arg( "index" ), python::arg( "values" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self      the block\n"
    "    index     the energy index\n"
    "    values    the cross section values"
  )
  .def_property_readonly(

    "MFTYPE",
    &Block::MFTYPE,
    "The representation type (should always be 13)"
  )
  .def_property_readonly(

    "type",
    &Block::type,
    "The representation type (should always be 13)"
  )
  .def_property_readonly(

    "energy_index",
    &Block::energyIndex,
    "The energy index"
  )
  .def_property_readonly(

    "number_values",
    &Block::numberValues,
    "The number of cross section values"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Block& self ) -> DoubleRange
       { return self.crossSections(); },
    "The cross section values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
