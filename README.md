![Continuous Integration](https://github.com/njoy/ACEtk/workflows/Continuous%20Integration/badge.svg)

# ACEtk

Toolkit for reading and interacting with ACE nuclear data files. This toolkit provides a full C++ library along with python bindings.

## ACEtk in python

The python bindings for ACEtk are still work in progress and should be used accordingly. Please report any issues encountered while using the python bindings using the issue tracker on this repository.

### Installing ACEtk for python

First of all, a user should clone the ACEtk repository and build the python bindings:
```
git clone https://github.com/njoy/ACEtk
cd ACEtk
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make ACEtk.python -j8
```

ACEtk in python requires python 3.x so you will need to have at least one python 3.x installed. When multiple python versions are installed, it may be beneficial to include ```-DPYTHON_EXECUTABLE=$(which python3)``` in the cmake configuration step so that the default python3 version will be picked. The compilation will produce a dynamic library linked to the python libraries on the user's computer (it'll be named something like `ACEtk.cpython-37m-darwin.so`). This name will also indicate which version of the python libraries this library is linked to. This is important since you will need to use the associated python version with the ACEtk python package.

In order to use the ACEtk python package, the user should make sure that the library is within the python path. This can be done in multiple ways. You can set that up by adding the ACEtk build path to the python path `$PYTHONPATH` environmental variable on your machine, or by using the following in your python code:
```
import sys
sys.path.append( < ACEtk-build-path > )
```
where `< ACEtk-build-path >` is the path to the ACEtk python dynamic library.

When running python in the build directory directly, none of these steps are required.

#### Troubleshooting ####

##### CMake doesn’t detect the right Python version #####

Taken from the pybind11 FAQ.

The CMake-based build system will try to automatically detect the installed version of Python and link against that. When this fails, or when there are multiple versions of Python and it finds the wrong one, delete CMakeCache.txt and then add -DPYTHON_EXECUTABLE=$(which python) to your CMake configure line. (Replace $(which python) with a path to python if your prefer.)

A version of python 3.x is preferred.

##### importError cannot import name <sysconfig> #####

This error sometimes comes up when running the cmake command. This appears to be related to an incomplete/corrupted python installation. It can be rectified by installing the distutils package for the python version that is being used. On a linux system, the following command should install the distutils package:
```
sudo apt install python3-distutils
```

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
