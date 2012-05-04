#ifndef Path_h
#define Path_h

class Vector;
class Path;

class Vector{
	public:
		double x,y;
		Vector(){};
		Vector(double,double);
		void setX(double);
		void setY(double);
		void set(double,double);
		double X();
		double Y();
		Vector operator-(Vector);
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
		void init(Vector, Vector, int);
		void init(double,double,int);
		int getType();
		Vector getStart();
		Vector getEnd();
		double getPsiS();
		double getPsiF();
		Vector n_hatCalc();
		double d_off(Vector);		
};

#endif
