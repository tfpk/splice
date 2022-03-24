#include <stdio.h>

int main(void) {

    int a, b, c;
    printf("Enter one number: ");
    scanf("%d", &a);
    printf("Enter another number: ");
    scanf("%d", &b);
    printf("Enter a last number: ");
    scanf("%d", &c);

    printf("%d + %d + %d = %d\n", a, b, c, a + b + c);

    return 0;
}
