[![SyobonKZ](https://m0rekz.github.io/SyobonKZ/logo.png)](https://m0rekz.github.io/SyobonKZ/)
==================
[Website](https://m0rekz.github.io/SyobonKZ/)
###### Original games developers: 
* ###### Chiku (ちく) for Syobon Action
* ###### Bluvel (大川和樹) for Syobon Action 2
###### Open Syobon Action developer: Mathew Velasquez
###### Developer/maintainer of this fork: +KZ (@M0REKZ)
###### [Syobon Action 2 readme (japanese)](readme_ja.txt)

> [!NOTE]
> **For modders:**
>
>    If you use this source code for your mod, would be cool if you give credits to "+KZ" and mention the SyobonKZ project, it takes a lot of time and high effort to improve Chiku's and Bluvel's code to make it easier to modify and port to other platforms.
>
>   Dont forget to also include Chiku as he requested in the original japanese readme.
>
> Thanks.
>
> *+KZ*

SyobonKZ is a cross-platform port of the unforgiving Japanese platformer ***Syobon Action***.

It is also known as:
* しょぼんのアクション
* Cat Mario
* Shobon no Action
* Neko Mario
* Cat MeOUCHio
* *and other names.....*

Included games:
-----
SyobonKZ includes the following game remakes/ports:

* Shobon Action (Original):
    * The original game made by Chiku, here is packed as the same game along Bluvel's modification.
* Shobon Action (Modified by Bluvel):
    * The "World 2" expansion made by Bluvel, also the most played and popular Syobon Action version thanks to OpenSyobonAction.
* Syobon Action 3 (Remake):
    * > [!IMPORTANT]
      > Work in progress, use ´´´--dev-sa3´´´ to try the current state, expect bugs
    * Custom sequel made by DakaArts (Daka256xr), now remade with original Syobon Action code and physics!
* Kaizo Syobon:
    * Kaizo Syobon by Zokalal, directly ported from Syobon Action: All Stars!

Supported platforms:
-----
* [x] Windows
* [x] Linux
* [x] macOS
* [x] Android
* [x] [Web Browsers (with Emscripten)](https://m0rekz.github.io/SyobonKZ/game.html)

About the license
-----
Chiku released the source code of Syobon Action to allow others modifying it, however he didnt use a license...
Instead he included a japanese readme.txt with the following text:

```
スパゲティソース かつ タブが一度も使用されてないうえ、
クラスわけ無しにif文大量使用のカオスを解読できる方はどーぞｗ
ご自由に改造なさって下さい。

ただ、そのままのソースを配布するのはご遠慮下さい。
```

In english it somewhat translates to:

```
Spaghetti sauce. The tabs aren't used even once, and the code is a chaotic mess of tons of if statements without any class divisions. If you can decipher it, go ahead!
Feel free to modify it as you like.

However, please refrain from distributing the source code as is.
```

So, as you can see, Syobon Action mods based on the original code can NOT use a open source license, due to the amount of developers that modified it and the unclear license situation.


Notes
-----
* Rather than just playing this game by yourself, it is much more enjoyable to let someone who's never tried it before try playing the game.
* Those who are under 12 years old are not allowed to play.
* Please be aware that by playing this game, there is a possibility that you may develop trust issues towards other humans.
* Please be aware that there is a possibility of getting stressed out while playing this game.
* If any problems are caused by this game, please understand that the developers cannot take any responsibility.
* If you wish to distribute this game to a large amount of people, please give credit to the original developer, Chiku (ちく).
* The game's text is entirely in Japanese, but you do not need to understand the Japanese language in order to play.

Controls (Keyboard)
-------------------
* Left/Right: Move
* Z or Up: Jump
* Space: Double-speed
* 0 (while in-game): Self-destruction
* Escape: Exit
* F1: Return to title screen
* 1-9 (while at the title screen): Select level
* 0 at the title screen: Mystery Dungeon (there is a possibility that some bugs may occur)

Bugs
----
Please report any bugs at the GitHub issue tracker: https://github.com/M0REKZ/SyobonKZ/issues

Command Line Arguments
----------------------
* `-h`,`--help` - Show available parameters
* `-nosound`,`--nosound` - Disables sound
* `--fullscreen` - Start in fullscreen mode

Building
------------
> [!NOTE]
> **For Windows users:**
> 
>    You need the MinGW-w64 toolchain to build this, you can install it by using MSYS2
>
>    Also make sure you are using *MinGW cmake and make* and NOT other one, otherwise you will get building errors, also when doing the cmake step add ```-G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++``` to make sure it will be built using MinGW
>
>    It *could* work by using another toolchain but MinGW-w64 is the only one tested

This project requires the following SDL3 libraries, they are included in this repository as submodules and they will be compiled when building SyobonKZ:

* CMake
* SDL3
* SDL3_image
* SDL3_mixer
* SDL3_ttf
* SDL3_gfx

Alternatively you can build SyobonKZ using SDL 1.2 (for old platforms), **but note that SDL 1.2 itself
is NOT included in this repository**:

* CMake
* SDL 1.2 (or sdl12-compat with SDL2)
* SDL_image 1.2
* SDL_mixer 1.2
* SDL_ttf 1.2
* SDL_gfx (dont confuse with SDL***2***_gfx)

As mentioned, the SDL 1.2 extensions and all SDL3 libraries are included as submodules in this repository, to build this project you need to include them when cloning by doing:
```
git clone --recursive https://github.com/M0REKZ/SyobonKZ.git
```

After that you can do the following to build the game:
```
mkdir build
cd build
cmake ..
make
```

If you want to use SDL 1.2 instead, use this CMake option:
```
cmake -DSYOBONKZ_USE_SDL3=OFF ..
```

Gamepad Notes
-------------
Your gamepad or joystick may not work by default with Open Syobon Action. Check joyconfig.h for more information.

TODO:
-------------
* Font thickness (Not really important)
* Port to other operating systems (iOS, etc.) M0REKZ/SyobonKZ#3
* Port more classic Syobon Action versions M0REKZ/SyobonKZ#4

Release Changelog
-----------------
See [CHANGELOG.md](CHANGELOG.md)
