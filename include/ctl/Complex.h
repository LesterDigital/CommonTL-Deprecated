#pragma once

#ifndef CTL_COMPLEX_H
#define CTL_COMPLEX_H

#include <ostream>

namespace ctl::Math
{
	struct Complex
	{
		double Real;
		double Imaginary;

		Complex()
			: Real(0), Imaginary(0) {}

		Complex(double real, double imaginary)
			: Real(real), Imaginary(imaginary) {}

		void Set(double real, double imaginary)
		{
			Real = real;
			Imaginary = imaginary;
		}

		Complex Add(const Complex& other) const
		{
			return Complex(Real + other.Real, Imaginary + other.Imaginary);
		}
		Complex Sub(const Complex& other) const
		{
			return Complex(Real - other.Real, Imaginary - other.Imaginary);
		}

		Complex Mult(double num) const
		{
			return Complex(Real * num, Imaginary * num);
		}
		Complex Divide(double num) const
		{
			return Complex(Real / num, Imaginary / num);
		}

		Complex Mult(const Complex& other) const
		{
			return Complex(
				Real * other.Real + Imaginary * other.Imaginary * (-1), // Real
				Real * other.Imaginary + Imaginary * other.Real // Imaginary
			);
		}
		Complex Divide(Complex other) const
		{
			Complex conjugate = other;
			conjugate.Imaginary = -conjugate.Imaginary;

			return this->Mult(conjugate).Divide(other.Mult(conjugate).Real);
		}

		Complex operator + (const Complex& other) const { return Add(other); }
		Complex operator - (const Complex& other) const { return Sub(other); }
		Complex operator * (const Complex& other) const { return Mult(other); }
		Complex operator / (const Complex& other) const { return Divide(other); }
		Complex operator * (const double& num) const { return Mult(num); }
		Complex operator / (const double& num) const { return Divide(num); }

		void operator += (const Complex& other) { *this = Add(other); }
		void operator -= (const Complex& other) { *this = Sub(other); }
		void operator *= (const Complex& other) { *this = Mult(other); }
		void operator /= (const Complex& other) { *this = Divide(other); }
		void operator *= (double num) { *this = Mult(num); }
		void operator /= (double num) { *this = Divide(num); }

		friend std::ostream& operator << (std::ostream& stream, const Complex& cx)
		{
			stream << "Real: " << cx.Real << " Imaginary: " << cx.Imaginary << std::endl;

			return stream;
		}
	};
}

#endif
