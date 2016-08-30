//
// Created by jenia on 28/08/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include "GenericHashTable.h"
#include "TableErrorHandle.h"

#define MAX_ROW_ELEMENTS 2
#define EXPANSION_COEFFICIENT 2

typedef struct Cell
{
    void *key;
    DataP data;
} *CellP;

typedef struct Table
{
    size_t size, origSize;
    CellP **cells;
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

static int hashedIndexOf(const TableP table, const void *key);

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
    TableP newTable = (TableP)calloc(tableSize, sizeof(Table));
    if (!newTable)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    newTable->origSize = newTable->size = tableSize;
    newTable->cells = calloc(tableSize, sizeof(CellP));
    if(!newTable->cells)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    newTable->cloneKey = cloneKey;
    newTable->freeKey = freeKey;
    newTable->hashFcn = hfun;
    newTable->printKeyFun = printKeyFun;
    newTable->printDataFun = printDataFun;
    newTable->compKeys = fcomp;

    return newTable;
}



static CellP createItem(TableP table, CellP *cell, int itemIdx, const void *key, DataP object)
{
    CellP item = cell[itemIdx] = malloc(sizeof(CellP));
    if(!item)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    item->key = table->cloneKey(key);
    item->data = object;
    return item;
}

static CellP *createCell(CellP **cells,int index)
{
    CellP *cell = (cells[index] = calloc(MAX_ROW_ELEMENTS, sizeof(*cell)));

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
static int **expandTable(TableP table, int expandBy)
{
    int i, j, oldSize = table->size;
    CellP **oldCells = table->cells;
    CellP **newCells = calloc(table->size *= expandBy, sizeof(*newCells));

    if (!newCells)
    {
        reportError(MEM_OUT);
        return false;
    }

    for (i = 0; i < oldSize; i++)
    {
        CellP *oldCell = oldCells[i];
        if (!oldCell)
        {
            continue;
        }

        CellP *newCell = createCell(newCells, i);

        if (!newCell)
        {
            reportError(MEM_OUT);
            return false;
        }

        for (j = 0; j < MAX_ROW_ELEMENTS; j++)
        {
            CellP oldItem = oldCell[j];
            if (!oldItem)
            {
                continue;
            }

            CellP item = createItem(table, newCell, j, oldItem->key, oldItem->data);
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

    return false;
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
    CellP **cells = table->cells;
    int d = (int)(table->size / table->origSize);
    int i, j, hashKey = d * table->hashFcn(key, table->size);
    for(i = hashKey; i < d + hashKey; ++i)
    {
        CellP *cell = cells[i];
        if (cell)
        {
            for (j = 0; j < MAX_ROW_ELEMENTS; j++)
            {
                CellP item = cell[j];
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
        CellP *newCell = createCell(cells, 2 * hashKey + 1);
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
    DataP data = NULL;
    int i, hashIndex = hashedIndexOf(table, key);
    CellP *cell = table->cells[hashIndex];

    for(i = 0; i < MAX_ROW_ELEMENTS; i++)
    {
        if(table->compKeys(key, cell[i]->key) == 0)
        {
            data = cell[i]->data;
            table->freeKey(cell[i]->key);
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
    CellP *cell = table->cells[hashedIndex];

    if(cell)
    {
        *arrCell = hashedIndex;
        for(i = 0; i < MAX_ROW_ELEMENTS; i++)
        {
            if(table->compKeys(key, cell[i]->key) == 0)
            {
                *listNode = i;
                data = cell[i]->data;
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
        return table->cells[arrCell][listNode]->data;
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
        return table->cells[arrCell][listNode]->key;
    }

    return NULL;
}

/**
 * @brief Print the table (use the format presented in PrintTableExample).
 */
void printTable(const TableP table)
{
    int cellIndex, itemIndex;
    CellP **cells = table->cells;
    for(cellIndex = 0; cellIndex < table->size; cellIndex++)
    {
        printf("[%d]\t", cellIndex);
        if(cells[cellIndex])
        {
            printf("Cell: %d", **cells[cellIndex]);
            for(itemIndex = 0; itemIndex < MAX_ROW_ELEMENTS; itemIndex++)
            {
                ConstKeyP key = getKeyAt(table, cellIndex, itemIndex);
                DataP data = getDataAt(table, cellIndex, itemIndex);
                if(key)
                {
                    table->printKeyFun(key);
                    printf(",");
                    table->printDataFun(data);
                    printf("\t-->\t");
                }
            }
        }
        printf("\n");
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
        CellP *cell = table->cells[i];
        if(cell)
        {
            for (j = 0; j < MAX_ROW_ELEMENTS; j++)
            {
                if (cell[j])
                {
                    free(cell[j]->key);
                }
            }

            free(*cell);
        }

        free(cell);
    }

    free(table);
}

int hashedIndexOf(const TableP table, const void *key)
{
    int d = (int)(table->size / table->origSize);
    return d * table->hashFcn(key, table->size);
}