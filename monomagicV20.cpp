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
string ActivePlayer; //player 1 or 2 name here
int ActualSkips; //# available blockers who for whatever reason did not end up blocking this turn
int BlockedAttackers; //# attackers this turn that are blocked
int BlockCheck; //counter for checking blocks
bool Survivor; //whether current combatant survives

class Player{
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
		bool IsCreat = false; //this card deals damage via creatures
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
		int LowLife; //lowest life total this deck has been reduced to on any game
		int MaxBurn[62]; //total burn damage that can be dealt this turn
		int SkipAttack[62]; //# available attackers not attacking
		int TapLands[62]; //# tapped lands in play
		int TapCrtr[62]; //# tapped creatures in play
		void Menu(); //deck select menu
		int Burning(Player enemy); //activate direct damage abilities
		void ClearVars(); //set all variables to default
		int Debug(); //display current gamestate
		void DeckChoice(); //menu for deck selection
		void FlagOff(); //reset win flags
		int FlipCard(); //activate flip cards
		int KillAttacker(Player enemy); //remove dead creature
		int LandFall(Player enemy); //play lands
		void Next(Player enemy); //pass gamestate variables after every turn
		void Summary(Player enemy); //end of game report
		Player Parameters(Player enemy); //adjust abilities relative to enemy deck
		Player Setup(Player enemy); //initialize gamestate
		Player Chance(Player enemy); //trigger Chancellors
		Player Cast(Player enemy); //play cards
		Player Combat(Player enemy); //Resolve combat
		Player Declare(Player enemy); //set attackers and blockers
		Player End(Player enemy); //end step
		Player AttackSkip(Player enemy); //Losing player looks for most recent attack and blocks instead
		Player Turn(Player enemy); //main turn cycle
		Player Win(Player enemy); //losing player searches for alt blocks/attacks/choices
		Player Reset(Player enemy); //reset the game to a previous turn
		Player BlockShuffle(Player enemy); //losing player incrementally rearranges existing blockers
		Player BlockSave(Player enemy); //defender adjusts blockers to avoid immediate death
		void StaleMate(Player enemy); //fast forward thru locked game states
		void FullCopy(Player enemy); //copy all decision variables on to next turn during stalemate
} P1, P2;

int Player::Debug(){
	cout << this->Name << "\n";
	cout << "Game " << Game << " Turn " << T << "\n";
	cout << "Active Player " << ActivePlayer << "\n";
	cout << "Attacks " << this->Attack[T] << " Blocks " << this->Blockers[T] << "\n";
	cout << "Tangle " << this->Tangle << " start hand " << this->StartHand << "\n";
	cout << "Counters 1: " << this->PCounters[T][1] << " Counters 2: " << this->PCounters[T][2] << "\n";
	cout << "Decisions " << this->Decision[T] << " choice " << this->Choice[T] << " option " << this->Option << "\n";
	cout << "Haste " << this->Haste << " maxblock " << this->MaxBlock << "\n";
	cout << "P " << this->Power << " T " << this->Tough << " VarPT " << this->VarPT << " Multi " << this->Multi << "\n";
	return 0;
}

//NEW GAME
	//set all variables to default
void Player::ClearVars(){
	for(int count=0; count<63; count++){
		this->AltVar[count] = 0;
		this->Decision[count] = 0;
		this->Attack[count] = 0;
		this->Blockers[count] = 0;
		this->Deck[count] = 0;
		this->Field[count] = 0;
		this->Grave[count] = 0;
		this->Hand[count] = 0;
		this->Lands[count] = 0;
		this->Life[count] = 20;
		this->SkipAttack[count] = 0;
		for(int i = 0; i<160; i++){
			this->Fight[count][i] = 0;
		}
	}
	this->Lost = false;
	this->Chancellor = false;
	this->DeckFlag = false;
	this->DStrike = false;
	this->Dtouch = false;
	this->Flash = false;
	this->Flying = false;
	this->Frost = false;
	this->FStrike = false;
	this->Haste = false;
	this->Hazard = false;
	this->Hex = false;
	this->Indestruct = false;
	this->Infect = false;
	this->IsCreat = true;
	this->IsLand = false;
	this->Link = false;
	this->Madness = false;
	this->Reach = false;
	this->SacEOT = false;
	this->Slug = false;
	this->Switch = false;
	this->Trample = false;
	this->Unblock = false;
	this->Vigil = false;
	this->WinFlag = false; //flag if this player has won the current game
	this->PStart = 1;
	this->TStart = 1;
	this->Power = 1;
	this->Tough = 1;
	this->Activate = 0;
	this->Barrens = 0;
	this->BigAttack = 0;
	this->Cost = 0;
	this->Flip = 0;
	this->Mammoth = 0;
	this->MaxAttack = 0;
	this->MaxBlock = 1;
	this->MinBlock = 1;
	this->Mine = 0;
	this->Pain = 0;
	this->Pitch = 0;
	this->SacGen = 0;
	this->StartHand = 1;
	this->Token = 0;
	this->LowLife = 20;
}

	//Display tournament menu
void Player::Menu(){
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
	DeckSelect--;
	this->Name = Tournament[DeckSelect];
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
	if (this->Name == P2.Name && this->StartHand == 1){ //decks that don't need more than 1 card in hand mull to 0 on the draw.
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
		this->VarPT = true;
	}
}

	//Initialize new game
Player Player::Setup(Player enemy){
	this->MaxBurn[0] = 0;
	this->Hand[1] = this->StartHand;
	this->Deck[0] = 60 - this->StartHand;
	this->Deck[1] = 60 - this->StartHand;
	this->Life[0] = 20;
	this->Life[1] = 20;
	this->Grave[0] = 0;
	this->Grave[1] = 0;
	if (this->Flash == true && (this->Name == P2.Name || this->Spike > 0)){
		enemy = this->Cast(enemy);
	}
	return enemy;
}

	//adjust abilities relative to enemy deck
