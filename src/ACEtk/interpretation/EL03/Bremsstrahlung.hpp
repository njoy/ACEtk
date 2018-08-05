class Bremsstrahlung {
  const Table& table;

public:
  Bremsstrahlung( const Table& table ) : table( table ) {}
  
  #include "ACEtk/interpretation/EL03/Bremsstrahlung/src/ProductionCrossSection.hpp"
  
  auto productionCrossSection() const {
    return ProductionCrossSection{ this->table };
  }

  #include "ACEtk/interpretation/EL03/Bremsstrahlung/src/OutgoingDistributions.hpp"  

  auto outgoingDistributions() const {
    return OutgoingDistributions{ this->table };
  }
  
};
