#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include"cuadmin.h"
using namespace std;

#define forn(i,n) for(int i=0;i<n;i++)
#define forsn(i,s,n) for(int i=s;i<n;i++)
#define forrn(i,n) for(int i=(n)-1;i>=0;i--)
#define forall(it,X) for(typeof((X).begin()) it=(X).begin();it!=(X).end();it++)

typedef vector<double> V;
typedef vector<int> Vi;


double step=.05;
double arq=0.;
int lastdir=0;


double poli(V coef,double x){
	double res=0;
	forn(i,coef.size()) res+=coef[i]*pow(x,i);
	return res;
}

void move(int i, int to){
	cout << i << "\t" << to << endl;
}

int go_to(double gol){
	int to=0;
	if(gol>arq+step/2 && lastdir!=-1 and arq<1-step/2){
		arq+=step;
		lastdir=1;
		to=2;
	}else if(gol<arq-step/2 && lastdir!=1 && arq>step/2-1){
		arq-=step;
		lastdir=-1;
		to=1;
	}else{
		lastdir=0;
		to=0;
	}
	//move(to);
	return to;
}

int main(int argc, const char* argv[]){
	if(argc<3){
		cout << "Not enough arguments" << endl;
		return 0;
	}
	ifstream fin(argv[1]);
	//ofstream out(argv[2]);
	int t; double x,y;
	Vi data_ts; V data_xs,data_ys;
	Vi ts; V xs,ys;
	while(fin>>t && t>=0){
		fin >> x >> y;
		data_ts.push_back(t);
		data_xs.push_back(x);
		data_ys.push_back(y);
	}
	forsn(i,1,data_ts[0]) move(i,0);
	forsn(n,data_ts[0],data_ts.back()+1){
		int curpos=0;
		//if data[0][0]<=n: pnts.append(data.pop(0))
		//ts,xs,ys=zip(*pnts)
		if(data_ts[curpos]<=n){
			ts.push_back(data_ts[curpos]);
			xs.push_back(data_xs[curpos]);
			ys.push_back(data_ys[curpos]);
			curpos++;
		}

		//if len(ts)>=4:
		if(ts.size()>=4){
			//cxa=cuadmin(ts,xs,min(6,len(ts)-1))
			//cya=cuadmin(ts,ys,min(6,len(ts)-1))
			//ts=ts[-6:]
			//xs=[poli(cxa,t) for t in ts]
			//ys=[poli(cya,t) for t in ts]

			//cx=cuadmin(ts,xs,2)
			//cy=cuadmin(ts,ys,2)
			//xs=[poli(cx,t) for t in ts]
			//ys=[poli(cy,t) for t in ts]

			//t=ts[-1]
			//y=ys[-1]
			//yans=ys[-2]
			//while y>0 and t<200:
				//t+=1
				//yans=y
				//y=poli(cy,t)
			//gol=poli(cx,t+y/(yans-y))
			//goto(gol)
			move(n,go_to(1));
		//elif len(ts)>1:
		}else if(ts.size()>1){
			//cx=cuadmin(ts,xs,len(ts)-1)
			//cy=cuadmin(ts,ys,len(ts)-1)
			//t=ts[-1]
			//y=ys[-1]
			//yans=ys[-2]
			//while y>0 and t<200:
				//t+=1
				//yans=y
				//y=poli(cy,t)
			//gol=poli(cx,t+y/(yans-y))
			//goto(gol)
			move(n,go_to(-1));
		//else: move(0)
		}else{
			move(n,0);
		}
	}
	
	return 0;
}
