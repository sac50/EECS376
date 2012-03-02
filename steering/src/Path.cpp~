#include<math.h>
#include "Vector.h"

const double pi = 3.141592;

using namespace std;

void Path::init(Vector s, Vector e, int t){
	start=s;
	end=e;
	type=t;
	length = sqrt(pow(s::X()-e::X(),2)+pow(s::Y()-e::Y),2));
	if(e::Y()-s::Y() >= 0){
		if(e::X()-s::X()>=0){
			//Q1
			seg_psi = atan((e::Y()-s::Y())/(e::X()-s::X()));
			t_hat::setX() = cos(seg_psi);
			t_hat::setY() = sin(seg_psi);
		}
		else{
			//Q2
			seg_psi = pi - atan((e::Y()-s::Y())/(e::X()-s::X()));
			t_hat::setX() = cos(seg_psi);
			t_hat::setY() = sin(seg_psi);
		}
	}
	else{
		if(e::X()-s::X()<0){
			//Q3
			seg_psi = pi + atan((e::Y()-s::Y())/(e::X()-s::X()));
			t_hat::setX() = cos(seg_psi);
			t_hat::setY() = sin(seg_psi);
		}
		else{
			//Q4
			seg_psi = (2*pi) - atan((e::Y()-s::Y())/(e::X()-s::X()));
			t_hat::setX() = cos(seg_psi);
			t_hat::setY() = sin(seg_psi);
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
	return psiF
}

Vector Path::n_hat(){
	Vector t;
	t::segX(-t_hat::X());
	t::segY(t_hat::Y());
	n_hat = t;
	return t;
}

Vector Path::d_off(Vector robo_coord){
	Vector t;
	Vector co;
	co::setX(robo_coord::X()-start::X());
	co::setY(robo_coord::Y()-start::Y()); 
	t::setX(co::X()*n_hat::X() + co::X()*n_hat::Y());
	t::setY(co::Y()*n_hat::X() + co::Y() *n_hat::Y());
	return t;
}

