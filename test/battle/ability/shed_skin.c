#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Shed Skin triggers 33% (Gen3, Gen5+) or 30% (Gen 4) of the time")
{
    u32 config, passes;
    PARAMETRIZE { config = GEN_3; passes = 33; }
    PARAMETRIZE { config = GEN_4; passes = 30; }
    PARAMETRIZE { config = GEN_5; passes = 33; }

    PASSES_RANDOMLY(passes, 100, RNG_SHED_SKIN);
    GIVEN {
        WITH_CONFIG(CONFIG_ABILITY_TRIGGER_CHANCE, config);
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ARBOK) { Status1(STATUS1_POISON); Ability(ABILITY_SHED_SKIN); }
    } WHEN {
        TURN;
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_SHED_SKIN);
        MESSAGE("The opposing Arbok's Shed Skin cured its poison problem!");
        STATUS_ICON(opponent, poison: FALSE);
    }
}

#if MAX_MON_TRAITS > 1
SINGLE_BATTLE_TEST("Shed Skin triggers 33% of the time (Traits)")
{
    if (B_ABILITY_TRIGGER_CHANCE == GEN_4)
        PASSES_RANDOMLY(30, 100, RNG_SHED_SKIN);
    else
        PASSES_RANDOMLY(33, 100, RNG_SHED_SKIN);
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ARBOK) { Status1(STATUS1_POISON); Ability(ABILITY_UNNERVE); Innates(ABILITY_SHED_SKIN); }
    } WHEN {
        TURN;
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_SHED_SKIN);
        MESSAGE("The opposing Arbok's Shed Skin cured its poison problem!");
        STATUS_ICON(opponent, poison: FALSE);
    }
}
#endif
