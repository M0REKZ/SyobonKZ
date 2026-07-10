//By: pipocalio
//From: https://discord.com/channels/966688863005339708/977225388906381332/1427056101962022942
//Modified by +KZ
#ifndef LEVEL_ENUMS_H
#define LEVEL_ENUMS_H

// Names here are NOT meant to be accurate to character names' here
// I want this to be understandable by anyone reading.

// -------------------------
// Level Types (stagecolor)
// -------------------------

enum class ELevelType : int
{
    OVERWORLD = 1,
    UNDERGROUND = 2,
    SKY = 3,
    CASTLE = 4,
    ICY = 5,
    KAIZO_SYOBON_OVERWORLD_SLIP = 6,
};




// -------------------------
// Block Types (ttypes)
// -------------------------

enum class EBlockType : int
{
    // Tiles 0–10 form the base set for a level type.
    // Adding multiples of 30 (up to +90) to these tile IDs switches to the
    // same block style in the next level type.
    // Example: In an overworld level, BRICK + 30 becomes the blue
    // underground version of the bricks.

    SOLID_COLOR = 0,
    BRICK = 1,
    ITEM_BLOCK_COIN = 2,
    ITEM_BLOCK_OPEN = 3,
    HARD_BLOCK = 4,
    GROUND_TOP = 5,
    GROUND_BOTTOM = 6,

    // Has a coin inside
    ITEM_BLOCK_HIDDEN = 7,

    // Only visible in overworld or sky stages
    CLOUD_BLOCK = 8,

    // A literal invisible solid block (not a hidden block)
    INVISIBLE_BLOCK = 9,
    SPIKE = 10,

    // A trampoline that you can't interact with
    TRAMPOLINE_BROKEN = 16,

    // A fake item block that you can't hit
    // (block at the start of 1-1)
    ITEM_BLOCK_DODGE = 100,

    ITEM_BLOCK_ENEMY = 101,      // Item block with a enemy (ball, spiky ball, burning flower, defrag)
    ITEM_BLOCK_MUSHROOM = 102,   // "Delicious!"
    ITEM_BLOCK_MUSHROOM_2 = 103, // "Not poisonous, but..."
    ITEM_BLOCK_STAR = 104,

    KAIZO_SYOBON_ITEM_BLOCK_105 = 105, //+KZ: from SA:All Stars

    // Invisible item block with infinite poisonous mushrooms
    ITEM_BLOCK_POISON_HIDDEN = 110,
    // Same as above, but already open
    ITEM_BLOCK_POISON_OPEN = 111,

    // Has a ton of coins inside
    ITEM_BLOCK_COINS = 112,
    // Same as above but already open
    ITEM_BLOCK_COINS_OPEN = 113,

    // Item block with a single poisonous mushroom inside
    // +KZ: Used for other traps too
    ITEM_BLOCK_TRAP_HIDDEN = 114,

    // Crumbles when stood on
    BRICK_BRITTLE = 115,
    ITEM_BLOCK_PSWITCH = 116,

    NOTE_BLOCK = 117,

    // Will push the player to its side when landed on
    PUSH_BLOCK = 118,
    TRAMPOLINE = 120,

    // will grow firebars when hit
    FIREBAR_GROW = 124,

    // Toggle blocks 
    // They're the same since game updates based on stageonoff
    ON_BLOCK = 130,
    OFF_BLOCK = 131,

    // Alias for clarity
    ON_OFF_BLOCK = OFF_BLOCK,

    SWORD = 140,
    BRIDGE_ROPE = 141,
    MELON = 142,

    // Hitting this will display the test message (id 0)
    MESSAGE_BLOCK = 300,
    MESSAGE_BLOCK_BREAKABLE = 301,
    PSWITCH = 400,
    COIN = 800,

    //end of legacy blocks

    //Syobon Action 3
    SA3_GRAY_SPIKE_LEFT,
    SA3_GRAY_SPIKE_RIGHT,
};




// -------------------------
// Enemy Types (atypes)
// -------------------------

