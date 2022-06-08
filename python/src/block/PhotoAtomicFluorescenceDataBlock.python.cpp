// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/PhotoAtomicFluorescenceDataBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapPhotoAtomicFluorescenceDataBlock( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::PhotoAtomicFluorescenceDataBlock;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "PhotoAtomicFluorescenceDataBlock",
    "The photoatomic JFLO block with the fluorescence data\n\n"
    "The PhotoAtomicFluorescenceDataBlock class contains 4 arrays of the\n"
    "same length:\n"
    "  - the fluoresence edge energies\n"
    "  - the relative ejection probabilities\n"
    "  - the yields\n"
    "  - the fluorescent energies\n"
    "The size of each (the total number of fluorescence edges) is stored in NXS(4)."
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< double >, std::vector< double > >(),
    python::arg( "edges" ), python::arg( "probabilities" ),
    python::arg( "yields" ), python::arg( "energies" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    edges            the edge energies\n"
    "    probabilities    the ejection probabilities\n"
    "    yields           the yields\n"
    "    energies         the fluorescent energies"
  )
  .def_property_readonly(

    "NFLO",
    &Block::NFLO,
    "The number of fluoresence edges"
  )
  .def_property_readonly(

    "number_fluorescence_edges",
    &Block::numberFluorescenceEdges,
    "The number of electron shells"
  )
  .def_property_readonly(

    "E",
    [] ( const Block& self ) -> DoubleRange
       { return self.E(); },
    "The fluoresence edge energies"
  )
  .def_property_readonly(

    "fluorescence_edge_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.fluorescenceEdgeEnergies(); },
    "The fluoresence edge energies"
  )
  .def_property_readonly(

    "PHI",
    [] ( const Block& self ) -> DoubleRange
       { return self.PHI(); },
    "The relative ejection probabilities"
  )
  .def_property_readonly(

    "relative_ejection_probabilities",
    [] ( const Block& self ) -> DoubleRange
       { return self.relativeEjectionProbabilities(); },
    "The relative ejection probabilities"
  )
  .def_property_readonly(

    "Y",
    [] ( const Block& self ) -> DoubleRange
       { return self.Y(); },
    "The yields"
  )
  .def_property_readonly(

    "yields",
    [] ( const Block& self ) -> DoubleRange
       { return self.yields(); },
    "The yields"
  )
  .def_property_readonly(

    "F",
    [] ( const Block& self ) -> DoubleRange
       { return self.Y(); },
    "The fluorescent energies"
  )
  .def_property_readonly(

    "fluorescent_energies",
    [] ( const Block& self ) -> DoubleRange
       { return self.fluorescentEnergies(); },
    "The fluorescent energies"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
