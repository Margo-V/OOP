#include "String.h"


//#define CONSTRUCTORSCHECK
//#define INPUT_CHECK
#define OPERATOR_PLUS_CHECK
//#define HOW_CAN_WE_CALL_CONSTRUCTORS

void main()
{
	setlocale(LC_ALL, "ru");
#ifdef CONSTRUCTORSCHECK
	String str;
	str.print();
	String str1 = "Hello";
	str1 = str1;
	str1.print();
	cout << str1 << endl;
	String str2 = str1;//CopyConstructor
	str2.print();
	String str3;
	str3 = str2;	//CopyAssignement(����������� ������������)
	cout << str3 << endl;
#endif // CONSTRUCTORSCHECK

#ifdef INPUT_CHECK
	String str;
	cout << "������� ������:" << tab; cin >> str;
	cout << str << endl;
#endif // INPUT_CHECK

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	cout << delimeter << endl;
	//String str3;		//Default Constructor
	//str3 = str1 + str2;	//Move Assignment
	//MoveMethods:MoveConstructor, MoveAssignement
	//cout << str3 << endl;
	str1 += str2;
	cout << str1 << endl;
	cout << delimeter << endl;
	String str3 = str1;
	cout << delimeter << endl;

	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef HOW_CAN_WE_CALL_CONSTRUCTORS
	String str1;			//Default constructor
	String str2 = "Hello";	//Single-argument constructor
	String str3 = str2;		//Copy constructor - ������ ��� �� ������� ������
	String str4;
	str4 = str3;			//Copy Assignment(operator=). Copy constructor
							//������� ����������, ��������� ������ str4 ��� ������
	String str5();			//�� Default constructor, ����� ������ �� ��������� ������
							//���������� ������� str5, ������� ������ �� ���������,
							//� ���������� �������� ���� String.
	String str6{};			//����� ����� ������������ �� ���������  
#endif // HOW_CAN_WE_CALL_CONSTRUCTORS


}