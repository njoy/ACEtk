program main
  use iso_c_binding
  implicit none

  real :: dummy

#ifdef F90_REAL_4BYTE
  integer, parameter :: expected = 4
#endif

#ifdef F90_REAL_8BYTE
  integer, parameter :: expected = 8
#endif

  if (c_sizeof(dummy) /= expected) then
     write(*,*) "size: ", c_sizeof(dummy), ", expected: ", expected
     stop 1
  endif
end program main
