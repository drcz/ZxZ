#include "wasm4.h"

//// JOYSTICK AND STUFF ///////////////////////////////////////////////////////////

enum {DIR_U,DIR_L,DIR_D,DIR_R,DIR_C};

uint8_t joystick = DIR_C;

void reset_joystick() { joystick = DIR_C; } /// \o/

/// todo: może jeśli wciśnione są jednocześnie up i down [right i left] to zeruj oba?
void update_joystick() {
    uint8_t gamepad = *GAMEPAD1;
    if (gamepad & BUTTON_UP) joystick = DIR_U;
    if (gamepad & BUTTON_LEFT) joystick = DIR_L;
    if (gamepad & BUTTON_DOWN) joystick = DIR_D;
    if (gamepad & BUTTON_RIGHT) joystick = DIR_R;
}


//// SPRITES AND STUFF ////////////////////////////////////////////////////////////

enum { RS_EMPTY, /// SURE?!
       RS_DIRT, RS_WALL,
       RS_BARELL,
       RS_PARTICLE_UDLR,
       RS_EXPLOSION12,
       RS_GUN_UDLR,
       RS_BOMB,
       RS_DETONATOR_0,RS_DETONATOR_1,
       RS_LEVER_L, RS_LEVER_R,       
       RS_ACTOR_U,RS_ACTOR_D,RS_ACTOR_LR,
       RS_ACTOR_U23,RS_ACTOR_D23,RS_ACTOR_LR2,RS_ACTOR_LR3,
       RAW_SPRITES_COUNT };

