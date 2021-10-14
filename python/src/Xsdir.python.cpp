// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <fstream>

// local includes
#include "ACEtk/Xsdir.hpp"

// namespace aliases
namespace python = pybind11;

void wrapXsdir( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ACEtk::Xsdir;
  using XsdirEntry = njoy::ACEtk::XsdirEntry;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Xsdir",
    "An xsdir file\n\n"
    "An xsdir file consists of the following:\n"
    "  - an optional data path\n"
    "  - a set of atomic weight values\n"
    "  - a set of xsdir entries\n"
  );

  // wrap the component
  component
  .def(

    python::init< std::map< unsigned int, double >,
           std::vector< XsdirEntry >,
           std::optional< std::string > >(),
    python::arg( "ratios" ), python::arg( "entries" ),
    python::arg( "datapath" ) = std::nullopt,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the xsdir\n"
    "    ratios     the atomic weight ratios\n"
    "    entries    the file name\n"
    "    datapath   the optional datapath"
  )
  .def_property_readonly(

    "data_path",
    &Component::dataPath,
    "The optional datapath"
  )
  .def_property_readonly(

    "atomic_weight_ratios",
    &Component::atomicWeightRatios,
    "The atomic weight ratios"
  )
  .def(

    "atomic_weight_ratio",
    &Component::atomicWeightRatio,
    python::arg( "za" ),
    "The atomic weight ratio for a given za"
  )
  .def_property_readonly(

    "entries",
    &Component::entries,
    "The xsdir entries"
  )
  .def(

    "entry",
    &Component::entry,
    python::arg( "zaid" ),
    "The xsdir entry for a given ZAID"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string ) -> Component {

      std::istringstream in( string );
      return Component( in );
    },
    python::arg( "string" ),
    "Read the xsdir from a string\n\n"
    "An exception is raised if something goes wrong while reading the xsdir\n\n"
    "Arguments:\n"
    "    string    the string representing the xsdir"
  )
  .def(

    "to_string",
    [] ( const Component& self ) {

      std::ostringstream out;
      self.print( out );
      return out.str();
    },
    "Return the string representation of the xsdir"
  )

  .def_static(

    "from_file",
    &Component::fromFile,
    "Read an xsdir from a file\n\n"
    "An exception is raised if something goes wrong while reading the xsdir\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  )
  .def(

    "to_file",
    [] ( const Component& self, const std::string& filename ) {

      std::ofstream out( filename );
      self.print( out );
      out.close();
    },
    "Write the xsdir to a file\n\n"
    "Arguments:\n"
    "    self        the xsdir\n"
    "    filename    the file name and path"
  );
}
