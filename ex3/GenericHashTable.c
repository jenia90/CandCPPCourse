//
// Created by jenia on 28/08/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include "GenericHashTable.h"
#include "TableErrorHandle.h"

#define MAX_ROW_ELEMENTS 2
#define EXPANSION_COEFFICIENT 2
#define DEFAULT_TABLE_SIZE 4

typedef struct Item
{
    void *key;
    DataP *data;
} Item;

typedef struct Cell
{
    Item items[MAX_ROW_ELEMENTS];
} Cell, *CellP;

typedef struct Table
{
    size_t size, origSize;
    CellP *cells;
    CloneKeyFcn cloneKey;
    FreeKeyFcn freeKey;
    HashFcn hashFcn;
    PrintKeyFcn printKeyFun;
    PrintDataFcn printDataFun;
    ComparisonFcn compKeys;
} Table = {.origSize = DEFAULT_TABLE_SIZE};

/**
 * @brief print function
 *
 */
typedef void(*PrintDataFcn)(const void* data);

void moveTable(TableP oldTable, TableP newTable);
int hashedIndexOf(const TableP table, const void *key);

/**
 * @brief Allocate memory for a hash table with which uses the given functions.
 * tableSize is the number of cells in the hash table.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */

TableP createTable(size_t tableSize, CloneKeyFcn cloneKey, FreeKeyFcn freeKey
        ,HashFcn hfun,PrintKeyFcn printKeyFun, PrintDataFcn printDataFun
        , ComparisonFcn fcomp)
{
    TableP newTable = (TableP)malloc(sizeof(Table) * tableSize);
    if (!newTable)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    newTable->size = tableSize;
    newTable->cells = (CellP *)malloc(sizeof(Cell) * tableSize);
    newTable->cloneKey = cloneKey;
    newTable->freeKey = freeKey;
    newTable->hashFcn = hfun;
    newTable->printKeyFun = printKeyFun;
    newTable->printDataFun = printDataFun;
    newTable->compKeys = fcomp;

    return newTable;
}

/**
 * @brief In case we run out of cells to allocate for new keys in our table we expand the table
 * to a given size transfer all our current items to the new table.
 * @param table
 * @param newSize
 * @return
 */
int expandTable(TableP table, const size_t newSize)
{
    TableP newTable = createTable(newSize, table->cloneKey, table->freeKey, table->hashFcn,
                                  table->printKeyFun, table->printDataFun, table->compKeys);

    if(!newTable)
    {
        reportError(MEM_OUT);
        return false;
    }
    moveTable(table, newTable);
    *table = *newTable;


    return true;
}


/**
 * @brief Insert an object to the table with key.
 * If all the cells appropriate for this object are full, duplicate the table.
 * If run out of memory, report
 * MEM_OUT and do nothing (the table should stay at the same situation
 * as it was before the duplication).
 * If everything is OK, return true. Otherwise (an error occured) return false;
 */
int insert( TableP table, const void* key, DataP object)
{
    bool result = false;
    int i,  hashKey = hashedIndexOf(table, key);
    CellP cell = table->cells[hashKey];
    if(!cell)
    {
        cell = (CellP)malloc(sizeof(Cell));

        if(!cell)
        {
            return false;
        }
    }

    for(i = 0; i < MAX_ROW_ELEMENTS && !result; i++)
    {
        if(!cell->items[i].data)
        {
            cell->items->key = table->cloneKey(key);
            cell->items[i].data = object;
            result = true;
        }
    }

    if(!result)
    {
        if(!expandTable(table, table->size * EXPANSION_COEFFICIENT))
        {
            return false;
        }
        result = (bool)insert(table, key, object);
    }

    return result;
}


/**
 * @brief remove an data from the table.
 * If everything is OK, return the pointer to the ejected data. Otherwise return NULL;
 */
