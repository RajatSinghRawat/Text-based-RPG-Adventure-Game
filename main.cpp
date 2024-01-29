#include <iostream>
using namespace std;

class ToolKit
{
  private:
  //member variable
  int randomNumber;

  public:
  //constructor
  ToolKit()
  {
    randomNumber = 0;
    srand(time(0));
  }

  //member function
  int randomNumberGenerator(int min_Value, int max_Value)
  {
    // Generating random number between given 2 values
    randomNumber = ((rand() % (max_Value - min_Value + 1)) + min_Value);
    return randomNumber;
  }

  //destructor
  ~ToolKit()
  {} 
};

//Base Class for all characters
class Character
{
  private:
  //member variable
  int health, meleeDamage, defence, actualReceivedDamage, damage, damageDefended;
  string characterName;

  public:
  //constructor
  Character(int health, int meleeDamage, int defence, string characterName)
  {
    this->health = health;
    this->meleeDamage = meleeDamage;
    this->defence = defence;
    this->characterName = characterName;
  }

  //abstrat functions
  virtual void Attack(Character *attacker, Character *defender, int level) = 0;

  virtual void TakeDamage(Character *damageGiver, Character *damageReceiver, int currentLevel, int totalDamageReceived) = 0;

  //member function
  void showDamageStats(int damageGiven, int damageDefended, int damageReceived, Character *attacker, Character *defender)
  {
    cout << "Damage Given by " << attacker->GetCharacterName() <<": " << damageGiven << endl;
    cout << "Damage Defended by " << defender->GetCharacterName() <<": " << damageDefended << endl;
    cout << "Total Damage Received by " << defender->GetCharacterName() <<": " << damageReceived << endl;
    cout << "Remaining Health of " << defender->GetCharacterName() << " after receiving damage: " << (isAlive()?
      GetHealth():
      0) << endl << endl;
  }

  //getters
  bool isAlive()
  {
    if(health > 0)
    {
      return true;
    }
      return false;
  }
  
  int GetHealth()
  {
    return health;
  }

  int GetMeleeDamage()
  {
    return meleeDamage;
  }

  string GetCharacterName()
  {
    return characterName;
  }

  int getDefence()
  {
    return defence;
  }

  int GetActualReceivedDamage()
  {
    return actualReceivedDamage;
  }

  int GetDamage()
  {
    return damage;
  }

  int GetDamageDefended()
  {
    return damageDefended;
  }

  //setters
  void SetHealth(int _health)
  {
    health =  _health;
  }

  void SetMeleeDamage(int _meleeDamage)
  {
    meleeDamage = _meleeDamage;
  }

  void SetDefence(int _defence)
  {
    defence = _defence;
  }

  void SetActualReceivedDamage(int _actualReceivedDamage)
  {
    actualReceivedDamage = _actualReceivedDamage;
  }

  void SetDamage(int _damage)
  {
    damage = _damage;
  }

  void SetDamageDefended(int _damageDefended)
  {
    damageDefended = _damageDefended;
  }

  //Destructor
  virtual ~Character()
  {
    if(isAlive())
    {
        cout << "!!!!!----------Game Over----------!!!!!" << endl << endl;
    }
    else
    {
      SetHealth(0);  
    }   
  }
};


class SpecialAbility : public ToolKit
{
  private:
  //probabilities of special abilities of Boss Enemy
  int GroundSlashProbability = 10;
  int SpeedDashProbability = 10;
  int HealthRegenerationProbability = 10;

  //probabilities of special abilities of Player
  int CriticalHitProbability = 10;
  int LifeStealProbability = 10;
  int RangedAttackProbability = 10;
  int BlockerProbability = 10;

  public:
  
  //Special Abilities of Boss Enemy
  int GroundSlash(string bossEnemyName, int maxHealth)
  {
    if(GroundSlashProbability >= randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! " << bossEnemyName << " used its special ability of Ground Slash." << endl;
      return ((maxHealth*25)/100);
    }
    return 0;
  }

  int SpeedDash(string bossEnemyName, int Health)
  {
    if(SpeedDashProbability >= randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! " << bossEnemyName << " used its special ability of Speed Dash." << endl;
      return ((Health*40)/100);
    }
    return 0;
  }

