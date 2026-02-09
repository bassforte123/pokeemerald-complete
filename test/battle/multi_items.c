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
        OPPONENT(SPECIES_WOBBUFFET) { Items(ITEM_LIFE_ORB, ITEM_METRONOME); }
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

static const u16 sMoveItemTable[][18] =
{
    { TYPE_NORMAL,   MOVE_SCRATCH,         ITEM_SILK_SCARF },
    { TYPE_FIGHTING, MOVE_KARATE_CHOP,     ITEM_BLACK_BELT },
    { TYPE_FLYING,   MOVE_WING_ATTACK,     ITEM_SHARP_BEAK },
    { TYPE_POISON,   MOVE_POISON_STING,    ITEM_POISON_BARB },
    { TYPE_GROUND,   MOVE_MUD_SHOT,        ITEM_SOFT_SAND },
    { TYPE_ROCK,     MOVE_ROCK_THROW,      ITEM_HARD_STONE },
    { TYPE_BUG,      MOVE_BUG_BITE,        ITEM_SILVER_POWDER },
    { TYPE_GHOST,    MOVE_SHADOW_PUNCH,    ITEM_SPELL_TAG },
    { TYPE_STEEL,    MOVE_METAL_CLAW,      ITEM_METAL_COAT },
    { TYPE_FIRE,     MOVE_EMBER,           ITEM_CHARCOAL },
    { TYPE_WATER,    MOVE_WATER_GUN,       ITEM_MYSTIC_WATER },
    { TYPE_GRASS,    MOVE_VINE_WHIP,       ITEM_MIRACLE_SEED },
    { TYPE_ELECTRIC, MOVE_THUNDER_SHOCK,   ITEM_MAGNET },
    { TYPE_PSYCHIC,  MOVE_CONFUSION,       ITEM_TWISTED_SPOON },
    { TYPE_ICE,      MOVE_AURORA_BEAM,     ITEM_NEVER_MELT_ICE },
    { TYPE_DRAGON,   MOVE_DRAGON_BREATH,   ITEM_DRAGON_FANG },
    { TYPE_DARK,     MOVE_BITE,            ITEM_BLACK_GLASSES },
    { TYPE_FAIRY,    MOVE_DISARMING_VOICE, ITEM_FAIRY_FEATHER },
};


