#include "global.h"
#include "test/battle.h"

#if MAX_MON_ITEMS > 1
// Generally one item activation per timing window.
SINGLE_BATTLE_TEST("Multi - IsOnSwitchInFirstTurnActivation")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_ORAN_BERRY, ITEM_PECHA_BERRY); HP(20); MaxHP(100); Status1(STATUS1_POISON); }
        OPPONENT(SPECIES_WOBBUFFET){ Items(ITEM_BERSERK_GENE, ITEM_PERSIM_BERRY); }
    } WHEN {
        TURN { }
    } SCENE {
        // Since only one item activates per timing window, both battlers activate one item on initial switch-in then one more after their turns.
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        MESSAGE("Wobbuffet restored its health using its Oran Berry!");
        HP_BAR(player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Using Berserk Gene, the Attack of the opposing Wobbuffet sharply rose!");
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        MESSAGE("Wobbuffet's Pecha Berry cured its poison!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        MESSAGE("The opposing Wobbuffet's Persim Berry snapped it out of its confusion!");
    }
}

SINGLE_BATTLE_TEST("Multi - Life Orb and Shell Bell stack")
{
    u32 maxHp, heldItem1, heldItem2;
    PARAMETRIZE {heldItem1 = ITEM_LIFE_ORB; heldItem2 = ITEM_SHELL_BELL; maxHp = 50; } // Equal heal and damage = no effect
    PARAMETRIZE {heldItem1 = ITEM_LIFE_ORB; heldItem2 = ITEM_SHELL_BELL; maxHp = 20; } // Greater healing = Shell Bell
    PARAMETRIZE {heldItem1 = ITEM_LIFE_ORB; heldItem2 = ITEM_SHELL_BELL; maxHp = 80; } // Greater damage = Life Orb
    PARAMETRIZE {heldItem1 = ITEM_SHELL_BELL; heldItem2 = ITEM_LIFE_ORB; maxHp = 50; } // Equal heal and damage = no effect
    PARAMETRIZE {heldItem1 = ITEM_SHELL_BELL; heldItem2 = ITEM_LIFE_ORB; maxHp = 20; } // Greater healing = Shell Bell
    PARAMETRIZE {heldItem1 = ITEM_SHELL_BELL; heldItem2 = ITEM_LIFE_ORB; maxHp = 80; } // Greater damage = Life Orb

    GIVEN {
        ASSUME(GetMoveEffect(MOVE_DRAGON_RAGE) == EFFECT_FIXED_HP_DAMAGE);
        ASSUME(GetMoveFixedHPDamage(MOVE_DRAGON_RAGE) == 40);
        PLAYER(SPECIES_WOBBUFFET) { Items(heldItem1, heldItem2); HP(10); MaxHP(maxHp); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, player);
        if (maxHp == 50) // No Effect
        {
            NONE_OF {
                HP_BAR(player);
            }
        }
        else if (maxHp == 20) // Shell Bell
        {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
            MESSAGE("Wobbuffet restored a little HP using its Shell Bell!");
            HP_BAR(player);
        }
        else if (maxHp == 100) // Life Orb
        {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
            MESSAGE("Wobbuffet was hurt by its Life Orb!");
            HP_BAR(player);
        }
    } THEN {
        EXPECT_EQ(player->hp, 10 + 5 - (maxHp/10));
    }
}

DOUBLE_BATTLE_TEST("Multi - Unburden only activates partial effect if more than one item is held")
{
    // Unburden gives a 2x speed boost if the user has no held item

    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { Items(ITEM_GREAT_BALL, ITEM_SHELL_BELL); Ability(ABILITY_UNBURDEN); Speed(10); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(19); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(12); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(16); }
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_KNOCK_OFF, target: playerLeft); }
        TURN { MOVE(opponentLeft, MOVE_KNOCK_OFF, target: playerLeft); }
        TURN { MOVE(opponentLeft, MOVE_KNOCK_OFF, target: playerLeft); }
    } SCENE {
        // No bonus, Driftlim goes last
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponentRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_KNOCK_OFF, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerLeft); // Driftlim
        // Partial bonus, Driftlim goes third
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponentRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerLeft); // Driftlim
        ANIMATION(ANIM_TYPE_MOVE, MOVE_KNOCK_OFF, opponentLeft);
        // Full bonus, Driftlim goes first
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerLeft); // Driftlim
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponentRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_KNOCK_OFF, opponentLeft);
    }
}

