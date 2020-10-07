# TopoMap
TopoMap is a dimensionality reduction technique which provides topological guarantees during the mapping process. In particular, TopoMap performs the mapping from a high-dimensional space to a visual space, while preserving the 0-dimensional persistence diagram of the Rips filtration of the high-dimensional data, ensuring that the filtrations generate the same connected components when applied to the original as well as projected data. This repo currently implements the geometric approach outlined in the paper:

*Harish Doraiswamy, Julien Tierny, Paulo J. S. Silva, Luis Gustavo Nonato, and Claudio Silva*, [TopoMap: A 0-dimensional Homology Preserving Projection of High-Dimensional Data](https://arxiv.org/abs/2009.01512), *IEEE Transactions on Visualization and Computer Graphics (IEEE SciVis '20), 2020*. 

## Compiling the code
The current version uses the qmake build system. 

### Dependencies
Compiling the code requires
* Boost headers (for computing the convex hull)
* [mlpack](https://www.mlpack.org/) (for computing the EMST)

#### Windows
Boost and mlpack can be installed using [vcpkg](https://github.com/microsoft/vcpkg). 
The qmake pro file assumes that the vcpkg home directory is set in the *VCPKG_HOME* environment variable.

#### Linux 
The default package manager can be used to install the dependencies. Depending on the the distribution, an older version of mlpack might be present which might not support the EMST functionality. In this case, mlpack has to be manually compiled and installed.
The qmake pro file assumes that the libraries are installed in */usr/local/*.

### Compilation using Qt Creator
The easiest way to build will be to import the [TopoMap.pro](https://github.com/harishd10/TopoMap/blob/master/TopoMap.pro) file into Qt Creator. Then build the project as follows:

0. Select whether you want a `Debug` or `Release` build
1. Right Click on Project TopoMap -> `run qmake`
2. Right Click on Project TopoMap -> `build`

### Compilation using command line

#### Windows
The following commands can be used on developer command prompt for visual studio (or alternatively powershell after running `VsDevCmd.bat -arch=amd64 -host_arch=amd64`)

`PS ...\TopoMap> mkdir build`

`PS ...\TopoMap> cd build`

`PS ...\TopoMap\build> qmake.exe ..\TopoMap.pro` 

`PS ...\TopoMap\build> nmake` 

#### Linux 
Using bash, TopoMap can be built using the following commands

`bash:~TopoMap$ mkdir build`

`bash:~TopoMap$ cd build`

`bash:~TopoMap/build$ qmake.exe ../TopoMap.pro` 

`bash:~TopoMap/build$ make` 


### Example Usage
The above build will create a shared library TopoMap.dll / libTopoMap.so that can then be used in an application together with the **[cpp/TopoMap.hpp](https://github.com/harishd10/TopoMap/blob/master/cpp/TopoMap.hpp)** header file. 

The **[example/main.cpp](https://github.com/harishd10/TopoMap/blob/master/example/main.cpp)** provides an example that takes as input a high dimensional point cloud (specified as a csv), and outputs as csv the projected points (in the same order as the input points) using the TopoMap shared library.


