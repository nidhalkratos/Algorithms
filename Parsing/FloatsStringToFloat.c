/*
Given a space separated floats , this code slit them and put them inside an array.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10
#define MAX_STR_LEN 1000
#define MAX_ARRAY_LEN 1000

int point_position(char * str)
{
    int i ;
    int len = strlen(str);
    for(i = 0;i<len;i++)
    {
        if(str[i] == '.')
            return i;
    }
    return -1;
}

void divide_string(char * source_str,char * decimalpart,char * floating_part)
{
        int  point_pos = point_position(source_str);
        int len = strlen(source_str);
        strcpy(decimalpart,"");
        strcpy(floating_part,"");
        if(point_pos == -1)//There is no point found
            strcpy(decimalpart,source_str);
        else
        {
            int i;
            for(i = 0;i<point_pos;i++)
                decimalpart[i] = source_str[i];
            decimalpart[i] = '\0';

            for(i = point_pos+1;i<len;i++)
                floating_part[i-(point_pos+1)] = source_str[i];
            floating_part[i-(point_pos+1)] = '\0';
        }

}

int str_to_int(char * str)
{
    int len = strlen(str);
    int result = 0;
    int i;
    for(i = 0;i<len;i++)
    {
        result += str[i] - '0';
        result *= 10;
    }
    return result/10;
}

float to_floating(float num)
{
    while(num >= 1)
        num /= 10;
    return num;
}

float str_to_float(char * str)
{
    char decimal_part[LEN];
    float floating_part[LEN];
    divide_string(str,decimal_part,floating_part);
    int decimal = str_to_int(decimal_part);
    float floating = str_to_int(floating_part);
    floating = to_floating(floating);
    return decimal + floating;
}

int split_nums_str(char * str,char  arr[MAX_ARRAY_LEN][LEN]) // Splits numbers into copy them inside the array and return its size
{
    int i;
    int len = strlen(str);
    char number[LEN];
    int k =0; //Counter for every character in a word
    int arr_it = 0; // Counter to keep track where to add the number in the array
    for(i = 0;i<len;i++)
    {
        if(str[i] == ' ')
        {
            number[k] = '\0';
            strcpy(arr[arr_it],number);
            arr_it++;
            strcpy(number,"");
            k = 0;
        }
        else
        {
            number[k] = str[i];
            k++;

        }
    }
    strcpy(arr[arr_it],number);
    arr_it++;
    return arr_it;
}

int main()
{
    char  str[MAX_STR_LEN] = "123.456 789.12 90.32 8 10";
    char  arr[MAX_ARRAY_LEN][LEN];
    int arr_size = split_nums_str(str,arr);//Contains the list of separated strings
    int i;
    for(i = 0;i<arr_size;i++)
    {
        printf("%f\n",str_to_float(arr[i]));  //Print all the numbers after converting them to float
    }
    return 0;
}
