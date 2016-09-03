/**
* @file GenericHashTable.c
* @author jenia90
* @version 1.0
* @date 1 Sep 2016
*
* @brief Generic hash table implementation
* @section DESCRIPTION:
* Defines a generic representation of a hash table which holds an array of defined size in each cell.
 * Upon creation it receives a size and a set of key management functions.
*/

/**
 * We defined here the default cell size in case it wasn't defined as compiler argument
 */
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

/**
 * Macros to calculate the updated index for a resized table
 */
#define RESIZED_INDEX_OLD(x) 2 * x
#define RESIZED_INDEX_NEW(x) 2 * x + 1

#define NOT_FOUND -1

/**
 * Structure defining a hash table item. It holds a unique key and data.
 */
typedef struct Item
{
    void *key;
    DataP data;
} *ItemP;

/**
 * Definitions of table cell types
 */
typedef ItemP **Cells;
typedef ItemP *Cell;
typedef ItemP Item;

/**
 * A structure representing a hash table and a new type definition.
 */
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
    // Check if passed table size is valid
    if(tableSize == 0)
    {
        reportError(GENERAL_ERROR);
        return NULL;
    }

    // allocate memory block for the hashtable of given size.
    TableP newTable = (TableP)calloc(tableSize, sizeof(Table));
    if (!newTable)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    // allocate cell array memory block for the hashtable cells.
    newTable->cells = calloc(tableSize, sizeof(*newTable->cells));
    if(!newTable->cells)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    // init Table struct members.
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
    // backup old size value.
    size_t oldSize = table->size;

    // get old cells array.
    Cells oldCells = table->cells;

    // allocate memory block for new cells array.
    Cells newCells = calloc(table->size *= expandBy, sizeof(*newCells));

    if (!newCells)
    {
        reportError(MEM_OUT);
        return false;
    }

    // iterate over each cell in the old cell array and recreate it in the new cell array
    // along with its items.
    for (i = 0; i < (int)oldSize; i++)
    {
        Cell oldCell = oldCells[i];
        if (oldCell)
        {
            Cell newCell = createCell(newCells, RESIZED_INDEX_OLD(i));

            if (!newCell)
            {
                reportError(MEM_OUT);
                free(newCells);
                return false;
            }

            for (j = 0; j < MAX_ROW_ELEMENTS; j++)
            {
                Item oldItem = oldCell[j];
                if (oldItem)
                {
                    Item item = createItem(table, newCell, j, oldItem->key, oldItem->data);
                    if (!item)
                    {
                        reportError(MEM_OUT);
                        free(newCell);
                        free(newCells);
                        return false;
                    }

                    table->freeKey(oldItem->key);
                    free(oldItem);
                }
            }

            free(oldCell);
        }
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
            cell = createCell(cells, i);
            if(!cell)
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
    int arrCell, listNode;
    DataP data = findData(table, key, &arrCell, &listNode);
    Cells cells = table->cells;

    if(!data)
    {
        return NULL;
    }

    table->freeKey(cells[arrCell][listNode]->key);
    free(cells[arrCell][listNode]);
    free(cells[arrCell]);
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
    Cells cells = table->cells;
    for (i = 0; i < (int)table->size; i++)
    {
        Cell cell = cells[i];
        if(cell)
        {
            for (j = 0; j < MAX_ROW_ELEMENTS; j++)
            {
                Item item = cell[j];
                if (item)
                {
                    table->freeKey(item->key);
                    free(item);
                }
            }

            free(cell);
        }
    }
    free(cells);
    free(table);
}