SINGLE_BATTLE_TEST("Multi - Duplicate type-enhancing items can stack when enabled", s16 damage)
{
    u32 move = 0, item = 0, type = 0;
    bool16 dupe = FALSE;

    for (u32 j = 0; j < ARRAY_COUNT(sMoveItemTable); j++) {
        PARAMETRIZE { type = sMoveItemTable[j][0]; move = sMoveItemTable[j][1]; item = ITEM_NONE;             dupe = FALSE; }
        PARAMETRIZE { type = sMoveItemTable[j][0]; move = sMoveItemTable[j][1]; item = sMoveItemTable[j][2];  dupe = FALSE; }
        PARAMETRIZE { type = sMoveItemTable[j][0]; move = sMoveItemTable[j][1]; item = ITEM_NONE;             dupe = TRUE; }
        PARAMETRIZE { type = sMoveItemTable[j][0]; move = sMoveItemTable[j][1]; item = sMoveItemTable[j][2];  dupe = TRUE; }
    }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        ASSUME(GetMovePower(move) > 0);
        if (item != ITEM_NONE) {
            ASSUME(GetItemHoldEffect(item) == HOLD_EFFECT_TYPE_POWER);
            ASSUME(GetItemSecondaryId(item) == type);
        }
        PLAYER(SPECIES_WOBBUFFET) { Items(item, item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        for (u32 j = 0; j < ARRAY_COUNT(sMoveItemTable); j++) {
            if (I_TYPE_BOOST_POWER >= GEN_4)
            {
                EXPECT_MUL_EQ(results[j*4].damage, Q_4_12(1.2), results[(j*4)+1].damage);
                EXPECT_MUL_EQ(results[(j*4)+2].damage, Q_4_12(1.44), results[(j*4)+3].damage);
            }
            else
            {
                EXPECT_MUL_EQ(results[j*4].damage, Q_4_12(1.1), results[(j*4)+1].damage);
                EXPECT_MUL_EQ(results[(j*4)+2].damage, Q_4_12(1.21), results[(j*4)+3].damage);
            }
        }
    }
}

SINGLE_BATTLE_TEST("Multi - Duplicate damage boosting items can stack", s16 damage, s16 itemDamage)
{
    u32 species = 0, move = 0, item = 0, itemType = 0;
    bool16 dupe = FALSE;

    PARAMETRIZE { species = SPECIES_WOBBUFFET; move = MOVE_SCRATCH;     item = ITEM_MUSCLE_BAND;      itemType = HOLD_EFFECT_MUSCLE_BAND;    dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; move = MOVE_SCRATCH;     item = ITEM_MUSCLE_BAND;      itemType = HOLD_EFFECT_MUSCLE_BAND;    dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; move = MOVE_BUBBLE;      item = ITEM_WISE_GLASSES;     itemType = HOLD_EFFECT_WISE_GLASSES;   dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; move = MOVE_BUBBLE;      item = ITEM_WISE_GLASSES;     itemType = HOLD_EFFECT_WISE_GLASSES;   dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_PALKIA;    move = MOVE_BUBBLE;      item = ITEM_LUSTROUS_ORB;     itemType = HOLD_EFFECT_LUSTROUS_ORB;   dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_PALKIA;    move = MOVE_BUBBLE;      item = ITEM_LUSTROUS_ORB;     itemType = HOLD_EFFECT_LUSTROUS_ORB;   dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_DIALGA;    move = MOVE_METAL_CLAW;  item = ITEM_ADAMANT_ORB;      itemType = HOLD_EFFECT_ADAMANT_ORB;    dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_DIALGA;    move = MOVE_METAL_CLAW;  item = ITEM_ADAMANT_ORB;      itemType = HOLD_EFFECT_ADAMANT_ORB;    dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_GIRATINA;  move = MOVE_SHADOW_CLAW; item = ITEM_GRISEOUS_ORB;     itemType = HOLD_EFFECT_GRISEOUS_ORB;   dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_GIRATINA;  move = MOVE_SHADOW_CLAW; item = ITEM_GRISEOUS_ORB;     itemType = HOLD_EFFECT_GRISEOUS_ORB;   dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_LATIAS;    move = MOVE_PSYSHOCK;    item = ITEM_SOUL_DEW;         itemType = HOLD_EFFECT_SOUL_DEW;       dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_LATIAS;    move = MOVE_PSYSHOCK;    item = ITEM_SOUL_DEW;         itemType = HOLD_EFFECT_SOUL_DEW;       dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; move = MOVE_MEGA_PUNCH;  item = ITEM_PUNCHING_GLOVE;   itemType = HOLD_EFFECT_PUNCHING_GLOVE; dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; move = MOVE_MEGA_PUNCH;  item = ITEM_PUNCHING_GLOVE;   itemType = HOLD_EFFECT_PUNCHING_GLOVE; dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_OGERPON;   move = MOVE_SCRATCH;     item = ITEM_CORNERSTONE_MASK; itemType = HOLD_EFFECT_OGERPON_MASK;   dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_OGERPON;   move = MOVE_SCRATCH;     item = ITEM_CORNERSTONE_MASK; itemType = HOLD_EFFECT_OGERPON_MASK;   dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; move = MOVE_SHADOW_CLAW; item = ITEM_EXPERT_BELT;      itemType = HOLD_EFFECT_EXPERT_BELT;   dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; move = MOVE_SHADOW_CLAW; item = ITEM_EXPERT_BELT;      itemType = HOLD_EFFECT_EXPERT_BELT;   dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        ASSUME(GetMovePower(move) > 0);
        if (item != ITEM_NONE) {
            ASSUME(GetItemHoldEffect(item) == itemType);
        }
        PLAYER(species) { Items(item, item); Speed(1); }
        OPPONENT(species) { Speed(10); }
    } WHEN {
        TURN { MOVE(player, move); MOVE(opponent, move); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
        HP_BAR(opponent, captureDamage: &results[i].itemDamage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.1), results[0].itemDamage); // Muscle Bandd
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.21), results[2].itemDamage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.1), results[2].itemDamage); // Wise Glasses
        EXPECT_MUL_EQ(results[3].damage, Q_4_12(1.21), results[3].itemDamage);
        EXPECT_MUL_EQ(results[4].damage, Q_4_12(1.2), results[4].itemDamage); // Lustrous Orb
        EXPECT_MUL_EQ(results[5].damage, Q_4_12(1.44), results[5].itemDamage);
        EXPECT_MUL_EQ(results[6].damage, Q_4_12(1.2), results[6].itemDamage); // Adamant Orb
        EXPECT_MUL_EQ(results[7].damage, Q_4_12(1.44), results[7].itemDamage);
        EXPECT_MUL_EQ(results[8].damage, Q_4_12(1.2), results[8].itemDamage); // Griseous Orb
        EXPECT_MUL_EQ(results[9].damage, Q_4_12(1.43), results[9].itemDamage);
        EXPECT_MUL_EQ(results[10].damage, Q_4_12(1.2), results[10].itemDamage); // Soul Dew
        EXPECT_MUL_EQ(results[11].damage, Q_4_12(1.44), results[11].itemDamage);
        EXPECT_MUL_EQ(results[12].damage, Q_4_12(1.1), results[12].itemDamage); // Punching Glove
        EXPECT_MUL_EQ(results[13].damage, Q_4_12(1.21), results[13].itemDamage);
        EXPECT_MUL_EQ(results[14].damage, Q_4_12(1.2), results[14].itemDamage); // Ogerpon Mask
        EXPECT_MUL_EQ(results[15].damage, Q_4_12(1.44), results[15].itemDamage);
        EXPECT_MUL_EQ(results[16].damage, Q_4_12(1.2), results[16].itemDamage); // Expert Belt
        EXPECT_MUL_EQ(results[17].damage, Q_4_12(1.44), results[17].itemDamage);
    }
}

