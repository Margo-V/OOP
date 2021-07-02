#include<iostream>
#include <regex>
using namespace std;

#define delimiter "\n------------------\n"

class Human
{
	string last_name;
	string first_name;
	unsigned int age;
public:
	const string& get_last_name()const
	{
		return last_name;
	}
	const string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const string& last_name)
	{
		std::regex en_rgx("[A-Z][a-z]{1,15}");
		std::regex ru_rgx("[А-Я][а-я]{1,15}");
		//std::regex ru_double_rgx("[А-Я][а-я-{1,15}[ -]{0,1}[А-Я]{0,1}[а-я]{0,15}");
		std::regex ru_double_rgx("([А-Я][а-я]{1,15}[ -]{0,1}){1,2}");
		//std::regex ru_double_rgx("(ru_rgx)[ -](ru_rgx){0,1}");
		if 
			(
				std::regex_match(last_name, en_rgx) || 
				std::regex_match(last_name, ru_rgx)	||
				std::regex_match(last_name, ru_double_rgx)
				)this->last_name = last_name;
		else this->last_name = "Bad name";
		
	}
	void set_first_name(const string& first_name)
	{
		std::regex en_rgx("[A-Z][a-z]{1,15}");
		std::regex ru_rgx("[А-Я][а-я]{1,15}");
		if (std::regex_match(first_name, en_rgx) || std::regex_match(first_name, ru_rgx))this->first_name = first_name;
		else this->last_name = "Bad name";
	}
	void set_age(unsigned int age)
	{
		if (age >= 18 && age <= 150)this->age = age;
		else this->age = 0;
		
	}
	//			Constructors:
	Human(const string& last_name, const string& first_name, unsigned int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	//			Methods:
	virtual void print()
	{
		cout << last_name << " " << first_name << " " << age << " лет." << endl;
	}
};

ostream& operator<<(ostream& os, const Human& obj)
{
	os << obj.get_last_name() << " " << obj.get_first_name() << ", " << obj.get_age() << " лет.";
	return os;
}


class Student :public Human
{
	string specialty;
	string group;
	double rating;
public:
	const string& get_specialty()const
	{
		return specialty;
	}
	const string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	void set_specialty(const string& specialty)
	{
		this->specialty = specialty;
	}
	void set_group(const string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		if (rating >= 0 && rating <= 100)this->rating = rating;
		else this->rating = 0;
		
	}
	//			Constructors:
	Student
	(
		const string& last_name, const string& first_name, unsigned int age,
		const string& specialty, const string& group, double rating
	) :Human(last_name, first_name, age)
	{
		set_specialty(specialty);
		set_group(group);
		set_rating(rating);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//			Methods:
	void print()
	{
		Human::print();
		cout << "Специальность: " << specialty << ", группа: " << group << ", успеваемость: " << rating << endl;
	}
};

ostream& operator<<(ostream& os, const Student& obj)
{
	os << (Human&)obj << " ";
	os << "Специальность: " << obj.get_specialty() 
		<< ", группа:" << obj.get_group() 
		<< ", успеваемость:" << obj.get_rating();
	return os;
}

class Teacher : public Human
{
	string specialty;
	unsigned int experience;
public:
	const string& get_specialty()const
	{
		return specialty;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_specialty(const string& specialty)
	{
		this->specialty = specialty;
	}
	void set_experience(unsigned int experience)
	{
		if(experience >=0 && experience <= 130)this->experience = experience;
		else experience =0;
	}
	//			Constructors:
	Teacher
	(
		const string& last_name, const string& first_name, unsigned int age,
		const string& specialty, unsigned int experience
	) :Human(last_name, first_name, age)
	{
		this->specialty = specialty;
		this->experience = experience;
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//			Methods:
	void print()
	{
		Human::print();
		cout << "Специальность: " << specialty << ", опыт преподавания: " << experience << " лет." << endl;
	}
};

ostream& operator<<(ostream& os, const Teacher& obj)
{
	os << (Human&)obj << " ";
	os << ", специальность:" << obj.get_specialty() 
		<< ", опыт преподавания:" << obj.get_experience()<< " лет.";
	return os;
}

class Graduate :public Student
{
	string subject;
	//Teacher instructor;
public:
	const string& get_subject()const
	{
		return subject;
	}
	void set_subject(const string& subject)
	{
		this->subject = subject;
	}
	//Constructor
	Graduate(
		const string& last_name, const string& first_name, unsigned int age,
		const string& specialty, const string& group, double rating,
		const string& subject
	) :Student(last_name, first_name, age, specialty, group, rating)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	void print()
	{
		Student::print();
		cout << "Тема дипломного проекта: " << subject << endl;
	}
};
ostream& operator<<(ostream& os, const Graduate& obj)
{
	os << (Student&)obj;
	return os << "\nТема диплома: " << obj.get_subject();
}

//#define INHERITANCE_BASICS

void main()
{
	setlocale(LC_ALL, "ru");
#ifdef INHERITANCE_BASICS
	/*Human human("Тупенко", "Василий", 18);
human.print();*/
	Student stud("Тупенко", "Василий", 18, "РПО", "BV_123", 43.4);
	stud.print();
	Teacher Albert("Einstein", "Albert", 150, "Astrophisics", 120);
	Albert.print();

	Albert.get_first_name();
	/*

class DerictedClass:access_modifier BaseClass
{
specification;
}
*/

#endif // INHERITANCE_BASICS

			//POINTERS TO BASE CLASS(указатели на базовый класс)
	Human* group[] =
	{
		new Student("Васильев", "Александр", 23, "РПО", "ПВ_011", 90),
		new Student("Васильева", "Маргарита", 25, "РПО", "ПВ_011", 90),
		new Teacher("Петров-Селедкин", "Олег", 36, "Разработка приложений на C++", 6),
		new Student("Ивлев", "Александр", 25, "РПО", "ПВ_011", 95),
		new Graduate("Рахманин", "Николай", 28, "РПО", "ПВ_011", 98, "Разработка кроссплатформенной обучающей игры"),
		new Teacher("Романов", "Андрей", 30, "HardwarePC", 5),
		new Student("Нусс", "Дмитрий", 22, "РПО", "ПВ_011", 100),
		new Student("Борн", "Евгений", 22, "РПО", "ПВ_011", 99),

	}; //UPCAST

	for (int i = 0; i < sizeof(group) / sizeof(Human*); i++)
	{
		//group[i]->print();
		//cout << *group[i] <<endl;
		//cout << typeid(*group[i]).name() << endl;
		if (typeid(*group[i]) == typeid(Student))cout << *dynamic_cast<Student*>(group[i]) << endl;
		if (typeid(*group[i]) == typeid(Teacher))cout << *dynamic_cast<Teacher*>(group[i]) << endl;
		if (typeid(*group[i]) == typeid(Graduate))cout << *dynamic_cast<Graduate*>(group[i]) << endl;

		cout << delimiter << endl;
	}

	for (int i = 0; i < sizeof(group) / sizeof(Human*); i++)
	{
		delete group[i];
	}

}


