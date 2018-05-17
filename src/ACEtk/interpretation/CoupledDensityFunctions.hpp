class CoupledDensityFunctions {
  Table::Slice PDF_;
  Table::Slice CDF_;

public:
#include "ACEtk/interpretation/CoupledDensityFunctions/src/ctor.hpp"

  auto PDF() const { return PDF_; }
  auto CDF() const { return CDF_; }
  auto size() const { return PDF_.size(); }
};
