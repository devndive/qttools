Little tools to ease programming with Qt.

## PFG - .pro file generator ##
The PFG will create .pro files which can be used to create project files. It is an enhancement to qmake which does not include subfolders as "INCLUDES" and does not add the used modules (xml, network, svg, ...) to the .pro file.
You do not have to configure your Xcode/Visual Studio/make-files to include the correct libs for debugging or release versions anymore.

## RFE - Resource File Editor ##
The RFE will help you organize, create and edit your .qrc files. It can handle relative and absolute paths.