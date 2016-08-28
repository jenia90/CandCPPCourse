//
// Created by jenia on 28/08/2016.
//

#include <stdio.h>
#include <stdlib.h>
#include "GenericHashTable.h"
#include "TableErrorHandle.h"

#define MAX_ROW_ELEMENTS 2

typedef struct Cell
{
    void *key;
    void *val;
} *CellP;

typedef struct Table
{
    size_t size;
    CellP *data;
    CloneKeyFcn cloneKey;
    FreeKeyFcn freeKey;
    HashFcn hashFcn;
    PrintKeyFcn printKeyFun;
    PrintDataFcn printDataFun;
    ComparisonFcn comparisonFun;
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
    TableP newTable = (TableP)malloc(sizeof(Table) * tableSize);
    if (!newTable)
    {
        reportError(MEM_OUT);
        return NULL;
    }

    newTable->data = (CellP*)malloc(sizeof(CellP) * tableSize);
    newTable->cloneKey = cloneKey;
    newTable->freeKey = freeKey;
    newTable->hashFcn = hfun;
    newTable->printKeyFun = printKeyFun;
    newTable->printDataFun = printDataFun;
    newTable->comparisonFun = fcomp;

    return newTable;
}

CellP createCell(void *key, void *val)
{
    CellP newCell = (CellP)malloc(sizeof(struct Cell) * MAX_ROW_ELEMENTS);
    newCell->key = key;
    newCell->val = val;

    return newCell;
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
    int hashKey = table->hashFcn(key, table->size);

    CellP newCell = createCell(table->cloneKey(key), object);
    if(!newCell)
    {
        reportError(MEM_OUT);
        return false;
    }
    table->data[hashKey] = newCell;

    return true;
}

TableP rehashTable(TableP table, size_t newSize)
{
    TableP newTable = createTable(newSize, table->cloneKey, table->freeKey, table->hashFcn, table
            ->printKeyFun, table->printDataFun, table->comparisonFun);

    if(!newTable)
    {
        return NULL;
    }



    return newTable;

}


/**
 * @brief remove an data from the table.
 * If everything is OK, return the pointer to the ejected data. Otherwise return NULL;
 */
DataP removeData(TableP table, const void* key)
{

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

}

/**
 * @brief Print the table (use the format presented in PrintTableExample).
 */
void printTable(const TableP table)
{

}

/**
 * @brief Free all the memory allocated for the table.
 * It's the user responsibility to call this function before exiting the program.
 */
void freeTable(TableP table)
{

}