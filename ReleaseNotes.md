# Release Notes&mdash;ACEtk
Given here are some release notes for ACEtk.

## [ACEtk v1.0.2](https://github.com/njoy/ENDFtk/pull/xxx)
This fixes the following issues in ACEtk:
  - The electron subshell populations are now returned as floating point values instead of
    integer values.
  - An UndefinedDistribution has been introduced to handle cases where locators in the energy
    distribution block for secondary particles are set to 0 (meaning no data is given).

## [ACEtk v1.0.1](https://github.com/njoy/ENDFtk/pull/133)
This updates the build system for ACEtk and contains no functional changes.

## [ACEtk v1.0.0](https://github.com/njoy/ENDFtk/pull/130)
This represents the first proper release of ACEtk.

The following ACE file types are supported in this version:
  - continuous energy neutron and incident charged particles files
  - photonuclear files
  - thermal scattering files
  - photoatomic and electron files (eprdata-style files)
  - dosimetry files