  int HealthRegeneration(string bossEnemyName, int health, int maxHealth)
  {
    if(HealthRegenerationProbability >= randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! " << bossEnemyName << " used its special ability of Health Regeneration." << endl;
      
      if(health == maxHealth)
      {
        cout << "Oooohhh.... But " <<  bossEnemyName << "'s" << " health is already full.";
        cout << "No requirement of healing..!!" << endl;
        cout << bossEnemyName << "'s health: " << bossEnemyName << endl << endl;
      }
      else
      {
        int temporaryHeal;
        temporaryHeal = ((maxHealth - health)*50)/100;
        cout << bossEnemyName <<" is healed by " << temporaryHeal << "." << endl;

        if((health + temporaryHeal) > maxHealth)
        {
          cout << bossEnemyName <<"'s Health after healing: " << maxHealth << endl << endl;
          return maxHealth;
        }
        else
        {
          cout << bossEnemyName <<"'s Health after healing: " << (health + temporaryHeal) << endl << endl;
          return (health + temporaryHeal);
        }
      }
    }
    return health;
  }

  //Special Abilities of Player
  int CriticalHit(string playerName, int meleeDamage)
  {
    if(CriticalHitProbability >= randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! " << playerName << " used its special ability of Critical Hit." << endl;
      return (meleeDamage * 2);
    }
    return 0;
  }

  int LifeSteal(string playerName, int maxHealth)
  {
    if(LifeStealProbability >= randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! " << playerName << " used its special ability of Life Steal." << endl;
      return (maxHealth*20/100);
    }
    return 0;
  }

  bool RangedAttack(string playerName)
  {
    if(RangedAttackProbability >= randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! " << playerName << " used its special ability of Ranged Attack. " << playerName << "won't take damage for the next attack of the enemy." << endl;
      return true;
    }
    return false;
  }

  int BlockAttack(string playerName, int actualReceivedDamage)
  {
    if(BlockerProbability >= randomNumberGenerator(0, 100))
    { 
      cout << endl;
      cout << "Woooooh! " << playerName << " used its special ability to fully block the attack." << endl;
      return 0;
    }
    return actualReceivedDamage;
  }
};


//Player class inherits from Character class and SpecialAbility class
class Player : public Character, public SpecialAbility
{
  private:
  //member variables
  int maxHealth, heal;
  bool rangedDamage;
  
  //specific level value is assigned to each Special Ability  
  enum SpecialAbilities {Critical_Hit = 3, Blocker = 4, Life_Steal = 5, Ranged_Attack = 6};

  public:
  //constructor
  Player(int health, int meleeDamage, int defence, int heal, bool rangedDamage, string characterName) : Character(health, meleeDamage, defence, characterName)
{
  this->maxHealth = health;
  this->heal = heal;
  this->rangedDamage = rangedDamage;

  cout << "Our Hero has arrived to release its village from Monster Murloc." << endl;
}

  //getters
  int getMaxHealth()
  {
    return maxHealth;
  }

  int GetHeal()
  {
    return heal;
  }

  bool GetRangedDamage()
  {
    return rangedDamage;
  }

  //setters
  void setMaxHealth(int _maxHealth)
  {
    maxHealth = _maxHealth;
  }

  void setHeal(int _heal)
  {
    heal = _heal;
  }

  void SetRangedDamage(bool _rangedDamage)
  {
    rangedDamage = _rangedDamage;
  }

  //member functions
  void Attack(Character *attacker, Character *defender, int currentLevel)
  { 
    cout << "-- " << attacker->GetCharacterName() << " is attacking " << defender->GetCharacterName() << " --" << endl << endl;
    
    SetDamage(attacker->GetMeleeDamage());

    for(int i = Critical_Hit; i <= currentLevel; i++)
    {
      if(i == Blocker)
      {
        continue;
      }
      else
      {
        UseSpecialAbility(i);
      }
    }
    defender->TakeDamage( attacker, defender, currentLevel, GetDamage());

  }

  void UseSpecialAbility(int assignedLevel)
  {
    switch(assignedLevel)
    {
      case Critical_Hit:
      SetDamage(GetDamage() + CriticalHit(GetCharacterName(), GetMeleeDamage()));
      break;

      case Life_Steal:
      Heal(LifeSteal(GetCharacterName(), getMaxHealth()));
      break;

      case Ranged_Attack:
      SetRangedDamage(RangedAttack(GetCharacterName()));
      break;
    }
  }

