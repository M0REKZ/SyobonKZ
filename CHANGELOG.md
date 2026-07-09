Release Changelog
-----------------

**SyobonKZ V2 (In Development)**
* Improve code for readability
* Rename executable to "SyobonKZ"
* Add functions to help modding the game
* Working on Syobon Action 3 by DakaArts
    * If you want to try it or help me developing it, use ```--dev-sa3``` parameter (will be removed when ready)
* Add Kaizo Syobon by Zokalal (with permission https://github.com/M0REKZ/SyobonKZ/issues/4)
* Make input more responsive
* Add Pause menu
* Add Options menu (for now only has "Fullscreen" option)
* Save progress and add level selection menu (still not added in SDL 1.2 version)
    * This also allows playing Level 9 in Android!
* Add new parameters:
    * ```--trap-display```: Cheating
    * ```--fast-death```: Dont do death animation
* Fix key keeping pressed after message box in SDL3
* Fix mismatches from the original games:
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
