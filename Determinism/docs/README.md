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

Then combine your SUT-specific configuration with the included `test/config/defaultModules_determinism.yaml`.

## DeterministicTesterOutput

This is an output module that computes a running checksum of all generated testcase contents and IDs. It prints out the checksum every 10 testcases, enabling a user to compare two runs for determinism validation.

This module has no configuration parameters.

## AFLDeterministicFeedback

This is a feedback module that can be used in a deterministic configuration. It is similar to core module AFLFeedback except that it removes testcase execution time from the fitness function calculation. It also ignores hangs, which alleviates, but not does not remove, determinism issues that arise from hangs.

This module has the following configuration parameters.

## `AFLDeterministicFeedback`

Configuration information specific to the AFLDeterministicFeedback module. This module is similar to AFLFeedback except that it only uses code coverage and test case size to compute fitness; execution speed is omitted. This module supports adjusting the relative weights of the components used to compute the fitness of each test case. Because test cases are sorted in storage by their fitness, and the Input Generator modules provided with VMF use a weighted random selection that favors more fit test cases, changing the fitness computation changes which test cases are selected for mutation.

### `AFLFeedback.useCustomWeights`

Value type: `<boolean>`

Status: Optional

Default value: false

Usage: Enables the use of custom weighting factors in the AFL feedback algorithm.

### `AFLFeedback.sizeWeight`

Value type: `<float>`

Status: Optional

Default value: 1.0

Usage: Provides a relative weighting factor for the normalized size of the test case. Value should be in the range of 0.0 - 10.0. A value of 0.0 will remove this factor from the weighting algorithm.