const uint8_t raw_sprites[RAW_SPRITES_COUNT][16] = {
    { /// RS_EMPTY
      0b00000000,0b01000000,
      0b00000000,0b00000000,
      0b00000100,0b00000100,
      0b00000000,0b00000000,
      0b01000000,0b00000000,
      0b00000000,0b00000000,
      0b00000100,0b00000001,
      0b00000000,0b00000000
      /*
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000000,0b00000000
      */
    },
    { /// RS_DIRT
      0b00000000,0b00000101,
      0b00000100,0b00000101,
      0b00000100,0b00000000,
      0b00000000,0b00000100,
      0b00000001,0b01010100,
      0b00010000,0b01100100,
      0b00000000,0b01000000,
    },
    { /// RS_WALL
      0b10101010,0b10101001,
      0b10101010,0b10100101,
      0b10100101,0b01100101,
      0b10100111,0b11100101,
      0b10100111,0b11100101,
      0b10101010,0b10100101,
      0b10010101,0b01010101,
      0b01010101,0b01010101
    },
    { /// RS_BARELL
      0b00000000,0b00000000,
      0b01010101,0b01010101,
      0b00011011,0b10100100,
      0b00011011,0b10100100,
      0b01010110,0b01010101,
      0b00011011,0b10100100,
      0b00011011,0b10100100,
      0b01010101,0b01010101
    },
    { /// RS_PARTICLE_UDLR
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000100,0b10001111,
      0b00010000,0b10001111,
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b00000000,0b00000000
    },
    { /// RS_EXPLOSION12
      0b00100010,0b10001010,
      0b00001011,0b10101100,
      0b10101111,0b11111010,
      0b00111111,0b11111110,
      0b10101111,0b11111110,
      0b10111111,0b11111011,
      0b00101011,0b10111100,
      0b00001000,0b10000010
    },
    { /// RS_GUN_UDLR
      0b01000000,0b00000000,
      0b01110000,0b00000000,
      0b01111001,0b00100000,
      0b01101001,0b11000000,
      0b01101001,0b11000000,
      0b01011001,0b00100000,
      0b01010000,0b00000000,
      0b01000000,0b00000000
    },
    { /// RS_BOMB
      0b00010000,0b01000100,
      0b00011010,0b01101000,
      0b10010101,0b01011001,
      0b10010111,0b11011001,
      0b01010111,0b11010101,
      0b10010101,0b01011001,
      0b10010110,0b01011001,
      0b00011010,0b01101000
    },
    { /// RS_DETONATOR_0
      0b01010101,0b01010101,
      0b00000010,0b01000000,
      0b00000010,0b01000000,
      0b00000010,0b01000000,
      0b00000101,0b01010000,
      0b00011110,0b10010100,
      0b00011110,0b10010100,
      0b00011110,0b10010100
    },
    { /// RS_DETONATOR_1
      0b00000000,0b00000000,
      0b00000000,0b00000000,
      0b01010101,0b01010101,
      0b00000010,0b01000000,
      0b00000101,0b01010000,
      0b00011110,0b10010100,
      0b00011110,0b10010100,
      0b00011110,0b10010100
    },
    { /// RS_LEVER_L
      0b00000000,0b00000000,
      0b11100000,0b00000000,
      0b10010000,0b00000000,
      0b00100100,0b00000000,
      0b00001001,0b00000000,
      0b00000010,0b01000000,
      0b00010101,0b01010100,
      0b01101110,0b10100101
    },
    { /// RS_LEVER_R
      0b00000000,0b00000000,
      0b00000000,0b00001110,
      0b00000000,0b00001001,
      0b00000000,0b00100100,
      0b00000000,0b10010000,
      0b00000010,0b01000000,
      0b00010101,0b01010100,
      0b01101110,0b10100101
    },
    { /// RS_ACTOR_U
      0b00000101,0b01010000,
      0b00001010,0b10100000,
      0b00011010,0b10100100,
      0b00011010,0b10100100,
      0b00010101,0b01010100,
      0b00010101,0b01010100,
      0b00000100,0b00010000,
      0b00000100,0b00010000
    },
    { /// RS_ACTOR_D
      0b00000101,0b01010000,
      0b00000111,0b11010000,
      0b00010111,0b11010100,
      0b00010101,0b01010100,
      0b00100110,0b10011000,
      0b00100101,0b01011000,
      0b00000100,0b00010000,
      0b00000100,0b00010000
    },
    { /// RS_ACTOR_LR
      0b00000001,0b01010000,
      0b00001001,0b01110000,
      0b00001001,0b01110000,
      0b00001001,0b10010000,
      0b00000001,0b10010000,
      0b00000001,0b10010000,
      0b00000001,0b01000000,
      0b00000001,0b01000000
    },
    { /// RS_ACTOR_U23
      0b00000101,0b01010000,
      0b00001010,0b10100000,
      0b00011010,0b10100100,
      0b00011010,0b10100100,
      0b00010101,0b01010100,
      0b00000101,0b01010100,
      0b00000100,0b00010000,
      0b00000100,0b00000000
    },
    { /// RS_ACTOR_D23
      0b00000101,0b01010000,
      0b00000111,0b11010000,
      0b00010111,0b11010100,
      0b00100101,0b01010100,
      0b00100110,0b10011000,
      0b00000101,0b01011000,
      0b00000100,0b00010000,
      0b00000100,0b00000000
    },
    { /// RS_ACTOR_LR2
      0b00000001,0b01010000,
      0b00001001,0b01110000,
      0b00001001,0b01110000,
      0b00001001,0b10010000,
      0b00000001,0b10010000,
      0b00000001,0b01100000,
      0b00000101,0b01010000,
      0b00000000,0b00010000
    },
    { /// RS_ACTOR_LR3
      0b00000001,0b01010000,
      0b00001001,0b01110000,
      0b00001001,0b01110000,
      0b00001001,0b10010000,
      0b00000001,0b10010000,
      0b00000001,0b10010000,
      0b00000001,0b01010000,
      0b00000001,0b00000000
    }
};

enum { S_EMPTY, S_DIRT, S_WALL,
       S_BARELL,
       S_PARTICLE_U,S_PARTICLE_D,S_PARTICLE_L,S_PARTICLE_R,
       S_PARTICLE_U2,S_PARTICLE_D2,S_PARTICLE_L2,S_PARTICLE_R2,
       S_EXPLOSION,S_EXPLOSION2,
       S_GUN_U,S_GUN_D,S_GUN_L,S_GUN_R,
       S_BOMB,S_DETONATOR_0, S_DETONATOR_1,
       S_LEVER_L,S_LEVER_R,
       S_ACTOR_U,S_ACTOR_D,S_ACTOR_L,S_ACTOR_R,
       S_ACTOR_U2,S_ACTOR_D2,S_ACTOR_L2,S_ACTOR_R2,
       S_ACTOR_U3,S_ACTOR_D3,S_ACTOR_L3,S_ACTOR_R3,
       SPRITES_COUNT };

typedef struct {
    uint8_t raw_sprite_index;
    uint32_t flags;
} sprite_t;

