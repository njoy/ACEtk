// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/TabulatedSecondaryParticleMultiplicity.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapTabulatedSecondaryParticleMultiplicity( python::module& module,
                                                 python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::TabulatedSecondaryParticleMultiplicity;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "TabulatedSecondaryParticleMultiplicity",
    "Tabulated secondary particle multiplicity\n\n"
    "The TabulatedSecondaryParticleMultiplicity class contains tabulated\n"
    "multiplicities for a secondary particle (MFMULT = 12 or 16). It also\n"
    "contains the MT number of the associated reaction."
  );

  // wrap the block
  block
  .def(

    python::init< unsigned int, unsigned int,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "mftype" ), python::arg( "mt" ),
    python::arg( "energies" ), python::arg( "multiplicities" ),
    "Initialise the block assuming linear interpolation\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    mftype           the type (12 or 16)\n"
    "    mt               the associated reaction number\n"
    "    energies         the energy values\n"
    "    multiplicities   the multiplicity values"
  )
  .def(

    python::init< unsigned int, unsigned int,
                  std::vector< long >, std::vector< long >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "mftype" ), python::arg( "mt" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self            the block\n"
    "    mftype          the type (12 or 16)\n"
    "    mt              the associated reaction number\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    xs              the xs values"
  )
  .def_property_readonly(

    "MFTYPE",
    &Block::MFTYPE,
    "The representation type (should always be 12 or 16))"
  )
  .def_property_readonly(

    "type",
    &Block::type,
    "The representation type (should always be 12 or 16))"
  )
  .def_property_readonly(

    "MT",
    &Block::MT,
    "The associated reaction number"
  )
  .def_property_readonly(

    "reaction_number",
    &Block::reactionNumber,
    "The associated reaction number"
  )
  .def_property_readonly(

    "interpolation_data",
    &Block::interpolationData,
    "The interpolation data"
  )
  .def_property_readonly(

    "NB",
    &Block::NB,
    "The number of interpolation regions"
  )
  .def_property_readonly(

    "number_interpolation_regions",
    &Block::numberInterpolationRegions,
    "The number of interpolation regions"
  )
  .def_property_readonly(

    "NBT",
    [] ( const Block& self ) -> LongRange
       { return self.NBT(); },
    "The interpolation boundaries"
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Block& self ) -> LongRange
       { return self.boundaries(); },
    "The interpolation boundaries"
  )
  .def_property_readonly(

    "INT",
    [] ( const Block& self ) -> LongRange
       { return self.INT(); },
    "The interpolants"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Block& self ) -> LongRange
       { return self.interpolants(); },
    "The interpolants"
  )
  .def_property_readonly(

    "NE",
    &Block::NE,
    "The number of values"
  )
  .def_property_readonly(

    "number_values",
    &Block::numberValues,
    "The number of values"
  )
  .def_property_readonly(

    "E",
    [] ( const Block& self ) -> DoubleRange
       { return self.E(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "NU",
    [] ( const Block& self ) -> DoubleRange
       { return self.NU(); },
    "The multiplicities"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Block& self ) -> DoubleRange
       { return self.multiplicities(); },
    "The multiplicities"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