SINGLE_BATTLE_TEST("Multi - Acrobatics only activates partial effect if more than one item is held", s16 damage)
{
    u32 heldItem1, heldItem2;
    PARAMETRIZE { heldItem1 = ITEM_POTION; heldItem2 = ITEM_POTION; }
    PARAMETRIZE { heldItem1 = ITEM_POTION; heldItem2 = ITEM_NONE; }
    PARAMETRIZE { heldItem1 = ITEM_NONE; heldItem2 = ITEM_NONE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Items(heldItem1, heldItem2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ACROBATICS); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.33), results[1].damage); // Partial bonus
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2), results[2].damage); // Full bonus
    }
}

SINGLE_BATTLE_TEST("Multi - Leftovers and Black Sludge can stack")
{
    u32 item1, item2, species;

    PARAMETRIZE {item1 = ITEM_LEFTOVERS; item2 = ITEM_NONE; species = SPECIES_WOBBUFFET;}
    PARAMETRIZE {item1 = ITEM_LEFTOVERS; item2 = ITEM_BLACK_SLUDGE; species = SPECIES_WOBBUFFET;}
    PARAMETRIZE {item1 = ITEM_LEFTOVERS; item2 = ITEM_BLACK_SLUDGE; species = SPECIES_GRIMER;}
    PARAMETRIZE {item1 = ITEM_NONE; item2 = ITEM_LEFTOVERS; species = SPECIES_WOBBUFFET;}
    PARAMETRIZE {item1 = ITEM_BLACK_SLUDGE; item2 = ITEM_LEFTOVERS; species = SPECIES_WOBBUFFET;}
    PARAMETRIZE {item1 = ITEM_BLACK_SLUDGE; item2 = ITEM_LEFTOVERS; species = SPECIES_GRIMER;}

    GIVEN {
        PLAYER(species) { Items(item1, item2); HP(50); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        if((item1 == ITEM_BLACK_SLUDGE || item2 == ITEM_BLACK_SLUDGE) && species != SPECIES_GRIMER) //Black Sludge damages
            MESSAGE("Wobbuffet was hurt by the Black Sludge!");
        else if ((item1 == ITEM_BLACK_SLUDGE || item2 == ITEM_BLACK_SLUDGE) && species == SPECIES_GRIMER) //Black Sludge heals
            MESSAGE("Grimer restored a little HP using its Black Sludge!");
        else
            MESSAGE("Wobbuffet restored a little HP using its Leftovers!");
    } THEN {
        if((item1 == ITEM_BLACK_SLUDGE || item2 == ITEM_BLACK_SLUDGE) && species != SPECIES_GRIMER)
            EXPECT_EQ(player->hp, 44); //Black Sludge damage + Leftovers heal
        else if ((item1 == ITEM_BLACK_SLUDGE || item2 == ITEM_BLACK_SLUDGE) && species == SPECIES_GRIMER)
            EXPECT_EQ(player->hp, 62); //Black Sludge + Leftovers heal
        else
            EXPECT_EQ(player->hp, 56); // Leftovers heal
    }
}

SINGLE_BATTLE_TEST("Multi - Metronome, Expert Belt, and Life Orb stack")
{
    s16 damage[9];

    GIVEN {
        PLAYER(SPECIES_GOLEM) { Items(ITEM_LIFE_ORB, ITEM_EXPERT_BELT); }
        OPPONENT(SPECIES_WOBBUFFET); { }
        OPPONENT(SPECIES_WOBBUFFET) { Items(ITEM_METRONOME, ITEM_EXPERT_BELT); }
        OPPONENT(SPECIES_WOBBUFFET) { Items(ITEM_METRONOME, ITEM_LIFE_ORB); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); MOVE(player, MOVE_BESTOW);}
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); MOVE(player, MOVE_BESTOW);}
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); }
        TURN { SWITCH(opponent, 1); }
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); }
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); }
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); }
        TURN { SWITCH(opponent, 2); }
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); }
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); }
        TURN { MOVE(opponent, MOVE_BULLET_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Base damage
        HP_BAR(player, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BESTOW, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Expert Belt
        HP_BAR(player, captureDamage: &damage[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BESTOW, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Expert Belt + Life Orb
        HP_BAR(player, captureDamage: &damage[2]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Expert Belt + Metronome(0)
        HP_BAR(player, captureDamage: &damage[3]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Expert Belt + Metronome(1)
        HP_BAR(player, captureDamage: &damage[4]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Expert Belt + Metronome(2)
        HP_BAR(player, captureDamage: &damage[5]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Life Orb + Metronome(0)
        HP_BAR(player, captureDamage: &damage[6]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Life Orb + Metronome(1)
        HP_BAR(player, captureDamage: &damage[7]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BULLET_PUNCH, opponent); //Expert Belt + Metronome(2)
        HP_BAR(player, captureDamage: &damage[8]);

    } THEN {
        EXPECT_MUL_EQ(damage[0], UQ_4_12(1.2), damage[1]); //Expert Belt
        EXPECT_MUL_EQ(damage[1], UQ_4_12(1.3), damage[2]); //Expert Belt + Life Orb
        EXPECT_MUL_EQ(damage[1], UQ_4_12(1), damage[3]); //Expert Belt + Metronome(0)
        EXPECT_MUL_EQ(damage[3], UQ_4_12(1.2), damage[4]); //Expert Belt + Metronome(1)
        EXPECT_MUL_EQ(damage[3], UQ_4_12(1.4), damage[5]); //Expert Belt + Metronome(2)
        EXPECT_MUL_EQ(damage[0], UQ_4_12(1.3), damage[6]); //Life Orb + Metronome(0)
        EXPECT_MUL_EQ(damage[6], UQ_4_12(1.2), damage[7]); //Life Orb + Metronome(1)
        EXPECT_MUL_EQ(damage[6], UQ_4_12(1.4), damage[8]); //Life Orb + Metronome(2)
    }
}

SINGLE_BATTLE_TEST("Multi - Burn Orb and Toxic Orb don't crash")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_TOXIC_ORB, ITEM_FLAME_ORB); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        MESSAGE("Wobbuffet was badly poisoned!"); // Toxic Orb has priority
        STATUS_ICON(player, badPoison: TRUE);
    }
}

SINGLE_BATTLE_TEST("Multi - OnTargetAfterHit Air Balloon popping has the highest priority, Rocky Helmet has the lowest")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_ROCKY_HELMET, ITEM_AIR_BALLOON); }
        OPPONENT(SPECIES_WOBBUFFET){ Items(ITEM_ABSORB_BULB, ITEM_AIR_BALLOON); }
        OPPONENT(SPECIES_WOBBUFFET){ Items(ITEM_LUMINOUS_MOSS, ITEM_ROCKY_HELMET); }
    } WHEN {
        TURN { MOVE(player, MOVE_AQUA_JET); MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_AQUA_JET); MOVE(opponent, MOVE_SCRATCH); }
        TURN { SWITCH(opponent, 1); MOVE(player, MOVE_AQUA_JET); }
        TURN { MOVE(player, MOVE_AQUA_JET); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AQUA_JET, player);
        MESSAGE("The opposing Wobbuffet's Air Balloon popped!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        MESSAGE("Wobbuffet's Air Balloon popped!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AQUA_JET, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Using Absorb Bulb, the Sp. Atk of the opposing Wobbuffet rose!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        HP_BAR(opponent);
        MESSAGE("The opposing Wobbuffet was hurt by Wobbuffet's Rocky Helmet!");
        //switch
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AQUA_JET, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Using Luminous Moss, the Sp. Def of the opposing Wobbuffet rose!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AQUA_JET, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        HP_BAR(player);
        MESSAGE("Wobbuffet was hurt by the opposing Wobbuffet's Rocky Helmet!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        HP_BAR(opponent);
        MESSAGE("The opposing Wobbuffet was hurt by Wobbuffet's Rocky Helmet!");
    } THEN {
        EXPECT(player->items[0] == ITEM_ROCKY_HELMET);
        EXPECT(player->items[1] == ITEM_NONE);
        EXPECT(opponent->items[0] == ITEM_NONE);
        EXPECT(opponent->items[1] == ITEM_ROCKY_HELMET);
    }
}

SINGLE_BATTLE_TEST("Multi - OnTargetAfterHit general item check")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_CELL_BATTERY, ITEM_ABSORB_BULB); }
        OPPONENT(SPECIES_WOBBUFFET){ Items(ITEM_SNOWBALL, ITEM_JABOCA_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET){ Items(ITEM_SNOWBALL, ITEM_JABOCA_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_AQUA_JET); MOVE(opponent, MOVE_AQUA_JET); }
        TURN { MOVE(player, MOVE_ICY_WIND); MOVE(opponent, MOVE_THUNDERSHOCK); }
        TURN { SWITCH(opponent, 1); MOVE(player, MOVE_ICY_WIND); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AQUA_JET, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        HP_BAR(player);
        MESSAGE("Wobbuffet was hurt by the opposing Wobbuffet's Jaboca Berry!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AQUA_JET, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Using Absorb Bulb, the Sp. Atk of Wobbuffet rose!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ICY_WIND, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Using Snowball, the Attack of the opposing Wobbuffet rose!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDERSHOCK, opponent);     
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Using Cell Battery, the Attack of Wobbuffet rose!");
        //switch
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ICY_WIND, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Using Snowball, the Attack of the opposing Wobbuffet rose!");
    } THEN {
        EXPECT(player->items[0] == ITEM_NONE);
        EXPECT(player->items[1] == ITEM_NONE);
        EXPECT(opponent->items[0] == ITEM_NONE);
        EXPECT(opponent->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Multi - onAttackerAfterHit first item takes priority but only if it activates")
{
    PASSES_RANDOMLY(10, 100, RNG_HOLD_EFFECT_FLINCH);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_KINGS_ROCK, ITEM_THROAT_SPRAY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_VOICE, player);
        NONE_OF {
            MESSAGE("Using Throat Spray, the Sp. Atk of Wobbuffet rose!");
        }
        MESSAGE("The opposing Wobbuffet flinched and couldn't move!");
        NONE_OF {
            MESSAGE("Using Throat Spray, the Sp. Atk of Wobbuffet rose!");
        }
    }
}

//onEffect appears to not have a 1 item limit due to more complicated activation logic in the battlescripts
SINGLE_BATTLE_TEST("Multi - onEffect effects do not conflict")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_ELECTRIC_SEED, ITEM_ROOM_SERVICE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TRICK_ROOM); MOVE(opponent, MOVE_ELECTRIC_TERRAIN); }
        TURN { SWITCH(player, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Using Electric Seed, the Defense of Wobbuffet rose!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Using Room Service, the Speed of Wobbuffet fell!");
    }
}

