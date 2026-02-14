#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_GEAR_UP) == EFFECT_GEAR_UP);
}

SINGLE_BATTLE_TEST("Gear Up raises Attack and Sp. Attack of the user with Plus/Minus in singles")
{
    GIVEN {
        PLAYER(SPECIES_PLUSLE) { Ability(ABILITY_PLUS); }
        OPPONENT(SPECIES_MINUN) { Ability(ABILITY_MINUS); }
    } WHEN {
        TURN { MOVE(player, MOVE_GEAR_UP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GEAR_UP, player);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
    }
}

DOUBLE_BATTLE_TEST("Gear Up raises Attack and Sp. Attack of all Plus/Minus allies in doubles")
{
    GIVEN {
        PLAYER(SPECIES_PLUSLE) { Ability(ABILITY_PLUS); }
        PLAYER(SPECIES_MINUN) { Ability(ABILITY_MINUS); }
        OPPONENT(SPECIES_PLUSLE) { Ability(ABILITY_PLUS); }
        OPPONENT(SPECIES_MINUN) { Ability(ABILITY_MINUS); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_GEAR_UP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GEAR_UP, playerLeft);
    } THEN {
        EXPECT_EQ(playerLeft->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(playerLeft->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(playerRight->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(playerRight->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponentLeft->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponentLeft->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponentRight->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponentRight->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
    }
}

#if MAX_MON_TRAITS > 1
AI_DOUBLE_BATTLE_TEST("AI uses Gear Up (Traits)")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_POUND, MOVE_CELEBRATE); }
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_POUND, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_KLINKLANG) { Ability(ABILITY_CLEAR_BODY); Innates(ABILITY_PLUS); Moves(MOVE_GEAR_UP, MOVE_WATER_GUN, MOVE_POUND); }
        OPPONENT(SPECIES_KLINKLANG) { Ability(ABILITY_CLEAR_BODY); Innates(ABILITY_PLUS); Moves(MOVE_GEAR_UP, MOVE_WATER_GUN, MOVE_POUND); }
    } WHEN {
        TURN {  EXPECT_MOVE(opponentLeft, MOVE_GEAR_UP); }
    }
}
#endif
