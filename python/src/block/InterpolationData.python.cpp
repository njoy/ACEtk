// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ACEtk/continuous/InterpolationData.hpp"
#include "views.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace block {

void wrapInterpolationData( python::module& module, python::module& ) {

  // type aliases
  using Block = njoy::ACEtk::block::InterpolationData;

  // wrap views created by this block

  // create the block
  python::class_< Block > block(

    module,
    "InterpolationData",
    "Convenience interface for interpolation data"
  );

  // wrap the block
  block
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

    "is_linear_linear",
    &Block::isLinearLinear,
    "Flag to indicate whether or not the data is fully linear-linear"
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
    "The interpolation type for each range"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Block& self ) -> LongRange
       { return self.interpolants(); },
    "The interpolation type for each range"
  );

  // add standard block definitions
  addStandardBlockDefinitions< Block >( block );
}

} // block namespace
