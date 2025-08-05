#include "global.h"
#include "test/battle.h"

static const u16 sMoveItemTable[][18] =
{
    { TYPE_NORMAL,   MOVE_SCRATCH,         ITEM_SILK_SCARF },
    { TYPE_FIGHTING, MOVE_KARATE_CHOP,     ITEM_BLACK_BELT },
    { TYPE_FLYING,   MOVE_WING_ATTACK,     ITEM_SHARP_BEAK },
    { TYPE_POISON,   MOVE_POISON_STING,    ITEM_POISON_BARB },
    { TYPE_GROUND,   MOVE_MUD_SHOT,        ITEM_SOFT_SAND },
    { TYPE_ROCK,     MOVE_ROCK_THROW,      ITEM_HARD_STONE },
    { TYPE_BUG,      MOVE_BUG_BITE,        ITEM_SILVER_POWDER },
    { TYPE_GHOST,    MOVE_SHADOW_PUNCH,    ITEM_SPELL_TAG },
    { TYPE_STEEL,    MOVE_METAL_CLAW,      ITEM_METAL_COAT },
    { TYPE_FIRE,     MOVE_EMBER,           ITEM_CHARCOAL },
    { TYPE_WATER,    MOVE_WATER_GUN,       ITEM_MYSTIC_WATER },
    { TYPE_GRASS,    MOVE_VINE_WHIP,       ITEM_MIRACLE_SEED },
    { TYPE_ELECTRIC, MOVE_THUNDER_SHOCK,   ITEM_MAGNET },
    { TYPE_PSYCHIC,  MOVE_CONFUSION,       ITEM_TWISTED_SPOON },
    { TYPE_ICE,      MOVE_AURORA_BEAM,     ITEM_NEVER_MELT_ICE },
    { TYPE_DRAGON,   MOVE_DRAGON_BREATH,   ITEM_DRAGON_FANG },
    { TYPE_DARK,     MOVE_BITE,            ITEM_BLACK_GLASSES },
    { TYPE_FAIRY,    MOVE_DISARMING_VOICE, ITEM_FAIRY_FEATHER },
};

SINGLE_BATTLE_TEST("Type-enhancing items increase the base power of moves by 20%", s16 damage)
{
    u32 move = 0, item = 0, type = 0;

    for (u32 j = 0; j < ARRAY_COUNT(sMoveItemTable); j++) {
        PARAMETRIZE { type = sMoveItemTable[j][0]; move = sMoveItemTable[j][1]; item = ITEM_NONE; }
        PARAMETRIZE { type = sMoveItemTable[j][0]; move = sMoveItemTable[j][1]; item = sMoveItemTable[j][2]; }
    }

    GIVEN {
        ASSUME(GetMovePower(move) > 0);
        if (item != ITEM_NONE) {
            ASSUME(GetItemHoldEffect(item) == HOLD_EFFECT_TYPE_POWER);
            ASSUME(GetItemSecondaryId(item) == type);
        }
        PLAYER(SPECIES_WOBBUFFET) { Item(item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        for (u32 j = 0; j < ARRAY_COUNT(sMoveItemTable); j++) {
            if (I_TYPE_BOOST_POWER >= GEN_4)
                EXPECT_MUL_EQ(results[j*2].damage, Q_4_12(1.2), results[(j*2)+1].damage);
            else
                EXPECT_MUL_EQ(results[j*2].damage, Q_4_12(1.1), results[(j*2)+1].damage);
        }
    }
}

SINGLE_BATTLE_TEST("Type-enhancing items increase the base power of moves by 20% (Multi)", s16 damage)
{
    u32 move = 0, item = 0, type = 0;

    for (u32 j = 0; j < ARRAY_COUNT(sMoveItemTable); j++) {
        PARAMETRIZE { type = sMoveItemTable[j][0]; move = sMoveItemTable[j][1]; item = ITEM_NONE; }
        PARAMETRIZE { type = sMoveItemTable[j][0]; move = sMoveItemTable[j][1]; item = sMoveItemTable[j][2]; }
    }

    GIVEN {
        ASSUME(GetMovePower(move) > 0);
        if (item != ITEM_NONE) {
            ASSUME(GetItemHoldEffect(item) == HOLD_EFFECT_TYPE_POWER);
            ASSUME(GetItemSecondaryId(item) == type);
        }
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_BLK_APRICORN, item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        for (u32 j = 0; j < ARRAY_COUNT(sMoveItemTable); j++) {
            if (I_TYPE_BOOST_POWER >= GEN_4)
                EXPECT_MUL_EQ(results[j*2].damage, Q_4_12(1.2), results[(j*2)+1].damage);
            else
                EXPECT_MUL_EQ(results[j*2].damage, Q_4_12(1.1), results[(j*2)+1].damage);
        }
    }
}

SINGLE_BATTLE_TEST("Flying Press activates one damage reduction berry per hit (Multi)")
{
    s16 damage[3];

    GIVEN {
        ASSUME(gItemsInfo[ITEM_CHOPLE_BERRY].holdEffect == HOLD_EFFECT_RESIST_BERRY);
        ASSUME(gItemsInfo[ITEM_CHOPLE_BERRY].holdEffectParam == TYPE_FIGHTING);
        ASSUME(gItemsInfo[ITEM_COBA_BERRY].holdEffect == HOLD_EFFECT_RESIST_BERRY);
        ASSUME(gItemsInfo[ITEM_COBA_BERRY].holdEffectParam == TYPE_FLYING);
        PLAYER(SPECIES_WOBBUFFET) { Attack(20); }
        OPPONENT(SPECIES_SHIFTRY) { Items(ITEM_CHOPLE_BERRY, ITEM_COBA_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_FLYING_PRESS); }
        TURN { MOVE(player, MOVE_FLYING_PRESS); }
        TURN { MOVE(player, MOVE_FLYING_PRESS); }
    } SCENE {
        MESSAGE("Wobbuffet used Flying Press!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        MESSAGE("The Chople Berry weakened the damage to the opposing Shiftry!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FLYING_PRESS, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        #if B_FLYING_PRESS_RESIST == FALSE
            MESSAGE("Wobbuffet used Flying Press!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_FLYING_PRESS, player);
            HP_BAR(opponent, captureDamage: &damage[1]);
        #endif
        #if B_FLYING_PRESS_RESIST == TRUE //Flying Berry only activates if enabled
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
            MESSAGE("The Coba Berry weakened the damage to the opposing Shiftry!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_FLYING_PRESS, player);
            HP_BAR(opponent, captureDamage: &damage[1]);
            MESSAGE("Wobbuffet used Flying Press!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_FLYING_PRESS, player);
            HP_BAR(opponent, captureDamage: &damage[2]);
        #endif
    } THEN {
        EXPECT_EQ(opponent->items[0], ITEM_NONE);
        #if B_FLYING_PRESS_RESIST == FALSE
            EXPECT_EQ(opponent->items[1], ITEM_COBA_BERRY);
            EXPECT_MUL_EQ(damage[0], Q_4_12(2), damage[1]);
        #endif
        #if B_FLYING_PRESS_RESIST == TRUE
            EXPECT_EQ(opponent->items[1], ITEM_NONE);
            EXPECT_EQ(damage[0], damage[1]);
            EXPECT_MUL_EQ(damage[0], Q_4_12(2), damage[2]);
        #endif
    }
}
