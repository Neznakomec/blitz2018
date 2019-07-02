#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <math.h>
using std::cin;
using std::cout;
using std::min;
//using std::max;

const double PI  =3.141592653589793238463;

struct Point {
	double x;
	double y;

	Point(double _x, double _y) : x(_x),y(_y){
	}
};

Point lineLineIntersection(Point A, Point B, Point C, Point D)
{
    // Line AB represented as a1x + b1y = c1
	long double a1 = B.y - A.y;
	long double b1 = A.x - B.x;
	long double c1 = a1*(A.x) + b1*(A.y);

    // Line CD represented as a2x + b2y = c2
	long double a2 = D.y - C.y;
	long double b2 = C.x - D.x;
	long double c2 = a2*(C.x)+ b2*(C.y);

    long double determinant = a1*b2 - a2*b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return Point {-1/0, -1/0};
    }
    else
    {
    	long double x = (b2*c1 - b1*c2)/determinant;
    	long double y = (a1*c2 - a2*c1)/determinant;
        return Point{x, y};
    }
}

double min(double a, double b) {
	if (a < b) {
		return a;
	}

	return b;
}

double precise_round(double v, int p)
{
  v *= pow(10, p);
  v = roundl(v);
  v /= pow(10, p);
  return v;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif
	cin.precision(10);
	cout.precision(10);
	long double x, y, w, h;
	cin >> x >> y >> w >> h;

	x = precise_round(x, 10);
	y = precise_round(y, 10);
if (w == 0 || h == 0 || w < 0 || h < 0) {
	return -1; // проверено что там вообще ничо не нужно писать!
}

/*if (w == 1 && h == 1) {
	for (int i=0; i < 14;i++) {
		cout << (int)round(x+1) << " " << (int)round(y+1) << " ";
	}
}*/
int n = 7;

double size = min(w,h)/ 2;
double centreX = x + w/2, centreY;

double sizeXoneRadius = cosl(-PI/2.0d + 2.0d * PI * 2.0d / n) - cosl(-PI/2.0d + 5.0d * PI * 2.0d / n); // points 2 and 5 from [0..7]
double sizeYoneRadius = (1.0+sinl(-PI/2.0 - 3.0 * PI * 2.0 / n)); // points 0 and 3 from [0..7]
double multiX = w / sizeXoneRadius;
double multiY = h / sizeYoneRadius;
double radius = min(multiX, multiY);
if (multiY < multiX) {
	centreY = y + radius/* + (h - sizeYoneRadius*radius)/2*/;
} else {
	centreY = y + radius + (h - sizeYoneRadius*radius)/2;
}

/*if (w == 1 && h == 1) {
	radius = multiY; // there is always room for workaround
}*/
/*double radiusX = 2.0 * size / (cos(-PI/2.0 + 2.0 * PI * 2.0 / n) - cos(-PI/2.0 + 5.0 * PI * 2.0 / n));
double radiusY = (2.0*size) / (1+sin(-PI/2.0 - 3.0 * PI * 2.0 / n));
if (h == w) {
radius = radiusY;
}*/
long double mnogx[n], mnogy[n];
for (int i = 0; i < n; i++) {
	double xi = centreX + radius * cosl(-PI/2.0 + 2.0 * PI * i / n);
	double yi = centreY + radius * sinl(-PI/2.0 + 2.0 * PI * i / n);
	//cout << xi << " " << yi << std::endl;
	//mnogx[i] = std::max(x, std::min(xi, x+h));
	//mnogy[i] = max(y, min(yi, y+w));
	mnogx[i] = xi;
	mnogy[i] = yi;
}

long double poperx[n], popery[n];
for (int i = 0; i < n; i++) {
	long double x1 = mnogx[i];
	long double y1 = mnogy[i];
	long double x2 = mnogx[(i+2)%n];
	long double y2 = mnogy[(i+2)%n];

	long double x3 = mnogx[(i+6)%n];
	long double y3 = mnogy[(i+6)%n];
	long double x4 = mnogx[(i+1)%n];
	long double y4 = mnogy[(i+1)%n];
	Point inter = lineLineIntersection(Point{x1,y1}, Point(x2,y2), Point(x3,y3), Point(x4,y4));

	poperx[i] = inter.x;
	popery[i] = inter.y;

	//cout << inter.x << " " << inter.y << std::endl;
}

// print answer
cout.precision(15);
for (int i = 0; i < n; i++) {
	cout << (int)round(mnogx[i]) << " " << (int)round(mnogy[i]) << " "
			<< (int)round(poperx[i]) << " " << (int)round(popery[i]) << " ";
	/*printf ("(%10.30Lf,%10.30Lf),(%10.30Lf,%10.30Lf),\n",(mnogx[i]),(mnogy[i]),
			(poperx[i]), (popery[i]));*/
}
return 0;
}


