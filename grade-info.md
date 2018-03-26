# Grade Information

## Test 1: Compilation

No dead/leftover/unnecessary code should be highlighted here. [1 pts]

```
+ gcc -g -Wall climate.c -o climate
climate.c:246:9: warning: unused variable 'index' [-Wunused-variable]
    int index = 0;
        ^
climate.c:247:9: warning: unused variable 'val' [-Wunused-variable]
    int val = 0;
        ^
climate.c:245:11: warning: unused variable 'token' [-Wunused-variable]
    char *token;
          ^
climate.c:306:34: warning: unused variable 'info' [-Wunused-variable]
            struct climate_info *info = states[i];
                                 ^
4 warnings generated.
+ test_end
+ return=0
+ [Output Lines: 13]
```

## Test 2: No Args

Program should gracefully exit with no arguments [1 pts]

```
+ ./climate
Usage: ./climate tdv_file1 tdv_file2 ... tdv_fileN 
+ test_end
+ return=1
+ [Output Lines: 1]
```

## Test 3: Missing File

Program should gracefully exit and print an error message [1 pts]

```
+ ./climate this_file_should_not_exist.tdv
fopen: No such file or directory
+ test_end
+ return=1
+ [Output Lines: 1]
```

## Test 4: Use perror to report file errors

```
+ grep -A2 -B2 perror climate.c
        if(file == NULL)
        {
            perror("fopen"); //perror prints the actual error 
            return EXIT_FAILURE; //we don't return 0 if it failed
        }
+ test_end
+ return=0
+ [Output Lines: 5]
```

## Test 5: Use of memory allocation functions

```
+ grep -A2 -B2 .alloc climate.c
}

/* This function allocates space in heap for a new array, called state. This is an array of structs that stores information for EACH 
state, using the tokens created in the "get_state" function */
struct climate_info *create_state(char* tokens[], int tokenIndex)
--
--

{ 
    struct climate_info* state = malloc(sizeof(struct climate_info));
    //update all the information in this to match what is given in the information table above
    strncpy(state->code, tokens[0], 2);
--
--

/* TODO function documentation */
//if theres a new state, you have to dynamically allocate memory
//if its an old state, you update the information
void analyze_file(FILE *file, struct climate_info **states, int num_states) 
+ test_end
+ return=0
+ [Output Lines: 19]
```

## Test 6: Tennessee

```
+ ./climate ../../220/p1-files/data_tn.tdv
States found: TN 
State: TN
Number of Records: 17097
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Dec 29 11:25:56 1969
Min Temperature: -11.1F on Sun Dec 14 08:34:18 1969
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0%
---------------------------
+ test_end
+ return=0
+ [Output Lines: 11]
```

## Test 7: Missing File + Valid File

Should still print data for TN [1 pts]

```
+ ./climate this_file_should_not_exist.tdv ../../220/p1-files/data_tn.tdv
fopen: No such file or directory
+ test_end
+ return=1
+ [Output Lines: 1]
```

## Test 8: Washington

```
+ ./climate ../../220/p1-files/data_wa.tdv
States found: WA 
State: WA
Number of Records: 48357
Average Humidity: 61.3%
Average Temperature: 52.9F
Max Temperature: 125.7F on Mon Jan 12 10:28:43 1970
Min Temperature: -18.7F on Mon Dec 29 02:17:34 1969
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5%
---------------------------
+ test_end
+ return=0
+ [Output Lines: 11]
```

## Test 9: Single state (WA) split across two files

This output should be the same as the previous test. [1 pts]

```
+ ./climate ../../220/p1-files/data_wa_1.tdv ../../220/p1-files/data_wa_2.tdv
States found: WA 
State: WA
Number of Records: 48357
Average Humidity: 61.3%
Average Temperature: 52.9F
Max Temperature: 125.7F on Mon Jan 12 10:28:43 1970
Min Temperature: -18.7F on Mon Dec 29 02:17:34 1969
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5%
---------------------------
+ test_end
+ return=0
+ [Output Lines: 11]
```

## Test 10: Tennessee + Washington

```
+ ./climate ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_wa.tdv
States found: TN WA 
State: TN
Number of Records: 17097
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Dec 29 11:25:56 1969
Min Temperature: -11.1F on Sun Dec 14 08:34:18 1969
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0%
---------------------------
State: WA
Number of Records: 48357
Average Humidity: 61.3%
Average Temperature: 52.9F
Max Temperature: 125.7F on Mon Jan 12 10:28:43 1970
Min Temperature: -18.7F on Mon Dec 29 02:17:34 1969
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5%
---------------------------
+ test_end
+ return=0
+ [Output Lines: 21]
```

## Test 11: Multi State

