#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <math.h>
using namespace std;
//remet une matrice a la bonne taille
vector<vector<double> > resize2d (vector<vector<double> > A,
								  int 				      line,
								  int 					  col)
{
  	A.resize(line);
	for (int i = 0; i < line; ++i)
    	A[i].resize(col);
  return A;
}
//fonction a modifier marche que pour matrice carré c'est de la merde
vector<int > shape2d(vector<vector<double> > A)
{
	vector<int > res(2);
	res[0] = A.size();
	//cout<<A.size()<<endl;
	//cout<<A[0].size()<<endl;
	res[1] = A[0].size();
	return res;
}
//echange des ligne
vector<vector<double> > swapline (vector<vector<double> > A,
								  int 				      i,
								  int 					  j)
{
	vector<double> acc;
	for (int k = 0; k < A.size(); ++k)
	{
		acc=A[i];
		A[i]=A[j];
		A[j]=acc;
	}
	return A;
}
//norme euclidienne d'un vecteur
double norm (vector<double>  A)
{	
	double acc;
	acc=0;
	for (int i = 0; i < A.size(); ++i)
	{
		acc=A[i]*A[i]+acc;
	}
	return sqrt(acc);
}
//produit scalaire entre 2 vecteur
double scalprod(vector<double>  A,vector<double>  B)
{
	double acc;
	if (A.size()==B.size())
	{
		for (int i = 0; i < A.size(); ++i)
		{
			acc+=A[i]*B[i];
		}
	}else{
		cout<<"wtf u duin bro"<<endl;
	}
	
	return acc;
}
//ajoute 2 vecteur entre eux valeur par valuer
vector<double> addvect(vector<double>  A,vector<double>  B)
{
	vector<double> acc(A.size(),0);
	if (A.size()==B.size())
	{
		for (int i = 0; i < A.size(); ++i)
		{
			acc[i]=A[i]+B[i];
		}
	}else{
		cout<<"wtf u duin bro"<<endl;
	}
	return acc;
}
//idem que en haut avec -
vector<double> minusvect(vector<double>  A,vector<double>  B)
{
	vector<double> acc(A.size(),0);
	if (A.size()==B.size())
	{
		for (int i = 0; i < A.size(); ++i)
		{
			acc[i]=A[i]-B[i];
		}
	}else{
		cout<<"wtf u duin bro"<<endl;
	}
	return acc;
}
//multiplie un vecteur par une constante
vector<double> ConstTimeVect(double alpha,vector<double>  A)
{
	for (int i = 0; i < A.size(); ++i)
	{
		A[i]=alpha*A[i];
	}
	return A;
}
//projeter de U V #wiki <U,V>/<U,U>  * U
vector<double> projuv(vector<double>  U,vector<double>  V)
{	double alpha;
	alpha=scalprod(U,V)/scalprod(U,U);
	for (int i = 0; i < U.size(); ++i)
	{
		U[i]=alpha*U[i];
	}
	return U;
}
//transposé ou matrice avec une bite
vector<vector<double> > trans(vector<vector<double> > A,int n)
{
	double temp;
	for(int i(0);i<n;i++)
	{
		for(int j(0);j<i;j++)
		{
			temp=A[i][j];
			A[i][j]=A[j][i];
			A[j][i]=temp;
		}
	}
	return A;
}
//putain ya pas plus explicite comme nom
vector<double> getcolumn(vector<vector<double> > A,int num)
{	
	vector<double> res(A[0].size(),0);
	for (int i = 0; i < A[0].size(); ++i)
	{
		res[i]=A[i][num];
	}
	return res;
}
///gram schmit tu ma casser les burnes fdp
//https://fr.wikipedia.org/wiki/D%C3%A9composition_QR exemple
vector<vector<double> > getQ2 (vector<vector<double> > A)
{	
	vector<int>show (2,0);
	show=shape2d(A);
	double acc;
	vector<vector<double> > e;
	vector<vector<double> > U;
	vector<double> init(A[0].size(),0);
	e=resize2d(e,show[0],show[1]);
	U=resize2d(U,show[0],show[1]);
	U[0]=A[0];
	acc=norm(getcolumn(A,0));
	e[0]=ConstTimeVect(1./acc,getcolumn(A,0));
	for (int i = 1; i < A[0].size(); ++i)
	{	
		U[i]=init;
		for (int j = 0; j < i; ++j)
		{	
			U[i]=addvect( projuv(e[j],getcolumn(A,i)),U[i]);
		}
		U[i]=minusvect( getcolumn(A,i),U[i]);
		e[i]=ConstTimeVect(1./norm(U[i]),U[i]);
	}
	return trans(e,e[0].size());
}


