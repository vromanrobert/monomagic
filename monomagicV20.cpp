#include <iostream>
#include <string>
//#include <bits/stdc++.h>
#include <math.h>
using namespace std;

const string Tournament[80] = {"Akoum Warrior", "Allosaurus Rider", "Barbarian Ring", "Basking Rootwalla", "Blackbloom Rogue", "Blazing Rootwalla", "Blinkmoth Nexus", "Castle Ardenvale", "Cave of the Frost Dragon", "Celestial Colonnade", "Cephalid Coliseum", "Chancellor of the Dross", "Chancellor of the Forge", "Chancellor of the Spires", "Chancellor of the Tangle", "Cradle of the Accursed", "Crawling Barrens", "Creeping Tar Pit", "Den of the Bugbear", "Dread Statuary", "Dryad Arbor", "Dwarven Mine", "Elvish Spirit Guide", "Emeria's Call", "Faceless Haven", "Faerie Conclave", "Forbidding Watchtower", "Foundry of the Consuls", "Frostwalk Bastion", "Gargoyle Castle", "Ghitu Encampment", "Hall of the Storm Giants", "Hissing Quagmire", "Hive of the Eye Tyrant", "Hostile Desert", "Ichorid", "Inkmoth Nexus", "Ipnu Rivulet", "Kazandu Mammoth", "Keldon Megaliths", "Lair of the Hydra", "Lavaclaw Reaches", "Lumbering Falls", "Memnite", "Memorial to Glory", "Mishra's Factory", "Mobilized District", "Mutavault", "Needle Spires", "Nether Shadow", "Nether Spirit", "Piranha Marsh", "Raging Ravine", "Rath's Edge", "Rocket-Powered Turbo Slug", "Shambling Vent", "Simian Spirit Guide", "Skyclave Cleric", "Soul Spike", "Spawning Bed", "Spawning Pool", "Spikefield Hazard", "Stalking Stones", "Stirring Wildwood", "Sunscorched Desert", "Surgical Extraction", "Tangled Florahedron", "Tomb of Urami", "Treetop Village", "Umara Wizard", "Urza's Factory", "Urza's Saga", "Vine Dryad", "Wandering Fumarole", "Westvale Abbey", "Zoetic Cavern", "Zof Consumption", "Filler"};
int GameOver; //strict winner found
int Game; //current game#
int T; //current turn#
int TC; //Turn on which an alternate play for losing player is found
int Report; //reporting detail level
int SkipGame; //skip reports until this game#
int Pause; //enter any integer to continue
int count; //multi-purpose counter
int subcount; //nested counter
int ct3; //double nested counter
int Deployed; //how many available blockers are blocking
int w; //misc temp toggle
int Attacker; //current attacker # being processed
int Blocker; //current blocker # being processed
int AttackDam; //amount of damage attacking creature has dealt in current blocking exchange
int BlockDam; //amount of damage blocking creature(s) has dealt in current blocking exchange
int StrikeDead; //blockers killed by a first/dubstrike attacker OR attacker killed by burn
int BurnDam; //return damage dealt from burn function
bool PlayLand; //whether active player should play a land this turn
bool BurnLost; //flag if a burn deck loses to a creature deck
int OnFire; //how much burn damage current creature target has taken
int Spaces; //#characters in name for menu spacing
bool Override; //flag for stalemate game state
int CheckPoint; //turn on which stalemate forms
int LongGame; //the highest turn# of any game this match
int FlipTurn; //turn # on which a card has flipped
int ActualSkips; //# available blockers who for whatever reason did not end up blocking this turn
int BlockedAttackers; //# attackers this turn that are blocked
int BlockCheck; //counter for checking blocks
bool Survivor; //whether current combatant survives
bool Testy;

class Player{ //move functions out
	public:
		string Name; //deck name
		int Activate = 0; //# untapped lands in play required to activate an ability
		int Barrens = 0; //# +1/+1 counters added per activation
		int BigAttack = 0; //the most creatures this player has attacked w on any turn this game
		int Burn = 0; //this card can deal this much damage to attackers
		int CardEBT = 0; //non-land card that enters play tapped
		int Cost = 0; //# untapped lands in play required to play card from hand
		int Extract = 0; //card that eliminates enemy hand, yard, and library if they have this many cards in yard
		int Factory = 0; //creature has X:+1/+1
		int Flip = 0; //# creatures in play required to activate flip ability
		int Flora = 0; //creature that taps for this much mana
		int Hostile = 0; //creature must exile this many cards from yard to combat
		int Ichorid = 0; //creature that returns to play in upkeep by erasing this many cards in yard
		int LandEBT = 0; //tapped lands increase by this many when this card is played
		int Lava = 0; //creature has X:+1/+0
		int Mammoth = 0; //creature that gets +X/+X if played land this turn
		int ManLand = 0; //land that becomes creature until eot for this cost
		int MaxAttack = 0; //maximum attackers this turn
		int MaxBlock = 0; //num blockers required to kill enemy attacker
		int Mill = 0; //how many enemy cards moved from deck to yard when used
		int MinBlock = 1; //min num enemy blockers to block this creature
		int Mine = 0; //num lands in play required to trigger token
		int Morph = 0; //creature that can turn into a land for this cost
		int MostBlocks = 0; //highest # of creatures this player has blocked with on any turn this game
		int Pain = 0; //life loss from using abilities
		int PainEBT = 0; //land that enters play tapped unless this much life paid
		int Piranha = 0; //land that deals this much damage when enters play
		int Pitch = 0; //num cards in hand required to put this card in play
		int Power = 1; //creature current power
		int PStart = 1; //creature default power
		int Rage = 0; //creature that gets +X/+X counters when attacks
		int Regen = 0; //cost to regenerate this creature
		int RogueThresh = 0; //creature gets +power if at least this many cards in enemy yard
		int RogueBonus = 0; //size of power bonus
		int SacDam = 0; //land that sacs to deal damage
		int SacGen = 0; //num lands sacrificed to create token
		int SacMill = 0; //how many enemy cards moved from deck to yard when sacked
		int Shadow = 0; //creature that returns to play if at least this many cards in yard
		int Spike = 0; //card that deals this much damage to enemy from hand
		int Spirit = 0; //creature that returns to play if exactly this many cards in yard
		int StartHand = 1; //starting hand size
		int Stones = 0; //land that becomes creature permanently for this cost
		int Tangle = 0; //can only play 1 creature per game, on T1, if start hand is at least this many
		int TapDam = 0; //land that taps to deal damage
		int TapGen = 0; //num untapped lands needed to create token
		bool Team = false; //creature's p/t = # creatures controlled
		int Threshold = 0; //how many cards in yard required to use ability
		int Token = 0; //tokens created per activation
		int Tough = 1; //creature current toughness
		int TStart = 1; //creature default toughness
		int Tyrant = 0; //how many enemy grave cards are exiled when this attacks
		bool Lost = false; //flag if this player lost the previous game
		bool AttackReset = false; //this player lost the most recent game and is attacking less the next game
		bool WinFlag = false; //flag if this player has won the current game
		bool DeckFlag = false; //flag if this player has lost any game this match by decking
		bool Chancellor = false; //can only play cards 1st upkeep
		bool ChangeMind = false; //losing player is changing a non-attack/block decision this game DELETE?
		bool Chump = false; //this creature loses resources to combat 1v1
		bool Multi = false; //this creature must be multiblocked to be killed
		bool VarPT = false; //this creature can change power/tough
		bool DStrike = false; //creature has double strike
		bool Dtouch = false; //kills enemy creatures if deals any damage
		bool Flash = false; //card that can be played at start of game
		bool Flying = false; //creature has flying while attacking
		bool Frost = false; //enemy creatures damaged by this creature don't untap the next turn
		bool FStrike = false; //creature has first strike
		bool GraveCard = false; //this card uses graveyard as a resource in any way
		bool Haste = false; //creature that can attack same turn is played
		bool Hazard = false; //enemy creatures killed by this are exiled
		bool Hex = false; //creature that cannot be targeted
		bool Indestruct = false; //this creature is indestructible
		bool Infect = false; //creature gives poison counters and -1/-1 counters instead of damage -ONLY POISON WORKS
		bool IsCreat = true; //this card deals damage via creatures
		bool IsLand = false; //this card is a land
		bool Link = false; //creature has lifelink
		bool Madness = false; //creature that enters play when discarded
		bool Reach = false; //creature that can block enemy flyers
		bool SacAll = false; //sacrifice all your lands to activate this ability
		bool SacEOT = false; //creature that is sacrificed at end step
		bool Slug = false; //creature that once played, loses the game the next turn
		bool Switch = false; //creature that can switch p/t
		bool Trample = false; //creature has trample
		bool Unblock = false; //creature is unblockable
		bool Vigil = false; //creature that does not tap to attack
		int AltVar[62]; //alternate trackable variable
		int Attack[62]; //# actual attackers this turn
		int Blockers[62]; //# blockers available this turn
		int Decision[62]; //# available non-combat decisions this turn
		int Choice[62]; //# alt decisions to make this turn
		int Option = 0; //how many decision points encountered this turn
		int Score = 0; //how many games this deck has won
		int Deck[62]; //# cards in library	
		int Field[62]; //# creatures in play
		int Fight[62][160]; //blocking pattern
		int Frozen[62]; //# frozen cards this player controls
		int Poison[62]; //# poison counters this player has
		int PCounters[62][12]; //+1/+1 counter distribution
		int Grave[62]; //# cards in graveyard
		int Hand[62]; //# cards in hand
		int Lands[62]; //# land in play
		int Life[62]; //life total
		int LowLife = 20; //lowest life total this deck has been reduced to on any game
		int MaxBurn[62]; //total burn damage that can be dealt this turn
		int SkipAttack[62]; //# available attackers not attacking
		int TapLands[62]; //# tapped lands in play
		int TapCrtr[62]; //# tapped creatures in play
		//METHODS
		int Burning(); //activate direct damage abilities
		int Debug(); //display current gamestate
		void DeckChoice(); //menu for deck selection
		void FlagOff(); //reset win flags
		void Next(); //pass gamestate variables after every turn
		void Summary(Player enemy); //end of game report
		void Parameters(Player opponent); //adjust abilities relative to enemy deck
		void Setup(); //initialize gamestate
		Player Chance(Player enemy); //trigger Chancellors
		Player AttackSkip(Player opponent); //Losing player looks for most recent attack and blocks instead
		Player Win(Player enemy); //losing player searches for alt blocks/attacks/choices
		Player Reset(Player opponent); //reset the game to a previous turn
		Player BlockShuffle(); //losing player incrementally rearranges existing blockers
		void FullCopy(Player opponent); //copy all decision variables on to next turn during stalemate
} P1, P2, active, enemy, killer, target;

string Menu(); //deck select menu
void StaleMate(); //fast forward thru locked game states
int Turn(); //main turn cycle
void Cast(); //play cards
int FlipCard(); //activate flip cards
int LandFall(); //play lands
int Declare(); //set attackers and blockers
int Combat(); //Resolve combat
void End(); //end step
int BlockSave(); //defender adjusts blockers to avoid immediate death

int KillCreature(); //remove dead creature

int Player::Debug(){
	cout << this->Name << "\n";
	cout << "Game " << Game << " Turn " << T << "\n";
	cout << "Active Player " << active.Name << "\n";
	cout << "Attacks " << this->Attack[T] << " Blocks " << this->Blockers[T] << "\n";
	cout << "Tangle " << this->Tangle << " start hand " << this->StartHand << "\n";
	cout << "Counters 1: " << this->PCounters[T][1] << " Counters 2: " << this->PCounters[T][2] << "\n";
	cout << "Decisions " << this->Decision[T] << " choice " << this->Choice[T] << " option " << this->Option << "\n";
	cout << "Haste " << this->Haste << " maxblock " << this->MaxBlock << "\n";
	cout << "P " << this->Power << " T " << this->Tough << " VarPT " << this->VarPT << " Multi " << this->Multi << "\n";
	return 0;
}

//NEW GAME
	//Display tournament menu
string Menu(){
	int rows = 20;
	int columns = 4;
	int spacing[4] = {};
	for (int i = 1; i < columns; i++){
		for (subcount = 0; subcount < rows; subcount++){
			if (Tournament[subcount + ((i - 1) * rows)].size() > spacing[i]){
				spacing[i] = Tournament[subcount + (i - 1) * rows].size();
			}
		}
	}
	for(int i = 1; i <= rows; i++){
		if (i < 10) {
			cout << " ";
		}
		subcount = 0;
		for (subcount = 0; subcount < columns; subcount++) {
			cout << i + subcount * rows << " " << Tournament[i-1 + subcount * rows];
			if (subcount < columns-1){
				for (Spaces = 1; Spaces <= 1 + spacing[subcount+1] - Tournament[i-1 + subcount * rows].size(); Spaces++) {
					cout << " ";
				}
			}
		}
		cout << "\n";
	}
	//choose deck
	int DeckSelect;
	cin >> DeckSelect;
	return Tournament[DeckSelect-1];
}

	//Choose your fighter
