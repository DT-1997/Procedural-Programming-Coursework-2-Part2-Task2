#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
FILE *fp = NULL;
Filename file;
FITNESS_DATA FITNESS_DATAS;
char option;
char file_name[50];
char buff[21];
char ff_buff[21];
char fl_buff[21];
char time1[6];
char time2[6];
char start_time[17];
char end_time[17];
char current_start_time[17];
char current_end_time[17];
char feweststeps_data[11];
char feweststeps_time[6];
int namestatment;
int feweststeps = 100000;
int largeststeps = 0;
int meanstepcount;
int quit = 0;
int counter = 0;
int linecounter = 0;
int periodcounter = 0;
int max_periodcounter = 0;
int statment = 0;
char hour[3];
char minute[3];
char rightname[] = "FitnessData_2023.csv";

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() {
   while (quit != 1)
    {
        printf("Menu Options:\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the date and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\n");
        printf("Enter choice: ");
        scanf("%s", &option);
        switch (option){
            case 'A':
                check_filename();
                break;
            case 'B':
                count_records();
                break;
            case 'C':
                find_feweststeps();
                break;
            case 'D':
                find_largeststeps();
                break;
            case 'E':
                find_meanstepcount();
                break;
            case 'F':
                find_longestperiod();
                break;
            case 'Q':
                if (fp != NULL)
                {
                    fclose(fp);
                    quit = 1;
                }
                else
                {
                    quit = 1;
                }
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
            }  
    }
    return 0;
}

void check_filename(){
    printf("Input filename:");
    scanf("%s",&file_name);
    namestatment = strcmp(file_name,rightname);
    if (namestatment != 0)
    {
        printf("Error: Could not find or open the file.\n");
    }
    else{
        printf("File successfully loaded.\n");
        fp = fopen("FitnessData_2023.csv","r");
    }
}

void count_records(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        counter++;
    }
    printf("Total records: %d\n",counter);
    counter = 0;
}

void find_feweststeps(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
        if (atoi(FITNESS_DATAS.steps) < feweststeps)
        {
            feweststeps = atoi(FITNESS_DATAS.steps);
            strcpy(ff_buff,FITNESS_DATAS.date);
            strcat(ff_buff," ");
            strcat(ff_buff,FITNESS_DATAS.time);
        }
    }
    printf("Fewest steps: %s\n",ff_buff);
}

void find_largeststeps(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
        if (atoi(FITNESS_DATAS.steps) > largeststeps)
        {
            largeststeps = atoi(FITNESS_DATAS.steps);
            strcpy(fl_buff,FITNESS_DATAS.date);
            strcat(fl_buff," ");
            strcat(fl_buff,FITNESS_DATAS.time);
        }
    }
    printf("Largest steps: %s\n",fl_buff);
}

void find_meanstepcount(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        counter++;
        tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
        meanstepcount += atoi(FITNESS_DATAS.steps);
    }
    meanstepcount /= counter;
    printf("Mean step count: %d\n",meanstepcount);
    counter = 0;
}

void find_longestperiod(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        counter++;
        tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
        if (atoi(FITNESS_DATAS.steps) > 500)
        {
            periodcounter++;
            if (linecounter == 0)
            {
                linecounter = counter;
            }
            if (counter != linecounter)
            {
                if (counter - linecounter == 1)
                {
                    NULL;
                }
                else
                {
                    statment = 0;
                    periodcounter = 0;
                    linecounter = counter;
                }
            }
            if (statment == 0)
            {
                strcpy(current_start_time,FITNESS_DATAS.date);
                strcat(current_start_time," ");
                strcat(current_start_time,FITNESS_DATAS.time);
                statment = 1;
            }
            if (counter - linecounter == 1)
            {
                linecounter = counter;
                strcpy(current_end_time,FITNESS_DATAS.date);
                strcat(current_end_time," ");
                strcat(current_end_time,FITNESS_DATAS.time);
            }
        }
        if (periodcounter > max_periodcounter)
        {
            max_periodcounter = periodcounter;
            strcpy(start_time,current_start_time);
            strcpy(end_time,current_end_time);
        }
    }
    printf("Longest period start: %s\nLongest period end: %s\n",start_time,end_time);
    counter = 0;
}









