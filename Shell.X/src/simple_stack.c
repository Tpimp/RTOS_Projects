#include "simple_stack.h"
//#include <stdlib.h>

void InitializeSimpleStack(Simple_Stack * Stack, int stack_size, int item_size)
{
    char ** stack =
            pvPortMalloc(sizeof(char *)/sizeof(char) * stack_size);
    int i;
    for(i = 0; i < item_size; i++)
    {
        stack[i] = pvPortMalloc(item_size);
    }
    Stack->Size = stack_size;
    Stack->ItemSize = item_size;
    Stack->StackPtr = 0;
    Stack->Items = stack;
}

char * StackPopItem(Simple_Stack * Stack)
{
    if(Stack->StackPtr != 0)
    {
        return Stack->Items[Stack->StackPtr--];
    }
    else
    {
        Stack->StackPtr = -1;
    }
}

void StackPushItem(Simple_Stack * Stack, const char * item, int length_item_data)
{
    if(Stack->StackPtr <= Stack->Size)
    {
        int i;
        // Use Memset instead
        for(i = 0; i < length_item_data; i++)
        {
            Stack->Items[Stack->StackPtr][i] = item[i];
            if(item[i] == '\0')
                i = length_item_data;
        }
        Stack->StackPtr++;
    }
}

void DeleteStack(Simple_Stack * Stack)
{
    int i;
    for(i = 0; i < Stack->Size; i++)
    {
        vPortFree(Stack->Items[i]);
    }
    vPortFree(Stack->Items);
    Stack->Items = NULL;
    Stack->Size = 0;
    Stack->ItemSize = 0;
    Stack->StackPtr = 0;
}
