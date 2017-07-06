# C_GTK_SimplePaint

## Features
This Software have a "New File " "Read File" and  "Save File " properties on "File"  Tool  Bar 
#### Colors Button :
* Red
* Gren
* Blue
* Yellow
* Purple
* Orange

#### Some Useful Tool
* Draw
* Eraser
* Line
* Radius
* RectAngle 
* Angle
* TriAngle 






## Installation 

IDE : CodeBlocks Mingw

Gtk+2.4 Implemantation Steps
1) http://downloads.sourceforge.net/gtk-win/gtk2-runtime-2.24.10-2012-10-10-ash.exe?download Dowland and Setup

2) https://yadi.sk/d/phJITkO1kL6y7 dowland this file and unrar this file and you will coppy file Directory : 'c:\gtk\' not 'c:\gtk\gtk'

3)MyComputer->Properties->Open Advanced System Setting->Environment Variables click user variables

3.1) Click New
Variable name	: gtk
Value			: c:\gtk
Click OK 

3.2)Click new again 
Variable name	: gdk-pixbuf
Value			: C:\gtk\include\gdk-pixbuf-2.0

3.3) Cilk OK  close 
4)MyComputer->Properties->Open Advanced System Setting->Environment Variables and  System variables 

4.1)Find Path
	;C:\gtk\bin
		add dont forget ';' 

5)In Code Blocks Settings  and Compile.. after that Under  Compiler Settings Window -> Click 'Linker Settings' and wire   Other  Linker Options Text area:
![linker options](https://user-images.githubusercontent.com/24591571/27910426-ce10a14a-625d-11e7-8805-8b265886d744.PNG)



Finally You can  usuage this project :) 

