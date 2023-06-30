# Intoduction
This repository is collection of reference projects for XYZ school c++ course.
Just open the Game.sln and enjoy.

# License and author rights 
©2023, XYZ School. All rights reserved.
Authored by Aleksandr Rybalka (polterageist@gmail.com)

This repository and all it's content (except content of SFML directory) are private property of "©XYZ school" and is intended only for it's students learning purposes.
It cannot be distributed, used or demonstrated to third parties in any form without direct permissions of property owner in written form.
Projects with significant changes, made on this template, can use their own license if they wish.

# Repository content
## SFMLTemplate
This is simple template project for developing games with SFML library.
Just open the Game.sln, compile and run project named Game. If you want to create a game - copy it, renaming it's directory and files SFMLTemplate.vcxproj and SFMLTemplate.vcxproj.filters.
Then add new project to Game.sln via visual studio.

## ApplesGame
This is project of first course block. Simple game with square, representing the player, which moves in four direction and eats "Apples". Each eaten apple increases the speed of player.
If player collides with the wall - the game is over.

## SFML
This directory contains the entire compiled SFML library for simplifying things. There is SFML VS project to maka easy access to SFML headers inside IDE.

# Branching policy
Each branch is intended for separate developing of projects as they appear in course. So each branch contains only those project, which student have at this stage (which allows us to tag each lesson result).
So if you need to improve something, consider following order of changing things:
* Template changes (including this readme and gitignore) goes to "template" branch
* Module's project changes goes to project branch. If you need to change result of specific lesson - create separate branch for it from commit where it was introduced and then update the tag

To not introduce something unnedded in branch consider following order of merging
template -> apples_game (module 1 project) -> ... -> main
Do not merge it in other direction. It is important to maintain clear structure of the repository for students.


