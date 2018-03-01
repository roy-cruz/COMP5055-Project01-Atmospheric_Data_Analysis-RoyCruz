/**
 * climate.c
 *
 * Performs analysis on climate data provided by the
 * National Oceanic and Atmospheric Administration (NOAA).
 *
 * Input:    Tab-delimited file(s) to analyze.
 * Output:   Summary information about the data.
 *
 * Compile:  gcc -g -Wall -o climate climate.c
 *           (or run make)
 *
 * Run:      ./climate data_tn.tdv data_wa.tdv
 *
 *
 * Opening file: data_tn.tdv
 * Opening file: data_wa.tdv
 * States found: WA TN
  * -- State: WA --
 * Number of Records: 48357
 * Average Humidity: 61.3%
 * Average Temperature: 52.9F
 * Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
 * Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
 * Lightning Strikes: 1190
 * Records with Snow Cover: 1383
 * Average Cloud Cover: 54.5%
 * -- State: TN --
 * Number of Records: 17097
 * Average Humidity: 49.4%
 * Average Temperature: 58.3F
 * Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
 * Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
 * Lightning Strikes: 781
 * Records with Snow Cover: 107
 * Average Cloud Cover: 53.0%

 *
 * TDV format:
 *
 * CA 1428300000000 9prc 93.0 0.0 100.0 0.0 95644.0  277.58716
 * CA 1430308800000 9prc 4.0  0.0 100.0 0.0 99226.0  282.63037
 * CA 1428559200000 9prr 61.0 0.0 0.0   0.0 102112.0 285.07513
 * CA 1428192000000 9prk 57.0 0.0 100.0 0.0 101765.0 285.21332
 * CA 1428170400000 9prd 73.0 0.0 22.0  0.0 102074.0 285.10425
 * CA 1429768800000 9pr6 38.0 0.0 0.0   0.0 101679.0 283.9342
 * CA 1428127200000 9prj 98.0 0.0 100.0 0.0 102343.0 285.75
 * CA 1428408000000 9pr4 93.0 0.0 100.0 0.0 100645.0 285.82413
 *
 * Each field is separated by a tab character \t and ends with a newline \n.
 *
 * Fields:
 *      state code (e.g., CA, TX, etc),
 *      timestamp (time of observation as a UNIX timestamp),
 *      geolocation (geohash string),
 *      humidity (0 - 100%),
 *      snow (1 = snow present, 0 = no snow),
 *      cloud cover (0 - 100%),
 *      lightning strikes (1 = lightning strike, 0 = no lightning),
 *      pressure (Pa),
 *      surface temperature (Kelvin)
 */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_STATES 50

/* TODO: Add elements to the climate_info struct as necessary. */
struct climate_info 
{
    char code[3]; 
    unsigned long num_records;
    long double humidity;
    int snow;
    long double cloud_cover;
    long double pressure;
    long double surface_temperature; 
    long double av_temp;
    long double av_humidity;
    long double max_temp;
    long double min_temp;
    int lightning_strikes;
    long double av_cloudCover;
    int timeStamp;
    long int max_timeStamp;
    long int min_timeStamp;
    
};

struct climate_info *create_state(char* tokens[], int tokenIndex);
void analyze_file(FILE *file, struct climate_info *states[], int num_states);
void print_report(struct climate_info *states[], int num_states);

