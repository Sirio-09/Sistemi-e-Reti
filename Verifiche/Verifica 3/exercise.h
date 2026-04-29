#define MAX_STR_LENGTH 30
#define MAX_LENGTH 100

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char source[MAX_STR_LENGTH];
    char destination[MAX_STR_LENGTH];

    float package_weight;
    float package_volume;

    float distance;
} Shipping;

// Prototypes of the functions to be implemented
int initialize_shipping(Shipping*, char*, char*, float, float, float);
int serialize_shipping(Shipping*, char*);
int unserialize_shipping(Shipping*, char*);
int sort_shippings_by_cost(Shipping*, int);
void print_shipping(Shipping*);
void print_shippings(Shipping*, int);

/**
 * @brief Initializes a Shipping structure with the given parameters.
 * @param s Pointer to the Shipping structure to initialize
 * @param source The source location of the shipping
 * @param destination The destination location of the shipping
 * @param package_weight The weight of the package
 * @param package_volume The volume of the package
 * @param distance The distance of the shipping
 * @return 0 on success, non-zero on failure
 */
int initialize_shipping(Shipping* s, char *source, char *destination, float package_weight, float package_volume, float distance) {
    if(s == NULL || source == NULL || destination == NULL || package_weight < 0 || package_volume < 0 || distance < 0){
        return -1;
    }

    strncpy(s -> source, source, MAX_STR_LENGTH);
    strncpy(s -> destination, destination, MAX_STR_LENGTH);
    s -> package_weight = package_weight;
    s -> package_volume = package_volume;
    s -> distance = distance;

    return 0;
}

/**
 * @brief Serializes a Shipping structure to a file.
 * @param s Pointer to the Shipping structure to serialize
 * @param filename The name of the file to write to
 * @return 0 on success, non-zero on failure
 */
int serialize_shipping(Shipping* s, char *filename) {
    if(s == NULL || filename == NULL){
        return -1;
    }

    FILE *fp = fopen(filename, "w");

    if(fp == NULL){
        return -1;
    }

    fprintf(fp, "%s %s %f %f %f\n", s -> source, s -> destination, s -> package_weight, s -> package_volume, s -> distance);

    fclose(fp);
    return 0;
}

/**
 * @brief Unserializes a Shipping structure from a file.
 * @param s Pointer to the Shipping structure to populate
 * @param filename The name of the file to read from
 * @return 0 on success, non-zero on failure
 */
int unserialize_shipping(Shipping* s, char *filename) {
    if(s == NULL || filename == NULL){
        return -1;
    }

    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        return -1;
    }


    fscanf(fp, "%s %s %f %f %f\n", s -> source, s -> destination, s -> package_weight, s -> package_volume, s -> distance);

    fclose(fp);
    return 0;
}

/**
 * @brief Sorts an array of shippings by cost in ascending order.
 * @param shippings Array of Shipping structures to sort
 * @param n The number of shippings in the array
 * @return 0 on success, non-zero on failure
 */
int sort_shippings_by_cost(Shipping *shippings, int n) {
    if(shippings == NULL || n <= 0){
        return -1;
    }

    //cost = weight * volume * distance
    Shipping temp;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            float cost1 = shippings[i].distance * shippings[i].package_volume * shippings[i].package_weight;
            float cost2 = shippings[j].distance * shippings[j].package_volume * shippings[j].package_weight;

            if(cost1 > cost2){
                temp = shippings[j];
                shippings[j] = shippings[i];
                shippings[i] = temp;
            }
        }
    }

    return 0;
}

/**
 * @brief Prints a single shipping to the standard output.
 * @param s Pointer to the Shipping structure to print
 */
void print_shipping(Shipping* s) {
    if(s == NULL){
        return -1;
    }

    printf("Source: %s, Destination: %s, Weight: %f, Volume: %f, Distance: %f\n", s -> source, s -> destination, s -> package_weight, s -> package_volume, s -> distance);
}

/**
 * @brief Prints an array of shippings to the standard output.
 * @param shippings Array of Shipping structures to print
 * @param n The number of shippings in the array
 */
void print_shippings(Shipping *shippings, int n) {
    if(shippings == NULL || n <= 0){
        return -1;
    }

    for(int i = 0; i < n; i++){
        printf("Source: %s, Destination: %s, Weight: %f, Volume: %f, Distance: %f\n", shippings[i].source, shippings[i].destination, shippings[i].package_weight, shippings[i].package_volume, shippings[i].distance);
    }
}

/**
 * @brief Selects a random shipping from an array of shippings. If the array
 * is empty, returns -1.
 * @param s Pointer to the Shipping structure to populate with the random shipping
 * @param shippings Array of Shipping structures to select from
 * @param n The number of shippings in the array
 * @return 0 on success, non-zero on failure
 */
int random_shipping(Shipping* s, Shipping* shippings, int n) {
    if(s == NULL || shippings == NULL || n <= 0){
        return -1;
    }

    int rnd = (rand() % n);

    strncpy(s -> source, shippings[rnd].source, MAX_STR_LENGTH);
    strncpy(s -> , shipping[rnd].destination, MAX_STR_LENGTH);
    s -> package_weight = shippings[rnd].package_weight;
    s -> package_volume = shippings[rnd].package_volume;
    s -> distance = shippings[rnd].distance;

    return 0;
}
