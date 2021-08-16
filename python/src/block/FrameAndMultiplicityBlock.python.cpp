// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/block/FrameAndMultiplicityBlock.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapFrameAndMultiplicityBlock( python::module& module,
                                    python::module& viewmodule ) {

  // type aliases
  using Block = njoy::ACEtk::block::FrameAndMultiplicityBlock;
  using ReferenceFrame = njoy::ACEtk::ReferenceFrame;
  using ReferenceFrameRange = BasicRandomAccessAnyView< ReferenceFrame >;

  // wrap views created by this block
  // none of these are supposed to be created directly by the user
  wrapBasicRandomAccessAnyViewOf< ReferenceFrame >(
      viewmodule,
      "any_view< ReferenceFrame, random_access >" );

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

    python::init< std::vector< ReferenceFrame >&&,
                  std::vector< unsigned int >&& >(),
    python::arg( "frames" ), python::arg( "multiplicities" ),
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self              the block\n"
    "    frames            the reference frames\n"
    "    multiplicities    the multiplicities"
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
    [] ( const Block& self ) -> ReferenceFrameRange
       { return self.referenceFrames(); },
    "The reference frames"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Block& self ) -> UnsignedIntRange
       { return self.multiplicities(); },
    "The reference frames"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