void Player::DeckChoice(){
	//assign stats and abilities
	if (Name == "Akoum Warrior"){
		StartHand = 7;
		PStart = 4;
		TStart = 5;
		Cost = 6;
		LandEBT = 1;
		Trample = true;
		cout << Name << "\n" << "Land Back Card - Land EBT" << "\n" << "Cost 6 - Creature 4/5 - Trample" << "\n";
	}
	if (Name == "Allosaurus Rider"){
		StartHand = 7;
		Pitch = 3;
		cout << Name << "\n" << "Pitch 2 - Creature 1/1" << "\n";
	}
	if (Name == "Barbarian Ring"){
		StartHand = 7;
		IsLand = true;
		IsCreat = false;
		SacDam = 2;
		Spike = 2;
		Burn = 2;
		Activate = 2;
		Threshold = 7;
		cout << Name << "\n" << "Land - T: 1 + 1 pain" << "\n" << "Threshold 7 -> 1, T, sac: 2dam any target" << "\n";
	}
	if (Name == "Basking Rootwalla"){
		StartHand = 7;
		Madness = true;
		cout << Name << "\n" << "Creature 1/1 - Madness 0" << "\n";
	}
	if (Name == "Blackbloom Rogue"){
		StartHand = 7;
		PStart = 2;
		TStart = 3;
		Cost = 3;
		LandEBT = 1;
		MinBlock = 2;
		RogueThresh = 8;
		RogueBonus = 3;
		cout << Name << "\n" << "Land Back Card - Land EBT - T: 1" << "\n" << "Cost 3 - Creature 2/3" << "\n" << "Menace. +3/+0 if enemy has 8+ cards in yard" << "\n";
	}
	if (Name == "Blazing Rootwalla") {
		StartHand = 7;
		Madness = true;
		cout << Name << "\n" << "Creature 1/1 - Madness 0" << "\n";
	}
	if (Name == "Blinkmoth Nexus"){
		IsLand = true;
		ManLand = 2;
		Flying = true;
		Reach = true;
		Factory = 2;
		cout << Name << "\n" << "Land - T: 1" << "\n" << "1: becomes 1/1 flying creature til EOT" << "\n" << "1: +1/+1 till EOT" << "\n";
	}
	if (Name == "Castle Ardenvale"){
		IsLand = true;
		LandEBT = 1;
		Token = 1;
		TapGen = 5;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "4, T: create 1/1 token" << "\n";
	}
	if (Name == "Cave of the Frost Dragon") {
		IsLand = true;
		LandEBT = 1;
		ManLand = 6;
		Flying = true;
		Reach = true;
		PStart = 3;
		TStart = 4;
		cout << Name << endl << "Land - EBT. T: 1" << endl << "5: becomes 3/4 flying creature til EOT" << endl;
	}
	if (Name == "Chancellor of the Dross"){
		StartHand = 7;
		Chancellor = true;
		IsCreat = false;
		Spike = 3;
		Pain = -3;
		cout << Name << "\n" << "At the beginning of the game, deal 3 damage to enemy and you gain 3 life for each card in your starting hand" << "\n";
	}
	if (Name == "Chancellor of the Forge"){
		StartHand = 7;
		Chancellor = true;
		Token = 1;
		cout << Name << "\n" << "At the beginning of the game, create a 1/1 haste token for each card in your starting hand" << "\n";
	}
	if (Name == "Chancellor of the Spires"){
		StartHand = 7;
		Chancellor = true;
		IsCreat = false;
		Mill = 7;
		cout << Name << "\n" << "At the beginning of the game, mill enemy 7 for each card in your starting hand" << "\n";
	}
	if (Name == "Chancellor of the Tangle"){
		StartHand = 7;
		PStart = 6;
		TStart = 7;
		Vigil = true;
		Reach = true;
		Tangle = 7;
		cout << Name << "\n" << "On first turn cast one 6/7 vigilance reach creature if started with 7 cards" << "\n";
	}
	if (Name == "Celestial Colonnade"){
		IsLand = true;
		ManLand = 6;
		LandEBT = 1;
		PStart = 4;
		TStart = 4;
		Flying = true;
		Reach = true;
		Vigil = true;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "5: becomes 4/4 flying vigilance until eot" << "\n";
	}
	if (Name == "Cephalid Coliseum"){
		StartHand = 7;
		IsLand = true;
		IsCreat = false;
		Activate = 2;
		Pain = 1;
		SacMill = 3;
		Threshold = 7;
	}
	if (Name == "Cradle of the Accursed"){
		IsLand = true;
		SacGen = 1;
		Activate = 4;
		Token = 1;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Crawling Barrens"){
		IsLand = true;
		ManLand = 5;
		PStart = 0;
		TStart = 0;
		Barrens = 2;
	}
	if (Name == "Creeping Tar Pit"){
		IsLand = true;
		ManLand = 4;
		LandEBT = 1;
		PStart = 3;
		TStart = 2;
		Unblock = true;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "3: becomes 3/2 unblockable until eot" << "\n";
	}
	if (Name == "Den of the Bugbear") {
		IsLand = true;
		LandEBT = 1;
		ManLand = 5;
		//AttackGen = 1;
		PStart = 3;
		TStart = 2;
		cout << Name << endl << "Land - EBT. T: 1" << endl << "4: becomes 3/2 creature til EOT. When attacks, creates 1/1 attacking token." << endl;
	}
	if (Name == "Dread Statuary"){
		IsLand = true;
		ManLand = 5;
		PStart = 4;
		TStart = 2;
		cout << Name << "\n" << "Land - T: 1" << "\n" << "4: becomes 4/2 until eot" << "\n";
	}
	if (Name == "Dryad Arbor"){
		IsLand = true;
		ManLand = 1;
		cout << Name << "\n" << "Land Creature" << "\n" << "1/1" << "\n";
	}
	if (Name == "Dwarven Mine"){
		IsLand = true;
		Token = 1;
		Mine = 3;
	}
	if (Name == "Elvish Spirit Guide"){
		StartHand = 7;
		Pitch = 4;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Emeria's Call"){
		StartHand = 7;
		Cost = 7;
		Token = 2;
		PStart = 4;
		TStart = 4;
		Flying = true;
		Reach = true;
		PainEBT = 3;
	}
	if (Name == "Faceless Haven"){
		IsLand = true;
		ManLand = 4;
		PStart = 4;
		TStart = 3;
		Vigil = true;
		cout << Name << "\n" << "Land - T: 1" << "\n" << "3: becomes 4/3 vigilance until eot" << "\n";
	}
	if (Name == "Faerie Conclave"){
		IsLand = true;
		ManLand = 3;
		LandEBT = 1;
		PStart = 2;
		Flying = true;
		Reach = true;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "2: becomes 2/1 flying until eot" << "\n";
	}
	if (Name == "Forbidding Watchtower"){
		IsLand = true;
		ManLand = 3;
		LandEBT = 1;
		TStart = 5;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "2: becomes 1/5 until eot" << "\n";
	}
	if (Name == "Foundry of the Consuls"){
		IsLand = true;
		SacGen = 1;
		Activate = 6;
		Token = 2;
		Flying = true;
		Reach = true;
	}
	if (Name == "Frostwalk Bastion"){
		IsLand = true;
		ManLand = 3;
		PStart = 2;
		TStart = 3;
		Frost = true;
		cout << Name << "\n" << "Land - T: 1" << "\n" << "2: becomes 2/3 frost until eot" << "\n";
	}
	if (Name == "Gargoyle Castle"){
		IsLand = true;
		SacGen = 1;
		Activate = 6;
		Token = 1;
		PStart = 3;
		TStart = 4;
		Flying = true;
		Reach = true;
	}
	if (Name == "Ghitu Encampment"){
		IsLand = true;
		ManLand = 3;
		LandEBT = 1;
		PStart = 2;
		FStrike = true;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "2: becomes 2/1 first strike until eot" << "\n";
	}
	if (Name == "Hall of the Storm Giants") {
		IsLand = true;
		LandEBT = 1;
		ManLand = 7;
		Hex = true;
		PStart = 7;
		TStart = 7;
		cout << Name << endl << "Land - EBT. T: 1" << endl << "6: becomes 7/7 creature w hexproof til EOT" << endl;
	}
	if (Name == "Hissing Quagmire"){
		IsLand = true;
		ManLand = 4;
		LandEBT = 1;
		PStart = 2;
		TStart = 2;
		Dtouch = true;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "3: becomes 2/2 death touch until eot" << "\n";
	}
	if (Name == "Hive of the Eye Tyrant") {
		IsLand = true;
		LandEBT = 1;
		ManLand = 5;
		MinBlock = 2;
		Tyrant = 1;
		PStart = 3;
		TStart = 3;
		cout << Name << endl << "Land - EBT. T: 1" << endl << "4: becomes 3/3 creature w menace and yardhate til EOT" << endl;
	}
	if (Name == "Hostile Desert"){
		StartHand = 7;
		IsLand = true;
		ManLand = 3;
		PStart = 3;
		TStart = 4;
		Hostile = 1;
		Threshold = 1;
	}
	if (Name == "Ichorid"){
		StartHand = 7;
		PStart = 3;
		Haste = true;
		Ichorid = 2;
		SacEOT = true;
	}
	if (Name == "Inkmoth Nexus"){
		IsLand = true;
		ManLand = 2;
		Flying = true;
		Reach = true;
		Infect = true;
		cout << Name << "\n" << "Land - T: 1" << "\n" << "1: becomes 1/1 flying infect until eot" << "\n";
	}
	if (Name == "Ipnu Rivulet"){
		IsLand = true;
		IsCreat = false;
		SacMill = 4;
		Pain = 1;
		Activate = 3;
	}
	if (Name == "Kazandu Mammoth"){
		StartHand = 7;
		Cost = 3;
		PStart = 3;
		TStart = 3;
		LandEBT = 1;
		Mammoth = 2;
	}
	if (Name == "Keldon Megaliths"){
		IsLand = true;
		IsCreat = false;
		LandEBT = 1;
		Spike = 1;
		TapDam = 3;
		Burn = 1;
	}
	if (Name == "Lair of the Hydra") {
		IsLand = true;
		LandEBT = 1;
		ManLand = 3;
		//Hydra = 1;
		cout << Name << endl << "Land - EBT. T: 1" << endl << "X1: becomes X/X creature til EOT" << endl;
	}
	if (Name == "Lavaclaw Reaches"){
		IsLand = true;
		ManLand = 4;
		LandEBT = 1;
		PStart = 2;
		TStart = 2;
		Lava = 1;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "3: becomes 2/2 with 1:+1/+0 until eot" << "\n";
	}
	if (Name == "Lumbering Falls"){
		IsLand = true;
		ManLand = 5;
		LandEBT = 1;
		PStart = 3;
		TStart = 3;
		Hex = true;
		cout << Name << "\n" << "Land EBT - T: 1" << "\n" << "4: becomes 3/3 hexproof until eot" << "\n";
	}
	if (Name == "Memnite"){
		StartHand = 7;
		Pitch = 1;
	}
	if (Name == "Memorial to Glory"){
		IsLand = true;
		LandEBT = 1;
		SacGen = 1;
		Activate = 5;
		Token = 2;
	}
	if (Name == "Mishra's Factory"){
		IsLand = true;
		ManLand = 2;
		PStart = 2;
		TStart = 2;
		Factory = 1;
	}
	if (Name == "Mobilized District"){
		IsLand = true;
		ManLand = 5;
		PStart = 3;
		TStart = 3;
		Vigil = true;
	}
	if (Name == "Mutavault"){
		IsLand = true;
		ManLand = 2;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Needle Spires"){
		IsLand = true;
		ManLand = 5;
		LandEBT = 1;
		PStart = 2;
		DStrike = true;
	}
	if (Name == "Nether Shadow"){
		StartHand = 7;
		Haste = true;
		Shadow = 3;
	}
	if (Name == "Nether Spirit"){
		StartHand = 7;
		PStart = 2;
		TStart = 2;
		Spirit = 1;
	}
	if (Name == "Piranha Marsh"){
		IsLand = true;
		IsCreat = false;
		Piranha = 1;
		Haste = true;
	}
	if (Name == "Raging Ravine"){
		IsLand = true;
		ManLand = 5;
		LandEBT = 1;
		PStart = 3;
		TStart = 3;
		Rage = 1;
	}
	if (Name == "Rath's Edge"){
		IsLand = true;
		IsCreat = false;
		SacDam = 5;
		Spike = 1;
		Burn = 1;
	}
	if (Name == "Rocket-Powered Turbo Slug"){
		StartHand = 7;
		Haste = true;
		PStart = 3;
		Slug = 1;
	}
	if (Name == "Shambling Vent"){
		IsLand = true;
		ManLand = 4;
		LandEBT = 1;
		PStart = 2;
		TStart = 3;
		Link = true;
	}
	if (Name == "Simian Spirit Guide"){
		StartHand = 7;
		Pitch = 4;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Skyclave Cleric"){
		StartHand = 7;
		Cost = 2;
		TStart = 3;
		Pain = -2;
		LandEBT = 1;
	}
	if (Name == "Soul Spike"){
		StartHand = 7;
		IsCreat = false;
		Flash = true;
		Pitch = 3;
		Spike = 4;
		Pain = -4;
		Burn = 4;
	}
	if (Name == "Spawning Bed"){
		IsLand = true;
		SacGen = 1;
		Activate = 7;
		Token = 3;
	}
	if (Name == "Spawning Pool"){
		IsLand = true;
		ManLand = 3;
		LandEBT = 1;
		Regen = 1;
	}
	if (Name == "Spikefield Hazard"){
		StartHand = 7;
		IsCreat = false;
		Cost = 1;
		Spike = 1;
		Burn = 1;
		Hazard = true;
		LandEBT = 1;
	}
	if (Name == "Stalking Stones"){
		IsLand = true;
		Stones = 6;
		PStart = 3;
		TStart = 3;
	}
	if (Name == "Stirring Wildwood"){
		IsLand = true;
		ManLand = 4;
		LandEBT = 1;
		PStart = 3;
		TStart = 4;
		Reach = true;
	}
	if (Name == "Sunscorched Desert"){
		IsLand = true;
		IsCreat = false;
		Piranha = 1;
		Haste = true;
	}
	if (Name == "Surgical Extraction"){
		IsCreat = false;
		Pain = 2;
		Extract = 1;
	}
	if (Name == "Tangled Florahedron"){
		StartHand = 7;
		Cost = 2;
		Flora = 1;
		LandEBT = 1;
	}
	if (Name == "Tomb of Urami"){
		IsLand = true;
		SacGen = 5;
		SacAll = true;
		Activate = 5;
		Token = 1;
		PStart = 5;
		TStart = 5;
		Flying = true;
		Reach = true;
		Pain = 4;
	}
	if (Name == "Treetop Village"){
		IsLand = true;
		ManLand = 3;
		LandEBT = 1;
		PStart = 3;
		TStart = 3;
		Trample = true;
	}
	if (Name == "Umara Wizard"){
		StartHand = 7;
		Cost = 5;
		PStart = 4;
		TStart = 3;
		Flying = true;
		LandEBT = 1;
	}
	if (Name == "Urza's Factory"){
		IsLand = true;
		TapGen = 8;
		Token = 1;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Urza's Saga"){
		IsLand = true;
		SacGen = 1;
		Activate = 3;
		Token = 1;
		Team = true;
		Haste = true;
		CardEBT = 1;
	}
	if (Name == "Vine Dryad"){
		StartHand = 7;
		Pitch = 2;
		Flash = true;
		TStart = 3;
	}
	if (Name == "Wandering Fumarole"){
		IsLand = true;
		ManLand = 5;
		LandEBT = 1;
		TStart = 4;
		Switch = true;
	}
	if (Name == "Westvale Abbey"){
		IsLand = true;
		TapGen = 6;
		Activate = 6;
		Token = 1;
		Pain = 1;
		Flip = 5;
	}
	if (Name == "Zoetic Cavern"){
		StartHand = 7;
		Cost = 3;
		PStart = 2;
		TStart = 2;
		Morph = 2;
	}
	if (Name == "Zof Consumption"){
		StartHand = 7;
		IsCreat = false;
		Cost = 6;
		Spike = 4;
		Pain = -4;
		LandEBT = 1;
	}
	Power = PStart;
	Tough = TStart;
	if (this->Name == P2.Name && this->StartHand == 1){ //decks that don't need more than 1 card in hand should mull to 0 on the draw.
		this->StartHand = 0;
	}
	if (this->SacMill > 0 || this->Spike > 0 || this->ManLand > 1){ //use mill and burn cards in 1st main
		this->Haste = true; 	//give haste to all manlands except Dryad Arbor
	}
	if (this->Threshold > 0 || this->Shadow || this->Ichorid > 0){ //determine if this card uses grave in any way this->Spirit > 0 || 
		this->GraveCard = true;
	}
	if (this->Haste == false){
//		cout << "lets not be hasty" << "\n";
	} else {
//		cout << "hasty pants" << "\n";
	}
	if (this->Factory > 0 || this->Lava > 0 || this->Rage > 0 || this->Barrens > 0 || this->Switch == true || this->Mammoth > 0 || this->Team == true){
		this->VarPT = true; //flag if deck's p/t can change for any reason
	}
}

	//Initialize new game
