# Release Notes&mdash;ACEtk
Given here are some release notes for ACEtk.

## ACEtk v1.0.3
A few updates were made in the CMake files for Windows compilation issues.

The GitHub CI was also updated: macos-14 (arm64 architecture) was added in addition to macos-13 (intel architecture).

The version of the tools dependency and the pybind11 deoendency was upped to the latest release (no functionality changes result from these dependency changes).

Valgrind testing was added to the GitHub CI to detect memory issues in the future.

## [ACEtk v1.0.2](https://github.com/njoy/ACEtk/pull/137)
This fixes the following issues in ACEtk:
  - The electron subshell populations are now returned as floating point values instead of
    integer values.
  - An UndefinedDistribution has been introduced to handle cases where locators in the energy
    distribution block for secondary particles are set to 0 (meaning no data is given). With
    earlier versions of ACEtk, this would have lead to a crash because the XSS array was being
    interpreted incorrectly.
  - Potential memory leaks have been eliminated when using placement new in copy and move
    assignments. Unit tests now have specific tests for copy and move constructors and copy and
    move assignment.

Python stubs have been added, which should improve Python auto-completion in IDEs.

This update also modifies the build system to use shacl-cmake.

## [ACEtk v1.0.1](https://github.com/njoy/ACEtk/pull/133)
This updates the build system for ACEtk and contains no functional changes.

## [ACEtk v1.0.0](https://github.com/njoy/ACEtk/pull/130)
This represents the first proper release of ACEtk.

The following ACE file types are supported in this version:
  - continuous energy neutron and incident charged particles files
  - photonuclear files
  - thermal scattering files
  - photoatomic and electron files (eprdata-style files)
  - dosimetry files
