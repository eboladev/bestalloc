==================================================
Best allocation analyzer installation guide. version 1.0
==================================================
Project description:
--------------------------------------------------
 Goal of this project is to implement tool which solves the problem of effective tasks assignment in IT projects. Program takes information about available employees, project's tasks which must be solved and each employee's qualification in some set of requied technologies and finds the best allocation of employees on the requied tasks. All employees are assigned with tasks and all tasks are distributed between employees, moreover total sum of qualifications of pairs Employee - assigned skill is maximal.

--------------------------------------------------
Hardware requirements:
--------------------------------------------------
- Supported processors: Intel Atom series, Intel core 2 duo or later, Intel i-series or later
- RAM: 1GB or more
- Graphics: Intel Integrated Graphics card or alternative external video card
- About 30 MB free disk space.
- OS Ubuntu Linux 12.04 or later or Windows 7 or later.
- Software required: Qt-sdk, git

--------------------------------------------------
For Linux users(Required Ubuntu 12.04 or later):
--------------------------------------------------
1. Install Qt.
Application requires Qt libraries version 4.8 or 5.02 or later
Qt can be installed from terminal typing command:
	`sudo apt-get install qt-sdk`
Check installation typing:
	`qmake --verion`
in terminal. 

2. Install git.
Git is required to download project source codes.
Install git typing next command in terminal:
	`sudo apt-get install git`
Check installation typing:
	`git --verion`
in terminal. 

3. Get project source codes.
Make directory for project code. You can type next command
	`mkdir $HOME/bestAlloc`
Swith to this directory typing
	`cd $HOME/bestAlloc`
Once you installed git, you can download source code from project repository on Github.com using git clone. Just type next command in terminal:
	`git clone https://github.com/kdeorg/bestalloc.git`
`https://github.com/kdeorg/bestalloc.git` - is a link to bestAlloc repository. This link can be found on best alloc project repository main page on Github: `https://github.com/kdeorg/bestalloc` in Https clone URL field.

4. Build project and run tests.
After you received project codes your folder three will be like that:
`$HOME/bestAlloc/bestalloc`
Switch to $HOME/bestAlloc/bestalloc directory typing:
	`cd $HOME/bestAlloc/bestalloc`
Build projects and run tests typing
	`make`
After project will be built you will receive several test tables in terminal, like "start testing of test::Test_Edge" ... "Totals: 8 passed 0 failed 0 skipped". Once all tests passed it means you have succesfully built bestAlloc project. If something has gone wrong during the installation you can clean wrong build with `make clean` command.

5. Run bestAlloc application.
To run bestAlloc application type next command in terminal:
	`$HOME/bestAlloc/bestalloc/bin/bestalloc/bestalloc`
A window of bestAlloc application will appear on your screen. 

--------------------------------------------------
For Windows 7 users: 
--------------------------------------------------
1. Install Qt.
Application requires Qt libraries version 4.8 or 5.02 or later
Qt can be installed from (qt-project.org/downloads).
Qt is installed in C:\Qt by default. Current version is Qt 5.2.1
After installing you should add next directories to system Path:
	`C:\Qt\Qt5.2.1\5.2.1\mingw48_32\bin\ `
	`C:\Qt\Qt5.2.1\Tools\mingw48_32\bin\ `
After that run cmd and type next command to check installation:
	`qmake --verion`
in cmd. 

2. Install git.
Git is required to download project source codes.
Git can be installed from here: (http://msysgit.github.io/)

Check installation typing:
	`git --verion`
in cmd. 

3. Get project source codes.
Run cmd, switch to directory you prefer.
Make directory for project code. You can type next command
	`mkdir bestAlloc`
Swith to this directory typing
	`cd bestAlloc`
Once you installed git, you can download source code from project repository on Github.com using git clone. Just type next command in cmd:
	`git clone https://github.com/kdeorg/bestalloc.git`
`https://github.com/kdeorg/bestalloc.git` - is a link to bestAlloc repository. This link can be found on best alloc project repository main page on Github: `https://github.com/kdeorg/bestalloc` in Https clone URL field.

4. Build project and run tests.
After you received project codes your folder three will be like that:
`bestAlloc\bestalloc`
Switch to bestAlloc\bestalloc directory typing:
	`cd bestAlloc\bestalloc`
Build projects and run tests typing
	`mingw32-make -f Makefile.Windows`
After project will be built you will receive several test tables in cmd, like "start testing of test::Test_Edge" ... "Totals: 8 passed 0 failed 0 skipped". Once all tests passed it means you have succesfully built bestAlloc project. If something has gone wrong during the installation you can clean wrong build with `mingw32-make clean` command.

5. Run bestAlloc application.
To run bestAlloc application type next command in cmd:
	`bestAlloc\bestalloc\bin\bestalloc\release\bestalloc`
A window of bestAlloc application will appear on your screen. 
