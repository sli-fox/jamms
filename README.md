jamms
=====

**Table of Contents** 

- [jamms](#user-content-jamms)
  - General info
	- [Consistent naming and style conventions](#user-content-consistent-naming-and-style-conventions)
	- [Guidelines for commits](#user-content-guidelines-for-commits)
  - Project configuration (what you need to do to get the project to compile)
	- [Installing SFML](#user-content-installing-sfml)
	- [Adding jamms headers path](#user-content-adding-jamms-headers-path)
  - About the code
	- [The TextureManager class](#user-content-the-texturemanager-class)

## Consistent naming and style conventions
If in doubt, we should all use the same naming and style conventions. I chose this system because I think it helps to quickly recognize what is a variable or a method, etc.
  - Variable names have underscores
    - Public: my_public_var
    - Private: _my_private_var
  - Class and struct names are in upper camel case
    - MyClassName
  - Method names are in lower camel case
    - myMethodName()
  - Enums are in upper camel case
    - MyEnumName
  - Code blocks with curly braces have the first brace inline:
    - void myMethodName {
      -   //Add code
    - }
  - Don't use "using namespace std" declarations, use "std::string" in front of the variable type instead

The above conventions I've used are based from Google's guide for C++:
[http://google-styleguide.googlecode.com/svn/trunk/cppguide.html#General_Naming_Rules]

## Guidelines for commits
- Only add and commit files that you have actually changed code in AND the .vcxproj file (if it has changed)
  - The .vcxproj file is the actual project file so it should be checked it.
  - If you've changed the .vcxproj.filters file, we need to talk as a team if you guys want to check that file in.The .vcxproj.filter files provides the folder structure you see in your build. IMO, I think all the devs should be using the same folder structure to lesson confusion, but that means each dev needs to NOT make unecessary changes to the file structure in jamms.
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
  - Copy all .dll files FROM SFML-2.1/bin into jamms/Debug
  - Make sure you're only adding .dll files

5. Now, your SFML should be ready! I've included a SFMLTest.txt file with code that should render a green circle in AN EMPTY SOLUTION if SFML is properly installed. To test, you can copy the code in SFMLTest.txt into your main cpp file and run the main function. If a green circle appears, then SFML works! :) Alternatively, you can just run the exisiting jamms project to test.

## Adding jamms headers path
To simplify adding headers to the project, you must add (<jamms-folder-path>/include) to C/C++ » General » Additional Include Directories in your project properties. 
  - For example, mine is "C:\Users\Steph\Projects\COMP345\jamms\jamms\jamms\include"
  - Then, in the project, create header files ONLY in the that same include folder
    - You'll be able to include header files simply by using #include \<MyHeaderFile.h\> without worrying about paths. 


##The TextureManager class
So, I created a singleton class called TextureManager that makes handles texture loading efficiently. Why is it useful? The class holds a single instance (hence the singleton class) of a map where all previously loaded textures go. Whenever you create a sprite and you give it a path to a texture image, the TextureManager class checks it against the map of textures. If the texture has been previously loaded, the loadTexture function of the class returns a reference to the loaded texture. If the texture is new, it loads the texture, saves the texture reference in the map, and returns you the newly loaded texture reference. Note all textures are implemented in the heap. 

How to create a sprite using the TextureManager class:
- TextureManager& t_manager = TextureManager::getInstance();  //Get an instance of the TextureManager object
- sf::Sprite yourSpriteName(t_manager.loadTexture("resources/images/YourImage.png"));  //Create the sprite!

Easy as pie!

There's also the unloadTexture() function whih removes the instance of texture associated with a image path in the texture map.



----
Note for Github markdown TOC: http://doctoc.herokuapp.com/
