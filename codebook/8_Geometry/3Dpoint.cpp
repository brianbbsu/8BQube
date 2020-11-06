struct Point {
	double x, y, z;
	Point(double _x = 0, double _y = 0, double _z = 0): x(_x), y(_y), z(_z){}
};
Point operator-(const Point &p1, const Point &p2)
{ return Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);}
Point cross(const Point &p1, const Point &p2)
{ return Point(p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x);}
double dot(const Point &p1, const Point &p2)
{ return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;}
double abs(const Point &a)
{ return sqrt(dot(a, a));}
Point cross3(const Point &a, const Point &b, const Point &c)
{ return cross(b - a, c - a);}
double area(Point a, Point b, Point c)
{ return abs(cross3(a, b, c));}
double volume(Point a, Point b, Point c, Point d)
{return dot(cross3(a, b, c), d - a);}
