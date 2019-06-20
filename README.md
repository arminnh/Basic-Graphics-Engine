# Basic Graphics Engine

A basic image generator written in C++ as part of a [Computer Graphics course](https://www.uantwerpen.be/popup/opleidingsonderdeel.aspx?catalognr=1001WETCGR&taal=en&aj=2014) at the University of Antwerp. The engine will create .bmp images by using a description in text files.

![example image](https://raw.githubusercontent.com/arminnh/Basic-Graphics-Engine/master/images/spheres_and_cylinders/spheres_and_cylinders014.png)

## Features

* 2D L-systems
* Linedrawings
* 3D figures
* Z buffering with lines and with triangles

## pdfs included for implementing features

* 3D fractals
* Lighting
  * Ambient
  * Diffuse
  * Specular
* Shadowing
* Texture Mapping
* Spheres and cylinders

## Setup

### Requirements

* g++

### Build

Simply run `make` to compile the engine under `/bin/`. The engine will be created in the images folder.

## Usage

Generate specific images

```sh
engine [image description files]
```

Generate sets of images

```sh
script [options]  
```

options:

* all
* 2dlsystems
* linedrawings
* 3dfigures
* zbufferinglines
* zbufferingtriangles
* 3dfractals
* lightingambient
* lightingdiffuse
* lightingspecular
* spheresandcylinders

## Libraries used

* EasyImage
* ini_configuration
* lparser
* vector3D

Documentation for each of these can be found in slides+pdfs/tools/

####Todo
Finish features + CMake + images script


