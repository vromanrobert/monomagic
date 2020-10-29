#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

int GameOver; //strict winner found
int Game; //current game#
int Report; //reporting detail level

class Player {
	public:
	string Name; //deck name
	string Tournament[70] = {"Akoum Warrior", "Allosaurus Rider", "Barbarian Ring", "Basking Rootwalla", "Blackbloom Rogue", "Blinkmoth Nexus", "Castle Ardenvale", "Celestial Colonnade", "Cephalid Coliseum", "Chancellor of the Dross", "Chancellor of the Forge", "Chancellor of the Spires", "Chancellor of the Tangle", "Cradle of the Accursed", "Crawling Barrens", "Creeping Tar Pit", "Dread Statuary", "Dryad Arbor", "Dwarven Mine", "Elvish Spirit Guide", "Emerias Call", "Faerie Conclave", "Forbidding Watchtower", "Foundry of the Consuls", "Frostwalk Bastion", "Gargoyle Castle", "Ghitu Encampment", "Hissing Quagmire", "Hostile Desert", "Ichorid", "Inkmoth Nexus", "Ipnu Rivulet", "Kazandu Mammoth", "Keldon Megaliths", "Lavaclaw Reaches", "Lumbering Falls", "Memnite", "Memorial to Glory", "Mishras Factory", "Mobilized District", "Mutavault", "Needle Spires", "Nether Shadow", "Nether Spirit", "Piranha Marsh", "Raging Ravine", "Raths Edge", "Rocket Powered Turbo Slug", "Shambling Vent", "Simian Spirit Guide", "Skyclave Cleric", "Soul Spike", "Spawning Bed", "Spawning Pool", "Spikefield Hazard", "Stalking Stones", "Stirring Wildwood", "Sunscorched Desert", "Surgical Extraction", "Tangled Florahedron", "Tomb of Urami", "Treetop Village", "Umara Wizard", "Urzas Factory", "Vine Dryad", "Wandering Fumarole", "Westvale Abbey", "Zoetic Cavern", "Zof Consumption", "Quit"};	
	int T; //current turn num
	int Lost; //flag if lost the previous game
	int MaxAttack; //maximum attackers this turn
	int StartHand; //starting hand size
	int PStart; //creature default power
	int TStart; //creature default toughness
	int Power; //creature current power
	int Tough; //creature current toughness
	int Pitch; //num cards in hand required to put a card in play
	int Cost; //num untapped lands in play required to play a card from hand
	int Activate; //num untapped cards in play required to activate an ability
	int MaxBlock; //num blockers required to kill enemy attacker
	int TapLands; //num tapped lands in play
	int TapCrtr; //num tapped creatures in play
	int Damage; //life lost this turn from enemy action
	int Casualties; //num cards in play put in graveyard this turn
	int Blocked; //num of own attackers blocked by enemy this turn
	int IsLand; //this card is a land
	int ManLand; //lands that become creatures until eot for this cost
	int Stones; //lands that become creatures permanently for this cost
	int Mill; //how many opponent cards moved from deck to yard when used
	int SacMill; //how many opponent cards moved from deck to yard when sacked
	int Token; //tokens created per activation
	int Pain; //life loss from using abilities
	int SacGen; //num lands sacrificed to create token
	int TapGen; //num untapped lands needed to create token
	int SacDam; //land that sacs to deal damage
	int TapDam; //land that taps to deal damage
	int Mine; //num lands in play required to trigger token
	int Flip; //num creatures in play required to activate flip ability
	int Barrens; //num +1/+1 counters added per activation
	int Flying; //creature has flying while attacking
	int Reach; //creature can block flyers
	int Unblock; //creature is unblockable
	int Trample; //creature has trample
	int Link; //creature has lifelink
	int Infect; //creature has infect
	int Frost; //creatures damaged by this creature don't untap the next turn
	int FStrike; //creature has first strike
	int DStrike; //creature has double strike
	int Hostile; //creature must exile cards from yard to combat
	int Lava; //this creature has X:+1/+0
	int Shadow; //how many cards in yard to return to play
	int Spirit; //creature that returns to play if only card in yard
	int Mammoth; //creature that is bigger when attacking
	int Spike; //card that deals damage from hand
	int LandEBT; //land that enters play tapped
	int PainEBT; //land that enters play tapped unless life paid
	int CardEBT; //non-land card that enters play tapped
	int Slug; //creature that once played, loses the game the next turn
	int Haste; //creature that can attack same turn is played
	int Menace; //creature that can only be multi-blocked
	int RogueThresh; //creature that gets power bonus if opponent has this many cards in yard
	int RogueBonus; //size of power bonus
	int Threshold; //how many cards in yard required to use ability
	int BackLand; //non-land card that can also be played as a land
	int Madness; //creature that enters play when discarded
	int Dtouch; //creature that kills in combat if deals any damage
	int Vigil; //creature that does not tap to attack
	int Rage; //creature that gets +1/+1 counter when attacks
	int Hex; //creature that cannot be targeted
	int Flash; //card that can be played at start of game
	int Extract; //card that eliminates enemy hand, yard, and library if they have card in yard
	int Ichorid; //creature that returns to play in upkeep by exiling other cards in yard
	int SacEOT; //creature that is sacrificed at eot
	int Piranha; //land that deals damage when enters play
	int Regen; //cost to regenerate
	int Hazard; //enemies killed by this are exiled
	int Switch; //creature that can switch p/t
	int Factory; //creature w X:+1/+1
	int Chancellor; //can only play spells 1st upkeep
	int Tangle; //can only play 1 creature per game, on T1 if start hand is 7
	int Flora; //creature that taps for mana
	int Morph; //creature that can flip into a land for this cost
	int Life [62], MyLife [62], PostLife [62]; //life at start of own turn, start of enemy turn, end of enemy turn
	int Field [62], MyField [62], PostField [62]; //num creatures in play at start of own turn, start of enemy turn, end of enemy turn
	int Attack [62], Blockers [62]; //num attackers this turn, num blockers available after attack
	int Grave [62], MyGrave [62], PostGrave [62]; //num cards in graveyard at start of own turn, start of enemy turn, end of enemy turn
	int MultiBlock [62], SkipBlock [62]; //num of multi-blocks, num available blockers not blocking
	int Lands [62], Hand [62], Deck [62]; //lands in play, current hand size, cards in library
	int AltVar[62]; //poison counters, frozen cards, etc
	int AltDec[62]; //non-combat decisions
	int ClearVars();
	int DeckChoice();
	int Parameters(Player enemy);
	int Setup(Player enemy);
	int Turn(Player enemy);
	int Cast(Player enemy);
	int Combat(Player enemy);
	int End(Player enemy);
	int Win(Player enemy);
	int Next(Player enemy);
} P1, P2;