DataP removeData(TableP table, const void* key)
{
    DataP data = NULL;
    int i, hashIndex = hashedIndexOf(table, key);
    CellP cell = table->cells[hashIndex];

    for(i = 0; i < MAX_ROW_ELEMENTS; i++)
    {
        if(table->compKeys(key, cell->items[i].key) == 0)
        {
            data = cell->items[i].data;
            table->freeKey(cell->items[i].key);
        }
    }

    return data;
}

/**
 * @brief Search the table and look for an object with the given key.
 * If such object is found fill its cell number into arrCell (where 0 is the
 * first cell), and its placement in the list into listNode (when 0 is the
 * first node in the list, i.e. the node that is pointed from the table
 * itself).
 * If the key was not found, fill both pointers with value of -1.
 * return pointer to the data or null
 */
DataP findData(const TableP table, const void* key, int* arrCell, int* listNode)
{
    DataP data = NULL;
    int i, hashedIndex = hashedIndexOf(table, key);

    if(table->cells[hashedIndex])
    {
        *arrCell = hashedIndex;
        for(i = 0; i < MAX_ROW_ELEMENTS; i++)
        {
            if(table->compKeys(key, table->cells[hashedIndex]->items[i].key) == 0)
            {
                *listNode = i;
                data = table->cells[hashedIndex]->items[i].data;
            }
        }
    }

    return data;
}

/**
 * @brief return a pointer to the data that exist in the table in cell number arrCell (where 0 is the
 * first cell), and placment at listNode in the list (when 0 is the
 * first node in the list, i.e. the node that is pointed from the table
 * itself).
 * If such data not exist return NULL
 */
DataP getDataAt(const TableP table, int arrCell, int listNode)
{
    if(arrCell < table->size && listNode < MAX_ROW_ELEMENTS)
    {
        return table->cells[arrCell]->items[listNode].data;
    }

    return NULL;
}

/**
 * @brief return the pointer to the key that exist in the table in cell number arrCell (where 0 is the
 * first cell), and placment at listNode in the list (when 0 is the
 * first node in the list, i.e. the node that is pointed from the table
 * itself).
 * If such key not exist return NULL
 */
ConstKeyP getKeyAt(const TableP table, int arrCell, int listNode)
{

    if(arrCell < table->size && listNode < MAX_ROW_ELEMENTS)
    {
        return table->cells[arrCell]->items[listNode].key;
    }

    return NULL;
}

/**
 * @brief Print the table (use the format presented in PrintTableExample).
 */
void printTable(const TableP table)
{
    int cellIndex, itemIndex;
    for(cellIndex = 0; cellIndex < table->size; cellIndex++)
    {
        printf("[%d]\t", cellIndex);
        if(table->cells[cellIndex])
        {
            for(itemIndex = 0; itemIndex< MAX_ROW_ELEMENTS; itemIndex++)
            {
                ConstKeyP key = getKeyAt(table, cellIndex, itemIndex);
                DataP data = getDataAt(table, cellIndex, itemIndex);
                if(key)
                {
                    table->printKeyFun(key);
                    puts(",");
                    table->printDataFun(data);
                    puts("\t-->\t");
                }
            }
        }
        puts("\n");
    }
}

/**
 * @brief Free all the memory allocated for the table.
 * It's the user responsibility to call this function before exiting the program.
 */
void freeTable(TableP table)
{
    int i, j;
    for (i = 0; i < table->size; i++)
    {
        CellP cell = table->cells[i];
        for(j = 0; j < MAX_ROW_ELEMENTS; j++)
        {
            free(cell->items[i].key);
        }
        free(cell);
    }

    free(table);
}

void moveTable(TableP oldTable, TableP newTable)
{
    int i, j;
    for (i = 0; i < oldTable->size; i++)
    {
        CellP cell = oldTable->cells[i];
        newTable->cells[2 * i] = cell;
        for(j = 0; j < MAX_ROW_ELEMENTS; j++)
        {
            free(cell->items[i].key);
        }
        free(cell);
    }
}

int hashedIndexOf(const TableP table, const void *key)
{
    int d = (int)(table->size / table->origSize);
    return d * table->hashFcn(key, table->size);
}