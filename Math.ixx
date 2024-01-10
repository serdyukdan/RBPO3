module;
#include <iostream>
export module Math;
export namespace Math
{
	export class Complex
	{
	private:
		double m_re;
		double m_im;
	public:
		Complex() { m_re = 0; m_im = 0; }
		Complex(double x, double y) { m_re = x; m_im = y; }
		Complex(double x) { m_re = x; m_im = 0; }
		static Complex FromExponentialForm(double x, double y)
		{
			double re = x * cos(y);
			double im = x * sin(y);
			Complex now(re, im);
			return now;
		}
		static Complex FromAlgebraicForm(double re, double im)
		{
			Complex now(re, im);
			return now;
		}
		double Re() const { return m_re; }
		double Im() const { return m_im; }
		double Mod() const { return sqrt(m_re * m_re + m_im * m_im); }
		double Arg() const { return atan2(m_im, m_re); }
		explicit operator double() const { return m_re; }
		Complex operator- () { return Complex(-m_re, -m_im); }
		Complex& operator++ () { m_re = m_re + 1; return *this; }
		Complex operator++ (int x)
		{
			Complex star = *this; m_re = m_re + 1; return star;
		}
		Complex& operator-- () { m_re = m_re - 1; return *this; }
		Complex operator-- (int x)
		{
			Complex star = *this; this->m_re = this->m_re - 1; return star;
		}
		Complex& operator+= (Complex x) { m_re = m_re + x.m_re; m_im = m_im + x.m_im; return *this; }
		Complex& operator-= (Complex x) { m_re = m_re - x.m_re; m_im = m_im - x.m_im; return *this; }
		Complex& operator*= (Complex x)
		{
			double real = m_re;
			double im = m_im;
			m_re = real * x.m_re - im * x.m_im;
			m_im = real * x.m_im + im * x.m_re;
			return *this;
		}
		Complex& operator/= (Complex x)
		{
			double real1 = m_re, real2 = x.m_re;
			double im1 = m_im, im2 = x.m_im;
			m_re = (real1 * real2 + im1 * im2) / (real2 * real2 + im2 * im2);
			m_im = (real2 * im1 - real1 * im2) / (real2 * real2 + im2 * im2);
			return *this;
		}
		friend Complex operator+(Complex lhs, Complex rhs);
		friend Complex operator-(Complex lhs, Complex rhs);
		friend Complex operator*(Complex lhs, Complex rhs);
		friend Complex operator/(Complex lhs, Complex rhs);
		friend Complex operator""i(long double x);
		friend Complex operator""i(unsigned long long x);
		friend std::ostream& operator<< (std::ostream& os, const Complex complex);
	};
	export Complex operator+ (Complex lhs, Complex rhs)
	{
		double re = lhs.m_re + rhs.m_re;
		double im = lhs.m_im + rhs.m_im;
		return Complex(re, im);
	}
	export Complex operator- (Complex lhs, Complex rhs)
	{
		double re = lhs.m_re - rhs.m_re;
		double im = lhs.m_im - rhs.m_im;
		return Complex(re, im);
	}
	export Complex operator*(Complex lhs, Complex rhs)
	{
		double re = lhs.m_re * rhs.m_re - lhs.m_im * rhs.m_im;
		double im = lhs.m_re * rhs.m_im + lhs.m_im * rhs.m_re;
		return Complex(re, im);
	}
	export Complex operator/ (Complex lhs, Complex rhs)
	{
		double re = (lhs.m_re * rhs.m_re + lhs.m_im * rhs.m_im) / (rhs.m_re * rhs.m_re + rhs.m_im * rhs.m_im);
		double im = (lhs.m_im * rhs.m_re - lhs.m_re * rhs.m_im) / (rhs.m_re * rhs.m_re + rhs.m_im * rhs.m_im);
		return Complex(re, im);
	}
	export Complex operator""i(long double x)
	{
		return Complex(0, static_cast<double>(x));
	}
	export Complex operator""i(unsigned long long x)
	{
		return Complex(0, double(x));
	}
	export int FindGreatestCommonDivisor(int a, int b)
	{
		if (a < b)
		{
			int temp = a;
			a = b;
			b = temp;
		}
		int r;
		while (b != 0)
		{
			r = a % b;
			a = b;
			b = r;
		}
		return abs(a);
	}
	export int FindLeastCommonMultiple(int x, int y)
	{
		return abs(x * y) / FindGreatestCommonDivisor(x, y);
	}
	export std::ostream& operator<< (std::ostream& os, const Complex complex)
	{
		if (complex.m_im < 0)
			return os << complex.m_re << complex.m_im << "i";
		else
			return os << complex.m_re << "+" << complex.m_im << "i";
	}
	export class Rational
	{
	private:
		int m_nominator;
		int m_denominator;
	public:
		void socr()
		{
			int nod = FindGreatestCommonDivisor(m_nominator, m_denominator);
			m_nominator = m_nominator / nod;
			m_denominator = m_denominator / nod;
			if (m_nominator < 0 && m_denominator < 0)
			{
				m_nominator = -m_nominator;
				m_denominator = -m_denominator;
			}
			else
				if (m_nominator > 0 && m_denominator < 0)
				{
					m_nominator = -m_nominator;
					m_denominator = -m_denominator;
				}
		}
		Rational() { m_nominator = 0; m_denominator = 1; }
		Rational(int x, int y)
		{
			m_nominator = x;
			m_denominator = y;
			this->socr();
		}
		Rational(int x) { m_nominator = x; m_denominator = 1; }
		int Nominator() const { return m_nominator; }
		int Denominator() const { return m_denominator; }
		explicit operator double() const { return double(m_nominator) / m_denominator; }
		Rational operator- () { return Rational(-this->m_nominator, this->m_denominator); }
		Rational& operator++ () { m_nominator += m_denominator; socr(); return *this; }
		Rational operator++ (int x) { Rational star = *this; (*this).m_nominator += m_denominator; socr(); return star; }
		Rational& operator-- () { m_nominator -= m_denominator; socr(); return *this; }
		Rational operator-- (int x) { Rational star = *this; (*this).m_nominator -= m_denominator; socr(); return star; }
		Rational& operator+= (Rational x)
		{
			int no = m_nominator * x.m_denominator + m_denominator * x.m_nominator;
			int de = m_denominator * x.m_denominator;
			m_nominator = no;
			m_denominator = de;
			socr();
			return *this;
		}
		Rational& operator-= (Rational x)
		{
			int no = m_nominator * x.m_denominator - m_denominator * x.m_nominator;
			int de = m_denominator * x.m_denominator;
			m_nominator = no;
			m_denominator = de;
			socr();
			return *this;
		}
		Rational& operator*= (Rational x)
		{
			int no = m_nominator * x.m_nominator;
			int de = m_denominator * x.m_denominator;
			m_nominator = no;
			m_denominator = de;
			socr();
			return *this;
		}
		Rational& operator/= (Rational x)
		{
			int no = m_nominator * x.m_denominator;
			int de = m_denominator * x.m_nominator;
			m_nominator = no;
			m_denominator = de;
			socr();
			return *this;
		}
		friend Rational operator+ (Rational lhs, Rational rhs);
		friend Rational operator- (Rational lhs, Rational rhs);
		friend Rational operator* (Rational lhs, Rational rhs);
		friend Rational operator/ (Rational lhs, Rational rhs);
		friend bool operator== (Rational lhs, Rational rhs);
		friend int operator<=> (Rational lhs, Rational rhs);
		friend bool operator< (Rational lhs, Rational rhs);
		friend bool operator<= (Rational lhs, Rational rhs);
		friend bool operator> (Rational lhs, Rational rhs);
		friend bool operator>= (Rational lhs, Rational rhs);

