//////////////////////////////////////////
//	C++ Polymorphism
//	Naughty Panda @ 2021
//////////////////////////////////////////

#include <iostream>

#ifdef _DEBUG
#define DEBUG_LOG(m) std::cout << (m) << std::endl
#else
#define DEBUG_LOG(m)
#endif

//////////////////////////////////////////
/// 3.1
//////////////////////////////////////////

class Figure {

public:
	virtual float Area() const = 0;

protected:
	Figure() { DEBUG_LOG("Figure()"); }
	virtual ~Figure() { DEBUG_LOG("~Figure()"); }
};

class Parallelogram : public Figure {

protected:
	float _length{ 1.0f };
	float _height{ 1.0f };

public:
	Parallelogram(const float& l, const float& h) : _length(l), _height(h) { DEBUG_LOG("Parallelogram()"); }
	virtual ~Parallelogram() { DEBUG_LOG("~Parallelogram()"); }

	float Area() const override { return _length * _height; }
};

class Circle : public Figure {

protected:
	float _radius{ 1.0f };
	const float _pi{ 3.14f };

public:
	Circle(const float& r) : _radius(r) { DEBUG_LOG("Circle()"); }
	~Circle() { DEBUG_LOG("~Circle()"); }

	float Area() const override { return _pi * _radius * _radius; }
};

class Rectangle : public Parallelogram {

public:
	Rectangle(const float& l, const float& w) : Parallelogram(l, w) { DEBUG_LOG("Rectangle()"); }
	~Rectangle() { DEBUG_LOG("~Rectangle()"); }

	// Base class Area() method should work the same for all children
	// So we don't actually need to override it
	float Area() const override { return Parallelogram::Area(); }
};

class Square : public Parallelogram {
	
public:
	Square(const float& l, const float& w) : Parallelogram(l, w) { DEBUG_LOG("Square()"); }
	~Square() { DEBUG_LOG("~Square()"); }

	float Area() const override { return Parallelogram::Area(); }
};

class Rhombus : public Parallelogram {
	
public:
	Rhombus(const float& l, const float& w) : Parallelogram(l, w) { DEBUG_LOG("Rhombus()"); }
	~Rhombus() { DEBUG_LOG("~Rhombus()"); }

	float Area() const override { return Parallelogram::Area(); }
};

//////////////////////////////////////////
/// 3.2
//////////////////////////////////////////

class Car {

public:
	static uint8_t _nCount;

protected:
	std::string _sCompany{ "no_company" };
	std::string _sModel{ "no_model" };

	Car(const char* c, const char* m);
	virtual ~Car() { DEBUG_LOG("~Car()"); }
};

class PassengerCar : virtual public Car {

public:
	PassengerCar(const char* c, const char* m);
	virtual ~PassengerCar() { DEBUG_LOG("~PassengerCar()"); }
};

class Bus : virtual public Car {

public:
	Bus(const char* c, const char* m);
	virtual ~Bus() { DEBUG_LOG("~Bus()"); }
};

class Minivan : public PassengerCar, public Bus {

public:
	Minivan(const char* c, const char* m);
	~Minivan() { DEBUG_LOG("~Minivan()"); }
};

uint8_t Car::_nCount{ 0 };

Car::Car(const char* c, const char* m) : _sCompany(c), _sModel(m) {

	DEBUG_LOG("\nCar()");
	std::cout << "Car # " << static_cast<int>(++_nCount) << std::endl;
	std::cout << "Car \"" << _sModel << "\" by " << _sCompany << std::endl;
}

PassengerCar::PassengerCar(const char* c, const char* m) : Car(c, m) {

	DEBUG_LOG("PassengerCar()");
	std::cout << "Passenger car \"" << _sModel << "\" by " << _sCompany << std::endl;
}

Bus::Bus(const char* c, const char* m) : Car(c, m) {

	DEBUG_LOG("Bus()");
	std::cout << "Bus \"" << _sModel << "\" by " << _sCompany << std::endl;
}

Minivan::Minivan(const char* c, const char* m) : PassengerCar(c,m), Bus(c,m), Car(c,m) {

	DEBUG_LOG("Minivan()");
	std::cout << "Minivan \"" << m << "\" by " << c << std::endl;
}

//////////////////////////////////////////
/// 3.3
//////////////////////////////////////////

class Fraction {

private:
	int _numerator{ 1 };
	int _denominator{ 1 };

public:

	// Denominator can't be 0, so if constructor gets 0, it will be 1 instead
	Fraction(const int& num, const int& denom) : _numerator(num), _denominator(denom ? denom : 1) {}

	int GetNumerator() const { return _numerator; }
	int GetDenominator() const { return _denominator; }
	void Print() const { std::cout << _numerator << "/" << _denominator << std::endl; }
	float GetValue() const { return static_cast<float>(_numerator) / _denominator; }

	// Operator overload using friend function
	friend Fraction operator+(const Fraction& f1, const Fraction& f2);

	// Operator overload using class methods
	Fraction operator-(const Fraction& f);
	Fraction operator-() const { return Fraction{ -_numerator, _denominator }; }

