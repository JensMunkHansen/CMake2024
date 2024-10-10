# VTK - extension to the VTK infrastructure

Introduction
================

x os.add_dll_directory (for python to work)
x make VTK work with python (just release mode)
x put sitecustomize.py into VIRTUAL_ENV/Lib/site-packages

x Install python
x activate
x build artifactory (shared + python)
x Build SPS
x RegressionTest

Script for listing public/private dependencies
./VTK/Utilities/Maintenance/FindNeededModules.py -j modules.json -s source.cxx

Note on ABI's and export 

Explain how std::vector can be instantiated and exported and still not good

Power of forward declaration (mutual dependencies)


// A.h
#include <memory>

class B;  // Forward declaration of B

class A {
    std::shared_ptr<B> bPtr;  // Use of forward-declared B
};

// B.h
#include <memory>

class A;  // Forward declaration of A

class B {
    std::shared_ptr<A> aPtr;  // Use of forward-declared A
};


TODO: Write an introduction

* [Doc](./Doc) Documentation with developer guidelines




