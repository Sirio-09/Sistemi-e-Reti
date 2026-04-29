#include <stdio.h>
#include "testing/test.h"
#include "../exercise.h"


/**
 * @brief Tests initialize_shipping.
 */
void test_initialize_shipping() {
    openTestGroup("initialize_shipping");

    Shipping s;
    assert("returns -1 on NULL shipping", initialize_shipping(NULL, "NYC", "LA", 10.5, 5.0, 100.0) == -1);
    assert("returns -1 on NULL source", initialize_shipping(&s, NULL, "LA", 10.5, 5.0, 100.0) == -1);
    assert("returns -1 on NULL destination", initialize_shipping(&s, "NYC", NULL, 10.5, 5.0, 100.0) == -1);
    assert("returns -1 on negative weight", initialize_shipping(&s, "NYC", "LA", -1.0, 5.0, 100.0) == -1);
    assert("returns -1 on negative volume", initialize_shipping(&s, "NYC", "LA", 10.5, -1.0, 100.0) == -1);
    assert("returns -1 on negative distance", initialize_shipping(&s, "NYC", "LA", 10.5, 5.0, -1.0) == -1);

    assert("returns 0 on valid input", initialize_shipping(&s, "NYC", "LA", 10.5, 5.0, 100.0) == 0);
    assert("source is correctly set", strcmp(s.source, "NYC") == 0);
    assert("destination is correctly set", strcmp(s.destination, "LA") == 0);
    assert("weight is correctly set", s.package_weight == 10.5);
    assert("volume is correctly set", s.package_volume == 5.0);
    assert("distance is correctly set", s.distance == 100.0);

    assert("returns 0 on zero values", initialize_shipping(&s, "Boston", "Miami", 0.0, 0.0, 0.0) == 0);
    assert("zero weight set correctly", s.package_weight == 0.0);

    closeTestGroup();
}

/**
 * @brief Tests serialize_shipping.
 */
void test_serialize_shipping() {
    openTestGroup("serialize_shipping");

    const char *filename = "serialize_shipping_test.tmp";
    Shipping ss = {"NYC", "LA", 10.5, 5.0, 100.0};

    remove(filename);

    assert("returns -1 on NULL shipping", serialize_shipping(NULL, "serialize_shipping_test.tmp") == -1);
    assert("returns -1 on NULL filename", serialize_shipping(&ss, NULL) == -1);
    assert("returns 0 on valid input", serialize_shipping(&ss, "serialize_shipping_test.tmp") == 0);

    FILE *file = fopen(filename, "r");
    assert("serialized file exists", file != NULL);
    if (file != NULL) {
        char source[MAX_STR_LENGTH];
        char destination[MAX_STR_LENGTH];
        float weight, volume, distance;

        assert("serialized content is readable", fscanf(file, "%29s %29s %f %f %f\n", source, destination, &weight, &volume, &distance) == 5);
        assert("serialized source is correct", strcmp(source, "NYC") == 0);
        assert("serialized destination is correct", strcmp(destination, "LA") == 0);
        assert("serialized weight is correct", weight == 10.5);
        assert("serialized volume is correct", volume == 5.0);
        assert("serialized distance is correct", distance == 100.0);
        fclose(file);
    }

    remove(filename);

    closeTestGroup();
}

/**
 * @brief Tests unserialize_shipping.
 */
void test_unserialize_shipping() {
    openTestGroup("unserialize_shipping");

    const char *filename = "unserialize_shipping_test.tmp";
    Shipping us;
    remove(filename);

    assert("returns -1 on NULL shipping", unserialize_shipping(NULL, "unserialize_shipping_test.tmp") == -1);
    assert("returns -1 on NULL filename", unserialize_shipping(&us, NULL) == -1);
    assert("returns -1 on nonexistent file", unserialize_shipping(&us, "nonexistent_xyz.tmp") == -1);

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "NYC LA 10.5 5.0 100.0\n");
        fclose(file);
    }

    Shipping restored;

    assert("returns 0 on valid file", unserialize_shipping(&restored, "unserialize_shipping_test.tmp") == 0);
    assert("source restored correctly", strcmp(restored.source, "NYC") == 0);
    assert("destination restored correctly", strcmp(restored.destination, "LA") == 0);
    assert("weight restored correctly", restored.package_weight == 10.5);
    assert("volume restored correctly", restored.package_volume == 5.0);
    assert("distance restored correctly", restored.distance == 100.0);

    remove(filename);

    closeTestGroup();
}

/**
 * @brief Tests sort_shippings_by_cost.
 */
