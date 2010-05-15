#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>
using namespace std;

// Las operaciones suponen que rige una regla de mano derecha en el espacio vectorial

class Vector3{

	public:

		/* Constructor por defecto */
		Vector3();

		/* Constructor que toma las coordenadas */
		Vector3(const double& _x, const double& _y, const double& _z);
//		Vector3(double _x, double _y, double _z);

		/* Constructor que toma los angulo th y phi donde 
		 * th = angulo en el plano xy
		 * phi = angulo en z 			*/
		Vector3(double& th, double& phi);
		Vector3(double th, double phi);

		double X() const;
		double Y() const;
		double Z() const;
		double& X(){return x;}
		double& Y(){return y;}
		double& Z(){return z;}

		/* Devuelve la norma del vector */
		double norm() const;

		/* devuelve el mismo vector pero normalizado */
		Vector3 normalize() const;

		/* Devuelve la inversa del vector */
		Vector3 inverse() const;

		/* Se fija si dos vectores son muy parecidos segun un umbral l */
		bool near(const Vector3& v, const double& l);

		/* refleja un vector con respecto a una normal N */
		Vector3 reflect(const Vector3& N) const;

		/* calcula la direccion del vector refractado segun la normal N 
		 * y los indices de refraccion n0 y n1 cuando pasa de n0 a n1 */
		Vector3 refract(const Vector3& N, const double& n0, const double& n1) const;

		// rota alrededor de z (phi grados) y luego alrededor de y (theta grados) en sentido horario
		Vector3 rotate(const double phi, const double theta) const;

		/* Operadores */

		Vector3 operator + (const Vector3& b) const;
		void operator += (const Vector3& b);

		void operator - ();
		Vector3 operator - (const Vector3& b) const;
		void operator -= (const Vector3& b);

		Vector3 operator * (const double& n) const;
		void operator *= (const double& n);
		friend Vector3 operator * (const double& n, const Vector3& v);

		Vector3 operator / (const double& n) const;
		void operator /= (const double& n);

		/* Producto interno */
		double operator * (const Vector3& b) const;

		/* Producto cruz */
		Vector3 operator ^ (const Vector3& b) const;

		friend ostream& operator << (ostream& os, const Vector3& v);

	private:

		double x;
		double y;
		double z;

};

Vector3 operator * (const double& n, const Vector3& v);

ostream& operator << (ostream& os, const Vector3& v);

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(const double& _x, const double& _y, const double& _z) : x(_x), y(_y), z(_z) {}

//Vector3::Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

Vector3::Vector3(double& th, double& phi) : x(cos(th)*sin(phi)), y(sin(th)*sin(phi)), z(cos(phi)) {}

Vector3::Vector3(double th, double phi) : x(cos(th)*sin(phi)), y(sin(th)*sin(phi)), z(cos(phi)) {}

double Vector3::X() const {
	return x;
}

double Vector3::Y() const {
	return y;
}

double Vector3::Z() const {
	return z;
}

double Vector3::norm() const {
	return sqrt(x*x+y*y+z*z);
}

Vector3 Vector3::normalize() const {
	double n = norm();
	return Vector3(x/n,y/n,z/n);
}

Vector3 Vector3::inverse() const {
	return Vector3(-x,-y,-z);
}

bool Vector3::near(const Vector3& v, const double& l){
	return ((v-(*this)).norm() < l);
}

Vector3 Vector3::reflect(const Vector3& N) const {
	return ( (*this) - N*(2*(N*(*this))) ).normalize();
}

Vector3 Vector3::refract(const Vector3& N, const double& n0, const double& n1) const {

	float n = n0 / n1;

	// coseno del angulo entre el rayo incidente y la normal
	float cos_i = N*(*this);

	// seno del angulo entre el rayo refractado y la inversa de la normal
	float sin2_r = n*n*(1.0-cos_i*cos_i);

	// chequeo por TIR (total internal reflection)
	if(sin2_r > 1.0) cout << "OJO! TIR" << endl;

	return ( (*this)*n - N*( n*cos_i + sqrtf(1-sin2_r) ) );
}

Vector3 Vector3::rotate(const double phi, const double theta) const{
	// roto alrededor de z
	Vector3 zz(
		x*cos(phi) + y*sin(phi),
		-x*sin(phi) + y*cos(phi),
		z
	);
	// roto alrededor de y a zz
	Vector3 yy(
		zz.x,
		zz.y*cos(theta) + zz.z*sin(theta),
		-zz.y*sin(theta) + zz.z*cos(theta)
	);
	return yy;
}

Vector3 Vector3::operator + (const Vector3& b) const {
	return Vector3(x+b.x,y+b.y,z+b.z);
}

void Vector3::operator += (const Vector3& b){
	x += b.x;
	y += b.y;
	z += b.z;
}

void Vector3::operator - (){
	x = -x;
	y = -y;
	z = -z;
}

Vector3 Vector3::operator - (const Vector3& b) const {
	return Vector3(x-b.x,y-b.y,z-b.z);
}

void Vector3::operator -= (const Vector3& b){
	x -= b.x;
	y -= b.y;
	z -= b.z;
}

double Vector3::operator * (const Vector3& b) const {
	return (x*b.x)+(y*b.y)+(z*b.z);
}

Vector3 Vector3::operator * (const double& n) const {
	return Vector3(x*n,y*n,z*n);
}

void Vector3::operator *= (const double& n){
	x *= n;
	y *= n;
	z *= n;
}

Vector3 Vector3::operator ^ (const Vector3& v) const {
	return Vector3(y*v.z-z*v.y , z*v.x-x*v.z , x*v.y-y*v.x );
}

Vector3 Vector3::operator / (const double& n) const {
	return Vector3(x/n,y/n,z/n);
}

void Vector3::operator /= (const double& n){
	x /= n;
	y /= n;
	z /= n;
}

Vector3 operator * (const double& n, const Vector3& v){
	return Vector3(v.x*n,v.y*n,v.z*n);
}

ostream& operator << (ostream& os, const Vector3& v){
	os << '<' << v.x << ',' << v.y << ',' << v.z << '>';
	return os;
}

#endif