  void TakeDamage(Character *damageGiver, Character *damageReceiver, int currentLevel, int totalDamageReceived)
  {
    if(!rangedDamage)
    {
      SetDamageDefended(randomNumberGenerator(0, getDefence()));
      SetActualReceivedDamage(totalDamageReceived - GetDamageDefended());
     
      GetActualReceivedDamage() < 0 ? SetActualReceivedDamage(0) : SetActualReceivedDamage(GetActualReceivedDamage());
      
      if(currentLevel >= Blocker)
      {
        SetActualReceivedDamage(BlockAttack(GetCharacterName(), GetActualReceivedDamage()));
      }
    }
    else
    {
     rangedDamage = false;
     SetActualReceivedDamage(0);
    }

    GetHealth() - GetActualReceivedDamage() < 0 ?
    SetHealth(0) : 
    SetHealth(GetHealth() - GetActualReceivedDamage()); 
    showDamageStats( totalDamageReceived, GetDamageDefended(), GetActualReceivedDamage(), damageGiver, damageReceiver);    
  }

  void Heal(int heal)
  {
    if(heal > 0)
    {
      if(GetHealth() == getMaxHealth())
      {
        cout << GetCharacterName() << "'s" << " health is already full.";
        cout << "No requirement of healing..!!" << endl;
        cout << GetCharacterName() << "'s health: " << GetHealth() << endl << endl;
      }
      else
      {
        cout << GetCharacterName() << " is using its ability to heal." << endl;
        cout << GetCharacterName() <<" is healed by " << heal << "." << endl;
        (GetHealth() + heal) > getMaxHealth() ? 
          SetHealth(getMaxHealth()) : 
          SetHealth(GetHealth() + heal);
        cout << GetCharacterName() <<"'s Health after healing: " << GetHealth() << endl << endl;
      }
    }
  }
};

//Enemy class inheriting from Character class and ToolKit class
class Enemy : public Character, public ToolKit
{
  public:
  //constructors
  Enemy(int health, int meleeDamage, int defence, string characterName, int enemyNumber) : Character(health, meleeDamage, defence, characterName)
  {
    cout << GetCharacterName() << " " << enemyNumber << " has came." << endl;
    cout << GetCharacterName() << " " << enemyNumber << " is ready to fight with you." << endl;
  }

  Enemy(int health, int meleeDamage, int defence, string characterName) : Character(health, meleeDamage, defence, characterName)
  {
    //For initiazing the Boss Enemy with different number of values
  }

  //member functions
  void Attack(Character *attacker, Character *defender, int currentLevel)
  { 
    cout << "-- " << attacker->GetCharacterName() << " is attacking " << defender->GetCharacterName() << " --" << endl << endl;
    
    SetDamage(attacker->GetMeleeDamage() + randomNumberGenerator( 0, (currentLevel * 2)));
    defender->TakeDamage( attacker, defender, currentLevel, GetDamage());
  }


  void TakeDamage(Character *damageGiver, Character *damageReceiver, int currentLevel, int totalDamageReceived)
  {
    SetActualReceivedDamage(totalDamageReceived);
    SetDamageDefended(randomNumberGenerator(0, getDefence() + (currentLevel * currentLevel)));
    SetActualReceivedDamage(GetActualReceivedDamage() - GetDamageDefended());

    GetActualReceivedDamage() < 0 ? SetActualReceivedDamage(0) : SetActualReceivedDamage(GetActualReceivedDamage());

    GetHealth() - GetActualReceivedDamage() < 0 ?
    SetHealth(0) : 
    SetHealth(GetHealth() - GetActualReceivedDamage()); 
    showDamageStats( totalDamageReceived, GetDamageDefended(), GetActualReceivedDamage(), damageGiver, damageReceiver);    
  }

  //destructor
  ~Enemy()
  {
    if(!isAlive())
    cout << GetCharacterName() << " has died." << endl << endl;
  }
};


//Boss class inheriting from Enemy class and SpecialAbility class
class Boss : public Enemy, public SpecialAbility
{
  private:
  //member variables
  int pickedSpecialAbility, maxHealth;
  enum SpecialAbilities { Ground_Slash, Speed_Dash, Health_Regeneration};

