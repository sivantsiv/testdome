// Descriptor.cpp : This is C task. Implement 2 functions: allocate_and_initialize_descriptor() and deallocate_descriptor()
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Descriptor
{
    int id;
    int name_length;
    char* name;
} Descriptor;

Descriptor* allocate_and_initialize_descriptor(int id, const char* name)
{
    Descriptor* ptr = (Descriptor*)malloc(sizeof(Descriptor));
    if (NULL == ptr)
    {
        return NULL;
    }
    else
    {
        ptr->id = id;
        ptr->name_length = strlen(name) + 1;
        char* str = (char*)malloc(ptr->name_length);
        if (NULL == str)
        {
            return  NULL;
        }
        else
        {
            strcpy(str, name);
            ptr->name = str;
        }
    }

    return ptr;
}

void deallocate_descriptor(Descriptor* descriptor)
{
    if (NULL != descriptor)
    {
        if (NULL != descriptor->name)
        {
            free(descriptor->name);
        }
        free(descriptor);
    }
}

#ifndef RunTests
int main()
{
    Descriptor* descriptor = allocate_and_initialize_descriptor(2, "File");
    printf("Id: %d, name length: %d, name: %s", descriptor->id, descriptor->name_length, descriptor->name);
    deallocate_descriptor(descriptor);
}
#endif
