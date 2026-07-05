## Overview
Terminal 2048 game. Have fun!

![](var/2048.gif)

## Dependencies
To play this game you would need ncurses library
### Ubuntu / Debian 

```
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev
```

To test this game you would need gtest
### Ubuntu / Debian 

```
sudo apt update
sudo apt install libgtest-dev libgmock-dev
```

## How to run

To play just run the follow commands. You can quit by pressing "q" or restart by pressing "r".

```
make
./bin/main
```

To run the tests, execute the following command:

```
make test
```