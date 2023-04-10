/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested,
and debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef char str10[10]; 
typedef char str20[20];
typedef char str15[15];
typedef char str30[30];

struct userTag {
		int userID;
		str10 password;
		str20 name;
		str30 address;
		int contact;          
	};

typedef struct userTag userTag;
	
struct itemTag {
	int productID;
	str20 itemName;
	str15 category;
	str30 description;
	int quantity;
	int price;  
	int sellerID;        
};

#define MAX_CART_SIZE 100

struct itemTag cart[MAX_CART_SIZE];

typedef struct itemTag itemTag;
struct transactionTag {
	str10 date;
	itemTag setItem[4];
	int buyerID;
	int tranSellerID;
	int total;     
};

typedef struct transactionTag transactionTag;

/*
	Purpose: display the welcome banner
*/
	void intro(){
	printf("\n");
	printf("_________________________________\n\n");
	printf("|   WELCOME TO SHOPPING APP     |\n");
	printf("_________________________________\n\n");
	}

/*
	Purpose: display the main menu
*/
	void mainMenu(){
	printf("\t     MAIN MENU\n\n");
	printf("     1 - Register as a User\n     2 - User Menu\n     3 - Admin Menu\n     4 - Exit\n\n");
	}

/*
	Purpose: append user text file to add the newly registered user
	@param : nMenu the condition of the selected menu
	@param : users is the structure that will contain the data of the users
	@param : ft is the flag when appending a new user
	@param : *fpUser is the User and file name that will be read, appended, and closed once nMenu is set to terminate
	@param : *fpItem is the Item and file name that will be read and closed once nMenu is set to terminate
	Pre-condition: the parameter is a valid structure, string, file pointer, and integer.
*/
	void writeTxt(int nMenu, userTag users, int ft, FILE *fpUser , FILE *fpItem){
	
	if (ft == 1){
		fclose(fpUser);
		fpUser = fopen("Users.txt", "a");
		fprintf(fpUser, "%d %s \n%s\n%s\n%d\n\n", users.userID, users.password, users.name, users.address, users.contact);
		ft = 0;
	} 	
		
		if (nMenu == 4){
			fclose(fpUser);
			fclose(fpItem);
		}
	}
	
/*
	Purpose: checks if the userID already exists in the users data
	Returns: either the (a) userID is invalid and will return a negative boolean value or
	         (b) the userID is valid and will return a positive boolean value
	@param : tempUserID is the integer that stores the desired userID to be added if valid
	@param : users is the structure array that will contain the data of the users
	@param : userCnt monitors the count of users added in the array
	Pre-condition: the parameter is a valid structure array and integer.
*/
	int checkUserID(int tempUserID, userTag users[], int userCnt){
		int nDup = 0;
		
		for (int i = 0; i < 99; i++){
			if (tempUserID == users[i].userID)
			nDup++;
			}
			
			
			if (nDup){
			printf("\n\tuserID already registered...\n\n");
				return 1;
			}
			else
			users[userCnt].userID = tempUserID;
				return 0;
	}

/*
	Purpose: checks if the userID is registered in the users data and if it does it will then check if the given password matches
	Returns: either the (a) userID is not registered and will return a negative boolean value or
	         (b) will return a positive boolean value when the userID is registered and password matches
	@param : users is the structure array that will contain the data of the users
	@param : tempUserID is the string that holds the userID that is given by the user.
	@param : tempPass is the string that holds the password that is given by the user.
	Pre-condition: the parameter is a valid structure array and string.
*/
	int logIn(userTag users[],int tempUserID, str10 tempPass){
		int nCon = 0;;
		
		for (int i = 0; i < 99; i++){
			if (tempUserID == users[i].userID)
					if (!(strcmp(tempPass, users[i].password)))
					nCon = 1;
			}
			
		return nCon;
	}

/*
	Purpose: collects information to be added in the user array
	@param : nMenu the condition of the selected menu
	@param : users is the structure array that will contain the data of the users
	@param : userCnt monitors the count of users added in the array
	@param : *fpUser is the User and file name that will be essential when calling the writeTxt function
	@param : *fpItem is the Item and file name that will be essential when calling the writeTxt function
	Pre-condition: the parameters contain valid values
*/	
	void regUser(int *nMenu, userTag users[], int *userCnt, FILE *fpUser , FILE *fpItem){
		*nMenu = 0;
		int tempUserID, ft = 1;
		

		printf("\n\n\t     REGISTER USER MENU\n\n");
		
		do {
			printf("Enter your userID: ");
			scanf("%d", &tempUserID);
		}while(checkUserID(tempUserID, users, *userCnt));

		printf("Enter your password: ");
		scanf("%s", users[*userCnt].password);
		printf("Enter your name: ");
		scanf("%s", users[*userCnt].name);
		printf("Enter your address: ");
		scanf("%s", users[*userCnt].address);
		printf("Enter your contact: ");
		scanf("%d", &users[*userCnt].contact);
		
		fpUser = fopen("Users.txt", "a");
		fprintf(fpUser, "%d %s \n%s\n%s\n%d\n\n", tempUserID, users[*userCnt].password, users[*userCnt].name, users[*userCnt].address, users[*userCnt].contact);
		fclose(fpUser);
		printf("\n\tRedirecting back to Main Menu...\n\n");
	}

