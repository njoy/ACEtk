/**
 *  @class
 *  @brief The header information in an ACE file
 *
 *  There are multiple version of the header.
 *
 *  The normal header contains the following information, fixed column format:
 *    - line 1: ZAID (10 characters), AW (atomic mass ratio, 12 characters),
 *              TZ (temperature in MeV, 12 characters), blank space,
 *              date (10 characters)
 *    - line 2: description (70 characters), material identifier (10 characters)
 *
 *  The 2.0.0 header contains the following information, in free format:
 *    - line 1: VERS (header version), SZAID, SRC (evaluation source)
 *    - line 2: AW (atomic mass ratio), TZ (temperature in MeV), date,
 *              N (comments)
 *    - line 3 to N+2: comment lines (the last two lines are always the normal
 *                     header)
 *
 *  The 2.0.1 header contains the following information, fixed column format:
 *    - line 1: VERS (header version, 10 characters), blank space,
 *              SZAID (24 characters), blank space,
 *              SRC (evaluation source, 24 characters)
 *    - line 2: AW (atomic mass ratio, 12 characters), blank space,
 *              TZ (temperature in MeV, 12 characters), blank space,
 *              date (10 characters), blank space, N (number of comment lines,
 *              4 characters)
 *    - line 3 to N+2: comment lines (the last two lines are always the normal
 *                     header)
 */
class Header {

  /* fields */
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
   *  @brief Return the titla string
   */
  const std::string& title() const { return this->title_; }

  /**
   *  @brief Return the material string
   */
  const std::string& material() const { return this->material_; }

  #include "ACEtk/Table/Header/src/print.hpp"
};
