# FarmerDays
a simple console-based farming RPG

Farmer Days is a console-based farming and adventure game developed in 
C++ using the SplashKit framework.
Players can grow and harvest crops, manage an inventory, trade in the market
and fight monsters in a dungeon to earn coins and progress through the game.

Requirements:
- C++
- SplashKit library (installed locally)
- compile using clang++ with SplashKit linked
- example compile command:
clang++ game_cli.cpp player.cpp monster.cpp farm.cpp crop.cpp utilities.cpp farm_menu.cpp market_menu.cpp dungeon_menu.cpp highscore.cpp audio.cpp savegame.cpp -o test -l SplashKit
