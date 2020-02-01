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
Notes:
