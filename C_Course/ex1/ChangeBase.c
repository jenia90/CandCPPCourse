/**
 * @file ChangeBase.c
 * @author jenia90
 * @version 1.0
 * @date 11 Aug 2016
 *
 * @brief Program to convert number representation bases.
 *
 * @section DESCRIPTION:
 * This program receives a set of number divided with '^' from the console and converts the last number's base
 * from first number to second.
 * Input: String of following structure: <original_base>^<new_base>^<number_to_convert>.
 * Process: The process will be explained in the CONVERSION ALGORITHM section.
 * Output: Prints the converted number if successful; "invalid!!" otherwise.
 *
 * @section CONVERSION ALGORITHM:
 * My implementation was based on the explanation given at:
 * http://www.tutorialspoint.com/computer_logical_organization/number_system_conversion.htm
 *
 * There are 3 cases:
 * 1. The number is converted from some base to decimal base:
 *      Extract each digit using modulo 10 operation and then multiply it by new base in digit place power.
 *      The product is added to the result variable which we then return to main method.
 *      Complexity of this case is: O(number_of_digits) => O(n)
 *
 * 2. The number is converted from decimal base to some other base:
 *      We divide the number by the new base and save the remainder which we later will place as digits in the
 *      new number.
 *      Complexity of this case is: O(number_of_times_the_number_is_dividable_by_the_new_base) => O(logn)
 *
 * 3. The number is converted from some base to another base (both not decimal):
 *      This case is combination of previous 2. First, we convert the number to decimal base and then to the other
 *      base from decimal.
 *      Complexity of this case is: O(n)+O(logn)=O(n)
 */

#include <stdio.h>
#include <stdlib.h>

#define uint64 unsigned long long

/**
 * Raises a given number to a given power recursively
 * @param base the number to raise to some power.
 * @param pow the power we want to raise it to.
 * @return result.
 */
uint64 power(uint64 base, int pow)
{
    if(pow == 0)
    {
        return 1;
    }

    return power(base, pow - 1) * base;
}

/**
 * Converts a number in decimal base to a different given base
 * @param newBase the new base for number representation.
 * @param numToConvert the number to convert.
 * @return the number in the new base representation.
 */
uint64 convertToNonDecimalBase(uint64 newBase, uint64 numToConvert)
{
    uint64 i = 1, remainder, divResult = numToConvert, convertedNum = 0;

    while(divResult != 0)
    {
        remainder = divResult % newBase; // gets the remainder of the division
        convertedNum += remainder * i; // adds the remainder as a digit in the final converted number
        divResult = (divResult - remainder) / newBase;
        i *= 10;
    }
    return convertedNum;
}

/**
 * Converts a number to decimal base representation
 * @param origBase the original base.
 * @param numToConvert the number to convert.
 * @return decimal representation of a given number.
 */
uint64 convertToDecimalBase(uint64 origBase, uint64 numToConvert)
{
    int j;
    uint64 result = 0, currentDigit;

    for(j = 0; numToConvert > 0; j++)
    {
        currentDigit = (numToConvert % 10); // extract current digit

        // check if each digit is smaller than the base. if yes, convert the digit to decimal base
        if(currentDigit < origBase)
        {
            result +=  currentDigit * power(origBase, j);
            numToConvert /= 10;
        }
        else
        {
            fprintf(stderr, "invalid!!\n");
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

/**
 * Main function
 * @return 0 if run was successful.
 */
int main()
{
    uint64 origNum, convertedNum, origBase, newBase;

    scanf("%llu^%llu^%llu^", &origBase, &newBase, &origNum);
    convertedNum = origNum; // init the the variable with original number for the case no conversion needed.

    if(origBase <= 1 || newBase <= 1)
    {
        return EXIT_FAILURE;
    }

    // first case where we convert from decimal base.
    if (origBase == 10 && newBase != 10)
    {
        convertedNum = convertToNonDecimalBase(newBase, origNum);
    }
    // second case where we convert to decimal base.
    else if(newBase == 10 && origBase != 10)
    {
        convertedNum = convertToDecimalBase(origBase, origNum);
    }
    // third case we convert to decimal and then from decimal to new base.
    else if(newBase != 10 && origBase != 10 && newBase != origBase)
    {
        uint64 temp = convertToDecimalBase(origBase, origNum);
        convertedNum = convertToNonDecimalBase(newBase, temp);
    }

    printf("%llu", convertedNum);

    return EXIT_SUCCESS;
}
