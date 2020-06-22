#pragma once
#include "include.h"

/*
Модель (Model) предоставляет данные и реагирует на команды контроллера, изменяя своё состояние.
Представление (View) отвечает за отображение данных модели пользователю, реагируя на изменения модели.
Контроллер (Controller) интерпретирует действия пользователя, оповещая модель о необходимости изменений.
https://habr.com/ru/post/215605/
*/

class Observer//наблюдатель для взаимодействия всех компонентов
{
public:
    virtual void update() = 0;
};

class Observable
{
public:
    void addObserver(Observer* observer)
    {
        _observers.push_back(observer);
    }
    void notifyUpdate()
    {
        int size = _observers.size();
        for (int i = 0; i < size; i++)
        {
            _observers[i]->update();
        }
    }
private:
    std::vector<Observer*> _observers;
};

class TemperatureModel : public Observable
{
public:
    double getF()
    {
        return _temperatureF;
    }
    double getC()
    {
        return (_temperatureF - 32.0) * 5.0 / 9.0;
    }
    void setF(double tempF)
    {
        _temperatureF = tempF;
        notifyUpdate();
    }
    void setC(double tempC)
    {
        _temperatureF = tempC * 9.0 / 5.0 + 32.0;
        notifyUpdate();
    }
private:
    double _temperatureF;
};

class ConsoleView : public Observer
{
public:
    ConsoleView(TemperatureModel* model)
    {
        _model = model;
        _model->addObserver(this);
    }
    virtual void update()
    {
        system("cls");
        std::cout.precision(4);
        std::cout << "Temperature in Celsius: " << _model->getC() << std::endl;
        std::cout << "Temperature in Farenheit: "<< _model->getF() << std::endl;
        std::cout << "Input temperature in Celsius: ";
    }
private:
    TemperatureModel* _model;
};

class Controller
{
public:
    Controller(TemperatureModel* model)
    {
        _model = model;
    }
    void start()
    {
        _model->setC(0);

        double temp;
        do
        {
            std::cin>>temp;
            _model->setC(temp);
        } while (temp != 0);
    }
private:
    TemperatureModel* _model;
};
void mvc()
{
    TemperatureModel model;
    ConsoleView view(&model);
    Controller controller(&model);
    controller.start();
   
}