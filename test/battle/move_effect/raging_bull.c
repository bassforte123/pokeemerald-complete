#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_RAGING_BULL) == EFFECT_RAGING_BULL);
    ASSUME(GetMoveEffect(MOVE_SNOWSCAPE) == EFFECT_WEATHER);
    ASSUME(GetMoveWeatherType(MOVE_SNOWSCAPE) == BATTLE_WEATHER_SNOW);
}

SINGLE_BATTLE_TEST("Move Raging Bull changes it's type depending on the Tauros Form")
{
    u16 speciesPlayer;
    u16 speciesOpponent;

    PARAMETRIZE { speciesPlayer = SPECIES_TAUROS_PALDEA_COMBAT; speciesOpponent = SPECIES_CHARIZARD; }
    PARAMETRIZE { speciesPlayer = SPECIES_TAUROS_PALDEA_BLAZE; speciesOpponent = SPECIES_BLASTOISE; }
    PARAMETRIZE { speciesPlayer = SPECIES_TAUROS_PALDEA_AQUA; speciesOpponent = SPECIES_VENUSAUR; }

    GIVEN {
        PLAYER(speciesPlayer);
        OPPONENT(speciesOpponent);
    } WHEN {
        TURN { MOVE(player, MOVE_RAGING_BULL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RAGING_BULL, player);
        HP_BAR(opponent);
        MESSAGE("It's not very effective…");
    }
}

#if MAX_MON_ITEMS > 1
SINGLE_BATTLE_TEST("Raging Bull doesn't remove Light Screen, Reflect and Aurora Veil if it misses (Items)")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_LIGHT_SCREEN; }
    PARAMETRIZE { move = MOVE_REFLECT; }
    PARAMETRIZE { move = MOVE_AURORA_VEIL; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Items(ITEM_PECHA_BERRY, ITEM_BRIGHT_POWDER); }
    } WHEN {
        TURN { MOVE(player, MOVE_SNOWSCAPE); MOVE(opponent, move); }
        TURN { MOVE(player, MOVE_RAGING_BULL, hit: FALSE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SNOWSCAPE, player);
        ANIMATION(ANIM_TYPE_MOVE, move, opponent);
        NONE_OF {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_RAGING_BULL, player);
            MESSAGE("The wall shattered!");
            HP_BAR(opponent);
        }
    }
}
#endif