const sprite_t sprites[SPRITES_COUNT] = {
    {RS_EMPTY,  BLIT_2BPP}, /// S_EMPTY
    {RS_DIRT,   BLIT_2BPP}, /// S_DIRT
    {RS_WALL,   BLIT_2BPP}, /// S_WALL
    {RS_BARELL, BLIT_2BPP}, /// S_BARELL
    
    {RS_PARTICLE_UDLR, BLIT_2BPP|BLIT_ROTATE},             /// S_PARTICLE_U
    {RS_PARTICLE_UDLR, BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_X}, /// S_PARTICLE_D
    {RS_PARTICLE_UDLR, BLIT_2BPP|BLIT_FLIP_X},             /// S_PARTICLE_L
    {RS_PARTICLE_UDLR, BLIT_2BPP},                         /// S_PARTICLE_R

    {RS_PARTICLE_UDLR, BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_Y},             /// S_PARTICLE_U2
    {RS_PARTICLE_UDLR, BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_Y|BLIT_FLIP_X}, /// S_PARTICLE_D2
    {RS_PARTICLE_UDLR, BLIT_2BPP|BLIT_FLIP_X|BLIT_FLIP_Y},             /// S_PARTICLE_L2
    {RS_PARTICLE_UDLR, BLIT_2BPP|BLIT_FLIP_Y},                         /// S_PARTICLE_R2

    {RS_EXPLOSION12, BLIT_2BPP},             /// S_EXPLOSION
    {RS_EXPLOSION12, BLIT_2BPP|BLIT_ROTATE}, /// S_EXPLOSION2

    {RS_GUN_UDLR, BLIT_2BPP|BLIT_ROTATE},             /// S_GUN_U
    {RS_GUN_UDLR, BLIT_2BPP|BLIT_ROTATE|BLIT_FLIP_X}, /// S_GUN_D
    {RS_GUN_UDLR, BLIT_2BPP|BLIT_FLIP_X},             /// S_GUN_L
    {RS_GUN_UDLR, BLIT_2BPP},                         /// S_GUN_R

    {RS_BOMB, BLIT_2BPP},        /// S_BOMB
    {RS_DETONATOR_0, BLIT_2BPP}, /// S_DETONATOR_0
    {RS_DETONATOR_1, BLIT_2BPP}, /// S_DETONATOR_1

    {RS_LEVER_L, BLIT_2BPP}, /// S_LEVER_L
    {RS_LEVER_R, BLIT_2BPP}, /// S_LEVER_R

    {RS_ACTOR_U,  BLIT_2BPP}, /// S_ACTOR_U
    {RS_ACTOR_D,  BLIT_2BPP}, /// S_ACTOR_D
    {RS_ACTOR_LR, BLIT_2BPP|BLIT_FLIP_X}, /// S_ACTOR_L
    {RS_ACTOR_LR, BLIT_2BPP}, /// S_ACTOR_R

    {RS_ACTOR_U23, BLIT_2BPP}, /// S_ACTOR_U2
    {RS_ACTOR_D23, BLIT_2BPP}, /// S_ACTOR_D2
    {RS_ACTOR_LR2, BLIT_2BPP|BLIT_FLIP_X}, /// S_ACTOR_L2
    {RS_ACTOR_LR2, BLIT_2BPP},             /// S_ACTOR_R2

    {RS_ACTOR_U23, BLIT_2BPP|BLIT_FLIP_X}, /// S_ACTOR_U3
    {RS_ACTOR_D23, BLIT_2BPP|BLIT_FLIP_X}, /// S_ACTOR_D3
    {RS_ACTOR_LR3, BLIT_2BPP|BLIT_FLIP_X}, /// S_ACTOR_L3
    {RS_ACTOR_LR3, BLIT_2BPP}              /// S_ACTOR_R3
};


void display_sprite(uint8_t spr, int32_t x, int32_t y) {
    sprite_t s = sprites[spr];
    blit(raw_sprites[s.raw_sprite_index],x,y,8,8,s.flags);
}
// also cf OBJECTS AND STUFF below for binding of things,facings,frames to sprites.


//// MAP AND STUFF ////////////////////////////////////////////////////////////////

#define MAP_W 128 /// these must be powers of 2 for cheap rounding,
#define MAP_H 32  /// cf map_at etc.

