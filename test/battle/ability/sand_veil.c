#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("ABILITY: Sand Veil prevents damage from sandstorm")
{
    GIVEN {
        PLAYER(SPECIES_CACNEA) { Ability(ABILITY_SAND_VEIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SANDSTORM); }
        TURN {}
    } SCENE {
        NONE_OF { HP_BAR(player); }
    }
}

SINGLE_BATTLE_TEST("ABILITY: Sand Veil increases evasion during sandstorm")
{
    PASSES_RANDOMLY(4, 5, RNG_ACCURACY);
    GIVEN {
        ASSUME(GetMoveAccuracy(MOVE_POUND) == 100);
        PLAYER(SPECIES_SANDSHREW) { Ability(ABILITY_SAND_VEIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SANDSTORM); }
        TURN { MOVE(opponent, MOVE_POUND); }
    } SCENE {
        HP_BAR(player);
    }
}

SINGLE_BATTLE_TEST("Sand Veil doesn't increase evasion if Cloud Nine/Air Lock is on the field")
{
    PASSES_RANDOMLY(5, 5, RNG_ACCURACY);
    GIVEN {
        ASSUME(GetMoveAccuracy(MOVE_POUND) == 100);
        PLAYER(SPECIES_SANDSHREW) { Ability(ABILITY_SAND_VEIL); }
        OPPONENT(SPECIES_GOLDUCK) { Ability(ABILITY_CLOUD_NINE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SANDSTORM); }
        TURN { MOVE(opponent, MOVE_POUND); }
    } SCENE {
        HP_BAR(player);
    }
}

SINGLE_BATTLE_TEST("INNATE: Sand Veil prevents damage from sandstorm")
{
    GIVEN {
        PLAYER(SPECIES_CACNEA) { Ability(ABILITY_WATER_ABSORB); Innates(ABILITY_SAND_VEIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SANDSTORM); }
        TURN {}
    } SCENE {
        NONE_OF { HP_BAR(player); }
    }
}

SINGLE_BATTLE_TEST("INNATE: Sand Veil increases evasion during sandstorm")
{
    PASSES_RANDOMLY(4, 5, RNG_ACCURACY);
    GIVEN {
        ASSUME(GetMoveAccuracy(MOVE_POUND) == 100);
        PLAYER(SPECIES_SANDSHREW) { Ability(ABILITY_SAND_RUSH); Innates(ABILITY_SAND_VEIL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SANDSTORM); }
        TURN { MOVE(opponent, MOVE_POUND); }
    } SCENE {
        HP_BAR(player);
    }
}
