#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 4
#define shapeText(TYPE) char name[10]; \
int (*perimeter)(struct TYPE*); \
int (*area)(struct TYPE*);

typedef struct shape_s {
    shapeText(shape_s);
} shape_t;

typedef struct circle_s {
    shapeText(circle_s);
    int radius;
} circle_t;

typedef struct rectangle_s {
    shapeText(rectangle_s);
    int width, height;
} rectangle_t;

typedef struct square_s {
    shapeText(square_s);
    int side;
} square_t;

typedef struct triangle_s {
    shapeText(triangle_s);
    int s1, s2, s3;
} triangle_t;

int circle_perimeter(circle_t* c) {
    return 2 * PI * c->radius;
}

int circle_area(circle_t* c) {
    return PI * c->radius * c->radius;
}

int rectangle_perimeter(rectangle_t* r) {
    return 2 * (r->width + r->height);
}

int rectangle_area(rectangle_t* r) {
    return r->width * r->height;
}

int square_perimeter(square_t* s) {
    return 4 * s->side;
}

int square_area(square_t* s) {
    return s->side * s->side;
}

int triangle_perimeter(triangle_t* t) {
    return t->s1 + t->s2 + t->s3;
}

int triangle_area(triangle_t* t) {
    // Heron's formula
    int s = (t->s1 + t->s2 + t->s3) / 2;
    return (int)sqrt(s * (s - t->s1) * (s - t->s2) * (s - t->s3));
}

typedef struct {
    shape_t* shape;
    int perimeter;
    int area;
} shape_info_t;

int compare_shapes(const void* a, const void* b) {
    shape_info_t* sa = (shape_info_t*)a;
    shape_info_t* sb = (shape_info_t*)b;
    
    if (sa->perimeter != sb->perimeter) {
        return sb->perimeter - sa->perimeter;
    } else {
        return sb->area - sa->area;
    }
}

int main() {
    int N;
    scanf("%d", &N);

    shape_info_t shapes[N];
    int total_perimeter = 0, total_area = 0;

    for (int i = 0; i < N; ++i) {
        char type[10];
        scanf("%s", type);

        if (strcmp(type, "circle") == 0) {
            circle_t* circle = (circle_t*)malloc(sizeof(circle_t));
            strcpy(circle->name, "circle");
            circle->perimeter = (int(*)(struct circle_s*))circle_perimeter;
            circle->area = (int(*)(struct circle_s*))circle_area;
            scanf("%d", &circle->radius);
            shapes[i].shape = (shape_t*)circle;
        } else if (strcmp(type, "rectangle") == 0) {
            rectangle_t* rectangle = (rectangle_t*)malloc(sizeof(rectangle_t));
            strcpy(rectangle->name, "rectangle");
            rectangle->perimeter = (int(*)(struct rectangle_s*))rectangle_perimeter;
            rectangle->area = (int(*)(struct rectangle_s*))rectangle_area;
            scanf("%d %d", &rectangle->width, &rectangle->height);
            shapes[i].shape = (shape_t*)rectangle;
        } else if (strcmp(type, "square") == 0) {
            square_t* square = (square_t*)malloc(sizeof(square_t));
            strcpy(square->name, "square");
            square->perimeter = (int(*)(struct square_s*))square_perimeter;
            square->area = (int(*)(struct square_s*))square_area;
            scanf("%d", &square->side);
            shapes[i].shape = (shape_t*)square;
        } else if (strcmp(type, "triangle") == 0) {
            triangle_t* triangle = (triangle_t*)malloc(sizeof(triangle_t));
            strcpy(triangle->name, "triangle");
            triangle->perimeter = (int(*)(struct triangle_s*))triangle_perimeter;
            triangle->area = (int(*)(struct triangle_s*))triangle_area;
            scanf("%d %d %d", &triangle->s1, &triangle->s2, &triangle->s3);
            shapes[i].shape = (shape_t*)triangle;
        }

        shapes[i].perimeter = shapes[i].shape->perimeter(shapes[i].shape);
        shapes[i].area = shapes[i].shape->area(shapes[i].shape);
        total_perimeter += shapes[i].perimeter;
        total_area += shapes[i].area;
    }

    qsort(shapes, N, sizeof(shape_info_t), compare_shapes);

    for (int i = 0; i < N; ++i) {
        printf("%s %d %d\n", shapes[i].shape->name, shapes[i].perimeter, shapes[i].area);
        free(shapes[i].shape);
    }

    printf("%d %d\n", total_perimeter, total_area);

    return 0;
}
