subroutine quit_program
  implicit none
#ifndef DO_F_PRE_PRO
  error stop 1
#else
  stop
#endif
end subroutine
