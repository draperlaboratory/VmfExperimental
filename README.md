# VMF experimental modules

## Overview

This repository is a collection of VMF module packages (sets of related modules) and associated tools.
Top-level directories are individual packages. Each package contains source code for one or more VMF
modules along with associated data, tests, and documentation.

Within each package we suggest the following directory hierarchy for source code:
* Second-level directory identifies the platform(s) the modules will run on (linux, windows, common, etc.)
* Third-level directory identifies the specific module type

```
/
|-- SamplePackage
    |-- data
    |-- docs
    |-- test
    |-- src
        |-- common
	    |-- mutator
	    |-- output
    |-- submodules
```

## Building and installing experimental module packages
VMF is built using CMake

Building the Experimental repository also requires an installed instance of VMF. It may be installed
in a public location like `/usr/local/vmf` or in the default location within a VMF source tree like
`/home/userdir/VaderModularFuzzer/build/vmf_install`. Specify the full path to the VMF install using
`-DVMF_INSTALL=/path/to/VMF`.

Execute the following commands to build the VMF experimental modules:

```bash
# from the top VmfExperimental directory:
mkdir build
cd build
cmake -DVMF_INSTALL=<path to VMF install> .. && make
```

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


