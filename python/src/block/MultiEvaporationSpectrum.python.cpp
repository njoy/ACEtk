// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/MultiEvaporationSpectrum.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapMultiEvaporationSpectrum( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::MultiEvaporationSpectrum;
  using DistributionData = njoy::ACEtk::block::EvaporationSpectrum;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "MultiEvaporationSpectrum",
    "The distribution is a combination of multiple EvaporationSpectrum\n\n"
    "The MultiEvaporationSpectrum class contains a set of evaporation spectra and\n"
    "associated probabilities to represent the particle's distribution data.\n"
    "It is used in the DLW block (there is no ACE LAW associated to this\n"
    "distribution type, but internally in ACEtk we refer to it as ACE LAW 6669\n"
    "because it is evil)."
  );

  // add standard block definitions
  addStandardMultiDistributionDefinitions< Block, DistributionData >( block );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