  public:
  //constructor
  Boss(int health, int meleeDamage, int defence, string characterName) : Enemy(health, meleeDamage, defence, characterName)
{
  this->maxHealth = health;
  cout << "Murloc has arrived to give you a tough fight. Be Ready to face Boss Murloc!!" << endl;
  cout << "Murloc is ready to fight with you." << endl;
}

  //getter
  int getMaxHealth()
  {
    return maxHealth;
  }

  //setter
  void setMaxHealth(int _maxHealth)
  {
    maxHealth = _maxHealth;
  }

  //member function
  void Attack(Character *attacker, Character *defender, int currentLevel)
  {
    cout << "-- " << attacker->GetCharacterName() << " is attacking " << defender->GetCharacterName() << " --" << endl << endl;
    
    SetDamage(attacker->GetMeleeDamage() + SpecialAbility::randomNumberGenerator( 0, (currentLevel * 2)));
    
    pickedSpecialAbility = SpecialAbility::randomNumberGenerator(Ground_Slash, Health_Regeneration);
    
    switch(pickedSpecialAbility)
    {
      case Ground_Slash:
      SetDamage(GetDamage() +  GroundSlash(GetCharacterName(), getMaxHealth()));
      break;

      case Speed_Dash:
      SetDamage(GetDamage() + SpeedDash(GetCharacterName(), GetHealth()));
      break;

      case Health_Regeneration:
      SetHealth(HealthRegeneration(GetCharacterName(), GetHealth(), getMaxHealth()));
      break;
    }

    defender->TakeDamage( attacker, defender, currentLevel, GetDamage());
  }
};

//LevelManager class to manage the levels
class LevelManager
{
  private:
  //member variables
  enum Levels {Level1=1, Level2, Level3, Level4, Level5, Level6};
  string Collectibles[5] = {"Map", "Sword", "Shield", "Armour", "Bow"};
  string PlayerSpecialAbilities[4] = {"Critical Hit", "Blocker", "Life Steal", "Ranged Attack"};
  enum EnemyType {RecurrentEnemy=1, BossEnemy};
  int currentLevel, inLevelEnemies, maxLevel;
  public:
  //Constructor
  LevelManager()
  {  
    currentLevel = 0;
    inLevelEnemies = 0;
    maxLevel = Level6;
  }

  //getters
  int getCurrentLevel()
  {
    return currentLevel;
  }

  int getNumberOfEnemies()
  {
    return inLevelEnemies;
  }

  int getEnemyType()
  {
    if(currentLevel == maxLevel)
    {
        return BossEnemy;
    }
    return RecurrentEnemy;
  }

  int getMaxLevel()
  {
    return maxLevel;
  }

  //member functions
  void increaseLevel()
  {
    if(currentLevel < maxLevel)
    {
      currentLevel++;
      inLevelEnemies++;
    }
  }

  void LoadCurrentLevel()
  {
    if(currentLevel < maxLevel)
    {
      cout << endl;
        cout << "--------Level " << currentLevel << " Loaded--------" << endl << endl;
        cout << "You have to fight through " << currentLevel << (currentLevel < Level2 ? " enemy." : " enemies.")  << endl << endl;
    }
    else
    {
      cout << endl;
        cout << "--------Final Level(Level " << currentLevel << ") Loaded--------" << endl << endl;
        cout << "You have to fight through the boss Murloc to release your village." << endl << endl;
    }
  }

  void LevelCompletionMessage()
  {
    if(currentLevel < maxLevel)
    {
      cout << "--------You have completed Level " << currentLevel << "--------" << endl;
      cout << "\t----------You found " << Collectibles[currentLevel-1] << "----------" << endl; 
      if(currentLevel > Level1 && currentLevel < Level6)
      {
        cout << "--" << PlayerSpecialAbilities[currentLevel-2] << " Special Ability unlocked--" << endl;
      }
    }
    else
    {
      cout << "--------Congratulations! You have completed the Final Level!--------" << endl;
      cout << "--------You have released your village from Murloc's control.--------" << endl;
    }  
  }

