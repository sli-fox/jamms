jamms
=====

## Guidelines for commits
- Only add and commit files that you have actually changed code in.
- .gitignore will prevent untracked files from being added (without an add -f) to the set of files tracked by git, however git will continue to track any files that are already being tracked. So you will see a lot of files like .suo and .sdf files in your git status. Ignore them! Only check in code (cpp and h files)!
- If you add files that you're not supposed to, use "git reset" to revert back to before you added the wrong files to your staging area. 
- Guide on git commands: [http://gitref.org/basic/]

## Installing SFML
SFML is the graphical library we will be using for this project. It's a dependency for the project, so please install it locally by following the steps below. 

1. First, you must download the SFML SDK from the [download page](http://sfml-dev.org/download/sfml/2.1/).
  - You must download the package that matches your version of Visual C++. If you got your VS2012 from the Dreamspark school download, its a 32-bit version (even if your system is 64-bit). So, if your VS2012 is 32-bit, download the "Visual C++ 11 (2012) - 32 bits" SFML package.
  - Remember where you extract your SFML folder to because you will need that path to link it up to VS.

2. When you open the jamms project in Visual Studio, you have to tell the complier where your SFML headers are and the linker where to find the SFML libraries. When you first pull the project off our repo, you have to change the linkage to your local url where SFML was extracted to.
  - In the project's properties, add:
    - The path to the SFML headers (<sfml-install-path>/include) to C/C++ » General » Additional Include Directories
    - The path to the SFML libraries (<sfml-install-path>/lib) to Linker » General » Additional Library Directories
  ![alt tag](http://sfml-dev.org/tutorials/2.1/images/start-vc-paths.png)

3. Then link your application to the SFML libraries (.lib files) that you will need. SFML is made of 5 modules (system, window, graphics, network and audio), and there's one library for each of them. We're going to add the Debug version because we're running the solution using the debugger in VS. Libraries must be added in the project's properties, in Linker » Input » Additional Dependencies. This should be done already, but check that all the SFML libraries that you need are there in your solution (the ones in the pic are just examples):
  - **sfml-system-d.lib;sfml-main-d.lib;sfml-graphics-d.lib;sfml-audio-d.lib;sfml-network-d.lib;sfml-window-d.lib;**
  - ![alt tag](http://sfml-dev.org/tutorials/2.1/images/start-vc-link-libs.png)

4. Last step, you need to copy all your SFML .dll files into the Debug folder of your jamms project.
  - Copy all files FROM SFML-2.1/bin into jamms/Debug
  - Make sure you're only adding .dll files

5. Now, your SFML should be ready! I've include a SFMLTest.txt file with code that should render a green circle in your solution if SFML is properly installed. To test, you can copy the code in SFMLTest.txt into your jamms.cpp file and run the main function. If a green circle appears, then SFML works! :)