SINGLE_BATTLE_TEST("Multi - Kings Rock effect stack when dupes enabled")
{
    PASSES_RANDOMLY(19, 100, RNG_HOLD_EFFECT_FLINCH);
    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, TRUE);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_KINGS_ROCK, ITEM_KINGS_ROCK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("The opposing Wobbuffet flinched and couldn't move!");
    }
}

SINGLE_BATTLE_TEST("Multi - Kings Rock effect don't stack when dupes disabled")
{
    PASSES_RANDOMLY(10, 100, RNG_HOLD_EFFECT_FLINCH);
    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, FALSE);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_KINGS_ROCK, ITEM_KINGS_ROCK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("The opposing Wobbuffet flinched and couldn't move!");
    }
}

SINGLE_BATTLE_TEST("Multi - Rocky Helmet effect stack only when dupes enabled")
{
    bool16 dupe = FALSE;
    s16 damage;

    PARAMETRIZE { dupe = FALSE; }
    PARAMETRIZE { dupe = TRUE; }
    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_ROCKY_HELMET, ITEM_ROCKY_HELMET); }
        OPPONENT(SPECIES_WOBBUFFET){ MaxHP(60); HP(60); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(opponent, captureDamage: &damage);
    } FINALLY {
        if (dupe)
            EXPECT_EQ(damage, 20);
        else
            EXPECT_EQ(damage, 10);
    }
}

SINGLE_BATTLE_TEST("Multi - Shell Bell can stack if dupes enabled")
{
    u32 dupe;
    s16 damage;
    PARAMETRIZE { dupe = FALSE; }
    PARAMETRIZE { dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        ASSUME(GetMoveEffect(MOVE_DRAGON_RAGE) == EFFECT_FIXED_HP_DAMAGE);
        ASSUME(GetMoveFixedHPDamage(MOVE_DRAGON_RAGE) == 40);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_SHELL_BELL, ITEM_SHELL_BELL); HP(10); MaxHP(20); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        MESSAGE("Wobbuffet restored a little HP using its Shell Bell!");
        HP_BAR(player, captureDamage: &damage);
    } FINALLY {
        if (dupe)
            EXPECT_EQ(damage, -10);
        else
            EXPECT_EQ(damage, -5);
    }
}

SINGLE_BATTLE_TEST("Multi - Life Orb can stack if dupes enabled", s16 damage, s16 itemDamage, s16 selfDamage)
{
    bool16 dupe = FALSE;

    PARAMETRIZE { dupe = FALSE; }
    PARAMETRIZE { dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_LIFE_ORB, ITEM_LIFE_ORB); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player, captureDamage: &results[i].damage); // Basic attack
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].itemDamage);
        HP_BAR(player, captureDamage: &results[i].selfDamage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.3), results[0].itemDamage);
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.69), results[1].itemDamage);
        EXPECT_MUL_EQ(results[0].selfDamage, Q_4_12(2), results[1].selfDamage); // Self damage is doubled with 2 orbs
    }
}