vector<vector<double> > mult(const vector<vector<double> > &A, const vector<vector<double> > &B)
{ const unsigned columnsA = A[0].size();
  const unsigned rowsA = A.size();
  const unsigned columnsB = B[0].size();
  const unsigned rowsB = B.size();
    // We multiply our matrix and return it as a vector<vector<double>>, or we throw a "Dimension error" exception 
   if (columnsA!=rowsB)
   	{ 
   		throw "Dimension error";
    } else { 
    	vector<vector<double> > C(rowsA,vector<double>(columnsB,0)); 
    	for(unsigned i=0;i<rowsA;++i)
    	{
    	 	for(unsigned j=0;j<columnsB;++j)
    	 		{ C[i][j]=0; 
    				for(unsigned k=0;k<columnsA;++k)
    				{
    		 			C[i][j]=C[i][j]+A[i][k]*B[k][j]; 
    				} 
    			} 
    	} 
    return C; 
	} 
} 
vector <double>multvectparmat(vector<vector<double> > A,vector<double>B)
{
	vector <double> res(B.size(),0);
	for (int i = 0; i < A[0].size(); ++i)
	{
		res[i]=scalprod(A[i],B);
	}
	return res;
}
void affmat(vector<vector<double> > R)
{
	int l = R[0].size();
	for (int i = 0; i < l; ++i)
	{
		for (int j = 0; j< l; ++j)
		{
			if (fabs(R[i][j])<0.000000000001)
			{
				R[i][j]=0;
			}			
			cout<<R[i][j]<<" ";
		}
		cout<<endl;
	}
}
void affvect(vector<double> &A, unsigned &n)
{
	for (int i = 0; i < n; ++i)
	{
		cout<<A[i]<<" ";
	}
	cout<<endl;
	cout<<endl;
}
vector<double> resolve(const vector<vector<double> > &R,const vector<double> &B)
{ 
	const unsigned n = B.size();
 	vector<double> X(n,0);
  	for(int i=n-1;i>=0;--i)
  	{ 
  		double sum = 0;
  	 	for(int k=n-1;k>=0;--k)
  	 	{ 
  	 		sum=sum+R[i][k]*X[k]; 
  	 	} 
  	 	if (R[i][i]!=0)
  	 	{
  	 		X[i]=(B[i]-sum)/R[i][i];
  	 	} else { 
  	 	 	cerr<<"AX=B doesn't have a unique solution"<<endl;
  	 	 	cerr<<"There is no solution or an infinity of solutions"<<endl;
  	 	 	throw "Infinite solutions error"; 
  	 	 } 
  	 }
  	 	  return X; 
}

vector<double> findX(vector<vector<double> > A,vector<double>  B)
{	
	unsigned taille;
	taille=A[0].size();
	vector<vector<double> > AT(taille,vector<double>(taille,0));
	vector<vector<double> > Q(taille,vector<double>(taille,0));
	vector<vector<double> > R(taille,vector<double>(taille,0));
	vector<double> X(taille,0);
	vector<double> test(taille,0);
//!	cout<<"A"<<endl;
//!	affmat(A);
	AT=trans(A,A[0].size());
//!	cout<<""<<endl;
//!	cout<<"B"<<endl;
//!	affvect(B,taille);


	
//!	cout<<endl;
//!	cout<<"Q"<<endl;
	Q=getQ2(A);
	
/*!!!!!!!
	for (int i = 0; i < Q[0].size(); ++i)
	{
		for (int j = 0; j< Q[0].size(); ++j)
		{		
			if (fabs(Q[i][j])<0.000000000001)
			{
				Q[i][j]=0;
			}
			cout<<Q[i][j]<<" ";
		}
		cout<<endl;
	}
*/
//!	cout<<""<<endl;
	AT=Q; //ligne de debug qui empéche Q de disparaitre
//!	cout<<"R"<<endl;
	R=mult(trans(AT,AT[0].size()),A);
//!	affmat(R);
	//R=mult(Q,R);
	
//!	cout<<endl;
	//affmat(R);
//cout<<"Q transposé"<<endl;
	Q=trans(Q,Q[0].size());
//affmat(Q);

//!   	cout<<endl;
	X=multvectparmat(Q,B);

//!	cout<<"Q^-1*B"<<endl;
//!	for (int i = 0; i < X.size(); ++i)
//!	{
//!		cout<<X[i]<<" ";
//!		cout<<endl;
//!	}
//!
//!	cout<<endl;
	X=resolve(R,X);	
	
//!	cout<<"X"<<endl;
//!	for (int i = 0; i < X.size(); ++i)
//!	{
//!		cout<<X[i]<<" ";
//!		cout<<endl;
//!	}
//!	cout<<endl;
//!	//mult(A,X);
//!	cout<<""<<endl;
	test=multvectparmat(A,X);

//!	cout<<"A*X"<<endl;
//!	for (int i = 0; i < X.size(); ++i)
//!	{
//!		cout<<test[i]<<" ";
//!		cout<<endl;
//!	}
//!	cout<<""<<endl;
	return X;
}
vector<vector<double> > adaptmatrix(vector<vector<double> > A,vector<vector<double> >  BIG)
{	
	
	unsigned acc;
	acc=BIG[0].size();
	
	vector<vector<double> >res(acc,vector<double>(A[0].size(),0));
	//BIG=trans(BIG,acc);
	for (int i = 0; i < acc; ++i)
	{
		res[i]=findX(A,BIG[i]);
	}
return trans(res,acc);
}


