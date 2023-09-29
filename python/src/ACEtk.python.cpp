// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - generic ACE table
void wrapHeader( python::module&, python::module& );
void wrapHeader201( python::module&, python::module& );
void wrapData( python::module&, python::module& );
void wrapTable( python::module&, python::module& );

// declarations - xsdir components
void wrapXsdirEntry( python::module&, python::module& );
void wrapXsdir( python::module&, python::module& );

// declarations - enumerators
void wrapReferenceFrame( python::module&, python::module& );
void wrapAngularDistributionType( python::module&, python::module& );
void wrapEnergyDistributionType( python::module&, python::module& );

// declarations - block and component subpackages
void wrapContinuous( python::module&, python::module& );
void wrapPhotoatomic( python::module&, python::module& );
void wrapPhotonuclear( python::module&, python::module& );
void wrapDosimetry( python::module&, python::module& );
void wrapElectron( python::module&, python::module& );
void wrapThermal( python::module&, python::module& );

// declarations - ACE table types
void wrapContinuousEnergyTable( python::module&, python::module& );
void wrapDosimetryTable( python::module&, python::module& );
void wrapThermalScatteringTable( python::module&, python::module& );
void wrapPhotoatomicTable( python::module&, python::module& );
void wrapPhotonuclearTable( python::module&, python::module& );

/**
 *  @brief ACEtk python bindings
 *
 *  The name given here (ACEtk) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( ACEtk, module ) {

  // create the views submodule
  python::module viewmodule = module.def_submodule(

    "sequence",
    "sequence - ACE sequences (internal use only)"
  );

  // wrap some basic recurring views
  // none of these are supposed to be created directly by the user
  wrapBasicRandomAccessAnyViewOf< double >(
      viewmodule,
      "any_view< double, random_access >" );
  wrapBasicRandomAccessAnyViewOf< unsigned int >(
      viewmodule,
      "any_view< unsigned int, random_access >" );
  wrapBasicRandomAccessAnyViewOf< long >(
      viewmodule,
      "any_view< long, random_access >" );

  // wrap enumerators
  wrapReferenceFrame( module, viewmodule );
  wrapAngularDistributionType( module, viewmodule );
  wrapEnergyDistributionType( module, viewmodule );

  // wrap generic ACE table components
  wrapHeader( module, viewmodule );
  wrapHeader201( module, viewmodule );
  wrapData( module, viewmodule );
  wrapTable( module, viewmodule );

  // wrap xsdir components
  wrapXsdirEntry( module, viewmodule );
  wrapXsdir( module, viewmodule );

  // component and block subpackages
  wrapContinuous( module, viewmodule );
  wrapPhotoatomic( module, viewmodule );
  wrapPhotonuclear( module, viewmodule );
  wrapDosimetry( module, viewmodule );
  wrapElectron( module, viewmodule );
  wrapThermal( module, viewmodule );

  // wrap ACE table types
  wrapContinuousEnergyTable( module, viewmodule );
  wrapDosimetryTable( module, viewmodule );
  wrapThermalScatteringTable( module, viewmodule );
  wrapPhotoatomicTable( module, viewmodule );
  wrapPhotonuclearTable( module, viewmodule );
}
