#include<math.h>
#include "Path.h"

const double pi = 3.141592;

using namespace std;

//class Vector;
/*
class Vector{
	public:
		double x,y;
		Vector(){};
		Vector(double,double);
		void setX(double);
		void setY(double);
		double X();
		double Y();
		Vector operator*(Vector);
};

class Path{
	public:
		Vector start, end;
		int type;
		double length;
		double psiS,psiF;
		double seg_psi;
		Vector t_hat;
		Vector n_hat;
		Path(){};
		void Path::init(Vector, Vector, int);
		void Path::init(double,double,int);
		int Path::getType();
		Vector Path::getStart();
		Vector Path::getEnd();
		double Path::getPsiS();
		double Path::getPsiF();
		Vector Path::n_hatCalc();
		Vector Path::d_off(Vector);		
};

*/




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

void Path::init(Vector s, Vector e, int t){
	start=s;
	end=e;
	type=t;
	length = sqrt(pow(s.X()-e.X(),2)+pow(s.Y()-e.Y(),2));
	if(e.Y()-s.Y() >= 0){
		if(e.X()-s.X()>=0){
			//Q1
			seg_psi = atan((e.Y()-s.Y())/(e.X()-s.X()));
			t_hat.setX(cos(seg_psi));
			t_hat.setY(sin(seg_psi));
		}
		else{
			//Q2
			seg_psi = pi - atan((e.Y()-s.Y())/(e.X()-s.X()));
			t_hat.setX(cos(seg_psi));
			t_hat.setY(sin(seg_psi));
		}
	}
	else{
		if(e.X()-s.X()<0){
			//Q3
			seg_psi = pi + atan((e.Y()-s.Y())/(e.X()-s.X()));
			t_hat.setX(cos(seg_psi));
			t_hat.setY(sin(seg_psi));
		}
		else{
			//Q4
			seg_psi = (2*pi) - atan((e.Y()-s.Y())/(e.X()-s.X()));
			t_hat.setX(cos(seg_psi));
			t_hat.setY(sin(seg_psi));
		}
	}
}

void Path::init(double s,double e,int t){
	psiS=s;
	psiF=e;
	type=t;
}

int Path::getType(){
	return type;
}

Vector Path::getStart(){
	return start;
}

Vector Path::getEnd(){
	return end;
}

double Path::getPsiS(){
	return psiS;
}

double Path::getPsiF(){
	return psiF;
}

Vector Path::n_hatCalc(){
	Vector t;
	t.setX(-t_hat.X());
	t.setY(t_hat.Y());
	n_hat = t;
	return t;
}

Vector Path::d_off(Vector robo_coord){
	Vector t;
	Vector co;
	co.setX(robo_coord.X()-start.X());
	co.setY(robo_coord.Y()-start.Y()); 
	t.setX(co.X()*n_hat.X() + co.X()*n_hat.Y());
	t.setY(co.Y()*n_hat.X() + co.Y() *n_hat.Y());
	return t;
}

	