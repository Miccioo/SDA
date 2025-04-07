/*
	Author: Zaidan Arkaan
	Date: 23/03/25 22:30
	Description: Program game rpg simpel turn based, program ini masih banyak sekali 
	kekurangan misalnya tidak dapat memakai inventory pada saat melawan musuh, tidak ada skill skill khusus
	untuk mage, evasion dan acc belum di implementasikan, serta tidak ada status critical dalam memberikan serangan.
	Kurangnya waktu dalam pengerjaan membuat program ini selesai ala kadarnya.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/list1.h"
#include "src/stack.h"
#include "src/queue.h"
#include "gameManager.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 40% dari chatgpt, (Penggunaan chatgpt hanya dalam memperbaiki kesalahan-kesalahan)
// Mohon maaf saya sudah pusing sekali

int main(int argc, char *argv[]) {
    // Initialize shop array
    Item shop[MAX_SHOP];
    infoItem classState;

    int userClass;
    int menu, level, item_index;
    int index_item = 0, jumlah = 0, uang = 100, shopItemCount = 0;
    const char *playerClass[] = {"warrior", "ranger", "mage"}; 
    
    // Queue is used for turn-based mechanics between player and enemy
    Queue Turn;
    
    // List is used for inventory item management
    List Inventory;
    
    // Stack is used when user wants to undo a previous action
    Stack Undo;
    
    // Create List, Stack and Queue
    CreateQueue(&Turn);
    CreateList(&Inventory);
    CreateStack(&Undo);
    
    // Set random seed
    srand(time(NULL));
    
    printf("--- SELAMAT DATANG DI GAME TURN BASE ---\n");
    PilihClass();
    printf("\nSilahkan pilih class terlebih dahulu. (Kamu bisa menggantinya nanti): ");
    scanf("%d", &userClass);
    
    // Input validation
    if (userClass < 1 || userClass > 3) {
        userClass = 1; // Default to warrior if invalid
        printf("Input tidak valid, default ke Warrior.\n");
    }
    
    do {
        tampilkanMenu();
        scanf("%d", &menu);
        
        // case 1 : Play Game
        // case 2 : Inventory
        // case 3 : Shop
        // case 4 : Change Class
        // case 5 : exit
        
        switch (menu) {
            
            case 1:
                tampilkanLevel();
                scanf("%d", &level);
                CombatMechanics(level, uang);
                
                continue;
                
            case 2:
                ShowInventory(Inventory, jumlah, uang);
                
                if (!ListEmpty(Inventory)) {
                    printf("\nIngin menggunakan item? (1: Ya, 0: Tidak): ");
                    int useChoice;
                    scanf("%d", &useChoice);
                    
                    if (useChoice == 1) {
                        printf("Pilih nomor item: ");
                        int itemNum;
                        scanf("%d", &itemNum);
                        
                        address P = Inventory.First;
                        int count = 1;
                        
                        while (P != Nil && count < itemNum) {
                            P = P->next;
                            count++;
                        }
                        
                        if (P != Nil && count == itemNum) {

                            infoItem itemCopy = P->nilai;
                            push(&Undo, itemCopy);
                            
                            // Use the item
                            UseInventory(&Inventory, P);
                            
                            // Option to undo
                            printf("Ingin undo penggunaan item? (1: Ya, 0: Tidak): ");
                            int undoChoice;
                            scanf("%d", &undoChoice);
                            
                            if (undoChoice == 1 && !isEmpty(&Undo)) {
                                // Retrieve the item from undo stack
                                infoItem undoItem;
                                DelVFirst(&(Undo.Top), &undoItem);
                                
                                // Add it back to inventory
                                AddToInventory(&Inventory, undoItem.item, 1);
                                printf("Berhasil undo penggunaan item!\n");
                            }
                        } else {
                            printf("Item tidak ditemukan!\n");
                        }
                    }
                }
                continue;
                
            case 3:
                // For random Shop
                InitShopItems();
                AddShop(shop);
                int exitshop = 0;
                while(!exitshop){
                    MenuShop(shop, uang);
                    scanf("%d", &item_index);
                    
                    if (item_index >= 1 && item_index <= 10) 
                    {
                        int idx = item_index - 1; // Convert to 0-based index
                        // Validate item
                        if(idx >= MAX_SHOP || shop[idx].quantity <= 0) {
                            printf("Item tidak tersedia!\n");
                            continue;
                        }
                        
                        if(uang < shop[idx].price) {
                            printf("Uang tidak cukup!\n");
                            continue;
                        }
                        
                        infoItem shopState;
                        strcpy(shopState.item.name, "ShopState");
                        shopState.item.type = 99; // Special type for shop state
                        shopState.item.status = uang;
                        shopState.item.price = shop[idx].price;
                        shopState.quantity = idx;
                        push(&Undo, shopState);
                        
                        if(shop[idx].quantity > 0 && uang >= shop[idx].price){
                            // Process purchase
                            int previousMoney = uang;
                            uang -= shop[idx].price;
                            AddToInventory(&Inventory, shop[idx], 1); // Add 1 to inventory
                            
                            // Reduce stock in shop
                            shop[idx].quantity--;
                            
                            printf("Berhasil membeli %s!\n", shop[idx].name);
                            
                            // Option to undo purchase
                            printf("Ingin undo pembelian? (1: Ya, 0: Tidak): ");
                            int undoChoice;
                            scanf("%d", &undoChoice);
                            
                            if (undoChoice == 1) {
                                // Undo the purchase
                                infoItem undoState;
                                DelVFirst(&(Undo.Top), &undoState);
                                
                                // Restore money
                                uang = undoState.item.status;
                                
                                // Remove from inventory (find by name)
                                address P = Inventory.First;
                                address Prev = Nil;
                                
                                while (P != Nil && strcmp(P->nilai.item.name, shop[idx].name) != 0) {
                                    Prev = P;
                                    P = P->next;
                                }
                                
                                if (P != Nil) {
                                    // Found the item, now remove one
                                    P->nilai.quantity--;
                                    if (P->nilai.quantity <= 0) {
                                        // Remove node if quantity is 0
                                        if (Prev == Nil) {
                                            // It's the first node
                                            Inventory.First = P->next;
                                        } else {
                                            Prev->next = P->next;
                                        }
                                        DeAlokasi(P);
                                    }
                                }
                                
                                // Restore shop quantity
                                shop[idx].quantity++;
                                
                                printf("Berhasil undo pembelian. Uang dikembalikan.\n");
                            }
                        }
                    } else if (item_index == 11) 
                    {   
                        exitshop = 1;
                    } else {
                        printf("Input tidak valid!\n");
                    }
                }
                continue;

            case 4:
                // Store previous class for potential undo
                strcpy(classState.item.name, "ClassState");
                classState.item.type = 99; // Special type for class state
                classState.item.status = userClass;
                classState.quantity = 0;
                push(&Undo, classState);
                
                int previousClass = userClass;
                
                do {
                    PilihClass();
                    printf("Silahkan ganti class: ");
                    scanf("%d", &userClass);
                    if(userClass >= 1 && userClass <= 3)
                    {
                        printf("\nBerhasil berganti class ke %s\n", playerClass[userClass-1]);
                        
                        // Option to undo class change
                        printf("Ingin undo perubahan class? (1: Ya, 0: Tidak): ");
                        int undoChoice;
                        scanf("%d", &undoChoice);
                        
                        if (undoChoice == 1) {
                            // Restore previous class
                            infoItem undoClass;
                            DelVFirst(&(Undo.Top), &undoClass);
                            userClass = undoClass.item.status;
                            printf("Berhasil undo perubahan class. Kembali ke %s\n", playerClass[userClass-1]);
                        }
                    } else {
                        printf("\nGagal berganti class, silakan ulangi\n");
                    }
                } while (userClass < 1 || userClass > 3);
                continue;
                
            case 5:
                printf("Terima kasih telah bermain...");
                break;
                
            default:
                printf("\nPilihan menu tidak tersedia.\n");
        }
            
    } while(menu != 5);
    
    return 0;
}
