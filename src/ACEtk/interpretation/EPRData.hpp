class EPRData {
  Table table;

protected:
  static int Z( const Table& table ) { return table.data.NXS( 2 ); }
  
public:
  EPRData( Table&& table ) : table( std::move(table) ) {}

  #include "ACEtk/interpretation/EPRData/ESZG.hpp"
  
  auto eszg() const {
    return ESZG{ this->table };
  }

  #include "ACEtk/interpretation/EPRData/IncoherentPhotonData.hpp"
  
  auto incoherentPhotonData() const {
    return IncoherentPhotonData( this->table );
  }

  #include "ACEtk/interpretation/EPRData/CoherentPhotonData.hpp"
  
  auto coherentPhotonData() const {
    return CoherentPhotonData( this->table );
  }

  #include "ACEtk/interpretation/EPRData/ShellData.hpp"
  
  auto shellData() const {
    return ShellData( this->table );
  }
  
};
