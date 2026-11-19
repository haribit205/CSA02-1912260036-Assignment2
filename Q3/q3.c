#include <stdio.h>

long server_calls = 0;

int verify_disability_card(int passenger_id, int has_card) {
    (void)passenger_id;
    server_calls++;
    return has_card;
}

int is_senior(int age) { return age >= 60; }
int is_eligible_class(int cls) { return (cls == 2 || cls == 3); }

int main(void) {
    int total_passengers = 1000;
    int ages[1000], classes[1000], cards[1000];

    for (int i = 0; i < total_passengers; i++) {
        ages[i]    = (i % 5 == 0) ? 65 : 35;            // 20% senior
        classes[i] = (i % 5 != 1 && i % 5 != 2) ? 2 : 1; // 60% eligible
        cards[i]   = (i % 10 == 3) ? 1 : 0;              // 10% cardholders
    }

    // Order A: Cheap senior/class check first
    server_calls = 0;
    int granted_A = 0;
    for (int i = 0; i < total_passengers; i++) {
        if ((is_senior(ages[i]) && is_eligible_class(classes[i])) ||
            verify_disability_card(i, cards[i])) {
            granted_A++;
        }
    }
    long calls_A = server_calls;

    // Order B: Slow verification first
    server_calls = 0;
    int granted_B = 0;
    for (int i = 0; i < total_passengers; i++) {
        if (verify_disability_card(i, cards[i]) ||
            (is_senior(ages[i]) && is_eligible_class(classes[i]))) {
            granted_B++;
        }
    }
    long calls_B = server_calls;

    // Order C: Non-short-circuit bitwise (& and |)
    server_calls = 0;
    int granted_C = 0;
    for (int i = 0; i < total_passengers; i++) {
        if ((is_senior(ages[i]) & is_eligible_class(classes[i])) |
            verify_disability_card(i, cards[i])) {
            granted_C++;
        }
    }
    long calls_C = server_calls;

    printf("Total Passengers: %d\n", total_passengers);
    printf("Order A [(senior && class) || slow_verify]: Granted=%d, Server Calls=%ld\n", granted_A, calls_A);
    printf("Order B [slow_verify || (senior && class)]: Granted=%d, Server Calls=%ld\n", granted_B, calls_B);
    printf("Order C [Bitwise & and | (No short-circuit)]: Granted=%d, Server Calls=%ld\n", granted_C, calls_C);
    return 0;
}