```
+ ./climate ../../220/p1-files/data_multi.tdv
States found: CA CO PA FL LA 
State: CA
Number of Records: 84601
Average Humidity: 38.1%
Average Temperature: 62.1F
Max Temperature: 126.5F on Sat Jan 10 11:25:55 1970
Min Temperature: -25.9F on Sun Dec 14 02:17:34 1969
Lightning Strikes: 1616
Records with Snow Cover: 599
Average Cloud Cover: 34.7%
---------------------------
State: CO
Number of Records: 67040
Average Humidity: 60.8%
Average Temperature: 49.6F
Max Temperature: 116.1F on Mon Dec  8 11:25:56 1969
Min Temperature: -29.8F on Fri Dec 26 02:17:34 1969
Lightning Strikes: 4763
Records with Snow Cover: 3082
Average Cloud Cover: 40.1%
---------------------------
State: PA
Number of Records: 19526
Average Humidity: 57.4%
Average Temperature: 48.8F
Max Temperature: 106.4F on Sat Dec 27 04:28:44 1969
Min Temperature: -30.4F on Sun Dec 14 08:34:18 1969
Lightning Strikes: 667
Records with Snow Cover: 575
Average Cloud Cover: 59.2%
---------------------------
State: FL
Number of Records: 35632
Average Humidity: 38.2%
Average Temperature: 76.1F
Max Temperature: 122.1F on Mon Jan  5 04:28:43 1970
Min Temperature: 0.0F on Wed Dec 31 16:00:00 1969
Lightning Strikes: 1436
Records with Snow Cover: 0
Average Cloud Cover: 39.1%
---------------------------
State: LA
Number of Records: 23350
Average Humidity: 42.1%
Average Temperature: 69.0F
Max Temperature: 126.1F on Thu Dec 25 11:25:56 1969
Min Temperature: 0.0F on Wed Dec 31 16:00:00 1969
Lightning Strikes: 814
Records with Snow Cover: 0
Average Cloud Cover: 44.5%
---------------------------
+ test_end
+ return=0
+ [Output Lines: 51]
```

## Test 12: Multi State + TN + WA

```
+ ./climate ../../220/p1-files/data_multi.tdv ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_wa.tdv
States found: CA CO PA FL LA TN WA 
State: CA
Number of Records: 84601
Average Humidity: 38.1%
Average Temperature: 62.1F
Max Temperature: 126.5F on Sat Jan 10 11:25:55 1970
Min Temperature: -25.9F on Sun Dec 14 02:17:34 1969
Lightning Strikes: 1616
Records with Snow Cover: 599
Average Cloud Cover: 34.7%
---------------------------
State: CO
Number of Records: 67040
Average Humidity: 60.8%
Average Temperature: 49.6F
Max Temperature: 116.1F on Mon Dec  8 11:25:56 1969
Min Temperature: -29.8F on Fri Dec 26 02:17:34 1969
Lightning Strikes: 4763
Records with Snow Cover: 3082
Average Cloud Cover: 40.1%
---------------------------
State: PA
Number of Records: 19526
Average Humidity: 57.4%
Average Temperature: 48.8F
Max Temperature: 106.4F on Sat Dec 27 04:28:44 1969
Min Temperature: -30.4F on Sun Dec 14 08:34:18 1969
Lightning Strikes: 667
Records with Snow Cover: 575
Average Cloud Cover: 59.2%
---------------------------
State: FL
Number of Records: 35632
Average Humidity: 38.2%
Average Temperature: 76.1F
Max Temperature: 122.1F on Mon Jan  5 04:28:43 1970
Min Temperature: 0.0F on Wed Dec 31 16:00:00 1969
Lightning Strikes: 1436
Records with Snow Cover: 0
Average Cloud Cover: 39.1%
---------------------------
State: LA
Number of Records: 23350
Average Humidity: 42.1%
Average Temperature: 69.0F
Max Temperature: 126.1F on Thu Dec 25 11:25:56 1969
Min Temperature: 0.0F on Wed Dec 31 16:00:00 1969
Lightning Strikes: 814
Records with Snow Cover: 0
Average Cloud Cover: 44.5%
---------------------------
State: TN
Number of Records: 17097
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Dec 29 11:25:56 1969
Min Temperature: -11.1F on Sun Dec 14 08:34:18 1969
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0%
---------------------------
State: WA
Number of Records: 48357
Average Humidity: 61.3%
Average Temperature: 52.9F
Max Temperature: 125.7F on Mon Jan 12 10:28:43 1970
Min Temperature: -18.7F on Mon Dec 29 02:17:34 1969
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5%
---------------------------
+ test_end
+ return=0
+ [Output Lines: 71]
```

## Test 13: File with all Zero Values

```
+ ./climate ../../220/p1-files/data_blank.tdv
States found: TX 
State: TX
Number of Records: 14
Average Humidity: 0.0%
Average Temperature: -459.7F
Max Temperature: 0.0F on Wed Dec 31 16:00:00 1969
Min Temperature: -459.7F on Wed Dec 31 16:00:00 1969
Lightning Strikes: 0
Records with Snow Cover: 0
Average Cloud Cover: 0.0%
---------------------------
+ test_end
+ return=0
+ [Output Lines: 11]
```

## Test 14: 3x Tennessee

```
+ ./climate ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_tn.tdv
States found: TN 
State: TN
Number of Records: 51291
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Dec 29 11:25:56 1969
Min Temperature: -11.1F on Sun Dec 14 08:34:18 1969
Lightning Strikes: 2343
Records with Snow Cover: 321
Average Cloud Cover: 53.0%
---------------------------
+ test_end
+ return=0
+ [Output Lines: 11]
```


## Deductions

* Remember to clean up unused variables/code [-0.5]
* Incorrect date conversion  [-1]
* (Test 7): TN + Missing File [-1]
* (Test 13): Zero values: Max temp should be -459.7F [-1]
