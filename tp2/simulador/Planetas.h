#ifndef PLANETAS_H
#define PLANETAS_H

	// Coordenada (0,0): Solar System Barycenter
	// datos para: A.D. 2010-May-05 00:00:00.0000 CT
	// G = 6,67428 * 10^-11 * m^3 / (Kg*s^2)
	// = 0.00002499215588275752801651213378056900054016 * AU^3 / (1e-30*Kg * dia^2)
	// unidades:
	// * distancia: AU	= 149597870.691 km
	// * tiempo: dias	= 86400 s
	// * peso: 1.e-30 Kg

struct Planeta{
	Vector x;
	Vector v;
	double m;
	double r;
};

list<Planeta> planetas;

void initPlanetas(){

	Planeta sol, mercurio, venus, tierra, luna, marte, jupiter, saturno, urano, neptuno, pluton;

	sol.x = Vector(-4.042895106228434e-03, 2.209532530800580e-03, 1.136425407067405e-05);	// AU
	sol.v = Vector(-1.786236608923230e-06, -5.959144368171789e-06, 4.287462284225408e-08);	// AU / dia
	sol.m = 1.9891; // 1.9891 * 10^30 Kg

	tierra.x = Vector(-7.262551982062518e-01, -7.016177342125620e-01, 2.942601923402196e-05);	// AU
	tierra.v = Vector(1.172032570433690e-02, -1.239499064419012e-02, -2.875393960566639e-07);	// AU / dia
	tierra.m = 0.0000059736; // 5.9736 * 10^24 Kg

	luna.x = Vector(-7.248557601516714e-01, -7.039097848869444e-01, 1.029051462977911e-04);	// AU
	luna.v = Vector(1.220576787081027e-02, -1.211595432894550e-02, 4.775108508860639e-05);	// AU / dia
	luna.m = 0.00000007349; // 734.9 * 10^20 Kg = m_sol/10^10

	planetas.push_back(sol);
	planetas.push_back(tierra);
	planetas.push_back(luna);

}

#endif
