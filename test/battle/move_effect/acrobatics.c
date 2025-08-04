#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_ACROBATICS) == EFFECT_ACROBATICS);
    ASSUME(GetMoveType(MOVE_ACROBATICS) == TYPE_FLYING);
}

SINGLE_BATTLE_TEST("Acrobatics doubles in power if the user has no held item", s16 damage)
{
    u16 heldItem;
    PARAMETRIZE { heldItem = ITEM_POTION; }
    PARAMETRIZE { heldItem = ITEM_NONE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Items(heldItem, heldItem); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ACROBATICS); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Acrobatics still doubles in power when Flying Gem is consumed", s16 damage)
{
    u16 heldItem;
    PARAMETRIZE { heldItem = ITEM_NONE; }
    PARAMETRIZE { heldItem = ITEM_FLYING_GEM; }
    GIVEN {
        ASSUME(I_GEM_BOOST_POWER >= GEN_6);
        ASSUME(gItemsInfo[ITEM_FLYING_GEM].holdEffect == HOLD_EFFECT_GEMS);
        ASSUME(gItemsInfo[ITEM_FLYING_GEM].secondaryId == TYPE_FLYING);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(heldItem); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ACROBATICS); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        if (I_GEM_BOOST_POWER >= GEN_6)
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.3), (results[1].damage));
        else
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), (results[1].damage));
    }
}

SINGLE_BATTLE_TEST("Acrobatics power scales correctly with number of held items (1.33x with 1 item) (Multi)", s16 damage)
{
    u16 heldItem1, helditem2;
    PARAMETRIZE { heldItem1 = ITEM_POTION; helditem2 = ITEM_SUPER_POTION; }
    PARAMETRIZE { heldItem1 = ITEM_POTION; helditem2 = ITEM_NONE; }
    PARAMETRIZE { heldItem1 = ITEM_NONE; helditem2 = ITEM_POTION; }
    PARAMETRIZE { heldItem1 = ITEM_NONE; helditem2 = ITEM_NONE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Items(heldItem1, helditem2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ACROBATICS); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.33), results[1].damage);
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.33), results[2].damage);
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2), results[3].damage);
    }
}