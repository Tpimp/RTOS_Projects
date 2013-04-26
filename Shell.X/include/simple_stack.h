/* 
 * File:   simple_stack.h
 * Author: Christopher
 *
 * Created on April 23, 2013, 11:36 AM
 */

#ifndef SIMPLE_STACK_H
#define	SIMPLE_STACK_H

#include "Data_Structs.h"

//typedef char * Stack_Item;

typedef struct SimpleStack
{
    int Size;
    int ItemSize;
    char ** Items;
    int StackPtr;
}Simple_Stack;

#include "Data_Structs.h"
void InitializeSimpleStack(Simple_Stack * Stack, int stack_size, int item_size);

char * StackPopItem(Simple_Stack * Stack);


void StackPushItem(Simple_Stack * Stack, const char * item, int length_item_data);


void DeleteStack(Simple_Stack * Stack);
/*static void InitializeSimpleStack(Simple_Stack * Stack, int stack_size, int item_size)
//InitializeSimpleStack(Simple_Stack * Stack, int stack_size, int item_size);
// extremely unsafe if used incorrectly
void   StackPushItem(Simple_Stack * Stack, char * item, int length_item_data);
Stack_Item * StackPopItem(Simple_Stack * Stack);
void  DeleteStack(Simple_Stack * Stack);
*/
#endif	/* SIMPLE_STACK_H */

