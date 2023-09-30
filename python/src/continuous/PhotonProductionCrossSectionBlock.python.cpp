// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/PhotonProductionCrossSectionBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapPhotonProductionCrossSectionBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::PhotonProductionCrossSectionBlock;
  using PhotonProductionData = njoy::ACEtk::continuous::PhotonProductionData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotonProductionCrossSectionBlock",
    "The PhotonProductionCrossSectionBlock class contains NXS(6) sets of photon\n"
    "production data, one for each reaction number on the MTRP block. The order\n"
    "of these cross section data sets is the same as the order of the reaction\n"
    "numbers in the MTRP block."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< PhotonProductionData > >(),
    python::arg( "xs" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self    the block\n"
    "    xs      the cross section data"
  )
  .def_property_readonly(

    "NTRP",
    &Block::NTRP,
    "The number of photon production reactions"
  )
  .def_property_readonly(

    "number_photon_production_reactions",
    &Block::numberPhotonProductionReactions,
    "The number of photon production reactions"
  )
  .def(

    "LSIG",
    &Block::LSIG,
    python::arg( "index" ),
    "Return the relative cross section locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "cross_section_locator",
    &Block::crossSectionLocator,
    python::arg( "index" ),
    "Return the relative cross section locator for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "The cross section data"
  )
  .def(

    "cross_section_data",
    &Block::crossSectionData,
    python::arg( "index" ),
    "Return the cross section data for a reaction index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
