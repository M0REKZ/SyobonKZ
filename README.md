[![SyobonKZ](https://m0rekz.github.io/SyobonKZ/logo.png)](https://m0rekz.github.io/SyobonKZ/)
==================
###### Original games developers: 
* ###### Chiku (ちく) for Syobon Action
* ###### Bluvel (大川和樹) for Syobon Action 2
###### Open Syobon Action developer: Mathew Velasquez
###### Developer/maintainer of this fork: +KZ (@M0REKZ)
###### [Syobon Action 2 readme (japanese)](readme_ja.txt)

SyobonKZ is a cross-platform port of the unforgiving Japanese platformer ***Syobon Action***.

It is also known as:
* Cat Mario
* Shobon no Action
* Neko Mario
* Cat MeOUCHio
* *and other names.....*

Supported platforms:
-----
* [x] Windows
* [x] Linux
* [x] macOS
* [x] [Web Browsers (with Emscripten)](https://m0rekz.github.io/SyobonKZ/)

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
`-nosound` - Disables sound

Dependencies
------------
This project requires libraries that are old and may not be directly available in your package manager.

* pkg-config (for lib searching)
* SDL 1.2 (or sdl12-compat with SDL2)
* SDL_image 1.2
* SDL_mixer 1.2
* SDL_ttf 1.2
* SDL_gfx (dont confuse with SDL***2***_gfx)

Gamepad Notes
-------------
Your gamepad or joystick may not work by default with Open Syobon Action. Check joyconfig.h for more information.

Unimplemented
-------------
* Font thickness (Not really important)
* Port to other operating systems (iOS, Android, etc.)

Release Changelog
-----------------
**SyobonKZ V1 (in development)**
* Added some "+KZ Edition" text
* Fixed missing Syobon Action 2 assets
* Fix non-transparent sprites
* Make window resizable
* Use CMake build system
* Emscripten (web browser) support
* Fix C++ warnings
* Fix a out of bounds memory access
* Fix including SDL libraries by using pkg-config
* Fix other random bugs...

**Open Syobon Action RC 3 (Karen／明美 fork)**
* Fixed audio on Windows 7 and above

**Open Syobon Action RC 2**
* First Windows release!
* Dvorak keyboard support
* Error messages more detailed and directed to stdout
* Compiled code optimized for speed
* Better initialization and de-initialization code, so you can be confident
 that all resources are freed.
* Optional sound: The game will no longer crash if there is no audio device
 available, and all sound can be disabled with the -nosound parameter
* Minor bugfixes here and there

**Open Syobon Action RC 1**
* Fixed incorrect "box" rendering (used to draw green pipes)
* Fixed random crashing at certain parts (thanks to mekuso for the bug report)
* Volumes now appropriately altered
* Gamepad support added
* Now uses original indexed PNGs, with original filenames (capital PNG)
* Minor tweaks and optimizations

**Open Syobon Action v0.9:**
* Fixed incorrect character rendering, uses font very similar to the original game
 (sazanami-gothic.ttf rather than msgothic.ttf)
* Changed encoding of the original readme and source code to UTF-8, so they can
 be viewed correctly with most software
* Changed DOS newlines to Unix newlines in source and readme
* Source code has been cleaned up with "indent", removed a few obsolete comments

**Open Syobon Action v0.8:**
* First release