  void LeveledUp(Player *player)
  {
    cout << endl;
    cout << player->GetCharacterName() << " is leveling up." << endl;
    player->setMaxHealth(player->getMaxHealth() + ((player->getMaxHealth()*20)/100));
    player->SetHealth(player->getMaxHealth());
    player->SetMeleeDamage(player->GetMeleeDamage() + 5);
    player->SetDefence(player->getDefence() + 5);
    player->setHeal(player->GetHeal()+5);
    cout << player->GetCharacterName() << "'s" << " health is increased to " << player->GetHealth() << "." << endl; 
    cout << player->GetCharacterName() << "'s" << " melee damage is increased to " << player->GetMeleeDamage() << "." << endl;
    cout << player->GetCharacterName() << "'s defence is increased to " << player->getDefence() << "." << endl;
    cout << player->GetCharacterName() << "'s healing ability is increased to " << player->GetHeal() << "." << endl;
  }


  void LoadGameIntro()
  {
    cout << "================== Welcome To Text - Based RPG Adventure Game ==================" << endl << endl;
    cout << "You are a brave warrior whose village is captured by a monster named Murlocs." << endl;
    cout << "You have to defeat Murlocs and save your village." << endl;
    cout << "To defeat Murlocs, you need to collect 4 items: Sword, Shield, Armour and Bow." << endl << endl;
    cout << "Each item will be rewarded after completing the respected levels." << endl;
    cout << "Sword (Will be rewarded after completing level 2)" << endl;
    cout << "Shield (Will be rewarded after completing level 3)" << endl;
    cout << "Armour (Will be rewarded after completing level 4)" << endl;
    cout << "Bow (Will be rewarded after completing level 5)" << endl << endl;
    cout << "Your health, melee damage, defence ability and healing capacity will be increased after completing each level." << endl;
    cout << "Special Abilities will be unlocked after completing each level." << endl << endl;
    cout << "You can choose to fight with either of the following options: " << endl;
    cout << "1. Attack" << endl;
    cout << "2. Heal" << endl;
    cout << "Attacking will decrease your enemy's health." << endl;
    cout << "Healing will increase your health." << endl;
    cout << "Each enemy will be able to defend your attack with a certain amount." << endl;
    cout  << "You will also be able to defend enemy's attack with a certain amount which is randomly generated."<< endl;
    cout << "Depending upon the probability of activation of the special abilities - the abilities will get triggered when a you choose to do an attack." << endl << endl;

    cout << "------------------------------ Detail Of Each Level ------------------------------" << endl << endl;
    cout << "Level 1:" << endl; 
    cout << "There will be only 1 enemy." << endl;
    cout << "You will be given a map." << endl << endl;

    cout << "Level 2:" << endl; 
    cout << "There will be 2 enemies." << endl;
    cout << "Special Ability Awarded - Critical hits (performs attack with massive damage boost)" << endl;
    cout << "Special Item Awarded - Sword" << endl << endl;

    cout << "Level 3:" << endl; 
    cout << "There will be 3 enemies." << endl;
    cout << "Special Ability Awarded - Blocker (will get 0 damage on enemy hit)" << endl;
    cout << "Special Item Awarded - Shield" << endl << endl;

    cout << "Level 4:" << endl; 
    cout << "There will be 4 enemies." << endl;
    cout << "Special Ability Awarded - Life steal (Recovering a small amount of HP after giving damage)" << endl;
    cout << "Special Item Awarded - Armour" << endl << endl;

    cout << "Level 5:" << endl; 
    cout << "There will be 5 enemies." << endl;
    cout << "Special Ability Awarded - Ranged Attack (After performing this attack, you won't take damage for the next attack of the enemy)" << endl;
    cout << "Special Item Awarded - Bow" << endl << endl;

    cout << "Level 6:" << endl; 
    cout << "There will be a boss fight with Murloc." << endl;
    cout << "You will get your village back" << endl << endl;

    cout << "Murloc is also having some special abilities." << endl;
    cout << "1. Ground Slash - Damages enemy with a large amount of damage (damage amount is depended on the maximum health of Murloc)" << endl;
    cout << "2. Speed Dash - Damages enemy with an amount depended on the health of Murloc)" << endl;
    cout << "3. Health Regeneration - Heals Murloc with an amount depended on both the maximum health and the health of Murloc" << endl << endl;

    cout << "NOTE: Each Special Ability of both (You and Murloc) will have a probability of 10%." << endl << endl;

    cout << "------------------------------- Game Starts Now --------------------------------" << endl << endl;   
  }
};