uint8_t the_map[MAP_H][MAP_W];
const uint8_t pre_map[MAP_H][MAP_W+1] = {
  //           1         2         3         4         5         6         7         8         9         10        11        12      
  // 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
    ".....................................#  #......#..................#                    #........................................", // 0
    ".....<#...........................####  #......#..................#                    #......................#.#.#.............", // 1
    "......#.............###########...#     #......#..................######################........................................", // 2
    ".....<#>..........................#     #......#..............................................................#.#.#.............", // 3
    "......#..............B............#     #......#................................................................................", // 4
    ".....<#...........................###   #......######.........................................................#.#.#.............", // 5
    "........................B...........#   #......#    #...................################################.#......................", // 6
    "....................................#   #......#    #...................#................................#......................", // 7
    "..B..........#.##.##.#.#............#   #......#    #..................##..............................#.#.......##########.....", // 8
    "....B........#z........#............#   #......#    ##################.#...............................#.#.......#........#.....", // 9
    ".............#.........##############   #......#       #......#......#.#...............................#.#.......#........#.....", // 10
    "BB.....b.....#.........#                #......#       #......#......#.#...............................#.#.......#........#.....", // 11
    ".............#.......B.#                #......#       #......#......#.#...............................#.#.......#........#.....", // 12
    "####...###########.######################......############.#####.####.###############...###############.############.##########", // 13
    "................................................................................................................................", // 14
    "================================================================================================================================", // 15
    "................................................................................................................................", // 16
    "################.#########.###.###.###.##......##########################################............###########################", // 17
    ".............# #........#B.B#...#...#...#......#..................................#     #............#..........................", // 18
    "..#..........# #........#...#...#...#...#......#..................................#     #............#..........................", // 19
    ".............# #........#...#...#...#...#......#......####.........#####..........#     #............#..............#####.......", // 20
    "..#....B...#####.#########.##############......#......#  #.........#   #..........#######............#..............#   #.......", // 21
    "...........#   #.....................#  #......#......####.........#####................#............#..............#   #.......", // 22
    "..#........#####.....................#  #......####.....................................#............#..............#####.......", // 23
    ".....................................#  #......#   #....................................#######.######..........................", // 24
    ".....................................#  #......#   #..........................................#.#...............................", // 25
    "######.################.#################......###############.################################.################################", // 26
    "................................................................................................................................", // 27
    "##.######################################......###################################.#############################################", // 28
    "....#                                   #......#.......................................#........................................", // 29
    "....##################################  #......#..................######################........................................", // 30
    ".....................................#  #......#..................#                    #........................................"  // 31
}; // :)

uint8_t read_map_at(uint8_t x,uint8_t y) { return the_map[y&(MAP_H-1)][x&(MAP_W-1)]; }

int8_t S1_difference(uint8_t a,uint8_t b,uint8_t r) {
    int8_t d = a-b;
    if(d <= r/2 && d>= -r/2) return d;
    if(d > 0) return d-r;
    return d+r;
}

int8_t S1_distance(uint8_t a,uint8_t b,uint8_t r) {
    int8_t d = S1_difference(a,b,r);
    if(d < 0) return -d;
    return d;
}


//// OBJECTS AND STUFF ////////////////////////////////////////////////////////////

int8_t dx_for(uint8_t dir) {
    if(dir==DIR_R) return 1;
    if(dir==DIR_L) return -1;
    return 0;
}

int8_t dy_for(uint8_t dir) {
    if(dir==DIR_D) return 1;
    if(dir==DIR_U) return -1;
    return 0;
}

enum { KIND_NOTHING,
       KIND_HERO,
       KIND_BARELL, KIND_PARTICLE, KIND_EXPLOSION, KIND_GUN,
       KIND_DETONATOR_0, KIND_DETONATOR_1, KIND_BOMB, KIND_LEVER,
       KINDS_COUNT };

typedef struct {
    uint8_t kind;
    uint8_t x,y;
    uint8_t facing,move;
    uint8_t counter,max_counter;
    uint8_t label;
} thing_t;

#define MAX_THINGS 4096 // XD
thing_t things[MAX_THINGS];
uint16_t first_free=0,last_occupied=0;


thing_t fresh_thing() { /// just some default values...
    thing_t t;
    t.kind = KIND_NOTHING;
    t.x = 0;t.y = 0;
    t.facing = DIR_C; t.move = DIR_C;
    t.counter = 0; t.max_counter = 0;
    t.label = 0;
    return t;
}

