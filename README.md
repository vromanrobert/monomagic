# monomagic
Mono Magic is a thought experiment about Magic: The Gathering cards. 
The rules of Mono Magic:
1. All decks are exactly 60 copies of the same card.
2. Legendary rule is ignored.
3. Matches are two games with each deck going first once.
4. Each game win is 1 point, and each game loss is -1 point. Thus possible match points are -2, 0, or 2.
5. There are currently no match ups that can produce a draw within an individual game.
6. Games are replayed until the loser has exhausted all possible options.
7. All other rules of MtG are as normal, including mulligans.
8. Legal decks must be able to win 2-0 against 60 Plains OR
9. Be able to win 2-0 against a deck that satisfies rule 8.

As of the July 2021 release of Adventures in the Forgotten Realms, there are 77 mono magic cards.
This program simulates every possible decision in most the matchups.
There are essentially 4 tiers of programming complexity, from most difficult to easiest:
1. 9 Cards that can produce different power/tough creatures on the same side of the field.
2. 6 Cards that involve a player decision beyond attack-block configurations.
3. 54 Cards that never change p/t and have strictly linear line of play.
4. 8 Cards that more or less do not interact with the opponent.

The current version includes all of Tier 3 and 4 correctly, Tier 2 to varying completeness, and three of Tier 1.

NOT INCLUDED: Blinkmoth Nexus, Crawling Barrens, Den of the Bugbear, Lavaclaw Reaches, Lair of the Hydra, Mishra's Factory, Tangled Florahedron

PARTLY IMPLEMENTED: Inkmoth Nexus, Raging Ravine, Wandering Fumarole, Zoetic Cavern
