# VMF experimental modules

## Overview

This repository is a collection of VMF module packages (sets of related modules) and associated tools.
Top-level directories are individual packages. Each package contains source code for one or more VMF
modules along with associated data, tests, and documentation.

Within each package we suggest using the same directory hierarchy as is used in the main 
VaderModularFuzzer repository:
* All source code is under `vmf/src/modules/`
* Next-level directory identifies the platform(s) the modules will run on (linux, windows, common, etc.)
* Lowest-level directory identifies the specific module type

```
/
|-- SamplePackage
    |-- data
    |-- docs
    |-- test
    |-- vmf/src/modules/common
	    |-- mutator
```

## Building and installing experimental module packages

VMF is built using CMake

Building the Experimental repository also requires an installed instance of VMF. It must be installed in the default location within a VMF source tree, like
`/home/userdir/VaderModularFuzzer/build/vmf_install`. Specify the full path to the VMF install using
`-DCMAKE_INSTALL_PREFIX=/path/to/VMF`.

### Linux

Execute the following commands to build the VMF experimental modules:

```bash
# from the top VmfExperimental directory:
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<path to VMF install> .. && make
```

### Windows

Run the Developer Command Prompt for Visual Studio (e.g. "Developer Command Prompt VS 2022"), and
navigate to the VMF directory.  Then execute the following commands to generation a solution file
for VMF.  The exact version of visual studio must be specified in the final command -- here we
specify Visual Studio 2022 Version 17.x.  Use `cmake --help` to see additional generation options.

*Note: The -DCMAKE_INSTALL_PREFIX may be used to optionally specify an install location other than
the default VMF in-tree install location (build\vmf_install).*

```powershell
#from \path\to\vmf directory
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
#Or optionally use this version instead to specify an install path
#cmake -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX=<your install path here> ..
cmake --build . --target INSTALL --config Release
```
You may alternatively open the VmfExtension.sln file that has been generated in the build directory 
and build the INSTALL target in the GUI.

### Installing experimental modules

The VMF experimental modules library must be installed in a VMF plugins directory, either the default
directory `<VMF install location>/plugins/` or another directory specified using the 
`vmfFramework.additionalPluginsDir` configuration parameter.

To install the VMF extension libary, do this in the build directory:
```bash
make install
```

## License
All experimental modules must be license-compatible with VMF itself, which is licensed under the GNU General Public License Version 2.


## Unit Tests

VMF uses the Google Test framework for unit testing. A basic overview of the framework as well as example unit test are available here: [Primer](http://google.github.io/googletest/primer.html).

### Running the Unit Tests
To run the existing unit tests, use the following commands
```bash
cd build
ctest
```

For additional output on any failed tests
```bash
ctest --output-on-failure
```

For additional output on all of the tests
```bash
ctest --VV
```

To build and run
```bash
cmake -DVMF_INSTALL=<path to VMF install> .. && make -j8 && ctest
```

### Running the Unit Tests (Docker)
From the VmfExperimental Directory on the HOS, run the following command via Bash / Powershell 7+
```powershell
docker build -t vmfexp -f ./dockerfiles/Dockerfile . && docker run --rm vmfexp
```
