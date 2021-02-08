# BIBLIO_ENSIAS


# GTK INSTALLATION PROCESS

## Windows installation


- Download and install msys2 from [https://www.msys2.org/](https://www.msys2.org/) there's an installation guide there 
- Note that you have to install the right binary for your machine's architucture either 64bit or 32bit
- Open the start menu and open the msys2 terminal (called **MSYS2 MinGW 64-bit** for 64bit systems and **MSYS2 MinGW 32-bit** for 32bit systems)
- Install pkg-config by running this command in the opened terminal 
  - pacman -S mingw-w64-x86_64-pkg-config (for 64 bit systems) 
  - pacman -S mingw-w64-i686-pkg-config (for 32bit systems)
- In the same terminal after the previous command has finished run the following command to install gtk 
  - pacman -S mingw-w64-x86_64-gtk3 (for 64 bit systems) 
  - pacman -S mingw-w64-i686-gtk3 (for 32bit systems)
- To install gcc and other dev tools you have to run this command again whitin the same terminal 
  - pacman -S mingw-w64-x86_64-toolchain base-devel (for 64 bit systems) 
  - pacman -S mingw-w64-i686-toolchain base-devel (for 32 bit systems)
- Install code-blocks it shouldn't be that hard from here [http://www.codeblocks.org/downloads/26](http://www.codeblocks.org/downloads/26)
- Add the msys2 to your system path following this tutorial [https://docs.alfresco.com/4.2/tasks/fot-addpath.html](https://docs.alfresco.com/4.2/tasks/fot-addpath.html) but instead of the C:\jdk use the msys2 path which is: 
  - **C:\msys64\mingw64\bin** (for 64 bit systems) 
  - **C:\msys32\mingw32\bin** (for 32 bit systems)
- To continue the installation scroll down to how to configure code blocks with gtk

## Linux Installation

run this command **_sudo apt install libgtk-3-dev_** and you're good to go :D (another reason why you should switch to linux )

## How To Configure Codeblocks With gtk

- Create a new project
- Go to Project > Build options 
- Within the Compiler settings tab switch to the Other compiler options sub-tab and add \`pkg-config gtk+-3.0 --cflags\` pay attention to the backticks this symbol \` it has to be copied as well with the command 
- Within the Linker settings tab add \`pkg-config gtk+-3.0 --libs\` to Other Linker options pay attention to the backticks this symbol \` it has to be copied as well with the command 
- All of the following commands are for windows users
  - Go to Settings > Compiler ... 
  - Within the Toolchain executables 
  - Change the compiler's installation to 
    - **C:\msys64\mingw64\bin** (for 64 bit systems) 
    - **C:\msys32\mingw32\bin** (for 32 bit systems) 
    - Change The C compiler to gcc.exe 
    - Change The C++ compiler to g++.exe 
    - Change The Linker for dynamic libs to g++.exe 
    - Change The Make program to make.exe 
  - Click Ok
- That's it you're good to go feel free to use gtk now

# Build The PROJECT

## On Windows Using CodeBlocks

- Open the command line and cd to the project's directory
- Run the following commands: 
  - cmake -DCMAKE_C_COMPILER="gcc.exe" -DCMAKE_CXX_COMPILER="g++.exe" -G "CodeBlocks - MinGW Makefiles" .
- Those last steps will generate a codeblocks project
- Open BIBLIOENSIAS.cbp using CodeBlocks
- Go to Project > Properties > Build targets 
  - And change Type to GUI application 
  - Click OK 
  - Build the project
- Now you can run the application found in build directory named BIBLIOENSIAS.exe

## On Linux

- Open the command line and cd to the project's directory
- Run the following commands:
  - cmake .
  - make
- Run the application from within the terminal by running the command ./BIBLIOENSIAS