int Player::ClearVars(){
	for(int count=0; count<63; count++){
		Life[count] = 20;
		MyLife[count] = 20;
		PostLife[count] = 20;
		Field[count] = 0;
		MyField[count] = 0;
		PostField[count] = 0;
		Grave[count] = 0;
		MyGrave[count] = 0;
		PostGrave[count] = 0;
		MultiBlock[count] = 0;
		SkipBlock [count] = 0;
		Lands[count] = 0;
		Hand[count] = 0;
		Deck[count] = 0;
		AltVar[count] = 0;
		AltDec[count] = 0;
	}
	T = 0;
	Lost = 0;
	MaxAttack = 0;
	StartHand = 0;
	PStart = 1;
	TStart = 1;
	Power = 1;
	Tough = 1;
	Pitch = 0;
	Cost = 0;
	Activate = 0;
	MaxBlock = 0;
	Damage = 0;
	Casualties = 0;
	Blocked = 0;
	Token = 0;
	Pain = 0;
	SacGen = 0;
	Mine = 0;
	Flip = 0;
	Barrens = 0;
}

int Player::DeckChoice(){
	for(int i = 0; i <70; i++){
		cout << i+1 << " " << Tournament[i] << endl;
	}	
	int DeckSelect;
	cin >> DeckSelect;
	DeckSelect--;
	Name = Tournament[DeckSelect];
	if (Name == "Akoum Warrior"){
		StartHand = 7;
		PStart = 4;
		TStart = 5;
		Cost = 6;
		BackLand = 1;
		LandEBT = 1;
		Trample = 1;
	}
	if (Name == "Allosaurus Rider"){
		StartHand = 7;
		Pitch = 3;
	}
	if (Name == "Barbarian Ring"){
		StartHand = 7;
		IsLand = 1;
		SacDam = 2;
		Activate = 2;
		Threshold = 7;
	}
	if (Name == "Basking Rootwalla"){
		StartHand = 7;
		Madness = 1;
	}
	if (Name == "Blackbloom Rogue"){
		StartHand = 7;
		PStart = 2;
		TStart = 3;
		Cost = 3;
		BackLand = 1;
		LandEBT = 1;
		Menace = 2;
		RogueThresh = 8;
		RogueBonus = 3;
	}
	if (Name == "Blinkmoth Nexus"){
		IsLand = 1;
		ManLand = 2;
		Flying = 1;
		Reach = 1;
		Factory = 2;
	}
	if (Name == "Castle Ardenvale"){
		IsLand = 1;
		LandEBT = 1;
		Token = 1;
		TapGen = 4;
	}
	if (Name == "Chancellor of the Dross"){
		StartHand = 7;
		Chancellor = 1;
		Spike = 3;
		Pain = -3;
	}
	if (Name == "Chancellor of the Forge"){
		StartHand = 7;
		Chancellor = 1;
		Token = 1;
		Haste = 1;
	}
	if (Name == "Chancellor of the Spires"){
		StartHand = 7;
		Chancellor = 1;
		Mill = 7;
	}
	if (Name == "Chancellor of the Tangle"){
		StartHand = 7;
		PStart = 6;
		TStart = 7;
		Vigil = 1;
		Reach = 1;
		Tangle = 7;
	}
	if (Name == "Celestial Colonnade"){
		IsLand = 1;
		ManLand = 6;
		LandEBT = 1;
		PStart = 4;
		TStart = 4;
		Flying = 1;
		Reach = 1;
		Vigil = 1;
	}
	if (Name == "Cephalid Coliseum"){
		StartHand = 7;
		IsLand = 1;
		Activate = 2;
		Pain = 1;
		SacMill = 3;
		Threshold = 7;
	}
	if (Name == "Cradle of the Accursed"){
		IsLand = 1;
		SacGen = 1;
		Activate = 4;
		Token = 1;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Crawling Barrens"){
		IsLand = 1;
		ManLand = 5;
		PStart = 0;
		TStart = 0;
		Barrens = 2;
	}
	if (Name == "Creeping Tar Pit"){
		IsLand = 1;
		ManLand = 4;
		LandEBT = 1;
		PStart = 3;
		TStart = 2;
		Unblock = 1;
	}
	if (Name == "Dread Statuary"){
		IsLand = 1;
		ManLand = 5;
		PStart = 4;
		TStart = 2;
	}
	if (Name == "Dryad Arbor"){
		IsLand = 1;
		ManLand = 1;
	}
	if (Name == "Dwarven Mine"){
		IsLand = 1;
		Token = 1;
		Mine = 3;
	}
	if (Name == "Elvish Spirit Guide"){
		Pitch = 4;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Emerias Call"){
		StartHand = 7;
		Cost = 7;
		Token = 2;
		PStart = 4;
		TStart = 4;
		Flying = 1;
		Reach = 1;
		BackLand = 1;
		PainEBT = 3;
	}
	if (Name == "Faerie Conclave"){
		IsLand = 1;
		ManLand = 3;
		LandEBT = 1;
		PStart = 2;
		Flying = 1;
		Reach = 1;
	}
	if (Name == "Forbidding Watchtower"){
		IsLand = 1;
		ManLand = 3;
		LandEBT = 1;
		TStart = 5;
	}
	if (Name == "Foundry of the Consuls"){
		IsLand = 1;
		SacGen = 1;
		Activate = 6;
		Token = 2;
		Flying = 1;
		Reach = 1;
	}
	if (Name == "Frostwalk Bastion"){
		IsLand = 1;
		ManLand = 3;
		PStart = 2;
		TStart = 3;
		Frost = 1;
	}
	if (Name == "Gargoyle Castle"){
		IsLand = 1;
		SacGen = 1;
		Activate = 6;
		Token = 1;
		PStart = 3;
		TStart = 4;
		Flying = 1;
		Reach = 1;
	}
	if (Name == "Ghitu Encampment"){
		IsLand = 1;
		ManLand = 3;
		LandEBT = 1;
		PStart = 2;
		FStrike = 1;
	}
	if (Name == "Hissing Quagmire"){
		IsLand = 1;
		ManLand = 4;
		LandEBT = 1;
		PStart = 2;
		TStart = 2;
		Dtouch = 1;
	}
	if (Name == "Hostile Desert"){
		StartHand = 7;
		IsLand = 1;
		ManLand = 3;
		PStart = 3;
		TStart = 4;
		Hostile = 1;
		Threshold = 1;
	}
	if (Name == "Ichorid"){
		StartHand = 7;
		PStart = 3;
		Haste = 1;
		Ichorid = 2;
	}
	if (Name == "Inkmoth Nexus"){
		IsLand = 1;
		ManLand = 2;
		Flying = 1;
		Reach = 1;
		Infect = 1;
	}
	if (Name == "Ipnu Rivulet"){
		IsLand = 1;
		SacMill = 4;
		Pain = 1;
		Activate = 3;
	}
	if (Name == "Kazandu Mammoth"){
		StartHand = 7;
		Cost = 3;
		PStart = 3;
		TStart = 3;
		BackLand = 1;
		LandEBT = 1;
		Mammoth = 2;
	}
	if (Name == "Keldon Megaliths"){
		IsLand = 1;
		LandEBT = 1;
		Activate = 3;
		TapDam = 1;
	}
	if (Name == "Lavaclaw Reaches"){
		IsLand = 1;
		ManLand = 4;
		LandEBT = 1;
		PStart = 2;
		TStart = 2;
		Lava = 1;
	}
	if (Name == "Lumbering Falls"){
		IsLand = 1;
		ManLand = 5;
		LandEBT = 1;
		PStart = 3;
		TStart = 3;
		Hex = 1;
	}
	if (Name == "Memnite"){
		StartHand = 7;
		Pitch = 1;
	}
	if (Name == "Memorial to Glory"){
		IsLand = 1;
		LandEBT = 1;
		SacGen = 1;
		Activate = 5;
		Token = 2;
	}
	if (Name == "Mishras Factory"){
		IsLand = 1;
		ManLand = 2;
		PStart = 2;
		TStart = 2;
		Factory = 1;
	}
	if (Name == "Mobilized District"){
		IsLand = 1;
		ManLand = 5;
		PStart = 3;
		TStart = 3;
		Vigil = 1;
	}
	if (Name == "Mutavault"){
		IsLand = 1;
		ManLand = 2;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Needle Spires"){
		IsLand = 1;
		ManLand = 5;
		LandEBT = 1;
		PStart = 2;
		DStrike = 1;
	}
	if (Name == "Nether Shadow"){
		StartHand = 7;
		Haste = 1;
		Shadow = 3;
	}
	if (Name == "Nether Spirit"){
		StartHand = 7;
		PStart = 2;
		TStart = 2;
		Spirit = 1;
	}
	if (Name == "Piranha Marsh"){
		IsLand = 1;
		Piranha = 1;
	}
	if (Name == "Raging Ravine"){
		IsLand = 1;
		ManLand = 5;
		LandEBT = 1;
		PStart = 3;
		TStart = 3;
		Rage = 1;
	}
	if (Name == "Raths Edge"){
		IsLand = 1;
		Activate = 5;
		SacDam = 1;
	}
	if (Name == "Rocket Powered Turbo Slug"){
		StartHand = 7;
		Haste = 1;
		PStart = 3;
		Slug = 1;
	}
	if (Name == "Shambling Vent"){
		IsLand = 1;
		ManLand = 4;
		LandEBT = 1;
		PStart = 2;
		TStart = 3;
		Link = 1;
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
		BackLand = 1;
		LandEBT = 1;
	}
	if (Name == "Soul Spike"){
		StartHand = 7;
		Flash = 1;
		Pitch = 3;
		Spike = 4;
		Pain = -4;
	}
	if (Name == "Spawning Bed"){
		IsLand = 1;
		SacGen = 1;
		Activate = 7;
		Token = 3;
	}
	if (Name == "Spawning Pool"){
		IsLand = 1;
		ManLand = 3;
		LandEBT = 1;
		Regen = 1;
	}
	if (Name == "Spikefield Hazard"){
		StartHand = 7;
		Cost = 1;
		Spike = 1;
		Hazard = 1;
		BackLand = 1;
		LandEBT = 1;
	}
	if (Name == "Stalking Stones"){
		IsLand = 1;
		Stones = 6;
		PStart = 3;
		TStart = 3;
	}
	if (Name == "Stirring Wildwood"){
		IsLand = 1;
		ManLand = 4;
		LandEBT = 1;
		PStart = 3;
		TStart = 4;
		Reach = 1;
	}
	if (Name == "Sunscorched Desert"){
		IsLand = 1;
		Piranha = 1;
	}
	if (Name == "Surgical Extraction"){
		Pain = 2;
		Extract = 1;
	}
	if (Name == "Tangled Florahedron"){
		StartHand = 7;
		Cost = 2;
		Flora = 1;
		BackLand = 1;
		LandEBT = 1;
	}
	if (Name == "Tomb of Urami"){
		IsLand = 1;
		SacGen = 5;
		Activate = 5;
		Token = 1;
		PStart = 5;
		TStart = 5;
		Flying = 1;
		Reach = 1;
		Pain = 4;
	}
	if (Name == "Treetop Village"){
		IsLand = 1;
		ManLand = 3;
		LandEBT = 1;
		PStart = 3;
		TStart = 3;
		Trample = 1;
	}
	if (Name == "Umara Wizard"){
		StartHand = 7;
		Cost = 5;
		PStart = 4;
		TStart = 3;
		Flying = 1;
		BackLand = 1;
		LandEBT = 1;
	}
	if (Name == "Urzas Factory"){
		IsLand = 1;
		TapGen = 8;
		Token = 1;
		PStart = 2;
		TStart = 2;
	}
	if (Name == "Vine Dryad"){
		StartHand = 7;
		Pitch = 2;
		Flash = 1;
		TStart = 3;
	}
	if (Name == "Wandering Fumarole"){
		IsLand = 1;
		ManLand = 5;
		LandEBT = 1;
		TStart = 4;
		Switch = 1;
	}
	if (Name == "Westvale Abbey"){
		IsLand = 1;
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
		BackLand = 1;
	}
	if (Name == "Zof Consumption"){
		StartHand = 7;
		Cost = 6;
		Spike = 4;
		Pain = -4;
		BackLand = 1;
		LandEBT = 1;
	}
}

