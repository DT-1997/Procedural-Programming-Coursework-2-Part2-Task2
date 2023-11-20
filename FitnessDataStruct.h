
#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	char steps[4];
} FITNESS_DATA;

typedef struct {
	char filename[18];
	char fileformat[6];
} Filename;

// Helper function prototypes
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);
void check_filename();
void count_records();
void find_feweststeps();
void find_largeststeps();
void find_meanstepcount();
void find_longestperiod();
#endif // FITNESS_DATA_STRUCT_H