void add_thing(thing_t the_thing) {
    if(first_free<MAX_THINGS) {
        things[first_free] = the_thing;
        if(first_free>last_occupied) last_occupied=first_free;
        while(first_free<MAX_THINGS &&
              things[first_free].kind!=KIND_NOTHING) first_free++;
    }
}

void remove_thing(uint16_t index) {
    things[index].kind = KIND_NOTHING;
    if(index<first_free) first_free = index;
    while(things[last_occupied].kind==KIND_NOTHING && last_occupied>=0) last_occupied--;
}


uint8_t sprite_for_maptile(uint8_t t, uint8_t subframe) {
    (void)(subframe); /// just to avoid "error: unused parameter" thing :)
    /// can add some animations here TODO
    switch(t) {
        case '#': return S_WALL;
        case ' ': return S_DIRT;
        /// TODO TODO
        default: break;
    }
    return S_EMPTY; /// just-in-case
}

uint8_t sprite_for_thing(thing_t *t, uint8_t subframe) {
    switch(t->kind) {
        case KIND_NOTHING: return S_EMPTY;
        case KIND_BARELL: return S_BARELL;
        case KIND_BOMB: return S_BOMB;
        case KIND_DETONATOR_0: return S_DETONATOR_0;
        case KIND_DETONATOR_1: return S_DETONATOR_1;
        case KIND_LEVER: return (t->facing==DIR_R?S_LEVER_R:S_LEVER_L);
        case KIND_EXPLOSION: return (subframe>=4 ? S_EXPLOSION : S_EXPLOSION2);
        case KIND_PARTICLE:
            switch(t->facing) {
                case DIR_U: return (subframe>=4 ? S_PARTICLE_U : S_PARTICLE_U2);
                case DIR_L: return (subframe>=4 ? S_PARTICLE_L : S_PARTICLE_L2);
                case DIR_D: return (subframe>=4 ? S_PARTICLE_D : S_PARTICLE_D2);
                case DIR_R: return (subframe>=4 ? S_PARTICLE_R : S_PARTICLE_R2);
            }
            break; // notreached, just-in-case
        case KIND_GUN:
            switch(t->facing) {
                case DIR_U: return S_GUN_U;
                case DIR_L: return S_GUN_L;
                case DIR_D: return S_GUN_D;
                case DIR_R: return S_GUN_R;
            }
            break; // notreached, just-in-case
        case KIND_HERO:
            if(t->move==DIR_C) {
                switch(t->facing) {
                    case DIR_U: return S_ACTOR_U;
                    case DIR_L: return S_ACTOR_L;
                    case DIR_D: return S_ACTOR_D;
                    case DIR_R: return S_ACTOR_R;
                }
            }
            switch(t->facing) {
                case DIR_U: return (t->y&1 ? S_ACTOR_U2 : S_ACTOR_U3);
                case DIR_L: return (t->x&1 ? S_ACTOR_L2 : S_ACTOR_L3);
                case DIR_D: return (t->y&1 ? S_ACTOR_D2 : S_ACTOR_D3);
                case DIR_R: return (t->x&1 ? S_ACTOR_R2 : S_ACTOR_R3);
            }
      default: break;
    }
    return S_EMPTY; // notreached
}


//// hmmmm... a bridge between map and things i presume... ////////////////////////