int Player::Parameters(Player enemy){
	this->Power = this->PStart;
	this->Tough = this->TStart;
	//convert flying to unblockable
	if (this->Flying == 1 && enemy.Reach == 0){
		this->Unblock = 1;
	}
	//give haste to all manlands except Dryad Arbor
	if (this->ManLand > 1){
		this->Haste = 1;
	}
	//remove irrelevant trample
	if (this->Trample > 0 && enemy.Tough >= this->Power){
		this->Trample = 0;
	}
}

int Player::Setup(Player enemy){
	this->Hand[0] = this->StartHand;
	enemy.Hand[0] = enemy.StartHand;
	this->Deck[0] = 60 - this->StartHand;
	enemy.Deck[0] = 60 - enemy.StartHand;
	if (this->Chancellor > 0){
		//dross
		//forge
		//spires
	}
	if (enemy.Chancellor > 0){
		//dross
		//forge
		//spires
	}
	if (this->Flash > 0){
		P1.Cast(P2);
	}
	if (enemy.Flash > 0){
		P2.Cast(P1);
	}
}

int Player::Turn(Player enemy){
	//get gamestate variables from end of enemy turn
	this->Deck[this->T+1] = this->Deck[this->T] - 1;
	this->Hand[this->T+1] = this->Hand[this->T] + 1;
	this->Life[this->T+1] = this->PostLife[this->T];
	this->Field[this->T+1] = this->PostField[this->T];
	this->Grave[this->T+1] = this->PostGrave[this->T];
	this->Lands[this->T+1] = this->Lands[this->T];
	this->T += 1; //increment turn and fill current variables
	this->MyField[this->T] = this->Field[this->T];
	this->MyGrave[this->T] = this->Grave[this->T];
	this->MyLife[this->T] = this->Life[this->T];
	this->TapLands = 0;
	this->TapCrtr = 0;
	if (Report < 3){
		cout << this->Name << " Turn " << this->T << endl;
	}
	if (Report == 1){
		cout << "Life " << this->Life[this->T] << " | Hand " << this->Hand[this->T] << " | Deck " << this->Deck[this->T] << endl;
		cout << "Grave " << this->Grave[this->T] << " | Lands " << this->Lands[this->T] << " | Creatures " << this->Field[this->T] << endl << endl;
		cin >> StartHand;
	}
	//1st main
	this->MaxAttack = this->MyField[this->T] - this->TapCrtr;
	if (this->Haste > 0 && this->Hand[this->T] > 0){
		this->Cast(enemy);
	}
	//combat
	if (this->MaxAttack > 0){
		this->Combat(enemy);
	}
	//win check
	if (enemy.Deck[enemy.T] < 1 || enemy.PostLife[enemy.T] < 1){
		GameOver = 1;
		cout << this->Name << " wins!" <<endl;
	}
	//2nd main
	if (this->Haste == 0 && this->Hand[this->T] > 0){
		this->Cast(enemy);
	}
	//end step
	cout << "enemy life "<< enemy.PostLife[enemy.T] << endl;
	this->End(enemy);
}