/*
	Purpose: checks if the productID is registered in the items data
	Returns: either the (a) productID is not found and will return a negative boolean value or
	         (b) the productID is registered and will return a positive boolean value
	@param : tempProductID is the string that holds the productID that is given by the user.
	@param : *fpItem is the Item and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/	
	int checkProductID(int tempProductID,  FILE *fpItem){
		itemTag tempItem;
		int nFlag = 0;
		
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		
		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7) 
		{
			if(tempProductID == tempItem.productID)
				nFlag = 1;	
		}
			if (nFlag)
				printf("\n\tproductID already registered...\n\n");
			
			return nFlag;
	}

/*
	Purpose: collects information to be added in the item array
	@param : items is the structure array that will contain the data of the items
	@param : *fpItem is the Item and file name that will be appended
	@param : sellerID stores the sellerID for the item
	@param : *itemCnt monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/		
	void newItem(itemTag items[], FILE *fpItem, int sellerID, int *itemCnt){
		int tempProductID;
		
		printf("\n\n\t     ADD NEW ITEM\n\n");
		do {
			printf("Enter the ProductID: ");
			scanf("%d", &tempProductID);
		} while(checkProductID(tempProductID, fpItem));

		items[*itemCnt].productID = tempProductID;
		printf("Enter the Item Name: ");
		scanf(" %s", items[*itemCnt].itemName);
		printf("Enter the Item Category: ");
		scanf("%s", items[*itemCnt].category);
		printf("Enter Item Description: ");
		scanf("%s", items[*itemCnt].description);
		printf("Enter Item Quantity: ");
		scanf("%d", &items[*itemCnt].quantity);
		printf("Enter Item Price: ");
		scanf("%d", &items[*itemCnt].price);


		FILE *fp;
	
	   fp = fopen("Item.txt", "a");
	
	   fprintf(fp, "%d %s %s %s %d %d\n" , tempProductID, items[*itemCnt].itemName,items[*itemCnt].category,items[*itemCnt].description,items[*itemCnt].quantity,items[*itemCnt].price); // write values to the file
	
	   fclose(fp);
		
		*itemCnt = *itemCnt + 1;
		printf("\n\tRedirecting back to Main Menu...\n\n");
	}

/*
	Purpose: displays the products of the seller
	@param : *fpItem is the Item and file name that will be scanned
	@param : sellerID stores the sellerID for the item
	Pre-condition: the parameters contain valid values
*/
	void myProducts(itemTag items[], int sellerID, int max){
		
		printf("\n\n\t\t\t\t\t     MY PRODUCTS\n\n");
		printf("  Product ID  ||      Item Name      ||  Item Category  ||  Unit Price  || Unit Quantity\n\n");
		
			for (int i = 0; i < max; i++)
			printf("%14d  %21s  %17s  %14d  %14d\n",  items[i].productID, items[i].itemName, items[i].category, items[i].price, items[i].quantity);
	}

void editItem(itemTag items[], FILE *fpItem, int sellerID, int *itemCnt){
    
}

/*
	Purpose: checks if the productID exists in the items array
	Returns: either the (a) productID is not registered and will return a negative boolean value or
	         (b) will return a positive boolean value when the productID is found
	@param : items contains the item structure array
	@param : tempProdID contains the productID that is given by the user
	Pre-condition: the parameters contain valid values
*/	
	int checkProductIDarray(itemTag items[], int tempProdID, int *index){
		int nFlag;

		
		for(int i = 0; i < 20; i++){
			if(tempProdID == items[i].productID){
				nFlag = 1;
				*index = i;
				}
		}
		
		if(!(nFlag))
			printf("\n\tINVALID PRODUCTID\n\tRedirecting back to Main Menu...\n\n");
		
		return nFlag;
	}

/*
	Purpose: menu that decides if the given productID will proceed to editMenu() or not
	@param : items contains the item structure array
	@param : *fpItem is the Item and file name that will be essential when calling the checkProductIDarray()
	@param : sellerID stores the sellerID for the item
	Pre-condition: the parameters contain valid values
*/		
	void editStock(itemTag items[], FILE *fpItem, int sellerID, int *max){
		int tempProdID, nCon = 0, index;
		int productID;
		printf("\n\n\t     EDIT STOCK\n\n");
		printf("\n\n\t     MY PRODUCTS\n\n");
		
		myProducts(items, sellerID, *max);
		
		printf("Enter ProductID: ");
		scanf("%d", &tempProdID);
		
		nCon = checkProductIDarray(items, tempProdID, &index);
		printf("\nnCon%d\n", index);
		int nOpt;
		
                                             

			
			
			do{
				printf("\n\n\t     EDIT MENU\n\n");	
				printf("\n\n     1 - Replenish\n     2 - Change Price\n     3 - Change Item Name\n     4 - Change Category\n     5 - Change Description\n     6 - Finish Editing\n\n");
				printf("Select Option: ");
				scanf("%d", &nOpt);
			
				switch(nOpt){
				case 1: {
						printf("\n\n\t     Replenish\n\n");
						int addqty;
					    for (int i = 0; i < *max; i++) {
					        if (items[i].productID == tempProdID) {
					            index = i;             
					            break;
					        }
					        if (i == (*max - 1)) {
					            printf("Item not found.\n");
					            return;
					        }
					    }
					    printf("Enter the new Item Quantity: ");
    					scanf("%d", &items[index].quantity);
					    printf("\n\tItem with ProductID %d has been updated.\n\n", productID + 1);
					    
				}break;
				case 2: {
						printf("\n\n\t     Change Price\n\n");
						int addqty;
					    for (int i = 0; i < *max; i++) {
					        if (items[i].productID == tempProdID) {
					            index = i;             
					            break;
					        }
					        if (i == (*max - 1)) {
					            printf("Item not found.\n");
					            return;
					        }
					    }
					    printf("Enter the new Item Price: ");
    					scanf("%d", &items[index].price);
					    printf("\n\tItem with ProductID %d has been updated.\n\n", productID + 1);
					    
				}break;
				case 3: {
						printf("\n\n\t     Change Item Name\n\n");
						int addqty;
					    for (int i = 0; i < *max; i++) {
					        if (items[i].productID == tempProdID) {
					            index = i;             
					            break;
					        }
					        if (i == (*max - 1)) {
					            printf("Item not found.\n");
					            return;
					        }
					    }
					    printf("Enter the new Item Name: ");
    					scanf("%s", items[index].itemName);
					    printf("\n\tItem with ProductID %d has been updated.\n\n", productID + 1);
					    
				}break;
				case 4: {
						printf("\n\n\t     Change Category\n\n");
						int addqty;
					    for (int i = 0; i < *max; i++) {
					        if (items[i].productID == tempProdID) {
					            index = i;             
					            break;
					        }
					        if (i == (*max - 1)) {
					            printf("Item not found.\n");
					            return;
					        }
					    }
					    printf("Enter the new Item Category: ");
    					scanf("%s", items[index].category);
					    printf("\n\tItem with ProductID %d has been updated.\n\n", productID + 1);
					    
				}break;
				case 5: {
						printf("\n\n\t     Change Description\n\n");
						int addqty;
					    for (int i = 0; i < *max; i++) {
					        if (items[i].productID == tempProdID) {
					            index = i;             
					            break;
					        }
					        if (i == (*max - 1)) {
					            printf("Item not found.\n");
					            return;
					        }
					    }
					    printf("Enter the new Item Description: ");
    					scanf("%s", items[index].description);
					    printf("\n\tItem with ProductID %d has been updated.\n\n", productID + 1);
					    
				}break;
				
			}
				printf("\n\n%d\n\n", items->quantity);
			}while(nOpt != 6);
		               
 		               
		    
			
	}
	                                             
	void printItems(FILE *fpItem, int max, itemTag items[],int sellerID){
	     
		fclose(fpItem);                                             
		fpItem = fopen("Items.txt", "w");

		for (int i = 0; i < max; i++)
		fprintf(fpItem, "%d %d\n%s\n%s\n%s\n%d %d\n\n", items[i].productID, sellerID, items[i].itemName, items[i].category, items[i].description, items[i].quantity, items[i].price);
}
	
/*
	Purpose: displays the low stock products of the seller
	@param : *fpItem is the Item and file name that will be scanned
	@param : sellerID stores the sellerID for the item
	Pre-condition: the parameters contain valid values
*/	
	void lowStock(FILE *fpItem, itemTag items[], int sellerID, int max){
		itemTag tempItem;
		char cCon = 'N';
		
		printItems(fpItem, max, items, sellerID);

		printf("\n\n\t     LOW STOCK\n\n");
		
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7)
		if(sellerID == tempItem.sellerID)
		if(tempItem.quantity < 5 && cCon == 'N'){
		printf("Product ID: %d\t Item Name: %s\t  Item Category: %s\t Unit Price: %d\t Unit Quantity: %d\n",  tempItem.productID, tempItem.itemName, tempItem.category, tempItem.price, tempItem.quantity);
		printf("\n\nPress N to see next product \nPress X to exit: ");
		scanf(" %c", &cCon);
		}

	}
	