SINGLE_BATTLE_TEST("Multi - Leftovers can stack if dupes enabled")
{
    bool16 dupe = FALSE;

    PARAMETRIZE { dupe = FALSE; }
    PARAMETRIZE { dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_LEFTOVERS, ITEM_LEFTOVERS); HP(50); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        MESSAGE("Wobbuffet restored a little HP using its Leftovers!");
    } FINALLY {
        if (dupe)
            EXPECT_EQ(player->hp, 62);
        else
            EXPECT_EQ(player->hp, 56);
    }
}

SINGLE_BATTLE_TEST("Multi - Black Sludge can stack if dupes enabled")
{
    bool16 dupe = FALSE;
    u32 species = SPECIES_NONE;

    PARAMETRIZE { species = SPECIES_WOBBUFFET; dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; dupe = TRUE; }
    PARAMETRIZE { species = SPECIES_GRIMER; dupe = FALSE; }
    PARAMETRIZE { species = SPECIES_GRIMER; dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(species) { Items(ITEM_BLACK_SLUDGE, ITEM_BLACK_SLUDGE); HP(50); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        if (species == SPECIES_GRIMER)
            MESSAGE("Grimer restored a little HP using its Black Sludge!");
        else
            MESSAGE("Wobbuffet was hurt by the Black Sludge!");
    } FINALLY {
        if (species == SPECIES_GRIMER)
        {
            if (dupe)
                EXPECT_EQ(player->hp, 62);
            else
                EXPECT_EQ(player->hp, 56);
        }
        else
        {
            if (dupe)
                EXPECT_EQ(player->hp, 26);
            else
                EXPECT_EQ(player->hp, 38);
        }
    }
}

SINGLE_BATTLE_TEST("Multi - Metronome can stack if dupes enabled", s16 damage1, s16 damage2, s16 damage3, s16 damage4)
{
    bool16 dupe = FALSE;

    PARAMETRIZE { dupe = FALSE; }
    PARAMETRIZE { dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_METRONOME, ITEM_METRONOME); Attack(180); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage1);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage2);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage3);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage4);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage1, UQ_4_12(1.2), results[0].damage2);
        EXPECT_MUL_EQ(results[0].damage1, UQ_4_12(1.4), results[0].damage3);
        EXPECT_MUL_EQ(results[0].damage1, UQ_4_12(1.6), results[0].damage4);
        EXPECT_MUL_EQ(results[1].damage1, UQ_4_12(1.42), results[1].damage2); // Multiplier lower than expected due to roundings in calculations
        EXPECT_MUL_EQ(results[1].damage1, UQ_4_12(1.79), results[1].damage3); // Multiplier lower than expected due to roundings in calculations
        EXPECT_MUL_EQ(results[1].damage1, UQ_4_12(2.19), results[1].damage4); // Multiplier lower than expected due to roundings in calculations
    }
}

#if B_BINDING_DAMAGE >= GEN_6
SINGLE_BATTLE_TEST("Multi - Binding Band can stack if dupes enabled (Gen 6)", s16 damage)
{
    bool16 dupe = FALSE;
    u16 item = ITEM_NONE;

    PARAMETRIZE {item = ITEM_NONE; dupe = FALSE; }
    PARAMETRIZE {item = ITEM_BINDING_BAND; dupe = FALSE; }
    PARAMETRIZE {item = ITEM_BINDING_BAND; dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(SPECIES_WOBBUFFET) { Items(item, item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WRAP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WRAP, player);
        MESSAGE("The opposing Wobbuffet is hurt by Wrap!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.32), results[1].damage); // Normal Binding Band multiplier
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.64), results[2].damage); // Newer Bind damage math has more starting damage and less Binding Band damage
    }
}
#endif

