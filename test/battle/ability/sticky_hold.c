#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Sticky Hold prevents item theft")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_THIEF) == EFFECT_STEAL_ITEM);
        PLAYER(SPECIES_URSALUNA) { Items(ITEM_NONE); }
        OPPONENT(SPECIES_GASTRODON) { Ability(ABILITY_STICKY_HOLD); Items(ITEM_LIFE_ORB); }
    } WHEN {
        TURN { MOVE(player, MOVE_THIEF); }
    } SCENE {
        MESSAGE("Ursaluna used Thief!");
        ABILITY_POPUP(opponent, ABILITY_STICKY_HOLD);
        MESSAGE("The opposing Gastrodon's Sticky Hold made Thief ineffective!");
    }
}

#if MAX_MON_TRAITS > 1
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
#endif
