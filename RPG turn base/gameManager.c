#include "gameManager.h"
#include <stdlib.h>
#include <string.h>
#include "src/list1.h"
#include "src/stack.h"
#include "src/queue.h" 


Item shop[MAX_SHOP];
// Case 1
static Item basePotions[] = {
    {"Potion S", 0, 10, 5, 0},
	{"Potion M", 0, 20, 10, 0},
	{"Potion L", 0, 50, 20, 0},
	{"Elixir", 0, 100, 50, 0}
};

static Item baseWeapons[] = {
	{"Wooden Sword", 1, 5, 15, 0},
    {"Iron Sword", 1, 10, 30, 0},
    {"Wooden Bow", 1, 7, 20, 0},
    {"Iron Bow", 1, 12, 35, 0},
    {"Wooden Staff", 1, 6, 20, 0},
    {"Iron Staff", 1, 11, 35, 0}
};

static Item baseEquipments[] = {
	{"Wooden Shield", 2, 5, 25, 0},
    {"Iron Shield", 2, 10, 40, 0},
    {"Wooden Armor", 2, 5, 25, 0},
    {"Leather Armor", 2, 8, 35, 0},
    {"Iron Armor", 2, 15, 60, 0},
    {"Wooden Helmet", 2, 3, 14, 0},
    {"Leather Helmet", 2, 5, 28, 0},
    {"Iron Helmet", 2, 8, 35, 0},
    {"Wooden Boots", 2, 2, 10, 0},
    {"Leather Boots", 2, 4, 20, 0},
    {"Iron Boots", 2, 6, 30, 0},
    {"Wooden Pants", 2, 4, 23, 0},
    {"Leather Pants", 2, 5, 26, 0},
    {"Iron Pants", 2, 7, 37, 0}
    
};

void tampilkanMenu()
{
    printf("\n==== GAME TURN BASE ====\n");
    printf("1. Play Game\n");
    printf("2. Inventory\n");
    printf("3. Shop\n");
    printf("4. Change Class\n");
    printf("5. Exit\n");
	printf("\nPilih Opsi: ");
}

void PilihClass() 
{
	printf("\nClass:  \n");
	printf("1. Warrior\n");
	printf("2. Ranger\n");
	printf("3. Mage\n\n");
}

void Level()
{
	
}

void tampilkanLevel()
{
	printf("\n==== FLOOR ====\n");
	printf("Level 1\tLevel 2\tLevel 3\n");
	printf("Level 4\tLevel 5\tLevel 6\n");
	printf("Level 7\tLevel 8\tLevel 9\n");
	printf("Pilih Level: ");
}

// Dari chatgpt