#if B_BINDING_DAMAGE < GEN_6
SINGLE_BATTLE_TEST("Multi - Binding Band can stack if dupes enabled (Gen 5)", s16 damage)
{
    bool16 dupe = FALSE;
    u16 item = ITEM_NONE, gen = 0;

    PARAMETRIZE {item = ITEM_NONE; dupe = FALSE; }
    PARAMETRIZE {item = ITEM_BINDING_BAND; dupe = FALSE; }
    PARAMETRIZE {item = ITEM_BINDING_BAND; dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        WITH_CONFIG(CONFIG_BINDING_DAMAGE, gen);
        PLAYER(SPECIES_WOBBUFFET) { Items(item, item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WRAP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WRAP, player);
        MESSAGE("The opposing Wobbuffet is hurt by Wrap!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(2), results[1].damage); // Normal Binding Band multiplier
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(3), results[2].damage); // +1/16 hp damage per Binding Band
    }
}
#endif

SINGLE_BATTLE_TEST("Multi - Speed affecting items can stack if dupes enabled")
{
    bool16 dupe = FALSE;
    u16 item = ITEM_NONE,  item2 = ITEM_NONE, speed1 = 0, speed2 = 0; 

    PARAMETRIZE {item = ITEM_NONE; item2 = ITEM_NONE; dupe = FALSE; speed1 = 99; speed2 = 100; }
    PARAMETRIZE {item = ITEM_NONE; item2 = ITEM_MACHO_BRACE; dupe = FALSE; speed1 = 99; speed2 = 200; }
    PARAMETRIZE {item = ITEM_NONE; item2 = ITEM_MACHO_BRACE; dupe = TRUE; speed1 = 51; speed2 = 200; }
    PARAMETRIZE {item = ITEM_NONE; item2 = ITEM_POWER_ANKLET; dupe = FALSE; speed1 = 99; speed2 = 200; }
    PARAMETRIZE {item = ITEM_NONE; item2 = ITEM_POWER_ANKLET; dupe = TRUE; speed1 = 51; speed2 = 200; }
    PARAMETRIZE {item = ITEM_NONE; item2 = ITEM_IRON_BALL; dupe = FALSE; speed1 = 99; speed2 = 200; }
    PARAMETRIZE {item = ITEM_NONE; item2 = ITEM_IRON_BALL; dupe = TRUE; speed1 = 51; speed2 = 200; }
    PARAMETRIZE {item = ITEM_CHOICE_SCARF; item2 = ITEM_NONE; dupe = FALSE; speed1 = 100; speed2 = 151; }
    PARAMETRIZE {item = ITEM_CHOICE_SCARF; item2 = ITEM_NONE; dupe = TRUE; speed1 = 100; speed2 = 224; }
    PARAMETRIZE {item = ITEM_QUICK_POWDER; item2 = ITEM_NONE; dupe = FALSE; speed1 = 100; speed2 = 201; }
    PARAMETRIZE {item = ITEM_QUICK_POWDER; item2 = ITEM_NONE; dupe = TRUE; speed1 = 100; speed2 = 399; }


    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        if (item == ITEM_QUICK_POWDER )
            PLAYER(SPECIES_DITTO) { Items(item, item); Speed(speed1); }
        else
            PLAYER(SPECIES_WOBBUFFET) { Items(item, item); Speed(speed1); }
        OPPONENT(SPECIES_WOBBUFFET) { Items(item2, item2); Speed(speed2); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        if (dupe)
        {
            if (item == ITEM_QUICK_POWDER)
                MESSAGE("Ditto used Scratch!");
            else
                MESSAGE("Wobbuffet used Scratch!");
            MESSAGE("The opposing Wobbuffet used Scratch!");
        }
        else
        {
            MESSAGE("The opposing Wobbuffet used Scratch!");
            if (item == ITEM_QUICK_POWDER)
                MESSAGE("Ditto used Scratch!");
            else
                MESSAGE("Wobbuffet used Scratch!");
        }
    }
}

SINGLE_BATTLE_TEST("Multi - Quick Claw effect stacks when dupes enabled")
{
    PASSES_RANDOMLY(36, 100, RNG_QUICK_CLAW);
    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, TRUE);
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); Items(ITEM_QUICK_CLAW, ITEM_QUICK_CLAW); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet used Scratch!");
        MESSAGE("The opposing Wobbuffet used Celebrate!");
    }
}

