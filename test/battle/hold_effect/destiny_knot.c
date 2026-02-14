#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gItemsInfo[ITEM_DESTINY_KNOT].holdEffect == HOLD_EFFECT_DESTINY_KNOT);
}

SINGLE_BATTLE_TEST("Destiny Knot infatuates back when holder is targeted")
{
    GIVEN {
<<<<<<< HEAD
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE);  }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Items(ITEM_DESTINY_KNOT); }
=======
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE); }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Item(ITEM_DESTINY_KNOT); }
>>>>>>> expansion/1.14.3
    } WHEN {
        TURN { MOVE(player, MOVE_ATTRACT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        MESSAGE("Wobbuffet fell in love because of the Destiny Knot!");
    } THEN {
        EXPECT(player->volatiles.infatuation);
    }
}

SINGLE_BATTLE_TEST("Destiny Knot infatuates back when holder is attacking")
{
    GIVEN {
<<<<<<< HEAD
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE); Items(ITEM_DESTINY_KNOT);}
        OPPONENT(SPECIES_CLEFAIRY)  { Gender(MON_FEMALE); Ability(ABILITY_CUTE_CHARM);}
=======
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE); Item(ITEM_DESTINY_KNOT); }
        OPPONENT(SPECIES_CLEFAIRY)  { Gender(MON_FEMALE); Ability(ABILITY_CUTE_CHARM); }
>>>>>>> expansion/1.14.3
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        MESSAGE("The opposing Clefairy fell in love because of the Destiny Knot!");
    } THEN {
        EXPECT(opponent->volatiles.infatuation);
    }
}


SINGLE_BATTLE_TEST("Destiny Knot procs but fails if the target is already infatuated")
{
    GIVEN {
<<<<<<< HEAD
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE);  }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Items(ITEM_DESTINY_KNOT); }
=======
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE); }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Item(ITEM_DESTINY_KNOT); }
>>>>>>> expansion/1.14.3
    } WHEN {
        TURN { MOVE(opponent, MOVE_ATTRACT); MOVE(player, MOVE_ATTRACT,  WITH_RNG(RNG_INFATUATION, FALSE)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Destiny Knot procs but fails if the target is oblivious")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE); Ability(ABILITY_OBLIVIOUS); }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Items(ITEM_DESTINY_KNOT); }
    } WHEN {
        TURN { MOVE(player, MOVE_ATTRACT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        ABILITY_POPUP(player, ABILITY_OBLIVIOUS);
    } THEN {
        EXPECT(!player->volatiles.infatuation);
    }
}

SINGLE_BATTLE_TEST("Destiny Knot procs but fails if the target is already infatuated (cute charm)")
{
    GIVEN {
<<<<<<< HEAD
        PLAYER(SPECIES_CLEFAIRY) { Gender(MON_MALE); Ability(ABILITY_CUTE_CHARM);}
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Items(ITEM_DESTINY_KNOT); }
=======
        PLAYER(SPECIES_CLEFAIRY) { Gender(MON_MALE); Ability(ABILITY_CUTE_CHARM); }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Item(ITEM_DESTINY_KNOT); }
>>>>>>> expansion/1.14.3
    } WHEN {
        TURN { MOVE(opponent, MOVE_ATTRACT); }
        TURN { MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        MESSAGE("But it failed!");
    }
}

#if MAX_MON_ITEMS > 1
SINGLE_BATTLE_TEST("Destiny Knot infatuates back when holder is targeted (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE);  }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Items(ITEM_PECHA_BERRY, ITEM_DESTINY_KNOT); }
    } WHEN {
        TURN {  MOVE(player, MOVE_ATTRACT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        MESSAGE("Wobbuffet fell in love because of the Destiny Knot!");
    } THEN {
        EXPECT(player->volatiles.infatuation);
    }
}

SINGLE_BATTLE_TEST("Destiny Knot infatuates back when holder is attacking (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE); Items(ITEM_PECHA_BERRY, ITEM_DESTINY_KNOT);}
        OPPONENT(SPECIES_CLEFAIRY)  { Gender(MON_FEMALE); Ability(ABILITY_CUTE_CHARM);}
    } WHEN {
        TURN {  MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        MESSAGE("The opposing Clefairy fell in love because of the Destiny Knot!");
    } THEN {
        EXPECT(opponent->volatiles.infatuation);
    }
}


SINGLE_BATTLE_TEST("Destiny Knot procs but fails if the target is already infatuated (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE);  }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Items(ITEM_PECHA_BERRY, ITEM_DESTINY_KNOT); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ATTRACT); MOVE(player, MOVE_ATTRACT,  WITH_RNG(RNG_INFATUATION, FALSE)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Destiny Knot procs but fails if the target is oblivious (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Gender(MON_MALE); Ability(ABILITY_OBLIVIOUS); }
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Items(ITEM_PECHA_BERRY, ITEM_DESTINY_KNOT); }
    } WHEN {
        TURN { MOVE(player, MOVE_ATTRACT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        ABILITY_POPUP(player, ABILITY_OBLIVIOUS);
    } THEN {
        EXPECT(!player->volatiles.infatuation);
    }
}

SINGLE_BATTLE_TEST("Destiny Knot procs but fails if the target is already infatuated (cute charm) (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_CLEFAIRY) { Gender(MON_MALE); Ability(ABILITY_CUTE_CHARM);}
        OPPONENT(SPECIES_WOBBUFFET)  { Gender(MON_FEMALE); Items(ITEM_PECHA_BERRY, ITEM_DESTINY_KNOT); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ATTRACT);}
        TURN { MOVE(opponent, MOVE_TACKLE);}
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
        MESSAGE("But it failed!");
    }
}
#endif
