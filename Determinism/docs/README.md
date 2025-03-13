# Determinism Modules

These modules provide support for deterministic VMF runs and determinism validation.

The following unifuzz SUTs have been found to run well deterministically:
- exiv2
- jhead
- mp3gain
- pdftotext
- imginfo

To run deterministically, you will also need to configure VMF with a fixed seed.  In your SUT-specific configuration file:
```yaml
vmfFramework:
   seed: 12345 #Or your favorite number, it just matters that that seed is set to something
```

Then combine your SUT-specific configuration with the included `defaultModulesDeterministic.yaml`.

## Build and installation directions

To build and install the modules into your vmf_install directory:
```
mkdir build
cd build
cmake -DVMF_INSTALL=<root of the VMF install> ..
make install
```

## DeterministicTesterOutput

This is an output module that computes a running checksum of all generated testcase contents and IDs. It prints out the checksum every 10 testcases, enabling a user to compare two runs for determinism validation.

## AFLDeterministicFeedback

This is a feedback module that can be used in a deterministic configuration. It removes testcase execution time from fitness. It also ignores hangs, which alleviates, but not does not remove, determinism issues that arise from hangs.