//play cards
int Player::Cast(Player enemy){
	//cast pitch creatures
	if (this->Pitch > 0){
		while (this->Hand[this->T] >= this->Pitch){
			this->MyField[this->T] += 1;
			this->Hand[this->T] -= this->Pitch;
			if (Report == 1){
				cout << this->Name << " casts a creature." << endl;
			}
		}
	}
	//play lands
	if (this->IsLand > 0 && this->MyGrave[this->T] >= this->Threshold){
		this->Lands[this->T] += 1;
		this->Hand[this->T] -= 1;
		TapLands += this->LandEBT;
		//Piranha Marsh/Sunscorched Desert
		if (this->Piranha > 0){
			cout << "chomp " << enemy.PostLife[enemy.T] << endl;
			enemy.PostLife[enemy.T] -= this->Piranha;
			cout << "chomp " << enemy.PostLife[enemy.T] << endl;
		}
		//Dwarven Mine
		if (this->Mine > 0 && this->Lands[this->T] > this->Mine){
			this->MyField[this->T] += this->Token;
			if (Report == 1){
				cout << this->Name << " makes a token." << endl;
			}			
		}
		//Stalking Stones
		if (this->Stones > 0 && this->Lands[this->T] >= this->Stones){
			this->MyField[this->T] += 1;
			this->TapCrtr += 1;
			this->Lands[this->T] -= 1;
			if (Report == 1){
				cout << this->Name << " makes a creature." << endl;
			}
		}
		//sac land token generators
		if (this->SacGen > 0 && this->Lands[this->T] - this->TapLands >= this->Activate && this->MyLife[this->T] > this->Pain){
			this->MyField[this->T] += this->Token;
			this->Lands[this->T] -= this->SacGen;
			this->MyGrave[this->T] += this->SacGen;
			this->MyLife[this->T] -= this->Pain;
			if (Report == 1){
				cout << this->Name << " makes " << this->Token << " creature." << endl;
			}	
		}
		//tap land token generators
		if (this->TapGen > 0){
			while (this->Lands[this->T] - this->TapLands >= this->TapGen && this->MyLife[this->T] > this->Pain){
				this->MyField[this->T] += this->Token;
				this->MyLife[this->T] -= this->Pain;
				this->TapLands += this->TapGen;
				if (Report == 1){
					cout << this->Name << " makes " << this->Token << " creature." << endl;
				}				
			}
		}
		//sac mill lands
		if (this->SacMill > 0 && this->Lands[this->T] >= this->Activate && this->MyLife[this->T] > this->Pain){
			this->MyLife[this->T] -= this->Pain;
			this->Lands[this->T] -= 1;
			this->MyGrave[this->T] += 1;
			//mill opponent
		}
		//manlands
		if (this->ManLand > 0){
			this->MaxAttack = (this->Lands[this->T] - this->TapLands) / this->ManLand;
		}
		//Nether Shadow
		if (this->Shadow > 0 && this->MyGrave[this->T] > this->Shadow){
			if (Report == 1){
				cout << this->Name << " recurs " << this->MyGrave[this->T] - this->Shadow << " creature." << endl;
			}
			this->MyField[this->T] += this->MyGrave[this->T] - this->Shadow;
			this->MyGrave[this->T] = this->Shadow;
		}
		//Nether Spirit
		if (this->Spirit > 0 && this->MyGrave[this->T] == this->Spirit){
			this->MyField[this->T] += 1;
			this->MyGrave[this->T] = 0;
			if (Report == 1){
				cout << this->Name << " recurs a creature." << endl;
			}
		}
		//Ichorid
		if (this->Ichorid > 0){
			this->MaxAttack = this->MyGrave[this->T] / this->Ichorid;
		}
		//Chancellor of the Tangle
		if (this->Tangle > 0 && this->T == 1 && this->Hand[this->T] >= this->Tangle){
			this->MyField[this->T] += 1;
			this->Hand[this->T] -= 1;
		}
		//Turbo Slug
		//land backed cards
			//creatures
			//Emeria's Call
			//Zof Consumption
			//Spikefield Hazard
		//Soul Spike
		//sac damage lands
		//tap damage lands
	}
	if (this->Haste > 0 && this->ManLand == 0 && this->Ichorid == 0){
		this->MaxAttack = this->MyField[this->T] - this->TapCrtr;
	}
}

