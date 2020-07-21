#pragma once
#include "include.h"
/*
S	SRP
������� ������������ ��������������� (The Single Responsibility Principle)
������ ����� ������ ����� ���� � ������ ���� ������� ��� ���������.
(��� ������� �������)
*/
//������ ������
class Employee {
	int ID;
	std::string name;
public:
	int getID() const { return ID; }
	void setID(int val) { ID = val; }
	const std::string& getName() const { return name; }
	void setName(const char* n) { name = n; }

	bool addToDB() {
	//��� ����������� ������� � ��
		return true;
	}
	void createReport() {
		//�������� ������ � ���������
		std::cout << "Name " << name << std::endl;
	}
};
//��� ��������������� SRP
class Employ {
	int ID;
	std::string name;
public:
	int getID() const { return ID; }
	void setID(int val) { ID = val; }
	const std::string& getName() const { return name; }
	void setName(const char* n) { name = n; }

	bool addToDB() {
		//��� ����������� ������� � ��
		return true;
	}
};

class EmployReport {
public:
	void createReport(const Employ& empl) {
		//�������� ������ � ���������
		std::cout << "Name " << empl.getName() << std::endl;
	}
};

/*
O	OCP
������� ����������/���������� (The Open Closed Principle)
������������ �������� � ������ ���� ������� ��� ����������, �� ������� ��� �����������.
///���������� ������������� ������������/�����������
*/
//��� �� ������ ��� ���������, ��� ���������� ����� ������ �������� ������ ����� ����
enum shape_type {circle,square};
class shape_bad {
	shape_type type;
public:
	shape_type getType()const { return type; }
};
class circle_bad:public shape_bad {
public:
	void draw_circle() {
	//������ ����
		std::cout << "paint circle\n";
	}
};
class square_bad :public shape_bad {
public:
	void draw_square() {
		//������ �������
		std::cout << "paint square\n";
	}
};
class draw_bad {
public:
	void paint(std::shared_ptr<shape_bad> sh) {
		if (sh->getType() == circle) {
			static_cast<circle_bad*>(sh.get())->draw_circle();
		}
		if (sh->getType() == square) {
			static_cast<square_bad*>(sh.get())->draw_square();
		}
	}
};
///������� ����� ����������� ����
class shape_good {
	shape_type type;
public:
	shape_type getType()const { return type; }
	virtual void draw_shape() = 0;//������� ��� ���� ����� � ������ ������ 
	//���� ������� ��� �� ��������
};
class circle_good :public shape_good {
public:
	void draw_circle() {
		//������ ����
	}
	void draw_shape()override {
		draw_circle();//����� ��������� �����
		std::cout << "paint circle\n";
	}
};
class square_good :public shape_good {
public:
	void draw_square() {
		//������ �������
		std::cout << "paint square\n";
	}
	void draw_shape() override {
		draw_square();
	}
};

class draw_good {
public:
	void paint(std::shared_ptr<shape_good> sh) {
		std::cout << "shape " << sh->getType() << std::endl;
		sh->draw_shape();
	}

};
/*
L	LSP
������� ����������� ������� ������ (The Liskov Substitution Principle)
�������� � ��������� ������ ���� ����������� �� ���������� �� �������� ��� ��������� ������������ ���������� ����������. ��. ����� ����������� ����������������.
����������� ����� ������ ���������, � �� �������� �������.
*/
class TemperatureController
{
	// ���������� ��� �������� ������� �����������
	int m_referenceTemperature;
public:
	virtual int GetReferenceTemperature() const	{
		return m_referenceTemperature;
	}

	virtual void SetReferenceTemperature(int referenceTemperature)	{
		m_referenceTemperature = referenceTemperature;
	}

	virtual int GetTemperature() const = 0;
	virtual void AdjustTemperature(int temperature) = 0;
	virtual void InitializeDevice() = 0;
};

class Brand_A_TemperatureController : public TemperatureController
{
public:

	int GetTemperature() const
	{
		int x; std::cin >> x;
		return x;
	}

	void AdjustTemperature(int temperature)
	{
		std::cout << "T-" << temperature << std::endl;
	}

	void InitializeDevice()
	{
		// ����������� ������ ������� � ����
	}
};

class Brand_B_TemperatureController : public TemperatureController
{
public:

	int GetTemperature() const
	{
		int x; std::cin >> x;
		return x;
	}

	void AdjustTemperature(int temperature)
	{
		// �� ������ ������ ������ �������: ��� ����������� � ����
		// ��������� ������������! ������, ��� �� � �����������.
		std::cout << "T-" << temperature + 273<<" K\n";
	}

	void InitializeDevice()
	{
		// �������� ��������� � ��������������
	}
};
class Brand_C_TemperatureController : public TemperatureController
{//���������� �����
public:

	// ������/������ �������� ��������������� � ��������
	int GetReferenceTemperature() const
	{
		int x; std::cout << "refrence: ";
		std::cin >> x;
		return x;
	}

	void SetReferenceTemperature(int referenceTemperature)
	{
		std::cout << "T-" << referenceTemperature << " grad\n";
	}

	int GetTemperature() const
	{
		int x; std::cin >> x;
		return x;
	}

	void AdjustTemperature(int temperature)
	{
		// ����� �������� �����: �� ������������ ��������� � ������ �����
	}
	void InitializeDevice()
	{
		// ��� ��������� ������, ����� ��������� ��������� ��� ������� ������
	}
};
void liskov() {
	TemperatureController* pTempCtrl = new Brand_A_TemperatureController;
	pTempCtrl->SetReferenceTemperature(10);
	pTempCtrl->InitializeDevice();
	//��������....
	TemperatureController* pTempCtrl = new Brand_C_TemperatureController;
	pTempCtrl->SetReferenceTemperature(10);
	pTempCtrl->InitializeDevice();
}

/*
I	ISP
������� ���������� ���������� (The Interface Segregation Principle)
������ �����������, ���������� ��������������� ��� ��������, �����, 
��� ���� ��������� ������ �����������.
*/


/*
D	DIP
������� �������� ������������ (The Dependency Inversion Principle)
������������ �� �����������. ��� ����������� �� ���-�� ����������.
*/