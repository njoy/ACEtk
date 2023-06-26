/**
 *  @class
 *  @brief The header information in an ACE file
 *
 *  There are multiple version of the header. This is the original header
 *  used by NJOY.
 *
 *  The header contains the following information, fixed column format:
 *    - line 1: ZAID (10 characters), AW (atomic mass ratio, 12 characters),
 *              TZ (temperature in MeV, 12 characters), blank space,
 *              date (10 characters)
 *    - line 2: description (70 characters), material identifier (10 characters)
 */
class Header {

  /* fields */
  std::string vers_;
  std::string zaid_;
  double temp_;
  double awr_;
  std::string date_;
  std::string title_;
  std::string material_;

  /* auxiliary functions */
  #include "ACEtk/Table/Header/src/strip.hpp"
  #include "ACEtk/Table/Header/src/parse.hpp"

public:

  #include "ACEtk/Table/Header/src/ctor.hpp"

  /**
   *  @brief Return the header version
   */
  const std::string& VERS() const { return this->vers_; }

  /**
   *  @brief Return the header version
   */
  const std::string& version() const { return this->vers_; }

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const { return this->zaid_; }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const { return this->awr_; }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->AWR(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const { return this->temp_; }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->TEMP(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const { return this->date_; }

  /**
   *  @brief Return the title string
   */
  const std::string& title() const { return this->title_; }

  /**
   *  @brief Return the material string
   */
  const std::string& material() const { return this->material_; }

  #include "ACEtk/Table/Header/src/print.hpp"
};
