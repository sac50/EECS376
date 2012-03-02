#ifndef Vector_h
#define Vector_h

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

#endif
