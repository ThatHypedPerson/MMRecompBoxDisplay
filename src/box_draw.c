#include "modding.h"
#include "global.h"

#include "box_types.h"

RECOMP_IMPORT("*", int recomp_printf(const char* fmt, ...));

#define OBJECT_BOX_CHEST_LIMB_01 0x1
#define OBJECT_BOX_CHEST_LIMB_03 0x3
#define OBJECT_BOX_CHEST_LIMB_MAX 0x5

struct EnBox;
struct struct_80867BDC_a0;

typedef void (*EnBoxActionFunc)(struct EnBox*, PlayState*);
typedef void (*EnBoxUnkFunc)(struct struct_80867BDC_a0* arg0, PlayState* play);

typedef struct struct_80867BDC_a0 {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ EnBoxUnkFunc unk_0C;
    /* 0x10 */ EnBoxUnkFunc unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} struct_80867BDC_a0; // size 0x24

typedef struct EnBox {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ s32 unk_1A0;
    /* 0x1A4 */ UNK_TYPE1 unk_1A4[0x04];
    /* 0x1A8 */ f32 unk_1A8;
    /* 0x1AC */ EnBoxActionFunc actionFunc;
    /* 0x1B0 */ Vec3s jointTable[OBJECT_BOX_CHEST_LIMB_MAX];
    /* 0x1CE */ Vec3s morphTable[OBJECT_BOX_CHEST_LIMB_MAX];
    /* 0x1EC */ s16 unk_1EC;
    /* 0x1EE */ u8 movementFlags;
    /* 0x1EF */ u8 alpha;
    /* 0x1F0 */ u8 switchFlag;
    /* 0x1F1 */ u8 type;
    /* 0x1F2 */ u8 iceSmokeTimer;
    /* 0x1F3 */ s8 unk_1F3;
    /* 0x1F4 */ struct_80867BDC_a0 unk_1F4;
    /* 0x218 */ s16 csId1;
    /* 0x21A */ s16 csId2;
    /* 0x21C */ s32 getItemId;
    /* 0x220 */ s32 collectableFlag;
} EnBox; // size = 0x224

#define THIS ((EnBox*)thisx)

int curBox = 0;
Input controller[1];

RECOMP_PATCH void EnBox_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    s32 pad;
    EnBox* this = THIS;

    PadMgr_GetInputNoLock(controller, false);
    if (CHECK_BTN_ALL(controller[0].press.button, BTN_L)) {
        ++curBox;
        if (curBox >= BOX_MAX) {
            curBox = BOX_NORMAL;
        }
        recomp_printf("Now Displaying: %s\n", BoxNames[curBox]);
    }
    

    if (limbIndex == OBJECT_BOX_CHEST_LIMB_01) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        switch (curBox) {
            case BOX_NORMAL:
                gSPDisplayList((*gfx)++, &gBoxChestBaseDL);
                return;
            case BOX_GILDED:
                gSPDisplayList((*gfx)++, &gBoxChestBaseGildedDL);
                return;
            case BOX_KEY_BOSS:
                gSPDisplayList((*gfx)++, &gBoxChestBaseOrnateDL);
                return;
            case BOX_KEY_SMALL:
                gSPDisplayList((*gfx)++, &keyChestBaseDL);
                return;
            case BOX_STRAY_FAIRY:
                gSPDisplayList((*gfx)++, &fairyChestBaseDL);
                return;
            case BOX_HEART:
                gSPDisplayList((*gfx)++, &heartChestBaseDL);
                return;
            case BOX_SKULL_TOKEN:
                gSPDisplayList((*gfx)++, &spiderChestBaseDL);
                return;
            case BOX_AP_PROG:
                gSPDisplayList((*gfx)++, &apProgChestBaseDL);
                return;
            case BOX_AP_USEFUL:
                gSPDisplayList((*gfx)++, &apUsefulChestBaseDL);
                return;
            case BOX_AP_FILLER:
                gSPDisplayList((*gfx)++, &apJunkChestBaseDL);
                return;
        }
    } else if (limbIndex == OBJECT_BOX_CHEST_LIMB_03) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        switch (curBox) {
            case BOX_NORMAL:
                gSPDisplayList((*gfx)++, &gBoxChestLidDL);
                return;
            case BOX_GILDED:
                gSPDisplayList((*gfx)++, &gBoxChestLidGildedDL);
                return;
            case BOX_KEY_BOSS:
                gSPDisplayList((*gfx)++, &gBoxChestLidOrnateDL);
                return;
            case BOX_KEY_SMALL:
                gSPDisplayList((*gfx)++, &keyChestLidDL);
                return;
            case BOX_STRAY_FAIRY:
                gSPDisplayList((*gfx)++, &fairyChestLidDL);
                return;
            case BOX_HEART:
                gSPDisplayList((*gfx)++, &heartChestLidDL);
                return;
            case BOX_SKULL_TOKEN:
                gSPDisplayList((*gfx)++, &spiderChestLidDL);
                return;
            case BOX_AP_PROG:
                gSPDisplayList((*gfx)++, &apProgChestLidDL);
                return;
            case BOX_AP_USEFUL:
                gSPDisplayList((*gfx)++, &apUsefulChestLidDL);
                return;
            case BOX_AP_FILLER:
                gSPDisplayList((*gfx)++, &apJunkChestLidDL);
                return;
        }
    }
}