# VTK - extension to the VTK infrastructure

Introduction
================

1. You need os.add_dll_directory (build tree)
2. VTK works with python release
3. TODO: Make my code use release of python

Put sitecustomize.py into VIRTUAL_ENV\Lib\site-packages\

TODO: Write an introduction

* [Doc](./Doc) Documentation with developer guidelines

Install python, activate, build artifactory (shared + python)
Build SPS, VTK_DIR=artifactory
RegressionTest

./VTK/Utilities/Maintenance/FindNeededModules.py -j modules.json -s source.cxx


class MyClass;  // Forward declaration of MyClass

#ifdef BUILDING_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

DLL_EXPORT std::shared_ptr<MyClass> mySharedPtr;


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