enum class EEnemyType : int
{
    BALL = 0,
    BALL_SHELLED = 1,
    SHELL = 2,
    SEAL = 3,
    BALL_SPIKY = 4,
    KUMA = 5,
    DEFRAG = 6,
    BALL_ROCKET = 7,
    SUPER_BOON = 8, //CAPE_GUY (+KZ: when stomped it turns into NORMAL_BOON)
    
    MAGMA = 9,
    FLAME = 10,

    // Enemy at the end of 1-4 on the bridge
    // Called "ボス" (boss) in Chiku's comments
    MOLALLA = 30,

    KUKKURU = 31,

    // ID exists in the code but doesn't do anything??
    UNKNOWN_ID_50 = 50,

    FALLING_BLOCK = 51,
    FALLING_BLOCK_2 = 52,

    LASER = 79,
    
    EVIL_CLOUD = 80,
    EVIL_CLOUD_TOUCHED = 81,

    SPIKY_BLOCK = 82,
    SPIKY_BLOCK_TOUCHED = 83,
    LAVA_FROM_PIPE = 84,

    FAKE_POLE = 85,

    // falls and breaks blocks below
    FALLING_CAT = 86,

    FIREBAR_CLOCKWISE = 87,
    FIREBAR_COUNTERCLOCKWISE = 88,

    BALL_BIG = 90, //+KZ: added this
    MUSHROOM = 100, //+KZ: added this
    BURNING_FLOWER = 101, //+KZ: added this
    MUSHROOM_POISONOUS = 102, //+KZ: added this

    // green "?" ball
    MYSTERY_BALL = 105,

    BAD_STAR = 110, //+KZ: added this

    NORMAL_BOON = 151, //+KZ: SUPER_BOON but without cape

    // The same as BALL but goes
    // right through the floor??
    BALL_NO_COLLISION = 200,

    //end of legacy enemy types
    //types below were added in SyobonKZ
    //must NOT be created with a Legacy function or you may get
    //memory access bugs
    LAST_LEGACY_ENEMY = BALL_NO_COLLISION,

    // -------------------------
    // Syobon Action 3 EnemyTypes
    // -------------------------

    SA3_BIG_MUSHROOM_FALLING,
    SA3_BIG_BALL_ROCKET,
    SA3_SHARK,
    SA3_BIG_STONE,
    SA3_JUMPSCARE_PLANT,
};




// -------------------------
// Decoration Types (ntypes)
// -------------------------

enum class EDecorationType : int
{
    HILL = 0,
    GRASS = 1,
    CLOUD = 2,
    CASTLE = 3,
    CLOUD_SMALL = 4,
    TREE = 5,
    LAVA = 6,

    TEXT_51 = 100,
    TEXT_GAME_CLEAR = 101,
    TEXT_THANKS_FOR_PLAYING = 102,
};




// -------------------------
// Platform types (srtypes) //+KZ: it is srsp
// -------------------------

enum class ELiftType : int
{
    YELLOW = 0,
    BREAKING = 1,

    // pushes you off when stood on
    PUSH_LEFT = 2,
    PUSH_RIGHT = 3,

    PILLAR = 10,

    // Will start falling as soon as you get close to it
    PILLAR_FALL = 11,

    PILLAR_BOUNCY = 12,
    KAIZO_SYOBON_UNKNOWN_13 = 13, //+KZ: from SA:All Stars, but seems like a invalid type?
    PILLAR_BRICKS = 15,

    GRAY = 21,

};




// -------------------------
// object types (stypes)
// -------------------------

enum class EObjectType : int
{
    // not sure what this is
    // +KZ: it is the same as PIPE_BODY :D
    GREEN_OUTLINE_PIPE_PART = 0, //used in 2-2 and 2-4 as the body of the exit pipes
    BLACK_OUTLINE_PIPE_PART = 1,
    VERTICAL_PIPE_BODY = 2,
    HORIZONTAL_PIPE_BODY = 5,

    // +KZ: You can go inside the pipe
    ENTRANCE_HORIZONTAL_PIPE_HEAD = 40,
    ENTRANCE_VERTICAL_PIPE_HEAD = 50,

    // Falling brick ceiling
    FALLING_BLOCKS = 51,
    FALLING_FLOOR = 52,

