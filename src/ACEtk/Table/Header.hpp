class Header {
public:
  #include "ACEtk/Table/Header/String.hpp"

  /* convenience typedefs */
  using Comment = String<70>;
  using SZAID = String<24, true>;
  
  /* fields */
  year_month_day                  processDate;
  Quantity< Mega<ElectronVolts> > processTemperature;
  double                          atomicWeightRatio;
  SZAID                           szaid;
  std::vector< Comment >          comments;

protected:
  using MAT = String<10, true>;
  using Source = String<24>;

  template< int... values >
  using Version = std::integer_sequence< int, values... > ;
  
  std::optional< MAT > mat;
  std::optional< Source > source;

public:
  Header( year_month_day processDate,
          Quantity< Mega<ElectronVolts> > processTemperature,
          double atomicWeightRatio,
          SZAID&& szaid,
          std::vector< Comment >&& comments ) :
    processDate( processDate ),
    processTemperature( processTemperature ),
    atomicWeightRatio( atomicWeightRatio ),
    szaid( std::move(szaid) ),
    comments( std::move(comments) ){}
  
  /* static methods */  
  #include "ACEtk/Table/Header/src/parse.hpp"
  #include "ACEtk/Table/Header/src/print.hpp"

  #include "ACEtk/Table/Header/Builder.hpp"
};
