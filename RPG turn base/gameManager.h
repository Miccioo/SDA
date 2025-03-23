#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "src/list1.h"
#include "src/stack.h"
#include "src/queue.h"
#define MAX_ITEM 10
#define TRUE 1
#define MAX_SHOP 10

Item shop[MAX_SHOP];

void tampilkanMenu();
void PilihClass();

void Level();
void tampilkanLevel();
void CombatMechanics(int level, int uang);

void ShowInventory(List L, int jumlah, int uang);
void UseInventory(List *L, address item);
void AddToInventory(List *L, Item item, int quantity);

void MenuShop(Item shop[],int uang);
void AddShop(Item shop[]);
// Fungsi inisialisasi
void InitShopItems();

// Fungsi akses item random
Item GetRandomPotion();
Item GetRandomWeapon();
Item GetRandomEquipment();

void Enemy(const char *enemyClass, int level);
void EnemyStat(const char *enemyClass, int *stat);

void Player(const char *playerClass);
void PlayerStat(const char *playerClass, int *stat);

#endif