void Player::Setup(){
	this->MaxBurn[0] = 0;
	this->Hand[1] = this->StartHand;
	this->Deck[0] = 60 - this->StartHand;
	this->Deck[1] = 60 - this->StartHand;
	this->Life[0] = 20;
	this->Life[1] = 20;
	this->Grave[0] = 0;
	this->Grave[1] = 0;
	if (this->Flash == true && (this->Name == P2.Name || this->Spike > 0)){
		active = P2;
		Cast();
		P2 = active;
	}
}

	//adjust abilities relative to enemy deck CHANGE ENEMY
void Player::Parameters(Player opponent){
	if (this->IsCreat == true && opponent.IsCreat == true){
		//convert flying to unblockable
		if ((this->Flying == true && opponent.Reach == false) || opponent.SacEOT == true){
			this->Unblock = true;
			if (this->IsCreat == true && Game == 1){
				cout << "\n" << this->Name << " is unblockable." << "\n";
			}
		}
		//remove irrel trample
		if (this->Power <= opponent.Tough){
			this->Trample = false;
		}
		//determine if blocking 1 on 1 causes resource loss
		if (opponent.Power >= this->Tough || opponent.Dtouch == true || this->Hostile > 0 || (opponent.DStrike == true && opponent.Power * 2 >= this->Tough)){
			this->Chump = true;
		}
		//strikers chump off
		if ((this->FStrike == true || this->DStrike == true) && opponent.Regen == 0 && this->Power >= opponent.Tough){
			this->Chump = false;
		}
		//always chump vs variable p/t creatures
		if (opponent.VarPT == true){
			if (Game == 1){
				cout << "varble pt" << "\n";
			}
			this->Chump = true;
		}
		//special abilities that turn off chump ?= this->SacEOT == true ||
		if (this->Shadow > 0 || (this->Regen == 1 && opponent.DStrike == false)){
			this->Chump = false;
		}
		if (this->Chump == true){
			if (Game == 1){
				cout << "\n" << this->Name << " dies when blocking" << "\n" << "\n";
			}
		} else { //multiblock flag
			this->Multi = true;
			if (Game == 1){
				cout << "\n" << this->Name << " must be blocked by multiple enemies to be killed" << "\n" << "\n";
			}
			if (this->Regen > 0){
				this->Multi = false;
			}
		}
		if (this->MinBlock > 1){
			this->Multi = true;
		}
		//determine max block APPLY
		if (this->Multi == true){
			this->MaxBlock = 1;
			int j = opponent.Power;
			if (j == 0){
				j = this->Tough;
			}
			while (this->Tough - j > 0){
				j += opponent.Power;
				this->MaxBlock++;
			}
			if(MaxBlock < MinBlock){
				MaxBlock = MinBlock;
			}
		}

		if ((this->FStrike == true || this->DStrike == true) && opponent.Regen == 0 && this->Power >= opponent.Tough && opponent.Tough > 0){
			this->MaxBlock = (this->Power / opponent.Tough) + 1;
		} else {
			if (this->Trample == true && this->MaxBlock * opponent.Tough < this->Power){
				this->MaxBlock = 0;
				if (opponent.Tough > 0){
					while (this->MaxBlock * opponent.Tough < this->Power){
						this->MaxBlock++;
					}
				}
			}
		}
		if (this->VarPT == true){
			this->MaxBlock = 99;
		}
		if (Game == 1){
			cout << this->Name << " dies if blocked by " << this->MaxBlock << "\n";
		}
	}
}

//RESET GAME
	//someone has WON the current Game -> Loser search for alt plays