    TRIGGERS_START = 100, //+KZ: TrapDisplay shows traps with types from 100 to 299
    TRIGGERS_END = 299,

    TRIGGER_SEAL_UP = 100,
    TRIGGER_SEAL_DOWN = 101,
    TRIGGER_GENERIC_1 = 102,
    TRIGGER_LASER = 103,
    // 1-3 and 2-4 multi laser trap
    TRIGGER_MULTI_LASER = 104,
    // This is what makes the brick platform split in 1-4
    TRIGGER_PLATFORM_SPLIT = 105,

    // Makes lava come out of the pipe in 1-2
    TRIGGER_LAVA_SPAWNER = 180,

    CASTLE_BRICKS = 200,

    GOAL_POLE = 300,

    CHECKPOINT = 500,

    LAST_LEGACY_OBJECT = CHECKPOINT,

    //Syobon Action 3
    SA3_FAKE_PIPE_BODY,
    SA3_FALLING_FLOOR, //requires player vel y > 0 to activate

    SA3_TRIGGER_START,
    SA3_TRIGGER_FAST_SEAL_UP = SA3_TRIGGER_START,
    SA3_TRIGGER_BIG_MUSHROOM_FALL,
    SA3_TRIGGER_SPIKES_LEVEL_1_1,
    SA3_TRIGGER_BIG_STONE_BALL_LEVEL_1_1,
    SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1,
    SA3_TRIGGER_END,
};

///********************************************///
/// Enums added by +KZ:
///********************************************///

//less "0 and 1" confusion
enum ELookingDirection : int
{
    LOOKING_LEFT = 0,
    LOOKING_RIGHT = 1,
};

enum ELegacyStageDate : uint8_t
{
    //only IDs from 1 to 255 (unsigned char)
    //many IDs were not even used though and many things are missing
    //i would not recommend using that stagedate thing to mod this game
    NONE = 0,

    //1-19 are Blocks
    //this list does not match EBlockType enum!
    BRICK = 1,
    ITEM_BLOCK_COIN = 2,
    ITEM_BLOCK_OPEN = 3,
    HARD_BLOCK = 4,
    GROUND_TOP = 5,
    GROUND_BOTTOM = 6,
    ITEM_BLOCK_HIDDEN = 7, // Has a coin inside
    CLOUD_BLOCK = 8, // Only visible in overworld or sky stages
    COIN = 9, //9 makes a coin in stagedate!!
    SPIKE = 10,
    TRAMPOLINE_BROKEN = 16, // A trampoline that you can't interact with

    BLOCKS_END = 19,
    //20-29 makes Lifts
    //however it does not set a type listed in this file,
    //but it sets srtype to 0...

    //30 is a Checkpoint
    CHECKPOINT = 30,

    //Pipes... does not seem to be used as their name indicate
    VERTICAL_PIPE_HEAD = 40, //40 is the Vertical pipe head
    VERTICAL_PIPE_BODY = 41, //41 is the Vertical pipe body
    HORIZONTAL_PIPE_HEAD = 43, //43 is the Horizontal pipe head
    HORIZONTAL_PIPE_BODY = 44, //44 is the Horizontal pipe body

    // Chiku(?): "これなぜかバグの原因ｗ (For some reason, this is the cause of the bug lol)"
    // what
    // 50-79 will create enemies/entities
    // the enemy will have type ID minus 50 from this list
    // check stage() function
    BALL = 50,
    BALL_SHELLED = 51,
    SHELL = 52,
    SEAL = 53,
    BALL_SPIKY = 54,
    KUMA = 55,
    DEFRAG = 56,
    BALL_ROCKET = 57,
    SUPER_BOON = 58, //CAPE_GUY (+KZ: when stomped it turns into NORMAL_BOON)
    MAGMA = 59,
    FLAME = 60,

    ENEMIES_END = 79,
    //80-89 will make background decorations
    //it will be ID - 80
    HILL = 80,
    GRASS = 81,
    CLOUD = 82,
    CASTLE = 83,
    CLOUD_SMALL = 84,
    TREE = 85,
    LAVA = 86,

