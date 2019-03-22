static bool outOfBounds(TempT value, TempT min_, TempT max_) {
  return not (min_ < value  && value < max_);
}

static bool outOfBounds(DenT value, DenT min_, DenT max_) {
  return not (min_ < value  && value < max_);
}  

