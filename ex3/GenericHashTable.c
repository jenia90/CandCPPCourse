//
// Created by jenia on 28/08/2016.
//

#ifndef MAX_ROW_ELEMENTS
#define MAX_ROW_ELEMENTS 2
#endif

#include <stdio.h>
#include <stdlib.h>
#include "GenericHashTable.h"
#include "TableErrorHandle.h"

#define EXPANSION_COEFFICIENT 2
#define CELL_IDX_STR "[%d]\t"
#define KEY_VAL_SPLIT ","
#define ITEM_SPLIT "\t-->\t"
#define NEW_LINE "\n"

#define RESIZED_INDEX_OLD(x) 2 * x
#define RESIZED_INDEX_NEW(x) 2 * x + 1

#define NOT_FOUND -1
typedef struct Item
{
    void *key;
    DataP data;
} *ItemP;

typedef ItemP **Cells;
typedef ItemP *Cell;
typedef ItemP Item;

typedef struct Table
{
    Cells cells;
    size_t size, origSize;
    CloneKeyFcn cloneKey;
    FreeKeyFcn freeKey;
    HashFcn hashFcn;
    PrintKeyFcn printKeyFun;
    PrintDataFcn printDataFun;
    ComparisonFcn compKeys;
} Table;

/**
 * @brief print function
 *
 */
typedef void(*PrintDataFcn)(const void* data);

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
    if(tableSize == 0)
    {
        reportError(GENERAL_ERROR);
        return NULL;
    }

    TableP newTable = (TableP)calloc(tableSize, sizeof(Table));
    if (!newTable)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    newTable->cells = calloc(tableSize, sizeof(*newTable->cells));
    if(!newTable->cells)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    newTable->origSize = newTable->size = tableSize;
    newTable->cloneKey = cloneKey;
    newTable->freeKey = freeKey;
    newTable->hashFcn = hfun;
    newTable->printKeyFun = printKeyFun;
    newTable->printDataFun = printDataFun;
    newTable->compKeys = fcomp;

    return newTable;
}

/**
 * @brief Creates a new item at a specific index inside the table cell and allocates memory for it.
 * @param table pointer to the hash table
 * @param cell pointer to the cell to which that item will be added
 * @param itemIdx index at which it will be placed
 * @param key key of the new item
 * @param object data pointer of the new item
 * @return pointer to the item if successful; NULL otherwise
 */
static ItemP createItem(TableP table, ItemP *cell, int itemIdx, const void *key, DataP object)
{
    // allocate memory for the new item.
    ItemP item = cell[itemIdx] = malloc(sizeof(*item));
    if(!item)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    // clone the key using a specific function and then assign data
    item->key = table->cloneKey(key);
    item->data = object;
    return item;
}

/**
 * @brief Creates a new cell and allocates memory for its items
 * @param cells array of cells to where a new cell will be allocated
 * @param index index of the new cell
 * @return pointer to the new cell if successful; NULL otherwise
 */
static Cell createCell(Cells cells, int index)
{
    Cell cell = cells[index] = calloc(MAX_ROW_ELEMENTS, sizeof(*cell));

    if(!cell)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    return cell;
}

/**
 * @brief In case we run out of cells to allocate for new keys in our table we expand the table
 * to a given size transfer all our current items to the new table.
 * @param table
 * @param newSize
 * @return
 */