Player Player::Parameters(Player enemy){
	if (this->IsCreat == true && enemy.IsCreat == true){
		//convert flying to unblockable
		if ((this->Flying == true && enemy.Reach == false) || enemy.SacEOT == true){
			this->Unblock = true;
			if (this->IsCreat == true && Game == 1){
				cout << "\n" << this->Name << " is unblockable." << "\n";
			}
		}
		//remove irrel trample
		if (this->Power <= enemy.Tough){
			this->Trample = false;
		}
		//determine if blocking 1 on 1 causes resource loss
		if (enemy.Power >= this->Tough || enemy.Dtouch == true || this->Hostile > 0 || (enemy.DStrike == true && enemy.Power * 2 >= this->Tough)){
			this->Chump = true;
		}
		//strikers chump off
		if ((this->FStrike == true || this->DStrike == true) && enemy.Regen == 0 && this->Power >= enemy.Tough){
			this->Chump = false;
		}
		//always chump vs variable p/t creatures
		if (enemy.VarPT == true){
			if (Game == 1){
				cout << "varble pt" << "\n";
			}
			this->Chump = true;
		}
		//special abilities that turn off chump ?= this->SacEOT == true ||
		if (this->Shadow > 0 || (this->Regen == 1 && enemy.DStrike == false)){
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
			int j = enemy.Power;
			if (j == 0){
				j = this->Tough;
			}
			while (this->Tough - j > 0){
				j += enemy.Power;
				this->MaxBlock++;
			}
			if(MaxBlock < MinBlock){
				MaxBlock = MinBlock;
			}
		}

		if ((this->FStrike == true || this->DStrike == true) && enemy.Regen == 0 && this->Power >= enemy.Tough && enemy.Tough > 0){
			this->MaxBlock = (this->Power / enemy.Tough) + 1;
		} else {
			if (this->Trample == true && this->MaxBlock * enemy.Tough < this->Power){
				this->MaxBlock = 0;
				if (enemy.Tough > 0){
					while (this->MaxBlock * enemy.Tough < this->Power){
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
	return enemy;
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
		cout << enemy.Name << " will start the game over and target creatures." << "\n";
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
				enemy.ChangeMind = true;
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
						enemy = this->BlockShuffle(enemy);
					} else {
						while (enemy.Fight[TC][Attacker] > 1){
							enemy = this->BlockShuffle(enemy); //shuffle blockers as needed
						}
					}
					enemy = this->Reset(enemy); //reset gamestate to turn TC
					if (Game >= SkipGame){
						cout << "\n" << enemy.Name << " will replay turn " << TC << " and shuffle blockers." << "\n";
						cout << "\n" << "BEGIN GAME " << Game << "\n";
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
					enemy = this->BlockSave(enemy);
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
					cout << "\n" << enemy.Name << " will replay turn " << TC << " and a skipped block now blocks." << "\n";
					cout << "\n" << "BEGIN GAME " << Game << "\n";
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
				cout << enemy.Name << " will replay turn " << TC << " and change a decision." << "\n";
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
		cout << "\n" << "Game " << Game - 1;
		cout << "\n" << enemy.Name << " starts the game over and mulligans to " << enemy.StartHand << "\n" << "\n";
			SkipGame = Game;
		T = 0;
		return enemy;
	}
	if (this->Name == P1.Name){
		cout << "Player 1 ";
	} else {
		cout << "Player 2 ";
	}
	cout << this->Name << " strictly wins in " << Game-1 << " games." << "\n";
	if (enemy.Score == 0){
		cout << "Ace!" << "\n";
		cout << "Lowest enemy life " << enemy.LowLife << "\n";
		cout << "Lowest enemy life " << this->LowLife << "\n";
		
	} else {
		cout << enemy.Name << " wins " << enemy.Score << "\n";
	}
	cout << "Longest game " << LongGame << "\n" << "\n";
	GameOver = 1;
	return enemy;
}

		//incrementally shuffle through multi-blocking options
Player Player::BlockShuffle(Player enemy){
	enemy.Fight[TC][Attacker]--;
	Deployed = 0;
	for(ct3 = 0; ct3 < Attacker; ct3++){
		Deployed += enemy.Fight[TC][ct3];
	}
	enemy.Fight[TC][Attacker+1] = enemy.Blockers[TC] - (Deployed + enemy.Fight[TC][Attacker] + ActualSkips);
	for (ct3 = Attacker + 2; ct3 < this->Attack[TC] + 1; ct3++){
		enemy.Fight[TC][ct3] = 0;
	}
	for (ct3 = Attacker; ct3 < this->Attack[TC] - 1; ct3++){
		if (enemy.Fight[TC][ct3+1] > enemy.Fight[TC][ct3]){
			enemy.Fight[TC][ct3+2] = enemy.Fight[TC][ct3+1] - enemy.Fight[TC][ct3];
			enemy.Fight[TC][ct3+1] = enemy.Fight[TC][ct3];
		}
	}
	return enemy;
}

		//adjust blockers to avoid immediate death
Player Player::BlockSave(Player enemy){
	BlockedAttackers = 0; //recalculate how many attackers are blocked
	for (Blocker = 1; Blocker <= this->Attack[TC]; Blocker++){
		if (enemy.Fight[TC][Blocker] > 0 && this->Trample == false){
			BlockedAttackers++;
		}
	}
	//if defender will die with this block pattern, spread blockers if able
	while ((this->Attack[TC] - BlockedAttackers) * this->Power >= enemy.Life[TC-w] && enemy.Link == false && BlockedAttackers < enemy.Blockers[TC]){
		Attacker = this->Attack[TC];
		while(Attacker > 0){
			if (enemy.Fight[TC][Attacker] > 1){
				enemy.Fight[TC][Attacker]--;
				enemy.Fight[TC][Attacker+1]++;
				if (enemy.Fight[TC][Attacker+1] == 1){
					BlockedAttackers++;
//					SkipGame = Game;
				}
//				cout << "you're gonna die" << "\n";
				Attacker = 1;
			}
			Attacker--;
		}
	}	
	return enemy;
}

		//winner blocks the same
Player Player::Reset(Player enemy){
	enemy.Lost = true;
	int j;
	if (this->Attack[TC] > enemy.Attack[TC]){
		j = this->Attack[TC];
	} else {
		j = enemy.Attack[TC];
	}
	//record block change on turn after reset
	for (int i = 1; i <= j + 1; i++){
		enemy.Fight[TC+1][i] = enemy.Fight[TC][i];
		this->Fight[TC+1][i] = this->Fight[TC][i];
		
	}
	if (Game >= SkipGame){
	//	cout << "both save turn " << TC << " block pattern onto turn " << TC + 1 << "\n";
	}
	T = TC - 1;	//reset the game on turn before alt play found
	return enemy;
}

		//Losing player looks for most recent attack and blocks instead
Player Player::AttackSkip(Player enemy){
	//if all blocking options already played, switch the most recent attack to block, if enemy has at least one coresponding attack or block or is burn
	if (enemy.Attack[TC] > 0 && (this->Name == P2.Name || TC < T)){ //check the below
		if (this->Attack[TC] > 0 || (this->Attack[TC+1] > 0 && this->Name == P1.Name) || this->Fight[TC][1] > 0 || this->Fight[TC+1][1] > 0 || (this->Burn > 0 && BurnLost == true)){
			enemy.AttackReset = true;
			enemy.SkipAttack[TC]++;
			enemy.Choice[TC] = 0;
			T = TC - 1;
			if (Game >= SkipGame){
				cout << enemy.Name << " will replay turn " << TC << " and skip an attack." << "\n";
				cout << "\n" << "BEGIN GAME " << Game << "\n";
			}
		}
	}
	return enemy;
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
											P1.Next(P2);
											P2.Next(P1);
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
void Player::FullCopy(Player enemy){ //auto-fill remaining turns 
	this->Attack[T+1] = this->Attack[T];
	this->Decision[T+1] = this->Decision[T];
	this->Choice[T+1] = this->Choice[T];
	this->Deck[T+1] = this->Deck[T] - 1;
	this->Grave[T+1] = this->Grave[T] + 1; //CONFIRM
	if (this->Ichorid > 0 || this->Hostile > 0){
		this->Grave[T+1] --; //QUESTIONABLE
	}
	this->Blockers[T+1] = this->Blockers[T];
	for (Attacker = 1; Attacker <= enemy.Attack[T] + 1; Attacker++){
		this->Fight[T+1][Attacker] = this->Fight[T][Attacker];
	}
}

	//REPORT end of game
void Player::Summary(Player enemy){
	cout << this->Name;
	if (this->WinFlag == true){
		cout << " WINNER";
		if (enemy.Deck[T] < 1 && enemy.Life[T] > 0){
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
		if (enemy.Infect == false){
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
				if (enemy.Poison[TC] < 10){
					cout << " ";
				}
				cout << enemy.Poison[TC];
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
		if (enemy.Frost == true && this->Tough >= enemy.Power){
			cout << "\n" << "FRZN ";
			for (TC = 1; TC <= T; TC++){
				if (enemy.Frozen[TC] < 10){
					cout << " ";
				}
				cout << enemy.Frozen[TC];
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
		if (enemy.Unblock == false){
			for(Attacker = 1; Attacker <= enemy.BigAttack; Attacker++){
				cout << "\n" << "BLOK ";
				for (TC = 1; TC <= T; TC++){
					if (this->Fight[TC][Attacker] < 10){
						cout << " ";
					}
					if (enemy.Attack[TC] < Attacker){
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
				if (this->Fight[TC][enemy.Attack[TC] + 1] < 10){
					cout << " ";
				}
				if (this->Fight[TC][enemy.Attack[TC] + 1] == 0){
					cout << " ";
				} else {
					if (P2.WinFlag == true || this->Name == P2.Name || TC < T){
						cout << this->Fight[TC][enemy.Attack[TC] + 1];
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
int Player::KillAttacker(Player enemy){
	//if enemy can morph
	if (enemy.Morph > 0 && enemy.Lands[T] - enemy.TapLands[T] >= enemy.Morph && enemy.Lands[T] < enemy.Cost * 2){
		enemy.Option++;
		enemy.Decision[T] = 1; //create enemy option to morph
		if (enemy.Choice[T] == 1){ //enemy takes morph option
			enemy.TapLands[T] += enemy.Morph; //pay cost
			enemy.Lands[T]++; //enemy gains land
			if (ActivePlayer == enemy.Name){ //if morpher attacked, new land is tapped
				enemy.TapLands[T]++;
			}
							SkipGame = Game;
			cout << enemy.Name << " morphs and doesn't kill your guy. Game " << Game << " Turn " << T << "\n";
			return 0;
		}
	}
	//regen exception here
	if (this->Regen > 0 && this->Lands[T] - this->TapLands[T] >= this->Regen){
		this->TapLands[T] += this->Regen;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " regenerates a creature." << "\n";
		}
		return 1;
	} else { //kill an attacker
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " loses a creature." << "\n";
		}
		if (this->ManLand > 0){
			this->Lands[T]--; //remove land from play
			if (this->Vigil == false){
				this->TapLands[T]--; //adjust # tapped lands
			}
		} else {
			this->Field[T]--; //remove creature from play
			if (ActivePlayer == this->Name && this->Vigil == false && enemy.Burn == 0){
				this->TapCrtr[T]--; //the creature that died was tapped
			}
		}
		//deal with dying creature
		if (this->Morph > 0 && this->Lands[T] - this->TapLands[T] >= this->Morph && this->Lands[T] < this->Cost * 2){ //check for morph conditions
			this->Decision[T] = 1; //create option to morph
			this->Option++;
			if (this->Choice[T] == 1){ //taking morph option
				this->TapLands[T] += this->Morph; //pay cost
				this->Lands[T]++; //gain land
				if (ActivePlayer == this->Name){ //if morpher attacked, new land is tapped
					this->TapLands[T]++;
				}
				SkipGame = Game;
				cout << this->Name << " morphs a creature into a land. Game " << Game << " Turn " << T << "\n";
				return 0;
			}
		}
		//no more outs creature is actually dead
		if (this->Token == 0 && enemy.Hazard == false){ //tokens and spikefield targets exiled
			this->Grave[T]++; //card ends up in grave
		}
		if (this->Name == ActivePlayer){ //remove +1/+1 counters from dead creature
			this->PCounters[T][Attacker] = 0;
		} else {
			this->PCounters[T][Blocker] = 0;
		}
		return 0;
	}
}

	//Direct damage
int Player::Burning(Player enemy){
	BurnDam = 0;
	//sac damage lands
	if (this->SacDam > 0 && this->Lands[T] >= this->Activate){
		this->Life[T] -= this->Pain;
		BurnDam += Spike;
		this->Lands[T] -= 1;
		this->Grave[T] += 1;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " deals " << this->Spike << " damage." << "\n";
		}
	}
	//tap damage lands
	if (this->TapDam > 0 && this->Lands[T] - this->TapLands[T] >= this->TapDam){
		BurnDam += Spike;
		this->TapLands[T] += this->TapDam;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " deals " << this->Spike << " damage." << "\n";
		}
	}
	//spell damage
	if (this->Cost > 0 || this->Pitch > 0){
		if(this->Lands[T] - this->TapLands[T] >= this->Cost && this->Hand[T] >= this->Pitch){
			this->Life[T] -= this->Pain;
			BurnDam += Spike;
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
Player Player::Chance(Player enemy){
	//Dross
	enemy.Life[1] -= this->Spike * this->Hand[1];
	this->Life[1] -= this->Pain * this->Hand[1];
	//Forge
	this->Field[1] = this->Token * this->Hand[1];
	//Spires
	enemy.Deck[0] -= this->Mill * this->Hand[1];
	enemy.Grave[0] += this->Mill * this->Hand[1];
	enemy.Deck[1] -= this->Mill * this->Hand[1];
	enemy.Grave[1] += this->Mill * this->Hand[1];
	return enemy;
}

	//Activate flip card
int Player::FlipCard(){
	if (this->Flip > 0){
		if (this->Field[T] >= this->Flip && this->Lands[T] - this->TapLands[T] >= this->TapGen){
			cout << "TRANSFORM! Turn " << T << "\n";
			this->Field[T] = 1;
			this->Power = 9;
			this->Tough = 7;
			this->Flying = true;
			this->Reach = true;
			this->Link = true;
			this->TapLands[T] += this->TapGen;
			this->TapGen = 99;
			this->Flip = 99;
			FlipTurn = T;
			return 1;
		}
		if ((T <= FlipTurn && this->Field[T] != 1) || (T < FlipTurn && this->Field[T] == 1)){ //check if need to unflip a card
			FlipTurn = 0;
			cout << "unflipping " << T << " " << FlipTurn << " Game " << Game << "\n";
	//	SkipGame = Game;
			this->Power = 1;
			this->Tough = 1;
			this->Flying = false;
			this->Reach = false;
			this->Link = false;
			this->Haste = false;
			this->TapGen = 6;
			this->Flip = 5;		
			return 0;
		}
	}
}

//-GAME PHASES-
	//TURN CYCLE
Player Player::Turn(Player enemy){
	//display active player gamestate at start of turn
	if (Report == 1 && Game >= SkipGame){
		cout << "\n" << this->Name << " Start Turn " << T << "\n";
		cout << "Life " << this->Life[T] << " | Hand " << this->Hand[T] << " | Deck " << this->Deck[T] << "\n";
		cout << "Grave " << this->Grave[T] << " | Lands " << this->Lands[T] << " | Creatures " << this->Field[T] << "\n";
		if (enemy.Poison[T] > 0){
			cout << "Poison " << enemy.Poison[T] << "\n";
		}
		if (enemy.Frozen[T] > 0){
			cout << "Frozen " << enemy.Frozen[T] << "\n";
		}
	}
	//reset # of alt decision points encountered
	this->Option = 0;
	//shrink landfall
	if (this->Mammoth > 0){
		this->Power = this->PStart;
		this->Tough = this->TStart;
	}
	//untap except frozen cards
	if (enemy.Frozen[T] > 0){
		if (this->ManLand > 0){
			this->TapLands[T] = enemy.Frozen[T];
		} else {
			this->TapCrtr[T] = enemy.Frozen[T];
			this->TapLands[T] = 0;
		}
		enemy.Frozen[T] = 0;
	} else {
		this->TapLands[T] = 0;
		this->TapCrtr[T] = 0;
	}
	//draw step
	if (T > 1 || this->Name == P2.Name){
		this->Deck[T] -= 1;
		this->Hand[T] += 1;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " draws a card." << "\n";
		}
	}
	//1st main
	if (Report == 1 && Game >= SkipGame){
		cout << "1st main phase" << "\n";
	}
	if (this->ManLand == 1){
		this->MaxAttack = this->Lands[T];
	} else {
		this->MaxAttack = this->Field[T] - this->TapCrtr[T];
	}
	if (this->Hand[T] > 0){ //if any cards in hand
		//play lands
		if (this->IsLand == true || this->Cost > 0){
			this->LandFall(enemy);
		}
		//flip card test
		if (this->Flip > 0 && (this->Field[T] >= this->Flip || (this->Field[T] == this->Flip - 1 && this->Lands[T] >= this->TapGen * 2))){
			this->Haste = true;
		}
		//play cards that can contribute to win this turn
		if (this->Haste == true){
			enemy = this->Cast(enemy);
		}
	}
	//ATTACK
	enemy = this->Declare(enemy); //establish attackers and blockers
	if (this->Attack[T] > 0){
		enemy = this->Combat(enemy); //resolve combat
	} else {
		if (this->Frost == true){ //if frost creature doesn't attack, erase previous kill decisions
			this->Choice[T] = 0;
			this->Decision[T] = 0;
		}
	}
	//win check
	if (enemy.Deck[T] < 1 || enemy.Life[T] < 1 || this->Poison[T] >= 10){
		if (Report == 1 && Game >= SkipGame){
			cout << "\n" << this->Name << " wins Game " << Game << " on turn " << T << "\n";
		}
		this->WinFlag = true;
		if (enemy.Deck[T] < 1){
			enemy.DeckFlag = true;
			//cout << enemy.Name << " decks GAME " << Game << "\n";
		}
		return enemy;
	}
	//2nd main - play cards that cannot contribute to win this turn
	if (Report == 1 && Game >= SkipGame){
		cout << "2nd main phase" << "\n";
	}
	if (this->Haste == false){
		enemy = this->Cast(enemy);
	}
	//end 
	if (Report == 1 && Game >= SkipGame){
		cout << "end step" << "\n";
	}
	enemy = this->End(enemy);
	return enemy;
}

	//PLAY LAND - MAIN PHASE - Play Land
int Player::LandFall(Player enemy){
	//play lands
	if (this->IsLand == true && (this->Grave[T] >= this->Threshold || enemy.Extract > 0) && this->Hostile == 0){
		PlayLand = true;
	}
	//land backed cards
	if (this->Lands[T] < this->Cost || enemy.Extract > 0){
		PlayLand = true;
	}
	//Hostile Desert play land or not
	if (this->Hostile > 0 && (this->Lands[T] < this->ManLand || this->Grave[T] > this->Lands[T]/this->ManLand)){
		PlayLand = true;
	}
	if (this->Flora == 0){
		//cout << T << " turn  lands " << this->Lands[T] << " hand " << this->Hand[T] << "\n";
		if (this->Lands[T] < this->Cost * 2 && this->Hand[T] > 1){
			PlayLand = true;
		}
		//cout << this->Name << " Lands played " << PlayLand << "\n";
		//mammoth exception
		//cout << "mammoth turn " << T << " choice " << this->Choice[T] << " max attack " << this->MaxAttack << " skips " << this->SkipAttack[T] << "\n";
		if (PlayLand == false && this->Mammoth > 0 && this->MaxAttack - this->SkipAttack[T] > 0){
			this->Decision[T] = 1;
			this->Option++;
			if (this->Choice[T] == 0){
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
			if (this->Mammoth > 0){
				this->Decision[T] = 0;
				this->Choice[T] = 0;
			}
		}
	} else { //Florahedron land drop decisions
		if (this->Lands[T] < this->Cost * 2 && this->Lands[T] >= this->Cost){
			this->Option++;
			this->Decision[T] = 1;
			if (this->Choice[T] > 0){
				PlayLand = true;
			}
		}
	}
	if (PlayLand == true){
		PlayLand = false;
		this->Lands[T] ++;
		this->Hand[T] --;
		if (this->PainEBT > 0){ //decide whether to play Emeria Shattered Skycave untapped
			if (this->Lands[T] == this->Cost && this->Life[T] > this->PainEBT){
				this->Life[T] -= this->PainEBT;
			} else {
				this->TapLands[T] ++;
			}
		}
		TapLands[T] += this->LandEBT;
		this->Power += this->Mammoth;
		this->Tough += this->Mammoth;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " plays a land";
			if (this->LandEBT > 0){
				cout << " tapped." << "\n";
			} else {
				cout << "." << "\n";
			}
		}
		//Dwarven Mine
		if (this->Mine > 0 && this->Lands[T] > this->Mine){
			this->Field[T] += this->Token;
			if (Report == 1 && Game >= SkipGame){
				cout << this->Name << " makes a token." << "\n";
			}			
		}
	}
	return 0;
}

	//MAIN PHASE - Play Cards
Player Player::Cast(Player enemy){
	//cast pitch creatures
	if (this->Pitch > 0 && this->IsCreat == true){
		while (this->Hand[T] >= this->Pitch){
			this->Field[T] += 1;
			this->Hand[T] -= this->Pitch;
			if (Report == 1 && Game >= SkipGame){
				cout << this->Name << " casts a creature." << "\n";
			}
		}
	}
		//Piranha Marsh/Sunscorched Desert
	if (this->Piranha > 0){
		enemy.Life[T] -= this->Piranha;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " deals " << this->Piranha << " damage." << "\n";
		}
	}
		//Stalking Stones
	if (this->Stones > 0 && this->Lands[T] >= this->Stones){
		this->Field[T] += 1;
		this->TapCrtr[T] += 1;
		this->Lands[T] -= 1;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " makes a creature." << "\n";
		}
	}
		//sac land token generators
	if (this->SacGen > 0 && this->Lands[T] - this->TapLands[T] >= this->Activate && this->Life[T] > this->Pain && enemy.Extract == false){
			//option to decline pain token
		if (this->Field[T] == 0 || this->Choice[T] == 0){
			if (this->Field[T] > 0 && this->Pain > 0){
				this->Decision[T] = 1;
				//cout << "Binary " << T << " true" << "\n";
			} else {
				this->Decision[T] = 0;
				this->Choice[T] = 0;
			}
			this->Field[T] += this->Token; //make token
			this->TapCrtr[T] += this->CardEBT;
			if (SacAll == false){
				this->Lands[T] -= this->SacGen;
				this->Grave[T] += this->SacGen;
			} else {
				this->Grave[T] += this->Lands[T];
				this->Lands[T] = 0;
			}
			this->Life[T] -= this->Pain;
			if (Report == 1 && Game >= SkipGame){
				cout << this->Name << " makes " << this->Token << " token." << "\n";
			}
		} else {
			this->Decision[T] = 0;
			this->Choice[T] = 0;
		}
	}
	//flip cards
	if (this->FlipCard() == 1){
		this->Parameters(enemy);
	}
	//tap land token generators
	if (this->TapGen > 0){
		while (this->Lands[T] - this->TapLands[T] >= this->TapGen && this->Life[T] > this->Pain){
			this->Field[T] += this->Token;
			this->Life[T] -= this->Pain;
			this->TapLands[T] += this->TapGen;
			if (Report == 1 && Game >= SkipGame){
				cout << this->Name << " makes " << this->Token << " token." << "\n";
			}
			if (this->FlipCard() == 1){
				this->Parameters(enemy);
			}
		}
	}
	//sac mill lands
	if (this->SacMill > 0){
		if ((enemy.Extract == false && (enemy.GraveCard == false || (enemy.Grave[T] >= enemy.Threshold && enemy.Lands[T] > 0))) || enemy.Deck[T] <= this->SacMill * (this->Lands[T] / this->Activate)){
			while (this->Lands[T] - this->TapLands[T] >= this->Activate && this->Life[T] > this->Pain){
				this->Life[T] -= this->Pain;
				this->Lands[T] --;
				this->Grave[T] ++;
				this->TapLands[T] ++;
				enemy.Deck[T] -= this->SacMill;
				enemy.Grave[T] += this->SacMill;
				if (Report == 1 && Game >= SkipGame){
					cout << this->Name << " mills " << enemy.Name << " " << this->SacMill << "\n";
				}
			}
		}
	}
	//Nether Shadow
	if (this->Shadow > 0 && this->Grave[T] > this->Shadow){
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " recurs " << this->Grave[T] - this->Shadow << " creature." << "\n";
		}
		this->Field[T] += this->Grave[T] - this->Shadow;
		this->Grave[T] = this->Shadow;
	}
	//Nether Spirit
	if (this->Spirit > 0 && this->Grave[T] == this->Spirit){
		this->Field[T] ++;
		this->Grave[T] = 0;
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " recurs a creature." << "\n";
		}
	}
	//Chancellor of the Tangle
	if (this->Tangle > 0 && T == 1 && this->StartHand >= this->Tangle){
		this->Field[T] = 1;
		this->Hand[T]--;
	}
	//Turbo Slug
	if (this->Slug > 0 && (this->Hand[T] + enemy.TapCrtr[T] - enemy.Field[T]) * this->Power >= enemy.Life[T]){
		this->Field[T] += this->Hand[T];
		this->Hand[T] = 0;
		cout << "Unleash the slugs!" << "\n";
	}
	//land backed cards
	if (this->Cost > 0){
		//cast cards
		while (this->Lands[T] - this->TapLands[T] >= this->Cost && this->Hand[T] > 0 && IsCreat == true){
			if (this->Token > 0){ //Emeria's Call
				if (enemy.Extract == 0){
					this->Field[T] += this->Token;
					this->Grave[T] ++;
					if (Report == 1 && Game >= SkipGame){
						cout << this->Name << " makes " << this->Token << " tokens." << "\n";
					}
				}
			} else { //creatures
				this->Field[T] += 1;
				this->Life[T] -= this->Pain;
				if (Report == 1 && Game >= SkipGame){
					cout << this->Name << " casts a creature." << "\n";
				}
			}
			this->Hand[T] -= 1;
			this->TapLands[T] += this->Cost;
		}
	}
	//direct damage effects
	this->MaxBurn[T] = 0;
	if (this->TapDam > 0 || (this->SacDam > 0 && this->Grave[T] >= this->Threshold)){
		this->MaxBurn[T] = this->Spike * ((this->Lands[T] - this->TapLands[T]) / (this->TapDam + this->SacDam));
		if (enemy.Extract > 0 && this->TapDam == 0 && this->MaxBurn[T] * 2 < enemy.Life[T]){
			this->MaxBurn[T] = 0;
		}
	}
	if (this->Cost > 0){
		if (this->Hand[T] >= (this->Lands[T] - this->TapLands[T]) / this->Cost){
			this->MaxBurn[T] = this->Spike * ((this->Lands[T] - this->TapLands[T]) / this->Cost);
		} else {
			this->MaxBurn[T] = this->Spike * this->Hand[T];
		}
		if (enemy.Extract > 0 && this->MaxBurn[T] < enemy.Life[T]){
			this->MaxBurn[T] = 0;
		}
	}
	if (this->Pitch > 0){
		this->MaxBurn[T] = this->Spike * (this->Hand[T] / this->Pitch);
		if (enemy.Extract > 0 && this->MaxBurn[T] < enemy.Life[T]){
			this->MaxBurn[T] = 0;
		}
	}
//	cout << this->MaxBurn[T] << enemy.Chancellor << this->Spike;
	if (this->MaxBurn[T] >= enemy.Life[T] || (enemy.Extract > 0 && this->MaxBurn[T] >= enemy.Life[T] - enemy.Pain) || (this->Spike > 0 && this->Burn == 0) || (enemy.Chancellor == true && enemy.Spike > 0) || enemy.Slug == true){
		while (MaxBurn[T] > 0){
			enemy.Life[T] -= this->Burning(enemy);
		}
	}
	//enemy burn active player creatures
	StrikeDead = 0;
	while (enemy.MaxBurn[T] >= this->Tough && this->Field[T] > 0 && BurnLost == true){
		enemy.Burning(enemy);
		if (this->KillAttacker(enemy) == 0){
			StrikeDead++;
			AttackDam = 0;
		}
		if (Report == 1 && Game >=SkipGame && this->ManLand == 0){
			cout << "remaining creatures " << this->Field[T] << "\n";
		}
	}
	//manlands
	if (this->ManLand > 0){
		this->MaxAttack = (this->Lands[T] - this->TapLands[T]) / this->ManLand;
		if (this->Barrens > 0 && this->Lands[T] - this->TapLands[T] == this->ManLand - 1){
			this->PCounters[T][1] += this->Barrens;
			this->TapLands[T] += this->ManLand - 1;
		}
	}
	if (this->Haste == true && this->ManLand == 0){
		if (this->Ichorid > 0){
			this->MaxAttack = this->Grave[T] / this->Ichorid;
		} else {
			this->MaxAttack = this->Field[T] - this->TapCrtr[T];
		}
	}
	if (this->Hostile > 0 && this->MaxAttack > this->Grave[T] / this->Hostile){
		this->MaxAttack = this->Grave[T] / this->Hostile;
	}
	return enemy;
}

	//DECLARE Attackers and Blockers
Player Player::Declare(Player enemy){
	//set Urza's saga p/t
	if (this->Team == true){
		this->Power = this->Field[T];
		this->Tough = this->Power;
	}
	if (enemy.Team == true){
		enemy.Power = enemy.Field[T];
		enemy.Tough = enemy.Power;
	}
	//get # attackers
	this->Attack[T] = this->MaxAttack - this->SkipAttack[T];
	if (this->Attack[T] < 0){
		//cout << "Skip Attack Error game " << Game << "\n";
		this->Attack[T] = 0;
		this->SkipAttack[T] = this->MaxAttack;
	}
	if (this->Unblock == false){ //get enemy available blockers
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
	if (this->Attack[T] > 0 && (this->Attack[T] - (enemy.Blockers[T] / this->MinBlock)) * this->Power < enemy.Life[T]){
		if (this->Trample == false && this->Vigil == false && this->SacEOT == false && this->VarPT == false && this->Link == false && this->Pain < 1){ //ignore relevant combat abilities
			if (enemy.ManLand > 0){ //check enemy damage from next attack w their current resources
				Attacker = (enemy.Lands[T] / enemy.ManLand);
			} else {
				Attacker = enemy.Field[T];
			}
			while(this->Attack[T] > 0 && (Attacker - this->SkipAttack[T]) * enemy.Power >= this->Life[T]){ 
			//if enemy prob has onboard lethal, and you prob don't, attack less if able
				this->SkipAttack[T]++;
				this->Attack[T]--;
			//	SkipGame = Game;
			//	cout << "killing you";
			}
		}
	}
	//skip attacks if will neither change life totals nor kill any blockers
	if (this->Link == false && this->Trample == false && enemy.Chump == false && enemy.Blockers[T] / this->MinBlock >= this->Attack[T]){
		this->SkipAttack[T] = this->MaxAttack;
		this->Attack[T] = 0;
		if (this->Mammoth > 0 || this->Frost == true){
			this->Choice[T] = 0;
			this->Decision[T] = 0; //causing problems?
		}
	}
	//exile graveyard costs to attack
	if (this->Hostile > 0){
		this->Grave[T] -= this->Attack[T] * this->Hostile;
	}
	if (this->Ichorid > 0){
		this->Grave[T] -= this->Attack[T] * this->Ichorid;
		this->Field[T] += this->Attack[T];
	}
	cout << this->Tyrant << "\n";
	enemy.Grave[T] -= this->Attack[T] * this->Tyrant;
	if (enemy.Grave[T] < 0) {
		enemy.Grave[T] = 0;
	}
	//pump Crawling Barrens and Raging Ravine 
	if (this->Attack[T] > 0 && (this->Barrens > 0 || this->Rage > 0)){
		for(Attacker = 1; Attacker <= this->Attack[T]; Attacker++){
			this->PCounters[T][Attacker] += this->Barrens + this->Rage;
		}
		//this->Debug();
		//if exactly 4 excess lands WHAT IF MULTIPLE ATTACKERS W DIF COUNTERS
		if (this->Lands[T] - this->TapLands[T] - this->Attack[T] * this->ManLand == this->ManLand - 1){
			this->PCounters[T][1] += this->Barrens + this->Rage;
		}
		//if 5+ unused lands, pump now or block later
	}
	//pump Blackbloom Rogue
	if (this->RogueThresh > 0){
		if (enemy.Grave[T] >= this->RogueThresh){
			if (Report == 1){
				cout << "GOING ROGUE" << "\n";
			}
			this->Power = this->PStart + this->RogueBonus;
		} else {
			this->Power = this->PStart;
		}
	}
	if (enemy.RogueThresh > 0){
		if (this->Grave[T] >= enemy.RogueThresh){
			enemy.Power = enemy.PStart + enemy.RogueBonus;
		} else {
			enemy.Power = enemy.PStart;
		}
	}
	enemy = this->Parameters(enemy);
	//Determine enemy blocking pattern
	//P2 clear enemy blocking pattern and P1 same, unless this is first turn of reset
	if ((this->Name == P1.Name && this->Lost == false && enemy.AttackReset == false) || this->Name == P2.Name){
		for(Attacker = 0; Attacker <= this->Attack[T]+2; Attacker++){ //clear block pattern
			enemy.Fight[T][Attacker] = 0;
		}
		//default blocks
		if (this->Attack[T] > 0){
			if (enemy.Chump == true){ //if these blockers die in combat, then default all blockers skip
				enemy.Fight[T][this->Attack[T]+1] = enemy.Blockers[T];
				Attacker = 1; //if defender will die if skips all blocks, then deploy blockers if able
				while ((this->Attack[T] - Attacker + 1) * this->Power >= enemy.Life[T] && enemy.Fight[T][this->Attack[T]+1] > 0 && enemy.Link == false){
					enemy.Fight[T][this->Attack[T]+1]--;
					enemy.Fight[T][Attacker] = 1;
					Attacker++;
				}
			} else { //these blockers survive combat
				if (this->Multi == false){ //if each attacker is killed by one blocker, then block even spread
					for (Blocker = 1; Blocker <= enemy.Blockers[T]; Blocker++){
						if (Blocker <= this->Attack[T]){
							enemy.Fight[T][Blocker] = 1;
						}
					}
					Blocker--;
					if (Blocker < this->Attack[T]){
						Blocker = this->Attack[T];
					}
					enemy.Fight[T][this->Attack[T]+1] = Blocker - this->Attack[T]; //excess blockers auto-skip
				} else { //if each attacker requires multiple blockers to kill, then all blockers on 1st attacker
					enemy.Fight[T][1] = enemy.Blockers[T];
					for (Attacker = 1; Attacker <= this->Attack[T]; Attacker++){ //shift blockers if over max necessary block
						if (enemy.Fight[T][Attacker] > this->MaxBlock){
							enemy.Fight[T][Attacker + 1] = enemy.Fight[T][Attacker] - this->MaxBlock;
							enemy.Fight[T][Attacker] = this->MaxBlock;
						}
					}
					//check if defender will die w this block pattern and adjust accordingly if able
					TC = T;
					w = 0;
					enemy = this->BlockSave(enemy);
				}
			}
		}
	}
	//if enemy lost last game, retrieve adjusted block pattern saved in next turn
	if (enemy.Lost == true || this->ChangeMind == true){
		for(int count = this->Attack[T]+1; count>0; count--){
			enemy.Fight[T][count] = enemy.Fight[T+1][count];
			enemy.Fight[T+1][count] = 0;
		}
	}
	//tap attackers and lands activating manlands
	if (this->ManLand > 0){
		this->TapLands[T] += (this->Attack[T] * this->ManLand);
	} else {
		this->TapCrtr[T] += this->Attack[T];
	}
	if (this->Vigil == true){
		this->TapCrtr[T] -= this->Attack[T];
		if (this->ManLand > 0){
			this->TapLands[T] -= this->Attack[T];
		}
	}
	if (enemy.ManLand > 0){
		enemy.TapLands[T] += enemy.Blockers[T] * (enemy.ManLand - 1);
		//pump blocking Barrens
		if (enemy.Barrens > 0){
			for (BlockCheck = 1; BlockCheck <= enemy.Blockers[T]; BlockCheck++){
				enemy.PCounters[T][BlockCheck] += this->Barrens;
			}
		}
	}
	//track largest attack for report screen MOVE TO REPORT FUNC
	this->BigAttack = 0;
	for (int count = 1; count <= T ; count++){
		if (this->Attack[count] > this->BigAttack){
			this->BigAttack = this->Attack[count];
		}
	}
	//attack report
	if (Report == 1 && Game >= SkipGame){ 
		cout << this->MaxAttack << " Max attacks" << "\n";
		cout << this->Attack[T] << " Attackers" << "\n";
		cout << this->SkipAttack[T] << " Skip Attacks" << "\n";
		cout << enemy.Blockers[T] << " Enemy Blockers" << "\n";
		if (this->Attack[T] > 0){
			cout << " S ";
			for (Attacker = 1; Attacker <= this->Attack[T]; Attacker++){
				cout << " A" << Attacker;
			}
			cout << "\n";
			for (Blocker = this->Attack[T] + 1; Blocker > 0; Blocker--){
				cout << " " << enemy.Fight[T][Blocker] << " ";
			}
			cout << "\n";
		}
		cout << "Enemy life was " << enemy.Life[T] << "\n";
	}
	return enemy;
}

	//RESOLVE COMBAT
Player Player::Combat(Player enemy){
	//resolve attacks
	for (Attacker = 1; Attacker <= this->Attack[T]; Attacker++){ //check each attacker outcome
		if (this->Barrens > 0 || this->Rage > 0){
			this->Power = this->PStart + this->PCounters[T][Attacker];
			this->Tough = this->TStart + this->PCounters[T][Attacker];
		}
		AttackDam = this->Power; //damage from attackers this exchange is reset
		BlockDam = 0; //damage from blockers this exchange is reset
		StrikeDead = 0; //blockers killed by striker is reset
		Survivor = false;
		if (enemy.Fight[T][Attacker] >= this->MinBlock){ //legal BLOCKER(s) found
			BlockDam = enemy.Fight[T][Attacker] * enemy.Power;
			//First Strike
				//non-strike attacker vs strike blocker
			if (this->FStrike == false && this->DStrike == false && (enemy.FStrike == true || enemy.DStrike == true)){
				if (BlockDam >= this->Tough){ // if strike blockers deal lethal,
					if (this->KillAttacker(enemy) == 0){ //kill attacker and if attacker doesnt regen, erase attacker damage
						AttackDam = 0;
						BlockDam = 0;
					}
				}
			}
				//strike attacker vs non-strike blocker
			if ((this->FStrike == true || this->DStrike == true) && enemy.FStrike == false && enemy.DStrike == false){
				Blocker = 1;
				while (AttackDam >= enemy.Tough && Blocker <= enemy.Fight[T][Attacker]){ //try to kill blockers
					Blocker++;
					AttackDam -= enemy.Tough; //apply attack damage
					if (enemy.KillAttacker(enemy) == 0){ //dead blockers either regen or erase their damage
						BlockDam -= enemy.Power;
						StrikeDead++;
					}
				}
			}
			//Regular Combat
			if (this->DStrike == true){ //if dstrike attacker in reg combat, deal power again
				AttackDam += this->Power;
			}
			if (enemy.DStrike == true){ //if dstrike blocker(s) in reg combat, double total damage
				BlockDam *= 2;
			}
			if (enemy.Switch == true && enemy.Tough > enemy.Power && (this->Power >= enemy.Tough || this->Dtouch == true)){
				//switcheroo for attacker + blocker
			}
			if (BlockDam >= this->Tough || (enemy.Dtouch == true && BlockDam > 0)){ //if attacker takes lethal,
				if (this->KillAttacker(enemy) == 1){ //attacker dies unless regen
					//if attacker regens, trigger blocker's frost
					if (enemy.Frost == true){
						enemy.Frozen[T]++;
						cout << "freeze - E " << enemy.Frozen[T] << "\n";
					}
				}
				if (this->Frost == true){ //if dead attacker has frost and is multiblocked and can only kill 1 blocker
					if (enemy.Fight[T][Attacker] > 1 && this->Power >= enemy.Tough && this->Power < enemy.Tough * 2){
						this->Option++;
						if (Game >+ SkipGame){
						
						cout << "Option++ game " << Game << " turn " << T << "\n";
						}
						if (this->Option > this->Decision[T]){
							this->Decision[T]++; //create option to freeze multiples instead of kill one
						}
					}
				}
				if (this->Switch == true && this->Power < this->Tough){ //if attacking fumarole takes lethal, switch
					AttackDam = this->Tough;
				}
			} else { //attacker lives, trigger blocker's frost
				Survivor = true;
				if (enemy.Frost == true){
					enemy.Frozen[T]++;
					cout << "freeze - A " << enemy.Frozen[T] << "\n";
				}
			}
			//deal trample
			if (this->Trample == true && AttackDam > enemy.Fight[T][Attacker] * enemy.Tough){
				enemy.Life[T] -= this->Power - (enemy.Fight[T][Attacker] * enemy.Tough);
			}
			//gain block link
			if (enemy.Link == true){
				enemy.Life[T] += BlockDam;
			}
			//gain attack link
			if(this->Link == true){
				this->Life[T] += AttackDam;
			}
			//resolve blockers of this attacker (omitting 1strike deaths)
			for(Blocker = 1; Blocker <= enemy.Fight[T][Attacker] - StrikeDead; Blocker++){ //for each blocker against this attacker
				if (enemy.Fight[T][Blocker] >= this->MinBlock){ // if actually blocking,
					enemy.Grave[T] -= enemy.Hostile; //pay graveyard costs to block
				}
				//check if attacker has killed a blocker
				if ((AttackDam >= enemy.Tough || (this->Dtouch == true && AttackDam > 0)) && (this->Frost == false || this->Choice[T] == 0 || this->Choice[T] < this->Option)){
					//dead blocker absorbs damage
					if (this->Dtouch == false){
						AttackDam -= enemy.Tough;
					} else {
						AttackDam--;
					}
				//	if (Game >= SkipGame){
				//		cout << "good shoot " << Game << " game turn " << T << "\n";
				//	}
					//if blocker regens vs frost, freeze blocker
					if (enemy.KillAttacker(enemy) == 1){
						if (this->Frost == true){
							this->Frozen[T]++;
							cout << "freeze - B " << this->Frozen[T] << "\n";
						}
					}
				//	if (enemy.Switch == true && enemy.Power > enemy.Tough){
				//		BlockDam -= enemy.Power;
				//		BlockDam += enemy.Tough;
				//	}
					Survivor = false;
				} else { //this blocker lives
					if (this->Frost == true && AttackDam == this->Power){ //freeze surviving blockers
						if (this->Power >= enemy.Fight[T][Attacker]){
							this->Frozen[T] += enemy.Fight[T][Attacker];
							cout << "freeze - C " << this->Frozen[T] << " choice " << this->Choice[T] << " of " << this->Option << "\n";
						} else {
							this->Frozen[T] += this->Power;
							cout << "freeze - D - " << this->Frozen[T] << " turn " << T << "\n";
						}
						AttackDam--;
					}
				}
			}
			if (Survivor == true){ //no one died in this block exchange
			//	cout << ActivePlayer << " BOUNCE turn " << T << "\n";
				if (this->Switch == true){ //create trade v bounce option for fumarole
					this->Option++;
				}
			}
		} else { //this attacker is unblocked
			//burn attackers
			OnFire = 0;
			if (enemy.MaxBurn[T] >= this->Tough && StrikeDead < this->Attack[T] && BurnLost == true){
				while (enemy.MaxBurn[T] > 0 && OnFire < this->Tough){
					OnFire += enemy.Burning(enemy);
					if (OnFire >= this->Tough){ //attacker is toast
						if (this->KillAttacker(enemy) == 0){ //if attacker doesn't regen, erase their damage
							StrikeDead++;
							AttackDam = 0;
						}
					}
				}
			}
			if (this->Infect == false){ //deal unblocked damage
				if (this->Switch == true && this->Tough > this->Power && this->Power > enemy.MaxBurn[T]){
					enemy.Life[T] -= this->Tough; //You let this fumarole just wander thru again
				} else { //regular damage
					enemy.Life[T] -= AttackDam;
				}
			} else { //poison counters
				this->Poison[T] += AttackDam;
			}
			if (this->DStrike == true){ //deal doublestrike damage
				enemy.Life[T] -= AttackDam;
			}
			if(this->Link == true){ //gain attacker lifelink
				this->Life[T] += AttackDam;
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
	if (this->Decision[T] > this->Option){
		this->Decision[T] = this->Option;
	}
	return enemy;
}

	//END STEP
Player Player::End(Player enemy){
	//enemy burn deck targets you
	while (enemy.MaxBurn[T] > 0){
		this->Life[T] -= enemy.Burning(enemy);
		if (Report == 1 && Game >= SkipGame){
			cout << this->Name << " life is now " << this->Life[T] << "\n";
		}
	}
	//discard
	if (this->Hand[T] > 7){
		this->Hand[T] = 7;
		if (this->Madness == true){
			this->Field[T] += 1;
			if (Report == 1 && Game >= SkipGame){
				cout << this->Name << " plays a madness creature." << "\n";
			}
		} else {
			this->Grave[T] += 1;
			if (Report == 1 && Game >= SkipGame){
				cout << this->Name << " discards." << "\n";
			}
		}
	}
	if (this->Mammoth > 0){	//shrink landfall
		this->Power = this->PStart;
		this->Tough = this->TStart;
	}
	if (this->SacEOT == true){	//kill sac-eot creatures
		this->Grave[T] += this->Field[T];
		this->Field[T] = 0;
	}
	//enemy checks for Surgical Extraction target
	if (enemy.Extract > 0 && enemy.Hand[T] > 0 && enemy.Life[T] > enemy.Pain && this->Grave[T] >= enemy.Extract){
		this->Hand[T] = 0;
		this->Grave[T] = 0;
		this->Deck[T] = 0;
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
		if (this->PCounters[T][Attacker] > 0){
			for(int count = Attacker - 1; count > 0; count--){
				if(this->PCounters[T][count] == 0){
					this->PCounters[T][count] = this->PCounters[T][Attacker];
					this->PCounters[T][Attacker] = 0;
				}
			}
		}
	}
	//untap urza saga nonhaste
	if (this->Field[T] > 0){
		this->TapCrtr[T] -= this->CardEBT;
	}
	if (Report == 1 && Game >= SkipGame){
		cout << "End " << this->Name << " Turn " << T << "\n";
		cin >> Pause;
	}
	return enemy;
}

	//PASS TURN
void Player::Next(Player enemy){ //record all gamestate variables on to next turn
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
	cout << "MONO MAGIC 2021" << "\n";
	cout << "By Robert Vroman" << "\n";
	cout << "All rights reserved Hasbro and Wizards of the Coast" << "\n" << "\n";
	P1.ClearVars();
	P2.ClearVars();
	//cin >> w;
	cout << "Choose Player 1" << "\n";
	P1.Menu();
	P1.DeckChoice();
	cout << "Choose Player 2" << "\n";
	P2.Menu();
	P2.DeckChoice();
	cout << "\n" << P1.Name << "\n";
	cout << " vs" << "\n";
	cout << P2.Name << "\n" << "\n";
	while (Report < 1 || Report > 5){
		cout << "Choose reporting detail level:" << "\n";
		cout << "1. Play by play" << "\n";
		cout << "2. Attacks only" << "\n";
		cout << "3. Full grid summary" << "\n";
		cout << "4. Game winners" << "\n";
		cout << "5. Conclusion only" << "\n";
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
			P2 = P1.Setup(P2);
			P1 = P2.Setup(P1);
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
		ActivePlayer = P1.Name;
		P2 = P1.Turn(P2);
		if (GameOver == 0){
			if (P1.WinFlag == false){ //if P1 doesn't win, proceed to P2 turn
				ActivePlayer = P2.Name;
				P1 = P2.Turn(P1); //P2 takes its turn
			} else { //P1 wins this turn
				if (Game >= SkipGame && Report < 4){ //end game report
					w = 0;
					P1.Summary(P2);
					w = 1;
					P2.Summary(P1);
					cout << "Enter any lower integer to continue or skip to game #" << "\n";
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
				cout << "Enter any lower integer to continue or skip to game #" << "\n";
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
		P1.Next(P2);
		P2.Next(P1);
		StaleMate(); //Check for stalemate
		if (T < CheckPoint){ //end stalemate
			if (Override == true){
			//	cout << "end override game " << Game << "\n";
			}
			Override = false;
		}
		//check for (un)flip card
		if (P1.Flip > 0 || P2.Flip > 0){
			P1.FlipCard();
			P2.FlipCard();
		}
	}
	cout << "Game Over";
	return 0;
}
