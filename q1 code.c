#include <stdio.h>

void test_buggy(int price, int qty, int senior) {
    int total = price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;
    int net   = total > 1000 ? total - 50 : total;
    printf("Bill (price=%d, qty=%d, senior=%d) -> Buggy total=%d, net=%d\n",
           price, qty, senior, total, net);
}

void test_fixed(double price, int qty, int senior) {
    if (price < 0 || qty < 0 || (senior != 0 && senior != 1)) {
        printf("Invalid billing input!\n");
        return;
    }
    double gross    = price * qty;
    double discount = senior ? (gross * 0.15) : 0.0;
    double after_dc = gross - discount;
    double gst      = after_dc * 0.05;
    double total    = after_dc + gst;
    double net      = (total > 1000.0) ? (total - 50.0) : total;
    printf("Bill (price=%.2f, qty=%d, senior=%d) -> Gross=%.2f, Disc=%.2f, GST=%.2f, Total=%.2f, Net=%.2f\n",
           price, qty, senior, gross, discount, gst, total, net);
}

int main(void) {
    printf("=== BUGGY ORIGINAL OUTPUT ===\n");
    test_buggy(250, 5, 1);
    test_buggy(19, 3, 1);
    test_buggy(500, 2, 0);

    printf("\n=== CORRECTED OUTPUT ===\n");
    test_fixed(250.0, 5, 1);
    test_fixed(19.0, 3, 1);
    test_fixed(500.0, 2, 0);
    return 0;
}