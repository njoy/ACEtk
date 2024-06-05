int main(){

#ifdef F90_REAL_4BYTE
  int value = 4;
#endif

#ifdef F90_REAL_8BYTE
  int value = 8;
#endif
  
  return EXPECTED == value ? 0 : 1;
}
