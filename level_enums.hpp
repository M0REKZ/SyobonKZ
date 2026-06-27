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

enum class ELevelType
{
    OVERWORLD = 1,
    UNDERGROUND = 2,
    SKY = 3,
    CASTLE = 4,
    ICY = 5,
};




// -------------------------
// Block Types (ttypes)
// -------------------------

enum class EBlockType
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

    // Invisible item block with infinite poisonous mushrooms
    ITEM_BLOCK_POISON_HIDDEN = 110,
    // Same as above, but already open
    ITEM_BLOCK_POISON_OPEN = 111,

    // Has a ton of coins inside
    ITEM_BLOCK_COINS = 112,
    // Same as above but already open
    ITEM_BLOCK_COINS_OPEN = 113,

    // Item block with a single poisonous mushroom inside
    ITEM_BLOCK_POISON_SINGLE_HIDDEN = 114,

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
    ARTICHOKE = 142,

    // Hitting this will display the test message (id 0)
    MESSAGE_BLOCK = 300,
    MESSAGE_BLOCK_BREAKABLE = 301,
    PSWITCH = 400,
    COIN = 800,
};




// -------------------------
// Enemy Types (atypes)
// -------------------------

enum class EEnemyType
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
    BOSS = 30,
    MOLALLA = BOSS,

    CHICKEN = 31,
    KUKURRU = CHICKEN,

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
};




// -------------------------
// Decoration Types (ntypes)
// -------------------------

enum class EDecorationType
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

enum class ELiftType
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
    PILLAR_BRICKS = 15,

    GRAY = 21,

};




// -------------------------
// object types (stypes)
// -------------------------

enum class EObjectType
{
    // not sure what this is
    // +KZ: it is the same as PIPE_BODY :D
    VERTICAL_PIPE_BODY = 0,
    VERTICAL_PIPE_HEAD = 1,
    HORIZONTAL_PIPE_BODY = 2,
    HORIZONTAL_PIPE_HEAD = 5,

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
};

#endif