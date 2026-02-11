#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Sticky Hold prevents item theft")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_THIEF) == EFFECT_STEAL_ITEM);
        PLAYER(SPECIES_URSALUNA) { Item(ITEM_NONE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STICKY_HOLD); Item(ITEM_LIFE_ORB); }
    } WHEN {
        TURN { MOVE(player, MOVE_THIEF); }
    } SCENE {
        MESSAGE("Ursaluna used Thief!");
        ABILITY_POPUP(opponent, ABILITY_STICKY_HOLD);
        MESSAGE("The opposing Gastrodon's Sticky Hold made Thief ineffective!");
    }
}

SINGLE_BATTLE_TEST("Sticky Hold prevents Incinerate from destroying berries")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_INCINERATE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STICKY_HOLD); Item(ITEM_CHERI_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_INCINERATE); }
    } THEN {
        EXPECT_EQ(gBattleMons[B_POSITION_OPPONENT_LEFT].item, ITEM_CHERI_BERRY);
    }
}

SINGLE_BATTLE_TEST("Sticky Hold prevents Incinerate from destroying gems")
{
    GIVEN {
        WITH_CONFIG(CONFIG_INCINERATE_GEMS, GEN_6);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_INCINERATE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STICKY_HOLD); Item(ITEM_GHOST_GEM); }
    } WHEN {
        TURN { MOVE(player, MOVE_INCINERATE); }
    } THEN {
        EXPECT_EQ(gBattleMons[B_POSITION_OPPONENT_LEFT].item, ITEM_GHOST_GEM);
    }
}

#if MAX_MON_TRAITS > 1
SINGLE_BATTLE_TEST("Sticky Hold prevents item theft (Traits)")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_THIEF) == EFFECT_STEAL_ITEM);
        PLAYER(SPECIES_URSALUNA) { Item(ITEM_NONE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STORM_DRAIN); Innates(ABILITY_STICKY_HOLD); Item(ITEM_LIFE_ORB); }
    } WHEN {
        TURN { MOVE(player, MOVE_THIEF); }
    } SCENE {
        MESSAGE("Ursaluna used Thief!");
        ABILITY_POPUP(opponent, ABILITY_STICKY_HOLD);
        MESSAGE("The opposing Gastrodon's Sticky Hold made Thief ineffective!");
    }
}

SINGLE_BATTLE_TEST("Sticky Hold prevents Incinerate from destroying berries (Traits)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_INCINERATE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STORM_DRAIN); Innates(ABILITY_STICKY_HOLD); Item(ITEM_CHERI_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_INCINERATE); }
    } THEN {
        EXPECT_EQ(gBattleMons[B_POSITION_OPPONENT_LEFT].item, ITEM_CHERI_BERRY);
    }
}

SINGLE_BATTLE_TEST("Sticky Hold prevents Incinerate from destroying gems (Traits)")
{
    GIVEN {
        WITH_CONFIG(CONFIG_INCINERATE_GEMS, GEN_6);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_INCINERATE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STORM_DRAIN); Innates(ABILITY_STICKY_HOLD); Item(ITEM_GHOST_GEM); }
    } WHEN {
        TURN { MOVE(player, MOVE_INCINERATE); }
    } THEN {
        EXPECT_EQ(gBattleMons[B_POSITION_OPPONENT_LEFT].item, ITEM_GHOST_GEM);
    }
}
#endif

#if MAX_MON_ITEMS > 1
SINGLE_BATTLE_TEST("Sticky Hold prevents item theft (Multi)")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_THIEF) == EFFECT_STEAL_ITEM);
        PLAYER(SPECIES_URSALUNA) { Items(ITEM_PECHA_BERRY, ITEM_NONE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STICKY_HOLD); Items(ITEM_PECHA_BERRY, ITEM_LIFE_ORB); }
    } WHEN {
        TURN { MOVE(player, MOVE_THIEF); }
    } SCENE {
        MESSAGE("Ursaluna used Thief!");
        ABILITY_POPUP(opponent, ABILITY_STICKY_HOLD);
        MESSAGE("The opposing Gastrodon's Sticky Hold made Thief ineffective!");
    }
}
SINGLE_BATTLE_TEST("Sticky Hold prevents Incinerate from destroying berries (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_INCINERATE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STICKY_HOLD); Items(ITEM_NUGGET, ITEM_CHERI_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_INCINERATE); }
    } THEN {
        EXPECT_EQ(gBattleMons[B_POSITION_OPPONENT_LEFT].item, ITEM_CHERI_BERRY);
    }
}

SINGLE_BATTLE_TEST("Sticky Hold prevents Incinerate from destroying gems (Multi)")
{
    GIVEN {
        WITH_CONFIG(CONFIG_INCINERATE_GEMS, GEN_6);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_INCINERATE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STICKY_HOLD); Items(ITEM_GREAT_BALL, ITEM_GHOST_GEM); }
    } WHEN {
        TURN { MOVE(player, MOVE_INCINERATE); }
    } THEN {
        EXPECT_EQ(gBattleMons[B_POSITION_OPPONENT_LEFT].item, ITEM_GHOST_GEM);
    }
}
#endif
