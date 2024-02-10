CMake configuration
========================

Template for a library, where targets can be configured in multiple
scopes. This is conventient for larger projects.

Third-party libraries
---------------------

We do not have an artifactory and do not want to create a `CMake`
superbuild. For now, we make a pre-build scripts, which fetches and
builds third-party dependencies. In this way, we do not pollute this
project and can pull-in dependencies using the `find_package` from
`CMake`.

Testing
-------
For testing, we use `Catch2`.

TODO
----

### COMPONENTS
They are set but only relevant for libraries using us and installation

### NAMESPACES
CMake namespaces. Do we want them?
