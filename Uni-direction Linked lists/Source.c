//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Gary Muller
// Fall 2016
// CS 315 Assignment 2
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A program that creates and utilizes a uni-directional linked list, it will utilize a struct type def
// 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Header files standard libraries and classes
#include <stdio.h> //standard io functions for C
#include <stdlib.h> //used for better malloc() function
#include <ctype.h> //used for tolower() function
#include <stdbool.h> //used for bool types


//Gloabal Variables and Defines
//Structure Type Definition for a linked list structure
typedef struct linkedList
{
	int itemData;
	struct linkedList *nextItem;
}LINKED_LIST_ITEM;

//Global pointer to list start
LINKED_LIST_ITEM *startItemPtr = NULL;


//Function Prototypes
int addItem(int);
int removeItem(int);
int printList();
LINKED_LIST_ITEM* checkList(int);


main()
{
	//Variable Declarations
	char activity = ' ';
	int tempItemData = -1;

	while (activity != 'q')
	{
		//query user for input on next action and normalize input
		printf("What do you want to do? [Enter i for insert, r for remove, or q to quit]: ");
		scanf_s(" %c", &activity);
		activity = tolower(activity); //make all inputs lowercase

		//use input as a case in switch

		switch (activity)
		{
		case 'i':
			//insert case
			printf("Value to be inserted: ");
			scanf_s(" %d", &tempItemData);
			addItem(tempItemData);
			printList();
			break;

		case 'r':
			//remove case
			printf("Value to be removed: ");
			scanf_s(" %d", &tempItemData);
			removeItem(tempItemData);
			printList();
			break;

		case 'q':
			//quit case
			printf("Your final list was:");
			printList();
			printf("\n\nBye");
			break;

		default:
			printf("Please only use the specified inputs: i for insert, r for remove, or q to quit\n\n");
			break;
		}//switch

	}//while

}//main


//function that adds an item to the list in an ordered fashion
int addItem(int newItemData)
{
	//temporary pointer needed for traversal
	LINKED_LIST_ITEM *traversalLeaderPtr = startItemPtr;
	LINKED_LIST_ITEM *traversalFollowPtr = startItemPtr;
	LINKED_LIST_ITEM *newListItemPtr = NULL;
	bool inserted = false;

	//get memory and edit the item
	newListItemPtr = malloc(sizeof(LINKED_LIST_ITEM));
	newListItemPtr->itemData = newItemData;
	newListItemPtr->nextItem = NULL;


	//check if the list is empty
	if (traversalLeaderPtr == NULL) //first entry on list
	{
		startItemPtr = newListItemPtr;
		return 1;
	}//if
	//check if the number is already in the list
	else if (checkList(newItemData) != NULL)
	{
		printf("ERR: The list already has %d in it\n", newItemData);
		return 1;
	}//elseif
	else //not first entry on list and not in the list already
	{
		//set the leader in the lead to start the insertion
		if (startItemPtr->nextItem != NULL)
		{
			traversalLeaderPtr = traversalLeaderPtr->nextItem;
		}

		while (traversalLeaderPtr != NULL && inserted != true)//loop to traverse list
		{
			//insert at the end of the list
			if ((traversalLeaderPtr->nextItem == NULL) && (traversalLeaderPtr->itemData < newItemData))
			{
				traversalLeaderPtr->nextItem = newListItemPtr; //set the privious item's nextItem ptr to the new item
				inserted = true;
			}//if

			//discovered location is at the start
			else if ((traversalFollowPtr == startItemPtr) && (traversalLeaderPtr->itemData > newItemData))
			{
				newListItemPtr->nextItem = startItemPtr; //set the new items nextItem ptr to the next item
				startItemPtr = newListItemPtr; //set the start equal to the new starting item
				inserted = true;
			}//elseif

			//regular insertion into list
			else if (traversalLeaderPtr->itemData > newItemData)
			{
				newListItemPtr->nextItem = traversalFollowPtr->nextItem; //set the new items nextItem ptr to the next item
				traversalFollowPtr->nextItem = newListItemPtr; //set the previous item's nextItem ptr to the new item
				inserted = true;
			}//else

			traversalLeaderPtr = traversalLeaderPtr->nextItem; //traversal
			traversalFollowPtr = traversalFollowPtr->nextItem;

		}//while
		return 1;
	}//else

	return 0;
}//addItem()


//functin that removes a specific item from the list
int removeItem(int itemdata)
{
	//temporary pointer needed for traversal
	LINKED_LIST_ITEM *traversalPtr = startItemPtr;

	//check if the list is empty
	if (traversalPtr == NULL)
	{
		//notify the user they tried to remove from an empty list
		printf("The list is currently empty\n");
		//return success
		return 1;
	}//if

	//check if item to be removed is in the list
	LINKED_LIST_ITEM *removalPtr = checkList(itemdata);

	//perform the removal if the item exists
	if (removalPtr != NULL)
	{
		if (removalPtr == startItemPtr)
		{
			//if the first item is being removed
			startItemPtr = removalPtr->nextItem;
		}//if
		else
		{
			while (traversalPtr->nextItem != removalPtr)
			{
				traversalPtr = traversalPtr->nextItem;
			}//while

			//fix the list so that the item before the one removed points to the one after
			traversalPtr->nextItem = removalPtr->nextItem;
		}//else

		//free the memory space
		free(removalPtr);

		//return success
		return 1;
	}//if
	else if (removalPtr == NULL)
	{
		//notify the user that the item was not found in the list
		printf("%d was not found in the list\n", itemdata);
		//return success
		return 1;
	}//elseif

	return 0;

}//removeItem()


//function that traverses the linked list and prints out every item
int printList()
{
	//temporary pointer needed for traversal
	LINKED_LIST_ITEM *traversalPtr = startItemPtr;

	//check if the list is empty
	if (traversalPtr == NULL)
	{
		return 1;
	}
	else //the list does not start with NULL ie: its not empty
	{
		do
		{
			printf("%d", traversalPtr->itemData);
			if (traversalPtr->nextItem != NULL)
			{
				printf(" -> ");
			}
			traversalPtr = traversalPtr->nextItem;
		} while (traversalPtr != NULL);
		printf("\n\n");
		return 1;

	}//else
	return 0;
}//printList


//function that searches the list for a specified number and returns a pointer to the number if it finds it
LINKED_LIST_ITEM* checkList(int checkNum)
{
	//if the list is empty
	if (startItemPtr == NULL)
	{
		return startItemPtr;
	}

	//temporary pointer needed for traversal if the list is not empty
	LINKED_LIST_ITEM *traversalPtr = startItemPtr;

	while (traversalPtr != NULL)
	{
		if (traversalPtr->itemData == checkNum)
		{
			return traversalPtr;
		}
		else if (traversalPtr->nextItem == NULL)
		{
			return NULL;//item not found
		}
		traversalPtr = traversalPtr->nextItem;
	}
}