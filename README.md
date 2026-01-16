# Multi-Items (Full Release)

This is the full release of a Multi-Item system which allows pokemon to hold more than one item at a time. By default this feature branch provides a second held item slot but it can be modified for more or less fairly easily. Currently updated to Pokeemerald Expansion 1.13.1.

- Battle Behavior:
	- Item activations happen once per opportunity.  For example if you have two healing berries and your hp drops below half, only one berry will be eaten.  Likewise, eating a berry means nothing else will activate during that opportunity.
	- Due to the above, Leftovers is given the lowest priority to keep it from blocking every other item every turn, likewise Life Orb is given the highest priority so that its life drain cannot be sidestepped.  Though other effects can still trigger with Life Orb if you use a non-damaging move and thus don't trigger the life drain for that opportunity.
	- Passive items that don't need explicit activations such as Charcoal are always active and can also stack effects, though two copies of the exact same item will not stack.
	- Battle effects that target opponent items they first read which slots are viable targets then select based on the B_MULTI_ITEM_ORDER custom setting.  By default this is set to target latest to earliest, but it can be set to earliest to latest and to random.
	- Battle effects that move or restore items are locked to the slot. Thief can only steal if the target slot has an item AND the corresponding attacking pokemon's slot is empty.  Thief will not allocate a stolen item to a different free slot.
	- Fling uses B_MULTI_ITEM_ORDER selection of the attacker's items but also prioritizes non berry items first.
	- Acrobatics loses most but not all of its bonus if even one item is held, losing up to the full bonus as more items are held.

- Organization Behavior:
	- Items are given to pokemon in slots from first to last.
	- Items are taken from pokemon in slots from last to first.  This is so you can generally order items by importance where items in later slots are more likely to either be consumed or swapped around.
	- There is also a B_HELD_ITEM_CATEGORIZATION option which allows you to specify items to specific slots.  All items have an additional .heldSlot value to designate a slot.  When Categorization is enabled, items can only be given to pokemon under the heldSlot value the item is specified with.  This can for example let you set all berries to heldSlot 1, making slot one a designated berry only slot.
	- Swapping or moving items through the party or storage interfaces only work on the first slot item to avoid complicating the system.

- Developer Notes:
	- To use more than 2 items, you'll need to update the MAX_MON_ITEMS value in global.c and main.c along with creating additional MON_DATA_HELD_ITEM variables, allocating space for another helditem varibale in the PokemonSubstructs, and updating the summary screen to account for the new slots.
	- The rest of the logic however will adjust for the slot numbers, so all the extra work is just in allocating the slot itself.
	- NOTE that since the held items are stored just before the moves, if you notice a pokemon's first move dissapear or change then that is likely due to the item logic mistakenly targeting a slot beyond what should be allowed.
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
Based off RHH's pokeemerald-expansion 1.14.2 https://github.com/rh-hideout/pokeemerald-expansion/
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
