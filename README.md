<img width="480" height="320" alt="image" src="https://github.com/user-attachments/assets/eb38a05c-d586-4659-b045-420c603e9ec1" /> <img width="480" height="320" alt="image" src="https://github.com/user-attachments/assets/6c43a30a-728d-4973-8665-8d725fc44448" />

This Trait and Items branch combines the features found in Trait System an Multi Items to allow multiple abilities and held items to be used by your Pokemon.

# Trait System (Release 1.14.3)

This is the full release of the Multi-Ability function I'm calling the Trait System!
Currently updated to Pokeemerald Expansion 1.14.3

The Trait System allows you to assign more than one ability to each pokemon for more complex and more interesting setups.

- General terminology I'm going for is:
   - Ability = Same as vanilla.
   - Innate = Additional abilities that are the same for all members of a species.
   - Trait = Encompassing term for either one
  Note: for the sake of making merging a little easier, "Ability" is still used in many places when "Trait" is intended.
- Abilities work exactly the same as vanilla where a pokemon could have one of 3 ability options, however Innates are fixed to each species and don't change.
- To add Innates you just need to add a new .innates parameter underneath the existing .abilities one using the same formatting.  Example innate setups have been included commented out for all pokemon in the Gen 1 families.
   - ex: .innates = { ABILITY_PROTEAN, ABILITY_ROUGH_SKIN, ABILITY_CLEAR_BODY },
- Uses the MAX_MON_INNATES variable to control how many Innates are available, default is 3 totaling up to 4 active abilities per pokemon.  If you assign more innates than the max, surplus entries will simply be ignored.  This means you could even set MAX_MON_INATES to 0 and you would functionally just get the original vanilla system. Currently does not support setting innates to 0 so if you only want the Multi Items feature then the standalone version would be best.
- There is a new Summary Page "Traits" to display the four slots along with some color changes across the vanilla pages for color balance.
- Most effects that target Abilities still only target a pokemon's primary Ability, ignoring their Innates.  Neutralizing Gas, Worry Seed, Trace, and Mummy for example all only affect Abilities but not Innates.  Mold Breaker type Traits however work on everything, including Innates.  (NOTE: Trace is also not designed to be an Innate since it replaces itself as part of its effect.  Trace in particular should ALWAYS be assigned as an Ability or else you'll get an infinite loop lock.)
- The basic code design is all Ability checks have been replaced with Trait checks, reading all passives a pokemon has whenever an Ability is looked for.  All previously mutually exclusive abilities like the weather ones which use a Switch Case format has been replaced with If statements so that they can all be called anyway (though natually any abilities that actually conflict will overwrite by code order, Drought and Snow Warning will both activate, but Snow Warning is later in the list so ultimately the weather will be snow/hail.  Really this is only a consideration for future randomizer settings.)
- Reffer to the AbilityEffect enum table for a more detailed list of how timing interactions work.  Most abilities will interact fine but there are exceptions such as abilities which activate during a terrain or weather change where only one ability in that timing window will activate at a time.
- If activated at the same time for the same item slot, Harvest, Pickup, and Ball Fetch will activate in that respective priority order.
- Ability popups have been modified into a Stack system so that when multiple abilities are triggered at once, they are stored then read out in the correct order.  Battle Message logic has also been updated to account for the new timings.
- Make Test system updated to account for Innates as well, all vanilla tests involving Abilities are given a second copy suffixed (Multi) where the tested Ability is instead an Innate.  There is also a new multi_abilities.c test file which contains more intensive innate specific tests such as potential conflicts in Traits or timings.
- A useful template for organizing pokemon and assigning Traits can be found here: https://docs.google.com/spreadsheets/d/1pNtGGapXx20svfM0PpztHYHJnbgvXHS8tc_i-h0a0Po/edit?gid=0#gid=0
Note that the Data sheet includes a collumn for automatically generating the .innate line to be added into Expansion's lists based on how you fill out the Pokemon's innate list.

- The AI system largely works the same just with Innates added on top and fixed.  This means the AI can still treat Abilities as unknown until they learn what the Ability is directly, but Innates will always be treated as known.

Basic code bedrock design comes from old Emerald Redux code with permission.

Huge thanks to the RH Hideout discord community for their help, advice, and testing, especially Alex, Surskitty, Kleem, Meister_anon, and MGriffin who helped make this possible.


# Multi-Items (Release 1.14.3)

