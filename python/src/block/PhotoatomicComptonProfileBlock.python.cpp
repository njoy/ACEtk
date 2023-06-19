// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/PhotoatomicComptonProfileBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotoatomicComptonProfileBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotoatomicComptonProfileBlock;
  using PhotoatomicComptonProfile = njoy::ACEtk::block::PhotoatomicComptonProfile;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotoatomicComptonProfileBlock",
    "The photoatomic LSWD and SWD block with the compton profile data\n\n"
    "The PhotoatomicComptonProfileBlock class contains NXS(5) sets of compton\n"
    "profiles, one for each electron shell."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< PhotoatomicComptonProfile > >(),
    python::arg( "profiles" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self        the block\n"
    "    profiles    the compton profile data"
  )
  .def_property_readonly(

    "NSH",
    &Block::NSH,
    "The number of electron shelld"
  )
  .def_property_readonly(

    "number_electron_shells",
    &Block::numberElectronShells,
    "The number of electron shelld"
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

} // block namespace