    BACKGROUNDS_END = 89,
    //99 is the finish pole
    GOAL_POLE = 99,

    //and... these were all the ids used in stagedate...
    //the following IDs are used but they are useless or
    //its purpose is unknown

    STAGEDATE_97 = 97,
    STAGEDATE_98 = 98,
};

enum class EExtraGraphicType : int
{
    COIN = 0,
    BLOCK_FRAGMENT = 1, //color depends on StageColor
    LIFT_FRAGMENT_LEFT = 2,
    LIFT_FRAGMENT_RIGHT = 3,
    GOAL_POLE = 4,

    //Syobon Action 3
    SA3_MUSHROOM,
};

// @note FIREBAR_CLOCKWISE and FIREBAR_COUNTERCLOCKWISE uses EnemySubType as their length
enum class EEnemySubType : int
{
    NONE = 0, //"none" wildcard for most enemy types

    BALL_NORMAL = 0,
    BALL_UNSTOMPABLE = 1,

    SHELL_STAY = 0,
    SHELL_MOVING,
    SHELL_MOVING_2, //unknown purpose

    SEAL_UP = 0,
    SEAL_DOWN,
    SEAL_SYOBONKZ_VERTICAL,

    BALL_SPIKY_NORMAL = 0,
    BALL_SPIKY_JUMPER = 1,
    BALL_SPIKY_SA3_HIDE_SPIKES,

    DEFRAG_NORMAL = 0,
    DEFRAG_GRAB_POLE,

    BALL_ROCKET_0 = 0,
    BALL_ROCKET_1,
    BALL_ROCKET_2,
    BALL_ROCKET_3,

    FLAME_0 = 0,
    FLAME_1,

    MOLALLA_ALIVE = 0,
    MOLALLA_DEAD,

    LASER_HORIZONTAL = 0,
    LASER_10_DEGREE_UP,
    LASER_10_DEGREE_DOWN,
    LASER_33_DEGREE_UP,
    LASER_33_DEGREE_DOWN,

    FAKE_POLE_STAY = 0,
    FAKE_POLE_TALKING = 1,
    FAKE_POLE_MOVE = 5,

    MUSHROOM_DELICIOUS = 0,
    MUSHROOM_NOT_POISONOUS = 1,
    MUSHROOM_GROW = 2,
    MUSHROOM_SA3_1UP,

    MUSHROOM_POISONOUS_FASTER = 1,

    MYSTERY_BALL_LEVEL_1_2 = 0,
    MYSTERY_BALL_LEVEL_1_3,

    EVIL_CLOUD_NORMAL = 0,
    EVIL_CLOUD_HIDDEN = 1,

    SPIKY_BLOCK_GROUND_TOP = 0,
    SPIKY_BLOCK_HARD_BLOCK,
    SPIKY_BLOCK_MESSAGE_BLOCK,

    SPIKY_BLOCK_TOUCHED_GROUND_TOP = 0,
    SPIKY_BLOCK_TOUCHED_HARD_BLOCK,

    UNKNOWN_ID_50_1 = 1,

};

enum class EBlockSubType : int
{
    NONE = 0, //"none" wildcard for most block types

    ITEM_BLOCK_UNKNOWN_10 = 10, //unknown purpose

    ITEM_BLOCK_DODGE_VERTICAL = 0,
    ITEM_BLOCK_DODGE_HORIZONTAL = 1, //unused

    ITEM_BLOCK_ENEMY_BALL_NORMAL = 0,
    ITEM_BLOCK_ENEMY_BALL_SPIKY_NORMAL = 1,
    ITEM_BLOCK_ENEMY_BURNING_FLOWER = 3,
    ITEM_BLOCK_ENEMY_DEFRAG_NORMAL = 4,
    ITEM_BLOCK_ENEMY_BURNING_FLOWER_10 = 10, //unused, same as ITEM_BLOCK_ENEMY_BURNING_FLOWER

    ITEM_BLOCK_MUSHROOM_DELICIOUS = 0,
    ITEM_BLOCK_MUSHROOM_GROW = 2,
    ITEM_BLOCK_MUSHROOM_POISONOUS_FASTER = 3,
    ITEM_BLOCK_MUSHROOM_SA3_TRAP = 4, //added in SA:All Stars for SA3 for big mushroom trap

