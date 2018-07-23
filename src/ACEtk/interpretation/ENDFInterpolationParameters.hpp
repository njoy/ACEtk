class ENDFInterpolationParameters {
  Table::Slice NBT_;
  Table::Slice schemes_;

public:
#include "ACEtk/interpretation/ENDFInterpolationParameters/src/ctor.hpp"

  auto NBT() const { return NBT_; }
  auto schemes() const { return schemes_; }
  auto size() const { return NBT_.size(); }

#include "ACEtk/interpretation/ENDFInterpolationParameters/src/range.hpp"
};