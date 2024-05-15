#include <stdio.h>
#include <math.h>

int main(){
    int N = 0;
    float sumPerimeter = 0, sumArea = 0;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        char shape[2];
        scanf(" %c", shape);

        if (shape[0] == 'C') {
            int radius = 0;
            scanf("%d", &radius);
            printf("%0.2f %0.2f\n", 2 * 3.14 * radius, radius * radius * 3.14);

            sumPerimeter += 2 * 3.14 * radius;
            sumArea += radius * radius * 3.14;
        }
        else if (shape[0] == 'R') {
            int length = 0, width = 0;
            scanf("%d %d", &length, &width);
            printf("%0.2f %0.2f\n", (length + width) * 2.0, length * width * 1.0);
            sumPerimeter += (length + width) * 2.0;
            sumArea += length * width * 1.0;
        }
        else if (shape[0] == 'S') {
            int edge = 0;
            scanf("%d", &edge);
            printf("%0.2f %0.2f\n", edge * 4.0, edge * edge * 1.0);
            sumPerimeter += edge * 4.0;
            sumArea += edge * edge * 1.0;
        }
        else {
            int a = 0, b = 0, c = 0;
            scanf("%d %d %d", &a, &b, &c);
            float s = (a + b + c) / 2.0;
            printf("%0.2f %0.2f\n", (a + b + c) * 1.0, sqrt(s * (s - a) * (s - b) * (s - c)));
            sumPerimeter += (a + b + c) * 1.0;
            sumArea += sqrt(s * (s - a) * (s - b) * (s - c));
        }
    }
    printf("%0.2f %0.2f\n", sumPerimeter, sumArea);
    return 0;
}