SINGLE_BATTLE_TEST("Multi - Quick Claw effect don't stack when dupes disabled")
{
    PASSES_RANDOMLY(20, 100, RNG_QUICK_CLAW);
    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, FALSE);
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); Items(ITEM_QUICK_CLAW, ITEM_QUICK_CLAW); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet used Scratch!");
        MESSAGE("The opposing Wobbuffet used Celebrate!");
    }
}

SINGLE_BATTLE_TEST("Multi - Scope Lens effect stacks when dupes enabled")
{
    u32 genConfig = 0, passes, trials;
    PARAMETRIZE { genConfig = GEN_1; passes = 2; trials = 4; } // 50% with Wobbuffet's base speed
    for (u32 j = GEN_2; j <= GEN_5; j++)
        PARAMETRIZE { genConfig = j; passes = 2; trials = 8; } // 25%
    for (u32 j = GEN_6; j <= GEN_9; j++)
        PARAMETRIZE { genConfig = j; passes = 4; trials = 8; } // 50%
    PASSES_RANDOMLY(passes, trials, RNG_CRITICAL_HIT);
    GIVEN {
        WITH_CONFIG(CONFIG_CRIT_CHANCE, genConfig);
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, TRUE);
        ASSUME(gItemsInfo[ITEM_SCOPE_LENS].holdEffect == HOLD_EFFECT_SCOPE_LENS);
        ASSUME(GetSpeciesBaseSpeed(SPECIES_WOBBUFFET) == 33);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_SCOPE_LENS, ITEM_SCOPE_LENS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Multi - Scope Lens effect doesn't stack when dupes disabled")
{
    u32 genConfig = 0, passes, trials;
    PARAMETRIZE { genConfig = GEN_1; passes = 1; trials = 4; } // 50% with Wobbuffet's base speed
    for (u32 j = GEN_2; j <= GEN_9; j++)
        PARAMETRIZE { genConfig = j; passes = 1; trials = 8; } // 25%

    PASSES_RANDOMLY(passes, trials, RNG_CRITICAL_HIT);
    GIVEN {
        WITH_CONFIG(CONFIG_CRIT_CHANCE, genConfig);
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, FALSE);
        ASSUME(gItemsInfo[ITEM_SCOPE_LENS].holdEffect == HOLD_EFFECT_SCOPE_LENS);
        ASSUME(GetSpeciesBaseSpeed(SPECIES_WOBBUFFET) == 33);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_SCOPE_LENS, ITEM_SCOPE_LENS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Multi - Lucky Punch effect stacks when dupes enabled")
{
    u32 genConfig = 0, passes, trials;
    PARAMETRIZE { genConfig = GEN_1; passes = 4; trials = 4; } // 50% with Wobbuffet's base speed
    for (u32 j = GEN_2; j <= GEN_5; j++)
        PARAMETRIZE { genConfig = j; passes = 4; trials = 8; } // 50%
    for (u32 j = GEN_6; j <= GEN_9; j++)
        PARAMETRIZE { genConfig = j; passes = 8; trials = 8; } // 100%
    PASSES_RANDOMLY(passes, trials, RNG_CRITICAL_HIT);
    GIVEN {
        WITH_CONFIG(CONFIG_CRIT_CHANCE, genConfig);
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, TRUE);
        ASSUME(gItemsInfo[ITEM_LUCKY_PUNCH].holdEffect == HOLD_EFFECT_LUCKY_PUNCH);
        PLAYER(SPECIES_CHANSEY) { Items(ITEM_LUCKY_PUNCH, ITEM_LUCKY_PUNCH); Speed(30);}
        OPPONENT(SPECIES_WOBBUFFET) { Speed(30); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Multi - Lucky Punch effect doesn't stack when dupes disabled")
{
    u32 genConfig = 0, passes, trials;
    PARAMETRIZE { genConfig = GEN_1; passes = 25; trials = 32; } // ~78.1% with Chansey's base speed
    for (u32 j = GEN_2; j <= GEN_5; j++)
        PARAMETRIZE { genConfig = j; passes = 1;  trials = 4; }  //  25%
    for (u32 j = GEN_6; j <= GEN_9; j++)
        PARAMETRIZE { genConfig = j; passes = 1;  trials = 2; }  //  50%
    PASSES_RANDOMLY(passes, trials, RNG_CRITICAL_HIT);
    GIVEN {
        WITH_CONFIG(CONFIG_CRIT_CHANCE, genConfig);
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, FALSE);
        ASSUME(gItemsInfo[ITEM_SCOPE_LENS].holdEffect == HOLD_EFFECT_SCOPE_LENS);
        PLAYER(SPECIES_CHANSEY) { Items(ITEM_LUCKY_PUNCH, ITEM_LUCKY_PUNCH); Speed(30);}
        OPPONENT(SPECIES_WOBBUFFET) { Speed(30); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Multi - Scope Lens effect stacks when dupes enabled")
{
    u32 genConfig = 0, passes, trials;
    PARAMETRIZE { genConfig = GEN_1; passes = 2; trials = 4; } // 50% with Wobbuffet's base speed
    for (u32 j = GEN_2; j <= GEN_5; j++)
        PARAMETRIZE { genConfig = j; passes = 2; trials = 8; } // 25%
    for (u32 j = GEN_6; j <= GEN_9; j++)
        PARAMETRIZE { genConfig = j; passes = 4; trials = 8; } // 50%
    PASSES_RANDOMLY(passes, trials, RNG_CRITICAL_HIT);
    GIVEN {
        WITH_CONFIG(CONFIG_CRIT_CHANCE, genConfig);
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, TRUE);
        ASSUME(gItemsInfo[ITEM_SCOPE_LENS].holdEffect == HOLD_EFFECT_SCOPE_LENS);
        ASSUME(GetSpeciesBaseSpeed(SPECIES_WOBBUFFET) == 33);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_SCOPE_LENS, ITEM_SCOPE_LENS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("A critical hit!");
    }
}

// Manual tests pass, 2 Focus Bands is 19% chance
TO_DO_BATTLE_TEST("Multi - Focus Band effect stacks when dupes enabled")
TO_DO_BATTLE_TEST("Multi - Focus Band effect don't stack when dupes disabled")
// SINGLE_BATTLE_TEST("Multi - BAND")
// {
//     GIVEN {
//         WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, TRUE);
//         PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_FOCUS_BAND, ITEM_FOCUS_BAND); MaxHP(100); HP(3); }
//         OPPONENT(SPECIES_WOBBUFFET){ Items(ITEM_FOCUS_BAND); MaxHP(100); HP(3); }
//     } WHEN {
//         TURN { MOVE(player, MOVE_HYPER_BEAM); MOVE(opponent, MOVE_HYPER_BEAM); }
//     }
// }

SINGLE_BATTLE_TEST("Multi - Light Clay effect stacks when dupes enabled")
{
    bool16 dupe = FALSE;

    PARAMETRIZE {dupe = FALSE; }
    PARAMETRIZE {dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_LIGHT_CLAY, ITEM_LIGHT_CLAY); }
        OPPONENT(SPECIES_ABOMASNOW) { Ability(ABILITY_SNOW_WARNING); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_LIGHT_SCREEN); MOVE(opponent, MOVE_LIGHT_SCREEN); } // Light Screen start
        TURN { MOVE(player, MOVE_REFLECT); MOVE(opponent, MOVE_REFLECT); }
        TURN { MOVE(player, MOVE_AURORA_VEIL); MOVE(opponent, MOVE_AURORA_VEIL); }
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); } // 5 turns, opponent wear off
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); } // 8 turns
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); } // 11 turns
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LIGHT_SCREEN, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LIGHT_SCREEN, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_REFLECT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_REFLECT, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AURORA_VEIL, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AURORA_VEIL, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("The opposing team's Light Screen wore off!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("The opposing team's Reflect wore off!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("The opposing team's Aurora Veil wore off!");
        if (!dupe)
        {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            MESSAGE("Your team's Light Screen wore off!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            MESSAGE("Your team's Reflect wore off!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            MESSAGE("Your team's Aurora Veil wore off!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        }
        else
        {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            MESSAGE("Your team's Light Screen wore off!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            MESSAGE("Your team's Reflect wore off!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            MESSAGE("Your team's Aurora Veil wore off!");
        }
    }
}

SINGLE_BATTLE_TEST("Multi - Grip Claw effect adds 2 turns when dupes enabled")
{
    u32 config, move;
    bool16 dupe = FALSE;

    PARAMETRIZE { config = GEN_4; dupe = FALSE; move = MOVE_WRAP; }
    PARAMETRIZE { config = GEN_5; dupe = FALSE; move = MOVE_WRAP; }
    PARAMETRIZE { config = GEN_4; dupe = TRUE; move = MOVE_WRAP; }
    PARAMETRIZE { config = GEN_5; dupe = TRUE; move = MOVE_WRAP; }
    PARAMETRIZE { config = GEN_4; dupe = FALSE; move = MOVE_FIRE_SPIN; }
    PARAMETRIZE { config = GEN_5; dupe = FALSE; move = MOVE_FIRE_SPIN; }
    PARAMETRIZE { config = GEN_4; dupe = TRUE; move = MOVE_FIRE_SPIN; }
    PARAMETRIZE { config = GEN_5; dupe = TRUE; move = MOVE_FIRE_SPIN; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        WITH_CONFIG(CONFIG_BINDING_TURNS, config);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_GRIP_CLAW, ITEM_GRIP_CLAW); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
        TURN {}
        TURN {}
        TURN {}
        TURN {}
        TURN { MOVE(opponent, MOVE_RECOVER); }
        TURN {}
        TURN {}
        TURN {}
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent); // Direct damage

        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Heal to continue test
        if (config >= GEN_5) {
            HP_BAR(opponent); // Residual Damage
            HP_BAR(opponent); // Residual Damage
        }
        if (dupe) {
            HP_BAR(opponent); // Residual Damage
            HP_BAR(opponent); // Residual Damage
        }
        NOT HP_BAR(opponent); // Residual Damage
    }
}

