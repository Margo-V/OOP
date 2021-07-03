#include<iostream>

using namespace std;


class Animal
{
	string name;
	double weight;
public:
	Animal(const string& name, double weight) :name(name), weight(weight){}
	virtual~Animal(){}

	virtual void sound() const = 0;	//����� ����������� �����.
	// ���� ����� ������ ����� �����������

};


class Cat :public Animal
{
public:
	Cat(const string& name, double weight):Animal(name, weight){}

	~Cat() {}
	//��� ���� ����������� �����, ��������� �� ���������� (�� ���������) ����� ������������ ����� - soud()
};

class Tiger :public Cat
{
	unsigned int stripes;
public:
	Tiger(const string& name, double weight) :Cat(name, weight){}
	~Tiger(){}
	void sound()const
	{
		cout << "Rrrrrrr...." << endl;
	}
};

class HomeCat :public Cat
{
public:
	HomeCat(const string& name, double weight) :Cat(name, weight) {}
	~HomeCat() {}

	void sound()const
	{
		cout << "���....." << endl;
	}
};

class Dog :public Animal
{
public:
	Dog(const string& name, double weight):Animal(name, weight) {}
	~Dog() {}

	void sound()const
	{
		cout << "���-���!" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "ru");

	//Animal zverek("Tom", 3);	//Can not instantiate abstract class
	//Cat cat("Tom", 3);	//Can not instantiate abstract class
	Tiger tiger("Pushistik", 30);
	tiger.sound();
	HomeCat tom("Tom", 2);
	tom.sound();
	Dog dog("�����", 15);
	dog.sound();
}