/*
	Purpose: scans the items text file
	@param : *fpItem is the Item and file name that will be scanned
	@param : items is the structure array that stores all items
	@param : sellerID stores the sellerID for the item
	@param : *itemCnt monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/		
	void scanItems( FILE *fpItem, itemTag items[],int sellerID, int *itemCnt){
		itemTag tempItem;
		
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7){
			if(sellerID == tempItem.sellerID){
				items[*itemCnt].productID =  tempItem.productID;
				items[*itemCnt].sellerID = tempItem.sellerID;
				strcpy(items[*itemCnt].itemName, tempItem.itemName);
				strcpy(items[*itemCnt].category, tempItem.category);
				strcpy(items[*itemCnt].description, tempItem.description);
				items[*itemCnt].quantity =  tempItem.quantity;
				items[*itemCnt].price = tempItem.price;
				*itemCnt = *itemCnt + 1;
			}
		}
	}


/*
	Purpose: displays the sell menu
	@param : *nMenu the condition of the selected menu
	@param : sellerID stores the sellerID for the item
	@param : transactions[] contains all the transaction data
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/	
	void sellMenu(int *nMenu, int sellerID, transactionTag transactions[], FILE *fpUser , FILE *fpItem){
		int itemCnt= 0;
		itemTag items[19];
		int nOpt;

		*nMenu = 0;
		scanItems( fpItem, items, sellerID, &itemCnt);
		
		do{
			printf("\n\n\t     SELL MENU\n\n");	
			printf("\n\n     1 - Add New Item\n     2 - Edit Stock\n     3 - Show My Products\n     4 - Show My Low Stock Products\n     5 - Exit Sell Menu\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);
			
			switch(nOpt){
				case 1: newItem(items, fpItem, sellerID, &itemCnt); break;
				case 2: editStock(items, fpItem, sellerID, &itemCnt); break;
				case 3: myProducts(items, sellerID, itemCnt); break;
				case 4: lowStock(fpItem, items, sellerID, itemCnt); break;
				case 5: printItems(fpItem,itemCnt, items, sellerID); printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		}while(nOpt != 5);	

	}

/*
	Purpose: display all products
	@param : *fpItem is the Item and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/		
	void allProducts(FILE *fpItem){
		itemTag tempItem;
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		printf("\n\n\t\t\t     SHOW PRODUCTS\n\n");
		
		printf("  Product ID  ||      Item Name      ||  Item Category  ||  Unit Price  || Unit Quantity\n\n");
		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7)
			printf("%14d  %22s  %17s  %14d  %14d\n",  tempItem.productID, tempItem.itemName, tempItem.category, tempItem.price, tempItem.quantity);
	}

/*
	Purpose: display all products by a specific seller
	@param : *fpItem is the Item and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/			
	void specificSeller(FILE *fpItem){
		itemTag tempItem;
		int tempSeller;
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		printf("Enter Specific Seller: ");
		scanf("%d", &tempSeller);
		
		printf("\n\n\t     %d PRODUCTS\n\n", tempSeller);
		
		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7)
			if(tempSeller == tempItem.sellerID)
				printf("Product ID: %d\t Item Name: %s\t  Item Category: %s\t Unit Price: %d\t Unit Quantity: %d\n",  tempItem.productID, tempItem.itemName, tempItem.category, tempItem.price, tempItem.quantity);
	}

/*
	Purpose: display all products by a specific category
	@param : *fpItem is the Item and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/		
	void specificCategory(FILE *fpItem){
		itemTag tempItem;
		str15 tempCat;
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		printf("Enter Specific Seller: ");
		scanf("%s", tempCat);
		
		printf("\n\n\t     %s PRODUCTS\n\n", tempCat);
		
		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7)
			if(!(strcmp(tempCat, tempItem.category)))
				printf("Product ID: %d\t Item Name: %s\t  Item Category: %s\t Unit Price: %d\t Unit Quantity: %d\n",  tempItem.productID, tempItem.itemName, tempItem.category, tempItem.price, tempItem.quantity);
	}

/*
	Purpose: display all products by a specific name
	@param : *fpItem is the Item and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/	
	void specificName(FILE *fpItem){
		itemTag tempItem;
		str20 tempName;
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		printf("Enter Specific Name: ");
		scanf("%s", tempName);
		
		printf("\n\n\t     %s PRODUCT\n\n", tempName);
		
		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7)
			if(!(strcmp(tempName, tempItem.itemName)))
				printf("Product ID: %d\t Item Name: %s\t  Item Category: %s\t Unit Price: %d\t Unit Quantity: %d\n",  tempItem.productID, tempItem.itemName, tempItem.category, tempItem.price, tempItem.quantity);
	}

/*
	Purpose: add items to cart[]
	@param : itemArray[] contains all stored items
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the array to avoid garbage values
	@param : *cartCtr monitors the count of items added in the cart
	Pre-condition: the parameters contain valid values
*/	



