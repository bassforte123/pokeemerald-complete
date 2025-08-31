#include "global.h"
#include "test/battle.h"

ASSUMPTIONS{
    ASSUME(gItemsInfo[ITEM_IRON_BALL].holdEffect == HOLD_EFFECT_IRON_BALL);
}

SINGLE_BATTLE_TEST("Ground-type moves do neutral damage to non-grounded Flying types holding Iron Ball regardless of other typings") //gen5+ only
{
    ASSUME(B_IRON_BALL >= GEN_5);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SKARMORY) { Item(ITEM_IRON_BALL); };
    } WHEN {
        TURN { MOVE(player, MOVE_EARTHQUAKE); };
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, player);
        NONE_OF {
            MESSAGE("It's super effective!");
        }
    }
}

SINGLE_BATTLE_TEST("Ground-type moves do neutral damage to non-grounded Flying types holding Iron Ball regardless of other typings (Multi)") //gen5+ only
{
    ASSUME(B_IRON_BALL >= GEN_5);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SKARMORY) { Items(ITEM_ABILITY_PATCH, ITEM_IRON_BALL); };
    } WHEN {
        TURN { MOVE(player, MOVE_EARTHQUAKE); };
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, player);
        NONE_OF {
            MESSAGE("It's super effective!");
        }
    }
}

SINGLE_BATTLE_TEST("Iron Ball takes priority over Air Balloon (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIKACHU) { Items(ITEM_AIR_BALLOON, ITEM_IRON_BALL); };
    } WHEN {
        TURN { MOVE(player, MOVE_EARTHQUAKE); };
        TURN { MOVE(player, MOVE_EARTHQUAKE); };
    } SCENE {
        MESSAGE("The opposing Pikachu's Air Balloon was weighed down by its Iron Ball!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, player);
        NONE_OF {
            MESSAGE("The opposing Pikachu floats in the air with its Air Balloon!");
        }
        MESSAGE("It's super effective!");
        MESSAGE("The opposing Pikachu's Air Balloon popped!");
        MESSAGE("It's super effective!");
    } THEN {
        EXPECT(player->items[0] == ITEM_NONE);
    }
}
