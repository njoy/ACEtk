#ifndef NJOY_ACETK_PYTHON_DEFINITIONS
#define NJOY_ACETK_PYTHON_DEFINITIONS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ACEtk/fromFile.hpp"
#include "ACEtk/block/DistributionProbability.hpp"
#include "views.hpp"

namespace python = pybind11;

/**
 *  @brief Add standard ACE table definitions
 *
 *  This adds the following standard properties:
 *    header, data, from_file, from_concatenated_file, to_file, xss_array
 *
 *  @param[in] table   the table to which the definitions have to be added
 */
template < typename Table, typename PythonClass >
void addStandardTableDefinitions( PythonClass& table ) {

  table
  .def_property_readonly(

    "header",
    [] ( const Table& self ) { return self.header(); },
    "The header information"
  )
  .def_property_readonly(

    "data",
    [] ( const Table& self ) { return self.data(); },
    "The data arrays"
  )
  .def_static(

    "from_file",
    [] ( const std::string& filename ) -> Table {

      return Table( njoy::ACEtk::fromFile( filename ) );
    },
    "Read an ACE table from a file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "table\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  )
  .def_static(

    "from_concatenated_file",
    [] ( const std::string& filename ) -> std::vector< Table > {

      std::vector< Table > tables;
      auto content = njoy::ACEtk::fromConcatenatedFile( filename );
      for ( auto&& table : content ) {

        tables.emplace_back( std::move( table ) );
      }
      return tables;
    },
    "Read ACE tables from a concatenated file\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "table\n\n"
    "Arguments:\n"
    "    filename    the file name and path"
  )
  .def(

    "to_file",
    [] ( const Table& self, const std::string& filename ) {

      std::ofstream out( filename );
      self.print( out );
      out.close();
    },
    "Write the ACE table to a file\n\n"
    "Arguments:\n"
    "    self        the table\n"
    "    filename    the file name and path"
  );
}

/**
 *  @brief Add standard block definitions
 *
 *  This adds the following standard properties:
 *    name, length, empty, xss_array, xss
 *
 *  @param[in] block   the block to which the definitions have to be added
 */
template < typename Block, typename PythonClass >
void addStandardBlockDefinitions( PythonClass& block ) {

  block
  .def_property_readonly(

    "name",
    [] ( const Block& self ) { return self.name(); },
    "The name of the block"
  )
  .def_property_readonly(

    "length",
    [] ( const Block& self ) { return self.length(); },
    "The length of the the xss array of the block"
  )
  .def_property_readonly(

    "empty",
    [] ( const Block& self ) { return self.empty(); },
    "Whether or not the block is empty"
  )
  .def_property_readonly(

    "xss_array",
    [] ( const Block& self ) -> DoubleRange
       { return self.XSS(); },
    "The xss array of the block"
  )
  .def(

    "xss",
    [] ( const Block& self, std::size_t index )
       { return self.XSS( index ); },
    python::arg( "index" ),
    "Return a value from the xss array of the block\n\n"
    "Arguments:\n"
    "    self     the data block\n"
    "    index    the index (one-based)"
  )
  .def(

    "xss",
    [] ( const Block& self, std::size_t index, std::size_t length ) -> DoubleRange
       { return self.XSS( index, length ); },
    python::arg( "index" ), python::arg( "length" ),
    "Return a subrange of a given length from the xss array of the block\n\n"
    "Arguments:\n"
    "    self      the data block\n"
    "    index     the index (one-based)\n"
    "    length    the length of the subrange"
  );
}

/**
 *  @brief Add standard ACE table definitions
 *
 *  This adds the following standard properties:
 *    header, data, from_file, from_concatenated_file, to_file, xss_array
 *
 *  @param[in] table   the table to which the definitions have to be added
 */
template < typename MultiDistribution, typename Distribution, typename PythonClass >
void addStandardMultiDistributionDefinitions( PythonClass& block ) {

  using DistributionProbability = njoy::ACEtk::block::DistributionProbability;

  block
  .def(

    python::init< std::vector< DistributionProbability >,
                  std::vector< Distribution >,
                  std::size_t >(),
    python::arg( "probabilities" ), python::arg( "distributions" ),
    python::arg( "locb" ) = 1,
    "Initialise the block\n\n"
    "Arguments:\n"
    "    self             the block\n"
    "    probabilities    the probabilities\n"
    "    distributions    the distributions\n"
    "    locb             the starting xss index with respect to the superblock\n"
    "                     (default = 1, the relative locators get recalculated)"
  )
  .def_property_readonly(

    "LAW",
    [] ( const MultiDistribution& self ) { return self.LAW(); },
    "The distribution type"
  )
  .def_property_readonly(

    "type",
    [] ( const MultiDistribution& self ) { return self.type(); },
    "The distribution type"
  )
  .def_property_readonly(

    "number_distributions",
    [] ( const MultiDistribution& self ) { return self.numberDistributions(); },
    "The number of distributions"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const MultiDistribution& self ) { return self.probabilities(); },
    "The probability data for each distribution"
  )
  .def(

    "probability",
    [] ( const MultiDistribution& self, std::size_t index )
       { return self.probability( index ); },
    python::arg( "index" ),
    "Return the probability data for a distribution index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  )
  .def_property_readonly(

    "distributions",
    [] ( const MultiDistribution& self ) { return self.distributions(); },
    "The distribution data for each distribution"
  )
  .def(

    "distribution",
    [] ( const MultiDistribution& self, std::size_t index )
       { return self.distribution( index ); },
    python::arg( "index" ),
    "Return the distribution data for a distribution index\n\n"
    "When the index is out of range an out of range exception is thrown\n"
    "(debug mode only).\n\n"
    "    self     the block\n"
    "    index    the index (one-based)"
  );
}

#endif