#if B_HELD_ITEM_CATEGORIZATION == TRUE
//If B_HELD_ITEM_CATEGORIZATION is set, pokeball should only be able to go into the specified slot even if another slot is available. 
WILD_BATTLE_TEST("Multi - Ball Fetch follows Item Categorization")
{
    u32 item;
    PARAMETRIZE {item = ITEM_NONE; }
    PARAMETRIZE {item = ITEM_NUGGET; }

    GIVEN {
        PLAYER(SPECIES_YAMPER) { Ability(ABILITY_BALL_FETCH); Items(item); }
        OPPONENT(SPECIES_METAGROSS);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_POKE_BALL, WITH_RNG(RNG_BALLTHROW_SHAKE, MAX_u16) );}
        TURN {}
    } SCENE {
        if (item == ITEM_NONE)
            ABILITY_POPUP(player, ABILITY_BALL_FETCH);
        else
            NOT ABILITY_POPUP(player, ABILITY_BALL_FETCH);
    } THEN {
        if (item == ITEM_NONE)
            EXPECT_EQ(player->items[0], ITEM_POKE_BALL);
        else
            EXPECT_EQ(player->items[0], item);
    }
}
#endif

#if B_MULTI_ITEM_ORDER == 0
WILD_BATTLE_TEST("Multi - B_MULTI_ITEM_ORDER targets latest to earliest item slot")
{
    u32 move;
    PARAMETRIZE { move = MOVE_THIEF; }
    PARAMETRIZE { move = MOVE_COVET; }
    PARAMETRIZE { move = MOVE_KNOCK_OFF; }
    PARAMETRIZE { move = MOVE_BUG_BITE; }
    PARAMETRIZE { move = MOVE_PLUCK; }
    PARAMETRIZE { move = MOVE_INCINERATE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Items(ITEM_ORAN_BERRY, ITEM_PECHA_BERRY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(opponent->items[1], ITEM_NONE);
    }
}
#endif

// Note, there's a catch in GetSlot that forces tests to Item Order 0 to keep tests from breaking.
// Disable that catch to use this test.
#if B_MULTI_ITEM_ORDER == 1
WILD_BATTLE_TEST("Multi - B_MULTI_ITEM_ORDER targets latest to earliest item slot")
{
    u32 move;
    PARAMETRIZE { move = MOVE_THIEF; }
    PARAMETRIZE { move = MOVE_COVET; }
    PARAMETRIZE { move = MOVE_KNOCK_OFF; }
    PARAMETRIZE { move = MOVE_BUG_BITE; }
    PARAMETRIZE { move = MOVE_PLUCK; }
    PARAMETRIZE { move = MOVE_INCINERATE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Items(ITEM_ORAN_BERRY, ITEM_PECHA_BERRY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(opponent->items[0], ITEM_NONE);
    }
}
#endif

#endif

