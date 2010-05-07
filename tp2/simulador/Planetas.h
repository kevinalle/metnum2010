#ifndef PLANETAS_H
#define PLANETAS_H

	// Coordenada (0,0): Solar System Barycenter
	// datos para: A.D. 2010-May-05 00:00:00.0000 CT
	// G = 6,67428 * 10^-11 * m^3 / (Kg*s^2)
	// = 0.00002499215588275752801651213378056900054016 * AU^3 / (1e-30*Kg * dia^2)
	// unidades:
	// * distancia: AU	= 149597870.691 km
	// * tiempo: dias	= 86400 s
	// * peso: 1.e30 Kg

struct Planeta{
	Vector x;
	Vector v;
	double m;
	list<Vector> orbit;
	Uint32 r, g, b;
};

list<Planeta> planetas;

void initPlanetas(){

	Planeta sol, mercurio, venus, tierra, luna, marte, jupiter, saturno, urano, neptuno, pluton;

	sol.x = Vector(-4.042895106228434e-03, 2.209532530800580e-03, 1.136425407067405e-05);	// AU
	sol.v = Vector(-1.786236608923230e-06, -5.959144368171789e-06, 4.287462284225408e-08);	// AU / dia
	sol.m = 1.9891; // 1.9891 * 10^30 Kg
	sol.r = 255; sol.g = 255; sol.b = 0;

	mercurio.x = Vector(-2.563687782457914E-01, -3.810998677594219E-01, -8.153193298845162E-03);
	mercurio.v = Vector(1.781451838572982E-02, -1.414097937982711E-02, -2.789632381177015E-03);
	mercurio.m = 0.0000003302; // 3.302 * 10^23
	mercurio.r = 255; mercurio.g = 128; mercurio.b = 0;

	venus.x = Vector(-2.745105890947935E-01, 6.675955871621595E-01, 2.473298509458710E-02);
	venus.v = Vector(-1.880800003531344E-02, -7.736184882354628E-03, 9.795183384655537E-04);
	venus.m = 0.0000048685; // 48.685 * 10^23 Kg
	venus.r = 255; venus.g = 0; venus.b = 255;

	tierra.x = Vector(-7.262551982062518e-01, -7.016177342125620e-01, 2.942601923402196e-05);	// AU
	tierra.v = Vector(1.172032570433690e-02, -1.239499064419012e-02, -2.875393960566639e-07);	// AU / dia
	tierra.m = 0.0000059736; // 5.9736 * 10^24 Kg
	tierra.r = 0; tierra.g = 255; tierra.b = 0;

	luna.x = Vector(-7.248557601516714e-01, -7.039097848869444e-01, 1.029051462977911e-04);	// AU
	luna.v = Vector(1.220576787081027e-02, -1.211595432894550e-02, 4.775108508860639e-05);	// AU / dia
	luna.m = 0.00000007349; // 734.9 * 10^20 Kg = m_sol/10^10
	luna.r = 0; luna.g = 255; luna.b = 255;

	marte.x = Vector(-1.644799113455717E+00, 2.491823732968801E-01, 4.547552485947825E-02);
	marte.v = Vector(-1.562104985945559E-03, -1.264976840237743E-02, -2.265804582138816E-04);
	marte.m = 0.00000064185; // 6.4185 * 10^23 Kg
	marte.r = 255; marte.g = 0; marte.b = 0;

	jupiter.x = Vector(4.814383212086098E+00, -1.241505788193773E+00, -1.026521185883739E-01);
	jupiter.v = Vector(1.791829827597031E-03, 7.666882051378563E-03, -7.193518744890309E-05);
	jupiter.m = 0.00189813; // 1898.13 * 10^24 Kg
	jupiter.r = 255; jupiter.g = 0; jupiter.b = 255;

	saturno.x = Vector(-9.498834472404264E+00, -4.314789953129710E-01, 3.854986365834464E-01);
	saturno.v = Vector(-4.474247412442582E-05, -5.585253179574848E-03, 9.894753356331143E-05);
	saturno.m = 0.000568319; // 5.68319 * 10^26 Kg
	saturno.r = 255; saturno.g = 0; saturno.b = 255;

	planetas.push_back(sol);
	planetas.push_back(mercurio);
	planetas.push_back(venus);
	planetas.push_back(tierra);
	planetas.push_back(luna);
	planetas.push_back(marte);
	planetas.push_back(jupiter);
	planetas.push_back(saturno);

}

#endif
