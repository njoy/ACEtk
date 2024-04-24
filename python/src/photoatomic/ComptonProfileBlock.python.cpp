// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/photoatomic/ComptonProfileBlock.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace photoatomic {

void wrapComptonProfileBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::photoatomic::ComptonProfileBlock;
  using ComptonProfile = njoy::ACEtk::photoatomic::ComptonProfile;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ComptonProfileBlock",
    "The photoatomic LSWD and SWD block with the compton profile data\n\n"
    "The ComptonProfileBlock class contains NXS(5) sets of compton profiles, one\n"
    "for each electron shell."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< ComptonProfile > >(),
    python::arg( "profiles" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    profiles    the compton profile data"
  )
  .def_property_readonly(

    "NSH",
    &Block::NSH,
    "The number of electron shells"
  )
  .def_property_readonly(

    "number_electron_shells",
    &Block::numberElectronShells,
    "The number of electron shells"
  )
  .def(

    "LSWD",
    &Block::LSWD,
    python::arg( "index" ),
    "Return the relative compton profile locator for an electron shell index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "compton_profile_locator",
    &Block::comptonProfileLocator,
    python::arg( "index" ),
    "Return the relative compton profile locator for an electron shell index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "The compton profiles"
  )
  .def(

    "compton_profile",
    &Block::comptonProfile,
    python::arg( "index" ),
    "Return the compton profile for an electron shell index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // photoatomic namespace
