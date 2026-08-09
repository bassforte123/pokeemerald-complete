#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gItemsInfo[ITEM_LEPPA_BERRY].holdEffect == HOLD_EFFECT_RESTORE_PP);
}

SINGLE_BATTLE_TEST("Restore PP berry activates immediately on switch in")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LEPPA_BERRY); MovesWithPP({MOVE_SCRATCH, 0}, {MOVE_CELEBRATE, 20}); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(opponent, MOVE_POUND); MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_BERRY, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
    } THEN {
        EXPECT(player->item == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Forced Leppa Berry consumption restores a move at 0 PP before other missing PP")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FLING) == EFFECT_FLING);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LEPPA_BERRY); Moves(MOVE_FLING); }
        OPPONENT(SPECIES_WYNAUT) { MovesWithPP({MOVE_SCRATCH, 6}, {MOVE_CELEBRATE, 0}, {MOVE_POUND, 35}); }
    } WHEN {
        TURN { MOVE(player, MOVE_FLING); MOVE(opponent, MOVE_POUND); }
    } THEN {
        EXPECT_EQ(opponent->pp[0], 6);
        EXPECT_EQ(opponent->pp[1], 10);
    }
}

SINGLE_BATTLE_TEST("Forced Leppa Berry consumption restores the first move found missing PP when none are at 0")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FLING) == EFFECT_FLING);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LEPPA_BERRY); Moves(MOVE_FLING); }
        OPPONENT(SPECIES_WYNAUT) { MovesWithPP({MOVE_SCRATCH, 6}, {MOVE_CELEBRATE, 6}, {MOVE_POUND, 35}); }
    } WHEN {
        TURN { MOVE(player, MOVE_FLING); MOVE(opponent, MOVE_POUND); }
    } THEN {
        EXPECT_EQ(opponent->pp[0], 16);
        EXPECT_EQ(opponent->pp[1], 6);
    }
}

#if MAX_MON_ITEMS > 1
SINGLE_BATTLE_TEST("Restore PP berry activates immediately on switch in (Items)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_PECHA_BERRY, ITEM_LEPPA_BERRY); MovesWithPP({MOVE_SCRATCH, 0}, {MOVE_CELEBRATE, 20}); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(opponent, MOVE_POUND); MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_BERRY, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
    } THEN {
        EXPECT(player->items[1]== ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Forced Leppa Berry consumption restores a move at 0 PP before other missing PP (Items)")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FLING) == EFFECT_FLING);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NONE, ITEM_LEPPA_BERRY); Moves(MOVE_FLING); }
        OPPONENT(SPECIES_WYNAUT) { MovesWithPP({MOVE_SCRATCH, 6}, {MOVE_CELEBRATE, 0}, {MOVE_POUND, 35}); }
    } WHEN {
        TURN { MOVE(player, MOVE_FLING); MOVE(opponent, MOVE_POUND); }
    } THEN {
        EXPECT_EQ(opponent->pp[0], 6);
        EXPECT_EQ(opponent->pp[1], 10);
    }
}

SINGLE_BATTLE_TEST("Forced Leppa Berry consumption restores the first move found missing PP when none are at 0 (Items)")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FLING) == EFFECT_FLING);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NONE, ITEM_LEPPA_BERRY); Moves(MOVE_FLING); }
        OPPONENT(SPECIES_WYNAUT) { MovesWithPP({MOVE_SCRATCH, 6}, {MOVE_CELEBRATE, 6}, {MOVE_POUND, 35}); }
    } WHEN {
        TURN { MOVE(player, MOVE_FLING); MOVE(opponent, MOVE_POUND); }
    } THEN {
        EXPECT_EQ(opponent->pp[0], 16);
        EXPECT_EQ(opponent->pp[1], 6);
    }
}
#endif
