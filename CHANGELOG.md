Release Changelog
-----------------

**SyobonKZ V2.2**
* Add SyobonKZ credits screen
* Fix some memory that was not being freed after use
* Fix some enemies collision with objects
* Try to fix updating installed Android app
* Fix Kaizo Syobon level 3 mushroom(?) platforms
* Rename some enemies in enums (level_enums.hpp) to match original names

**SyobonKZ V2.1**
* Fix wrong graphics for some falling floor traps

**SyobonKZ V2**
* Improve code for readability
* Rename executable to "SyobonKZ"
* Add functions to help modding the game
* Working on Syobon Action 3 by DakaArts, Syobon Action JAM by StudsX.. And my own Syobon Action game :P
    * If you want to try current progress or help me developing them, use ```--dev-games``` parameter
* Add Kaizo Syobon by Zokalal (with permission https://github.com/M0REKZ/SyobonKZ/issues/4)
* Make input more responsive by using **input buffering**
* Make macOS binary be in a App Bundle (SyobonKZ.app)
* Add Pause menu
* Add Options menu (for now only has "Fullscreen" option)
* Save progress and add level selection menu (still not added in SDL 1.2 version)
    * This also allows playing Level 9 in Android!
* Add basic Screenshot and GIF Recorder keys (Desktop SDL3 only)
* Add new parameters:
    * ```--dev-games```: Check the above changes in this list for more information
    * ```--trap-display```: Cheating
    * ```--fast-death```: Dont do death animation
* Fix key keeping pressed after message box in SDL3
* Fix mismatches/bugs from the original games:
    * General:
        * Now title screen will toggle Enter key text between Chiku's and Bluvel's
        * Restored no-text Checkpoint sprite for Syobon Action 1 levels
        * Use a version of field.ogg that loops correctly
    * Level 1-3:
        * Fixed finish sound still being played after Defrag grabs the pole
    * Level 2-3:
        * Removed "wall" bricks that did not allow Defrag to fall
* Fix random bugs...

**SyobonKZ V1**
* Add macOS, Android and Web Browser support
* Format, separate, rename and do more improvements to the code for readability
* Added some "+KZ Edition" text
* Use a new icon :P
* Fixed missing Syobon Action 2 assets
* Fix non-transparent sprites
* Make window resizable
* Use CMake build system
* Fix C++ warnings
* Fix a out of bounds memory access
* Fix including SDL libraries
* Optimize japanese text rendering by loading CPU expensive images as bmp
* Fix sound overlap
* Allow to use SDL3 instead of SDL 1.2
* Add "--fullscreen" and "--help" parameters
* Fix some mismatches/bugs from the original games:
    * Level 1-1:
        * Restored delicious mushroom
        * Restored unstompable enemy
        * Fixed gray line of the checkpoint (but keep the text)
    * Level 1-4:
        * Fixed sword ending (it should not end the game here)
    * Level 2-3:
        * Restored stompable enemy from the start
        * Restored a Evil Cloud that was removed
        * Now hitting the hidden block with the shell is consistent
    * Level 2-4:
        * Fix wrong music in final section (it was credits music)
    * Level 3-1 (Secret level 9):
        * Fix loading a invalid level after beating it
    * Other:
        * Restore some of the enemy messages from Syobon Action 1
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
