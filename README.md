# cs_raytrace

//brief project description

## Project Setup
The preferred IDE for working on this project would be Visual Studio. You can download it [here](https://visualstudio.microsoft.com/downloads/).

You'll also need to download Git Bash or the Git UI [here](https://git-scm.com/downloads).
The project thus far has (loosely) used the [Git Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows) but mostly just consisted of pushing to and pulling from the Master Branch. 

### Initial Download

To get the project on your local machine, navigate to your newly downloaded Git Bash terminal. From here navigate to the directory that you wish to clone the project. Once in the directory, type `git clone <url>` where <url> is the clone/download URL from the project page. At this time, the URL is `https://github.com/rpthorne/cs_raytrace.git` and is unlikely to change. Once given the success message, you may navigate into the project directory with `cd cs_raytrace`. You now have a local repository of the project on your local machine. 

### Subsequent Pulling
Now that you have a local repository, you may wish to pull in changes that have since been pushed to the branch you're working in. To do so, again navigate to the project directory in Git Bash. Once in, simply type `git pull` and you should pull down any changes that have been made.

### Pushing Code
If you've updated the project and wish to push it to your current branch, again, navigate to the project directory in Git Bash. Now you need to stage and commit your changes. Choose which files you wish to update in the project with `git add <filePath>` where filePath is the relative path from your current directory to the file(s) you wish to update. If you wish to update all files you've changed, you can simply do `git add .` and press Enter. Now you've staged the changes you wish to add. From here, you must commit them to the repository and attach a commit message. Do so with `git commit -m "<msg>"` or `git commit`. If you don't use the -m flag and set a message, the the Git Bash terminal will prompt you for one. Once this is done, you've committed your changes. Now your local repository is updated properly, but the Git repository branch is not. Finally, you must `git push` to add the changes to the git repository. 