static int expandTable(TableP table, int expandBy)
{
    int i, j;
    size_t oldSize = table->size;
    Cells oldCells = table->cells;
    Cells newCells = calloc(table->size *= expandBy, sizeof(*newCells));

    if (!newCells)
    {
        reportError(MEM_OUT);
        return false;
    }

    for (i = 0; i < (int)oldSize; i++)
    {
        Cell oldCell = oldCells[i];
        if (!oldCell)
        {
            continue;
        }

        Cell newCell = createCell(newCells, RESIZED_INDEX_OLD(i));

        if (!newCell)
        {
            reportError(MEM_OUT);
            return false;
        }

        for (j = 0; j < MAX_ROW_ELEMENTS; j++)
        {
            Item oldItem = oldCell[j];
            if (!oldItem)
            {
                continue;
            }

            Item item = createItem(table, newCell, j, oldItem->key, oldItem->data);
            if (!item)
            {
                reportError(MEM_OUT);
                return false;
            }

            table->freeKey(oldItem->key);
            free(oldItem);
        }

        free(oldCell);
    }

    free(oldCells);
    table->cells = newCells;

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
int insert(TableP table, const void* key, DataP object)
{
    Cells cells = table->cells;
    int d = (int)(table->size / table->origSize);
    int i, j, hashKey = d * table->hashFcn(key, table->origSize);
    for(i = hashKey; i < d + hashKey; ++i)
    {
        Cell cell = cells[i];
        if (cell)
        {
            for (j = 0; j < MAX_ROW_ELEMENTS; j++)
            {
                Item item = cell[j];
                if (!item)
                {
                    return createItem(table, cell, j, key, object) != NULL;
                }
                else if(!table->compKeys(item->key, key))
                {
                    item->data = object;
                    return true;
                }
            }

        }
        else
        {
            if(!(cell = createCell(cells, i)))
            {
                return false;
            }
            return createItem(table, cell, 0, key, object) != NULL;
        }

    }

    if(expandTable(table, EXPANSION_COEFFICIENT))
    {
        cells = table->cells;
        Cell newCell = createCell(cells, RESIZED_INDEX_NEW(hashKey));
        if(newCell)
        {
            return createItem(table, newCell, 0, key, object) != NULL;
        }
    }

    return false;
}

/**
 * @brief remove an data from the table.
 * If everything is OK, return the pointer to the ejected data. Otherwise return NULL;
 */
DataP removeData(TableP table, const void* key)
{
    int i, j;
    DataP data = findData(table, key, &i, &j);
    Cells cells = table->cells;

    if(!data)
    {
        return NULL;
    }

    table->freeKey(cells[i][j]->key);
    free(cells[i][j]);
    free(cells[i]);
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
    int d = (int)(table->size / table->origSize);
    int i, j, hashKey = d * table->hashFcn(key, table->origSize);

    for(i = hashKey; i < d + hashKey; i++)
    {
        Cell cell = table->cells[i];
        if (cell)
        {
            for (j = 0; j < MAX_ROW_ELEMENTS; j++)
            {
                Item item = cell[j];
                if (item && !table->compKeys(item->key, key))
                {
                    *arrCell = i;
                    *listNode = j;
                    return item->data;
                }
            }
        }
    }

    *arrCell = NOT_FOUND;
    *listNode = NOT_FOUND;
    return NULL;
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
    if(arrCell < (int)table->size && listNode < MAX_ROW_ELEMENTS)
    {
        Item cell = table->cells[arrCell][listNode];
        if(cell)
        {
            return cell->data;
        }
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

    if(arrCell < (int)table->size && listNode < MAX_ROW_ELEMENTS)
    {
        Item cell = table->cells[arrCell][listNode];
        if(cell)
        {
            return cell->key;
        }
    }

    return NULL;
}

/**
 * @brief Print the table (use the format presented in PrintTableExample).
 */
void printTable(const TableP table)
{
    int cellIndex, itemIndex;
    Cells cells = table->cells;
    for(cellIndex = 0; cellIndex < (int)table->size; cellIndex++)
    {
        printf(CELL_IDX_STR, cellIndex);
        if(cells[cellIndex])
        {
            for(itemIndex = 0; itemIndex < MAX_ROW_ELEMENTS; itemIndex++)
            {
                ConstKeyP key = getKeyAt(table, cellIndex, itemIndex);
                DataP data = getDataAt(table, cellIndex, itemIndex);
                if(key && data)
                {
                    table->printKeyFun(key);
                    printf(KEY_VAL_SPLIT);
                    table->printDataFun(data);
                    printf(ITEM_SPLIT);
                }
            }
        }
        printf(NEW_LINE);
    }
}

/**
 * @brief Free all the memory allocated for the table.
 * It's the user responsibility to call this function before exiting the program.
 */
void freeTable(TableP table)
{
    int i, j;
    for (i = 0; i < (int)table->size; i++)
    {
        Cell cell = table->cells[i];
        if(cell)
        {
            for (j = 0; j < MAX_ROW_ELEMENTS; j++)
            {
                if (cell[j])
                {
                    table->freeKey(cell[j]->key);
                }
            }

            free(*cell);
        }

        free(cell);
    }

    free(table);
}