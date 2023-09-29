// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/ProbabilityTableBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapProbabilityTableBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::ProbabilityTableBlock;
  using ProbabilityTable = njoy::ACEtk::block::ProbabilityTable;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "ProbabilityTableBlock",
    "The continuous energy UNR block with the unresolved resonance probability tables"
  );

  // wrap the block
  block
  .def(

    python::init< unsigned int, int, int, unsigned int,
                  std::vector< ProbabilityTable > >(),
    python::arg( "interpolation" ),
    python::arg( "inelastic" ),
    python::arg( "absorption" ),
    python::arg( "type" ),
    python::arg( "tables" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    interpolation    the interpolation type\n"
    "    inelastic        the inelastic competition flag\n"
    "    absorption       the absorption competition flag\n"
    "    type             the probability table type\n"
    "    tables           the probability tables"
  )
  .def_property_readonly(

    "N",
    &Block::N,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "number_incident_energies",
    &Block::numberIncidentEnergies,
    "The number of incident energy values"
  )
  .def_property_readonly(

    "M",
    &Block::M,
    "The number of bins in each table"
  )
  .def_property_readonly(

    "number_bins",
    &Block::numberBins,
    "The number of bins in each table"
  )
  .def_property_readonly(

    "INT",
    &Block::INT,
    "The interpolation flag"
  )
  .def_property_readonly(

    "interpolation",
    &Block::interpolation,
    "The interpolation flag"
  )
  .def_property_readonly(

    "ILF",
    &Block::ILF,
    "The inelastic competition flag"
  )
  .def_property_readonly(

    "inelastic_competition",
    &Block::inelasticCompetition,
    "The inelastic competition flag"
  )
  .def_property_readonly(

    "IOA",
    &Block::IOA,
    "The absorption competition flag"
  )
  .def_property_readonly(

    "absorption_competition",
    &Block::absorptionCompetition,
    "The absorption competition flag"
  )
  .def_property_readonly(

    "IFF",
    &Block::IFF,
    "The table type (values or multipliers)"
  )
  .def_property_readonly(

    "type",
    &Block::type,
    "The table type (values or multipliers)"
  )
  .def_property_readonly(

    "energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.energies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "data",
    &Block::data,
    "The probability tables"
  )
  .def(

    "probability_table",
    &Block::probabilityTable,
    python::arg( "index" ),
    "Return the probability table for an incident energy index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
