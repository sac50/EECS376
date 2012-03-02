#include <math.h>

using namespace std;

Vector::Vector(double a, double b){
	x=a;
	y=b;
}

void Vector::setX(double X0){
	x=X0;
}

void Vector::setY(double Y0){
	y=Y0;
}

double Vector::X(){
	return x;
}

double Vector::Y(){
	return y;
}

Vector Vector::operator*(Vector param){
	Vector temp;

	return temp;
}
