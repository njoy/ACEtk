![Continuous Integration](https://github.com/njoy/ACEtk/workflows/Continuous%20Integration/badge.svg)

# ACEtk
Toolkit for reading and interacting with ACE nuclear data files. This toolkit provides a full C++ library along with python bindings.

## Release and development versions
For the latest version of ACEtk and an overview of the latest changes, please see the [Release Notes](ReleaseNotes.md) or the [release](https://github.com/njoy/ACEtk/releases) page.

The latest release version of ACEtk can always be found at the head of the [main](https://github.com/njoy/ACEtk) branch of this repository and every release is associated to a release tag. New versions are released on a regular basis (we aim to provide updates at least every three months). The latest development version of ACEtk containing the latest updates and changes can be found in at the head of the [develop](https://github.com/njoy/ACEtk/tree/develop) branch. This development version should be used with caution.

## ACEtk in python

### Required NJOY libraries

The ACEtk python bindings require the python bindings of the [tools](https://github.com/njoy/tools) library (more specifically version v0.3.0).

### Installing ACEtk for python

First of all, a user should clone the ACEtk repository and build the python bindings:
```
git clone https://github.com/njoy/ACEtk
cd ACEtk
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make -j8
```

The compilation will produce a number of dynamic libraries linked to the python libraries on the user's computer (these will be named something like `< component >.cpython-37m-darwin.so` with `< component >` the name of the component). The names of these dynamic libraries will also indicate which version of the python libraries they are linked against. This is important since you will need to use the associated python version along with them.

ACEtk in python requires python 3.x so you will need to have at least one python 3.x installed. When multiple python versions are installed, it may be beneficial to include ```-DPYTHON_EXECUTABLE=$(which python3)``` in the cmake configuration step so that the default python3 version will be picked.

In order to use the ACEtk python package, the user should make sure that the library is within the python path. This can be done in multiple ways. You can set that up by adding the ACEtk build path to the python path `$PYTHONPATH` environmental variable on your machine, or by using the following in your python code:
```
import sys
sys.path.append( < ACEtk-build-path > )
```
where `< ACEtk-build-path >` is the path to the ACEtk python dynamic library.

#### Troubleshooting ####

##### c++: Permission denied #####

On MacOS, an error may occur when using `make -j8` telling the user that there is no permission to execute the compiler (the error message will contain the full path to the compiler executable). This error is related to an issue with the MacOS system default make installation not allowing parallel compilation (the `-j8` part of the make command). Executing `make` without a parallel option will function, but the user should consider installing a different version of make (e.g. using homebrew) to get around this.

##### CMake doesn’t detect the right Python version #####

Taken from the pybind11 FAQ.

The CMake-based build system will try to automatically detect the installed version of Python and link against that. When this fails, or when there are multiple versions of Python and it finds the wrong one, delete CMakeCache.txt and then add -DPYTHON_EXECUTABLE=$(which python) to your CMake configure line. (Replace $(which python) with a path to python if your prefer.)

A version of python 3.x is preferred.

##### ImportError cannot import name <sysconfig> #####

This error sometimes comes up when running the cmake command. This appears to be related to an incomplete/corrupted python installation. It can be rectified by installing the distutils package for the python version that is being used. On a linux system, the following command should install the distutils package:
```
sudo apt install python3-distutils
```

##### ImportError `GLIBCXX_3.4.30' not found

A problem may occur if a user's installed python environment is through conda. The user will be able to build properly but all of the unit tests for python may fail due to GLIBCXX_3.4.30 being missing. This seems to be an a problem with conda not having GLIBCXX_3.4.30 in the path. If the user is able to compile ENDFtk, they have GLIBCXX_3.4.30. At which point, a symlink will need to be created to point the conda enviroment to where GLIBCXX_3.4.30 is installed.


##### cannot find python.h #####

When compiling the python bindings, this error indicates that the python header files and static library we need to link to are not installed on your system. This appears to be related to an incomplete python installation. It can be rectified by installing the python3-dev package (when using python 3). On a linux system, the following command should install the header files:
```
sudo apt install python3-dev
```

### A minimal user guide:

Opening up a continuous energy ACE file (incident neutron or incident charged particle file):
```
import ACEtk
table = ACEtk.ContinuousEnergyTable.from_file( '1001.00c' )
```

An `ACEtk.ContinuousEnergyTable` reads the ACE nuclear data file and interprets it as a continuous energy table for incident neutrons or incident charged particles. A more generic `ACEtk.Table` is available for reading any ACE file but this generic table does not provide any abstraction or interpretation option other than accessing the underlying IZ, AW, NXS, JXS and XSS arrays. The specialised `ACEtk.ContinuousEnergyTable` will index the data available in the ACE file and make the information available through a more abstracted interface.

Once the data is read in, a user can retrieve information from the IZ, AW, NXS, JXS and XSS arrays directly (both for the generic `ACEtk.Table` and the specialised `ACEtk.ContinuousEnergyTable`):
```
xss = table.data.xss_array    # the entire xss array
element = table.data.xss(1)   # the first element of the xss array, the index is one-based
slice = table.data.xss(1, 20) # a slice containing the first 20 elements of the xss array
```

Every component in ACEtk has python documentation associated to it that can be viewed using the `help(...)` function in python:
```
help( table )     # this will display the help for an continuous energy ACE table
help( table.esz ) # this will display the help for the ESZ block in the ACE table
```

ACEtk uses a concept called ranges (aka sequences) so as a result, anything coming out as a range will be a custom type. These custom range types allow subscripting and iteration like any other sequence or list. To convert such a range into a proper list, you can use the `to_list()` method or slicing. This will do a deep copy of primitive types (int, doubles, etc.). It will not do a deep copy for custom types like sections or underlying components. To deep copy a range of custom types, a user can use the `copy()` method on the range.

## LICENSE
The software contained in this repository is covered under the associated [LICENSE](LICENSE) file.
