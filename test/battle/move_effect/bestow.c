#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Bestow transfers its held item to the target")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SITRUS_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } THEN {
        EXPECT(player->items[0] == ITEM_NONE);
        EXPECT(opponent->items[0] == ITEM_SITRUS_BERRY);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the user has no held item")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[0] == ITEM_NONE);
        EXPECT(opponent->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the target already has a held item")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SITRUS_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_LUM_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[0] == ITEM_SITRUS_BERRY);
        EXPECT(opponent->items[0] == ITEM_LUM_BERRY);
    }
}

#include "mail.h"
SINGLE_BATTLE_TEST("Bestow fails if the user is holding Mail")
{
    GIVEN {
        ASSUME(ItemIsMail(ITEM_ORANGE_MAIL));
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_ORANGE_MAIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[0] == ITEM_ORANGE_MAIL);
        EXPECT(opponent->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the user's held item is a Mega Stone")
{
    GIVEN {
        PLAYER(SPECIES_BLAZIKEN) { Item(ITEM_BLAZIKENITE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[0] == ITEM_BLAZIKENITE);
        EXPECT(opponent->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the user's held item is a Z-Crystal")
{
    GIVEN {
        ASSUME(GetItemHoldEffect(ITEM_FIGHTINIUM_Z) == HOLD_EFFECT_Z_CRYSTAL);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_FIGHTINIUM_Z); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[0] == ITEM_FIGHTINIUM_Z);
        EXPECT(opponent->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the target is behind a Substitute (Gen 6+)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SITRUS_BERRY); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUBSTITUTE); MOVE(player, MOVE_BESTOW); }
    } SCENE {
        if (B_UPDATED_MOVE_FLAGS >= GEN_6) {
            NOT MESSAGE("But it failed!");
        } else {
            MESSAGE("But it failed!");
        }
    } THEN {
        if (B_UPDATED_MOVE_FLAGS >= GEN_6) {
            EXPECT(player->items[0] == ITEM_NONE);
            EXPECT(opponent->items[0] == ITEM_SITRUS_BERRY);
        } else {
            EXPECT(player->items[0] == ITEM_SITRUS_BERRY);
            EXPECT(opponent->items[0] == ITEM_NONE);
        }
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the user's held item changes its form")
{
    GIVEN {
        PLAYER(SPECIES_GIRATINA_ORIGIN) { Item(ITEM_GRISEOUS_CORE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[0] == ITEM_GRISEOUS_CORE);
        EXPECT(opponent->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Bestow transfers its held item to the target (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items( ITEM_NONE, ITEM_SITRUS_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } THEN {
        EXPECT(player->items[1] == ITEM_NONE);
        EXPECT(opponent->items[1] == ITEM_SITRUS_BERRY);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the target already has a held item (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items( ITEM_NONE, ITEM_SITRUS_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET) { Items( ITEM_NONE, ITEM_LUM_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[1] == ITEM_SITRUS_BERRY);
        EXPECT(opponent->items[1] == ITEM_LUM_BERRY);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the user is holding Mail (Multi)")
{
    GIVEN {
        ASSUME(ItemIsMail(ITEM_ORANGE_MAIL));
        PLAYER(SPECIES_WOBBUFFET) { Items( ITEM_NONE, ITEM_ORANGE_MAIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[1] == ITEM_ORANGE_MAIL);
        EXPECT(opponent->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the user's held item is a Mega Stone (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_BLAZIKEN) { Items( ITEM_NONE, ITEM_BLAZIKENITE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[1] == ITEM_BLAZIKENITE);
        EXPECT(opponent->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the user's held item is a Z-Crystal (Multi)")
{
    GIVEN {
        ASSUME(GetItemHoldEffect(ITEM_FIGHTINIUM_Z) == HOLD_EFFECT_Z_CRYSTAL);
        PLAYER(SPECIES_WOBBUFFET) { Items( ITEM_NONE, ITEM_FIGHTINIUM_Z); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[1] == ITEM_FIGHTINIUM_Z);
        EXPECT(opponent->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the target is behind a Substitute (Gen 6+) (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items( ITEM_NONE, ITEM_SITRUS_BERRY); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUBSTITUTE); MOVE(player, MOVE_BESTOW); }
    } SCENE {
        if (B_UPDATED_MOVE_FLAGS >= GEN_6) {
            NOT MESSAGE("But it failed!");
        } else {
            MESSAGE("But it failed!");
        }
    } THEN {
        if (B_UPDATED_MOVE_FLAGS >= GEN_6) {
            EXPECT(player->items[1] == ITEM_NONE);
            EXPECT(opponent->items[1] == ITEM_SITRUS_BERRY);
        } else {
            EXPECT(player->items[1] == ITEM_SITRUS_BERRY);
            EXPECT(opponent->items[1] == ITEM_NONE);
        }
    }
}

SINGLE_BATTLE_TEST("Bestow fails if the user's held item changes its form (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_GIRATINA_ORIGIN) { Items( ITEM_NONE, ITEM_GRISEOUS_CORE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BESTOW); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(player->items[1] == ITEM_GRISEOUS_CORE);
        EXPECT(opponent->items[1] == ITEM_NONE);
    }
}
