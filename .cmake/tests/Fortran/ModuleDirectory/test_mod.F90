module test_mod
  implicit none

contains

  function foo()
    implicit none
    integer :: foo

    foo = 0
    return
  end function foo
end module