		friend std::ostream& operator<< (std::ostream& os, const Rational& rational);
	};
	export Rational operator+ (Rational lhs, Rational rhs)
	{
		int no = lhs.m_nominator * rhs.m_denominator + lhs.m_denominator * rhs.m_nominator;
		int de = lhs.m_denominator * rhs.m_denominator;
		Rational now = Rational(no, de);
		now.socr();
		return now;
	}
	export Rational operator- (Rational lhs, Rational rhs)
	{
		int no = lhs.m_nominator * rhs.m_denominator - lhs.m_denominator * rhs.m_nominator;
		int de = lhs.m_denominator * rhs.m_denominator;
		Rational now = Rational(no, de);
		now.socr();
		return now;
	}
	export Rational operator* (Rational lhs, Rational rhs)
	{
		int no = lhs.m_nominator * rhs.m_nominator;
		int de = lhs.m_denominator * rhs.m_denominator;
		Rational now = Rational(no, de);
		now.socr();
		return now;
	}
	export Rational operator/ (Rational lhs, Rational rhs)
	{
		int no = lhs.m_nominator * rhs.m_denominator;
		int de = lhs.m_denominator * rhs.m_nominator;
		Rational now = Rational(no, de);
		now.socr();
		return now;
	}

	export bool operator== (Rational lhs, Rational rhs)
	{
		if (lhs.m_nominator == rhs.m_nominator && lhs.m_denominator == rhs.m_denominator)
			return true;
		else
			return false;
	}
	export int operator<=> (Rational lhs, Rational rhs)
	{
		if (lhs == rhs)
			return 0;
		Rational rez = lhs - rhs;
		if (rez.Nominator() > 0)
			return 1;
		else
			return -1;
	}
	export bool operator< (Rational lhs, Rational rhs)
	{
		if ((lhs <=> rhs) == -1)
			return true;
		else
			return false;
	}
	export bool operator<= (Rational lhs, Rational rhs)
	{
		if (lhs <=> rhs == -1)
			return true;
		if (lhs <=> rhs == 0)
			return true;
		else
			return false;
	}
	export bool operator> (Rational lhs, Rational rhs)
	{

		if (lhs <=> rhs == 1)
			return true;
		else
			return false;
	}

	export bool operator>= (Rational lhs, Rational rhs)
	{
		{
			if (lhs <=> rhs == 1)
				return true;
			if (lhs <=> rhs == 0)
				return true;
			else
				return false;
		}
	}
	export std::ostream& operator<< (std::ostream& os, const Rational& rational)
	{
		return os << rational.m_nominator << "/" << rational.m_denominator;
	}
}
