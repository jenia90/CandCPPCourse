//
// Created by jenia on 06/08/2016.
//

#include <stdio.h>

/**
 * Raises a given number to a given power recursively
 * @param base the number to raise to some power.
 * @param pow the power we want to raise it to.
 * @return result.
 */
int power(int base, int pow)
{
    if(pow == 0)
    {
        return 1;
    }

    return power(base, pow-1) * base;
}

/**
 * Converts a number in decimal base to a different given base
 * @param newBase the new base for number representation.
 * @param numToConvert the number to convert.
 * @return the number in the new base representation.
 */
unsigned long convertToNonDecimalBase(int newBase, unsigned long numToConvert)
{
    int i = 1;
    unsigned long divResult = numToConvert, convertedNum = 0;

    while(divResult != 0)
    {
        printf("%d\n",sizeof(convertedNum));
        unsigned long int remainder = divResult % newBase;
        convertedNum += remainder * i;
        divResult = (divResult-remainder) / newBase;
        i*=10;
    }

    return convertedNum;
}

/**
 * Converts a number to decimal base representation
 * @param origBase the original base.
 * @param numToConvert the number to convert.
 * @return decimal representation of a given number.
 */
unsigned long convertToDecimalBase(int origBase, unsigned long numToConvert)
{
    int j;
    unsigned long result = 0;


    for(j = 0; numToConvert > 0; j++)
    {
        result += (numToConvert%10)*power(origBase, j);
        numToConvert/=10;
    }

    return result;
}

int main(int argc, char* argv[])
{
    int origBase, newBase;
    unsigned long origNum, convertedNum;

    scanf("%d^%d^%lu^", &origBase, &newBase, &origNum);
    convertedNum = origNum;

    if (origBase == 10 && newBase != 10)
    {
        convertedNum = convertToNonDecimalBase(newBase, origNum);
    }
    else if(newBase == 10 && origBase != 10)
    {
        convertedNum = convertToDecimalBase(origBase, origNum);
    }
    else if(newBase != origBase != 10)
    {
        unsigned long temp = convertToDecimalBase(origBase, origNum);
        convertedNum = convertToNonDecimalBase(newBase, temp);

    }

    printf("%lu", convertedNum);

    return 0;
}
