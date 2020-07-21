#pragma once
#include "include.h"
/*
S	SRP
Принцип единственной ответственности (The Single Responsibility Principle)
Каждый класс должен иметь одну и только одну причину для изменений.
(нет Большим классам)
*/
//плохой пример
class Employee {
	int ID;
	std::string name;
public:
	int getID() const { return ID; }
	void setID(int val) { ID = val; }
	const std::string& getName() const { return name; }
	void setName(const char* n) { name = n; }

	bool addToDB() {
	//код описывающий вставку в бд
		return true;
	}
	void createReport() {
		//создание отчета о работнике
		std::cout << "Name " << name << std::endl;
	}
};
//код соответствующий SRP
class Employ {
	int ID;
	std::string name;
public:
	int getID() const { return ID; }
	void setID(int val) { ID = val; }
	const std::string& getName() const { return name; }
	void setName(const char* n) { name = n; }

	bool addToDB() {
		//код описывающий вставку в бд
		return true;
	}
};

class EmployReport {
public:
	void createReport(const Employ& empl) {
		//создание отчета о работнике
		std::cout << "Name " << empl.getName() << std::endl;
	}
};

/*
O	OCP
Принцип открытости/закрытости (The Open Closed Principle)
«программные сущности … должны быть открыты для расширения, но закрыты для модификации».
///необходимо использование наследования/интерфейсов
*/
//код не открыт для раширения, для добавления новой фигуры придется менять много кода
enum shape_type {circle,square};
class shape_bad {
	shape_type type;
public:
	shape_type getType()const { return type; }
};
class circle_bad:public shape_bad {
public:
	void draw_circle() {
	//рисуем круг
		std::cout << "paint circle\n";
	}
};
class square_bad :public shape_bad {
public:
	void draw_square() {
		//рисуем квадрат
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
///вариант более привильного кода
class shape_good {
	shape_type type;
public:
	shape_type getType()const { return type; }
	virtual void draw_shape() = 0;//сделано для того чтобы в каждой фигуре 
	//было описано как ее рисовать
};
class circle_good :public shape_good {
public:
	void draw_circle() {
		//рисуем круг
	}
	void draw_shape()override {
		draw_circle();//вызов рисовалки круга
		std::cout << "paint circle\n";
	}
};
class square_good :public shape_good {
public:
	void draw_square() {
		//рисуем квадрат
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
Принцип подстановки Барбары Лисков (The Liskov Substitution Principle)
«объекты в программе должны быть заменяемыми на экземпляры их подтипов без изменения правильности выполнения программы». См. также контрактное программирование.
Наследующий класс должен дополнять, а не изменять базовый.
*/
class TemperatureController
{
	// Переменная для хранения опорной температуры
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
		// Уговариваем девайс дружить с нами
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
		// Уж больно хитрый девайс попался: ему температуру в надо
		// Кельвинах предоставить! Хорошо, что не в Фаренгейтах.
		std::cout << "T-" << temperature + 273<<" K\n";
	}

	void InitializeDevice()
	{
		// Склоняем термостат к сотрудничеству
	}
};
class Brand_C_TemperatureController : public TemperatureController
{//проблемный класс
public:

	// Геттер/сеттер общается непосредственно с девайсом
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
		// Нафиг ненужный метод: мы температурой управляем в другом месте
	}
	void InitializeDevice()
	{
		// Тут шаманские пляски, чтобы термостат ниспослал нам хорошую погоду
	}
};
void liskov() {
	TemperatureController* pTempCtrl = new Brand_A_TemperatureController;
	pTempCtrl->SetReferenceTemperature(10);
	pTempCtrl->InitializeDevice();
	//бядабяда....
	TemperatureController* pTempCtrl = new Brand_C_TemperatureController;
	pTempCtrl->SetReferenceTemperature(10);
	pTempCtrl->InitializeDevice();
}

/*
I	ISP
Принцип разделения интерфейса (The Interface Segregation Principle)
«много интерфейсов, специально предназначенных для клиентов, лучше, 
чем один интерфейс общего назначения».
*/


/*
D	DIP
Принцип инверсии зависимостей (The Dependency Inversion Principle)
«Зависимость на Абстракциях. Нет зависимости на что-то конкретное».
*/