
class InterfazDeArquero
{
	public:
		InterfazDeArquero() { posicion=0;ultima_direccion=0; }
		virtual void Inicializar() = 0;
		virtual int Respuesta(int i) = 0;
		virtual int Respuesta(int i, double x, double y) = 0;
		double Posicion() const { return posicion; };
		int UltimaDireccion() const { return ultima_direccion; };
		void Mover(int direccion);
	protected:
		int Decidir(double x_pelota);
	private:
		double posicion;
		int ultima_direccion;
};

void InterfazDeArquero::Mover(int direccion)
{
	if( direccion*ultima_direccion < 0 )
		ultima_direccion=0;
	else
		ultima_direccion=direccion;

	posicion += ultima_direccion*0.05;
}

int InterfazDeArquero::Decidir(double x_pelota)
{
	if (x_pelota-Posicion() >= .05)
	{
		Mover(1);
		return 2;
	}
	else if (x_pelota-Posicion() <= .05)
	{
		Mover(-1);
		return 1;
	}
	else
	{
		Mover(0);
		return 0;
	}
}