This is the full release of a Multi-Item system which allows pokemon to hold more than one item at a time. By default this feature branch provides a second held item slot but it can be modified for more or less fairly easily. Currently updated to Pokeemerald Expansion 1.14.3.

- Battle Behavior:
	- Item activations generally happen once per opportunity and by first slot.  For example if you have a poisoned and injured pokemon switch in with a healing and a poison cure berry, the healing berry will be eaten and the poison berry has to wait until the next activation chance like after an attack.
	- Some windows have exceptions such as the Terrain Seeds which have a sort of special activation sequence and can stack with Room Service.
	- As a result, Air Balloon's intro message and Rocky Helm are given low priority so they don't always overwrite the other effects in their window.  Likewise, Air Balloon popping is given higher priority to prevent it from being shielded by other items.
	- Leftovers and Black Sludge are given a special exception where both can activate together.  The message will give Black Sludge priority but the resulting HP change is the total between the two.
	- Shell Bell and Life Orb are given a special exception where both can activate together, the resulting message will be based on whether healing or damage is greater.
	- Passive items that don't need explicit activations such as Charcoal are always active and can also stack effects, though two copies of the exact same item will not stack. This also includes items that share the exact same effect such as the Incense items which directly copy the effects of other items, or how King's Rock and Razor Fang share the flinching on hit effect.
	- Battle effects that target opponent items first read which slots are viable targets then select based on the B_MULTI_ITEM_ORDER custom setting.  By default this is set to target latest to earliest, but it can be set to earliest to latest and to random.
	- Battle effects that move or restore items are locked to the slot. Thief can only steal if the target slot has an item AND the corresponding attacking pokemon's slot is empty.  Thief will not allocate a stolen item to a different free slot.
	- Fling uses B_MULTI_ITEM_ORDER selection of the attacker's items but also prioritizes non berry items first.
	- Acrobatics loses most but not all of its bonus if even one item is held, losing up to the full bonus as more items are held.
	- Unburden uses the same logic as Acrobatics where a partial bonus is given as long as some held item slots are empty.
	- In the event of Evolution using different held items (Clampearl), the first valid evolution will get priority and activate.  Also note that the evolution process eats all valid evolution items, so even though Clampearl will only evolve into Huntail, both Deep Sea items would get consumed in the process.

- Organization Behavior:
	- Items are given to pokemon in slots from first to last.
	- Items are taken from pokemon in slots from last to first.  This is so you can generally order items by importance where items in later slots are more likely to either be consumed or swapped around.
	- There is also a B_HELD_ITEM_CATEGORIZATION option which allows you to specify items to specific slots.  All items have an additional .heldSlot value to designate a slot.  When Categorization is enabled, items can only be given to pokemon under the heldSlot value the item is specified with.  This can for example let you set all berries to heldSlot 1, making slot one a designated berry only slot.
	- Swapping or moving items through the party or storage interfaces only work on the first slot item to avoid complicating the system.

- Developer Notes:
	- To use more than 2 items, you'll need to update the MAX_MON_ITEMS value in global.c and main.c along with creating additional MON_DATA_HELD_ITEM variables, allocating space for another helditem varibale in the PokemonSubstructs, and updating the summary screen to account for the new slots. Curently does not support setting to 1 and disabling the feature, if you only want the Trait System then the standalone version would be best.
	- The rest of the logic however will adjust for the slot numbers, so all the extra work is just in allocating the slot itself.
	- NOTE that since the held items are stored just before the moves, if you notice a pokemon's first move dissapear or change then that is likely due to the item logic mistakenly targeting a slot beyond what should be allowed.
    - A sample alternate Pokemon Skills page where Berries are specified instead of general Held Items is included.  Just rename the "page_skills(berry)" file to "page_skills", replacing the existing one, to use it.
	- Please report any bugs or suggestions to Bassforte in the RHH discord.

# About `pokeemerald-expansion`

