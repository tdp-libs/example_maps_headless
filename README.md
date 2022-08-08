# Example headless tp_maps application
This example demonstrates how to render OpenGL on a headless system with no UI. We simply create a model of a sphere and render it to file using tp_maps and OpenGL.

The program should create output.png in the directory that it is run in.

![Output](images/output.png)

## Prerequisites 
* tp_tools [Installation instructions](https://github.com/tp-libs/tp_tools)
* A toolchain for your chosen platform. [Installation instructions](https://github.com/tp-libs/tp_build)

## Clone Instructions
These steps will clone the repo and all of its dependencies. You will need [tp_tools](https://github.com/tp-libs/tp_tools) in your path for this to work.
```
mkdir maps_headless
cd maps_headless
git clone https://github.com/tp-libs/example_maps_headless.git
cp example_maps_headless/maps_headless.pro .
cp example_maps_headless/CMakeLists.top CMakeLists.txt
tpUpdate

```

## Include and Library Paths
Depending on your platform you may need to specify include and library paths. The previous steps should have created a `maps_headless/project.inc` file, this can be modified to add platform specific include and library paths. If these modifications may be of use to someone else then they can be added to the project.inc file found in `maps_headless/example_maps_headless/` directory.

## CMake Build Instructions
From the maps_headless directory created in the steps above perform the following steps.
```
mkdir ../build-maps_headless-desktop
cd ../build-maps_headless-desktop
cmake ../maps_headless
make -j12

```
Run:
```
example_maps_headless/example_maps_headless 
ls output.png 

```


## QMake Build Instructions
To build and deploy the application using QtCreator perform the following steps.
1. Open the top level maps_headless.pro file in QtCreator.
2. Select a kit.
3. Click the green arrow in the bottom left to build and run.
