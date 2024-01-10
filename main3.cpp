import Math;
#include<math.h>
#include<Windows.h>
#include<iostream>
using namespace Math;




double e = 2.7182;




Rational f(const Rational& r)
{
	Rational u = r;
	Rational rezult;
	Rational a = (1, 1);
	rezult = a - pow(double(u), 5) - ((exp(double(2 * u / 2)) - 1) / (exp(double(2 * u / 2)) + 1));
	return rezult;
}

Complex f(const Complex& z)
{
	Complex rezult;
	Complex u = z;
	Complex a = 1 + 0i;
	return rezult = a - pow(double(u), 5) - ((exp(double(2 * u / 2)) - 1) / (exp(double(2 * u / 2)) + 1));
}

double f(double x)
{
	double rezult;
	double a = 1.0;
	double u = x;
	rezult = a - pow(u, 5) - ((exp(2 * u / 2) - 1) / (exp(2 * u / 2) + 1));
	return rezult;
}

void main()
{
	setlocale(LC_ALL, "rus");
	int m, s;
	using namespase std;
	double a, b, x;

	cout << "Действительная часть: ";
	cin >> a;

	cout << "Мнимая часть: ";
	cin >> b;

	cout << "Числитель дроби: ";
	cin >> s;

	cout << "Знаменатель: ";
	cin >> m;

	cout << "Вещественное число: ";
	cin >> x;

	Math::Complex z = Math::Complex(a, b);
	Math::Rational r = Math::Rational(s, m);

	cout << "Комплексный: " << f(z) << endl;
	cout << "Рациональный: " << f(r) << endl;
	cout << "Вещественный: " << f(x) << endl;
}

