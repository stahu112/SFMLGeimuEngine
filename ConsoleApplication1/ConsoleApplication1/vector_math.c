#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "vector_math.h"

int main()
{
//Create 4 vec3ds
	Point first;
	Point second;
	Point third;
	Point fourth;

//Set first two vectors
	vec3dSet(&first,-2,1,10);
	vec3dSet(&second, 3.6,-7,0.2);

//Set third vector
	vec3dAdd(&first, &second, &third);

//Set the forth vector
	vec3dScalarMul(&third,0.5,&fourth);

//Print vectors
	puts("Points:");
	vec3dPrint(&first);
	vec3dPrint(&second);
	vec3dPrint(&third);
	vec3dPrint(&fourth);

//Create array of vectors
	Point vectors[] = { first, second, third, fourth};

	qsort(vectors, 4, sizeof(Vec3d), compar);

	return 0;
}


//Functions definitions
void vec3dSet(Vec3d * vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void vec3dPrint(const Vec3d *vec)
{
	printf("(%g, &g, &g)\n", vec->x, vec->y, vec->z);
}

double vec3dMag(const Vec3d *vec)
{
	return sqrt(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z);
}

void vec3dAdd(const Vec3d *src1, const Vec3d *src2, Vec3d *dst)
{
	dst->x = src1->x + src2->x;
	dst->y = src1->y + src2->y;
	dst->z = src1->z + src2->z;
}

void vec3dScalarMul(const Vec3d *src, double a, Vec3d *dst)
{
	dst->x *= a;
	dst->y *= a;
	dst->z *= a;
}

//Comparision function for qsort
int compar(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}