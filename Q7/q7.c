#include <stdio.h>

unsigned long checks_orig = 0, checks_opt = 0;

int is_prime_orig(unsigned long n) {
    checks_orig = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i <= n / i; i++) {
        checks_orig++;
        if (n % i == 0) return 0;
    }
    return 1;
}

int is_prime_6k(unsigned long n) {
    checks_opt = 0;
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    checks_opt++; if (n % 2 == 0) return 0;
    checks_opt++; if (n % 3 == 0) return 0;

    for (unsigned long i = 5; i <= n / i; i += 6) {
        checks_opt++; if (n % i == 0) return 0;
        checks_opt++; if (n % (i + 2) == 0) return 0;
    }
    return 1;
}

int main(void) {
    unsigned long tests[] = {97, 100, 7919, 104729, 1000003, 1000000007ULL};
    printf("Number       | Result    | Original Divs | 6k+-1 Divs | Reduction\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < 6; i++) {
        int r1 = is_prime_orig(tests[i]);
        int r2 = is_prime_6k(tests[i]);
        double pct = 100.0 * (checks_orig - checks_opt) / checks_orig;
        printf("%-12lu | %-9s | %-13lu | %-10lu | %.1f%%\n",
               tests[i], (r1 && r2) ? "Prime" : "Composite",
               checks_orig, checks_opt, pct);
    }
    return 0;
}