// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/PhotoatomicComptonProfile.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotoatomicComptonProfile( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotoatomicComptonProfile;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotoatomicComptonProfile",
    "Tabulated Compton profile data for a given electron shell\n\n"
    "The PhotoatomicComptonProfile class contains the probability density\n"
    "function (PDF) and cumulative density function (CDF) as a function of\n"
    "momentum. It is used in the LSWD block."
  );

  // wrap the block
  block
  .def(

    python::init< int, std::vector< double >, std::vector< double >,
                  std::vector< double > >(),
    python::arg( "interpolation" ), python::arg( "momentum" ),
    python::arg( "pdf" ), python::arg( "cdf" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self            the block\n"
    "    interpolation   the interpolation type\n"
    "    momentum        the cosine values (N values)\n"
    "    pdf             the pdf values (N values)\n"
    "    cdf             the cdf values (N values)"
  )
  .def_property_readonly(

    "interpolation",
    &Block::interpolation,
    "The interpolation flag"
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
    "The momentum values"
  )
  .def_property_readonly(

    "pdf",
    [] ( const Block& self ) -> DoubleRange
       { return self.pdf(); },
    "The pdf values"
  )
  .def_property_readonly(

    "cdf",
    [] ( const Block& self ) -> DoubleRange
       { return self.cdf(); },
    "The cdf values"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
