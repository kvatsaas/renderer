Code used for examples in the FCG4 Edition of Using Graphics Hardware chapter.

### Prerequisite Libraries

This code uses the libpng, zlib and Boost libraries. These are relatively easy to install on Linux and macos, but will require a little effort on Windows.

## Building the code on Linux

On Ubuntu Linux, you can grab the needed libraries with these package installs:

~~~~
sudo apt-get install libpng-dev libz-dev libboost-all-dev
~~~~

Then, building should be as simple as

~~~~
mkdir build
cd build
cmake ..
make
~~~~

## Building on macos

For the mac, you will certainly need Xcode installed. You can get this from Apple's App Store.

After this, you will want to install Brew [https://brew.sh/](https://brew.sh/).  Brew is a package installer for macos that works well for installing a large variety of external packages and development libraries. With it, you will install 

* cmake
* glew
* boost
* libpng

After you install brew, you can install packages with the following command:

~~~~
brew install <packageName>
~~~~

typed at the command line of the Terminal.

Building the code should be straight forward, but you will need to supply a couple of CMake options on the command line when you run cmake to help it find your PNG libraries correctly and also set the C++ variant you wish to use. The issue is that Apple has older PNG libraries installed that conflict with the more recent libpng I've had you install with brew.  Brew installs its libraries into /usr/local, but unfortunately, the cmake build system locates the header files in Apple's location and the libraries in Brew's location.  When you run your code you will get a conflict between these two libraries stating

~~~~
libpng warning: Application built with libpng-XXXXX but running with YYYYY
~~~~

To fix this, you will add the following flag when you run cmake to create your build files. This option will force CMake to look in /usr/local for the include files for PNG:

   -DPNG_PNG_INCLUDE_DIR=/usr/local/include

Next, by default, Apple's compiler currently uses an older standard of C++. This code requires a more recent standard, like C++14. So, we'll add this option:

  -DCMAKE_CXX_FLAGS=-std=c++14

### Using Makefiles to build on macos

You can use Makefiles to build your program on macos. 

~~~~
mkdir build
cd build
cmake -DCMAKE_CXX_FLAGS=-std=c++14 -DPNG_PNG_INCLUDE_DIR=/usr/local/include ..
make
~~~~

### Using Xcode to build on macos

~~~~
mkdir buildXcode
cd buildXcode
cmake -GXcode -DCMAKE_CXX_FLAGS=-std=c++14 -DPNG_PNG_INCLUDE_DIR=/usr/local/include ..
~~~~

This will create an Xcode project, called OpenGL_FCG.xcodeproj.  The name comes from the string used in the top-level CMakeLists.txt PROJECT function.  You can then open this project with Xcode by double clicking on it in the Finder, or even typing

~~~~
open OpenGL_FCG.xcodeproj
~~~~

on the command line.

### Using CLion to develop on macos

CLion is great for C++ development and provides a nice IDE.  As a student, you can get a free copy of this IDE.  Go to [https://www.jetbrains.com/clion/](https://www.jetbrains.com/clion/) to download it and register as a student. You can use CLion to develop this code.  To do so, download and install CLion. Then, using CLion, open up your project by selecting the folder that contains your top-level CMakeLists.txt file.  When you first run CLion, you'll be given the option to "Open" a project.

Once the project is opened, you will need to add the same CMake options discussed above.  To do so, open up the Preferences dialog:

~~~~
CLion > Preferences
~~~~

Once that dialog pops-up, select the

~~~~
Build, Execution, Deployment > CMake
~~~~

menu options.  Then, in the "CMake options:" textbox, enter these flags:

~~~~
-DCMAKE_CXX_FLAGS=-std=c++14 -DPNG_PNG_INCLUDE_DIR=/usr/local/include
~~~~

Click OK and then build your project.


## Building on Windows 10

Building on Windows will take a little effort. First, make sure you have development libraries and IDEs installed. The code has been tested with VS 2019 and VS 2022 - those instructions vary a bit as marked below.  I also use Git Bash fairly extensively as my main console on Windows.  You will probably find it useful:

* Git Bash [https://git-scm.com/downloads](https://git-scm.com/downloads)

#### VS 2022 Environment

* Visual Studio Community Edition 2022
* CMake version 3.22.1 [https://cmake.org/download/](https://cmake.org/download/)

#### VS 2019 Environment

* Visual Studio Community Edition 2019
* CMake version 3.19 

When you install VS, feel free to add whatever development languages and frameworks you want, but certainly add C++ and the graphics libraries (DirectX, etc...). Once the development environments are installed, make sure to setup your git SSH keys if you want. 

Next, you will need to grab the PNG and ZLib code and build it. After that, you will need to get Boost and GLEW. Luckily there are nice pre-built binaries for these that you can install.

Step 1 - Get zlib and libpng 

You can download Zlib and libpng at the following URLS:

* Zlib - Go to [https://zlib.net/](https://zlib.net/) to grab the ZLIB libraries.
* PNG - Go to [http://www.libpng.org/pub/png/libpng.html](http://www.libpng.org/pub/png/libpng.html) to grab the PNG libraries.

These libraries use CMake, so you can build them with cmake rather easily. After downloading and extracting the files, bring up your preferred developer Command Prompt (I'd suggest the Visual Studio Developer Command Prompt). Then build each. I've provided instructions below:

### zlib

In the Zlib source directory, issue the following commands. Note that I have built all of this in the past using Visual Studio 2019 Community Edition which I specify with the Cmake Generator "Visual Studio 16 2017".  You can use another version of Visual Studio if you like, and I'd suggest being consistent.  So if buildings with Visual Studio 2022 Community, you'd use the "Visual Studio 17 2022" generator.

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX="C:\CS4212Libs" ..
~~~~

You could load this up into Visual Studio if you like (there's a .sln file in te build folder you created), but you can also build it from the Visual Studio Developer Command Prompt using the following command (which I'd recommend since it's fairly easy for these libraries):

~~~~
cmake --build . --config Release --target install 
~~~~

That command will build the Release version of zlib and install it in the C:\CS4212Libs folder that was specified in the previous cmake command.


### libpng

Next, navigate to the libpng source. Then issue the following commands:

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:\CS4212Libs" -DCMAKE_INSTALL_PREFIX="C:\CS4212Libs" ..
cmake --build . --config Release --target install
~~~~

### Boost

Finally, you will need to install Boost. You should grab the Precompiled Windows Binaries of Boost from the Boost site https://sourceforge.net/projects/boost/files/boost-binaries/ (Links to an external site). If you download other boost installers you may have to build the entire thing. You will want to grab Boost 1.72.0 and maybe higher. 

Be careful to download the correct installer. Visual Studio 2022's C++ version number is 14.3, and Visual Studio 2019's C++ version number is 14.2 (e.g. Visual Studio 2017's C++ version number is 14.1). You should only need the 64-bit versions. When I compiled with VS 2019, I downloaded boost_1_72_0-msvc-14.2-64.exe. The installer will place this in the C:\local\boost_1_72_0 folder on your machine and cmake knows to look here to locate the files. When using VS 2022, I downloaded the boost_1_78_0-msvc-14.3-64.exe.

### GLEW

You may also need to grab GLEW (OpenGL Extension Wrangler Library) from [http://glew.sourceforge.net/](http://glew.sourceforge.net/).  You are going to want to grab the Windows 32-bit and 64-bit libraries.  Once you you've extracted the ZIP file, copy the includes, libs and DLLs to the appropriate places.  If you are running git Bash, you can use standard Unix commands like this to do the copying:

~~~~
cp -pr ~/Downloads/glew-2.1.0/include/GL /c/CS4212Libs/include
cp -pr ~/Downloads/glew-2.1.0/lib/Release/x64/glew32*.lib /c/CS4212Libs/lib
cp -pr ~/Downloads/glew-2.1.0/bin/Release/x64/glew32.dll /c/CS4212Libs/bin
~~~~

### Vulkan SDK

We may learn about Vulkan (a fairly recent graphics hardware API).  To use it, you will need a graphics card that is compatible and the Vulkan SDK.  The Vulkan SDK can be downloaded for Windows, Linux, Mac and Android:

* [https://www.lunarg.com/vulkan-sdk/](https://www.lunarg.com/vulkan-sdk/)

## Build the Code

You're now ready to build your code on Windows. Navigate to the location where you cloned the repo and following these instructions to generate the Visual Studio solutions file:

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:\CS4212Libs" -DCMAKE_INSTALL_PREFIX="C:\CS4212Libs" -DBOOST_LIBRARYDIR="C:\local\boost_1_78_0\lib64-msvc-14.3" ..
~~~~

At this point, you could open up the Visual Studio Solution file that will be created in that directory and build and edit within Visual Studio if you want.  This file will be called OpenGL_FCG.sln.  You are free to work right in the VS IDE.

Alternatively, you can also build from the command line using cmake to issue the build:

~~~~
cmake --build . --config Release
~~~~

If you go this route and do not want to use Visual Studio for editing, you can install emacs, atom, sublime or whichever editors you prefer to use.

### Try out the examples

After it builds, you can try executing the code. Before you do that, you're going to need to copy the DLLs in the C:\CS4212Libs\bin folder to where your executables are located. Alternatively, you can copy the DLLs into the Windows system folders. At some point, we could configure the CMake project to do this for us.  Also, don't forget to make sure that any OpenGL Shading Language files (*.glsl) are also in the appropriate locations.  If all works, you'll be able to see some images, triangles or whatever you're developing!

~~~~
OpenGL/Release/glfwExample
~~~~

or

~~~~
examples/Release/test_pngWrite
~~~~
