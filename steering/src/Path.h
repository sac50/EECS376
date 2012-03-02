#ifndef Path_h
#define Path_h

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
		void init(Vector,Vector,in);
		void init(double,double,int);
		int getType();
		Vector getStart();
		Vector getEnd();
		Vector n_hat();
		Vector d_off(Vector);
		double getPsiS();
		double getPsiF();		
};

#endif