    ITEM_BLOCK_STAR_BRICK = 0,
    ITEM_BLOCK_STAR_NORMAL = 1,

    ITEM_BLOCK_HIDDEN_NORMAL = 0,
    ITEM_BLOCK_HIDDEN_SA3_NO_SHELL,

    ITEM_BLOCK_TRAP_HIDDEN_NORMAL = 0,
    ITEM_BLOCK_TRAP_HIDDEN_VISIBLE = 1,
    ITEM_BLOCK_TRAP_HIDDEN_BRITTLE = 2,
    ITEM_BLOCK_TRAP_HIDDEN_FIREBAR_SWITCH = 10,
    ITEM_BLOCK_TRAP_HIDDEN_SA3_1UP,

    BRICK_BRITTLE_ITEM_BLOCK_OPEN = 0,
    BRICK_BRITTLE_BRICK = 1,
    BRICK_BRITTLE_BRICK_3 = 3, //same as BRICK_BRITTLE_BRICK

    ON_BLOCK_LOCKED = 1, //can not be disabled
    ON_BLOCK_UNLOCKED = 2,

    OFF_BLOCK_FIREBARS = 1,
    OFF_BLOCK_LOCKED = 2, //can not be enabled

    NOTE_BLOCK_RED_HIDDEN = 0,
    NOTE_BLOCK_RED_VISIBLE = 1,
    NOTE_BLOCK_WHITE_HIDDEN = 2,
    NOTE_BLOCK_WHITE_VISIBLE = 3,

    TRAMPOLINE_VISIBLE = 0,
    TRAMPOLINE_HIDDEN = 1,
    TRAMPOLINE_VISIBLE_3 = 3, //same as TRAMPOLINE_VISIBLE

    //triggers text box for specific levels...
    //had a lot of magic numbers
    //named by World_Level_Section(_Number)
    MESSAGE_BLOCK_1_2_0 = 1,
    MESSAGE_BLOCK_1_3_0_1 = 2,
    MESSAGE_BLOCK_1_3_5 = 3,
    MESSAGE_BLOCK_1_3_0_2 = 4,
    MESSAGE_BLOCK_1_4_0 = 5,
    MESSAGE_BLOCK_2_1_0_1 = 6,
    MESSAGE_BLOCK_2_1_0_2 = 7,
    MESSAGE_BLOCK_2_3_0 = 8,
    MESSAGE_BLOCK_2_4_2 = 9,
    MESSAGE_BLOCK_3_1_0 = 10,
    MESSAGE_BLOCK_1_3_0_3 = 80, //appears after mystery ball is taken

    //Kaizo Syobon
    MESSAGE_BLOCK_KAIZO_SYOBON_1 = 12,
    MESSAGE_BLOCK_KAIZO_SYOBON_2 = 17,
    MESSAGE_BLOCK_KAIZO_SYOBON_3 = 13,
    MESSAGE_BLOCK_KAIZO_SYOBON_4 = 14,
    MESSAGE_BLOCK_KAIZO_SYOBON_5 = 15,
    MESSAGE_BLOCK_KAIZO_SYOBON_6 = 16,

    MESSAGE_BLOCK_MAX = 100, //seems to be a "MAX" ids value

    //animation after firing laser in 1-3
    MESSAGE_BLOCK_1_3_0_4_WAIT_START = 500,
    MESSAGE_BLOCK_1_3_0_4_WAIT_END = 540,
    MESSAGE_BLOCK_1_3_0_4_SHOW_MESSAGE = 541,
};

enum class EObjectSubType : int
{
    NONE = 0, //"none" wildcard for most ground types

    //these seems to be very level specific
    FALLING_BLOCKS_OVERWORLD_BRICK = 0,
    FALLING_BLOCKS_UNDERGROUND_BRICK,
    FALLING_BLOCKS_UNDERGROUND_BRICK_LEVEL_1_2, //1-2 third falling blocks
    FALLING_BLOCKS_CASTLE_GROUND_TOP,
    FALLING_BLOCKS_CASTLE_GROUND_TOP_4, //unused, has different behavior
    FALLING_BLOCKS_CASTLE_GROUND_TOP_X_ONLY = 10, //does not draw in Y Size