![Gif that shows debugging functionality that is unique to pokeemerald-expansion such as rerolling Trainer ID, Cheat Start, PC from Debug Menu, Debug PC Fill, Pokémon Sprite Visualizer, Debug Warp to Map, and Battle Debug Menu](https://github.com/user-attachments/assets/cf9dfbee-4c6b-4bca-8e0a-07f116ef891c) ![Gif that shows overworld functionality that is unique to pokeemerald-expansion such as indoor running, BW2 style map popups, overworld followers, DNA Splicers, Gen 1 style fishing, OW Item descriptions, Quick Run from Battle, Use Last Ball, Wild Double Battles, and Catch from EXP](https://github.com/user-attachments/assets/383af243-0904-4d41-bced-721492fbc48e) ![Gif that shows off a number of modern Pokémon battle mechanics happening in the pokeemerald-expansion engine: 2 vs 1 battles, modern Pokémon, items, moves, abilities, fully customizable opponents and partners, Trainer Slides, and generational gimmicks](https://github.com/user-attachments/assets/50c576bc-415e-4d66-a38f-ad712f3316be)

<!-- If you want to re-record or change these gifs, here are some notes that I used: https://files.catbox.moe/05001g.md -->

**`pokeemerald-expansion`** is a GBA ROM hack base that equips developers with a comprehensive toolkit for creating Pokémon ROM hacks. **`pokeemerald-expansion`** is built on top of [pret's `pokeemerald`](https://github.com/pret/pokeemerald) decompilation project. **It is not a playable Pokémon game on its own.**

# [Features](FEATURES.md)

**`pokeemerald-expansion`** offers hundreds of features from various [core series Pokémon games](https://bulbapedia.bulbagarden.net/wiki/Core_series), along with popular quality-of-life enhancements designed to streamline development and improve the player experience. A full list of those features can be found in [`FEATURES.md`](FEATURES.md).

# [Credits](CREDITS.md)

 [![](https://img.shields.io/github/all-contributors/rh-hideout/pokeemerald-expansion/upcoming)](CREDITS.md)

If you use **`pokeemerald-expansion`**, please credit **RHH (Rom Hacking Hideout)**. Optionally, include the version number for clarity.

```
Based off RHH's pokeemerald-expansion 1.14.3 https://github.com/rh-hideout/pokeemerald-expansion/
```

Please consider [crediting all contributors](CREDITS.md) involved in the project!

# Choosing `pokeemerald` or **`pokeemerald-expansion`**

- **`pokeemerald-expansion`** supports multiplayer functionality with other games built on **`pokeemerald-expansion`**. It is not compatible with official Pokémon games.
- If compatibility with official games is important, use [`pokeemerald`](https://github.com/pret/pokeemerald). Otherwise, we recommend using **`pokeemerald-expansion`**.
- **`pokeemerald-expansion`** incorporates regular updates from `pokeemerald`, including bug fixes and documentation improvements.

# [Getting Started](INSTALL.md)

❗❗ **Important**: Do not use GitHub's "Download Zip" option as it will not include commit history. This is necessary if you want to update or merge other feature branches.

If you're new to git and GitHub, [Team Aqua's Asset Repo](https://github.com/Pawkkie/Team-Aquas-Asset-Repo/) has a [guide to forking and cloning the repository](https://github.com/Pawkkie/Team-Aquas-Asset-Repo/wiki/The-Basics-of-GitHub). Then you can follow one of the following guides:

## 📥 [Installing **`pokeemerald-expansion`**](INSTALL.md)
## 🏗️ [Building **`pokeemerald-expansion`**](INSTALL.md#Building-pokeemerald-expansion)
## 🚚 [Migrating from **`pokeemerald`**](INSTALL.md#Migrating-from-pokeemerald)
## 🚀 [Updating **`pokeemerald-expansion`**](INSTALL.md#Updating-pokeemerald-expansion)

# [Documentation](https://rh-hideout.github.io/pokeemerald-expansion/)

For detailed documentation, visit the [pokeemerald-expansion documentation page](https://rh-hideout.github.io/pokeemerald-expansion/).

# [Contributions](CONTRIBUTING.md)
If you are looking to [report a bug](CONTRIBUTING.md#Bug-Report), [open a pull request](CONTRIBUTING.md#Pull-Requests), or [request a feature](CONTRIBUTING.md#Feature-Request), our [`CONTRIBUTING.md`](CONTRIBUTING.md) has guides for each.

# [Community](https://discord.gg/6CzjAG6GZk)

[![](https://dcbadge.limes.pink/api/server/6CzjAG6GZk)](https://discord.gg/6CzjAG6GZk)

Our community uses the [ROM Hacking Hideout (RHH) Discord server](https://discord.gg/6CzjAG6GZk) to communicate and organize. Most of our discussions take place there, and we welcome anybody to join us!