class GameManager
{
  private:
  //member variables
  //assigning all character's values at one place   
  int PlayerHealth = 100;
  int PlayerMeleeDamage = 20; 
  int PlayerDefence = 20;
  int PlayerHealingCapacity = 20;
  bool isRangedAttackActive = false;
  string PlayerName = "Player";

  int EnemyHealth = 100;
  int EnemyMeleeDamage = 15;
  int EnemyDefence = 15;
  string EnemyName = "Enemy";

  int BossEnemyHealth = 210;
  int BossEnemyMeleeDamage = 30;
  int BossEnemyDefence = 30;
  string BossEnemyName = "Murloc";

  Player *player = NULL;
  Enemy *enemy = NULL;
  LevelManager *levelManager = NULL;
  ToolKit *toolkit_obj = NULL;

  enum EnemyType {RecurrentEnemy=1, BossEnemy};
  char playerInput, playerChoice;
  int numberOfEnemies;


  public:
  //member function to start the game
  void StartGame()
  { //game loop
    do
      {   
        toolkit_obj = new ToolKit();
        levelManager = new LevelManager();
        levelManager->LoadGameIntro();
        player = new Player( PlayerHealth, PlayerMeleeDamage, PlayerDefence, PlayerHealingCapacity, isRangedAttackActive, PlayerName);
        while(levelManager->getCurrentLevel() < levelManager->getMaxLevel())
        {
          levelManager->increaseLevel();
          levelManager->LoadCurrentLevel();
          numberOfEnemies = levelManager->getNumberOfEnemies();
          if(levelManager->getEnemyType() == RecurrentEnemy)
          {
            for(int i = 1; i <= numberOfEnemies; i++)
            {
              if(!player->isAlive())
              break;
              enemy = new Enemy( EnemyHealth, EnemyMeleeDamage, EnemyDefence, EnemyName, i);
              inGameActionLoop(player, enemy);
            }  
            if(player->isAlive())
            {
              levelManager->LevelCompletionMessage();
              levelManager->LeveledUp(player);
            }          
            else
            {
              break;
            }
          }
          else if(levelManager->getEnemyType() == BossEnemy)
          {
            enemy = new Boss( BossEnemyHealth, BossEnemyMeleeDamage, BossEnemyDefence, BossEnemyName);     
            inGameActionLoop(player, enemy);
    
            if(player->isAlive())
            levelManager->LevelCompletionMessage();
            else
            {
              break;
            }
          }      
        }
    
        delete player;
        delete levelManager;
        delete toolkit_obj;
        
        cout << "Do you want to play again? (Y/N): ";
        cin >> playerChoice;
        cout << endl;
    
      }while(playerChoice == 'Y' || playerChoice == 'y'); 
  }

  //function to handle the player's input
  void GetPlayerInput(Player *player, Enemy *enemy)
  {
    cout << "Press A to attack or H to heal: ";
    cin >>playerInput;

    if(playerInput == 'H' || playerInput == 'h')
    {      
      cout << "You have chosen to heal yourself." << endl << endl;
      player->Heal(toolkit_obj->randomNumberGenerator( (player->GetHeal())/2, player->GetHeal()));
      enemy->Attack(enemy, player, levelManager->getCurrentLevel());
    }
    else if(playerInput == 'A' || playerInput == 'a')
    {
      cout << "You have chosen to attack " << enemy->GetCharacterName() << endl << endl;
      player->Attack(player, enemy, levelManager->getCurrentLevel());
      if(enemy->isAlive())
      enemy->Attack(enemy, player, levelManager->getCurrentLevel());
    }
    else
    {
      cout << "Invalid Input. Please select a valid option." << endl << endl;
      GetPlayerInput( player, enemy);
    }
  }

  //function to check whether the player or enemy is alive
  void inGameActionLoop(Player *player, Enemy *enemy)
  {
    do
      {
        GetPlayerInput(player, enemy);
      }while(player->isAlive() && enemy->isAlive());

    if(player->isAlive())
    {
      cout << "You have defeated the " << enemy->GetCharacterName() << "." << endl; 
      if(player->GetRangedDamage())
      { player->SetRangedDamage(false); }     
    }
    else
    {
      cout << "You have been defeated by " << enemy->GetCharacterName() << "." << endl; 
    }
    delete enemy;
  }
};

int main()
{
  GameManager *GameManager_Obj = new GameManager();
  GameManager_Obj->StartGame();
  delete GameManager_Obj;
  return 0;
}