void CombatMechanics(int level, int uang) {
    if (level < 1 || level > 9) {
        printf("Level tidak valid!\n");
        return;
    }
    
    printf("\n==== COMBAT LEVEL %d ====\n", level);
    
    // Generate random enemy based on level
    const char *enemyClasses[] = {"warrior", "ranger", "mage"};
    int randomEnemyIndex = rand() % 3;
    const char *enemyClass = enemyClasses[randomEnemyIndex];
    
    printf("Kamu bertemu dengan musuh!\n");
    Enemy(enemyClass, level);
    
    printf("\nSimulasi pertarungan dimulai...\n");
    
    int playerHP = 100;
    int enemyHP = 50 * level;
    int turn = 1;
    
    // Create a queue for turn order
    Queue turnQueue;
    CreateQueue(&turnQueue);
    
    // Set up turn order with player and enemy
    infoItem playerTurn, enemyTurn;
    
    // Initialize player turn info
    strcpy(playerTurn.item.name, "Player");
    playerTurn.item.type = 0;
    playerTurn.item.status = 0;
    playerTurn.item.price = 0;
    playerTurn.quantity = 1;
    
    // Initialize enemy turn info
    strcpy(enemyTurn.item.name, "Enemy");
    enemyTurn.item.type = 0;
    enemyTurn.item.status = 0;
    enemyTurn.item.price = 0;
    enemyTurn.quantity = 1;
    
    // Add initial turns to queue (player goes first)
    EnQueue(&turnQueue, playerTurn);
    EnQueue(&turnQueue, enemyTurn);
    
    // Create a stack for undo
    Stack actionStack;
    CreateStack(&actionStack);
    
    // Create a structure to store combat state for undo
    typedef struct {
        int playerHP;
        int enemyHP;
        int turn;
    } CombatState;
    
    while (playerHP > 0 && enemyHP > 0) {
        printf("\nTurn %d:\n", turn);
        
        // Display the turn order
        printf("Turn order: ");
        displayQueue(&turnQueue);
        
        // Save current state for potential undo
        CombatState currentState;
        currentState.playerHP = playerHP;
        currentState.enemyHP = enemyHP;
        currentState.turn = turn;
        
        infoItem stateItem;
        strcpy(stateItem.item.name, "CombatState");
        stateItem.item.type = 99; // Special type for combat state
        stateItem.item.status = turn;
        stateItem.item.price = 0;
        stateItem.quantity = (playerHP * 1000) + enemyHP; // Store HPs in quantity field
        
        // Push state to stack
        push(&actionStack, stateItem);
        
        // Get the next turn from queue
        infoItem currentTurn;
        deQueue(&turnQueue, &currentTurn);
        
        // Process turn based on who is acting
        if (strcmp(currentTurn.item.name, "Player") == 0) {
            // Player's turn
            int playerDamage = rand() % 20 + 10;
            enemyHP -= playerDamage;
            printf("Kamu menyerang musuh dan memberikan %d damage!\n", playerDamage);
            
            // Option to undo
            printf("Apakah ingin undo? (1: Ya, 0: Tidak): ");
            int undoChoice;
            scanf("%d", &undoChoice);
            
            if (undoChoice == 1 && !isEmpty(&actionStack)) {
                // Pop the current state (discard it)
                infoItem temp;
                DelVFirst(&(actionStack.Top), &temp);
                
                // Get previous state if available
                if (!isEmpty(&actionStack)) {
                    infoItem prevState;
                    DelVFirst(&(actionStack.Top), &prevState);
                    
                    // Restore previous state
                    turn = prevState.item.status;
                    playerHP = prevState.quantity / 1000;
                    enemyHP = prevState.quantity % 1000;
                    
                    printf("Undo berhasil! Kembali ke status sebelumnya.\n");
                    printf("Status HP - Kamu: %d | Musuh: %d\n", playerHP, enemyHP);
                    
                    // Re-add the current turn to the queue
                    EnQueue(&turnQueue, currentTurn);
                    continue;
                } else {
                    printf("Tidak ada state sebelumnya untuk di-undo.\n");
                    // Re-push the current state since we couldn't undo
                    push(&actionStack, stateItem);
                }
            }
        } else {
            // Enemy's turn
            int enemyDamage = rand() % 15 + (5 * level);
            playerHP -= enemyDamage;
            printf("Musuh menyerang dan memberikan %d damage!\n", enemyDamage);
        }
        
        // Re-add the turn to the queue for next round
        EnQueue(&turnQueue, currentTurn);
        
        // Check battle conditions
        if (enemyHP <= 0) {
            printf("Musuh dikalahkan!\n");
            break;
        }
        
        if (playerHP <= 0) {
            printf("Kamu kalah dalam pertarungan!\n");
            break;
        }
        
        printf("Status HP - Kamu: %d | Musuh: %d\n", playerHP, enemyHP);
        turn++;
        
        // Simulate turn-based gameplay with a pause
        printf("Tekan Enter untuk melanjutkan...");
        getchar();
        getchar();
    }
    
    // Reward for winning
    if (enemyHP <= 0) {
        int goldReward = 20 * level;
        printf("\nKamu mendapatkan %d gold!\n", goldReward);
        uang += goldReward;
    }
}

// Case 2

void ShowInventory(List L, int jumlah, int uang)
{
	printf("\n==== INVENTORY ====\n");
	PrintInfo(L);
}

void AddToInventory(List *L, Item item, int quantity){
	address P = L->First;
	
	while (P != Nil){
		if (strcmp(P->nilai.item.name, item.name) == 0) {
            P->nilai.quantity += quantity;
            return;
        }
        P = P->next;
	}
	
	// Jika item belum ada, tambahkan baru
    infoItem newItem;
    newItem.item = item;
    newItem.quantity = quantity;
    address newNode = Alokasi(newItem);
    
    if (newNode != NULL) {
        InsertFirst(L, newNode);
    }
}

void UseInventory(List *L, address item) {
    if (ListEmpty(*L)) {
        printf("Inventory kosong!\n");
        return;
    }
    
    if (item == NULL) {
        printf("Item tidak valid!\n");
        return;
    }
    
    // Decrease quantity
    item->nilai.quantity--;
    
    // If quantity is 0, remove the item
    if (item->nilai.quantity <= 0) {
        // Find the previous node
        if (item == L->First) {
            L->First = item->next;
        } else {
            address P = L->First;
            while (P != NULL && P->next != item) {
                P = P->next;
            }
            if (P != NULL) {
                P->next = item->next;
            }
        }
        
        // Free memory
        free(item);
    }
    
    printf("Item berhasil digunakan!\n");
}


// Case 3

// Dari chatgpt

// Function untuk menambahkan item ke shop secara acak
void AddShop(Item shop[]) {
	int index = 0;
    // Tambahkan 2 potion random
    for(int i = 0; i < 3 && index < MAX_SHOP; i++, index++) {
        Item item = GetRandomPotion();
        item.quantity = rand() % 3 + 1;  // Stok 1-3
        shop[index] = item;
    }
    
    // Tambahkan 2 weapon random
    for(int i = 0; i < 2 && index < MAX_SHOP; i++, index++) {
        Item weapon = GetRandomWeapon();
        weapon.quantity = rand() % 2 + 1;
        shop[index] = weapon;
    }
    
    // Tambahkan 1 equipment random
    for(int i = 0; i < 5 && index < MAX_SHOP; i++, index++){
	    Item equip = GetRandomEquipment();
	    equip.quantity = rand() % 5 + 1;
	    shop[index] = equip;
	}
}