//attack
int Player::Combat(Player enemy){
	cout << "FIGHT" << endl;
}

//clean up
int Player::End(Player enemy){
	cout << "END TURN" << endl;
	//discard
	if (this->Hand[this->T] > 7){
		this->Hand[this->T] = 7;
		if (this->Madness > 0){
			this->MyField[this->T] += 1;
			if (Report == 1){
				cout << this->Name << " plays a madness creature." << endl;
			}
		} else {
			this->MyGrave[this->T] += 1;
			if (Report == 1){
				cout << this->Name << " discards." << endl;
			}
		}
	}
	//enemy checks for Surgical Extraction target
	if (enemy.Extract > 0 && enemy.Hand[enemy.T] > 0 && enemy.PostLife[enemy.T] > enemy.Pain && this->MyGrave[this->T] > 0){
		this->Hand[this->T] = 0;
		this->MyGrave[this->T] = 0;
		this->Deck[this->T] = 0;
		enemy.PostLife[enemy.T] -= enemy.Pain;
		enemy.PostGrave[enemy.T] += 1;
		enemy.Hand[enemy.T] -= 1;
	}
	//pass turn gamestate variables
	this->PostField[this->T] = this->MyField[this->T];
	this->PostGrave[this->T] = this->MyGrave[this->T];
	this->PostLife[this->T] = this->MyLife[this->T];
}

