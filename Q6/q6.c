#include <stdio.h>

void simulate_loan(double principal, double monthly_rate, double repayment, int max_months, int print_schedule)
{
    if (principal <= 0 || monthly_rate < 0 || repayment <= 0) {
        printf("Invalid loan parameters.\n");
        return;
    }
    double balance = principal;
    double total_interest = 0.0;
    int month = 0;

    if (print_schedule) {
        printf("Month | Opening Bal | Interest | Payment  | Closing Bal\n");
        printf("--------------------------------------------------------\n");
    }

    while (balance > 1e-6) {
        if (month >= max_months) {
            printf("ALERT: Safety limit of %d months (30 years) reached! Remaining balance: Rs %.2f. "
                   "Monthly repayment is too low to amortize interest.\n", max_months, balance);
            break;
        }
        month++;
        double opening = balance;
        double interest = opening * monthly_rate;
        total_interest += interest;
        double due = opening + interest;
        double payment = (due < repayment) ? due : repayment;
        balance = due - payment;
        if (balance < 1e-6) balance = 0.0;

        if (print_schedule) {
            printf("%5d | %11.2f | %8.2f | %8.2f | %11.2f\n",
                   month, opening, interest, payment, balance);
        }
    }
    if (balance == 0.0) {
        printf("Repayment=Rs %.2f -> Months=%d, Total Interest=Rs %.2f\n",
               repayment, month, total_interest);
    }
}

int main(void)
{
    simulate_loan(10000.0, 0.02, 2000.0, 360, 1);
    printf("\n=== Growth Investigation ===\n");
    double emis[] = {2000.0, 1000.0, 500.0, 250.0, 210.0, 201.0, 200.0, 190.0};
    for (int i = 0; i < 8; i++) simulate_loan(10000.0, 0.02, emis[i], 360, 0);
    return 0;
}