void MenuShop(Item shop[], int uang) {
    printf("\n==================== SHOP =====================\n");
    printf("Uang: %d Coin\n\n", uang);
    
    for (int i = 0; i < MAX_SHOP; i++) {
    	if(shop[i].quantity > 0) {    		
	    	char typeStr[20];
	        switch(shop[i].type) {
	            case 0: strcpy(typeStr, "Heal"); break;
	            case 1: strcpy(typeStr, "Attack"); break;
	            case 2: strcpy(typeStr, "Defense"); break;
	            default: strcpy(typeStr, "Unknown");
	        }
	        
	        printf("%2d. %-20s [%2dx] %s +%d\t%d Coin\n",
	            i + 1,
	            shop[i].name,
	            shop[i].quantity,
	            typeStr,
	            shop[i].status,
	            shop[i].price
	        );
		}
    }
    printf("11. Kembali\n");
    printf("================================================\n\n");
    printf("Pilih item yang mau dibeli: ");
}

void InitShopItems() {
    srand(time(NULL));
}

Item GetRandomPotion() {
    return basePotions[rand() % (sizeof(basePotions)/sizeof(basePotions[0]))];
}

Item GetRandomWeapon() {
    return baseWeapons[rand() % (sizeof(baseWeapons)/sizeof(baseWeapons[0]))];
}

Item GetRandomEquipment() {
    return baseEquipments[rand() % (sizeof(baseEquipments)/sizeof(baseEquipments[0]))];
}


void Enemy(const char *enemyClass, int level)
{
	int stat[8];
	EnemyStat(enemyClass, stat);
	
	for (int i = 0; i < 8; i++) {
        stat[i] *= level;
    }
	
	printf("Enemy Class: %s (Level %d)\n", enemyClass, level);
    printf("STR: %d, AGI: %d, INT: %d\n", stat[0], stat[1], stat[2]);
    printf("HP: %d, Attack: %d, Defense: %d, Evasion: %d, Accuracy: %d\n",
           stat[3], stat[4], stat[5], stat[6], stat[7]);
}

void EnemyStat(const char *enemyClass, int *stat)
{
	// Base Stat Monster
	int str, agi, intel, hp, attack, def, evasion, acc;
	
	// enemy class + Base Status per class
	if (strcmp(enemyClass, "warrior") == 0) {
		str = 5, agi = 2, intel = 1; hp = 100 * str, attack = 25 * str, def = 26 * str, evasion = 2 * agi, acc = 75 * agi;
	} else if (strcmp(enemyClass, "ranger") == 0) {
		str = 2, agi = 5, intel = 1, hp = 100 * str, attack = 30 * agi , def = 25 * str, evasion = 2 * agi, acc = 70 * agi;
	} else if (strcmp(enemyClass, "mage") == 0) {
		str = 2, agi = 3, intel = 5, hp = 120 * str, attack = 50 * intel , def = 20 * str, evasion = 2 * agi, acc = 77 * agi;
	} else {
		printf("Tidak ada class!\n");
		return;
	}
	
	stat[0] = str;
    stat[1] = agi;
    stat[2] = intel;
    stat[3] = hp;
    stat[4] = attack;
    stat[5] = def;
    stat[6] = evasion;
    stat[7] = acc;
}

void Player(const char *playerClass) 
{
    int stat[8];
    PlayerStat(playerClass, stat);
    
    printf("Player Class: %s\n", playerClass);
    printf("STR: %d, AGI: %d, INT: %d\n", stat[0], stat[1], stat[2]);
    printf("HP: %d, Attack: %d, Defense: %d, Evasion: %d, Accuracy: %d\n",
           stat[3], stat[4], stat[5], stat[6], stat[7]);
}

void PlayerStat(const char *playerClass, int *stat) {
    // Base Stat Player
    int str, agi, intel, hp, attack, def, evasion, acc;
    
    // Player class + Base Status per class
    if (strcmp(playerClass, "warrior") == 0) {
        str = 8, agi = 4, intel = 2;
        hp = 120 * str;
        attack = 30 * str;
        def = 30 * str;
        evasion = 3 * agi;
        acc = 80 * agi;
    } else if (strcmp(playerClass, "ranger") == 0) {
        str = 3, agi = 8, intel = 3;
        hp = 110 * str;
        attack = 35 * agi;
        def = 22 * str;
        evasion = 4 * agi;
        acc = 85 * agi;
    } else if (strcmp(playerClass, "mage") == 0) {
        str = 2, agi = 3, intel = 9;
        hp = 100 * str;
        attack = 55 * intel;
        def = 18 * str;
        evasion = 3 * agi;
        acc = 75 * agi;
    } else {
        printf("Class tidak valid!\n");
        return;
    }
    
    stat[0] = str;
    stat[1] = agi;
    stat[2] = intel;
    stat[3] = hp;
    stat[4] = attack;
    stat[5] = def;
    stat[6] = evasion;
    stat[7] = acc;
}