WILD_BATTLE_TEST("Multi - Lucky Egg effect adds 2 turns when dupes enabled", s32 exp)
{
    bool16 dupe = FALSE;

    PARAMETRIZE {dupe = FALSE; }
    PARAMETRIZE {dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(SPECIES_WOBBUFFET) { Level(20); Items(ITEM_LUCKY_EGG, ITEM_LUCKY_EGG); }
        OPPONENT(SPECIES_CATERPIE) { Level(10); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet used Scratch!");
        MESSAGE("The wild Caterpie fainted!");
        EXPERIENCE_BAR(player, captureGainedExp: &results[i].exp);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].exp, Q_4_12(1.5), results[1].exp);
    }
}

WILD_BATTLE_TEST("Multi - Macho Brace effect does not stack when dupes disabled")
{
    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, FALSE);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_MACHO_BRACE, ITEM_MACHO_BRACE); }
        OPPONENT(SPECIES_CATERPIE) { HP(1); }
        ASSUME(gSpeciesInfo[SPECIES_CATERPIE].evYield_HP == 1);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet used Scratch!");
        MESSAGE("The wild Caterpie fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_EV), 2);
    }
}

WILD_BATTLE_TEST("Multi - Macho Brace effect stacks when dupes enabled")
{
    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, TRUE);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_MACHO_BRACE, ITEM_MACHO_BRACE); }
        OPPONENT(SPECIES_CATERPIE) { HP(1); }
        ASSUME(gSpeciesInfo[SPECIES_CATERPIE].evYield_HP == 1);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet used Scratch!");
        MESSAGE("The wild Caterpie fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_EV), 3);
    }
}

WILD_BATTLE_TEST("Multi - Power Weight effect stacks regardless of dupe setting")
{
    bool16 dupe = FALSE;

    PARAMETRIZE {dupe = FALSE; }
    PARAMETRIZE {dupe = TRUE; }

    GIVEN {
        WITH_CONFIG(CONFIG_ALLOW_HELD_DUPES, dupe);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_POWER_WEIGHT, ITEM_POWER_WEIGHT); }
        OPPONENT(SPECIES_CATERPIE) { HP(1); }
        ASSUME(gSpeciesInfo[SPECIES_CATERPIE].evYield_HP == 1);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet used Scratch!");
        MESSAGE("The wild Caterpie fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_EV), 17); // 1 + 8 + 8 
    }
}

WILD_BATTLE_TEST("Multi - Power Weight effect stacks with Macho Brace")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_POWER_WEIGHT, ITEM_MACHO_BRACE); }
        OPPONENT(SPECIES_CATERPIE) { HP(1); }
        ASSUME(gSpeciesInfo[SPECIES_CATERPIE].evYield_HP == 1);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet used Scratch!");
        MESSAGE("The wild Caterpie fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_EV), 18); // (1 + 8) * 2
    }
}

#endif