/*
	Purpose: checks if the given sellerID is stored in the cart[] and removes it from the array
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the array to avoid garbage values
	@param : tempSellerID contains the productID that is given by the user
	@param : *index stores the index
	Pre-condition: the parameters contain valid values
*/	
	void checkCart(itemTag cart[],int *max, int tempSellerID){
		itemTag tempCart[*max];
		int l = 0, newMax;
		newMax = *max;
		newMax--;
		
		for(int i = 0; i < *max; i++){
			if (cart[i].sellerID == tempSellerID){
				i++;
				newMax--;
			}
			else{
				tempCart[l].productID = cart[i].productID;
				strcpy(tempCart[l].itemName, cart[i].itemName);
				strcpy(tempCart[l].category, cart[i].category);
				strcpy(tempCart[l].description, cart[i].description);
				tempCart[l].quantity = cart[i].quantity;
				tempCart[l].price = cart[i].price;
				tempCart[l].sellerID = cart[i].sellerID;
				l++;
			}
		}
			
			for(int i = 0; i < newMax; i++){
				cart[i].productID = tempCart[i].productID;
				strcpy(cart[i].itemName, tempCart[i].itemName);
				strcpy(cart[i].category, tempCart[i].category);
				strcpy(cart[i].description, tempCart[i].description);
				cart[i].quantity = tempCart[i].quantity;
				cart[i].price = tempCart[i].price;
				cart[i].sellerID = tempCart[i].sellerID;
			}
			
			*max = newMax;
	}

	void removeProductID(itemTag cart[],int *max, int tempProductID){
		itemTag tempCart[*max];
		int l = 0, newMax;
		newMax = *max;
		newMax--;
		
		for(int i = 0; i < *max; i++){
			printf("%d productID %d temp prodID", cart[i].productID, tempProductID);
				if (cart[i].productID == tempProductID){
					i++;
					newMax--;
				}
				else{
					tempCart[l].productID = cart[i].productID;
					strcpy(tempCart[l].itemName, cart[i].itemName);
					strcpy(tempCart[l].category, cart[i].category);
					strcpy(tempCart[l].description, cart[i].description);
					tempCart[l].quantity = cart[i].quantity;
					tempCart[l].price = cart[i].price;
					tempCart[l].sellerID = cart[i].sellerID;
					l++;
				}
		}
			
			for(int i = 0; i < newMax; i++){
				cart[i].productID = tempCart[i].productID;
				strcpy(cart[i].itemName, tempCart[i].itemName);
				strcpy(cart[i].category, tempCart[i].category);
				strcpy(cart[i].description, tempCart[i].description);
				cart[i].quantity = tempCart[i].quantity;
				cart[i].price = tempCart[i].price;
				cart[i].sellerID = tempCart[i].sellerID;
			}
			
			*max = newMax;
	}

