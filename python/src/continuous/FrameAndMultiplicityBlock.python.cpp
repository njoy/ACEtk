// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/FrameAndMultiplicityBlock.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace continuous {

void wrapFrameAndMultiplicityBlock( python::module& module,
                                    python::module& viewmodule ) {

  // type aliases
  using Block = njoy::ACEtk::continuous::FrameAndMultiplicityBlock;
  using ReferenceFrame = njoy::ACEtk::ReferenceFrame;
  using ReferenceFrameRange = BasicRandomAccessAnyView< ReferenceFrame >;

  // create the block
  python::class_< Block > block(

    module,
    "FrameAndMultiplicityBlock",
    "The continuous energy TYR block with the outgoing projectile multiplicities\n"
    "and reference frames\n\n"
    "The FrameAndMultiplicityBlock class contains the reference frame and\n"
    "outgoing projectile multiplicity. The order of this data is the same as\n"
    "the order of the reaction numbers in the MTR block.\n\n"
    "The number of available reactions (excluding elastic) is stored in NXS(4).\n"
  );

  // wrap the block
  block
  .def(

    python::init< std::vector< ReferenceFrame >,
                  std::vector< unsigned int > >(),
    python::arg( "frames" ), python::arg( "multiplicities" ),
    "Initialise the TYR block\n\n"
    "Arguments:\n"
    "    self              the block\n"
    "    frames            the reference frames\n"
    "    multiplicities    the multiplicities"
  )
  .def(

    python::init< std::vector< ReferenceFrame > >(),
    python::arg( "frames" ),
    "Initialise the TYRH block\n\n"
    "Arguments:\n"
    "    self              the block\n"
    "    frames            the reference frames"
  )
  .def_property_readonly(

    "NTR",
    &Block::NTR,
    "The number of available reactions (excluding elastic)"
  )
  .def_property_readonly(

    "number_reactions",
    &Block::numberReactions,
    "The number of available reactions (excluding elastic)"
  )
  .def(

    "reference_frame",
    &Block::referenceFrame,
    python::arg( "index" ),
    "The reference frame for a reaction index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def(

    "multiplicity",
    &Block::multiplicity,
    python::arg( "index" ),
    "The multiplicity for a reaction index\n\n"
    "Arguments:\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "reference_frames",
    &Block::referenceFrames,
    "The reference frames"
  )
  .def_property_readonly(

    "multiplicities",
    &Block::multiplicities,
    "The reference frames"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // continuous namespace
