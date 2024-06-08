# Game_of_life
A short adaptation of game of life with other functions for future ideas and changes

## Setup

- You have to first download SFML to be able to use it. Edit in you c_cpp_properties.json file to add to the includePath the path to the include file of SFML so that intellisense can know where it is.
- Then, in the makefile, it is specified where you should put another time the path to the include folder of SFML and the path to the lib folder of SFML. put them accordingly.
- Finally, you should put the specific bin files in the same directory as the executable to be able to run the executable. You can do this after compilation. The specific files would be ```sfml-graphics-2.dll ```, ``` sfml-system-2.dll``` and ```sfml-window-2.dll```.

  __N.B:__ if you don't have makefile, just copy the commands on compile and link, and run them on the terminal, it should do the job

 ## How to use
 Well turn run it you should type the command ``` .\FileName ``` then it will run indefinitely until you click the close button on the window.