Player Player::Win(Player enemy){
	this->Score++;
	int Marker = 10000; //call out every 10,000 games for long fast forwards
	if (remainder(Game, Marker) == 0){
		cout << Game << "\n";
	}
	Game++;
	TC = T;
	//if burn deck loses to creatures, burn switches to target creatures
	if (this->IsCreat == true && this->Hex == false && enemy.Burn > 0 && BurnLost == false){
		enemy.MaxBurn[T] = 0;
		BurnLost = true;
		for (int count = 0; count <= T; count++){
			this->Choice[count] = 0;
		}
		T = 0;
		cout << "Game " << Game << "\n";
		cout << enemy.Name << " will start the game over and target creatures.\n";
		return enemy;
	}
	this->MostBlocks = 0;
	for (BlockCheck = 1; BlockCheck <= TC; BlockCheck++){ //determine if winner deployed any blockers this game
		if (this->Fight[BlockCheck][1] > 0 && enemy.Attack[BlockCheck] > 0){
			this->MostBlocks++;
		}
	}
	//if winner is unblockable determine if game is over
	if (this->Unblock == true && (this->MostBlocks == 0 || enemy.Unblock == true || (this->Chump == true && enemy.Chump == false))){
		TC = 0;
	}
	//if nether spirit loses a stalemate, look for alt plays on the last turn it had recurrable grave
	if (enemy.Spirit > 0 && (enemy.Deck[T] <= 1 || (enemy.Chump == false && enemy.DeckFlag == true))){
		while (enemy.Grave[TC] > 1){
			TC--;
		}
		TC++;
	}
	//creature vs creature decks or creature loses to burn
	while (TC > 0){ //check each turn from most recent to oldest
		//P1 priority checks: Decision - Attacks - Block Shuffle - Block Unskip
		//P2 priority checks: Block Shuffle - Block Unskip - Decision - Attacks
		if (enemy.Decision[TC] > 1){
			cout << "multi decision";
		//	SkipGame = Game;
		}
		if (this->Name == P1.Name || (this->Burn > 0 && BurnLost == true)){ //if P2 loses or winner is burn deck, check decision changes, then attack skips, then blocks
			if (enemy.Choice[TC] < enemy.Decision[TC]){ //non-combat decision toggle
				T = TC - 1;
//				if (Game >= SkipGame){
					cout << enemy.Name << " will replay turn " << TC << " and change a decision. " << enemy.Choice[TC] << "\n";
					cout << "BEGIN GAME " << Game << "\n";
//				}
				enemy = this->Reset(enemy);
				this->Choice[TC] = 0;
				enemy.Choice[TC]++;
				if (enemy.Decision[TC] > 1){
//					SkipGame = Game;
				}
				enemy.ChangeMind = true; //used?
				return enemy;
			}
			//SKIP ATTACK
			enemy = this->AttackSkip(enemy);
			if (enemy.AttackReset == true){
				this->Choice[TC] = 0;
				enemy.Choice[TC] = 0;
				return enemy;
			}
		}
		//BLOCKER SHUFFLE
		ActualSkips = enemy.Fight[TC][this->Attack[TC] + 1]; //current number of available blockers assigned to skip their next block opportunity
		//Block Pattern Analysis and Change for Multi-Blocking options
		for (Attacker = this->Attack[TC] - 1; Attacker > 0; Attacker--){ //starting w next to last attacker,
			for (int Shuffle = Attacker + 1; Shuffle < this->Attack[TC] + 1; Shuffle++){ //check the # of blockers for each attacker following it,
				if (enemy.Fight[TC][Attacker] > enemy.Fight[TC][Shuffle] + 1){ //if any attacker has 2+ more blockers than a subsequent attacker,
					if(this->Trample == true || this->VarPT == true || enemy.VarPT == true){ //shuffle blockers once
						enemy = BlockShuffle();
					} else {
						while (enemy.Fight[TC][Attacker] > 1){
							enemy = BlockShuffle(); //shuffle blockers as needed
						}
					}
					enemy = this->Reset(enemy); //reset gamestate to turn TC
					if (Game >= SkipGame){
						cout << "\n" << enemy.Name << " will replay turn " << TC << " and shuffle blockers.\n";
						cout << "\nBEGIN GAME " << Game << "\n";
					}
					this->Choice[TC] = 0;
					enemy.Choice[TC] = 0;
					return enemy;
				}
			}
		}
		BlockedAttackers = 0; //determine how many attackers were blocked
		for (Blocker = 1; Blocker <= this->Attack[TC]; Blocker++){
			if (enemy.Fight[TC][Blocker] > 0 && this->Trample == false){
				BlockedAttackers++;
			}
		}
		//SKIPBLOCK TOGGLE
		//if no more block options among current blockers, and any blockers skipping, then involve another blocker
		if (ActualSkips > 0 && enemy.Chump == true && this->Attack[TC] > 0 && ((this->Attack[TC] - enemy.Blockers[TC]) * this->Power < enemy.Life[TC-1] || enemy.Link == true)){ 
			if ((enemy.Blockers[TC] - ActualSkips < this->Attack[TC] * this->MaxBlock && enemy.Blockers[TC] >= this->MaxBlock) || this->VarPT == true || BlockedAttackers < this->Attack[TC]){ //proceed only if not already at max relevant blockers
				ActualSkips--;
				for (Attacker = 1; Attacker <= this->Attack[TC]; Attacker++){ //clear block pattern
					enemy.Fight[TC][Attacker] = 0;
				}
				//if attacker survives 1v1 combat default put all loser's blockers on one attacker
				if (this->Multi == true || this->VarPT == true){ //varpt test cause probs?
					enemy.Fight[TC][1] = enemy.Blockers[TC] - ActualSkips;
					//if this is insufficient to kill at least one attacker, and there are enough available blockers to do so, deploy them if will not cost additional losses
					if (enemy.Fight[TC][1] > 1 && enemy.Fight[TC][1] < this->MaxBlock && enemy.Blockers[TC] >= this->MaxBlock && this->Power < enemy.Tough * 2){
						ActualSkips = enemy.Blockers[TC] - this->MaxBlock;
						enemy.Fight[TC][1] = this->MaxBlock;
					}
					for (Attacker = 1; Attacker <= this->Attack[TC]; Attacker++){ //stagger according to max blocks
						if (enemy.Fight[TC][Attacker] > this->MaxBlock){ //if more blockers than needed then move excess to next attacker
							enemy.Fight[TC][Attacker + 1] = enemy.Fight[TC][Attacker] - this->MaxBlock;
							enemy.Fight[TC][Attacker] = this->MaxBlock;
						}
						if (enemy.Fight[TC][Attacker] > 1 && enemy.Fight[TC][Attacker] < this->MaxBlock && this->Trample == false && this->VarPT == false){ //if fewer blockers than needed then chump and move rest to next attacker
							enemy.Fight[TC][Attacker + 1] = enemy.Fight[TC][Attacker] - 1;
							enemy.Fight[TC][Attacker] = 1;
						}
					}
					//check if defender will die with this block pattern, spread blockers one attacker further if able
					w = 1;
					BlockSave();
				} else { //if attacker dies 1v1, default spread blockers 1v1
					while ((this->Attack[TC] - (enemy.Blockers[TC] - ActualSkips)) * this->Power >= enemy.Life[TC-1] && ActualSkips > 0){
						ActualSkips--; //if loser will still die with this block pattern, then keep deploying skipped blocks
					}
					for (Attacker = 1; Attacker <= this->Attack[TC]; Attacker++){ //put one blocker against each attacker if able
						if (enemy.Blockers[TC] - ActualSkips >= Attacker){
							enemy.Fight[TC][Attacker] = 1;
						}
					}
				}
				enemy.Fight[TC][this->Attack[TC]+1] = ActualSkips;
				enemy = this->Reset(enemy);
				if (Game >= SkipGame){
					cout << "\n" << enemy.Name << " will replay turn " << TC << " and a skipped block now blocks.\n";
					cout << "\nBEGIN GAME " << Game << "\n";
				}
				this->Choice[TC] = 0;
				enemy.Choice[TC] = 0;
				return enemy;
			}
		}
		//if all blocking options already played
		enemy = this->AttackSkip(enemy); //switch the most recent attack to block, if enemy has at least one coresponding attack or block, or winner is burn
		if (enemy.AttackReset == true){
			//cout << "attack reset true" << "\n";
				this->Choice[TC] = 0;
				enemy.Choice[TC] = 0;
			return enemy;
		}
		//non-combat decision toggle
		if (enemy.Choice[TC] < enemy.Decision[TC]){
			enemy.Choice[TC]++;
			this->Choice[TC] = 0;
			enemy.ChangeMind = true;
			T = TC - 1;
		//	if (Game >= SkipGame){
				cout << enemy.Name << " will replay turn " << TC << " and change a decision.\n";
				cout << "BEGIN GAME " << Game << "\n";
		//	}
		//	SkipGame = Game;
			return enemy;
		}
		enemy.SkipAttack[TC] = 0;
		this->SkipAttack[TC] = 0;
		this->Decision[TC] = 0;
		enemy.Decision[TC] = 0;
		this->Choice[TC] = 0;
		enemy.Choice[TC] = 0;
		TC--;
	}
	//if reach this point, current loser has exhausted all combat options
	//mulligan if have lost any game by decking since last mulligan
	if (enemy.DeckFlag == true && enemy.StartHand > 0){
		enemy.DeckFlag = false;
		this->MaxBurn[T] = 0;
		enemy.MaxBurn[T] = 0;
		enemy.StartHand--;
		cout << "\nGame " << Game - 1;
		cout << "\n" << enemy.Name << " starts the game over and mulligans to " << enemy.StartHand << "\n\n";
			SkipGame = Game;
		T = 0;
		return enemy;
	}
	if (this->Name == P1.Name){
		cout << "Player 1 ";
	} else {
		cout << "Player 2 ";
	}
	cout << this->Name << " strictly wins in " << Game-1 << " games.\n";
	if (enemy.Score == 0){
		cout << "Ace!\n";
		cout << "Lowest winner life " << this->LowLife << "\n";
		
	} else {
		cout << enemy.Name << " wins " << enemy.Score << "\n";
	}
	cout << "Longest game was " << LongGame << " turns.\n\n";
	GameOver = 1;
	return enemy;
}

		//incrementally shuffle through multi-blocking options
Player Player::BlockShuffle(){
	enemy.Fight[TC][Attacker]--;
	Deployed = 0;
	for(ct3 = 0; ct3 < Attacker; ct3++){
		Deployed += enemy.Fight[TC][ct3];
	}
	enemy.Fight[TC][Attacker+1] = enemy.Blockers[TC] - (Deployed + enemy.Fight[TC][Attacker] + ActualSkips);
	for (ct3 = Attacker + 2; ct3 < active.Attack[TC] + 1; ct3++){
		enemy.Fight[TC][ct3] = 0;
	}
	for (ct3 = Attacker; ct3 < active.Attack[TC] - 1; ct3++){
		if (enemy.Fight[TC][ct3+1] > enemy.Fight[TC][ct3]){
			enemy.Fight[TC][ct3+2] = enemy.Fight[TC][ct3+1] - enemy.Fight[TC][ct3];
			enemy.Fight[TC][ct3+1] = enemy.Fight[TC][ct3];
		}
	}
	return enemy;
}

		//adjust blockers to avoid immediate death
int BlockSave(){
	BlockedAttackers = 0; //recalculate how many attackers are blocked
	for (Blocker = 1; Blocker <= active.Attack[TC]; Blocker++){
		if (enemy.Fight[TC][Blocker] > 0 && active.Trample == false){
			BlockedAttackers++;
		}
	}
	//if defender will die with this block pattern, spread blockers if able
	while ((active.Attack[TC] - BlockedAttackers) * active.Power >= enemy.Life[TC-w] && enemy.Link == false && BlockedAttackers < enemy.Blockers[TC]){
		Attacker = active.Attack[TC];
		while(Attacker > 0){
			if (enemy.Fight[TC][Attacker] > 1){
				enemy.Fight[TC][Attacker]--;
				enemy.Fight[TC][Attacker+1]++;
				if (enemy.Fight[TC][Attacker+1] == 1){
					BlockedAttackers++;
//					SkipGame = Game;
				}
//				cout << "ur gonna die" << "\n";
				Attacker = 1;
			}
			Attacker--;
		}
	}	
	return 0;
}

		//winner blocks the same
Player Player::Reset(Player opponent){
	opponent.Lost = true;
	int j;
	if (this->Attack[TC] > opponent.Attack[TC]){
		j = this->Attack[TC];
	} else {
		j = opponent.Attack[TC];
	}
	//record block change on turn after reset
	for (int i = 1; i <= j + 1; i++){
		opponent.Fight[TC+1][i] = opponent.Fight[TC][i];
		this->Fight[TC+1][i] = this->Fight[TC][i];
		
	}
	if (Game >= SkipGame){
	//	cout << "both save turn " << TC << " block pattern onto turn " << TC + 1 << "\n";
	}
	T = TC - 1;	//reset the game on turn before alt play found
	return opponent;
}

		//Losing player looks for most recent attack and blocks instead
Player Player::AttackSkip(Player opponent){
	//if all blocking options this turn already played, switch the most recent attack to block, if enemy has at least one coresponding attack or block or is burn
	if (opponent.Attack[TC] > 0 && (this->Name == P2.Name || TC < T)){ //check the below
		if (this->Attack[TC] > 0 || (this->Attack[TC+1] > 0 && this->Name == P1.Name) || this->Fight[TC][1] > 0 || this->Fight[TC+1][1] > 0 || (this->Burn > 0 && BurnLost == true)){
			opponent.AttackReset = true;
			opponent.SkipAttack[TC]++;
			opponent.Choice[TC] = 0;
			T = TC - 1;
			if (Game >= SkipGame){
				cout << opponent.Name << " will replay turn " << TC << " and skip an attack." << "\n";
				cout << "\n" << "BEGIN GAME " << Game << "\n";
			}
		}
	}
	return opponent;
}

		//win flags off
void Player::FlagOff(){
	this->Lost = false;
	this->AttackReset = false;
	this->ChangeMind = false;
}

		//Override stalemates
