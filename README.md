jamms
=====

## Installing SFML
SFML is the graphical library we will be using for this project. It's a dependency for the project, so please install it locally by following the steps below. 

1. First, you must download the SFML SDK from the [download page](http://sfml-dev.org/download/sfml/2.1/).
  - You must download the package that matches your version of Visual C++. A library compiled with VC++ 9 (Visual Studio 2008) won't be compatible with VC++ 10 (Visual Studio 2010) for example.
  - Remember where you extract your SFML folder to because you will need that path to link it up to VS.

2. When you open the jamms project in Visual Studio, you have to tell the complier where your SFML headers are and the linker where to find the SFML libraries.
  - In the project's properties, add:
    - The path to the SFML headers (<sfml-install-path>/include) to C/C++ » General » Additional Include Directories
    - The path to the SFML libraries (<sfml-install-path>/lib) to Linker » General » Additional Library Directories
  ![alt tag](http://sfml-dev.org/tutorials/2.1/images/start-vc-paths.png)

3. Then link your application to the SFML libraries (.lib files) that you will need. SFML is made of 5 modules (system, window, graphics, network and audio), and there's one library for each of them. We're going to add the Debug version because we're running the solution using the debugger in VS. Libraries must be added in the project's properties, in Linker » Input » Additional Dependencies. Add all the SFML libraries that you need (the ones in the pic are just exmaples):
  - **sfml-system-d.lib;sfml-main-d.lib;sfml-graphics-d.lib;sfml-audio-d.lib;sfml-network-d.lib;sfml-window-d.lib;**
  - ![alt tag](http://sfml-dev.org/tutorials/2.1/images/start-vc-link-libs.png)

4. Now, your SFML should be ready! Make sure you can build the solution. :)
