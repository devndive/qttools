## Dependencies ##

To compile the PFG you need at least [Boost v. 1.34.1](http://www.boost.org) . It has to linked against boost\_filesystem and boost\_program\_options. There are no other dependencies.

To compile with the g++ the command could look like
  * g++ -L /usr/lib/ -lboost\_program\_options -lboost\_filesystem -o PFG `*`.cpp

To compile with the cl.exe the command could look like
  * cl.exe /EHsc /I %BOOSTDIR% `*`.cpp /link /LIBPATH:%BOOSTLIB% -out:PFG.exe

## Usage ##
| General options: | | |
|:-----------------|:|:|
|-h [--help ](.md) | this help message | |
|-p [--path ](.md) arg | location of project | Default: . |
|-n [--name ](.md) arg | application name | Default: Default App |
|-o [--output-file ](.md) arg | name of output file, if omitted the standard output is used | |
|-t [--template-type ](.md) arg | | Default: app |
|                  | templatetypes: | |
|                  |app | Creates a Makefile to build an application. |
|                  |lib | Creates a Makefile to build a library. |
|                  |sub | Creates a Makefile containing rules for the subdirectories specified using the SUBDIRS variable. Each subdirectory must contain its own project file. |
|                  |vca | Creates a Visual Studio Project file to build an application. |
|                  |vcl | Creates a Visual Studio Project file to build a library. |
|-L [--lib-dir ](.md) arg | extra library dirs | multiple directories are possible |
|-l [--lib ](.md) arg | extra libraries | multiple libraries are possible |
|                  | | |
| Module options:  | | |
|--core            | use qt core module | |
|--no-core         | do not use qt core (use with caution) | |
|--gui             | use qt gui module | |
|--no-gui          | do not use qt gui (use with caution) | |
|--network         | use qt network module | |
|--no-network      | do not use qt network module | |
|--opengl          | use qt opengl module | |
|--no-opengl       | do not use qt opengl module | |
|--sql             | use qt sql module | |
|--no-sql          | do not use qt sql module | |
|--svg             | use qt svg module | |
|--no-svg          | do not use qt svg module | |
|--qt3support      | use qt3support module | |
|--no-qt3support   | do not use qt3support module | |
|--xml             | use qt xml support | |
|--no-xml          | do not use qt xml support | |

e.g:
PFG -p ~/workspace/qttools/RFE -n RFE -o ~/workspace/qttools/RFE.pro

will create a project file (-o ~/workspace/qttools/RFE.pro) for the project in ~/workspace/qttools/RFE
PFG will recursevly find all .cpp, .h, .qrc and .uic files. Then the .cpp and .h files will be scanned for all #include's. These includes will be checked against Qt include files. Depending on the included files the corresponding modules are added to the .pro file (e.g. QT += xml network)