void StaleMate(){ //auto fill repetitive game state onto remaining turns
	if (T > 5 && P1.IsCreat == true && P2.IsCreat == true){
		if (P1.Field[T] == P1.Field[T-1] && P1.Field[T-1] == P1.Field[T-2] && P2.Field[T] == P2.Field[T-1] && P2.Field[T-1] == P2.Field[T-2]){
			if (P1.Life[T] == P1.Life[T-1] && P1.Life[T-1] == P1.Life[T-2] && P2.Life[T] == P2.Life[T-1] && P2.Life[T-1] == P2.Life[T-2]){
				if (P1.Lands[T] == P1.Lands[T-1] && P1.Lands[T-1] == P1.Lands[T-2] && P2.Lands[T] == P2.Lands[T-1] && P2.Lands[T-1] == P2.Lands[T-2]){
					if (P1.Fight[T][1] == P1.Fight[T-1][1] && P1.Fight[T-1][1] == P1.Fight[T-2][1]){
						if (P2.Fight[T][1] == P2.Fight[T-1][1] && P2.Fight[T-1][1] == P2.Fight[T-2][1]){
							if (P1.Hand[T] == P1.Hand[T-1] && P1.Hand[T-1] == P1.Hand[T-2] && P2.Hand[T] == P2.Hand[T-1] && P2.Hand[T-1] == P2.Hand[T-2]){
								if (P1.Attack[T] == P1.Attack[T-1] && P1.Attack[T] == P1.Attack[T-2] && P2.Attack[T] == P2.Attack[T-1] && P2.Attack[T] == P2.Attack[T-2]){
									if (Override == false){
										cout << "stalemate detected. game " << Game << " turn " << T << "\n";
										Override = true;
										CheckPoint = T;
										int BigHand = P1.StartHand;
										if (P2.StartHand > BigHand){
											BigHand = P2.StartHand;
										}
										for (; T < 61 - BigHand; T++){
											P1.Next();
											P2.Next();
											P1.FullCopy(P2);
											P2.FullCopy(P1);
										}
										T--;
										P1.Deck[T+1]++;
										P2.Deck[T+1]++;
										P1.FlagOff();
										P2.FlagOff();
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

		//copy all decision variables on to next turn during stalemate
void Player::FullCopy(Player opponent){ //auto-fill remaining turns 
	this->Attack[T+1] = this->Attack[T];
	this->Decision[T+1] = this->Decision[T];
	this->Choice[T+1] = this->Choice[T];
	this->Deck[T+1] = this->Deck[T] - 1;
	this->Grave[T+1] = this->Grave[T] + 1; //CONFIRM
	if (this->Ichorid > 0 || this->Hostile > 0){
		this->Grave[T+1]--; //QUESTIONABLE
	}
	this->Blockers[T+1] = this->Blockers[T];
	for (Attacker = 1; Attacker <= opponent.Attack[T] + 1; Attacker++){
		this->Fight[T+1][Attacker] = this->Fight[T][Attacker];
	}
}

	//REPORT end of game
void Player::Summary(Player opponent){
	cout << this->Name;
	if (this->WinFlag == true){
		cout << " WINNER";
		if (opponent.Deck[T] < 1 && opponent.Life[T] > 0){
			cout << " by decking";
		}
	}
	if (this->Name == P1.Name){
		cout << "\n" << "TURN ";
		for (TC = 1; TC <= T; TC++){
			if (TC < 10){
				cout << " ";
			}
			cout << TC;
			if(TC < 40){
				cout << " ";	
			}
		}
	}
	if(Report != 2){
		if (opponent.Infect == false){
			cout << "\n" << "LIFE ";
			for (TC = 1; TC <= T; TC++){
				if (this->Life[TC] < 10){
					cout << " ";
				}
				cout << this->Life[TC];
				if(TC < 40){
					cout << " ";	
				}
			}
		} else {
			cout << "\n" << "POSN ";
			for (TC = 1; TC <= T; TC++){
				if (opponent.Poison[TC] < 10){
					cout << " ";
				}
				cout << opponent.Poison[TC];
				if(TC < 40){
					cout << " ";	
				}
			}
		}
		if (this->StartHand > 1){
			cout << "\n" << "HAND ";
			for (TC = 1; TC <= T-w; TC++){
				if (this->Hand[TC] < 10){
					cout << " ";
				}
				cout << this->Hand[TC];
				if(TC < 40){
					cout << " ";	
				}
			}
		}
		if (this->IsLand == true || this->Cost > 0){
			cout << "\n" << "LAND ";
			for (TC = 1; TC <= T; TC++){
				if (this->Lands[TC] < 10){
					cout << " ";
				}
				cout << this->Lands[TC];
				if(TC < 40){
					cout << " ";	
				}
			}
		}
		if (this->ManLand == 0 && this->IsCreat == true){
			cout << "\n" << "CRTR ";
			for (TC = 1; TC <= T; TC++){
				if (this->Field[TC] < 10){
					cout << " ";
				}
				cout << this->Field[TC];
				if(TC < 40){
					cout << " ";	
				}
			}		
		}
		if (opponent.Frost == true && this->Tough >= opponent.Power){
			cout << "\n" << "FRZN ";
			for (TC = 1; TC <= T; TC++){
				if (opponent.Frozen[TC] < 10){
					cout << " ";
				}
				cout << opponent.Frozen[TC];
				if(TC < 40){
					cout << " ";	
				}
			}		
		}		
	}
	if (this->IsCreat == true){
		cout << "\n" << "ATAK ";
		for (TC = 1; TC <= T-w; TC++){
			if (this->Attack[TC] < 10){
				cout << " ";
			}
			cout << this->Attack[TC];
			if(TC < 40){
				cout << " ";
			}
		}
		if (opponent.Unblock == false){
			for(Attacker = 1; Attacker <= opponent.BigAttack; Attacker++){
				cout << "\n" << "BLOK ";
				for (TC = 1; TC <= T; TC++){
					if (this->Fight[TC][Attacker] < 10){
						cout << " ";
					}
					if (opponent.Attack[TC] < Attacker){
						cout << " ";
					} else {
						if (P2.WinFlag == true || this->Name == P2.Name || TC < T){
							cout << this->Fight[TC][Attacker];
						}
					}
					if(TC < 40){
						cout << " ";	
					}
				}
			}
			cout << "\n" << "SKIP ";
			for (TC = 1; TC <= T; TC++){
				if (this->Fight[TC][opponent.Attack[TC] + 1] < 10){
					cout << " ";
				}
				if (this->Fight[TC][opponent.Attack[TC] + 1] == 0){
					cout << " ";
				} else {
					if (P2.WinFlag == true || this->Name == P2.Name || TC < T){
						cout << this->Fight[TC][opponent.Attack[TC] + 1];
					}
				}
				if(TC < 40){
					cout << " ";	
				}
			}
		}
	}
	int j = 0;
	for (TC = 1; TC <= T; TC++){
		j += this->Decision[TC];
	}
	if (j > 0){
		cout << "\n" << "PLAY ";
		for (TC = 1; TC <= T; TC++){
			cout << " " << this->Choice[TC];
			if(TC < 40){
				cout << " ";
			}
		}
		cout << "\n" << "OPTS ";
		for (TC = 1; TC <= T; TC++){
			cout << " " << this->Decision[TC];
			if(TC < 40){
				cout << " ";	
			}
		}		
	}
	cout << "\n" << "YARD ";
	for (TC = 1; TC <= T; TC++){
		if (this->Grave[TC] < 10){
			cout << " ";
		}
		cout << this->Grave[TC];
		if(TC < 40){
			cout << " ";	
		}
	}
	if (Report != 2){
		cout << "\n" << "DECK ";
		for (TC = 1; TC <= T; TC++){
			if (this->Deck[TC] < 10){
				cout << " ";
			}
			cout << this->Deck[TC];
			if(TC < 40){
				cout << " ";	
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

//SPECIAL ABILITIES
	//Regenerate or morph or remove a dead creature
int KillCreature(){
	//this-> = killer
	//target = dead creature
	target.Life[T] = 21;
	//if killer can morph
	if (killer.Morph > 0 && killer.Lands[T] - killer.TapLands[T] >= killer.Morph && killer.Lands[T] < killer.Cost * 2){
		killer.Option++;
		killer.Decision[T] = 1; //create enemy option to morph
		if (killer.Choice[T] == 1){ //enemy takes morph option
			killer.TapLands[T] += killer.Morph; //pay cost
			killer.Lands[T]++; //enemy gains land
			if (active.Name == killer.Name){ //if dead morpher attacked, new land is tapped
				killer.TapLands[T]++;
			}
			SkipGame = Game;
			cout << killer.Name << " morphs and doesn't kill your guy. Game " << Game << " Turn " << T << "\n";
			return 0;
		}
	}
	//regen exception here
	if (target.Regen > 0 && target.Lands[T] - target.TapLands[T] >= target.Regen){
		target.TapLands[T] += target.Regen;
		if (Report == 1 && Game >= SkipGame){
			cout << target.Name << " regenerates a creature." << "\n";
		}
		return 1;
	} else { //kill an attacker
		if (Report == 1 && Game >= SkipGame){
			cout << target.Name << " loses a creature." << "\n";
		}
		if (target.ManLand > 0){
			target.Lands[T]--; //remove land from play
			if (target.Vigil == false){
				target.TapLands[T]--; //adjust # tapped lands
			}
		} else {
			target.Field[T]--; //remove creature from play
			if (active.Name == target.Name && target.Vigil == false && killer.Burn == 0){
				target.TapCrtr[T]--; //the creature that died was tapped
			}
		}
		//deal with dying creature
		if (target.Morph > 0 && target.Lands[T] - target.TapLands[T] >= target.Morph && target.Lands[T] < target.Cost * 2){ //check for morph conditions
			target.Decision[T] = 1; //create option to morph
			target.Option++;
			if (target.Choice[T] == 1){ //taking morph option
				target.TapLands[T] += target.Morph; //pay cost
				target.Lands[T]++; //gain land
				if (active.Name == target.Name){ //if morpher attacked, new land is tapped
					target.TapLands[T]++;
				}
				SkipGame = Game;
				cout << target.Name << " morphs a creature into a land. Game " << Game << " Turn " << T << "\n";
				return 0;
			}
		}
		//no more outs creature is actually dead
		if (target.Token == 0 && killer.Hazard == false){ //tokens and spikefield targets exiled
			target.Grave[T]++; //card ends up in grave
		}
		if (target.Name == active.Name){ //remove +1/+1 counters from dead creature
			target.PCounters[T][Attacker] = 0;
		} else {
			target.PCounters[T][Blocker] = 0;
		}
		return 0;
	}
}

	//Direct damage
int Player::Burning(){
	BurnDam = 0;
	//sac damage lands
	if (this->SacDam > 0 && this->Lands[T] >= this->Activate){
		this->Life[T] -= this->Pain;
		BurnDam += this->Spike;
		this->Lands[T] -= 1;
		this->Grave[T] += 1;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " deals " << this->Spike << " damage." << "\n";
		}
	}
	//tap damage lands
	if (this->TapDam > 0 && this->Lands[T] - this->TapLands[T] >= this->TapDam){
		BurnDam += this->Spike;
		this->TapLands[T] += this->TapDam;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " deals " << this->Spike << " damage." << "\n";
		}
	}
	//spell damage
	if (this->Cost > 0 || this->Pitch > 0){
		if(this->Lands[T] - this->TapLands[T] >= this->Cost && this->Hand[T] >= this->Pitch){
			this->Life[T] -= this->Pain;
			BurnDam += this->Spike;
			this->TapLands[T] += this->Cost;
			if (this->Pitch > 0){
				this->Hand[T] -= this->Pitch;
			} else {
				this->Hand[T] -= 1;
			}
			if (Report == 1 && Game >= SkipGame){
				cout << this->Name << " deals " << this->Spike << " damage." << "\n";
			}
			this->Grave[T] += 1;
		}
	}
	this->MaxBurn[T] -= BurnDam;
	return BurnDam;
}

	//trigger Chancellors
Player Player::Chance(Player opponent){
	//Dross
	opponent.Life[1] -= this->Spike * this->Hand[1];
	this->Life[1] -= this->Pain * this->Hand[1];
	//Forge
	this->Field[1] = this->Token * this->Hand[1];
	//Spires
	opponent.Deck[0] -= this->Mill * this->Hand[1];
	opponent.Grave[0] += this->Mill * this->Hand[1];
	opponent.Deck[1] -= this->Mill * this->Hand[1];
	opponent.Grave[1] += this->Mill * this->Hand[1];
	return opponent;
}

	//flip Westvale Abbey
int FlipCard(){
	if (active.Flip > 0){
		if (active.Field[T] >= active.Flip && active.Lands[T] - active.TapLands[T] >= active.TapGen){
			cout << "TRANSFORM! Turn " << T << "\n";
			active.Field[T] = 1;
			active.Power = 9;
			active.Tough = 7;
			active.Flying = true;
			active.Reach = true;
			active.Link = true;
			active.TapLands[T] += active.TapGen;
			active.TapGen = 99;
			active.Flip = 99;
			FlipTurn = T;
			return 1;
		}
		if ((T <= FlipTurn && active.Field[T] != 1) || (T < FlipTurn && active.Field[T] == 1)){ //check if need to unflip a card
			FlipTurn = 0;
			cout << "unflipping " << T << " " << FlipTurn << " Game " << Game << "\n";
	//	SkipGame = Game;
			active.Power = 1;
			active.Tough = 1;
			active.Flying = false;
			active.Reach = false;
			active.Link = false;
			active.Haste = false;
			active.TapGen = 6;
			active.Flip = 5;
		}
	}
	return 0;
}

//-GAME PHASES-
	//TURN CYCLE
int Turn(){
	//display active player gamestate at start of turn
	if (Report == 1 && Game >= SkipGame){
		cout << "\n" << active.Name << " Start Turn " << T << "\n";
		cout << "Life " << active.Life[T] << " | Hand " << active.Hand[T] << " | Deck " << active.Deck[T] << "\n";
		cout << "Grave " << active.Grave[T] << " | Lands " << active.Lands[T] << " | Creatures " << active.Field[T] << "\n";
		if (enemy.Poison[T] > 0){
			cout << "Poison " << enemy.Poison[T] << "\n";
		}
		if (enemy.Frozen[T] > 0){
			cout << "Frozen " << enemy.Frozen[T] << "\n";
		}
	}
	//reset # of alt decision points encountered
	active.Option = 0;
	//shrink landfall
	if (active.Mammoth > 0){
		active.Power = active.PStart;
		active.Tough = active.TStart;
	}
	//untap except frozen cards
	if (enemy.Frozen[T] > 0){
		if (active.ManLand > 0){
			active.TapLands[T] = enemy.Frozen[T];
		} else {
			active.TapCrtr[T] = enemy.Frozen[T];
			active.TapLands[T] = 0;
		}
		enemy.Frozen[T] = 0;
	} else {
		active.TapLands[T] = 0;
		active.TapCrtr[T] = 0;
	}
	//draw step
	if (T > 1 || active.Name == P2.Name){
		active.Deck[T] -= 1;
		active.Hand[T] += 1;
		if (Report == 1 && Game >= SkipGame){
			cout << active.Name << " draws a card.\n";
		}
	}
	//1st main
	if (Report == 1 && Game >= SkipGame){
		cout << "1st main phase" << "\n";
	}
	if (active.ManLand == 1){
		active.MaxAttack = active.Lands[T];
	} else {
		active.MaxAttack = active.Field[T] - active.TapCrtr[T];
	}
	if (active.Hand[T] > 0){ //if any cards in hand
		//play lands
		if (active.IsLand == true || active.Cost > 0){
			LandFall();
		}
		//flip card test
		if (active.Flip > 0 && (active.Field[T] >= active.Flip || (active.Field[T] == active.Flip - 1 && active.Lands[T] >= active.TapGen * 2))){
			active.Haste = true;
		}
		//play cards that can contribute to win this turn
		if (active.Haste == true){
			Cast();
		}
	}
	//ATTACK
	Declare(); //establish attackers and blockers
	if (active.Attack[T] > 0){
		Combat(); //resolve combat
	} else {
		if (active.Frost == true){ //if frost creature doesn't attack, erase previous kill decisions
			active.Choice[T] = 0;
			active.Decision[T] = 0;
		}
	}
	//win check
	if (enemy.Deck[T] < 1 || enemy.Life[T] < 1 || active.Poison[T] >= 10){
		if (Report == 1 && Game >= SkipGame){
			cout << "\n" << active.Name << " wins Game " << Game << " on turn " << T << "\n";
		}
		active.WinFlag = true;
		if (enemy.Deck[T] < 1){
			enemy.DeckFlag = true;
			//cout << enemy.Name << " decks GAME " << Game << "\n";
		}
		return 1;
	}
	//2nd main - play cards that cannot contribute to win this turn
	if (Report == 1 && Game >= SkipGame){
		cout << "2nd main phase" << "\n";
	}
	if (active.Haste == false){
		Cast();
	}
	//end 
	if (Report == 1 && Game >= SkipGame){
		cout << "end step" << "\n";
	}
	End();
	return 0;
}

	//PLAY LAND - MAIN PHASE - Play Land
int LandFall(){
	//play lands
	if (active.IsLand == true && (active.Grave[T] >= active.Threshold || enemy.Extract > 0) && active.Hostile == 0){
		PlayLand = true;
	}
	//land backed cards
	if (active.Lands[T] < active.Cost || enemy.Extract > 0){
		PlayLand = true;
	}
	//Hostile Desert play land or not
	if (active.Hostile > 0 && (active.Lands[T] < active.ManLand || active.Grave[T] > active.Lands[T]/active.ManLand)){
		PlayLand = true;
	}
	if (active.Flora == 0){
		//cout << T << " turn  lands " << this->Lands[T] << " hand " << this->Hand[T] << "\n";
		if (active.Lands[T] < active.Cost * 2 && active.Hand[T] > 1){
			PlayLand = true;
		}
		//cout << this->Name << " Lands played " << PlayLand << "\n";
		//mammoth exception
		//cout << "mammoth turn " << T << " choice " << this->Choice[T] << " max attack " << this->MaxAttack << " skips " << this->SkipAttack[T] << "\n";
		if (PlayLand == false && active.Mammoth > 0 && active.MaxAttack - active.SkipAttack[T] > 0){
			active.Decision[T] = 1;
			active.Option++;
			if (active.Choice[T] == 0){
				if (Game >= SkipGame){
					cout << "CHOOSE - NO land - game " << Game << " turn " << T << "\n";
				}
			} else {
				PlayLand = true;
				if (Game >= SkipGame){
				//	cout << "CHOOSE - YES land - game " << Game << " turn " << T << "\n";
				}
			}
		} else {
			if (active.Mammoth > 0){
				active.Decision[T] = 0;
				active.Choice[T] = 0;
			}
		}
	} else { //Florahedron land drop decisions
		if (active.Lands[T] < active.Cost * 2 && active.Lands[T] >= active.Cost){
			active.Option++;
			active.Decision[T] = 1;
			if (active.Choice[T] > 0){
				PlayLand = true;
			}
		}
	}
	if (PlayLand == true){
		PlayLand = false;
		active.Lands[T] ++;
		active.Hand[T] --;
		if (active.PainEBT > 0){ //decide whether to play Emeria Shattered Skycave untapped
			if (active.Lands[T] == active.Cost && active.Life[T] > active.PainEBT){
				active.Life[T] -= active.PainEBT;
			} else {
				active.TapLands[T]++;
			}
		}
		active.TapLands[T] += active.LandEBT;
		active.Power += active.Mammoth;
		active.Tough += active.Mammoth;
		if (Report == 1 && Game >= SkipGame){
			cout << active.Name << " plays a land";
			if (active.LandEBT > 0){
				cout << " tapped." << "\n";
			} else {
				cout << "." << "\n";
			}
		}
		//Dwarven Mine
		if (active.Mine > 0 && active.Lands[T] > active.Mine){
			active.Field[T] += active.Token;
			if (Report == 1 && Game >= SkipGame){
				cout << active.Name << " makes a token." << "\n";
			}			
		}
	}
	return 0;
}

	//MAIN PHASE - Play Cards
void Cast(){
	//cast pitch creatures
	if (active.Pitch > 0 && active.IsCreat == true){
		while (active.Hand[T] >= active.Pitch){
			active.Field[T] += 1;
			active.Hand[T] -= active.Pitch;
			if (Report == 1 && Game >= SkipGame){
				cout << active.Name << " casts a creature." << "\n";
			}
		}
	}
		//Piranha Marsh/Sunscorched Desert
	if (active.Piranha > 0){
		enemy.Life[T] -= active.Piranha;
		if (Report == 1 && Game >= SkipGame){
			cout << active.Name << " deals " << active.Piranha << " damage." << "\n";
		}
	}
		//Stalking Stones
	if (active.Stones > 0 && active.Lands[T] >= active.Stones){
		active.Field[T]++;
		active.TapCrtr[T]++;
		active.Lands[T]--;
		if (Report == 1 && Game >= SkipGame){
			cout << active.Name << " makes a creature." << "\n";
		}
	}
		//sac land token generators
	if (active.SacGen > 0 && active.Lands[T] - active.TapLands[T] >= active.Activate && active.Life[T] > active.Pain && enemy.Extract == false){
			//option to decline pain token
		if (active.Field[T] == 0 || active.Choice[T] == 0){
			if (active.Field[T] > 0 && active.Pain > 0){
				active.Decision[T] = 1;
				//cout << "Binary " << T << " true" << "\n";
			} else {
				active.Decision[T] = 0;
				active.Choice[T] = 0;
			}
			active.Field[T] += active.Token; //make token
			active.TapCrtr[T] += active.CardEBT;
			if (active.SacAll == false){
				active.Lands[T] -= active.SacGen;
				active.Grave[T] += active.SacGen;
			} else {
				active.Grave[T] += active.Lands[T];
				active.Lands[T] = 0;
			}
			active.Life[T] -= active.Pain;
			if (Report == 1 && Game >= SkipGame){
				cout << active.Name << " makes " << active.Token << " token." << "\n";
			}
		} else {
			active.Decision[T] = 0;
			active.Choice[T] = 0;
		}
	}
	//flip cards
	if (FlipCard() == 1){
		active.Parameters(enemy);
	}
	//tap land token generators
	if (active.TapGen > 0){
		while (active.Lands[T] - active.TapLands[T] >= active.TapGen && active.Life[T] > active.Pain){
			active.Field[T] += active.Token;
			active.Life[T] -= active.Pain;
			active.TapLands[T] += active.TapGen;
			if (Report == 1 && Game >= SkipGame){
				cout << active.Name << " makes " << active.Token << " token." << "\n";
			}
			if (FlipCard() == 1){
				active.Parameters(enemy);
			}
		}
	}
	//sac mill lands
	if (active.SacMill > 0){
		if ((enemy.Extract == false && (enemy.GraveCard == false || (enemy.Grave[T] >= enemy.Threshold && enemy.Lands[T] > 0))) || enemy.Deck[T] <= active.SacMill * (active.Lands[T] / active.Activate)){
			while (active.Lands[T] - active.TapLands[T] >= active.Activate && active.Life[T] > active.Pain){
				active.Life[T] -= active.Pain;
				active.Lands[T]--;
				active.Grave[T]++;
				active.TapLands[T]++;
				enemy.Deck[T] -= active.SacMill;
				enemy.Grave[T] += active.SacMill;
				if (Report == 1 && Game >= SkipGame){
					cout << active.Name << " mills " << enemy.Name << " " << active.SacMill << "\n";
				}
			}
		}
	}
	//Nether Shadow
	if (active.Shadow > 0 && active.Grave[T] > active.Shadow){
		if (Report == 1 && Game >= SkipGame){
			cout << active.Name << " recurs " << active.Grave[T] - active.Shadow << " creature." << "\n";
		}
		active.Field[T] += active.Grave[T] - active.Shadow;
		active.Grave[T] = active.Shadow;
	}
	//Nether Spirit
	if (active.Spirit > 0 && active.Grave[T] == active.Spirit){
		active.Field[T]++;
		active.Grave[T]--;
		if (Report == 1 && Game >= SkipGame){
			cout << active.Name << " recurs a creature." << "\n";
		}
	}
	//Chancellor of the Tangle
	if (active.Tangle > 0 && T == 1 && active.StartHand >= active.Tangle){
		active.Field[T] = 1;
		active.Hand[T]--;
	}
	//Turbo Slug
	if (active.Slug > 0 && (active.Hand[T] + enemy.TapCrtr[T] - enemy.Field[T]) * active.Power >= enemy.Life[T]){
		active.Field[T] += active.Hand[T];
		active.Hand[T] = 0;
		cout << "Unleash the slugs!" << "\n";
	}
	//land backed cards
	if (active.Cost > 0){
		//cast cards
		while (active.Lands[T] - active.TapLands[T] >= active.Cost && active.Hand[T] > 0 && active.IsCreat == true){
			if (active.Token > 0){ //Emeria's Call
				if (enemy.Extract == 0){
					active.Field[T] += active.Token;
					active.Grave[T] ++;
					if (Report == 1 && Game >= SkipGame){
						cout << active.Name << " makes " << active.Token << " tokens." << "\n";
					}
				}
			} else { //creatures
				active.Field[T]++;
				active.Life[T] -= active.Pain;
				if (Report == 1 && Game >= SkipGame){
					cout << active.Name << " casts a creature." << "\n";
				}
			}
			active.Hand[T]--;
			active.TapLands[T] += active.Cost;
		}
	}
	//determine max direct damage can be dealt this turn
	active.MaxBurn[T] = 0;
	if (active.TapDam > 0 || (active.SacDam > 0 && active.Grave[T] >= active.Threshold)){
		active.MaxBurn[T] = active.Spike * ((active.Lands[T] - active.TapLands[T]) / (active.TapDam + active.SacDam));
		if (enemy.Extract > 0 && active.TapDam == 0 && active.MaxBurn[T] * 2 < enemy.Life[T]){
			active.MaxBurn[T] = 0;
		}
	}
	if (active.Cost > 0){
		if (active.Hand[T] >= (active.Lands[T] - active.TapLands[T]) / active.Cost){
			active.MaxBurn[T] = active.Spike * ((active.Lands[T] - active.TapLands[T]) / active.Cost);
		} else {
			active.MaxBurn[T] = active.Spike * active.Hand[T];
		}
		if (enemy.Extract > 0 && active.MaxBurn[T] < enemy.Life[T]){
			active.MaxBurn[T] = 0;
		}
	}
	if (active.Pitch > 0){
		active.MaxBurn[T] = active.Spike * (active.Hand[T] / active.Pitch);
		if (enemy.Extract > 0 && active.MaxBurn[T] < enemy.Life[T]){
			active.MaxBurn[T] = 0;
		}
	}
	//if can kill opponent, do so
	if (active.MaxBurn[T] >= enemy.Life[T] || (enemy.Extract > 0 && active.MaxBurn[T] >= enemy.Life[T] - enemy.Pain) || (active.Spike > 0 && active.Burn == 0) || (enemy.Chancellor == true && enemy.Spike > 0) || enemy.Slug == true){
		while (active.MaxBurn[T] > 0){
			enemy.Life[T] -= active.Burning();
		}
	}
	//enemy burns active player creatures
	StrikeDead = 0;
	while (enemy.MaxBurn[T] >= active.Tough && active.Field[T] > 0 && BurnLost == true){
		enemy.Burning(); //PROBLEM
		killer = enemy;
		target = active;
		if (KillCreature() == 0){
			StrikeDead++;
			AttackDam = 0;
		}
		enemy = killer;
		active = target;
		if (Report == 1 && Game >=SkipGame && active.ManLand == 0){
			cout << "remaining creatures " << active.Field[T] << "\n";
		}
	}
	//manlands
	if (active.ManLand > 0){
		active.MaxAttack = (active.Lands[T] - active.TapLands[T]) / active.ManLand;
		if (active.Barrens > 0 && active.Lands[T] - active.TapLands[T] == active.ManLand - 1){
			active.PCounters[T][1] += active.Barrens;
			active.TapLands[T] += active.ManLand - 1; // -1? deal w vigilance here?
		}
	}
	if (active.Haste == true && active.ManLand == 0){
		if (active.Ichorid > 0){
			active.MaxAttack = active.Grave[T] / active.Ichorid;
		} else {
			if (active.TapCrtr[T] > active.Field[T]) {
				active.TapCrtr[T] = active.Field[T];
			}
			active.MaxAttack = active.Field[T] - active.TapCrtr[T];
		}
	}
	if (active.Hostile > 0 && active.MaxAttack > active.Grave[T] / active.Hostile){
		active.MaxAttack = active.Grave[T] / active.Hostile;
	}
}

	//DECLARE Attackers and Blockers
int Declare(){
	//set Urza's saga p/t
	if (active.Team == true){
		active.Power = active.Field[T];
		active.Tough = active.Power;
	}
	if (enemy.Team == true){
		enemy.Power = enemy.Field[T];
		enemy.Tough = enemy.Power;
	}
	//get # attackers
	active.Attack[T] = active.MaxAttack - active.SkipAttack[T];
	if (active.Attack[T] < 0){
		//cout << "Skip Attack Error game " << Game << "\n";
		active.Attack[T] = 0;
		active.SkipAttack[T] = active.MaxAttack;
	}
	if (active.Unblock == false){ //get enemy available blockers
		if (enemy.ManLand > 0){
			enemy.Blockers[T] = (enemy.Lands[T] - enemy.TapLands[T]) / enemy.ManLand;
			if (enemy.Hostile > 0 && enemy.Blockers[T] > enemy.Grave[T] / enemy.Hostile){
				enemy.Blockers[T] = enemy.Grave[T] / enemy.Hostile;
			}
		} else {
			enemy.Blockers[T] = enemy.Field[T] - enemy.TapCrtr[T];
		}
	} else {
		enemy.Blockers[T] = 0;
	}
	//if max attack can't kill and active player will die on swingback, attack less
	if (active.Attack[T] > 0 && (active.Attack[T] - (enemy.Blockers[T] / active.MinBlock)) * active.Power < enemy.Life[T]){
		if (active.Trample == false && active.Vigil == false && active.SacEOT == false && active.VarPT == false && active.Link == false && active.Pain < 1){ //ignore relevant combat abilities
			if (enemy.ManLand > 0){ //check enemy damage from next attack w their current resources
				Attacker = (enemy.Lands[T] / enemy.ManLand);
			} else {
				Attacker = enemy.Field[T];
			}
			while(active.Attack[T] > 0 && (Attacker - active.SkipAttack[T]) * enemy.Power >= active.Life[T]){ 
			//if enemy prob has onboard lethal, and you prob don't, attack less if able
				active.SkipAttack[T]++;
				active.Attack[T]--;
			//	SkipGame = Game;
			//	cout << "killing you";
			}
		}
	}
	//skip attacks if will neither change life totals nor kill any blockers
	if (active.Link == false && active.Trample == false && enemy.Chump == false && enemy.Blockers[T] / active.MinBlock >= active.Attack[T]){
		active.SkipAttack[T] = active.MaxAttack;
		active.Attack[T] = 0;
		if (active.Mammoth > 0 || active.Frost == true){
			active.Choice[T] = 0;
			active.Decision[T] = 0; //causing problems?
		}
	}
	//exile graveyard costs to attack
	active.Grave[T] -= active.Attack[T] * active.Hostile;
	if (active.Ichorid > 0){
		active.Grave[T] -= active.Attack[T] * active.Ichorid;
		active.Field[T] += active.Attack[T];
	}
	enemy.Grave[T] -= active.Attack[T] * active.Tyrant;
	if (enemy.Grave[T] < 0) {
		enemy.Grave[T] = 0;
	}
	//pump Crawling Barrens and Raging Ravine 
	if (active.Attack[T] > 0 && (active.Barrens > 0 || active.Rage > 0)){
		for(Attacker = 1; Attacker <= active.Attack[T]; Attacker++){
			active.PCounters[T][Attacker] += active.Barrens + active.Rage;
		}
		//this->Debug();
		//if exactly 4 excess lands WHAT IF MULTIPLE ATTACKERS W DIF COUNTERS
		if (active.Lands[T] - active.TapLands[T] - active.Attack[T] * active.ManLand == active.ManLand - 1){
			active.PCounters[T][1] += active.Barrens + active.Rage;
		}
		//if 5+ unused lands, pump now or block later
	}
	//pump Blackbloom Rogue
	if (active.RogueThresh > 0){
		if (enemy.Grave[T] >= active.RogueThresh){
			if (Report == 1){
				cout << "GOING ROGUE" << "\n";
			}
			active.Power = active.PStart + active.RogueBonus;
		} else {
			active.Power = active.PStart;
		}
	}
	if (enemy.RogueThresh > 0){
		if (active.Grave[T] >= enemy.RogueThresh){
			enemy.Power = enemy.PStart + enemy.RogueBonus;
		} else {
			enemy.Power = enemy.PStart;
		}
	}
	active.Parameters(enemy);
	//Determine enemy blocking pattern
	//P2 clear enemy blocking pattern and P1 same, unless this is first turn of reset
	if ((active.Name == P1.Name && active.Lost == false && enemy.AttackReset == false) || active.Name == P2.Name){
		for(Attacker = 0; Attacker <= active.Attack[T]+2; Attacker++){ //clear block pattern
			enemy.Fight[T][Attacker] = 0;
		}
		//default blocks
		if (active.Attack[T] > 0){
			if (enemy.Chump == true){ //if these blockers die in combat, then default all blockers skip
				enemy.Fight[T][active.Attack[T]+1] = enemy.Blockers[T];
				Attacker = 1; //if defender will die if skips all blocks, then deploy blockers if able
				while ((active.Attack[T] - Attacker + 1) * active.Power >= enemy.Life[T] && enemy.Fight[T][active.Attack[T]+1] > 0 && enemy.Link == false){
					enemy.Fight[T][active.Attack[T]+1]--;
					enemy.Fight[T][Attacker] = 1;
					Attacker++;
				}
			} else { //these blockers survive combat
				if (active.Multi == false){ //if each attacker is killed by one blocker, then block even spread
					for (Blocker = 1; Blocker <= enemy.Blockers[T]; Blocker++){
						if (Blocker <= active.Attack[T]){
							enemy.Fight[T][Blocker] = 1;
						}
					}
					Blocker--;
					if (Blocker < active.Attack[T]){
						Blocker = active.Attack[T];
					}
					enemy.Fight[T][active.Attack[T]+1] = Blocker - active.Attack[T]; //excess blockers auto-skip
				} else { //if each attacker requires multiple blockers to kill, then all blockers on 1st attacker
					enemy.Fight[T][1] = enemy.Blockers[T];
					for (Attacker = 1; Attacker <= active.Attack[T]; Attacker++){ //shift blockers if over max necessary block
						if (enemy.Fight[T][Attacker] > active.MaxBlock){
							enemy.Fight[T][Attacker + 1] = enemy.Fight[T][Attacker] - active.MaxBlock;
							enemy.Fight[T][Attacker] = active.MaxBlock;
						}
					}
					//check if defender will die w this block pattern and adjust accordingly if able
					TC = T;
					w = 0;
					BlockSave();
				}
			}
		}
	}
	//if enemy lost last game, retrieve adjusted block pattern saved in next turn
	if (enemy.Lost == true || active.ChangeMind == true){ //changemind still a thing?
		for(int count = active.Attack[T]+1; count>0; count--){
			enemy.Fight[T][count] = enemy.Fight[T+1][count];
			enemy.Fight[T+1][count] = 0;
		}
	}
	//tap attackers and lands activating manlands
	if (active.ManLand > 0){
		active.TapLands[T] += (active.Attack[T] * active.ManLand);
	} else {
		active.TapCrtr[T] += active.Attack[T];
	}
	if (active.Vigil == true){
		active.TapCrtr[T] -= active.Attack[T];
		if (active.ManLand > 0){
			active.TapLands[T] -= active.Attack[T];
		}
	}
	if (enemy.ManLand > 0){
		enemy.TapLands[T] += enemy.Blockers[T] * (enemy.ManLand - 1);
		//pump blocking Barrens
		if (enemy.Barrens > 0){
			for (BlockCheck = 1; BlockCheck <= enemy.Blockers[T]; BlockCheck++){
				enemy.PCounters[T][BlockCheck] += enemy.Barrens;
			}
		}
	}
	//track largest attack for report screen MOVE TO SUMMARY()
	active.BigAttack = 0;
	for (int count = 1; count <= T ; count++){
		if (active.Attack[count] > active.BigAttack){
			active.BigAttack = active.Attack[count];
		}
	}
	//attack report
	if (Report == 1 && Game >= SkipGame){ 
		cout << active.MaxAttack << " Max attacks" << "\n";
		cout << active.Attack[T] << " Attackers" << "\n";
		cout << active.SkipAttack[T] << " Skip Attacks" << "\n";
		cout << enemy.Blockers[T] << " Enemy Blockers" << "\n";
		if (active.Attack[T] > 0){
			cout << " S ";
			for (Attacker = 1; Attacker <= active.Attack[T]; Attacker++){
				cout << " A" << Attacker;
			}
			cout << "\n";
			for (Blocker = active.Attack[T] + 1; Blocker > 0; Blocker--){
				cout << " " << enemy.Fight[T][Blocker] << " ";
			}
			cout << "\n";
		}
		cout << "Enemy life was " << enemy.Life[T] << "\n";
	}
	return 0;
}

	//RESOLVE COMBAT
int Combat(){
	//resolve attacks
	for (Attacker = 1; Attacker <= active.Attack[T]; Attacker++){ //check each attacker outcome
		if (active.Barrens > 0 || active.Rage > 0){
			active.Power = active.PStart + active.PCounters[T][Attacker];
			active.Tough = active.TStart + active.PCounters[T][Attacker];
		}
		AttackDam = active.Power; //damage from attackers this exchange is reset
		BlockDam = 0; //damage from blockers this exchange is reset
		StrikeDead = 0; //blockers killed by striker is reset
		Survivor = false;
		if (enemy.Fight[T][Attacker] >= active.MinBlock){ //legal BLOCKER(s) found
			BlockDam = enemy.Fight[T][Attacker] * enemy.Power;
			//First Strike
				//non-strike attacker vs strike blocker
			if (active.FStrike == false && active.DStrike == false && (enemy.FStrike == true || enemy.DStrike == true)){
				if (BlockDam >= active.Tough){ // if strike blockers deal lethal,
					killer = enemy;
					target = active;
					if (KillCreature() == 0){ //kill attacker and if attacker doesnt regen, erase attacker damage
						AttackDam = 0;
						BlockDam = 0;
					}
					enemy = killer;
					active = target;
				}
			}
				//strike attacker vs non-strike blocker
			if ((active.FStrike == true || active.DStrike == true) && enemy.FStrike == false && enemy.DStrike == false){
				Blocker = 1;
				while (AttackDam >= enemy.Tough && Blocker <= enemy.Fight[T][Attacker]){ //try to kill blockers
					Blocker++;
					AttackDam -= enemy.Tough; //apply attack damage
					killer = active;
					target = enemy;
					if (KillCreature() == 0){ //dead blockers either regen or erase their damage
						BlockDam -= enemy.Power;
						StrikeDead++;
					}
					active = killer;
					enemy = target;
				}
			}
			//Regular Combat
			if (active.DStrike == true){ //if dstrike attacker in reg combat, deal power again
				AttackDam += active.Power;
			}
			if (enemy.DStrike == true){ //if dstrike blocker(s) in reg combat, double total damage
				BlockDam *= 2;
			}
			if (enemy.Switch == true && enemy.Tough > enemy.Power && (active.Power >= enemy.Tough || active.Dtouch == true)){
				//switcheroo for attacker + blocker
			}
			if (BlockDam >= active.Tough || (enemy.Dtouch == true && BlockDam > 0)){ //if attacker takes lethal,
				killer = enemy;
				target = active;
				if (KillCreature() == 1){ //attacker dies unless regen
					//if attacker regens, trigger blocker's frost
					if (enemy.Frost == true){
						enemy.Frozen[T]++;
						cout << "freeze - E " << enemy.Frozen[T] << "\n";
					}
				}
				enemy = killer;
				active = target;
				if (active.Frost == true){ //if dead attacker has frost and is multiblocked and can only kill 1 blocker
					if (enemy.Fight[T][Attacker] > 1 && active.Power >= enemy.Tough && active.Power < enemy.Tough * 2){
						active.Option++;
						if (Game >+ SkipGame){
						
						cout << "Option++ game " << Game << " turn " << T << "\n";
						}
						if (active.Option > active.Decision[T]){
							active.Decision[T]++; //create option to freeze multiples instead of kill one
						}
					}
				}
				if (active.Switch == true && active.Power < active.Tough){ //if attacking fumarole takes lethal, switch
					AttackDam = active.Tough;
				}
			} else { //attacker lives, trigger blocker's frost
				Survivor = true;
				if (enemy.Frost == true){
					enemy.Frozen[T]++;
					cout << "freeze - A " << enemy.Frozen[T] << "\n";
				}
			}
			//deal trample
			if (active.Trample == true && AttackDam > enemy.Fight[T][Attacker] * enemy.Tough){
				enemy.Life[T] -= active.Power - (enemy.Fight[T][Attacker] * enemy.Tough);
			}
			//gain block link
			if (enemy.Link == true){
				enemy.Life[T] += BlockDam;
			}
			//gain attack link
			if(active.Link == true){
				active.Life[T] += AttackDam;
			}
			//resolve blockers of this attacker (omitting 1strike deaths)
			for(Blocker = 1; Blocker <= enemy.Fight[T][Attacker] - StrikeDead; Blocker++){ //for each blocker against this attacker
				if (enemy.Fight[T][Blocker] >= active.MinBlock){ // if actually blocking,
					enemy.Grave[T] -= enemy.Hostile; //pay graveyard costs to block
				}
				//check if attacker has killed a blocker
				if ((AttackDam >= enemy.Tough || (active.Dtouch == true && AttackDam > 0)) && (active.Frost == false || active.Choice[T] == 0 || active.Choice[T] < active.Option)){
					//dead blocker absorbs damage
					if (active.Dtouch == false){
						AttackDam -= enemy.Tough;
					} else {
						AttackDam--;
					}
				//	if (Game >= SkipGame){
				//		cout << "good shoot " << Game << " game turn " << T << "\n";
				//	}
					//if blocker regens vs frost, freeze blocker
					target = enemy;
					killer = active;
					if (KillCreature() == 1){
						if (active.Frost == true){
							active.Frozen[T]++;
							cout << "freeze - B " << active.Frozen[T] << "\n";
						}
					}
					enemy = target;
					active = killer;
				//	if (enemy.Switch == true && enemy.Power > enemy.Tough){
				//		BlockDam -= enemy.Power;
				//		BlockDam += enemy.Tough;
				//	}
					Survivor = false;
				} else { //this blocker lives
					if (active.Frost == true && AttackDam == active.Power){ //freeze surviving blockers
						if (active.Power >= enemy.Fight[T][Attacker]){
							active.Frozen[T] += enemy.Fight[T][Attacker];
							cout << "freeze - C " << active.Frozen[T] << " choice " << active.Choice[T] << " of " << active.Option << "\n";
						} else {
							active.Frozen[T] += active.Power;
							cout << "freeze - D - " << active.Frozen[T] << " turn " << T << "\n";
						}
						AttackDam--;
					}
				}
			}
			if (Survivor == true){ //no one died in this block exchange
			//	cout << ActivePlayer << " BOUNCE turn " << T << "\n";
				if (active.Switch == true){ //create trade v bounce option for fumarole
					active.Option++;
				}
			}
		} else { //this attacker is unblocked
			//burn attackers
			OnFire = 0;
			if (enemy.MaxBurn[T] >= active.Tough && StrikeDead < active.Attack[T] && BurnLost == true){
				while (enemy.MaxBurn[T] > 0 && OnFire < active.Tough){
					OnFire += enemy.Burning(); //attacker is burning
					if (OnFire >= active.Tough){ //attacker is toast
						killer = enemy;
						target = active;
						if (KillCreature() == 0){ //if attacker doesn't regen, erase their damage
							StrikeDead++;
							AttackDam = 0;
						}
						enemy = killer;
						active = target;
					}
				}
			}
			if (active.Infect == false){ //deal unblocked damage
				if (active.Switch == true && active.Tough > active.Power && active.Power > enemy.MaxBurn[T]){
					enemy.Life[T] -= active.Tough; //You let this fumarole just wander thru again
				} else { //regular damage
					enemy.Life[T] -= AttackDam;
				}
			} else { //poison counters
				active.Poison[T] += AttackDam;
			}
			if (active.DStrike == true){ //deal doublestrike damage
				enemy.Life[T] -= AttackDam;
			}
			if(active.Link == true){ //gain attacker lifelink
				active.Life[T] += AttackDam;
			}
		}
	}
	if (Report == 1 && Game >= SkipGame){
		cout << "Enemy life is now " << enemy.Life[T] << "\n";
	}
	if (enemy.Life[T] < enemy.LowLife){
		enemy.LowLife = enemy.Life[T];
	}
	//if previously expected number of alt decisions is more than actually encountered this turn, then reduce decision range to that #
	if (active.Decision[T] > active.Option){
		active.Decision[T] = active.Option;
	}
	return 0;
}

	//END STEP
void End(){
	//enemy burn deck targets you
	while (enemy.MaxBurn[T] > 0){
		active.Life[T] -= enemy.Burning();
		if (Report == 1 && Game >= SkipGame){
			cout << active.Name << " life is burned to " << active.Life[T] << "\n";
		}
	}
	//discard
	if (active.Hand[T] > 7){
		active.Hand[T] = 7;
		if (active.Madness == true){
			active.Field[T] ++;
			if (Report == 1 && Game >= SkipGame){
				cout << active.Name << " plays a madness creature." << "\n";
			}
		} else {
			active.Grave[T]++;
			if (Report == 1 && Game >= SkipGame){
				cout << active.Name << " discards." << "\n";
			}
		}
	}
	if (active.Mammoth > 0){	//shrink landfall
		active.Power = active.PStart;
		active.Tough = active.TStart;
	}
	if (active.SacEOT == true){	//kill sac-eot creatures
		active.Grave[T] += active.Field[T];
		active.Field[T] = 0;
	}
	//enemy checks for Surgical Extraction target
	if (enemy.Extract > 0 && enemy.Hand[T] > 0 && enemy.Life[T] > enemy.Pain && active.Grave[T] >= enemy.Extract){
		active.Hand[T] = 0;
		active.Grave[T] = 0;
		active.Deck[T] = 0;
		enemy.Life[T] -= enemy.Pain;
		enemy.Grave[T] += 1;
		enemy.Hand[T] -= 1;
//		if (Report == 1 && Game >= SkipGame){
			cout << enemy.Name << " extracts. Turn " << T << " game " << Game << "\n";
//		}
	}
	//restack empty counters
	Attacker = 12;
	while (Attacker > 0){
		Attacker--;
		if (active.PCounters[T][Attacker] > 0){
			for(int count = Attacker - 1; count > 0; count--){
				if(active.PCounters[T][count] == 0){
					active.PCounters[T][count] = active.PCounters[T][Attacker];
					active.PCounters[T][Attacker] = 0;
				}
			}
		}
	}
	//untap urza saga nonhaste UGLY
	if (active.Field[T] > 0){
		active.TapCrtr[T] -= active.CardEBT;
	}
	if (Report == 1 && Game >= SkipGame){
		cout << "End " << active.Name << " Turn " << T << "\n";
		cin >> Pause;
	}
}

	//PASS TURN
void Player::Next(){ //record all gamestate variables on to next turn
	this->Life[T+1] = this->Life[T];
	this->Field[T+1] = this->Field[T];
	this->Grave[T+1] = this->Grave[T];
	this->Lands[T+1] = this->Lands[T];
	this->Deck[T+1] = this->Deck[T];
	this->Hand[T+1] = this->Hand[T];
	this->TapCrtr[T+1] = this->TapCrtr[T];
	this->TapLands[T+1] = this->TapLands[T];
	this->AltVar[T+1] = this->AltVar[T]; //ERASE?
	this->Frozen[T+1] = this->Frozen[T];
	this->Poison[T+1] = this->Poison[T];
	this->MaxBurn[T+1] = this->MaxBurn[T];
	for (Attacker = 1; Attacker < 12; Attacker++){
		this->PCounters[T+1][Attacker] = this->PCounters[T][Attacker];
	}
}

int main(){
	GameOver = 0;
	Game = 1;
	SkipGame = 0;
	cout << "MONO MAGIC 2021\n";
	cout << "By Robert Vroman\n";
	cout << "All rights reserved Hasbro and Wizards of the Coast\n\n";
	cout << "Choose Player 1\n";
	P1.Name = Menu();
	P1.DeckChoice();
	cout << "Choose Player 2\n";
	P2.Name = Menu();
	P2.DeckChoice();
	cout << "\n" << P1.Name << "\n";
	cout << " vs\n";
	cout << P2.Name << "\n\n";
	while (Report < 1 || Report > 5){
		cout << "Choose reporting detail level:\n";
		cout << "1. Play by play\n";
		cout << "2. Attacks only\n";
		cout << "3. Full grid summary\n";
		cout << "4. Game winners\n";
		cout << "5. Conclusion only\n";
		cin >> Report;
	}
	cout << "Begin report on Game: ";
	cin >> SkipGame;
	//compare deck interactions
	P1.Parameters(P2);
	P2.Parameters(P1);
	T = 0;
	//main turn cycle
	while (GameOver == 0){
		T += 1; //increment turn
		if (T > LongGame){
			LongGame = T;
		}
		if (T == 1){ //turn 1 set up
			P1.Setup();
			P2.Setup();
			if (P1.Chancellor == true){
				P2 = P1.Chance(P2);
			}
			if (P2.Chancellor == true){
				P1 = P2.Chance(P1);
			}
		}
		P1.WinFlag = false;
		P2.WinFlag = false;
		//P1 takes its turn
		active = P1;
		enemy = P2;
		Turn(); //USE RETURN INT OVER WINFLAG?
		P1 = active;
		P2 = enemy;
		if (GameOver == 0){
			if (P1.WinFlag == false){ //if P1 doesn't win, proceed to P2 turn
				active = P2;
				enemy = P1;
				Turn(); //P2 takes its turn
				P2 = active;
				P1 = enemy;				
			} else { //P1 wins this turn
				if (Game >= SkipGame && Report < 4){ //end game report
					w = 0;
					P1.Summary(P2);
					w = 1;
					P2.Summary(P1);
					cout << "Enter any lower integer to continue or skip to game #\n";
					cin >> SkipGame;
				}
				P1.FlagOff(); //turn off prior win flags
				P2.FlagOff();
				P2 = P1.Win(P2); //P2 find alt plays
			}
		}
		//if P2 wins this turn,
		if (P2.WinFlag == true){
			if (Game >= SkipGame && Report < 4){ //end game report
				w = 0;
				P1.Summary(P2);
				P2.Summary(P1);
				cout << "Enter any lower integer to continue or skip to game #\n";
				cin >> SkipGame;
			}
			P1.FlagOff(); //turn off prior win flags
			P2.FlagOff();
			P1 = P2.Win(P1); //P1 search alt plays on prior turns
		}
		//if no player wins the game this turn, turn off win flags from prior games
		if (P1.WinFlag == false && P2.WinFlag == false){
			P1.FlagOff();
			P2.FlagOff();
		}
		//transfer game state to next turn
		P1.Next();
		P2.Next();
		StaleMate(); //Check for stalemate
		if (T < CheckPoint){ //end stalemate
			if (Override == true){
			//	cout << "end override game " << Game << "\n";
			}
			Override = false;
		}
		//check for (un)flip card
		if (P1.Flip > 0 || P2.Flip > 0){
		//	P1.FlipCard();
		//	P2.FlipCard();
		}
	}
	cout << "Game Over";
	return 0;
}
