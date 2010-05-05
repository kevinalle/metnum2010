#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>
using namespace std;

// Las operaciones suponen que rige una regla de mano derecha en el espacio vectorial

class Vector{

	public:

		/* Constructor por defecto */
		Vector();

		/* Constructor que toma las coordenadas */
		Vector(double& _x, double& _y, double& _z);
		Vector(double _x, double _y, double _z);

		/* Constructor que toma los angulo th y phi donde 
		 * th = angulo en el plano xy
		 * phi = angulo en z 			*/
		Vector(double& th, double& phi);
		Vector(double th, double phi);

		double X() const;
		double Y() const;
		double Z() const;

		/* Devuelve la norma del vector */
		double norm() const;

		/* devuelve el mismo vector pero normalizado */
		Vector normalize() const;

		/* Devuelve la inversa del vector */
		Vector inverse() const;

		/* Se fija si dos vectores son muy parecidos segun un umbral l */
		bool near(const Vector& v, const double& l);

		/* refleja un vector con respecto a una normal N */
		Vector reflect(const Vector& N) const;

		/* calcula la direccion del vector refractado segun la normal N 
		 * y los indices de refraccion n0 y n1 cuando pasa de n0 a n1 */
		Vector refract(const Vector& N, const double& n0, const double& n1) const;

		// rota alrededor de z (phi grados) y luego alrededor de y (theta grados) en sentido horario
		Vector rotate(const double phi, const double theta) const;

		/* Operadores */

		Vector operator + (const Vector& b) const;
		void operator += (const Vector& b);

		void operator - ();
		Vector operator - (const Vector& b) const;
		void operator -= (const Vector& b);

		Vector operator * (const double& n) const;
		void operator *= (const double& n);
		friend Vector operator * (const double& n, const Vector& v);

		Vector operator / (const double& n) const;
		void operator /= (const double& n);

		/* Producto interno */
		double operator * (const Vector& b) const;

		/* Producto cruz */
		Vector operator ^ (const Vector& b) const;

		friend ostream& operator << (ostream& os, const Vector& v);

	private:

		double x;
		double y;
		double z;

};

Vector operator * (const double& n, const Vector& v);

ostream& operator << (ostream& os, const Vector& v);

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(double& _x, double& _y, double& _z) : x(_x), y(_y), z(_z) {}

Vector::Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

Vector::Vector(double& th, double& phi) : x(cos(th)*sin(phi)), y(sin(th)*sin(phi)), z(cos(phi)) {}

Vector::Vector(double th, double phi) : x(cos(th)*sin(phi)), y(sin(th)*sin(phi)), z(cos(phi)) {}

double Vector::X() const {
	return x;
}

double Vector::Y() const {
	return y;
}

double Vector::Z() const {
	return z;
}

double Vector::norm() const {
	return sqrtf(x*x+y*y+z*z);
}

Vector Vector::normalize() const {
	double n = norm();
	return Vector(x/n,y/n,z/n);
}

Vector Vector::inverse() const {
	return Vector(-x,-y,-z);
}

bool Vector::near(const Vector& v, const double& l){
	return ((v-(*this)).norm() < l);
}

Vector Vector::reflect(const Vector& N) const {
	return ( (*this) - N*(2*(N*(*this))) ).normalize();
}

Vector Vector::refract(const Vector& N, const double& n0, const double& n1) const {

	float n = n0 / n1;

	// coseno del angulo entre el rayo incidente y la normal
	float cos_i = N*(*this);

	// seno del angulo entre el rayo refractado y la inversa de la normal
	float sin2_r = n*n*(1.0-cos_i*cos_i);

	// chequeo por TIR (total internal reflection)
	if(sin2_r > 1.0) cout << "OJO! TIR" << endl;

	return ( (*this)*n - N*( n*cos_i + sqrtf(1-sin2_r) ) );
}

Vector Vector::rotate(const double phi, const double theta) const{
	// roto alrededor de z
	Vector zz(
		x*cos(phi) + y*sin(phi),
		-x*sin(phi) + y*cos(phi),
		z
	);
	// roto alrededor de y a zz
	Vector yy(
		zz.x,
		zz.y*cos(theta) + zz.z*sin(theta),
		-zz.y*sin(theta) + zz.z*cos(theta)
	);
	return yy;
}

Vector Vector::operator + (const Vector& b) const {
	return Vector(x+b.x,y+b.y,z+b.z);
}

void Vector::operator += (const Vector& b){
	x += b.x;
	y += b.y;
	z += b.z;
}

void Vector::operator - (){
	x = -x;
	y = -y;
	z = -z;
}

Vector Vector::operator - (const Vector& b) const {
	return Vector(x-b.x,y-b.y,z-b.z);
}

void Vector::operator -= (const Vector& b){
	x -= b.x;
	y -= b.y;
	z -= b.z;
}

double Vector::operator * (const Vector& b) const {
	return (x*b.x)+(y*b.y)+(z*b.z);
}

Vector Vector::operator * (const double& n) const {
	return Vector(x*n,y*n,z*n);
}

void Vector::operator *= (const double& n){
	x *= n;
	y *= n;
	z *= n;
}

Vector Vector::operator ^ (const Vector& v) const {
	return Vector(y*v.z-z*v.y , z*v.x-x*v.z , x*v.y-y*v.x );
}

Vector Vector::operator / (const double& n) const {
	return Vector(x/n,y/n,z/n);
}

void Vector::operator /= (const double& n){
	x /= n;
	y /= n;
	z /= n;
}

Vector operator * (const double& n, const Vector& v){
	return Vector(v.x*n,v.y*n,v.z*n);
}

ostream& operator << (ostream& os, const Vector& v){
	os << '<' << v.x << ',' << v.y << ',' << v.z << '>';
	return os;
}

#endif