	bool operator==(const Fraction& f) const { return this->GetValue() == f.GetValue() ? true : false; }
	bool operator!=(const Fraction& f) const { return *this == f ? false : true; }
	bool operator>(const Fraction& f) const { return this->GetValue() > f.GetValue() ? true : false; }
	bool operator<=(const Fraction& f) const { return *this > f ? false : true; }
	bool operator<(const Fraction& f) const { return this->GetValue() < f.GetValue() ? true : false; }
	bool operator>=(const Fraction& f) const { return *this < f ? false : true; }
};

Fraction operator+(const Fraction& f1, const Fraction& f2) {

	int denominator = f1._denominator * f2._denominator;
	int numerator = f1._numerator * denominator / f1._denominator + f2._numerator * denominator / f2._denominator;
	return Fraction{ numerator, denominator };
}

// Should be const btw! But let's try with *this
Fraction Fraction::operator-(const Fraction& f) {

	int denominator = _denominator * f._denominator;
	_numerator = _numerator * denominator / _denominator - f._numerator * denominator / f._denominator;
	_denominator = denominator;
	return *this;
}

// Operator overload using functions
Fraction operator*(const Fraction& f1, const Fraction& f2) {

	return Fraction{ f1.GetNumerator() * f2.GetNumerator(), f1.GetDenominator() * f2.GetDenominator() };
}

Fraction operator/(const Fraction& f1, const Fraction& f2) {

	return Fraction{ f1.GetNumerator() * f2.GetDenominator(), f1.GetDenominator() * f2.GetNumerator() };
}

//////////////////////////////////////////
/// 3.4
//////////////////////////////////////////

enum class ECardSuit {

	Clubs = 1, Diamonds, Hearts, Spades,
	Undefined = 0
};

enum class ECardValue : uint8_t {

	Two = 2U, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
	Jack = 10U, Queen = 10U, King = 10U, Ace = 1U,
	Undefined = 0U
};

class Card {

protected:
	ECardSuit _suit{ ECardSuit::Undefined };
	ECardValue _value{ ECardValue::Undefined };
	bool _bVisible{ false };

public:
	ECardValue GetValue() const { return _value; }
	void Flip() { _bVisible = !_bVisible; }
};


int main() {

	//////////////////////////////////////////
	/// 3.1
	//////////////////////////////////////////

	Parallelogram p{ 2.0f, 3.0f };
	Figure* f1 = &p;
	std::cout << "Parallelogram's area: " << f1->Area() << std::endl;

	Circle c{ 4.0f };
	Figure* f2 = &c;
	std::cout << "Circle's area: " << f2->Area() << std::endl;

	Rectangle r{ 5.0f, 7.0f };
	Figure* f3 = &r;
	std::cout << "Rectangle's area: " << f3->Area() << std::endl;

	Square s{ 4.0f, 9.0f };
	Figure* f4 = &s;
	std::cout << "Square's area: " << f4->Area() << std::endl;

	Rhombus rh{ 3.0f, 6.0f };
	Figure* f5 = &rh;
	std::cout << "Rhombus's area: " << f5->Area() << std::endl;

	//////////////////////////////////////////
	/// 3.2
	//////////////////////////////////////////
	{
		PassengerCar pc{ "Toyota", "Camry" };
	} {
		Bus b{ "Ikarus", "250 SL" };
	} {
		Minivan m{ "Dodge", "Caravan" };
	}

	//////////////////////////////////////////
	/// 3.3
	//////////////////////////////////////////

	Fraction fr1{ 1,3 };
	Fraction fr2{ 4,5 };
	Fraction fr3 = fr1 + fr2;
	std::cout << "1/3 + 4/5 = ";
	fr3.Print();

	fr3 = fr1 - fr2;
	std::cout << "1/3 - 4/5 = ";
	fr3.Print();

	fr1 = { 2,3 };
	fr2 = { 4,7 };
	fr3 = fr1 * fr2;
	std::cout << "2/3 * 4/7 = "; 
	fr3.Print();

	fr1 = { 1,6 };
	fr2 = { 3,8 };
	fr3 = fr1 / fr2;
	std::cout << "1/6 / 3/8 = ";
	fr3.Print();

	fr3 = { 2,5 };
	fr3 = -fr3;
	std::cout << "-2/5 = ";
	fr3.Print();

	fr1 = { 1,3 };
	fr2 = { 2,6 };
	std::cout << "1/3 != 2/6 ? " << (fr1 != fr2 ? "true" : "false") << std::endl;
	std::cout << "1/3 == 2/6 ? " << (fr1 == fr2 ? "true" : "false") << std::endl;
	std::cout << "1/3 > 2/6 ? " << (fr1 > fr2 ? "true" : "false") << std::endl;
	std::cout << "1/3 >= 2/6 ? " << (fr1 >= fr2 ? "true" : "false") << std::endl;
	std::cout << "1/3 < 2/6 ? " << (fr1 < fr2 ? "true" : "false") << std::endl;
	std::cout << "1/3 <= 2/6 ? " << (fr1 <= fr2 ? "true" : "false") << std::endl;

	return 0;
}
