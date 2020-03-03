Hey welcome to the Pacman project! The purpose of this file is to help you get up and running as quickly as possible.
-Matt

1) If you're on your home pc/laptop you'll want to have WinSCP open after cloning/downloading this onto your Seneca C: using Putty, and you'll want to drag the folder "sc_pacman" (the one this file is contained in) to a place on your hard drive that is easy to find.
2) Open VS Code 2019 and choose "Open a project or solution", find where the folder sc_pacman is and open "pacman.sln".
3) You're now ready to go!
(This is done so that we can work with a VS Project and run our code in VS Code to test as opposed to creating a runnable file with gcc to test)

For when you're ready to push your changes (this will change if we have branches):
1) If you're on a home pc/laptop, using WinSCP move your sc_pacman folder back to the spot it was cloned/downloaded to, choosing to overwrite all that was previously there. This spot will have a .git folder which is needed for pushing to git.
2) Do these commands in Putty in the directory that contains both your sc_pacman folder & .git folder
	
	git add *                            <--this adds all files in current directory to "staging"
	
	git commit -m "Some message here"    <--this will create a "commit" all of the files in "staging", with the message given inside of quotation marks
	
	git push							 <--this will push all of your files up to the repository, which will be viewed by Jacky before being approved.

It is also perfectly fine to just make changes to the sc_pacman.c file directly, and using WinSCP to drag the file back to your Seneca C: and in Putty using the command

	gcc -Wall sc_pacman.c -o game
	
This will create an executable file called "game" that you can run in Putty by using the command "game", use step 2) in the above section to apply changes if this is your preferred method.


-Add notes here that need to be addressed! Please leave instructions above alone
<<<<<<< HEAD

Notes:
=======
Notes:
hey guys this is Adonis, I could not figure out the graphics but while I was hunting around for examples but while I was hunting around I came across this gem. I've uploaded a file called pacman1.c and taken the liberty of designing the level based on the picture that Professor Lau had uploaded its about half of the map A,B and c building. anyways you can run it is VS 2019 and have a look. If we can learn something from it then I'm happy I could contribute.
>>>>>>> 09dfe0cbcb16d98d6b851884361b2e5435341bab

---

### Update on Feb. 22, 2020

##### Files Reorganise
- all source code can be found in `./Source Codes`
- all dependent header files can be checked in `./Include`
- all dependent libruaries are stored in `./Lib`
- all source code are sorted in `./Source Code`
- older files are backuped in `./Source Code/backup`

##### OpenGL Set Up
the example can be compiled, please check `./Source Codes/opengl.c`

##### Dependent files link
- all the headers and libruaries currently needed are successfully linked to the solution file
- to add more header files, simply copy the files to `./Include`
- to add more libruaries, follow the procedures below
	- copy the libruary file to `./Lib`
	- project => poperties
	- linker => input
	- type the new lib's name in the first line on your right, and followe the same syntax

##### Suggestion :D
You can learn `markdown` to make this page look more better!

Leon

---

### Update on March 2, 2020

##### SDL Immigration
Because OpenGL math library only work in C++, there is no way to create animation; switching to SDL is a better choice.

##### About Game Version 0.0.1
A super basic version has been created, which includes:
- `pacman.c` - a main function source file 
	- overall game logic designing
	- functions encapsulating
- `functions.c` - a separate source file to store functions
	- handmade functions
- `declaration.h` - a header file to store macros and prototypes
	- simply use `extern` to import functions from `functions.c`
	
##### Further Improvement
- Refine comments
- Fix the facing direction when pacman move to another direction
	- use rotation and flipping function
- Draw pictures
	- draw a better pacman picture
	- draw ghosts' picture
	- draw dots' picture
	- draw fruits (optional)
- Set the boundary
	- set the wall and make the collision detection function work
	- make the tunnel in the middle a "tunnel"
- Create more game logic
	- determine the consequence when pacman catched by ghosts
	- give reactions when pacman eat dots and energizer
- Apply A* algorithm to the ghosts

##### Tutorial
I found Lazy Foo's online tutorial is quite useful and relavent easy, and I have read the first 20 sections of it.
[The tutorial can be found here.](https://lazyfoo.net/tutorials/SDL/index.php)






