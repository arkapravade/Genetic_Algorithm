#include<bits/stdc++.h>
using namespace std;

#define SolSpace 150		//Total number of solutions
#define MaxGen 200			//Max Generations
#define bitpervar 5
#define prob_mu 0.6		//Probability of mutation; if value >= 0.5, mutation takes place

#define ObjFun(x1,x2) (x1+x2-2*x1*x1-x2*x2+x1*x2)
#define xmax 0.5
#define xmin 0

// #define ObjFun(x1,x2) (100*(x2-x1*x1)*(x2-x1*x1) - (1-x1)*(1-x1))
// #define xmax 3
// #define xmin -3

// #define ObjFun(x1,x2) (((x1-1)*(x1-1))+2*(2*x2*x2 - x1)*(2*x2*x2 - x1))
// #define xmax 1
// #define xmin -1

// #define ObjFun(x1,x2) (x1 + x2 + x1*x2)
// #define xmax 2
// #define xmin -2

// #define ObjFun(x1,x2) ((x1+x2)*(x1+x2) - (x1-x2) + 1)


double FunVal,X1,X2,del_v_1,del_v_2,mini=INT_MAX;
double X1f,X2f;
double sol[50];

double fvalue(int *p)
{
	double x1,x2;
	del_v_1=0,del_v_2=0;		//dv is decoded value
	// for(int i=0;i<10;i++)
	for(int i=0;i<2*bitpervar;i++)
	{
		if(i<bitpervar)
		del_v_1+=p[i]*pow(2,(bitpervar-1-i));
		else
		del_v_2+=p[i]*pow(2,(2*bitpervar-1-i));
	}
	x1 = xmin + (xmax-xmin)*del_v_1/31;
	x2 = xmin + (xmax-xmin)*del_v_2/31;
	FunVal = ObjFun(x1,x2);
	X1 = x1;
	X2 = x2;
	// return (-1)*ObjFun(x1,x2);
	return 1/(1+pow(ObjFun(x1,x2),2));		// converted into maximization problem
	// return 1/(ObjFun(x1,x2)+1);		// converted into maximization problem
	// return ObjFun(x1,x2);
}

void randomize(int *a,int n)
{
	srand(time(0));
	for(int i=n-1;i>=0;i--)
	{
	int random_v=rand()%bitpervar;
	double temporary=a[i];
	a[i]=a[random_v];
	a[random_v]=temporary;
    }
}

int main()
{   		
	srand(time(0));
	int n=SolSpace,i,j,t=0;		//t is generation counter
	int MatingPool[n][2*bitpervar];		// Mating Pool
	int **S;		// S is solution space
	S=new int* [n];

	
	for(i=0;i<n;i++)
	{
	S[i]=new int[2*bitpervar];

    }
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<2*bitpervar;j++)
		S[i][j]=rand()%2;		//initial solution
	}
	
	int index[n];
	for(i=0;i<n;i++)
	index[i]=i;		//representing solution
	
	double fval[n];		//fitness value
	cout<<"The final solution matrix is: \n"<<endl;
	do{ t++;
	randomize(index,n);    //Binary Tournament Selection
		
    for(i=0;i<n;i++){
	fval[i]=fvalue(S[index[i]]);
	}		//fitness evaluation


	for(i=0;i<n;i+=2)
	{	
		for(j=0;j<2*bitpervar;j++)
		{
		if (fval[i]>=fval[i+1])
		MatingPool[i/2][j]=S[index[i]][j];
		
		else
		MatingPool[i/2][j]=S[index[i+1]][j];
		}
	}
	
	randomize(index,n);

    for(i=0;i<n;i++)
	fval[i]=fvalue(S[index[i]]);		//fitness evaluation

	for(i=0;i<n;i+=2)
	{
		for(j=0;j<2*bitpervar;j++)
		{
		if (fval[i]>=fval[i+1])
		MatingPool[i/2+n/2][j]=S[index[i]][j];
		
		else
		MatingPool[i/2+n/2][j]=S[index[i+1]][j];
		}
	}

	for(i=0;i<n;i+=2)      //crossover
	{	
     int major= 1+rand()%8;
     
     
       for(j=major;j<2*bitpervar;j++)
		{
	        int temporary=MatingPool[i][j];
			MatingPool[i][j]=MatingPool[i+1][j];
			MatingPool[i+1][j]=temporary;
		}
	}		
	for(i=0;i<n;i++)
	{
		for(j=0;j<2*bitpervar;j++)
		S[i][j]= MatingPool[i][j];
	}

		//mutation starts

	for(i=0;i<n;i++){
		for(j=0;j<2*bitpervar;j++){
			double x = rand() / (double)(RAND_MAX);
			if(x > prob_mu){
				if(S[i][j] == 1)	S[i][j]=0;
				else	S[i][j]=1;
			}
			//cout<< x <<" ";
		}
		//cout<<endl;
	}

	
	}while(t<MaxGen);		//termination condition

	for(i=0;i<SolSpace;i++)
	{
	for(j=0;j<2*bitpervar;j++){
		if(j==bitpervar){
			cout<<"\t\t";
		}
		cout<<S[i][j]<<"  ";
	}
	
	cout<<endl;
	}
	cout<<endl<<endl;

	
    // double solution=fvalue(S[0]);
	double tempo1 = fvalue(S[0]);
	sol[0] = ObjFun(X1,X2);

	for(int i=1; i<SolSpace; i++){
		double y = fvalue(S[i]);
		sol[i] = ObjFun(X1,X2);
		if(sol[i] < tempo1){
			tempo1 = sol[i];
			X1f = X1;
			X2f = X2;		//storing the final X values for output
		}
		//mini = min(sol[i], mini);
		//cout<<fixed<<setprecision(6)<<X1<<"\t"<<X2<<endl;
	}

	//cout<<"The optimum solution of the problem is: "<<solution<<endl;
	//cout<<"The optimum solution of the problem is: "<<ObjFun(X1,X2)<<endl;
	//cout<<"The optimum solution of the problem is: "<<mini<<endl;
	cout<<"The optimum solution of the problem is: "<<tempo1<<endl;
	cout<<fixed<<setprecision(6)<<"The values of the optimum variables are: "<<X1f<<" and "<<X2f<<endl;
	// cout<<del_v_1<<endl;
	// cout<<del_v_2<<endl;
	return 0;
}