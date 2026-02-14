#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(MoveMakesContact(MOVE_BREAKING_SWIPE));
    ASSUME(MoveMakesContact(MOVE_SCRATCH));
}

DOUBLE_BATTLE_TEST("Pickpocket checks contact/effect per target for spread moves")
{
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_CLEFAIRY, 0) == TYPE_FAIRY);
        ASSUME(GetMoveType(MOVE_BREAKING_SWIPE) == TYPE_DRAGON);
        ASSUME(GetMoveTarget(MOVE_BREAKING_SWIPE) == MOVE_TARGET_BOTH);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
        OPPONENT(SPECIES_CLEFAIRY);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BREAKING_SWIPE); }
    } SCENE {
        ABILITY_POPUP(opponentLeft, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponentLeft->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(playerLeft->items[0] == ITEM_NONE);
    }
}

DOUBLE_BATTLE_TEST("Pickpocket activates for the fastest itemless target when both are hit by a contact spread move")
{
    GIVEN {
        ASSUME(GetMoveTarget(MOVE_BREAKING_SWIPE) == MOVE_TARGET_BOTH);
        PLAYER(SPECIES_WOBBUFFET) { Speed(20); Item(ITEM_MAGOST_BERRY); }
        PLAYER(SPECIES_WYNAUT) { Speed(10); }
        OPPONENT(SPECIES_SNEASEL) { Speed(40); Ability(ABILITY_PICKPOCKET); }
        OPPONENT(SPECIES_SNEASEL) { Speed(30); Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BREAKING_SWIPE); }
    } SCENE {
        ABILITY_POPUP(opponentLeft, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponentLeft->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(opponentRight->items[0] == ITEM_NONE);
        EXPECT(playerLeft->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals the attacker's item unless it already has one")
{
    bool32 targetHasItem;
    PARAMETRIZE { targetHasItem = FALSE; }
    PARAMETRIZE { targetHasItem = TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Item(targetHasItem ? ITEM_EVIOLITE : ITEM_NONE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        if (targetHasItem) {
            NONE_OF {
                ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
                MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
            }
        } else {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
            MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
        }
    } THEN {
        if (targetHasItem) {
            EXPECT(opponent->items[0] == ITEM_EVIOLITE);
            EXPECT(player->items[0] == ITEM_MAGOST_BERRY);
        } else {
            EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
            EXPECT(player->items[0] == ITEM_NONE);
        }
    }
}

SINGLE_BATTLE_TEST("Pickpocket does not activate if the user faints")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
            MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
        }
        MESSAGE("The opposing Sneasel fainted!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_NONE);
        EXPECT(player->items[0] == ITEM_MAGOST_BERRY);
    }
}

SINGLE_BATTLE_TEST("Pickpocket cannot steal from Sticky Hold")
{
    GIVEN {
        PLAYER(SPECIES_GRIMER) { Ability(ABILITY_STICKY_HOLD); Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        ABILITY_POPUP(player, ABILITY_STICKY_HOLD);
        MESSAGE("Grimer's item cannot be removed!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_NONE);
        EXPECT(player->items[0] == ITEM_MAGOST_BERRY);
    }
}

SINGLE_BATTLE_TEST("Pickpocket cannot steal restricted held items")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_NORMALIUM_Z].holdEffect == HOLD_EFFECT_Z_CRYSTAL);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_NORMALIUM_Z); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        }
    } THEN {
        EXPECT(opponent->items[0] == ITEM_NONE);
        EXPECT(player->items[0] == ITEM_NORMALIUM_Z);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after the final hit of a multi-strike move")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FURY_SWIPES) == EFFECT_MULTI_HIT);
        ASSUME(MoveMakesContact(MOVE_FURY_SWIPES));
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_FURY_SWIPES, WITH_RNG(RNG_HITS, 3)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        MESSAGE("The Pokémon was hit 3 time(s)!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Magician steals an item")
{
    GIVEN {
        PLAYER(SPECIES_DELPHOX) { Ability(ABILITY_MAGICIAN); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Item(ITEM_MAGOST_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MAGICIAN);
        MESSAGE("Delphox stole the opposing Sneasel's Magost Berry!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Delphox's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Sticky Barb transfers")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_STICKY_BARB].holdEffect == HOLD_EFFECT_STICKY_BARB);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Item(ITEM_STICKY_BARB); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The Sticky Barb attached itself to Wobbuffet!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Sticky Barb!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_STICKY_BARB);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Thief or Covet steals an item")
{
    u16 move;
    PARAMETRIZE { move = MOVE_THIEF; }
    PARAMETRIZE { move = MOVE_COVET; }
    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_STEAL_ITEM);
        ASSUME(MoveMakesContact(move));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Item(ITEM_MAGOST_BERRY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Wobbuffet stole the opposing Sneasel's Magost Berry!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Focus Sash is consumed")
{
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SEISMIC_TOSS));
        ASSUME(gItemsInfo[ITEM_FOCUS_SASH].holdEffect == HOLD_EFFECT_FOCUS_SASH);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); Level(100); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Item(ITEM_FOCUS_SASH); MaxHP(6); HP(6); }
    } WHEN {
        TURN { MOVE(player, MOVE_SEISMIC_TOSS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SEISMIC_TOSS, player);
        MESSAGE("The opposing Sneasel hung on using its Focus Sash!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Knock Off, Bug Bite, or Pluck")
{
    u16 move;
    PARAMETRIZE { move = MOVE_KNOCK_OFF; }
    PARAMETRIZE { move = MOVE_BUG_BITE; }
    PARAMETRIZE { move = MOVE_PLUCK; }
    GIVEN {
        ASSUME(MoveMakesContact(move));
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Item(ITEM_ORAN_BERRY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals Life Orb after it activates")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_LIFE_ORB].holdEffect == HOLD_EFFECT_LIFE_ORB);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LIFE_ORB); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet was hurt by the Life Orb!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Life Orb!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_LIFE_ORB);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals Shell Bell after it heals the user")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_SHELL_BELL].holdEffect == HOLD_EFFECT_SHELL_BELL);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SHELL_BELL); MaxHP(100); HP(66); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        HP_BAR(player);
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Shell Bell!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_SHELL_BELL);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket does not prevent King's Rock or Razor Fang flinches")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_KINGS_ROCK].holdEffect == HOLD_EFFECT_FLINCH);
        PLAYER(SPECIES_WOBBUFFET) { Speed(20); Item(ITEM_KINGS_ROCK); }
        OPPONENT(SPECIES_SNEASEL) { Speed(10); Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_HOLD_EFFECT_FLINCH, 1)); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's King's Rock!");
        MESSAGE("The opposing Sneasel flinched and couldn't move!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_KINGS_ROCK);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

#if MAX_MON_TRAITS > 1
DOUBLE_BATTLE_TEST("Pickpocket checks contact/effect per target for spread moves")
{
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_CLEFAIRY, 0) == TYPE_FAIRY);
        ASSUME(GetMoveType(MOVE_BREAKING_SWIPE) == TYPE_DRAGON);
        ASSUME(GetMoveTarget(MOVE_BREAKING_SWIPE) == MOVE_TARGET_BOTH);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
        OPPONENT(SPECIES_CLEFAIRY);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BREAKING_SWIPE); }
    } SCENE {
        ABILITY_POPUP(opponentLeft, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponentLeft->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(playerLeft->items[0] == ITEM_NONE);
    }
}