void initialize_world() {
    uint8_t x,y;
    thing_t t;
    uint16_t i;
    first_free=0; 
    last_occupied=0;
    /// :)
    t.kind = KIND_HERO;
    t.x = 18; t.y = 10;
    t.facing = DIR_D; t.move = DIR_C;
    t.counter = 0; t.max_counter = 0;
    add_thing(t);
    
    for(x=0;x<MAP_W;x++)
        for(y=0;y<MAP_H;y++) {
            switch(pre_map[y][x]) {
                case 'B':
                    the_map[y][x] = '.';
                    t = fresh_thing();
                    t.kind = KIND_BARELL;
                    t.x = x; t.y = y;
                    add_thing(t);
                    break;
                case '<':
                    the_map[y][x] = '.';
                    t = fresh_thing();
                    t.kind = KIND_GUN;
                    t.x = x; t.y = y;
                    t.facing = DIR_L; t.move = DIR_C;
                    t.counter = 1+y%5; t.max_counter = 5;
                    add_thing(t);
                    break;
                case '>':
                    the_map[y][x] = '.';
                    t = fresh_thing();
                    t.kind = KIND_GUN;
                    t.x = x; t.y = y;
                    t.facing = DIR_R; t.move = DIR_C;
                    t.counter = 1+(1+y)%5; t.max_counter = 5;
                    add_thing(t);
                    break;
                case 'V':
                    the_map[y][x] = '.';
                    t = fresh_thing();
                    t.kind = KIND_GUN;
                    t.x = x; t.y = y;
                    t.facing = DIR_D; t.move = DIR_C;
                    t.counter = 1+y%3; t.max_counter = 3;
                    add_thing(t);
                    break;
                case '^':
                    the_map[y][x] = '.';
                    t = fresh_thing();
                    t.kind = KIND_GUN;
                    t.x = x; t.y = y;
                    t.facing = DIR_U; t.move = DIR_C;
                    t.counter = 1+(1+y)%3; t.max_counter = 3;
                    add_thing(t);
                    break;
                //// heh.
                case 'z':
                    the_map[y][x] = '.';
                    t = fresh_thing();
                    t.kind = KIND_DETONATOR_0;
                    t.x = x; t.y = y;
                    t.label = 1; /// !!
                    add_thing(t);
                    break;
                case 'b':
                    the_map[y][x] = '.';
                    t = fresh_thing();
                    t.kind = KIND_BOMB;
                    t.x = x; t.y = y;
                    t.label = 1; /// !!
                    add_thing(t);
                    break;
                    
                /// (...)
                default:
                    the_map[y][x] = pre_map[y][x];
                    break;
            }
        }
}


//// GAME MECHANICS AND STUFF /////////////////////////////////////////////////////

/// ok this is pretty specific but for now...
void explode_all_bombs_with_label(uint8_t label) {
    uint16_t t;
    for(t=0;t<=last_occupied;t++) {
        if(things[t].kind!=KIND_BOMB) continue;
        if(things[t].label==label) {
            things[t].kind = KIND_EXPLOSION;
            things[t].move = DIR_C; things[t].facing = DIR_C;
            things[t].counter = 2; things[t].max_counter = 0;
            /// TODO: chain reaction...
        }
    }
}

int can_move(thing_t *mover) {
    uint16_t t;
    uint8_t nx,ny;
    thing_t *collider,*something;

    if(mover->kind==KIND_NOTHING || mover->move==DIR_C) return 0;

    nx = (mover->x+dx_for(mover->move)) & (MAP_W-1);
    ny = (mover->y+dy_for(mover->move)) & (MAP_H-1);
    /// collision with map?
    switch(read_map_at(nx,ny)) {
        case '#': return 0;
        /// TODO :)
        default: break;
    }
    /// then maybe with other object?
    for(t=0;t<=last_occupied;t++) {
        if(things[t].kind==KIND_NOTHING) continue;
        if(things[t].x==nx && things[t].y==ny) {
            collider = &things[t];
            switch(collider->kind) {
                case KIND_NOTHING:
                    mover->x = nx; mover->y = ny;
                    return 1;

                case KIND_GUN:
                    collider->facing = mover->facing;
                    return 0;

                case KIND_DETONATOR_0:
                    collider->kind = KIND_DETONATOR_1;
                    explode_all_bombs_with_label(collider->label); /// XD
                    return 0;

                case KIND_BARELL: /// TODO: other pushables...
                case KIND_BOMB:
                    collider->move = mover->move;
                    if(can_move(collider)) {
                        mover->x = nx; mover->y = ny;
                        return 1;
                    }
                    collider->move=DIR_C;
                    return 0;

                //// TODO :)

                default: return 0;
            }
        }
    }
    /// boom just move'em.
    mover->x = nx;
    mover->y = ny;
    return 1;
}


