#pragma once

class CVector3D
{
public:
	// Конструирует нулевой вектор
	CVector3D()
	{
		x = 0;
		y = 0;
		z = 0;
	};
	// Конструирует вектор с заданными координатами
	CVector3D(double x0, double y0, double z0)
	{
		x = x0;
		y = y0;
		z = z0;
	};
	const CVector3D operator+()const;
	const CVector3D operator-()const;
	CVector3D const operator+(CVector3D const& vector)const;
	CVector3D const operator-(CVector3D const & vector)const;
	const CVector3D operator *(double scalar)const;
	CVector3D const operator/(double scalar)const;
	CVector3D& operator+=(CVector3D const& vector);
	CVector3D & operator-=(CVector3D const & vector);
	bool operator==(CVector3D const& vector)const;
	bool operator!=(CVector3D const &other)const;
	
	CVector3D & operator*=(double scalar);
	CVector3D const operator/=(double scalar);
	double GetLength() const; // Возвращает длину вектора
	
	friend CVector3D const operator *(double scalar, CVector3D const& vector);

	void Normalize();// Нормализует вектор (приводит его к единичной длине)
	double x, y, z;
private:
	
	
};
CVector3D const operator *(double scalar, CVector3D const& vector);