#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include"cuadmin.h"
#include<algorithm>
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
ofstream out;

double poli(V coef,double x){
	double res=0;
	forn(i,coef.size()) res+=coef[i]*pow(x,i);
	return res;
}

void move(int i, int to){
	out << i << "\t" << to << endl;
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
	return to;
}

int main(int argc, const char* argv[]){
	if(argc<3){
		cout << "Not enough arguments" << endl;
		return 0;
	}
	out.open(argv[2]);
	ifstream fin(argv[1]);
	int t; double x,y;
	Vi data_ts; V data_xs,data_ys;
	V ts; V xs,ys;
	while(fin>>t && t>=0){
		fin >> x >> y;
		data_ts.push_back(t);
		data_xs.push_back(x);
		data_ys.push_back(y);
	}
	fin.close();
	
	forsn(i,1,data_ts[0]) move(i,0);
	int c=0;
	forsn(n,data_ts[0],data_ts.back()+1){
		if( data_ts[c] <= n ){
			ts.push_back(data_ts[c]);
			xs.push_back(data_xs[c]);
			ys.push_back(data_ys[c]);
			c++;
		}

		if(ts.size()>=4){
			int grado = min(6,(int)ts.size()-1);
			V cxa( CM(ts,xs,grado) );
			V cya( CM(ts,ys,grado) );
			//ts=ts[-6:]
			V tts;
			//tts.erase(tts.begin(),tts.end()-6);
			for(int j=max(0,(int)ts.size()-6);j<ts.size();j++) tts.push_back(ts[j]);
			//xs=[poli(cxa,t) for t in tts]
			//ys=[poli(cya,t) for t in tts]
			V xxs; forall(t,tts) xxs.push_back( poli(cxa,*t) );
			V yys; forall(t,tts) yys.push_back( poli(cya,*t) );
			//cx=cuadmin(ts,xs,2)
			//cy=cuadmin(ts,ys,2)
			V cx( CM(tts,xxs,2) );
			V cy( CM(tts,yys,2) );
			//xs=[poli(cx,t) for t in ts]
			//ys=[poli(cy,t) for t in ts]
			V xxxs; forall(t,tts) xxxs.push_back(poli(cx,*t));
			V yyys; forall(t,tts) yyys.push_back(poli(cy,*t));
			//t=ts[-1]
			int t=ts.back();
			//y=ys[-1]
			double y=yyys.back();
			//yans=ys[-2]
			double yans=*(yyys.end()-1);
			//while y>0 and t<200:
				//t+=1
				//yans=y
				//y=poli(cy,t)
			while(y>0 && t<200){
				t++;
				yans=y;
				y=poli(cy,t);
			}
			//gol=poli(cx,t+y/(yans-y))
			double gol=poli(cx,t+y/(yans-y));
			//goto(gol)
			move(n,go_to(gol));
		//elif len(ts)>1:
		}else if(ts.size()>1){
			//cx=cuadmin(ts,xs,len(ts)-1)
			//cy=cuadmin(ts,ys,len(ts)-1)
			V cx( CM(ts,xs,(int)ts.size()-1) );
			V cy( CM(ts,ys,(int)ts.size()-1) );
			//t=ts[-1]
			int t=ts.back();
			//y=ys[-1]
			double y=ys.back();
			//yans=ys[-2]
			double yans=*(ys.end()-1);
			//while y>0 and t<200:
				//t+=1
				//yans=y
				//y=poli(cy,t)
			while(y>0 && t<200){
				t++;
				yans=y;
				y=poli(cy,t);
			}
			//gol=poli(cx,t+y/(yans-y))
			double gol=poli(cx,t+y/(yans-y));
			//goto(gol)
			move(n,go_to(gol));
		//else: move(0)
		}else{
			move(n,0);
		}
	}
	out.close();
	return 0;
}
