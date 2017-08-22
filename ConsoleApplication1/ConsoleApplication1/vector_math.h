
// 3D vector structure definition
typedef struct {
	double x;     // The vector's X coordinate
	double y;     // The vector's Y coordinate
	double z;     // The vector's Z coordinate
} Vec3d;

// Vector math function prototypes

// Initialize all coordinate values of a 3D vector.
void vec3dSet(Vec3d *vec, double x, double y, double z);

// Print a vector (just print the x, y, and z coordinates).
// Example output:
// (3.3, -7.9, 11)
void vec3dPrint(const Vec3d *vec);

// Calculate and return the magnitude of a 3D vector,
// where magnitude is defined as sqrt(x*x + y*y + z*z)
double vec3dMag(const Vec3d *vec);

// Add two vectors: dst = src1 + src2 
void vec3dAdd(const Vec3d *src1, const Vec3d *src2, Vec3d *dst);

// Multiply a vector by a scalar: dst = a*src
void vec3dScalarMul(const Vec3d *src, double a, Vec3d *dst);
                
/********** Do not make any changes above this line ************/

// A 3D vector can also represent a point with x, y, z coordinates.
// ***Add a typedef here that makes Point an alias for Vec3d.
typedef Vec3d Point;

// ***Add a structure definition here for a Line which consists of two Point structures.
// The first Point is the start, and the second Point is the end of the line.
// Note: Do not use pointers (Point*) in this structure.
typedef struct
{
	Point start;
	Point end;
} Line;

// Initialize the points of a line (do not change this prototype).
void lineSet(Line *line, const Point *start, const Point *end);

// Print a line (do not change this prototype). Example output:
// (3.3, -7.9, 11) - (0, -9, 1.2)
void linePrint(const Line *line);

