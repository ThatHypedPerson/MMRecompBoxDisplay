#include "global.h"

#include "box_ootmm.h"
#include "box_ap.h"

typedef enum {
    BOX_NORMAL,
    BOX_GILDED,
    BOX_KEY_BOSS,
    BOX_KEY_SMALL,
    BOX_STRAY_FAIRY,
    BOX_HEART,
    BOX_SKULL_TOKEN,
    BOX_AP_PROG,
    BOX_AP_USEFUL,
    BOX_AP_FILLER,
    BOX_MAX
} BoxType;

// debug print
char* BoxNames[] = {
    "Normal",
    "Gilded",
    "Boss Key",
    "Small Key",
    "Stray Fairy",
    "Heart",
    "Skull Token",
    "AP Progressive",
    "AP Useful",
    "AP Filler",
};

// original chests
extern Gfx gBoxChestBaseDL[];
extern Gfx gBoxChestLidDL[];
extern Gfx gBoxChestBaseGildedDL[];
extern Gfx gBoxChestLidGildedDL[];
extern Gfx gBoxChestBaseOrnateDL[];
extern Gfx gBoxChestLidOrnateDL[];