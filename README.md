# C_GTK_SimplePaint
Basic text editor made with C programming language and GTK+2.4
I used CodeBlocks IDE (MingwEdition) for this project.

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
* Round
* RectAngle 
* Angle
* TriAngle 

** Line Usuage : **

* Step 1 :Left Click for start point

* Step 2 :Left Click for finis point 

* Step 3 :Rigt Click and Drawed 

**TriAngle**

Step 1 :Left Click for First point

*Step 2 :Left Click for Second point 

* Step 3 :Left Click for Last point 

* Step 4 :Rigt Click and Drawed 

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

### Some  Issues and Bugs 

We use this command for clean screen. It have load white screen every for every new button click. Don't worry We will change save path and name for every new photo. You cant just save  new.jpg photo lol

`char newfilename[100]="C:\\Users\\Tunay\\Desktop\\new.jpg";` 


* If you chose eraser you can't draw rectangle, squared, round, line,  triangle. If you want draw you should change background :P 


* Point Button Bug : If you choose  3 point You will draw triangle 






