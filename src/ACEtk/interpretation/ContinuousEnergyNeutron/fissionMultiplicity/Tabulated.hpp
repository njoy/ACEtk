class Tabulated : protected ENDFtk::TabulationRecord {
public:
  using TabulationRecord::TabulationRecord;

  auto energies() const{
    return scaleBy( 1.0*mega( electronVolts ) )( this->x() );
  }

  auto multiplicities() const{ return this->y(); }
};