void test_sort_shippings_by_cost() {
    openTestGroup("sort_shippings_by_cost");

    Shipping shippings[3] = {
        {"NYC", "LA", 2.0, 5.0, 2.0},     // cost: 20
        {"Boston", "Miami", 1.0, 2.0, 5.0}, // cost: 10
        {"Seattle", "Denver", 3.0, 1.0, 2.0} // cost: 6
    };

    assert("returns -1 on NULL array", sort_shippings_by_cost(NULL, 3) == -1);
    assert("returns -1 on n = 0", sort_shippings_by_cost(shippings, 0) == -1);
    assert("returns -1 on n < 0", sort_shippings_by_cost(shippings, -1) == -1);
    assert("returns -1 on n > MAX_LENGTH", sort_shippings_by_cost(shippings, MAX_LENGTH + 1) == -1);
    assert("returns 0 on n = 1", sort_shippings_by_cost(shippings, 1) == 0);
    assert("returns 0 on valid input", sort_shippings_by_cost(shippings, 3) == 0);
    
    float cost1 = shippings[0].package_weight * shippings[0].package_volume * shippings[0].distance;
    float cost2 = shippings[1].package_weight * shippings[1].package_volume * shippings[1].distance;
    float cost3 = shippings[2].package_weight * shippings[2].package_volume * shippings[2].distance;
    
    assert("first element has lowest cost", cost1 == 6.0);
    assert("second element sorted correctly", cost2 == 10.0);
    assert("third element has highest cost", cost3 == 20.0);

    assert("already sorted stays sorted", sort_shippings_by_cost(shippings, 3) == 0);
    assert("order preserved after re-sort", strcmp(shippings[0].source, "Seattle") == 0);

    closeTestGroup();
}

/**
 * @brief Tests print_shipping.
 */
void test_print_shipping() {
    openTestGroup("print_shipping");

    print_shipping(NULL);
    assert("NULL shipping does not crash", 1);

    Shipping ps = {"NYC", "LA", 10.5, 5.0, 100.0};
    print_shipping(&ps);
    char **out = getLastCapturedPrints(1);
    assert("prints correct format", strcmp(out[0], "Source: NYC, Destination: LA, Weight: 10.50, Volume: 5.00, Distance: 100.00\n") == 0);

    closeTestGroup();
}

/**
 * @brief Tests print_shippings.
 */
void test_print_shippings() {
    openTestGroup("print_shippings");

    Shipping arr[2] = {
        {"NYC", "LA", 10.5, 5.0, 100.0},
        {"Boston", "Miami", 2.0, 3.0, 50.0}
    };

    print_shippings(NULL, 2);
    assert("NULL array does not crash", 1);

    print_shippings(arr, 0);
    assert("n = 0 does not crash", 1);

    print_shippings(arr, MAX_LENGTH + 1);
    assert("n > MAX_LENGTH does not crash", 1);

    print_shippings(arr, 2);
    char **out = getLastCapturedPrints(2);
    assert("first shipping printed correctly", strcmp(out[0], "Source: NYC, Destination: LA, Weight: 10.50, Volume: 5.00, Distance: 100.00\n") == 0);
    assert("second shipping printed correctly", strcmp(out[1], "Source: Boston, Destination: Miami, Weight: 2.00, Volume: 3.00, Distance: 50.00\n") == 0);

    closeTestGroup();
}

void test_random_shipping() {
    openTestGroup("random_shipping");

    Shipping shippings[10] = {
        {"NYC", "LA", 10.5, 5.0, 100.0},
        {"Boston", "Miami", 2.0, 3.0, 50.0},
        {"Seattle", "Denver", 3.0, 1.0, 200.0},
        {"Chicago", "Dallas", 5.0, 4.0, 150.0},
        {"Phoenix", "Portland", 1.5, 2.0, 75.0},
        {"Atlanta", "Houston", 4.0, 3.0, 120.0},
        {"Philadelphia", "Washington", 2.5, 2.5, 30.0},
        {"San Francisco", "San Diego", 6.0, 6.0, 80.0},
        {"Detroit", "Cleveland", 3.5, 3.5, 90.0},
        {"Memphis", "Nashville", 1.0, 1.0, 60.0}
    };

    srand(42); // Set a fixed seed for reproducibility
    Shipping expected = shippings[6]; // With seed 42, the random index should be 6

    Shipping actual;
    int result = random_shipping(NULL, shippings, 10);
    assert("returns -1 on NULL output shipping", result == -1);

    result = random_shipping(&actual, NULL, 10);
    assert("returns -1 on NULL input array", result == -1);

    result = random_shipping(&actual, shippings, 0);
    assert("returns -1 on invalid n (under)", result == -1);

    result = random_shipping(&actual, shippings, MAX_LENGTH + 1);
    assert("returns -1 on invalid n (over)", result == -1);

    result = random_shipping(&actual, shippings, 10);
    assert("returns 0 on valid input", result == 0);
    assert("random shipping has correct source", strcmp(actual.source, expected.source) == 0);
    assert("random shipping has correct destination", strcmp(actual.destination, expected.destination) == 0);
    assert("random shipping has correct weight", actual.package_weight == expected.package_weight);  
    
    closeTestGroup();
}

int main() {
    test_initialize_shipping();
    test_serialize_shipping();
    test_unserialize_shipping();
    test_sort_shippings_by_cost();
    test_print_shipping();
    test_print_shippings();
    test_random_shipping();

    return 0;
}

