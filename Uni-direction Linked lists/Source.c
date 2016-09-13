//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Gary Muller
// Fall 2016
// CS 315 Assignment 2
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A program that creates and utilizes a uni-directional linked list, it will utilize a struct type def
// and includes an add and remove functionality
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
		//"payload"
		int itemData;
		//pointer to next item
		struct linkedList *nextItem;
	}LINKED_LIST_ITEM;

	//Global pointer to list start
	LINKED_LIST_ITEM *startItemPtr = NULL;
//


//Function Prototypes
int addItem(int);
int removeItem(int);
int printList();
LINKED_LIST_ITEM* checkList(int);
//


main()
{
	//Variable Declarations
	char activity = ' ';
	int tempItemData = -1;

	//loop for program body
	while (activity != 'q')
	{
		//query user for input on next action and normalize input
		printf("What do you want to do? [Enter i for insert, r for remove, or q to quit]: ");
		scanf(" %c", &activity);
		activity = tolower(activity); //make all inputs lowercase

		//use input as a case in switch

		switch (activity)
		{
		case 'i':
			//insert case
			//query user for number to add
				printf("Value to be inserted: ");
				scanf(" %d", &tempItemData);
			//add number to list
				addItem(tempItemData);
			//print new list for user
				//list header
				printf("\nThe list is currently:\n");
				printList();
			break;

		case 'r':
			//remove case
			//only bother asking for a removal input if there is anything that could be removed
			if (startItemPtr != NULL)
			{
				//query user for number to remove
					printf("Value to be removed: ");
					scanf(" %d", &tempItemData);
				//remove number from list
					removeItem(tempItemData);
				//print new list
					//list header
					printf("\nThe list is currently:\n");
					printList();
			}
			//the list is already empty
			else
			{
				//inform the user they are a fool
				printf("The list is currently empty\n\n");
			}
			
			break;

		case 'q':
			//quit case
			//print the final list
				printf("Your final list was: ");
				printList();
			//quit gracefully
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
	//temporary pointers needed for traversal
	LINKED_LIST_ITEM *traversalLeaderPtr = startItemPtr;
	LINKED_LIST_ITEM *traversalFollowPtr = startItemPtr;
	LINKED_LIST_ITEM *newListItemPtr = NULL;

	//get memory and edit the new item
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
		//make the leader pointer lead if there is more than one item in the list
		if (startItemPtr->nextItem != NULL)
		{
			traversalLeaderPtr = traversalLeaderPtr->nextItem;
		}

		//variable to end the loop when the number has been inserted
		bool inserted = false;

		//loop for list traversal
		while (traversalLeaderPtr != NULL && inserted != true)
		{
			//insert at the end of the list
			if ((traversalLeaderPtr->nextItem == NULL) && (traversalLeaderPtr->itemData < newItemData))
			{
				//set the privious item's 'nextItem' pointer to the new item
				traversalLeaderPtr->nextItem = newListItemPtr;
				//end the loop
				inserted = true;
			}//if

			//discovered location is at the start
			else if ((traversalFollowPtr == startItemPtr) && (startItemPtr->itemData > newItemData))
			{
				//set the new items nextItem pointer to the next item
				newListItemPtr->nextItem = startItemPtr;
				//set the start equal to the new starting item
				startItemPtr = newListItemPtr;
				//end the loop
				inserted = true;
			}//elseif

			//regular insertion into list
			else if (traversalLeaderPtr->itemData > newItemData)
			{
				//set the new items 'nextItem' pointer to the next item
				newListItemPtr->nextItem = traversalFollowPtr->nextItem;
				//set the previous item's 'nextItem' pointer to the new item
				traversalFollowPtr->nextItem = newListItemPtr;
				//end the loop
				inserted = true;
			}//else

			//traversal
			traversalLeaderPtr = traversalLeaderPtr->nextItem;
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
		printf("The list is currently empty\n\n");
		//return success
		return 1;
	}//if

	//check if item to be removed is in the list
	LINKED_LIST_ITEM *removalPtr = checkList(itemdata);

	//perform the removal if the item exists
	if (removalPtr != NULL)
	{
		//if the first item is being removed
		if (removalPtr == startItemPtr)
		{
			//change the start of the list
			startItemPtr = removalPtr->nextItem;
		}//if
		//if any item other than the first is being removed
		else
		{
			//traverse the list until the item before the one to remove is found
			while (traversalPtr->nextItem != removalPtr)
			{
				traversalPtr = traversalPtr->nextItem;
			}//while

			//fix the list so that the item before the one to be removed points to the one after
			traversalPtr->nextItem = removalPtr->nextItem;
		}//else

		//free the memory space of the removed item
		free(removalPtr);

		//return success
		return 1;
	}//if
	//if the removal item does not exist
	else if (removalPtr == NULL)
	{
		//notify the user that the item was not found in the list
		printf("%d was not found in the list\n", itemdata);
		//return success
		return 1;
	}//elseif

	//return failed removal
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
		printf("\n");
		//return success
		return 1;
	}
	else //the list does not start with NULL ie: its not empty
	{
		//loop to print all the items in the list
		do
		{
			//print the item data
			printf("%d", traversalPtr->itemData);

			//if its not the last item print an arrow
			if (traversalPtr->nextItem != NULL)
			{
				printf(" -> ");
			}
			//traverse to the next item in the list
			traversalPtr = traversalPtr->nextItem;
		} while (traversalPtr != NULL);

		//print newlines after the list to indicate completion 
		printf("\n\n");

		//return success
		return 1;

	}//else

	//return failure
	return 0;
}//printList


//function that searches the list for a specified number and returns a pointer to the number if it finds it
LINKED_LIST_ITEM* checkList(int checkNum)
{
	//if the list is empty
	if (startItemPtr == NULL)
	{
		//return success
		return startItemPtr;
	}

	//temporary pointer needed for traversal if the list is not empty
	LINKED_LIST_ITEM *traversalPtr = startItemPtr;

	//loop to traverse through the list
	while (traversalPtr != NULL)
	{
		//if the item is found before the end of the list
		if (traversalPtr->itemData == checkNum)
		{
			//return success
			return traversalPtr;
		}
		//if the item is not found by the end of the list
		else if (traversalPtr->nextItem == NULL)
		{
			//return success
			return NULL;
		}
		//traversal
		traversalPtr = traversalPtr->nextItem;
	}
}