/*
	Purpose: displays the edit cart menu and manages the cart
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the array to avoid garbage values
	Pre-condition: the parameters contain valid values
*/		
	void editCart(itemTag cart[], int *max){
		int tempProductID, tempSellerID, nOpt, nQuan;
		
		do{
			printf("\n\n\t     EDIT CART MENU\n\n");	
			printf("\n\n     1 - Remove All Items from Seller\n     2 - Remove Specific Item\n     3 - Edit Quantity\n     4 - Finish Edit Cart\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);
			
			switch(nOpt){
				case 1: { 	printf("Enter SellerID: ");
							scanf("%d", &tempSellerID);
							checkCart(cart, max, tempSellerID);
							printf("\nCart is updated\n");
						}; break;
				case 2: { 	printf("Enter ProductID: ");
							scanf("%d", &tempProductID);
							removeProductID(cart, max, tempSellerID);
							printf("\nCart is updated\n");
						}; break;break;
				case 3: {	printf("Enter ProductID: ");
							scanf("%d", &tempSellerID);
							printf("Enter New Quantity: ");
							scanf("%d", &nQuan);
							
							for(int i = 0; i < *max; i++)
								if(tempSellerID == cart[i].productID)
									cart[i].quantity = nQuan;
						}; break;
				case 4: printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		
		}while(nOpt != 4);	
	}
	
	void checkOutAll(itemTag cart[],int  max,transactionTag transaction[]){
		
	}
	
	void checkOutSeller(){
	}
	
	void checkOutItem(){
	}

/*
	Purpose: displays the check out menu and calls the function that the user requires
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the array to avoid garbage values
	Pre-condition: the parameters contain valid values
*/		
	void checkOutMenu(itemTag cart[], int max){
		transactionTag transaction[19];
		str10 tempDate;
		int nOpt;
		
		printf("Enter tempDate: ");
		scanf("%s", tempDate);
		
		do{
			printf("\n\n\t     CHECK OUT MENU\n\n");	
			printf("\n\n     1 - All\n     2 - By a Specific Seller\n     3 - Specific Item\n     4 - Exit Check Out\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);
			
			switch(nOpt){
				case 1: checkOutAll(cart, max, transaction); break;
				case 2: checkOutSeller(); break;
				case 3: checkOutItem(); break;
				case 4: printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		}while(nOpt != 4);
	}
	
/*
	Purpose: scans all items in the Items.txt
	@param : itemArray[] is the array that contains all items available to be bought
	@param : *fpItem is the Item and file name that will be scanned
	@param : *ctr monitors the count of items added in the cart
	Pre-condition: the parameters contain valid values
*/	
	void scanBuyItems(itemTag itemArray[],FILE *fpItem, int *ctr){
		itemTag tempItem;
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
	
		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7){
			itemArray[*ctr].productID = tempItem.productID;
			itemArray[*ctr].sellerID = tempItem.sellerID;
			strcpy(itemArray[*ctr].itemName, tempItem.itemName);
			strcpy(itemArray[*ctr].category, tempItem.category);
			strcpy(itemArray[*ctr].description, tempItem.description);
			itemArray[*ctr].quantity = tempItem.quantity;
			itemArray[*ctr].price = tempItem.price;
			*ctr = *ctr + 1;
		}
	}
	
/*
	Purpose: rewrite the Cart.txt file
	@param : *fpItem is the Item and file name that will be scanned
	@param : *fpCart is the cart and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/	
	void updateCart(itemTag cart[], int max,  FILE *fpCart){
		fclose(fpCart);
		fpCart = fopen("Cart.txt", "w");
		
		for(int i = 0; i < max; i++)
			fprintf(fpCart, "%d %s %s %s %d %d %d\n", cart[i].productID, cart[i].itemName, cart[i]. category, cart[i].description, cart[i].quantity, cart[i].price, cart[i].sellerID);
	}

/*
	Purpose: displays the buy menu and calls the function that the user requires
	@param : *fpItem is the Item and file name that will be scanned
	@param : *fpCart is the cart and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/	

	void buyMenu(int sales, itemTag items[],FILE *fpItem, FILE *fpCart,int *itemCnt){
		int nOpt, ctr = 0, cartCtr = 0;
		itemTag cart[9];
		itemTag itemArray[20];
		int ID;
		
		scanBuyItems(itemArray, fpItem, &ctr);
		
		do{
			printf("\n\n\t     BUY MENU\n\n");	
			printf("\n\n     1 - View All Products\n     2 - Show All Products by a Specific Seller\n     3 - Search Products by Category\n     4 - Show Products by Name\n     5 - Add to cart\n     6 - Edit Cart\n     7 - Check Out Menu\n     8 - Exit Buy Menu\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);

			int productID, quantity, index;
					    bool found = false;
			int option, sellerID, i, j;
			switch(nOpt){
				case 1: allProducts(fpItem); break;
				case 2: specificSeller(fpItem); break;
				case 3: specificCategory(fpItem); break;
				case 4: specificName(fpItem); break;
				case 5: 
						
					    
					
					    printf("\n\n\t     ADD TO CART\n\n");
					    printf("Enter the ProductID of the item to add to cart: ");
					    scanf("%d", &productID);
					
							int found = 0;
						    char line[100];
						    int quanti = 0;
						    int prodID, qty, pri;
							char desc[100],name[100],categ[100];
						    
						
							FILE *fp;
							   int value;
							
							   fp = fopen("Item.txt", "r"); 
							
							   if (fp == NULL) { 
							      printf("Unable to open file\n");
							      return 1;
							   }
							
							   while (fscanf(fp, "%d %s %s %s %d %d", &prodID, name,categ,desc,&qty,&pri) != EOF) { 
							      if(prodID == productID){
						        	found = 1;
						        	break;
									}
							   }
							
							   fclose(fp); 
							if(found == 1){
								printf("Enter quantity: ");
								scanf("%d", &quanti);
								
								if(quanti <= 0 || quanti > qty){
									printf("Invalid Quantity!");
								}else{
									FILE *fp;
	
								   fp = fopen("Cart.txt", "a"); 
								   fprintf(fp, "%d %s %s %s %d %d\n" , prodID, &name,&categ,&desc,qty,pri); 
									
									sales = sales + (quanti * pri);
								   fclose(fp); 
								}
								
								
							}else{
								
							}
					    break; 
				case 6:                        
				
				if(true){
					FILE *fp;
							   int value;
							
							   fp = fopen("Cart.txt", "r");
							
							   if (fp == NULL) { 
							      printf("Unable to open file\n");
							      return 1;
							   }
								printf("\n\n\t     CART ITEMS\n\n");
								printf("PRODUCTID NAME CATEGORY DESCRIPTION QUANTITY PRICE\n");
							   while (fscanf(fp, "%d %s %s %s %d %d\n", &prodID, name,categ,desc,&qty,&pri) != EOF) {
							      printf("%d %s %s %s %d %d\n", prodID, &name,&categ,&desc,qty,pri);
							   }
							
							   fclose(fp); 
				}
			    printf("\n\n\t     EDIT CART\n\n");
			    printf("1. Remove all items from a specific seller.\n");
			    printf("2. Remove a specific item from the cart.\n");
			    printf("3. Finish editing cart.\n");
			    printf("Enter your option: ");
			    scanf("%d", &option);
				
			    switch(option) {
			        case 1:
			        	if(true){
			        		FILE *file_pointer;
			        		file_pointer = fopen("Cart.txt", "w");
					    
					    fclose(file_pointer);
					    printf("All items remove!");
						}
					    
			            break;
			        case 2:
			            
			            if(true){
						    int line_number = 0;
						    printf("Enter the line you want to remove: ");
							scanf("%d", &line_number);
						    
						    FILE *fp1 = fopen("Cart.txt", "r");
						    if (fp1 == NULL) {
						        printf("Failed to open file.\n");
						        return 0;
						    }
						
						    int num_lines = 0;
						    char ch;
						    while ((ch = fgetc(fp1)) != EOF) {
						        if (ch == '\n') {
						            num_lines++;
						        }
						    }
						    if (line_number < 1 || line_number > num_lines) {
						        printf("Invalid line number.\n");
						        fclose(fp1);
						        return 0;
						    }
						
						    FILE *tmp = fopen("tmp.txt", "w");
						    if (tmp == NULL) {
						        printf("Failed to create temporary file.\n");
						        fclose(fp1);
						        return 0;
						    }
						
						    rewind(fp1);
						
						    int current_line = 1;
						    char buffer[1024];
						    while (fgets(buffer, sizeof(buffer), fp1) != NULL) {
						        if (current_line != line_number) {
						            fputs(buffer, tmp);
						        }
						        current_line++;
						    }
						
						    fclose(fp1);
						    fclose(tmp);
							
						    if (remove("Cart.txt") != 0) {
						        printf("Failed to delete original file.\n");
						        return 0;
						    }
						    if (rename("tmp.txt", "Cart.txt") != 0) {
						        printf("Failed to rename temporary file.\n");
						        return 0;
						    }
						
						    printf("Line %d removed successfully.\n", line_number);
					
						}
			            break;
			        case 3:
			            printf("Exiting edit cart...\n");
			            break;
			    }
				break;
				case 7: printf("Checked out successfully.\n");
						break;
				case 8: printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		}while(nOpt != 8);
	}
/*
	Purpose: displays the user menu and calls the function that the user requires
	@param : sellerID stores the sellerID for the item
	@param : transactions[] contains all the transaction data
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/		
	void userMenu(int sales,int *itemCnt,itemTag items[],int sellerID, transactionTag transactions[], FILE *fpUser , FILE *fpItem, FILE *fpCart){
		int nMenu;
		
		do{	
			printf("\n\n\t     USER MENU\n\n");
			printf("\n\n     1 - Sell Menu\n     2 - Buy Menu\n     3 - Exit User Menu\n\n");
			printf("Select Menu: ");
			scanf("%d", &nMenu);
			
			switch(nMenu){
				case 1: sellMenu(&nMenu, sellerID, transactions, fpUser, fpItem); break;
				case 2: buyMenu(sales,items,fpItem, fpCart,itemCnt); break;
				case 3: printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		}while(nMenu != 3);
	}

/*
	Purpose: checks if the given login details are valid
	@param : *nMenu the condition of the selected menu
	@param : users is the structure array that will contain the data of the users
	@param : transactions[] contains all the transaction data
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/		
	void logInUserMenu(int sales, itemTag items[],int *nMenu, userTag users[], transactionTag transactions[], FILE *fpUser , FILE *fpItem, FILE *fpCart){
		int tempUserID;
		str10 tempPass;
		int itemCnt = 0;
		printf("\nUserID:");
		scanf("%d", &tempUserID);
		printf("Password:");
		scanf("%s", tempPass);

		if (!(logIn(users, tempUserID ,tempPass))){
			printf("\nInvalid UserID or Password\n");
			printf("\n\tRedirecting back to Main Menu...\n\n");
		}
		else
			userMenu(sales,&itemCnt,items,tempUserID,transactions, fpUser, fpItem, fpCart);
	}

/*
	Purpose: checks if the password is valid for admin access
	Returns: either the (a) password is invalid and will return a negative boolean value or
	         (b) will return a positive boolean value when the password is valid
*/	
	int adminAccess(){
		str10 tempPass;
		int nCon = 0;
		
		printf("Admin Password: ");
		scanf("%s", tempPass);
		
		if(!(strcmp(tempPass, "H3LLo?"))){
			nCon = 1;
		}else if(!(strcmp(tempPass, "admin2"))){
			nCon = 1;
		}else if(!(strcmp(tempPass, "admin3"))){
			nCon = 1;
		}
		else
			printf("\n\tUnauthorized Access Not Allowed\n\n");
			
		return nCon;
			
	}

/*
	Purpose: displays all users
	@param : *fpUser is the User and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/	
	void showAllUsers(FILE *fpUser){
		userTag tempUser;
		
		fclose(fpUser);
		fpUser = fopen("Users.txt", "r");
		
		printf("    User ID    ||     Password     ||       Name      ||        Address        ||   Phone Number\n\n");
		while(fscanf(fpUser, "%d %s %s %s %d", &tempUser.userID, tempUser.password, tempUser.name, tempUser.address, &tempUser.contact) == 5)
			printf("%15d  %18s  %17s  %23s  %15d\n", tempUser.userID, tempUser.password, tempUser.name, tempUser.address, tempUser.contact);
		fclose(fpUser);
	}
	
/*
	Purpose: displays all sellers
	@param : *fpItem is the User and file name that will be scanned
	@param : *fpUser is the User and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/		
	void showAllSellers(FILE *fpItem, FILE *fpUser){
//	struct tempSeller {
//		int itemSale;  
//		int ID;        
//		};
//		
//		struct tempSeller tempSeller;
//		itemTag tempItem;
//		int itemCount;
//		
//		fclose(fpItem);
//		fclose(fpUser);
//		fpUser = fopen("Users.txt", "r");
//		fpItem = fopen("Item.txt", "r");
//		
//		while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7)
//			itemCount++;
//		
//		for(int i = 0; i < itemCount; i++){
//			if(tempSeller.ID != tempItem.sellerID){
//				tempSeller.ID = tempItem.sellerID;
//				while(fscanf(fpItem, "%d %d %s %s %s %d %d", &tempItem.productID, &tempItem.sellerID, tempItem.itemName, tempItem.category, tempItem.description, &tempItem.quantity, &tempItem.price) == 7){
//					if (tempSeller.ID == tempItem.sellerID)
//					tempSeller.itemSale++;
//				}
//			}
//		}
		userTag tempUser;
		
		fclose(fpUser);
		fpUser = fopen("Users.txt", "r");
		
		printf("    User ID    ||     Password     ||       Name      ||        Address        ||   Phone Number\n\n");
		while(fscanf(fpUser, "%d %s %s %s %d", &tempUser.userID, tempUser.password, tempUser.name, tempUser.address, &tempUser.contact) == 5)
			printf("%15d  %18s  %17s  %23s  %15d\n", tempUser.userID, tempUser.password, tempUser.name, tempUser.address, tempUser.contact);
		fclose(fpUser);
	}

/*
	Purpose: displays total sales

	Pre-condition: the parameters contain valid values
*/	
	void showTotalSales(int sales){
	printf("Total Sales: %d", sales);	
	}

/*
	Purpose: displays sellers sales

	Pre-condition: the parameters contain valid values
*/	
	void showSellers(int sales){
		showTotalSales(sales);
	}

/*
	Purpose:

	Pre-condition: the parameters contain valid values
*/	
	void showShopaholics(){
	printf("Shopaholics Func");
	}

/*
	Purpose: displays the admin menu and calls the function that the user requires
	@param : *nMenu the condition of the selected menu
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/		
	void adminMenu(int sales,int *nMenu, FILE *fpUser, FILE *fpItem){
		int nOpt;
		
		*nMenu = 0;
		
		if (adminAccess()){
			do{
				printf("\n\n\t     ADMIN MENU\n\n");	
				printf("\n\n     1 - Show All Users\n     2 - Show All Sellers\n     3 - Show Total Sales in Given Duration\n     4 - Show Sellers Sales\n     5 - Show Shopaholics\n     6 - Back to Main Menu\n\n");
				printf("Select Option: ");
				scanf("%d", &nOpt);
				
				switch(nOpt){
					case 1: showAllUsers(fpUser); break;
					case 2: showAllSellers(fpItem,fpUser); break;
					case 3: showTotalSales(sales); break;
					case 4: showSellers(fpItem); break;
					case 5: showShopaholics(fpItem); break;
					case 6: printf ("\n"); break;
					default: printf("\nINVALID INPUT\n\n"); break;
				}
			}while(nOpt != 6);
		}
			
	}

/*
	Purpose: close all opened file pointers
	@param : *nMenu the condition of the selected menu
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	@param : *fpCart is the Cart and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/	
	void nExit(int *nMenu, FILE *fpUser, FILE *fpItem,  FILE *fpCart){
		fclose(fpUser);
		fclose(fpItem);
		fclose(fpCart);
		*nMenu = 4;
	}

int main(){
	int cartSize = 0;
	int sales = 0;
	int line_number = 1, count = 1;
	userTag users[99];
	itemTag items[99];
	transactionTag transactions[10];
	int nMenu, userCnt = 0;
	FILE *fpUser, *fpItem, *fpCart;
	fpUser = fopen("Users.txt", "w");
	fpItem = fopen("Items.txt", "w");
	
	
	intro();
	
	do{	
		mainMenu();
		
		printf("Select Menu: ");
		scanf("%d", &nMenu);	
		
		switch(nMenu){
			case 1: regUser(&nMenu, users, &userCnt, fpUser, fpItem); userCnt++; break;
			case 2: logInUserMenu(sales,items,&nMenu, users, transactions, fpUser, fpItem, fpCart); break;
			case 3: adminMenu(&sales,&nMenu, fpUser, fpItem); break;
			case 4: nExit(&nMenu, fpUser, fpItem, fpCart); break;
			default: printf("\nINVALID INPUT\n\n"); break;
		}
	}while(nMenu != 4);

	
	return 0;
}
