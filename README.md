# Zombie Project
Zombie Project - a simple console game in which you have to survive in an unfair world full of zombies.
You come to your senses in an empty New York, which is full of zombies.
For now, all you need is to survive, and how to achieve this depends on you.
So get up and don't waste a single moment on empty thoughts, otherwise you simply won't survive.
# Preparing Your Machine
Before you can build and play "Zombie Project" you'll need to ensure that your system has the necessary tools installed.
* CMake. CMake is an essential tool for building C++ projects. It generates platform-specific build files from CMakeLists.txt, making the build process straightforward and consistent across different systems. To download CMake, visit the official website at https://cmake.org/download/ and choose the appropriate installer for your operating system.
* C++ Compiler. You need a C++ compiler to compile the C++ source code of "Zombie Project".  You can download it from the official website (https://gcc.gnu.org/).
# Installation instructions
1. Clone the Repository. Start by cloning the "Zombie Project" repository from GitHub to your local machine. Open a terminal or command prompt and enter the following command:  
   `git clone https://github.com/Maksymr0906/Zombie-Project`
2. Navigate to the Project Directory. Move into the "Zombie-Project" directory that was created after cloning the repository:  
   `cd zombie-project`
3. Build the Project with CMake. "Zombie Project" uses CMake as its build system, which offers platform-independent building. Create a new "build" directory and navigate into it:  
   `mkdir build`  
   `cd build`
5. Generate the Makefile. Use CMake to generate the build files:  
   `cmake ..`
6. Build the Game. Once the CMake configuration is complete, proceed to build the game using the build tool:  
   `cmake --build .`
7. Run the game. Execute the game from the command line or by double-clicking the executable. Executable may be located in Debug folder. For example, executing game using command line:  
   `cd .\Debug\`  
   `.\ConsoleRPG.exe`
