#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Node {
    char key;            
    int value;           
    struct Node* prev;    
    struct Node* next;    
} Node;


Node* createNode(char key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node)); 
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


void restockItem(Node* head, char restock_key, int restock_amount) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->key == restock_key) {
            temp->value += restock_amount;
            printf("Barang %c berhasil ditambahkan. Jumlah sekarang: %d\n", temp->key, temp->value);
            return; 
        }
        temp = temp->next;
    }

   
    printf(" Barang %c tidak ditemukan dalam gudang.\n", restock_key);
}



void insertAtFront(Node** head, char key, int value) {
    Node* newNode = createNode(key, value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}


void insertAtEnd(Node** head, char key, int value) {
    Node* newNode = createNode(key, value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void displayForward(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("    Nama barang = %c ,Jumlah Barang = %d \n", temp->key, temp->value);
        temp = temp->next;
    }
    printf("\n");
}

void displayBackward(Node* head) {
    if (head == NULL) return;
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (temp != NULL) {
        printf("    Nama barang = %c ,Jumlah Barang = %d \n", temp->key, temp->value);
        temp = temp->prev;
    }
    printf("\n");
}


void deleteNode(Node** head, char key) {
    Node* temp = *head;

    // Search for the node to be deleted
    while (temp != NULL && temp->key != key) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Node with key '%c' not found.\n", key);
        return;
    }

    // Update links
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        *head = temp->next; 

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
    printf("Node with key '%c' deleted.\n", key);
}



void admincheck(const char* username, const char* password, char* ptr) {
    char temp_username[15];
    char temp_pass[8];

    printf("Masukan username anda: ");
    fgets(temp_username, sizeof(temp_username), stdin);
    temp_username[strcspn(temp_username, "\n")] = '\0'; 

    printf("Masukan password anda: ");
    fgets(temp_pass, sizeof(temp_pass), stdin);
    temp_pass[strcspn(temp_pass, "\n")] = '\0'; 

    // Compare strings
    if (strcmp(temp_username, username) == 0) {
        if (strcmp(temp_pass, password) == 0) {
            *ptr = 'A';
        } else {
            *ptr = 'L';
            printf("Kombinasi Username dan password anda salah");
        }
    } else {
        *ptr = 'L'; 
        printf("Kombinasi Username dan password anda salah \n");
    }
}

int main() {
    

    char state = 'L';
    
    Node* head = NULL;

    
    insertAtFront(&head, 'A', 10);
    insertAtFront(&head, 'B', 20);
    insertAtFront(&head, 'C', 5);

    while (true) {
        switch (state) {
            case 'L': {
                char username[15] = "admin";
                char password[8] = "pass123";
                admincheck(username, password, &state);
                break;
            }

            case 'A': {
                while (true) {
                    int mode;
                    printf ("\n <======= Pemiliham Mode =======> ");
                    printf("\n 1. Menambahkan barang baru");
                    printf("\n 2. Melakukan Restock Kepada Barang Tertentu ");
                    printf("\n 3. Menghapus Barang Yang sudah ada ");
                    printf("\n 4. Melihat Stock yang ada di Gudang ");
                    printf("\n 5. Keluar dari Aplikasi");
                    printf("\nMode apa yang ingin anda pilih? = ");
                    scanf("%d", &mode);

                    switch (mode) {
                        case 1:
                            char product_name ;
                            int product_stock ;
                            int pos ;
                            printf ("\n <======= Penambahan Barang =======> \n ");
                            printf ("Nama barang yang ingin dimasukan = ") ;
                            scanf(" %c", &product_name);
                            printf ("jumlah barang yang ingin dimasukan = ") ;
                            scanf ("%d" , &product_stock );
                            printf (" 1. Dimasukan didepan \n 2. Dimasukan di belakang "); 
                            printf ("Posisi yang ingin dipilih = "); 
                            scanf ("%d", &pos); 
                            if (pos == 1) {
                            insertAtFront(&head, product_name, product_stock);
                            } 
                            else if  (pos == 2 ) { 
                            insertAtEnd(&head, product_name, product_stock);
                            }
                            else { 
                                printf ("Pilihan tidak ada dalam pilihan") ; 
                                break ;
                            }

                            break;

                        case 2: {
                            char restock_key;
                            int restock_amount;

                            printf("\n<======= Restock Barang =======>\n");
                            printf("Nama barang yang ingin di-restock: ");
                            scanf(" %c", &restock_key);
                            printf("Jumlah barang yang ingin ditambahkan: ");
                            scanf("%d", &restock_amount);
                            restockItem(head, restock_key, restock_amount); 
                            break;
                        }

                        case 3:
                            char item_del ; 
                            printf ("\n <=======  Menghapus barang yang ingin Dihapus  =======> \n");
                            displayForward(head);
                            printf("Pilih Barang apa yang ingin Di Hapus ");
                            scanf ("%c", &item_del); 
                            deleteNode(&head, item_del);
                            break;

                        case 4:
                            int view_mode ; 
                            printf ("\n <=======  Display Barang Dalam gudang =======> \n");
                            printf (" 1. Perlihatkan dari depan \n 2. perlihatkan dari belakang "); 
                            printf ("Mode yang ingin dipilih = "); 
                            scanf ("%d", &view_mode);
                            
                            if (view_mode == 1) {
                            printf ("\n <=======  Display Barang Dari Depan =======> \n");
                            displayForward(head);
                            } 
                            else if  (view_mode == 2 ) {
                            printf ("\n <=======  Display Barang Dari Belakang =======> \n");
                            displayBackward(head);
                            }
                            else { 
                                printf ("Pilihan tidak ada dalam pilihan") ; 
                                break ;
                            }

                            break;

                        case 5:
                            printf("Keluar dari aplikasi\n");
                            return 0;

                        default:
                            printf("Pilihan tidak valid. Pilih angka 1-5.\n");
                            break;
                    }

                    if (mode == 4) {
                        break; 
                    }
                }
                break;
            }

            default:
                printf("State tidak valid. Kembali ke login.\n");
                state = 'L';
                break;
        }
    }

    return 0;
}
