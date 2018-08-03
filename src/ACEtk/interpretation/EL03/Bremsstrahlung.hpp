class Bremsstrahlung {
  const Table& table;

public:
  Bremsstrahlung( const Table& table ) : table( table ) {}
  
  #include "ACEtk/interpretation/EL03/Bremsstrahlung/ProductionCrossSection.hpp"
  
  auto productionCrossSection() const {
    return ProductionCrossSection{ this->table };
  }

  #include "ACEtk/interpretation/EL03/Bremsstrahlung/OutgoingDistributions.hpp"  

  auto outgoingDistributions() const {
    return OutgoingDistributions{ this->table };
  }
  
};