    FALLING_FLOOR_GROUND_TOP_BOTTOM = 0, //draws GROUND_BOTTOM below, but that is not solid
    FALLING_FLOOR_BRICK = 1,
    FALLING_FLOOR_GROUND_TOP = 2,

    ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_ROCKET = 0, //1-1 rocket pipe trap
    ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION, //1-2 1-3 pipe entrace from above, go to next section
    ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_LAVA, //1-2 lava pipe, shows player message 51 on death
    ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_WARP_ZONE = 5, //1-2 warp zone trap pipe, shows player message 52 on death
    ENTRACE_VERTICAL_PIPE_HEAD_PLUS_10_SECTION, //2-4 go back trap pipe

    ENTRACE_HORIZONTAL_PIPE_HEAD_KILL_PLAYER_CANNON = 0, //1-2 cannon pipe trap
    ENTRACE_HORIZONTAL_PIPE_HEAD_GO_NEXT_SECTION = 2, //1-2 2-4 pipe entrace from left, go to next section
    ENTRACE_HORIZONTAL_PIPE_HEAD_PLUS_10_SECTION = 6, //unused, same behavior as 2-4 go back trap pipe but horizontal

    //Triggers
    TRIGGER_SEAL_UP_NORMAL = 0,
    TRIGGER_SEAL_UP_LEVEL_1_2, //does not appear if the poison mushroom block is open

    TRIGGER_GENERIC_1_SUBTYPE_4_BALLS = 0, //1-1 4 balls trap
    TRIGGER_GENERIC_1_SUBTYPE_BALL_SPIKY_JUMP, //1-2 spiky ball jumps from the hole
    TRIGGER_GENERIC_1_SUBTYPE_FIRST_KUMA, //1-2 first kuma appear, will become next type after triggering
    TRIGGER_GENERIC_1_SUBTYPE_ENABLE_SECOND_KUMA, //1-2 enables the second kuma trigger
    TRIGGER_GENERIC_1_SUBTYPE_SECOND_KUMA, //1-2 second kuma appear
    TRIGGER_GENERIC_1_SUBTYPE_WARP_ZONE = 7, //1-2 appears WARP ZONE message
    TRIGGER_GENERIC_1_SUBTYPE_THIRD_KUMA, //1-2 overworld kuma
    TRIGGER_GENERIC_1_SUBTYPE_THREE_SEALS, //??? is this unused?
    TRIGGER_GENERIC_1_SUBTYPE_SEAL_DOWN, //appears a falling seal
    TRIGGER_GENERIC_1_SUBTYPE_SURPRISE_MAGMA = 12, //1-4 surprise magma
    TRIGGER_GENERIC_1_SUBTYPE_SCROLLING_OFF = 20, //turn off scrolling by setting scrollx to 0
    TRIGGER_GENERIC_1_SUBTYPE_CLEAR_GAME = 30, //1-4 finish the game (get the melon)

    TRIGGER_LASER_NORMAL = 0,
    TRIGGER_LASER_LEVEL_1_3, //the laser that appears after hitting the message block

    TRIGGER_MULTI_LASER_ACTIVE = 0, //does not work if subtype is not 0

    TRIGGER_PLATFORM_SPLIT_TIMER_END = 3, //it uses subtype as a timer, in 1-4 it starts on 0

    //Syobon Action 3
    SA3_TRIGGER_FAST_SEAL_UP_1_SEAL = 0,
    SA3_TRIGGER_FAST_SEAL_UP_4_SEALS = 1,

    SA3_TRIGGER_SPIKES_LEVEL_1_1_WAITING = 0,
    SA3_TRIGGER_SPIKES_LEVEL_1_1_ACTIVE = 1,
    SA3_TRIGGER_SPIKES_LEVEL_1_1_FINISHED = 2,

    SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_WAITING = 0,
    SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_ACTIVE = 1,
    SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_FINISHED = 2,
};

#endif