int main(int argc, char *argv[]) 
{
    /* TODO: fix this conditional. You should be able to read multiple files. */
    if (argc < 2) 
    {
        printf("Usage: %s tdv_file1 tdv_file2 ... tdv_fileN \n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Let's create an array to store our state data in. As we know, there are
     * 50 US states. */
    struct climate_info *states[NUM_STATES] = {NULL};

    int i;
    for (i = 1; i < argc; ++i) 
    {
        /* TODO: Open the file for reading */
        /* TODO: If the file doesn't exist, print an error message and move on
         * to the next file. */

        FILE *file = fopen(argv[i], "r");
        if(file == NULL)
        {
            perror("fopen"); //perror prints the actual error 
            return EXIT_FAILURE; //we don't return 0 if it failed
        }

        /* TODO: Analyze the file */

         analyze_file(file, states, NUM_STATES); 
    }

    /* Now that we have recorded data for each file, we'll summarize them: */
    print_report(states, NUM_STATES);
    return 0;
}

//create a new method that reads the dates (in our case its the state code) of each line
//and stores it inside the struct

/* This function tokenizes each line in the tdv file, and updates a 'tokenIndex variable', and updates it. We do 
this because the "create_state" function's parameters takes in the tokens array, as well as the tokenIndex, to 
update the values into the new state array */

struct climate_info *get_state(char* line)
{ 
    char* token = strtok(line, "\t");
    char* tokens[9];

    int tokenIndex = 0;

    while (token != NULL && tokenIndex < 9)
    {
        tokens[tokenIndex++] = token;
        token = strtok(NULL, "\t");
    }

    return create_state(tokens, tokenIndex);

}

/* This function allocates space in heap for a new array, called state. This is an array of structs that stores information for EACH 
state, using the tokens created in the "get_state" function */
struct climate_info *create_state(char* tokens[], int tokenIndex)

{ 
    struct climate_info* state = malloc(sizeof(struct climate_info));
    //update all the information in this to match what is given in the information table above
    strncpy(state->code, tokens[0], 2);
    state->timeStamp = (atoi(tokens[1]))/1000;
    state->humidity = atof(tokens[3]);
    state->snow = atof(tokens[4]);
    state->cloud_cover = atof(tokens[5]);
    state->lightning_strikes = atof(tokens[6]);
    state->pressure = atof(tokens[7]);
    state->surface_temperature = ((atof(tokens[8]))*9/5 - 459.67);

    return state;
}

/* adds each state array to the states array if it isn't there  */

void add_State(struct climate_info *states[], struct climate_info *state, int index)
{
        
        if (states[index] == NULL)
        {
            states[index] = state;
            states[index]->num_records = 1;

        }

}

/* If the state is already in the states array, the we just update the information of each state. Most calculations are in this function*/

void add_Info(struct climate_info *states[], struct climate_info *state, int index)
{
    long double max_temp = state->surface_temperature;
    long double min_temp = state->surface_temperature;

    states[index]->num_records++;
    //to go from kelvin to fahrenheit we have to *9/5 and - 459.67
    states[index]->humidity += state->humidity;
    states[index]->cloud_cover += state->cloud_cover; 
    states[index]->pressure += state->pressure;
    states[index]->surface_temperature += state->surface_temperature;

    //LIGHTNING STRIKES
    states[index]->lightning_strikes += state->lightning_strikes;

    //SNOW COVER
    states[index]->snow += state->snow;  

    //AVERAGE HUMIDITY
    states[index]->av_humidity = ((states[index]-> humidity)/states[index]->num_records);

    //AVERAGE TEMP
    states[index]->av_temp = ((states[index]-> surface_temperature)/states[index]->num_records);
    
    //MAX TEMP
    if (max_temp > states[index]->max_temp)
    {
        states[index]->max_temp = state->surface_temperature;
        states[index]->max_timeStamp = state->timeStamp;
    }

    //MIN TEMP
    if (min_temp < states[index]->min_temp)
    {
        states[index]->min_temp = state->surface_temperature;
        states[index]->min_timeStamp = state->timeStamp;
    }

    //AVERAGE CLOUD COVER
    states[index]->av_cloudCover = ((states[index]->cloud_cover)/states[index]->num_records);

}

/* TODO function documentation */
//if theres a new state, you have to dynamically allocate memory
//if its an old state, you update the information
void analyze_file(FILE *file, struct climate_info **states, int num_states) 
{

    const int line_sz = 100;
    char line[line_sz];
    char *token;
    int index = 0;
    int val = 0;


    while (fgets(line, line_sz, file) != NULL)
    
    {
        struct climate_info *state = get_state(line);

        if (state == NULL)
            continue;

        char *code = state->code;

        for(int i = 0; i < num_states;i++)                  
        {                                                   

            if (states[i] == NULL) 
            {                                         
                add_State(states, state,i);                 
                break;                                      
            } 

            else 
            {                                        
                int val = strcmp(states[i]->code, code);    
                if (val == 0)                               
                {                                           
                    add_Info(states, state, i);             
                    break;                                  

                }                                           

            }                                               

        }         
        
    }

}

/* printing out all the information*/
void print_report(struct climate_info *states[], int num_states)
{
    printf("States found: ");
    int i;
    for (i = 0; i < num_states; ++i) 
    {
        if (states[i] != NULL) 
        {
            struct climate_info *info = states[i];
            printf("%s ", info->code);
        }
    }
    printf("\n");

    for (i = 0; i < num_states; ++i) 
    {
        if (states[i] != NULL) 
        {
            struct climate_info *info = states[i];
            printf("State: %s\n", states[i]->code); 
            printf("Number of Records: %lu\n",states[i]->num_records);
            printf("Average Humidity: %0.1Lf%s\n", states[i]->av_humidity, "%");
            printf("Average Temperature: %0.1Lf%s\n", states[i]->av_temp,"F");
            printf("Max Temperature: %0.1Lf%s", states[i]->max_temp,"F on ");
            printf("%s", ctime(&states[i]->max_timeStamp));
            printf("Min Temperature: %0.1Lf%s", states[i]->min_temp, "F on ");
            printf("%s", ctime(&states[i]->min_timeStamp));
            printf("Lightning Strikes: %d\n", states[i]->lightning_strikes);
            printf("Records with Snow Cover: %d\n", states[i]->snow);
            printf("Average Cloud Cover: %0.1Lf%s\n", states[i]->av_cloudCover, "%");
            printf("%s\n", "---------------------------");
        }
    }
}