//vect2D 				resize2d (vect2D A,int line, int col)
//vector<int > 			shape2d(vector<vector<double> > A)
//double 				norm (vector<double>  A)
//double 				scalprod(vector<double>  A,vector<double>  B)
//vector<double> 		ConstTimeVect(double alpha,vector<double>  A)
//vector<double> 		projuv(vector<double>  U,vector<double>  V)
//vector<vector<double> > getQ (vector<vector<double> > A)
//double 				addvect(vector<double>  A,vector<double>  B)
//add 2 vector value by value
//double 				minusvect(vector<double>  A,vector<double>  B)
//soustract 2 vector value by value
int main(int argc, char *argv[]) 
{	
	srand (time(NULL));
	int taille = atoi(argv[1]);
	//taille=3;
	vector<vector<double> > A;
	vector<vector<double> > AT(taille,vector<double>(taille,0));
	vector<vector<double> > Q;
	vector<vector<double> > R;

	
	taille=AT[0].size();
	vector<vector<double> > BIG(taille,vector<double>(taille,0));
	vector<vector<double> > XX(taille,vector<double>(taille,0));

	//vector<double> test;
	//cout<<"dick"<<endl;
	A=resize2d(A,taille,taille);
	R=resize2d(R,taille,taille);
	vector<double> B(A[0].size(),0);
	vector<double> X(A[0].size(),0);


	
	for (int i = 0; i < taille; ++i)
	{
		for (int j = 0; j< taille; ++j)
		{
				A[i][j] = 1-11 +rand() % 20;
				BIG[i][j] = 1-11 +rand() % 20;   
		}		
	}
	


/*
	A[0][0]=12;		A[0][1]=-51;	A[0][2]=4;
	A[1][0]=6;		A[1][1]=167;	A[1][2]=-68;
	A[2][0]=-4;		A[2][1]=24;		A[2][2]=-41;


	A[0][0]=1;		A[0][1]=0;	A[0][2]=0;
	A[1][0]=0;		A[1][1]=1;	A[1][2]=0;
	A[2][0]=0;		A[2][1]=0;	A[2][2]=1;

	A[0][0]=1;		A[0][1]=25;		A[0][2]=3;
	A[1][0]=2;		A[1][1]=3;		A[1][2]=78;
	A[2][0]=3;		A[2][1]=100;	A[2][2]=2;	

	B[0]=2;			B[1]=5;			B[2]=3;
	/*
	BIG[0][0]=2;		BIG[0][1]=5;	BIG[0][2]=3;
	BIG[1][0]=2;		BIG[1][1]=5;	BIG[1][2]=3;
	BIG[2][0]=2;		BIG[2][1]=5;	BIG[2][2]=3;
	
	BIG[0][0]=12;		BIG[0][1]=-51;	BIG[0][2]=4;
	BIG[1][0]=6;		BIG[1][1]=167;	BIG[1][2]=-68;
	BIG[2][0]=-4;		BIG[2][1]=24;	BIG[2][2]=-41;
*/
//findX(A,B);

	XX=adaptmatrix(A,BIG);
//!	cout<<"#####################################################################################"<<endl;
//!	cout<<"before this line you'll find every Q R decomposition for each column of X and B"<<endl;
//!	affmat(A);
	cout<<endl;
//!	affmat(XX);
	cout<<endl;
//!	affmat(trans(mult(A,XX),taille));
    return 0;
}
//unsigned c'est pour les itérateur genre i d'une boucle (int positif)
//dans une fonction const c'est si tu dois pas modifier le parametre de la fonction et & tout le temps