int Player::Win(Player enemy){
	//check for alt plays on previous turns
}

int Player::Next(Player enemy){
	//reset game state to previous turn
}

int main(){
	GameOver = 0;
	Game = 1;
	cout << "MONO MAGIC 2020" << endl;
	cout << "By Robert Vroman" << endl;
	cout << "All rights reserved Hasbro and Wizards of the Coast" << endl << endl;
	P1.ClearVars();
	P2.ClearVars();
	cout << "Choose Player 1" << endl;
	P1.DeckChoice();
	cout << "Choose Player 2" << endl;
	P2.DeckChoice();
	cout << P1.Name << endl;
	cout << "vs" << endl;
	cout << P2.Name << endl << endl;
	while (Report < 1 || Report > 5){
		cout << "Choose reporting detail level:" << endl;
		cout << "1. Play by play" << endl;
		cout << "2. Attacks" << endl;
		cout << "3. Grid summary" << endl;
		cout << "4. Game winners" << endl;
		cout << "5. Conclusion only" << endl;
		cin >> Report;
	}
	P1.Parameters(P2);
	P2.Parameters(P1);
	while (GameOver == 0){
		if (P1.T == 0){
			P1.Setup(P2);
			P2.Setup(P1);
		}
		P1.Turn(P2);
		if (GameOver == 0){
			P2.Turn(P1);
		}
	}
	return 0;
}