void update_world() {
    uint16_t t;
    thing_t newthing;

    /// cleanup after previous step (animation info and stuff?)
    for(t=0;t<=last_occupied;t++) {
        if(things[t].kind==KIND_NOTHING) continue;
        things[t].move = DIR_C;
    }
    /// and the new stuff (moves, collisions, whatever)
    for(t=0;t<=last_occupied;t++) {
        if(things[t].kind==KIND_NOTHING) continue;
        switch(things[t].kind) {
            case KIND_HERO:
                things[t].move = joystick;
                if(joystick!=DIR_C) {                    
                    things[t].facing = joystick;
                    reset_joystick(); /// hehe.
                }
                if(!can_move(&things[t])) things[t].move = DIR_C;
                break;
            case KIND_PARTICLE:
                things[t].move = things[t].facing;
                if(!can_move(&things[t])) {
                    things[t].kind = KIND_EXPLOSION; /// TODO: ESKTRAKCJA EKSPLOZJI WIESZ?!
                    things[t].facing = DIR_C; things[t].move = DIR_C;
                    things[t].counter = 2; things[t].max_counter = 0;
                }
                if(--(things[t].counter)<=0) remove_thing(t); // in case they leak? TODO maybe not?
                break;
            case KIND_EXPLOSION:
                if(--(things[t].counter)<=0) remove_thing(t); // :)
                break;
            case KIND_GUN:
                if(--(things[t].counter)<=0) {
                    things[t].counter=things[t].max_counter;
                    newthing.kind = KIND_PARTICLE;
                    newthing.facing = things[t].facing;
                    newthing.move = things[t].facing;
                    newthing.x = things[t].x;
                    newthing.y = things[t].y;
                    newthing.counter = 200;
                    add_thing(newthing);
                    can_move(&newthing); /// yup.                    
                }
                /// guns don't move.
                break;
            case KIND_BARELL:
            case KIND_BOMB:
                break; /// skip the can_move thing, it's managed by the mover.
            /// TODO.
            default:
                if(!can_move(&things[t])) things[t].move = DIR_C;
                break;
        }
    }
}


//// DISPLAY AND STUFF ////////////////////////////////////////////////////////////

#define CENTRE 76 // (SCREEN_SIZE - SPRITE_SIZE)/2 = (190-8)/2 m'kay?

#define VIEW_RADIUS_W 11 // just enough to fit the screen + offset for animation
#define VIEW_RADIUS_H 11

uint8_t visible_from(uint8_t src_x,uint8_t src_y,uint8_t tgt_x,uint8_t tgt_y) {
    return (S1_distance(src_x,tgt_x,MAP_W)<=VIEW_RADIUS_W &&
            S1_distance(src_y,tgt_y,MAP_H)<=VIEW_RADIUS_H);
}


void display(uint8_t subframe) {
    uint8_t spr;
    uint8_t x_offset,y_offset;
    int32_t x,y;
    int8_t i,j;
    uint16_t t;
    thing_t *a_thing;
    thing_t *actor = &things[0]; // :D

    //// draw the map
    x_offset = CENTRE + (8-subframe)*dx_for(actor->move);
    y_offset = CENTRE + (8-subframe)*dy_for(actor->move);
    for(j=-VIEW_RADIUS_H;j<=VIEW_RADIUS_H;j++)
        for(i=-VIEW_RADIUS_W;i<=VIEW_RADIUS_W;i++) {
            spr = sprite_for_maptile(read_map_at(actor->x+i,actor->y+j), subframe);
            x = x_offset + i*8;
            y = y_offset + j*8;
            display_sprite(spr,x,y);
        }
    /// and animate objects
    for(t=0;t<=last_occupied;t++) {
        if(things[t].kind==KIND_NOTHING) continue;
        a_thing = &things[t];
        if(visible_from(actor->x,actor->y,a_thing->x,a_thing->y)) {
            spr = sprite_for_thing(a_thing, subframe);
            x = x_offset + S1_difference(a_thing->x,actor->x,MAP_W)*8
                - (8-subframe)*dx_for(a_thing->move);
            y = y_offset + S1_difference(a_thing->y,actor->y,MAP_H)*8
                - (8-subframe)*dy_for(a_thing->move);
            display_sprite(spr,x,y);
        }
    }
}

/// THE GAME MAIN DRIVER THINGS ///////////////////////////////////////////////////
uint8_t subframe = 0;

void start() {
    thing_t t;
    subframe = 0;
    reset_joystick();

    PALETTE[0] = 0x521296;
    PALETTE[1] = 0x8a1fac;
    PALETTE[2] = 0xd4864a;
    PALETTE[3] = 0xebdb5e;

    *DRAW_COLORS = 0x4320;
    initialize_world();
}

void update () {
    update_joystick();
    if(subframe==0) update_world();    
    display(subframe);
    subframe++;
    if(subframe==7) reset_joystick(); /// XD
    if(subframe==8) subframe=0;
}