DOUBLE_BATTLE_TEST("Pickpocket activates for the fastest itemless target when both are hit by a contact spread move (Traits)")
{
    GIVEN {
        ASSUME(GetMoveTarget(MOVE_BREAKING_SWIPE) == MOVE_TARGET_BOTH);
        PLAYER(SPECIES_WOBBUFFET) { Speed(20); Item(ITEM_MAGOST_BERRY); }
        PLAYER(SPECIES_WYNAUT) { Speed(10); }
        OPPONENT(SPECIES_SNEASEL) { Speed(40); Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
        OPPONENT(SPECIES_SNEASEL) { Speed(30); Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BREAKING_SWIPE); }
    } SCENE {
        ABILITY_POPUP(opponentLeft, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponentLeft->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(opponentRight->items[0] == ITEM_NONE);
        EXPECT(playerLeft->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals the attacker's item unless it already has one (Traits)")
{
    bool32 targetHasItem;
    PARAMETRIZE { targetHasItem = FALSE; }
    PARAMETRIZE { targetHasItem = TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); Item(targetHasItem ? ITEM_EVIOLITE : ITEM_NONE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        if (targetHasItem) {
            NONE_OF {
                ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
                MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
            }
        } else {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
            MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
        }
    } THEN {
        if (targetHasItem) {
            EXPECT(opponent->items[0] == ITEM_EVIOLITE);
            EXPECT(player->items[0] == ITEM_MAGOST_BERRY);
        } else {
            EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
            EXPECT(player->items[0] == ITEM_NONE);
        }
    }
}

SINGLE_BATTLE_TEST("Pickpocket does not activate if the user faints (Traits)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
            MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
        }
        MESSAGE("The opposing Sneasel fainted!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_NONE);
        EXPECT(player->items[0] == ITEM_MAGOST_BERRY);
    }
}

SINGLE_BATTLE_TEST("Pickpocket cannot steal from Sticky Hold (Traits)")
{
    GIVEN {
        PLAYER(SPECIES_GRIMER) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_STICKY_HOLD); Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        ABILITY_POPUP(player, ABILITY_STICKY_HOLD);
        MESSAGE("Grimer's item cannot be removed!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_NONE);
        EXPECT(player->items[0] == ITEM_MAGOST_BERRY);
    }
}

SINGLE_BATTLE_TEST("Pickpocket cannot steal restricted held items (Traits)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_NORMALIUM_Z].holdEffect == HOLD_EFFECT_Z_CRYSTAL);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_NORMALIUM_Z); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        }
    } THEN {
        EXPECT(opponent->items[0] == ITEM_NONE);
        EXPECT(player->items[0] == ITEM_NORMALIUM_Z);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after the final hit of a multi-strike move (Traits)")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FURY_SWIPES) == EFFECT_MULTI_HIT);
        ASSUME(MoveMakesContact(MOVE_FURY_SWIPES));
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_FURY_SWIPES, WITH_RNG(RNG_HITS, 3)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        MESSAGE("The Pokémon was hit 3 time(s)!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Magician steals an item (Traits)")
{
    GIVEN {
        PLAYER(SPECIES_DELPHOX) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_MAGICIAN); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); Item(ITEM_MAGOST_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MAGICIAN);
        MESSAGE("Delphox stole the opposing Sneasel's Magost Berry!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Delphox's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Sticky Barb transfers (Traits)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_STICKY_BARB].holdEffect == HOLD_EFFECT_STICKY_BARB);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); Item(ITEM_STICKY_BARB); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The Sticky Barb attached itself to Wobbuffet!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Sticky Barb!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_STICKY_BARB);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Thief or Covet steals an item (Traits)")
{
    u16 move;
    PARAMETRIZE { move = MOVE_THIEF; }
    PARAMETRIZE { move = MOVE_COVET; }
    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_STEAL_ITEM);
        ASSUME(MoveMakesContact(move));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); Item(ITEM_MAGOST_BERRY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Wobbuffet stole the opposing Sneasel's Magost Berry!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Focus Sash is consumed (Traits)")
{
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SEISMIC_TOSS));
        ASSUME(gItemsInfo[ITEM_FOCUS_SASH].holdEffect == HOLD_EFFECT_FOCUS_SASH);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); Level(100); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); Item(ITEM_FOCUS_SASH); MaxHP(6); HP(6); }
    } WHEN {
        TURN { MOVE(player, MOVE_SEISMIC_TOSS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SEISMIC_TOSS, player);
        MESSAGE("The opposing Sneasel hung on using its Focus Sash!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Knock Off, Bug Bite, or Pluck (Traits)")
{
    u16 move;
    PARAMETRIZE { move = MOVE_KNOCK_OFF; }
    PARAMETRIZE { move = MOVE_BUG_BITE; }
    PARAMETRIZE { move = MOVE_PLUCK; }
    GIVEN {
        ASSUME(MoveMakesContact(move));
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); Item(ITEM_ORAN_BERRY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals Life Orb after it activates (Traits)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_LIFE_ORB].holdEffect == HOLD_EFFECT_LIFE_ORB);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LIFE_ORB); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet was hurt by the Life Orb!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Life Orb!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_LIFE_ORB);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals Shell Bell after it heals the user (Traits)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_SHELL_BELL].holdEffect == HOLD_EFFECT_SHELL_BELL);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SHELL_BELL); MaxHP(100); HP(66); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        HP_BAR(player);
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Shell Bell!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_SHELL_BELL);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket does not prevent King's Rock or Razor Fang flinches (Traits)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_KINGS_ROCK].holdEffect == HOLD_EFFECT_FLINCH);
        PLAYER(SPECIES_WOBBUFFET) { Speed(20); Item(ITEM_KINGS_ROCK); }
        OPPONENT(SPECIES_SNEASEL) { Speed(10); Ability(ABILITY_KEEN_EYE); Innates(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_HOLD_EFFECT_FLINCH, 1)); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's King's Rock!");
        MESSAGE("The opposing Sneasel flinched and couldn't move!");
    } THEN {
        EXPECT(opponent->items[0] == ITEM_KINGS_ROCK);
        EXPECT(player->items[0] == ITEM_NONE);
    }
}
#endif

