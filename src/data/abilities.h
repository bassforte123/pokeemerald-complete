const struct AbilityInfo gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("No special ability."),
        .longDescription = COMPOUND_STRING("No special ability.\n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .name = _("Stench"),
        .description = COMPOUND_STRING("May cause a foe to flinch."),
        .longDescription = COMPOUND_STRING("When the Pokémon deals\n"
                                           "damage with its moves,\n"
                                           "there is a 10% chance\n"
                                           "that targets will flinch.\n"
                                           "Reduces wild encounter\n"
                                           "rate by 50% when first\n"
                                           "in the party."),
        .aiRating = 1,
    },

    [ABILITY_DRIZZLE] =
    {
        .name = _("Drizzle"),
        .description = COMPOUND_STRING("Summons rain in battle."),
        .longDescription = COMPOUND_STRING("Summons rain for 5 turns\n"
                                           "when the Pokémon enters\n"
                                           "a battle."),
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = _("Speed Boost"),
        .description = COMPOUND_STRING("Gradually boosts Speed."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "Speed stat by 1 stage at\n"
                                           "the end of every turn."),
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = _("Battle Armor"),
        .description = COMPOUND_STRING("Blocks critical hits."),
        .longDescription = COMPOUND_STRING("Attacks landed on the\n"
                                           "Pokémon will never be\n"
                                           "critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_STURDY] =
    {
        .name = _("Sturdy"),
        .description = COMPOUND_STRING("Negates 1-hit KO attacks."),
        .longDescription = COMPOUND_STRING("If the Pokémon has full\n"
                                           "HP and takes damage\n"
                                           "from a move that would\n"
                                           "knock it out in one hit,\n"
                                           "it will endure the hit\n"
                                           "with 1 HP"),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .name = _("Damp"),
        .description = COMPOUND_STRING("Prevents self-destruction."),
        .longDescription = COMPOUND_STRING("All Pokémon become\n"
                                           "unable to use explosive\n"
                                           "moves or Abilities."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .name = _("Limber"),
        .description = COMPOUND_STRING("Prevents paralysis."),
        .longDescription = COMPOUND_STRING("The Pokémon's limber\n"
                                           "body prevents it from\n"
                                           "being paralyzed."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = _("Sand Veil"),
        .description = COMPOUND_STRING("Ups evasion in a sandstorm."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "evasiveness by 25% in a\n"
                                           "sandstorm. Reduces wild\n"
                                           "encounter rate by 50%\n"
                                           "when first in the party."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .name = _("Static"),
        .description = COMPOUND_STRING("Paralyzes on contact."),
        .longDescription = COMPOUND_STRING("When hit by a contact\n"
                                           "move, the attacker has\n"
                                           #if B_ABILITY_TRIGGER_CHANCE < GEN_4
                                           "a 1/3 chance of being\n"
                                           #else
                                           "a 30% chance of being\n"
                                           #endif
                                           "paralyzed. 50% chance to\n"
                                           "encounter electric\n"
                                           "pokemon when in the\n"
                                           "front of the party."),
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = _("Volt Absorb"),
        .description = COMPOUND_STRING("Turns electricity into HP."),
        .longDescription = COMPOUND_STRING("Electric-type moves do\n"
                                           "not work on the Pokémon.\n"
                                           "Instead, they restore\n"
                                           "1/4 of its max HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = _("Water Absorb"),
        .description = COMPOUND_STRING("Changes water into HP."),
        .longDescription = COMPOUND_STRING("Water-type moves do\n"
                                           "not work on the Pokémon.\n"
                                           "Instead, they restore\n"
                                           "1/4 of its max HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_OBLIVIOUS] =
    {
        .name = _("Oblivious"),
        .description = COMPOUND_STRING("Prevents attraction."),
        .longDescription = COMPOUND_STRING("Not affected by Taunt,\n"
                                           "Infatuation, or\n"
                                           "Intimidate."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_CLOUD_NINE] =
    {
        .name = _("Cloud Nine"),
        .description = COMPOUND_STRING("Negates weather effects."),
        .longDescription = COMPOUND_STRING("Eliminates the effects\n"
                                           "of weather."),
        .aiRating = 5,
    },

    [ABILITY_COMPOUND_EYES] =
    {
        .name = _("Compound Eyes"),
        .description = COMPOUND_STRING("Raises accuracy."),
        .longDescription = COMPOUND_STRING("Boosts the accuracy of\n"
                                           "the Pokémon's moves\n"
                                           "by 30%."),
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .name = _("Insomnia"),
        .description = COMPOUND_STRING("Prevents sleep."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot\n"
                                           "become drowsy or be\n"
                                           "put to sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = _("Color Change"),
        .description = COMPOUND_STRING("Changes type to foe's move."),
        .longDescription = COMPOUND_STRING("The Pokémon's type\n"
                                           "becomes the type of the\n"
                                           "move used on it."),
        .aiRating = 2,
    },

    [ABILITY_IMMUNITY] =
    {
        .name = _("Immunity"),
        .description = COMPOUND_STRING("Prevents poisoning."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot be\n"
                                           "poisoned or\n"
                                           "badly poisoned."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = _("Flash Fire"),
        .description = COMPOUND_STRING("Powers up if hit by fire."),
        .longDescription = COMPOUND_STRING("Fire-type moves are\n"
                                           "absorbed to give a 50%\n"
                                           "boost to own Fire-type\n"
                                           "moves. 50% chance to\n"
                                           "encounter fire\n"
                                           "pokemon when in the\n"
                                           "front of the party."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = _("Shield Dust"),
        .description = COMPOUND_STRING("Prevents added effects."),
        .longDescription = COMPOUND_STRING("The Pokémon is immune to\n"
                                           "additional effects\n"
                                           "from attacks."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = _("Own Tempo"),
        .description = COMPOUND_STRING("Prevents confusion."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot\n"
                                           #if B_UPDATED_INTIMIDATE < GEN_8
                                           "become confused."),
                                           #else
                                           "become confused and is\n"
                                           "unaffected by\n"
                                           "Intimidate."),
                                           #endif
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = _("Suction Cups"),
        .description = COMPOUND_STRING("Firmly anchors the body."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot be\n"
                                           "forced to switch out by\n"
                                           "other Pokémon.\n"
                                           "Increases fishing bite\n"
                                           #if I_FISHING_STICKY_BOOST < GEN_4
                                           "chance by 35% when first\n"
                                           #else
                                           "chance by 2x when first\n"
                                           #endif
                                           "in the party."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = _("Intimidate"),
        .description = COMPOUND_STRING("Lowers the foe's Attack."),
        .longDescription = COMPOUND_STRING("When entering a battle,\n"
                                           "lowers the Attack of\n"
                                           "of opponents by 1 stage.\n"
                                           "Reduces wild encounters\n"
                                           "5 levels or lower by 50%\n"
                                           "when first in the party."),
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = _("Shadow Tag"),
        .description = COMPOUND_STRING("Prevents the foe's escape."),
        .longDescription = COMPOUND_STRING("Opponents cannot switch\n"
                                           "out of battle. Does not\n"
                                           #if B_SHADOW_TAG_ESCAPE < GEN_4
                                           "affect Ghost Pokémon."),
                                           #else
                                           "affect Ghost Pokémon.\n"
                                           "Negated if opponents\n"
                                           "also have Shadow Tag."),
                                           #endif
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = _("Rough Skin"),
        .description = COMPOUND_STRING("Hurts to touch."),
        .longDescription = COMPOUND_STRING("When the Pokémon is hit\n"
                                           "by a contact move, the\n"
                                           "attacker takes damage\n"
                                           "equal to 1/8 of its\n"
                                           "max HP."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = _("Wonder Guard"),
        .description = COMPOUND_STRING("Only “Supereffective” hits."),
        .longDescription = COMPOUND_STRING("Moves can only deal\n"
                                           "Supereffective damage.\n"
                                           "Indirect damage is\n"
                                           "unaffected."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_LEVITATE] =
    {
        .name = _("Levitate"),
        .description = COMPOUND_STRING("Not hit by Ground attacks."),
        .longDescription = COMPOUND_STRING("The Pokémon is immune to\n"
                                           "Ground-type moves, as\n"
                                           "well as the Spikes,\n"
                                           "Toxic Spikes, and\n"
                                           "Sticky Web statuses."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EFFECT_SPORE] =
    {
        .name = _("Effect Spore"),
        .description = COMPOUND_STRING("Leaves spores on contact."),
        .longDescription = COMPOUND_STRING("When hit by a move that\n"
                                           #if B_ABILITY_TRIGGER_CHANCE < GEN_4
                                           "makes contact, has a 33%\n"
                                           #else
                                           "makes contact, has a 30%\n"
                                           #endif
                                           "chance to inflict\n"
                                           "poison, sleep,\n"
                                           "or paralysis."),
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = _("Synchronize"),
        .description = COMPOUND_STRING("Passes on status problems."),
        .longDescription = COMPOUND_STRING("Copies paralysis, poison,\n"
                                           "or burn statuses onto\n"
                                           "the Pokémon inflicting\n"
                                           "them. When first in the\n"
                                           "party, wild pokemon will\n"
                                           "have a matching nature\n"
                                           "to this one."),
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = _("Clear Body"),
        .description = COMPOUND_STRING("Prevents ability reduction."),
        .longDescription = COMPOUND_STRING("The Pokémon's stats\n"
                                           "cannot be lowered by\n"
                                           "other Pokémon's moves or\n"
                                           "Abilities."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = _("Natural Cure"),
        .description = COMPOUND_STRING("Heals upon switching out."),
        .longDescription = COMPOUND_STRING("The Pokémon's status\n"
                                           "conditions are cured\n"
                                           "when it switches out of\n"
                                           "battle."),
        .aiRating = 7,
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .name = _("Lightning Rod"),
        .description = COMPOUND_STRING("Draws electrical moves."),
        .longDescription = COMPOUND_STRING(
                                           #if B_REDIRECT_ABILITY_IMMUNITY < GEN_5
                                           "Draws Electric moves.\n"
                                           "toward the Pokémon.\n"
                                           #else
                                           "Draws and absorbs\n"
                                           "Electric-type moves to\n"
                                           "raise Sp. Atk. by 1 stage.\n"
                                           #endif
                                           #if OW_LIGHTNING_ROD < GEN_8
                                           "When in the party, Match\n"
                                           "Call rate is doubled."
                                           #else
                                           "When in the party, Match\n"
                                           "Call rate is doubled and\n"
                                           "50% chance to encounter\n"
                                           "wild Elec Pokémon."
                                           #endif
                                           ),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SERENE_GRACE] =
    {
        .name = _("Serene Grace"),
        .description = COMPOUND_STRING("Promotes added effects."),
        .longDescription = COMPOUND_STRING("Doubles the likelihood\n"
                                           "of additional effects\n"
                                           "occurring when the\n"
                                           "Pokémon uses its moves."
                                           #if B_SERENE_GRACE_BOOST < GEN_5
                                           "\nKing's Rock and Razor\n"
                                           "Fang are excluded."
                                           #endif
                                           ),
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = _("Swift Swim"),
        .description = COMPOUND_STRING("Raises Speed in rain."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "Speed stat in rain."),
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = _("Chlorophyll"),
        .description = COMPOUND_STRING("Raises Speed in sunshine."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "Speed stat in harsh\n"
                                           "sunlight."),
        .aiRating = 6,
    },

    [ABILITY_ILLUMINATE] =
    {
        .name = _("Illuminate"),
        .description = COMPOUND_STRING("Encounter rate increases."),
        .longDescription = COMPOUND_STRING("Wild Pokémon encounter\n"
                                           "rate doubled when first\n"
                                           #if B_ABILITY_TRIGGER_CHANCE < GEN_9
                                           "in the party."
                                           #else
                                           "in the party. Ignore\n"
                                           "changes to targets'\n"
                                           "evasiveness and own\n"
                                           "accuracy cannot be\n"
                                           "lowered."
                                           #endif
                                           ),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_TRACE] =
    {
        .name = _("Trace"),
        .description = COMPOUND_STRING("Copies special ability."),
        .longDescription = COMPOUND_STRING("When the Pokémon enters\n"
                                           "a battle, it changes its \n"
                                           "Ability to match that of\n"
                                           "an opponent with some\n"
                                           "exceptions."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = _("Huge Power"),
        .description = COMPOUND_STRING("Raises Attack."),
        .longDescription = COMPOUND_STRING("Doubles the power of\n"
                                           "the Pokémon's physical\n"
                                           "moves.\n"),
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .name = _("Poison Point"),
        .description = COMPOUND_STRING("Poisons foe on contact."),
        .longDescription = COMPOUND_STRING("When the Pokémon is hit\n"
                                           "by a contact move,\n"
                                           #if B_ABILITY_TRIGGER_CHANCE < GEN_4
                                           "the attacker has a 33%\n"
                                           #else
                                           "the attacker has a 30%\n"
                                           #endif
                                           "chance of being\n"
                                           "poisoned."),
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = _("Inner Focus"),
        .description = COMPOUND_STRING("Prevents flinching."),
        .longDescription = COMPOUND_STRING("The Pokémon never\n"
                                           #if B_UPDATED_INTIMIDATE < GEN_8
                                           "flinches when attacked.),"
                                           #else
                                           "flinches when attacked\n"
                                           "and is unaffected by\n"
                                           "Intimidate."),
                                           #endif

        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .name = _("Magma Armor"),
        .description = COMPOUND_STRING("Prevents freezing."),
        .longDescription = COMPOUND_STRING("The Pokémon’s hot magma\n"
                                           "coating prevents it from\n"
                                           "being frozen. Doubles\n"
                                           "egg hatching speed if in\n"
                                           "the party (does not\n"
                                           "stack).\n"),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_WATER_VEIL] =
    {
        .name = _("Water Veil"),
        .description = COMPOUND_STRING("Prevents burns."),
        .longDescription = COMPOUND_STRING("The Pokémon's water veil\n"
                                           "prevents it from being\n"
                                           "burned."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = _("Magnet Pull"),
        .description = COMPOUND_STRING("Traps Steel-type Pokémon."),
        .longDescription = COMPOUND_STRING("Prevents Steel-type\n"
                                           "Pokémon from fleeing,\n"
                                           "Ghost-types excludded.\n"
                                           "50% chance to encounter\n"
                                           "Steel-type Pokémon when\n"
                                           "first in the party."),
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = _("Soundproof"),
        .description = COMPOUND_STRING("Avoids sound-based moves."),
        .longDescription = COMPOUND_STRING("Soundproofing gives the\n"
                                           "Pokémon full immunity to\n"
                                           "all sound-based moves."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = _("Rain Dish"),
        .description = COMPOUND_STRING("Slight HP recovery in rain."),
        .longDescription = COMPOUND_STRING("The Pokémon has 1/16 of\n"
                                           "its max HP restored at\n"
                                           "the end of every turn\n"
                                           "in rain. "),
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = _("Sand Stream"),
        .description = COMPOUND_STRING("Summons a sandstorm."),
        .longDescription = COMPOUND_STRING("Summons a sandstorm for\n"
                                           "5 turns when the Pokémon\n"
                                           "enters a battle."),
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .name = _("Pressure"),
        .description = COMPOUND_STRING("Raises foe's PP usage."),
        .longDescription = COMPOUND_STRING("Opponents to expend 1\n"
                                           "more PP when using moves\n"
                                           "against the Pokémon.\n"
                                           "When first in the party,\n"
                                           "50% chance for wild\n"
                                           "Pokémon to be their\n"
                                           "highest available level"),
        .aiRating = 5,
    },

    [ABILITY_THICK_FAT] =
    {
        .name = _("Thick Fat"),
        .description = COMPOUND_STRING("Heat-and-cold protection."),
        .longDescription = COMPOUND_STRING("The Pokémon is protected\n"
                                           "by a layer of thick fat,\n"
                                           "which halves the damage\n"
                                           "taken from Fire- and\n"
                                           "Ice-type moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = _("Early Bird"),
        .description = COMPOUND_STRING("Awakens quickly from sleep."),
        .longDescription = COMPOUND_STRING("The Pokémon awakens\n"
                                           "from sleep twice as fast\n"
                                           "as other Pokémon."),
        .aiRating = 4,
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = _("Flame Body"),
        .description = COMPOUND_STRING("Burns the foe on contact."),
        .longDescription = COMPOUND_STRING("When hit by a contact\n"
                                           "move, the attacker has\n"
                                           #if B_ABILITY_TRIGGER_CHANCE < GEN_4
                                           "a 1/3 chance of being\n"
                                           #else
                                           "a 30% chance of being\n"
                                           #endif
                                           "burned. Doubles egg\n"
                                           "hatching speed if in the\n"
                                           "party (does not stack)."),
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = _("Run Away"),
        .description = COMPOUND_STRING("Makes escaping easier."),
        .longDescription = COMPOUND_STRING("Enables a sure getaway\n"
                                           "from wild Pokémon."),
        .aiRating = 0,
    },

    [ABILITY_KEEN_EYE] =
    {
        .name = _("Keen Eye"),
        .description = COMPOUND_STRING("Prevents loss of accuracy."),
        .longDescription = COMPOUND_STRING("Ignores changes to \n"
                                           "targets' evasiveness and\n"
                                           "its accuracy cannot\n"
                                           "be lowered. Reduces wild\n"
                                           "encounters 5 levels or\n"
                                           "lower by 50% when first\n"
                                           "in the party."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_HYPER_CUTTER] =
    {
        .name = _("Hyper Cutter"),
        .description = COMPOUND_STRING("Prevents Attack reduction."),
        .longDescription = COMPOUND_STRING("The Pokémon's prized,\n"
                                           "mighty pincers prevent\n"
                                           "other Pokémon from\n"
                                           "lowering its Attack stat.\n"
                                           "Extends Cut's grass\n"
                                           "cutting range."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .name = _("Pickup"),
        .description = COMPOUND_STRING("May pick up items."),
        .longDescription = COMPOUND_STRING("The Pokémon may pick up\n"
                                           "an item another Pokémon\n"
                                           "used during a battle. It\n"
                                           "also has a 10% chance to\n"
                                           "pick up items at the end\n"
                                           "of battle based on its\n"
                                           "level.\n"),
        .aiRating = 1,
    },

    [ABILITY_TRUANT] =
    {
        .name = _("Truant"),
        .description = COMPOUND_STRING("Moves only every two turns."),
        .longDescription = COMPOUND_STRING("Each time the Pokémon\n"
                                           "uses a move, it spends\n"
                                           "the next turn loafing\n"
                                           "around."),
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HUSTLE] =
    {
        .name = _("Hustle"),
        .description = COMPOUND_STRING("Trades accuracy for power."),
        .longDescription = COMPOUND_STRING("Physical move Attack\n"
                                           "is boosted by 50% and\n"
                                           "accuracy is lowered by\n" 
                                           "20%. When first in the\n"
                                           "party, 50% chance for\n"
                                           "wild Pokémon to be their\n"
                                           "highest available level."),
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = _("Cute Charm"),
        .description = COMPOUND_STRING("Infatuates on contact."),
        .longDescription = COMPOUND_STRING(
                                           #if B_ABILITY_TRIGGER_CHANCE < GEN_4
                                           "1/3 chance opposite\n"
                                           #else
                                           "30% chance opposite\n"
                                           #endif
                                           "gender Pokémon are\n"
                                           "infatuated when making\n"
                                           "contact with a move.\n"
                                           "When first in party,\n"
                                           "2/3 chance wild pokemon\n"
                                           "are the opposite gender."),
        .aiRating = 2,
    },

    [ABILITY_PLUS] =
    {
        .name = _("Plus"),
        .description = COMPOUND_STRING("Powers up with Minus."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "Sp. Atk stat by 50% if\n"
                                           "an ally with the Plus\n"
                                           #if B_PLUS_MINUS_INTERACTION >= GEN_5
                                           "or Minus Ability is also\n"
                                           "in battle."
                                           #else
                                           "Ability is also in battle."
                                           #endif
                                           ),
        .aiRating = 0,
    },

    [ABILITY_MINUS] =
    {
        .name = _("Minus"),
        .description = COMPOUND_STRING("Powers up with Plus."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "Sp. Atk stat by 50% if\n"
                                           "an ally with the Minus\n"
                                           #if B_PLUS_MINUS_INTERACTION >= GEN_5
                                           "or Plus Ability is also\n"
                                           "in battle."
                                           #else
                                           "Ability is also in battle."
                                           #endif
                                           ),
        .aiRating = 0,
    },

    [ABILITY_FORECAST] =
    {
        .name = _("Forecast"),
        .description = COMPOUND_STRING("Changes with the weather."),
        .longDescription = COMPOUND_STRING("The Pokémon transforms\n"
                                           "with the weather to\n"
                                           "change its type to Water\n"
                                           "in the Rain, Fire in the\n"
                                           "Sun, or Ice in the Snow or\n"
                                           "Hail."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STICKY_HOLD] =
    {
        .name = _("Sticky Hold"),
        .description = COMPOUND_STRING("Prevents item theft."),
        .longDescription = COMPOUND_STRING("The Pokémon's held items\n"
                                           "cling to its sticky body\n"
                                           "and cannot be removed by\n"
                                           "other Pokémon. Fishing\n"
                                           "bite chance increased\n"
                                           #if I_FISHING_STICKY_BOOST < GEN_4
                                           "bite chance increased\n"
                                           "by 35% when first in\n"
                                           "the party."
                                           #else
                                           "bite chance is\n"
                                           "doubled when first in\n"
                                           "the party."
                                           #endif
                                           ),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SHED_SKIN] =
    {
        .name = _("Shed Skin"),
        .description = COMPOUND_STRING("Heals the body by shedding."),
        .longDescription = COMPOUND_STRING(
                                           #if B_ABILITY_TRIGGER_CHANCE == GEN_4
                                           "The Pokémon has a 30%\n"
                                           #else
                                           "The Pokémon has a 1/3\n"
                                           #endif
                                           "chance of curing its own\n"
                                           "status conditions at the\n"
                                           "end of every turn."),
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .name = _("Guts"),
        .description = COMPOUND_STRING("Ups Attack if suffering."),
        .longDescription = COMPOUND_STRING("When the Pokémon has a\n"
                                           "status condition, its\n"
                                           "Attack stat is boosted\n"
                                           "by 50%. Being burned\n"
                                           "does not halve the\n"
                                           "damage dealt physical\n"
                                           "moves."),
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = _("Marvel Scale"),
        .description = COMPOUND_STRING("Ups Defense if suffering."),
        .longDescription = COMPOUND_STRING("When the Pokémon has a\n"
                                           "status condition, its\n"
                                           "Defense stat is boosted\n"
                                           "by 50%."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = _("Liquid Ooze"),
        .description = COMPOUND_STRING("Draining causes injury."),
        .longDescription = COMPOUND_STRING("The strong stench of the\n"
                                           "Pokémon's oozed liquid\n"
                                           "damages attackers that\n"
                                           "use HP-draining moves."),
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .name = _("Overgrow"),
        .description = COMPOUND_STRING("Ups Grass moves in a pinch."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Grass-type\n"
                                           "moves by 50% when its HP\n"
                                           "drops to 1/3 or less of\n"
                                           "its max. "),
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .name = _("Blaze"),
        .description = COMPOUND_STRING("Ups Fire moves in a pinch."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Fire-type\n"
                                           "moves by 50% when its HP\n"
                                           "drops to 1/3 or less of\n"
                                           "its max. "),
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .name = _("Torrent"),
        .description = COMPOUND_STRING("Ups Water moves in a pinch."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Water-type\n"
                                           "moves by 50% when its HP\n"
                                           "drops to 1/3 or less of\n"
                                           "its max. "),
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .name = _("Swarm"),
        .description = COMPOUND_STRING("Ups Bug moves in a pinch."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Bug-type\n"
                                           "moves by 50% when its HP\n"
                                           "drops to 1/3 or less of\n"
                                           "its max. "),
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = _("Rock Head"),
        .description = COMPOUND_STRING("Prevents recoil damage."),
        .longDescription = COMPOUND_STRING("The Pokémon will not\n"
                                           "lose HP due to recoil\n"
                                           "damage from its moves."),
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .name = _("Drought"),
        .description = COMPOUND_STRING("Summons sunlight in battle."),
        .longDescription = COMPOUND_STRING("Summons harsh sunlight\n"
                                           "when the Pokémon enters\n"
                                           #if B_ABILITY_WEATHER < GEN_6
                                           "a battle. Lasts until\n"
                                           "overwritten."
                                           #else
                                           "a battle. Lasts for 5\n"
                                           "turns"
                                           #endif
                                           ),
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = _("Arena Trap"),
        .description = COMPOUND_STRING("Prevents fleeing."),
        .longDescription = COMPOUND_STRING("Prevents opposing\n"
                                           #if B_GHOSTS_ESCAPE < GEN_6
                                           "grounded Pokémon from\n"
                                           "fleeing or switching.\n"
                                           "Does not stop flee\n"
                                           "boosting effects. 2x \n"
                                           "wild encounter rate\n"
                                           "when first in the party."
                                           #else
                                           "grounded and non Ghost-\n"
                                           "types from fleeing or\n"
                                           "switching. Does not stop\n"
                                           "flee boosting effects.\n"
                                           "2x wild encounter rate\n"
                                           "when first in the party."
                                           #endif
                                           ),
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = _("Vital Spirit"),
        .description = COMPOUND_STRING("Prevents sleep."),
        .longDescription = COMPOUND_STRING("The Pokémon cannot\n"
                                           "become drowsy or be put\n"
                                           "to sleep. When first in\n"
                                           "the party, 50% chance\n"
                                           "for wild Pokémon to be\n"
                                           "their highest available\n"
                                           "level"),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = _("White Smoke"),
        .description = COMPOUND_STRING("Prevents ability reduction."),
        .longDescription = COMPOUND_STRING("The Pokémon's stats\n"
                                           "cannot be lowered by\n"
                                           "other Pokémon. Reduces\n"
                                           "wild encounter rate by\n"
                                           "50% when first in the\n"
                                           "party."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .name = _("Pure Power"),
        .description = COMPOUND_STRING("Raises Attack."),
        .longDescription = COMPOUND_STRING("Doubles the power of the\n"
                                           "Pokémon's physical\n"
                                           "moves."),
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = _("Shell Armor"),
        .description = COMPOUND_STRING("Blocks critical hits."),
        .longDescription = COMPOUND_STRING("A hard shell protects\n"
                                           "the Pokémon from\n"
                                           "critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_AIR_LOCK] =
    {
        .name = _("Air Lock"),
        .description = COMPOUND_STRING("Negates weather effects."),
        .longDescription = COMPOUND_STRING("Eliminates the effects\n"
                                           "of weather."),
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .name = _("Tangled Feet"),
        .description = COMPOUND_STRING("Ups evasion if confused."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "evasiveness if it is\n"
                                           "confused."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MOTOR_DRIVE] =
    {
        .name = _("Motor Drive"),
        .description = COMPOUND_STRING("Electricity raises Speed."),
        .longDescription = COMPOUND_STRING("Electric-type moves do\n"
                                           "not work on the Pokémon.\n"
                                           "Instead, they boost its\n"
                                           "Speed stat by 1 stage."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .name = _("Rivalry"),
        .description = COMPOUND_STRING("Powers up against rivals."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's moves by 25%\n"
                                           "against targets of the\n"
                                           "same gender, and lowers\n"
                                           "it by 25% against\n"
                                           "targets of the opposite\n"
                                           "gender."),
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .name = _("Steadfast"),
        .description = COMPOUND_STRING("Flinching raises Speed."),
        .longDescription = COMPOUND_STRING("When the Pokémon\n"
                                           "flinches, its Speed stat\n"
                                           "is boosted by 1 stage."),
        .aiRating = 2,
    },

    [ABILITY_SNOW_CLOAK] =
    {
        .name = _("Snow Cloak"),
        .description = COMPOUND_STRING("Ups evasion in Hail or Snow."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "evasiveness by 25% in\n"
                                           "Hail or Snow. Reduces\n"
                                           "wild encounter rate by\n"
                                           "50% in Hail or Snow when\n"
                                           "first in party."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_GLUTTONY] =
    {
        .name = _("Gluttony"),
        .description = COMPOUND_STRING("Eats Berries early."),
        .longDescription = COMPOUND_STRING("Berries that are eaten\n"
                                           "at 1/4th or less of max\n"
                                           "HP will instead be eaten\n"
                                           "at 1/2 HP or less."),
        .aiRating = 3,
    },

    [ABILITY_ANGER_POINT] =
    {
        .name = _("Anger Point"),
        .description = COMPOUND_STRING("Critical hits raise Attack."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "Attack stat to its sixth\n"
                                           "stage when the Pokémon\n"
                                           "takes a critical hit."),
        .aiRating = 4,
    },

    [ABILITY_UNBURDEN] =
    {
        .name = _("Unburden"),
        .description = COMPOUND_STRING("Using a hold item ups Speed."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "Speed stat when its held\n"
                                           "item is consumed or lost."),
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .name = _("Heatproof"),
        .description = COMPOUND_STRING("Heat and burn protection."),
        .longDescription = COMPOUND_STRING("The Pokémon's heatproof\n"
                                           "body halves the damage\n"
                                           "taken from Fire-type\n"
                                           "moves and burn."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .name = _("Simple"),
        .description = COMPOUND_STRING("Prone to wild stat changes."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "stat changes. "),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .name = _("Dry Skin"),
        .description = COMPOUND_STRING("Prefers moisture to heat."),
        .longDescription = COMPOUND_STRING("Water-type moves heal\n"
                                           "1/4 of the Pokémon's\n"
                                           "max HP. Takes 25% more\n"
                                           "damage from Fire-type\n"
                                           "moves. Rain heals 1/8\n"
                                           "max HP each turn but\n"
                                           "sunlight takes 1/8."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .name = _("Download"),
        .description = COMPOUND_STRING("Adjusts power favorably."),
        .longDescription = COMPOUND_STRING("Compares an opposing\n"
                                           "Pokémon's Defense and\n"
                                           "Sp. Def stats before\n"
                                           "raising its own Attack\n"
                                           "or Sp. Atk stat,\n"
                                           "whichever will be more\n"
                                           "effective."),
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .name = _("Iron Fist"),
        .description = COMPOUND_STRING("Boosts punching moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's punching\n"
                                           "moves by 20%."),
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .name = _("Poison Heal"),
        .description = COMPOUND_STRING("Restores HP if poisoned."),
        .longDescription = COMPOUND_STRING("If poisoned or badly\n"
                                           "poisoned, the Pokémon\n"
                                           "has 1/8 of its max HP\n"
                                           "restored at the end of\n"
                                           "every turn instead of\n"
                                           "losing HP. "),
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .name = _("Adaptability"),
        .description = COMPOUND_STRING("Boosts same type attacks."),
        .longDescription = COMPOUND_STRING("Boosts the power of\n"
                                           "moves of the same type\n"
                                           "as the Pokémon by 100%\n"
                                           "instead of 50%. When\n"
                                           "Terastallized, only \n"
                                           "affects moves of the\n"
                                           "same Tera Type."),
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .name = _("Skill Link"),
        .description = COMPOUND_STRING("Multi-hit moves hit 5 times."),
        .longDescription = COMPOUND_STRING("The Pokémon's\n"
                                           "multistrike moves always\n"
                                           "hit the maximum number\n"
                                           "of times."),
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .name = _("Hydration"),
        .description = COMPOUND_STRING("Cures status in rain."),
        .longDescription = COMPOUND_STRING("Cures the Pokémon's\n"
                                           "status conditions\n"
                                           "at the end of every\n"
                                           "turn in rain."),
        .aiRating = 4,
    },

    [ABILITY_SOLAR_POWER] =
    {
        .name = _("Solar Power"),
        .description = COMPOUND_STRING("Powers up in sunshine."),
        .longDescription = COMPOUND_STRING("In harsh sunlight, the\n"
                                           "Pokémon's Sp. Atk stat\n"
                                           "is boosted by 50%, but\n"
                                           "it loses 1/8 of its max\n"
                                           "HP at the end of every\n"
                                           "turn."),
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .name = _("Quick Feet"),
        .description = COMPOUND_STRING("Ups Speed if suffering."),
        .longDescription = COMPOUND_STRING("Boots speed by 50% if\n"
                                           "the Pokémon has a status\n"
                                           "condition. Paralysis\n"
                                           "does not lower speed.\n"
                                           "Reduces wild encounter\n"
                                           "rate by 50% when first \n"
                                           "in the party"),
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .name = _("Normalize"),
        .description = COMPOUND_STRING("Moves become Normal-type."),
        .longDescription = COMPOUND_STRING("All the Pokémon's moves\n"
                                           #if B_ATE_MULTIPLIER < GEN_7
                                           "become Normal type."
                                           #else
                                           "become Normal type. The\n"
                                           "power of those moves\n"
                                           "is boosted by 20%."
                                           #endif
                                           ),
        .aiRating = -1,
    },

    [ABILITY_SNIPER] =
    {
        .name = _("Sniper"),
        .description = COMPOUND_STRING("Boosts critical hits."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's critical hits\n"
                                           "by 50%."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .name = _("Magic Guard"),
        .description = COMPOUND_STRING("Only damaged by attacks."),
        .longDescription = COMPOUND_STRING("The Pokémon only takes\n"
                                           "damage from attacks,\n"
                                           "becoming immune to\n"
                                           "indirect damage."),
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .name = _("No Guard"),
        .description = COMPOUND_STRING("Ensures that all moves hit."),
        .longDescription = COMPOUND_STRING("The accuracy of moves\n"
                                           "used both by and against\n"
                                           "the Pokémon becomes\n"
                                           "100%. Doubles wild\n"
                                           "encounter rate when\n"
                                           "first in the party."),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .name = _("Stall"),
        .description = COMPOUND_STRING("Always moves last."),
        .longDescription = COMPOUND_STRING("The Pokémon's moves go\n"
                                           "last among moves of the\n"
                                           "same priority. "),
        .aiRating = -1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .name = _("Technician"),
        .description = COMPOUND_STRING("Boosts weaker moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's moves by 50%\n"
                                           "if their power is 60 or\n"
                                           "less."),
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .name = _("Leaf Guard"),
        .description = COMPOUND_STRING("Blocks status in sunshine."),
        .longDescription = COMPOUND_STRING("The Pokémon is immune\n"
                                           "to status conditions in\n"
                                           "harsh sunlight."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .name = _("Klutz"),
        .description = COMPOUND_STRING("Can't use hold items."),
        .longDescription = COMPOUND_STRING("Items do not work when\n"
                                           "held by the Pokémon."),
        .aiRating = -1,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .name = _("Mold Breaker"),
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .longDescription = COMPOUND_STRING("The Pokémon's moves are\n"
                                           "unaffected by the\n"
                                           "Ability of the target\n"
                                           "(with some exceptions).\n"
                                           "Abilities that react to\n"
                                           "moves will still take\n"
                                           "effect."),
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .name = _("Super Luck"),
        .description = COMPOUND_STRING("Critical hits land often."),
        .longDescription = COMPOUND_STRING("Boost Critical-Hit Ratio\n"
                                           #if OW_SUPER_LUCK < GEN_8
                                           "by 1-stage.\n"
                                           #else
                                           "by 1-stage. If first in\n"
                                           "the party, wild Pokémon\n"
                                           "common/rare held item\n"
                                           "chance goes from 50%/5%\n"
                                           "to 60%/20%."
                                           #endif
                                           ),
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .name = _("Aftermath"),
        .description = COMPOUND_STRING("Fainting damages the foe."),
        .longDescription = COMPOUND_STRING("Attackers that knock\n"
                                           "out the Pokémon with a\n"
                                           "contact move take\n"
                                           "damage equal to 1/4 of\n"
                                           "their own max HP."),
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .name = _("Anticipation"),
        .description = COMPOUND_STRING("Senses dangerous moves."),
        .longDescription = COMPOUND_STRING("When the Pokémon enters\n"
                                           "a battle, it shudders\n"
                                           "if the opponents knows\n"
                                           "any one-hit KO moves or\n"
                                           "moves that are super\n"
                                           "effective against it."),
        .aiRating = 2,
    },

    [ABILITY_FOREWARN] =
    {
        .name = _("Forewarn"),
        .description = COMPOUND_STRING("Determines a foe's move."),
        .longDescription = COMPOUND_STRING("When it enters a battle,\n"
                                           "the Pokémon can tell a\n"
                                           "move of an opposing\n"
                                           "Pokémon with the highest\n"
                                           "power or threat (OHKO\n"
                                           "and countering moves are\n"
                                           "high threat)."),
        .aiRating = 2,
    },

    [ABILITY_UNAWARE] =
    {
        .name = _("Unaware"),
        .description = COMPOUND_STRING("Ignores stat changes."),
        .longDescription = COMPOUND_STRING("The Pokémon ignores the\n"
                                           "target's stat changes \n"
                                           "when attacking or being\n"
                                           "attacked and overall\n"
                                           "damage or accuracy are\n"
                                           "considered. Does not\n"
                                           "affect turn order or\n"
                                           "stat-reading move power."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .name = _("Tinted Lens"),
        .description = COMPOUND_STRING("Ups “not very effective”."),
        .longDescription = COMPOUND_STRING("Doubles the damage of\n"
                                           "“not very effective”\n"
                                           "moves."),
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .name = _("Filter"),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .longDescription = COMPOUND_STRING("Reduces the damage the\n"
                                           "Pokémon takes from\n"
                                           "supereffective moves\n"
                                           "by 25% (2x damage\n"
                                           "becomes 1.5x)."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .name = _("Slow Start"),
        .description = COMPOUND_STRING("Takes a while to get going."),
        .longDescription = COMPOUND_STRING("For five turns, the\n"
                                           "Pokémon's Attack and\n"
                                           "Speed stats are halved."),
        .aiRating = -2,
    },

    [ABILITY_SCRAPPY] =
    {
        .name = _("Scrappy"),
        .description = COMPOUND_STRING("Hits Ghost-type Pokémon."),
        .longDescription = COMPOUND_STRING("The Pokémon can hit\n"
                                           "Ghost types with Normal-\n"
                                           #if  B_UPDATED_INTIMIDATE < GEN_8
                                           "and Fighting-type moves."
                                           #else
                                           "and Fighting-type moves.\n"
                                           "It is also unaffected\n"
                                           "by Intimidate."
                                           #endif
                                           ),
        .aiRating = 6,
    },

    [ABILITY_STORM_DRAIN] =
    {
        .name = _("Storm Drain"),
        .description = COMPOUND_STRING("Draws in Water moves."),
        .longDescription = COMPOUND_STRING(
                                           #if B_REDIRECT_ABILITY_IMMUNITY < GEN_5
                                           "Draws Water-type moves.\n"
                                           "toward the Pokémon.\n"
                                           #else
                                           "Draws and absorbs\n"
                                           "Water-type moves to\n"
                                           "raise Sp. Atk. by 1 stage.\n"
                                           #endif
                                           #if OW_STORM_DRAIN >= GEN_8
                                           "When first in the party,\n"
                                           "50% chance to encounter\n"
                                           "wild Water Pokémon."
                                           #endif
                                           ),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_ICE_BODY] =
    {
        .name = _("Ice Body"),
        .description = COMPOUND_STRING("HP recovery in Hail or Snow."),
        .longDescription = COMPOUND_STRING("The Pokémon has 1/16 of\n"
                                           "its max HP restored at\n"
                                           "the end of every turn\n"
                                           "in hail or snow and is\n"
                                           "not hurt by hail."),
        .aiRating = 3,
    },

    [ABILITY_SOLID_ROCK] =
    {
        .name = _("Solid Rock"),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .longDescription = COMPOUND_STRING("Reduces the damage the\n"
                                           "Pokémon takes from\n"
                                           "supereffective moves\n"
                                           "by 25% (2x damage\n"
                                           "becomes 1.5x)."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .name = _("Snow Warning"),
    #if B_SNOW_WARNING >= GEN_9
        .description = COMPOUND_STRING("Summons snow in battle."),
        .longDescription = COMPOUND_STRING(
                                           #if B_ABILITY_WEATHER < GEN_6
                                           "Summons persistent snow\n"
                                           "when the Pokémon enters\n"
                                           "a battle."
                                           #else
                                           "Summons snow for 5\n"
                                           "turns when the Pokémon\n"
                                           "enters a battle."
                                           #endif
                                           ),
    #else
        .description = COMPOUND_STRING("Summons hail in battle."),
        .longDescription = COMPOUND_STRING(
                                           #if B_ABILITY_WEATHER < GEN_6
                                           "Summons persistent hail\n"
                                           "when the Pokémon enters\n"
                                           "a battle."
                                           #else
                                           "Summons hail for 5\n"
                                           "turns when the Pokémon\n"
                                           "enters a battle."
                                           #endif
                                           ),
    #endif
        .aiRating = 8,
    },

    [ABILITY_HONEY_GATHER] =
    {
        .name = _("Honey Gather"),
        .description = COMPOUND_STRING("May gather Honey."),
        .longDescription = COMPOUND_STRING("The Pokémon may gather\n"
                                           "Honey after a battle.\n"
                                           "The chance of finding\n"
                                           "Honey is 5% at level 1\n"
                                           "plus 5% for every 10\n"
                                           "levels."),
        .aiRating = 0,
    },

    [ABILITY_FRISK] =
    {
        .name = _("Frisk"),
        .description = COMPOUND_STRING("Checks a foe's item."),
        .longDescription = COMPOUND_STRING("When the Pokémon enters\n"
                                           "a battle, it identifies\n"
                                           "opponents' held items."),
        .aiRating = 3,
    },

    [ABILITY_RECKLESS] =
    {
        .name = _("Reckless"),
        .description = COMPOUND_STRING("Boosts moves with recoil."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's moves by 20%\n"
                                           "if they have recoil or\n"
                                           "crash damage. "),
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .name = _("Multitype"),
        .description = COMPOUND_STRING("Changes type to its Plate."),
        .longDescription = COMPOUND_STRING("Changes the Pokémon's\n"
                                           "type to match the plate\n"
                                           "or Z-Crystal it holds."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_FLOWER_GIFT] =
    {
        .name = _("Flower Gift"),
        .description = COMPOUND_STRING("Allies power up in sunshine."),
        .longDescription = COMPOUND_STRING("In harsh sunlight,\n"
                                           "Transforms Cherrim with\n"
                                           "this ability and Boosts\n"
                                           "the Attack and Sp. Def\n"
                                           "stats of the Pokémon and\n"
                                           "its allies."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_BAD_DREAMS] =
    {
        .name = _("Bad Dreams"),
        .description = COMPOUND_STRING("Damages sleeping Pokémon."),
        .longDescription = COMPOUND_STRING("Damages opposing\n"
                                           "Pokémon that are asleep\n"
                                           "by 1/8 of their max HP\n"
                                           "at the end of every turn."),
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .name = _("Pickpocket"),
        .description = COMPOUND_STRING("Steals the foe's held item."),
        .longDescription = COMPOUND_STRING("When the Pokémon is hit\n"
                                           "by a contact move, it\n"
                                           "will steal the held item\n"
                                           "of the attacker if it is\n"
                                           "not already holding an\n"
                                           "item."),
        .aiRating = 3,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .name = _("Sheer Force"),
        .description = COMPOUND_STRING("Trades effects for power."),
        .longDescription = COMPOUND_STRING("Removes added effects\n"
                                           "to increase move power\n"
                                           "by 30%. Excludes self-\n"
                                           "detrimental, charging,\n"
                                           "high crit-ratio, sure-\n"
                                           "hit, variable power,\n"
                                           "and removing screens"),
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .name = _("Contrary"),
        .description = COMPOUND_STRING("Inverts stat changes."),
        .longDescription = COMPOUND_STRING("Reverses any stat\n"
                                           "changes affecting the\n"
                                           "Pokémon when they are\n"
                                           "applied."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .name = _("Unnerve"),
        .description = COMPOUND_STRING("Foes can't eat Berries."),
        .longDescription = COMPOUND_STRING("Makes opponents unable\n"
                                           "to eat Berries."),
        .aiRating = 3,
    },

    [ABILITY_DEFIANT] =
    {
        .name = _("Defiant"),
        .description = COMPOUND_STRING("Lowered stats up Attack."),
        .longDescription = COMPOUND_STRING("When the Pokémon has any\n"
                                           "of its stats lowered by\n"
                                           "an opponent, its Attack\n"
                                           "stat is boosted by 2\n"
                                           "stages. Triggers for\n"
                                           "each stat if more than\n"
                                           "one is lowered."),
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .name = _("Defeatist"),
        .description = COMPOUND_STRING("Gives up at half HP."),
        .longDescription = COMPOUND_STRING("Halves the Pokémon's\n"
                                           "Attack and Sp. Atk stats\n"
                                           "when its HP drops to\n"
                                           "half or less."),
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .name = _("Cursed Body"),
        .description = COMPOUND_STRING("Disables moves on contact."),
        .longDescription = COMPOUND_STRING("When the Pokémon takes \n"
                                           "damage from a move, the\n"
                                           "attacker has a 30%\n"
                                           "chance of their Move\n"
                                           "being Disabled status\n"
                                           "for 4 turns."),
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .name = _("Healer"),
        .description = COMPOUND_STRING("Heals partner Pokémon."),
        .longDescription = COMPOUND_STRING("The Pokémon has a 50%\n"
                                           "chance of curing the\n"
                                           "status conditions of its\n"
                                           "allies at the end of\n"
                                           "every turn."),
        .aiRating = 0,
    },

    [ABILITY_FRIEND_GUARD] =
    {
        .name = _("Friend Guard"),
        .description = COMPOUND_STRING("Lowers damage to partner."),
        .longDescription = COMPOUND_STRING("Reduces the damage\n"
                                           "allies take by 25%."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .name = _("Weak Armor"),
        .description = COMPOUND_STRING("Its stats change when hit."),
        .longDescription = COMPOUND_STRING("When the Pokémon takes\n"
                                           "damage from a physical\n"
                                           "move, its Defense stat\n"
                                           "is lowered by 1 stage, \n"
                                           "but its Speed stat is\n"
                                           #if B_WEAK_ARMOR_SPEED < GEN_7
                                           "boosted by 1 stage."
                                           #else
                                           "boosted by 2 stages."
                                           #endif
                                           ),
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .name = _("Heavy Metal"),
        .description = COMPOUND_STRING("Doubles weight."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "weight. No effect on\n"
                                           "Heavy Ball."),
        .aiRating = -1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .name = _("Light Metal"),
        .description = COMPOUND_STRING("Halves weight."),
        .longDescription = COMPOUND_STRING("Halves the Pokémon's\n"
                                           "weight. No effect on\n"
                                           "Heavy Ball."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .name = _("Multiscale"),
        .description = COMPOUND_STRING("Halves damage at full HP."),
        .longDescription = COMPOUND_STRING("Halves the damage the\n"
                                           "Pokémon takes while its\n"
                                           "HP is full. Does not\n"
                                           "affect moves with fixed\n"
                                           "damage such as Seismic\n"
                                           "Toss or Counter."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .name = _("Toxic Boost"),
        .description = COMPOUND_STRING("Ups Attack if poisoned."),
        .longDescription = COMPOUND_STRING("Powers up physical moves\n"
                                           "when the Pokémon is\n"
                                           "poisoned."),
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .name = _("Flare Boost"),
        .description = COMPOUND_STRING("Ups Sp. Atk if burned."),
        .longDescription = COMPOUND_STRING("Powers up special moves\n"
                                           "when the Pokémon is\n"
                                           "burned."),
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .name = _("Harvest"),
        .description = COMPOUND_STRING("May recycle a used Berry."),
        .longDescription = COMPOUND_STRING("When using a berry, has\n"
                                           "a 50% chance to create\n"
                                           "another to replace it.\n"
                                           "100% in harsh sunlight.\n"
                                           #if OW_HARVEST >= GEN_8
                                           "When first in the party,\n"
                                           "50% chance to encounter\n"
                                           "wild Grass Pokémon."
                                           #endif
                                           ),
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .name = _("Telepathy"),
        .description = COMPOUND_STRING("Can't be damaged by an ally."),
        .longDescription = COMPOUND_STRING("The Pokémon anticipates\n"
                                           "and dodges the attacks\n"
                                           "of its allies."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .name = _("Moody"),
        .description = COMPOUND_STRING("Stats change gradually."),
        .longDescription = COMPOUND_STRING("At the end of every\n"
                                           "turn, one of the\n"
                                           "Pokémon's stats will be\n"
                                           "boosted by 2 stages,\n"
                                           "and another lowered\n"
                                           #if B_MOODY_ACC_EVASION < GEN_8
                                           "by 1 stage."
                                           #else
                                           "by 1 stage except\n"
                                           "evasion or accuracy."
                                           #endif
                                           ),
        .aiRating = 10,
    },

    [ABILITY_OVERCOAT] =
    {
        .name = _("Overcoat"),
        .description = COMPOUND_STRING("Blocks weather and powder."),
        .longDescription = COMPOUND_STRING("Protects the Pokémon\n"
                                           "from sand and hail\n"
                                           #if B_POWDER_OVERCOAT < GEN_6
                                           "damage."
                                           #else
                                           "damage. also grants\n"
                                           "immunity to powder based\n"
                                           "moves and abilities."
                                           #endif
                                           ),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_POISON_TOUCH] =
    {
        .name = _("Poison Touch"),
        .description = COMPOUND_STRING("Poisons foe on contact."),
        .longDescription = COMPOUND_STRING("When the Pokémon hits a\n"
                                           "target with a contact\n"
                                           "move, the target has a\n"
                                           "30% chance of being\n"
                                           "poisoned."),
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .name = _("Regenerator"),
        .description = COMPOUND_STRING("Heals upon switching out."),
        .longDescription = COMPOUND_STRING("The Pokémon has 1/3 of\n"
                                           "its max HP restored\n"
                                           "when it switches out\n"
                                           "of battle."),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .name = _("Big Pecks"),
        .description = COMPOUND_STRING("Prevents Defense loss."),
        .longDescription = COMPOUND_STRING("The Pokémon's Defense\n"
                                           "stat cannot be lowered\n"
                                           "by other Pokémon's\n"
                                           "moves or Abilities."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .name = _("Sand Rush"),
        .description = COMPOUND_STRING("Ups Speed in a sandstorm."),
        .longDescription = COMPOUND_STRING("Doubles the Pokémon's\n"
                                           "Speed stat in a\n"
                                           "sandstorm."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .name = _("Wonder Skin"),
        .description = COMPOUND_STRING("May avoid status problems."),
        .longDescription = COMPOUND_STRING("Status moves cannot\n"
                                           "have more than 50%\n"
                                           "base accuracy against \n"
                                           "this Pokémon."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .name = _("Analytic"),
        .description = COMPOUND_STRING("Moving last boosts power."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's moves by 30%\n"
                                           "when the Pokémon is the\n"
                                           "last to move that turn."),
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .name = _("Illusion"),
        .description = COMPOUND_STRING("Appears as a partner."),
        .longDescription = COMPOUND_STRING("The Pokémon enters\n"
                                           "battle disguised as the\n"
                                           "last Pokémon in its\n"
                                           "party. It reverts to its\n"
                                           "usual appearance when it\n"
                                           "takes damage from a\n"
                                           "move. "),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .name = _("Imposter"),
        .description = COMPOUND_STRING("Transforms into the foe."),
        .longDescription = COMPOUND_STRING("The Pokémon transforms\n"
                                           "into the Pokémon in\n"
                                           "front of it. It also\n"
                                           "copies all of that\n"
                                           "Pokémon's stats apart\n"
                                           "from its HP."),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INFILTRATOR] =
    {
        .name = _("Infiltrator"),
        .description = COMPOUND_STRING("Passes through barriers."),
        .longDescription = COMPOUND_STRING("When using its moves,\n"
                                           "the Pokémon ignores the\n"
                                           "effects of targets'\n"
                                           "Light Screen, Reflect,\n"
                                           "Aurora Veil, Safeguard,\n"
                                           "and substitutes."),
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .name = _("Mummy"),
        .description = COMPOUND_STRING("Spreads with contact."),
        .longDescription = COMPOUND_STRING("When the Pokémon is hit\n"
                                           "by a contact move, the\n"
                                           "attacker has its\n"
                                           "Ability changed to\n"
                                           "Mummy."),
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .name = _("Moxie"),
        .description = COMPOUND_STRING("KOs raise Attack."),
        .longDescription = COMPOUND_STRING("When the Pokémon knocks\n"
                                           "out a target, it shows\n"
                                           "moxie, which boosts\n"
                                           "its Attack stat."),
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .name = _("Justified"),
        .description = COMPOUND_STRING("Dark hits raise Attack."),
        .longDescription = COMPOUND_STRING("When the Pokémon takes\n"
                                           "damage from a Dark-type\n"
                                           "move, its Attack stat\n"
                                           "is boosted by 1 stage."),
        .aiRating = 4,
    },

    [ABILITY_RATTLED] =
    {
        .name = _("Rattled"),
        .description = COMPOUND_STRING("Raises Speed when scared."),
        .longDescription = COMPOUND_STRING("The Pokémon gets scared\n"
                                           "when hit by a Dark-,\n"
                                           "Ghost-, or Bug-type\n"
                                           #if B_UPDATED_INTIMIDATE < GEN_8
                                           "attack, which boosts\n"
                                           "its Speed stat by one\n"
                                           "stage."
                                           #else
                                           "attack or if\n"
                                           "intimidated, which\n"
                                           "boosts its Speed stat\n"
                                           "by one stage."
                                           #endif
                                           ),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .name = _("Magic Bounce"),
        .description = COMPOUND_STRING("Reflects status moves."),
        .longDescription = COMPOUND_STRING("The Pokémon reflects\n"
                                           "status moves instead of\n"
                                           "getting hit by them. "),
        .aiRating = 9,
        .breakable = TRUE,
    },

    [ABILITY_SAP_SIPPER] =
    {
        .name = _("Sap Sipper"),
        .description = COMPOUND_STRING("Grass increases Attack."),
        .longDescription = COMPOUND_STRING("Grass-type moves do not\n"
                                           "work on the Pokémon.\n"
                                           "Instead, they boost its\n"
                                           "Attack stat by 1 stage."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .name = _("Prankster"),
        .description = COMPOUND_STRING("Status moves go first."),
        .longDescription = COMPOUND_STRING("Increases the priority\n"
                                           "of the Pokémon's status\n"
                                           #if B_PRANKSTER_DARK_TYPES < GEN_7
                                           "moves by 1 stage."
                                           #else
                                           "moves by 1 stage. Dark-\n"
                                           "type Pokémon are immune\n"
                                           "to these boosted moves."
                                           #endif
                                           ),
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .name = _("Sand Force"),
        .description = COMPOUND_STRING("Powers up in a sandstorm."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's Rock-,\n"
                                           "Ground-, and Steel-type\n"
                                           "moves by 30% in a\n"
                                           "sandstorm."),
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .name = _("Iron Barbs"),
        .description = COMPOUND_STRING("Hurts to touch."),
        .longDescription = COMPOUND_STRING("Attackers that hit this\n"
                                           "Pokémon with contact\n"
                                           "moves are damaged for\n"
                                           "1/8 of their max HP."),
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .name = _("Zen Mode"),
        .description = COMPOUND_STRING("Transforms at half HP."),
        .longDescription = COMPOUND_STRING("Changes the Pokémon's\n"
                                           "shape when its HP drops\n"
                                           "to half or less."),
        .aiRating = -1,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = B_UPDATED_ABILITY_DATA >= GEN_7,
    },

    [ABILITY_VICTORY_STAR] =
    {
        .name = _("Victory Star"),
        .description = COMPOUND_STRING("Raises party accuracy."),
        .longDescription = COMPOUND_STRING("Boosts the accuracy of\n"
                                           "the Pokémon and its\n"
                                           "allies by about 10%.\n"
                                           "OHKO moves are excluded."),
        .aiRating = 6,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .name = _("Turboblaze"),
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .longDescription = COMPOUND_STRING("The Pokémon's moves are\n"
                                           "unaffected by the\n"
                                           "Ability of the target\n"
                                           "(with some exceptions).\n"
                                           "Abilities that react to\n"
                                           "moves will still take\n"
                                           "effect."),
        .aiRating = 7,
    },

    [ABILITY_TERAVOLT] =
    {
        .name = _("Teravolt"),
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .longDescription = COMPOUND_STRING("The Pokémon's moves are\n"
                                           "unaffected by the\n"
                                           "Ability of the target\n"
                                           "(with some exceptions).\n"
                                           "Abilities that react to\n"
                                           "moves will still take\n"
                                           "effect."),
        .aiRating = 7,
    },

    [ABILITY_AROMA_VEIL] =
    {
        .name = _("Aroma Veil"),
        .description = COMPOUND_STRING("Prevents limiting of moves."),
        .longDescription = COMPOUND_STRING("The Pokémon and its\n"
                                           "allies cannot gain the\n"
                                           "Infatuated, Taunted, \n"
                                           "Unable to Repeat, Move\n"
                                           "Disabled, Healing\n"
                                           "Prevented, or Encore\n"
                                           "statuses."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .name = _("Flower Veil"),
        .description = COMPOUND_STRING("Protects Grass-types."),
        .longDescription = COMPOUND_STRING("Grass-type allies are\n"
                                           "immune to status\n"
                                           "conditions and cannot\n"
                                           "have their stats\n"
                                           "lowered."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .name = _("Cheek Pouch"),
        .description = COMPOUND_STRING("Eating Berries restores HP."),
        .longDescription = COMPOUND_STRING("The Pokémon has 1/3 of\n"
                                           "its max HP restored\n"
                                           "when it eats a Berry,\n"
                                           "in addition to the\n"
                                           "Berry's usual effect."),
        .aiRating = 4,
    },

    [ABILITY_PROTEAN] =
    {
        .name = _("Protean"),
        .description = COMPOUND_STRING("Changes type to used move."),
        .longDescription = COMPOUND_STRING("Changes the Pokémon's\n"
                                           "type to the type of the\n"
                                           "move it's about to use."
                                           #if B_PROTEAN_LIBERO >= GEN_9
                                           "\nThis works only once\n"
                                           "per time the Pokémon\n"
                                           "enters battle."
                                           #endif
                                           ),
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .name = _("Fur Coat"),
        .description = COMPOUND_STRING("Raises Defense."),
        .longDescription = COMPOUND_STRING("Halves the damage the\n"
                                           "Pokémon takes from\n"
                                           "physical moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MAGICIAN] =
    {
        .name = _("Magician"),
        .description = COMPOUND_STRING("Steals the foe's held item."),
        .longDescription = COMPOUND_STRING("If the Pokémon is not\n"
                                           "already holding an item,\n"
                                           "it will steal the held\n"
                                           "item from targets it\n"
                                           "deals damage to with\n"
                                           "its moves."),
        .aiRating = 3,
    },

    [ABILITY_BULLETPROOF] =
    {
        .name = _("Bulletproof"),
        .description = COMPOUND_STRING("Avoids some projectiles."),
        .longDescription = COMPOUND_STRING("The Pokémon is immune\n"
                                           "to ball and bomb moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_COMPETITIVE] =
    {
        .name = _("Competitive"),
        .description = COMPOUND_STRING("Lowered stats up Sp. Atk."),
        .longDescription = COMPOUND_STRING("When the Pokémon has any\n"
                                           "of its stats lowered by\n"
                                           "an opponent, its\n"
                                           "Sp. Atk stat is boosted\n"
                                           "by 2 stages."),
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .name = _("Strong Jaw"),
        .description = COMPOUND_STRING("Boosts biting moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's biting moves\n"
                                           "by 50%."),
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .name = _("Refrigerate"),
        .description = COMPOUND_STRING("Normal moves become Ice."),
        .longDescription = COMPOUND_STRING("The Pokémon's Normal-\n"
                                           "type moves become Ice-\n"
                                           "type moves and their\n"
                                           #if B_ATE_MULTIPLIER < GEN_7
                                           "power is boosted by 30%."
                                           #else
                                           "power is boosted by 20%."
                                           #endif
                                           ),
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .name = _("Sweet Veil"),
        .description = COMPOUND_STRING("Prevents party from sleep."),
        .longDescription = COMPOUND_STRING("The Pokémon and its\n"
                                           "allies cannot become\n"
                                           "drowsy or be put to \n"
                                           "sleep. "),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .name = _("Stance Change"),
        .description = COMPOUND_STRING("Transforms as it battles."),
        .longDescription = COMPOUND_STRING("The Pokémon changes\n"
                                           "into its Blade Forme\n"
                                           "when it attacks and\n"
                                           "changes into its Shield \n"
                                           "Forme when it uses the\n"
                                           "move King's Shield."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_GALE_WINGS] =
    {
        .name = _("Gale Wings"),
        .description = COMPOUND_STRING("Flying moves go first."),
        .longDescription = COMPOUND_STRING("Increases the priority\n"
                                           "of the Pokémon's Flying-\n"
                                           #if B_GALE_WINGS < GEN_7
                                           "type moves by 1 stage."
                                           #else
                                           "type moves by 1 stage.\n"
                                           "while its HP is full."
                                           #endif
                                           ),
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .name = _("Mega Launcher"),
        .description = COMPOUND_STRING("Boosts pulse moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's pulse moves\n"
                                           "by 50%."),
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .name = _("Grass Pelt"),
        .description = COMPOUND_STRING("Ups Defense in grass."),
        .longDescription = COMPOUND_STRING("Boosts the Pokémon's\n"
                                           "Defense stat on Grassy\n"
                                           "Terrain by 50%."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .name = _("Symbiosis"),
        .description = COMPOUND_STRING("Passes its item to an ally."),
        .longDescription = COMPOUND_STRING("When an ally consumes\n"
                                           " an item, the Pokémon\n"
                                           " gives its own held item\n"
                                           " to that ally."),
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .name = _("Tough Claws"),
        .description = COMPOUND_STRING("Boosts contact moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Pokémon's contact moves\n"
                                           "by 30%."),
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .name = _("Pixilate"),
        .description = COMPOUND_STRING("Normal moves become Fairy."),
        .longDescription = COMPOUND_STRING("The Pokémon's Normal-\n"
                                           "type moves become Ice-\n"
                                           "type moves and their\n"
                                           #if B_ATE_MULTIPLIER < GEN_7
                                           "power is boosted by 30%."
                                           #else
                                           "power is boosted by 20%."
                                           #endif
                                           ),
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .name = _("Gooey"),
        .description = COMPOUND_STRING("Lowers Speed on contact."),
        .longDescription = COMPOUND_STRING("When the Pokémon is hit\n"
                                           "by a contact move, the\n"
                                           "attacker's Speed stat is\n"
                                           "lowered by 1 stage. "),
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .name = _("Aerilate"),
        .description = COMPOUND_STRING("Normal moves become Flying."),
        .longDescription = COMPOUND_STRING("The Pokémon's Normal-\n"
                                           "type moves become\n"
                                           "Flying-type moves and\n"
                                           "their power is boosted\n"
                                           #if B_ATE_MULTIPLIER < GEN_7
                                           "by 30%."
                                           #else
                                           "by 20%."
                                           #endif
                                           ),
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .name = _("Parental Bond"),
        .description = COMPOUND_STRING("Moves hit twice."),
        .longDescription = COMPOUND_STRING("The parent and child\n"
                                           "attack one after the\n"
                                           "other. The power of the\n"
                                           #if B_PARENTAL_BOND_DMG < GEN_7
                                           "child's attacks is 1/2\n"
                                           #else
                                           "child's attacks is 1/4\n"
                                           #endif
                                           "of those of the parent."),
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .name = _("Dark Aura"),
        .description = COMPOUND_STRING("Boosts Dark moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Dark-type moves of all\n"
                                           "Pokémon on the field by\n"
                                           "33%."),
        .aiRating = 6,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .name = _("Fairy Aura"),
        .description = COMPOUND_STRING("Boosts Fairy moves."),
        .longDescription = COMPOUND_STRING("Boosts the power of the\n"
                                           "Fairy-type moves of all\n"
                                           "Pokémon on the field\n"
                                           "by 33%."),
        .aiRating = 6,
    },

    [ABILITY_AURA_BREAK] =
    {
        .name = _("Aura Break"),
        .description = COMPOUND_STRING("Reverse aura abilities."),
        .longDescription = COMPOUND_STRING("The effects of “Aura”\n"
                                           "Abilities are reversed\n"
                                           "to lower the power of\n"
                                           "affected moves."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .name = _("Primordial Sea"),
        .description = COMPOUND_STRING("Summons heavy rain."),
        .longDescription = COMPOUND_STRING("While on the field, the\n"
                                           "Pokémon changes the\n"
                                           "weather to a heavy\n"
                                           "rain that nullifies\n"
                                           "Fire-type attacks."),
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .name = _("Desolate Land"),
        .description = COMPOUND_STRING("Summons intense sunlight."),
        .longDescription = COMPOUND_STRING("While on the field, the\n"
                                           "Pokémon changes the\n"
                                           "weather to a harsh\n"
                                           "sunlight that nullifies\n"
                                           "Fire-type attacks."),
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .name = _("Delta Stream"),
        .description = COMPOUND_STRING("Summons strong winds."),
        .longDescription = COMPOUND_STRING("While on the field, the\n"
                                           "Pokémon changes the\n"
                                           "weather to a strong\n"
                                           "wind so that no moves\n"
                                           "are super effective\n"
                                           "against the Flying type."),
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .name = _("Stamina"),
        .description = COMPOUND_STRING("Boosts Defense when hit."),
        .longDescription = COMPOUND_STRING("When the Pokémon takes\n"
                                           "damage from a move,\n"
                                           "its Defense stat is\n"
                                           "boosted by 1 stage."),
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .name = _("Wimp Out"),
        .description = COMPOUND_STRING("Flees at half HP."),
        .longDescription = COMPOUND_STRING("The Pokémon cowardly\n"
                                           "switches out when its HP\n"
                                           "drops to half or less."),
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .name = _("Emergency Exit"),
        .description = COMPOUND_STRING("Flees at half HP."),
        .longDescription = COMPOUND_STRING("The Pokémon, sensing\n"
                                           "danger, switches out\n"
                                           "when its HP drops to\n"
                                           "half or less."),
        .aiRating = 3,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .name = _("Water Compaction"),
        .description = COMPOUND_STRING("Water boosts Defense."),
        .longDescription = COMPOUND_STRING("Boosts the Defense stat\n"
                                           "sharply when the Pokémon\n"
                                           "is hit by a Water-type\n"
                                           "move."),
        .aiRating = 4,
    },

    [ABILITY_MERCILESS] =
    {
        .name = _("Merciless"),
        .description = COMPOUND_STRING("Criticals poisoned foes."),
        .longDescription = COMPOUND_STRING("The Pokémon's attacks\n"
                                           "become critical hits if\n"
                                           "the target is poisoned\n"
                                           "or badly poisoned."),
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .name = _("Shields Down"),
        .description = COMPOUND_STRING("Shell breaks at half HP."),
        .longDescription = COMPOUND_STRING("Starts in a shell form\n"
                                           "with defensive stats\n"
                                           "and cannot gain major\n"
                                           "status ailments. At 50%\n"
                                           "HP or lower, the shell\n"
                                           "breaks and the Pokémon\n"
                                           "takes on a form with\n"
                                           "more offensive stats."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_STAKEOUT] =
    {
        .name = _("Stakeout"),
        .description = COMPOUND_STRING("Stronger as foes switch in."),
        .longDescription = COMPOUND_STRING("Doubles the damage dealt\n"
                                           "to a target that has\n"
                                           "just switched into\n"
                                           "battle that turn. Does\n"
                                           "not count the switching\n"
                                           "in at the very start of\n"
                                           "battle."),
        .aiRating = 6,
    },

    [ABILITY_WATER_BUBBLE] =
    {
        .name = _("Water Bubble"),
        .description = COMPOUND_STRING("Guards from fire and burns."),
        .longDescription = COMPOUND_STRING("Halves the damage \n"
                                           "Pokémon takes from Fire-\n"
                                           "type moves and doubles\n"
                                           "the power of its Water-\n"
                                           "type moves. The Pokémon\n"
                                           "cannot be burned."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_STEELWORKER] =
    {
        .name = _("Steelworker"),
        .description = COMPOUND_STRING("Powers up Steel moves."),
        .longDescription = COMPOUND_STRING("Powers up Steel-type\n"
                                           "moves by 50%."),
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .name = _("Berserk"),
        .description = COMPOUND_STRING("Boosts Sp. Atk at low HP."),
        .longDescription = COMPOUND_STRING("Boosts Sp. Atk at low\n"
                                           "HP.                     \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_SLUSH_RUSH] =
    {
        .name = _("Slush Rush"),
        .description = COMPOUND_STRING("Raises Speed in Hail/Snow."),
        .longDescription = COMPOUND_STRING("Raises Speed in\n"
                                           "Hail/Snow.              \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_LONG_REACH] =
    {
        .name = _("Long Reach"),
        .description = COMPOUND_STRING("Never makes contact."),
        .longDescription = COMPOUND_STRING("Never makes contact.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .name = _("Liquid Voice"),
        .description = COMPOUND_STRING("Makes sound moves Water."),
        .longDescription = COMPOUND_STRING("Makes sound moves Water.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .name = _("Triage"),
        .description = COMPOUND_STRING("Healing moves go first."),
        .longDescription = COMPOUND_STRING("Healing moves go first.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .name = _("Galvanize"),
        .description = COMPOUND_STRING("Normal moves turn Electric."),
        .longDescription = COMPOUND_STRING("Normal moves turn\n"
                                           "Electric.               \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_SURGE_SURFER] =
    {
        .name = _("Surge Surfer"),
        .description = COMPOUND_STRING("Faster on electricity."),
        .longDescription = COMPOUND_STRING("Faster on electricity.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .name = _("Schooling"),
        .description = COMPOUND_STRING("Forms a school when strong."),
        .longDescription = COMPOUND_STRING("Forms a school when\n"
                                           "strong.                 \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_DISGUISE] =
    {
        .name = _("Disguise"),
        .description = COMPOUND_STRING("Decoy protects it once."),
        .longDescription = COMPOUND_STRING("Decoy protects it once.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
        .breakable = TRUE,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_BATTLE_BOND] =
    {
        .name = _("Battle Bond"),
        .description = COMPOUND_STRING("Changes form after a KO."),
        .longDescription = COMPOUND_STRING("Changes form after a KO.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_POWER_CONSTRUCT] =
    {
        .name = _("Power Construct"),
        .description = COMPOUND_STRING("Cells aid it when weakened."),
        .longDescription = COMPOUND_STRING("Cells aid it when\n"
                                           "weakened.               \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_CORROSION] =
    {
        .name = _("Corrosion"),
        .description = COMPOUND_STRING("Poisons any type."),
        .longDescription = COMPOUND_STRING("Poisons any type.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .name = _("Comatose"),
        .description = COMPOUND_STRING("Always drowsing."),
        .longDescription = COMPOUND_STRING("Always drowsing.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_QUEENLY_MAJESTY] =
    {
        .name = _("Queenly Majesty"),
        .description = COMPOUND_STRING("Protects from priority."),
        .longDescription = COMPOUND_STRING("Protects from priority.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_INNARDS_OUT] =
    {
        .name = _("Innards Out"),
        .description = COMPOUND_STRING("Hurts foe when defeated."),
        .longDescription = COMPOUND_STRING("Hurts foe when defeated.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .name = _("Dancer"),
        .description = COMPOUND_STRING("Dances along with others."),
        .longDescription = COMPOUND_STRING("Dances along with\n"
                                           "others.                 \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .name = _("Battery"),
        .description = COMPOUND_STRING("Boosts ally's Sp. Atk."),
        .longDescription = COMPOUND_STRING("Boosts ally's Sp. Atk.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 0,
    },

    [ABILITY_FLUFFY] =
    {
        .name = _("Fluffy"),
        .description = COMPOUND_STRING("Tougher but flammable."),
        .longDescription = COMPOUND_STRING("Tougher but flammable.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .name = _("Dazzling"),
        .description = COMPOUND_STRING("Protects from priority."),
        .longDescription = COMPOUND_STRING("Protects from priority.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SOUL_HEART] =
    {
        .name = _("Soul-Heart"),
        .description = COMPOUND_STRING("KOs raise Sp. Atk."),
        .longDescription = COMPOUND_STRING("KOs raise Sp. Atk.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .name = _("Tangling Hair"),
        .description = COMPOUND_STRING("Lowers Speed on contact."),
        .longDescription = COMPOUND_STRING("Lowers Speed on contact.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .name = _("Receiver"),
        .description = COMPOUND_STRING("Copies ally's ability."),
        .longDescription = COMPOUND_STRING("Copies ally's ability.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .name = _("Power Of Alchemy"),
        .description = COMPOUND_STRING("Copies ally's ability."),
        .longDescription = COMPOUND_STRING("Copies ally's ability.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .name = _("Beast Boost"),
        .description = COMPOUND_STRING("KOs boost best stat."),
        .longDescription = COMPOUND_STRING("KOs boost best stat.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .name = _("RKS System"),
        .description = COMPOUND_STRING("Memories change its type."),
        .longDescription = COMPOUND_STRING("Memories change its\n"
                                           "type.                   \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTRIC_SURGE] =
    {
        .name = _("Electric Surge"),
        .description = COMPOUND_STRING("Field becomes Electric."),
        .longDescription = COMPOUND_STRING("Field becomes Electric.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .name = _("Psychic Surge"),
        .description = COMPOUND_STRING("Field becomes weird."),
        .longDescription = COMPOUND_STRING("Field becomes weird.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .name = _("Misty Surge"),
        .description = COMPOUND_STRING("Field becomes misty."),
        .longDescription = COMPOUND_STRING("Field becomes misty.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .name = _("Grassy Surge"),
        .description = COMPOUND_STRING("Field becomes grassy."),
        .longDescription = COMPOUND_STRING("Field becomes grassy.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .name = _("Full Metal Body"),
        .description = COMPOUND_STRING("Prevents stat reduction."),
        .longDescription = COMPOUND_STRING("Prevents stat reduction.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
    },

    [ABILITY_SHADOW_SHIELD] =
    {
        .name = _("Shadow Shield"),
        .description = COMPOUND_STRING("Halves damage at full HP."),
        .longDescription = COMPOUND_STRING("Halves damage at full\n"
                                           "HP.                     \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .name = _("Prism Armor"),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .longDescription = COMPOUND_STRING("Weakens\n"
                                           "“supereffective”.       \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .name = _("Neuroforce"),
        .description = COMPOUND_STRING("Ups “supereffective”."),
        .longDescription = COMPOUND_STRING("Ups “supereffective”.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
    },

    [ABILITY_INTREPID_SWORD] =
    {
        .name = _("Intrepid Sword"),
        .description = COMPOUND_STRING("Ups Attack on entry."),
        .longDescription = COMPOUND_STRING("Ups Attack on entry.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
    },

    [ABILITY_DAUNTLESS_SHIELD] =
    {
        .name = _("Dauntless Shield"),
        .description = COMPOUND_STRING("Ups Defense on entry."),
        .longDescription = COMPOUND_STRING("Ups Defense on entry.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
    },

    [ABILITY_LIBERO] =
    {
        .name = _("Libero"),
        .description = COMPOUND_STRING("Changes type to move's."),
        .longDescription = COMPOUND_STRING("Changes type to move's.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
    },

    [ABILITY_BALL_FETCH] =
    {
        .name = _("Ball Fetch"),
        .description = COMPOUND_STRING("Fetches failed Poké Ball."),
        .longDescription = COMPOUND_STRING("Fetches failed\n"
                                           "Poké Ball.              \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 0,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .name = _("Cotton Down"),
        .description = COMPOUND_STRING("Lower Speed of all when hit."),
        .longDescription = COMPOUND_STRING("Lower Speed of all when\n"
                                           "hit.                    \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .name = _("Propeller Tail"),
        .description = COMPOUND_STRING("Ignores foe's redirection."),
        .longDescription = COMPOUND_STRING("Ignores foe's\n"
                                           "redirection.            \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .name = _("Mirror Armor"),
        .description = COMPOUND_STRING("Reflect stat decreases."),
        .longDescription = COMPOUND_STRING("Reflect stat decreases.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .name = _("Gulp Missile"),
        .description = COMPOUND_STRING("If hit, spits prey from sea."),
        .longDescription = COMPOUND_STRING("If hit, spits prey from\n"
                                           "sea.                    \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
        .cantBeCopied = B_UPDATED_MOVE_FLAGS <= GEN_8,
        .cantBeSwapped = B_UPDATED_MOVE_FLAGS <= GEN_8,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STALWART] =
    {
        .name = _("Stalwart"),
        .description = COMPOUND_STRING("Ignores foe's redirection."),
        .longDescription = COMPOUND_STRING("Ignores foe's\n"
                                           "redirection.            \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .name = _("Steam Engine"),
        .description = COMPOUND_STRING("Fire or Water hits up Speed."),
        .longDescription = COMPOUND_STRING("Fire or Water hits up\n"
                                           "Speed.                  \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .name = _("Punk Rock"),
        .description = COMPOUND_STRING("Ups and resists sound."),
        .longDescription = COMPOUND_STRING("Ups and resists sound.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .name = _("Sand Spit"),
        .description = COMPOUND_STRING("Creates a sandstorm if hit."),
        .longDescription = COMPOUND_STRING("Creates a sandstorm if\n"
                                           "hit.                    \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .name = _("Ice Scales"),
        .description = COMPOUND_STRING("Halves special damage."),
        .longDescription = COMPOUND_STRING("Halves special damage.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .name = _("Ripen"),
        .description = COMPOUND_STRING("Doubles effect of Berries."),
        .longDescription = COMPOUND_STRING("Doubles effect of\n"
                                           "Berries.                \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
    },

    [ABILITY_ICE_FACE] =
    {
        .name = _("Ice Face"),
        .description = COMPOUND_STRING("Hail or Snow renew free hit."),
        .longDescription = COMPOUND_STRING("Hail or Snow renew free\n"
                                           "hit.                    \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .breakable = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_SPOT] =
    {
        .name = _("Power Spot"),
        .description = COMPOUND_STRING("Powers up ally moves."),
        .longDescription = COMPOUND_STRING("Powers up ally moves.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .name = _("Mimicry"),
        .description = COMPOUND_STRING("Changes type on terrain."),
        .longDescription = COMPOUND_STRING("Changes type on terrain.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .name = _("Screen Cleaner"),
        .description = COMPOUND_STRING("Removes walls of light."),
        .longDescription = COMPOUND_STRING("Removes walls of light.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .name = _("Steely Spirit"),
        .description = COMPOUND_STRING("Boosts ally's Steel moves."),
        .longDescription = COMPOUND_STRING("Boosts ally's Steel\n"
                                           "moves.                  \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
    },

    [ABILITY_PERISH_BODY] =
    {
        .name = _("Perish Body"),
        .description = COMPOUND_STRING("Foe faints in 3 turns if hit."),
        .longDescription = COMPOUND_STRING("Foe faints in 3 turns if\n"
                                           "hit.                    \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = -1,
    },

    [ABILITY_WANDERING_SPIRIT] =
    {
        .name = _("Wandering Spirit"),
        .description = COMPOUND_STRING("Trade abilities on contact."),
        .longDescription = COMPOUND_STRING("Trade abilities on\n"
                                           "contact.                \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .name = _("Gorilla Tactics"),
        .description = COMPOUND_STRING("Ups Attack and locks move."),
        .longDescription = COMPOUND_STRING("Ups Attack and locks\n"
                                           "move.                   \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .name = _("Neutralizing Gas"),
        .description = COMPOUND_STRING("All Abilities are nullified."),
        .longDescription = COMPOUND_STRING("All Abilities are\n"
                                           "nullified.              \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .name = _("Pastel Veil"),
        .description = COMPOUND_STRING("Protects team from poison."),
        .longDescription = COMPOUND_STRING("Protects team from\n"
                                           "poison.                 \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .name = _("Hunger Switch"),
        .description = COMPOUND_STRING("Changes form each turn."),
        .longDescription = COMPOUND_STRING("Changes form each turn.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUICK_DRAW] =
    {
        .name = _("Quick Draw"),
        .description = COMPOUND_STRING("Moves first occasionally."),
        .longDescription = COMPOUND_STRING("Moves first\n"
                                           "occasionally.           \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .name = _("Unseen Fist"),
        .description = COMPOUND_STRING("Contact evades protection."),
        .longDescription = COMPOUND_STRING("Contact evades\n"
                                           "protection.             \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .name = _("Curious Medicine"),
        .description = COMPOUND_STRING("Remove ally's stat changes."),
        .longDescription = COMPOUND_STRING("Remove ally's stat\n"
                                           "changes.                \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .name = _("Transistor"),
        .description = COMPOUND_STRING("Ups Electric-type moves."),
        .longDescription = COMPOUND_STRING("Ups Electric-type moves.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .name = _("Dragon's Maw"),
        .description = COMPOUND_STRING("Ups Dragon-type moves."),
        .longDescription = COMPOUND_STRING("Ups Dragon-type moves.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .name = _("Chilling Neigh"),
        .description = COMPOUND_STRING("KOs boost Attack stat."),
        .longDescription = COMPOUND_STRING("KOs boost Attack stat.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .name = _("Grim Neigh"),
        .description = COMPOUND_STRING("KOs boost Sp. Atk stat."),
        .longDescription = COMPOUND_STRING("KOs boost Sp. Atk stat.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .name = _("As One"),
        .description = COMPOUND_STRING("Unnerve and Chilling Neigh."),
        .longDescription = COMPOUND_STRING("Unnerve and\n"
                                           "Chilling Neigh          \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_AS_ONE_SHADOW_RIDER] =
    {
        .name = _("As One"),
        .description = COMPOUND_STRING("Unnerve and Grim Neigh."),
        .longDescription = COMPOUND_STRING("Unnerve and Grim Neigh.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_LINGERING_AROMA] =
    {
        .name = _("Lingering Aroma"),
        .description = COMPOUND_STRING("Spreads with contact."),
        .longDescription = COMPOUND_STRING("Spreads with contact.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .name = _("Seed Sower"),
        .description = COMPOUND_STRING("Affects terrain when hit."),
        .longDescription = COMPOUND_STRING("Affects terrain when\n"
                                           "hit.                    \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .name = _("Thermal Exchange"),
        .description = COMPOUND_STRING("Fire hits up Attack."),
        .longDescription = COMPOUND_STRING("Fire hits up Attack.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .name = _("Anger Shell"),
        .description = COMPOUND_STRING("Gets angry at half HP."),
        .longDescription = COMPOUND_STRING("Gets angry at half HP.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .name = _("Purifying Salt"),
        .description = COMPOUND_STRING("Protected by pure salts."),
        .longDescription = COMPOUND_STRING("Protected by pure salts.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .name = _("Well-Baked Body"),
        .description = COMPOUND_STRING("Strengthened by Fire."),
        .longDescription = COMPOUND_STRING("Strengthened by Fire.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .name = _("Wind Rider"),
        .description = COMPOUND_STRING("Ups Attack if hit by wind."),
        .longDescription = COMPOUND_STRING("Ups Attack if hit by\n"
                                           "wind.                   \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .name = _("Guard Dog"),
        .description = COMPOUND_STRING("Cannot be intimidated."),
        .longDescription = COMPOUND_STRING("Cannot be intimidated.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .name = _("Rocky Payload"),
        .description = COMPOUND_STRING("Powers up Rock moves."),
        .longDescription = COMPOUND_STRING("Powers up Rock moves.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
    },

    [ABILITY_WIND_POWER] =
    {
        .name = _("Wind Power"),
        .description = COMPOUND_STRING("Gets charged by wind."),
        .longDescription = COMPOUND_STRING("Gets charged by wind.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
    },

    [ABILITY_ZERO_TO_HERO] =
    {
        .name = _("Zero to Hero"),
        .description = COMPOUND_STRING("Changes form on switch out."),
        .longDescription = COMPOUND_STRING("Changes form on switch\n"
                                           "out.                    \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_COMMANDER] =
    {
        .name = _("Commander"),
        .description = COMPOUND_STRING("Commands from Dondozo."),
        .longDescription = COMPOUND_STRING("Commands from Dondozo.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .name = _("Electromorphosis"),
        .description = COMPOUND_STRING("Gets Charged when hit."),
        .longDescription = COMPOUND_STRING("Gets Charged when hit.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .name = _("Protosynthesis"),
        .description = COMPOUND_STRING("Sun boosts best stat."),
        .longDescription = COMPOUND_STRING("Sun boosts best stat.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .name = _("Quark Drive"),
        .description = COMPOUND_STRING("Elec. field ups best stat."),
        .longDescription = COMPOUND_STRING("Elec. field ups best\n"
                                           "stat.                   \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .name = _("Good as Gold"),
        .description = COMPOUND_STRING("Avoids status moves."),
        .longDescription = COMPOUND_STRING("Avoids status moves.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .name = _("Vessel of Ruin"),
        .description = COMPOUND_STRING("Lowers foes' sp. damage."),
        .longDescription = COMPOUND_STRING("Lowers foes' sp. damage.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .name = _("Sword of Ruin"),
        .description = COMPOUND_STRING("Lowers foes' Defense."),
        .longDescription = COMPOUND_STRING("Lowers foes' Defense.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .name = _("Tablets of Ruin"),
        .description = COMPOUND_STRING("Lowers foes' damage."),
        .longDescription = COMPOUND_STRING("Lowers foes' damage.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .name = _("Beads of Ruin"),
        .description = COMPOUND_STRING("Lowers foes' Sp. Defense."),
        .longDescription = COMPOUND_STRING("Lowers foes'\n"
                                           "Sp. Defense.            \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .name = _("Orichalcum Pulse"),
        .description = COMPOUND_STRING("Summons sunlight in battle."),
        .longDescription = COMPOUND_STRING("Summons sunlight in\n"
                                           "battle.                 \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .name = _("Hadron Engine"),
        .description = COMPOUND_STRING("Field becomes Electric."),
        .longDescription = COMPOUND_STRING("Field becomes Electric.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .name = _("Opportunist"),
        .description = COMPOUND_STRING("Copies foe's stat change."),
        .longDescription = COMPOUND_STRING("Copies foe's stat\n"
                                           "change.                 \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .name = _("Cud Chew"),
        .description = COMPOUND_STRING("Eats a used berry again."),
        .longDescription = COMPOUND_STRING("Eats a used berry again.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .name = _("Sharpness"),
        .description = COMPOUND_STRING("Strengthens slicing moves."),
        .longDescription = COMPOUND_STRING("Strengthens slicing\n"
                                           "moves.                  \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .name = _("Supreme Overlord"),
        .description = COMPOUND_STRING("Inherits fallen's strength."),
        .longDescription = COMPOUND_STRING("Inherits fallen's\n"
                                           "strength.               \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .name = _("Costar"),
        .description = COMPOUND_STRING("Copies ally's stat changes."),
        .longDescription = COMPOUND_STRING("Copies ally's stat\n"
                                           "changes.                \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .name = _("Toxic Debris"),
        .description = COMPOUND_STRING("Throws poison spikes if hit."),
        .longDescription = COMPOUND_STRING("Throws poison spikes if\n"
                                           "hit.                    \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .name = _("Armor Tail"),
        .description = COMPOUND_STRING("Protects from priority."),
        .longDescription = COMPOUND_STRING("Protects from priority.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .name = _("Earth Eater"),
        .description = COMPOUND_STRING("Eats ground to heal HP."),
        .longDescription = COMPOUND_STRING("Eats ground to heal HP.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .name = _("Mycelium Might"),
        .description = COMPOUND_STRING("Status moves never fail."),
        .longDescription = COMPOUND_STRING("Status moves never fail.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .name = _("Hospitality"),
        .description = COMPOUND_STRING("Restores ally's HP."),
        .longDescription = COMPOUND_STRING("Restores ally's HP.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .name = _("Mind's Eye"),
        .description = COMPOUND_STRING("Keen Eye and Scrappy."),
        .longDescription = COMPOUND_STRING("Keen Eye and Scrappy.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Speed."),
        .longDescription = COMPOUND_STRING("Raises Speed.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Attack."),
        .longDescription = COMPOUND_STRING("Raises Attack.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Sp. Def."),
        .longDescription = COMPOUND_STRING("Raises Sp. Def.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .name = _("Embody Aspect"),
        .description = COMPOUND_STRING("Raises Defense."),
        .longDescription = COMPOUND_STRING("Raises Defense.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .name = _("Toxic Chain"),
        .description = COMPOUND_STRING("Moves can poison."),
        .longDescription = COMPOUND_STRING("Moves can poison.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .name = _("Supersweet Syrup"),
        .description = COMPOUND_STRING("Lowers the foe's Evasion."),
        .longDescription = COMPOUND_STRING("Lowers the foe's\n"
                                           "Evasion.                \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .name = _("Tera Shift"),
        .description = COMPOUND_STRING("Terastallizes upon entry."),
        .longDescription = COMPOUND_STRING("Terastallizes upon\n"
                                           "entry.                  \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TERA_SHELL] =
    {
        .name = _("Tera Shell"),
        .description = COMPOUND_STRING("Resists all at full HP."),
        .longDescription = COMPOUND_STRING("Resists all at full HP.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .name = _("Teraform Zero"),
        .description = COMPOUND_STRING("Zeroes weather and terrain."),
        .longDescription = COMPOUND_STRING("Zeroes weather and\n"
                                           "terrain.                \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .name = _("Poison Puppeteer"),
        .description = COMPOUND_STRING("Confuses poisoned foes."),
        .longDescription = COMPOUND_STRING("Confuses poisoned foes.\n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        \n"
                                           "                        "),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },
};