#if MAX_MON_ITEMS > 1
DOUBLE_BATTLE_TEST("Pickpocket checks contact/effect per target for spread moves (Multi)")
{
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_CLEFAIRY, 0) == TYPE_FAIRY);
        ASSUME(GetMoveType(MOVE_BREAKING_SWIPE) == TYPE_DRAGON);
        ASSUME(GetMoveTarget(MOVE_BREAKING_SWIPE) == MOVE_TARGET_BOTH);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
        OPPONENT(SPECIES_CLEFAIRY);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BREAKING_SWIPE); }
    } SCENE {
        ABILITY_POPUP(opponentLeft, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponentLeft->items[1] == ITEM_MAGOST_BERRY);
        EXPECT(playerLeft->items[1] == ITEM_NONE);
    }
}

DOUBLE_BATTLE_TEST("Pickpocket activates for the fastest itemless target when both are hit by a contact spread move (Multi)")
{
    GIVEN {
        ASSUME(GetMoveTarget(MOVE_BREAKING_SWIPE) == MOVE_TARGET_BOTH);
        PLAYER(SPECIES_WOBBUFFET) { Speed(20); Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
        PLAYER(SPECIES_WYNAUT) { Speed(10); }
        OPPONENT(SPECIES_SNEASEL) { Speed(40); Ability(ABILITY_PICKPOCKET); }
        OPPONENT(SPECIES_SNEASEL) { Speed(30); Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BREAKING_SWIPE); }
    } SCENE {
        ABILITY_POPUP(opponentLeft, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponentLeft->items[1] == ITEM_MAGOST_BERRY);
        EXPECT(opponentRight->items[1] == ITEM_NONE);
        EXPECT(playerLeft->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals the attacker's item unless it already has one (Multi)")
{
    bool32 targetHasItem;
    PARAMETRIZE { targetHasItem = FALSE; }
    PARAMETRIZE { targetHasItem = TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Items(ITEM_NUGGET, targetHasItem ? ITEM_EVIOLITE : ITEM_NONE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        if (targetHasItem) {
            NONE_OF {
                ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
                MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
            }
        } else {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
            MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
        }
    } THEN {
        if (targetHasItem) {
            EXPECT(opponent->items[1] == ITEM_EVIOLITE);
            EXPECT(player->items[1] == ITEM_MAGOST_BERRY);
        } else {
            EXPECT(opponent->items[1] == ITEM_MAGOST_BERRY);
            EXPECT(player->items[1] == ITEM_NONE);
        }
    }
}

SINGLE_BATTLE_TEST("Pickpocket does not activate if the user faints (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
            MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
        }
        MESSAGE("The opposing Sneasel fainted!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_NONE);
        EXPECT(player->items[1] == ITEM_MAGOST_BERRY);
    }
}

SINGLE_BATTLE_TEST("Pickpocket cannot steal from Sticky Hold (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_GRIMER) { Ability(ABILITY_STICKY_HOLD); Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        ABILITY_POPUP(player, ABILITY_STICKY_HOLD);
        MESSAGE("Grimer's item cannot be removed!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_NONE);
        EXPECT(player->items[1] == ITEM_MAGOST_BERRY);
    }
}

SINGLE_BATTLE_TEST("Pickpocket cannot steal restricted held items (Multi)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_NORMALIUM_Z].holdEffect == HOLD_EFFECT_Z_CRYSTAL);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NONE, ITEM_NORMALIUM_Z); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        }
    } THEN {
        EXPECT(opponent->items[1] == ITEM_NONE);
        EXPECT(player->items[1] == ITEM_NORMALIUM_Z);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after the final hit of a multi-strike move (Multi)")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FURY_SWIPES) == EFFECT_MULTI_HIT);
        ASSUME(MoveMakesContact(MOVE_FURY_SWIPES));
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_FURY_SWIPES, WITH_RNG(RNG_HITS, 3)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FURY_SWIPES, player);
        MESSAGE("The Pokémon was hit 3 time(s)!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Magician steals an item (Multi)")
{
    GIVEN {
        PLAYER(SPECIES_DELPHOX) { Ability(ABILITY_MAGICIAN); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MAGICIAN);
        MESSAGE("Delphox stole the opposing Sneasel's Magost Berry!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Delphox's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Sticky Barb transfers (Multi)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_STICKY_BARB].holdEffect == HOLD_EFFECT_STICKY_BARB);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Items(ITEM_NUGGET, ITEM_STICKY_BARB); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The Sticky Barb attached itself to Wobbuffet!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Sticky Barb!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_STICKY_BARB);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Thief or Covet steals an item (Multi)")
{
    u16 move;
    PARAMETRIZE { move = MOVE_THIEF; }
    PARAMETRIZE { move = MOVE_COVET; }
    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_STEAL_ITEM);
        ASSUME(MoveMakesContact(move));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("Wobbuffet stole the opposing Sneasel's Magost Berry!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Focus Sash is consumed (Multi)")
{
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SEISMIC_TOSS));
        ASSUME(gItemsInfo[ITEM_FOCUS_SASH].holdEffect == HOLD_EFFECT_FOCUS_SASH);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); Level(100); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Items(ITEM_NUGGET, ITEM_FOCUS_SASH); MaxHP(6); HP(6); }
    } WHEN {
        TURN { MOVE(player, MOVE_SEISMIC_TOSS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SEISMIC_TOSS, player);
        MESSAGE("The opposing Sneasel hung on using its Focus Sash!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket activates after Knock Off, Bug Bite, or Pluck (Multi)")
{
    u16 move;
    PARAMETRIZE { move = MOVE_KNOCK_OFF; }
    PARAMETRIZE { move = MOVE_BUG_BITE; }
    PARAMETRIZE { move = MOVE_PLUCK; }
    GIVEN {
        ASSUME(MoveMakesContact(move));
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NUGGET, ITEM_MAGOST_BERRY); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); Items(ITEM_NUGGET, ITEM_ORAN_BERRY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Magost Berry!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_MAGOST_BERRY);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals Life Orb after it activates (Multi)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_LIFE_ORB].holdEffect == HOLD_EFFECT_LIFE_ORB);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NUGGET, ITEM_LIFE_ORB); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("Wobbuffet was hurt by the Life Orb!");
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Life Orb!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_LIFE_ORB);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket steals Shell Bell after it heals the user (Multi)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_SHELL_BELL].holdEffect == HOLD_EFFECT_SHELL_BELL);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_NUGGET, ITEM_SHELL_BELL); MaxHP(100); HP(66); }
        OPPONENT(SPECIES_SNEASEL) { Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        HP_BAR(player);
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's Shell Bell!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_SHELL_BELL);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Pickpocket does not prevent King's Rock or Razor Fang flinches (Multi)")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_KINGS_ROCK].holdEffect == HOLD_EFFECT_FLINCH);
        PLAYER(SPECIES_WOBBUFFET) { Speed(20); Items(ITEM_NUGGET, ITEM_KINGS_ROCK); }
        OPPONENT(SPECIES_SNEASEL) { Speed(10); Ability(ABILITY_PICKPOCKET); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_HOLD_EFFECT_FLINCH, 1)); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PICKPOCKET);
        MESSAGE("The opposing Sneasel stole Wobbuffet's King's Rock!");
        MESSAGE("The opposing Sneasel flinched and couldn't move!");
    } THEN {
        EXPECT(opponent->items[1] == ITEM_KINGS_ROCK);
        EXPECT(player->items[1] == ITEM_NONE);
    }
}
#endif