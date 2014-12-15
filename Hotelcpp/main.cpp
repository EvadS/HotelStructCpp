#include <iostream>
#include <conio.h>
#include <fstream>

#include <iomanip>

#define FILENAME "PERSFILE.txt"
#define ROWNUM	 20 //����������� ����� ����� � ����� 

using namespace std;

/*
��� ������� ���������� ��� ������� ������� ����� Lucida Console 
���� ������� ���� �� ����� -> ��������� -> ������
*/
#pragma warning(disable : 4996)

///-------------------------------------------------------
/// ����� ����� ������
///-------------------------------------------------------
enum ColumnLen
{
	adresslen = 20,
	namelen  =20,
	starlen = 5,
	costNumLen = 10,
	placeNumLen = 5
};

class Hotel
{
	///---------------------
	/// �������� ����� 
	///---------------------
	char *_name;
	///---------------------
	/// ������ ����� 
	///---------------------
	char *_adress;

	///---------------------
	/// ���������� �����
	///---------------------
	short  _starNum;

	///---------------------
	/// ���������� ������
	///---------------------
	short  _placeNum;

	///---------------------
	/// ���������
	///---------------------
	double _costRoom;

public :

	Hotel()
	{		
		_name = new char[1];
		_name[0] = '\0';		
	
		_adress = new char[1];
		_adress[0] = '\0';
		
		_starNum = 1;
		
		_placeNum = 1;

		_costRoom = 0;
	}

	///---------------------
	/// ����������� � �����������  
	///---------------------
	Hotel(char* pname, char *padress,int pstarnum,int pleacenum,int pcost)
	{
		int len= 0;

		len = strlen(pname);
		_name = new char[len+1];
		strcpy(_name,pname);
		_name[len] = '\0';

		len = strlen(padress);
		_adress = new char[len+1];
		strcpy(_adress,padress);
		_adress[len] = '\0';

		_starNum = pstarnum;

		_placeNum=pleacenum;
		_costRoom=pcost;
	}

	///---------------------
	/// ��������� ����� 
	///---------------------
	void set_Name(char *pname)
	{
		int len = strlen(pname);
		_name = new char[len+1];
		strcpy(_name,pname);
		_name[len] = '\0';
	}

	///---------------------
	/// ��������� ������ 
	///---------------------
	void set_Address(char *padress)
	{
		int len = strlen(padress);
		_adress = new char[len+1];
		strcpy(_adress,padress);
		_name[len] = '\0';
	}

	///---------------------
	/// ����������� �����������
	///---------------------
	Hotel(const Hotel & object)
	{
		
		int len = strlen(object._name);
		_name = new char[len+1];
		strcpy(_name,object._name);
		_name[len] = '\0';

		len = strlen(object._adress);
		_adress = new char[len+1];
		strcpy(_adress,object._adress);
		_adress[len] = '\0';

		_starNum = object._starNum;

		_placeNum=object._placeNum;
		_costRoom=object._costRoom;
	}

	///---------------------
	/// ��������������� ��������� ������������
	///---------------------
	Hotel& operator=(const Hotel& object)
    {   
		if (this != &object)
		{
       
			int len = strlen(object._name);
			_name = new char[len+1];
			strcpy(_name,object._name);
			_name[len] = '\0';

			len = strlen(object._adress);
			_adress = new char[len+1];
			strcpy(_adress,object._adress);
			_adress[len] = '\0';

			_starNum = object._starNum;

			_placeNum=object._placeNum;
			_costRoom=object._costRoom;
		}
	 
		return *this;	
	}

	///---------------------
	/// ����������
	///---------------------
	~Hotel()
	{
		// ���� ������ ���� ��������
		if(_name != NULL)
		{
			// ����������
			delete []_name;
		}

		if(_adress != NULL)
		{
			delete []_adress;
		}
	}

    static int diskCount();  // ����� ������� � �����	
	
	///---------------------
	/// ����� ������
	///---------------------
	friend ostream &operator<< (ostream &stream,Hotel o);		
	
	///---------------------
	/// ���� ������
	///---------------------
	friend istream &operator>>(istream &stream,Hotel &o);

};
// ���������� �������
int currLineNum;

///������ ������ 
Hotel HotelRecord[ROWNUM];


///---------------------
/// ���������� ������� � �����
///---------------------
int Hotel::diskCount()
{
	ifstream infile;
    infile.open(FILENAME, ios::binary);
    infile.seekg(0, ios::end); // ������� �� ������� �0 ����
                             // �� ����� �����
                             // ��������� ���������� �����
   return (int)infile.tellg() / sizeof(Hotel);	
}

///------------------------------------------
/// ������� �� ����� ��� � ����� ��������
///------------------------------------------
ostream &operator<< (ostream &stream,Hotel o)
{
	cout.width(ColumnLen::adresslen);
	cout<<o._name;
	cout<<"|";

	cout.width(ColumnLen::namelen);
	cout<<o._adress;
	cout<<"|";

	// ���������� �����
	cout.width(ColumnLen::starlen);
	for(int i =0; i <o._starNum;i++)
	{
		cout<<"*";
	}

	cout.width(ColumnLen::placeNumLen);
	cout<<o._placeNum;
	cout<<"|";
	
	cout.width(ColumnLen::costNumLen);
	cout<<o._costRoom;
	cout<<"|";

	return stream;
}


///------------------------------------------
/// ���������� ������ � �����
///------------------------------------------
istream &operator>>(istream &stream,Hotel &o)
{
	//Hotel o;
	cout<<"������� �������� :"<<endl;
		cin.clear();
		//������� ����� �� ��������� � ��� ��������
		cin.sync();

		char * ltemp = new char[ColumnLen::namelen];
		// ������������ ���������� ��������
	    cin>>setw(ColumnLen::namelen)>>ltemp;
		o.set_Name(ltemp);	
		delete [] ltemp;
		
		cout<<"������� ������ "<<endl;
		ltemp = new char[ColumnLen::adresslen];
	    cin>>setw(ColumnLen::adresslen)>>ltemp;
		o.set_Address(ltemp);	

		//������� ����� �� ��������� � ��� ��������
		cin.clear();		
		cin.sync();
		delete [] ltemp;

		cout<<"������� ���������� �����"<<endl;
		cin.clear();
		//������� ����� �� ��������� � ��� ��������
		cin.sync();
		// ������ ����� 5 �����
		cin>>setw(5)>>o._starNum;
		
		cout<<"������� ���������� ���� "<<endl;
		cin.clear();
		//������� ����� �� ��������� � ��� ��������
		cin.sync();
		cin>>o._placeNum;
	
		cout<<"��������� "<<endl;
		cin.clear();
		//������� ����� �� ��������� � ��� ��������
		cin.sync();
		cin>>o._costRoom;	
		
	return stream;
}



///�������� �� ���� 
/// <param = pValue>������� ������� ���������� ��������� � ���� </param>
/// <param = fileName > ��������� �� ������ ���������� ��� �����</param>
void Write(Hotel pValue,char *pFileName)
{
	fstream file;
	file.open(pFileName, ios::app| ios::out/* | ios::in /*| ios::binary*/);

	if(file == NULL)
    {
        cout << "������ ������  �����!";
		_getch();
        exit(1);
    }

	file.write((char*)&pValue,sizeof(pValue));
	//fwrite(&m, sizeof(struct Medicazos), 1, f);
}


/// ������� ��� ������ �� �����  
/// <param = fileName > ��������� �� ������ ���������� ��� �����</param>
void ReadInFile(char * pFileName)
{	
	Hotel lplane;

	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in /*| ios::binary*/);

	if(file == NULL)
    {
        cout << "������ ������  �����!";
		_getch();
        exit(1);
    }

	int i =0;
	// ���������� ������� ������� � ������
	file.seekg(0);
	//file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));
	file.read((char*)&lplane,sizeof(struct Hotel));

	currLineNum =0;
	while(!file.eof())
	{			
		// ������� ������ � ��������� 
		HotelRecord[i] = lplane;
		i++;
		currLineNum++;

		file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));
					
		cout<<"\n";
	}
}


//--------------------------------------
///������ � ���� 
/// <param = fileName > ��������� �� ������ ���������� ��� �����</param>
void CreateTestRecord(char *fileName )
{
	//������ ������� ���� 	
	ofstream out(fileName);  
    out.close();  
	
	Hotel hotel("��������","������ 1 ",4,5,300);

	// ��������� ��� ������
	fstream file;
	//out �������� � ������ (���� ���������, ���� ��� ���) �w�
	//app �������� (���� ���������, ���� ��� ���) �a�
	//in|out ������ � ������ (���� ������ ������������) �r+�
	file.open(fileName, ios::app| ios::out | ios::in/* | ios::binary*/);
 
    if(file == NULL)
    {
        cout << "������ �������� �����!";
		_getch();
        exit(1);
    }

    file.close(); 

	 Write(hotel,FILENAME);
}


/// ����������� ���� ��������� �� �������
int  PrintMenu()
{
	int lshoose = 0;

	bool lfisrt = true;

	do
	{	
		//������� ��������� ������
		cin.clear();
		//������� ����� �� ��������� � ��� ��������
		cin.sync();

		if(!lfisrt)
		{
			cout<<"������������ �������� - ��������� �������"<<endl;
		}
		
		cout<<"\n �������� ����� ���� :"<<endl;
		cout<<"1. ��������� ��� ������."<<endl;
		cout<<"2. ����������� ��� ������� ������"<<endl;
		cout<<"3. �������� ������ "<<endl;
		cout<<"4. ��������� �� �����"<<endl;
		cout<<"5. ����������� �� ���� �������."<<endl;
		cout<<"6. ����� ������ �� ���� �������."<<endl;	
		cout<<"9. ���������� ����������� � ����"<<endl;	
		cout<<"0. �����"<<endl;

		cin>>lshoose;

		lfisrt = false;

	}while(lshoose< 0 || lshoose> 6 );

	return lshoose;
}

///�������� ������ �� �����
void PrintCurrRow()
{
	cout<<"Hello world!"<<endl;
}



/// ���� - ���������� �� ���� 
bool isExist(char * pFileName)
{
   fstream file;

   file.open(pFileName);

	if(file == NULL)
    {
        return false;
    }

	return true;
}

int main ()
{
	setlocale(LC_ALL,"Russian");
	setlocale(LC_CTYPE,"Russian");
	//setlocale(LC_ALL, "rus");

	
	 // ���� ����� ����
	 if(!isExist(FILENAME))
	 {
		 //������� ���� � ����� �������	
		 CreateTestRecord(FILENAME);	
	 }	


	// ��������� ����� ����
	int lshoose  =0;
	do
	{
		lshoose = PrintMenu();
		cout<<endl;
		//��������� ������ �� �����
		if(lshoose==1)
		{
			ReadInFile(FILENAME);
		}
		//������� �� ����� 
		else if(lshoose==2)
		{
			PrintCurrRow();
		}

		// �������� ������
		else if(lshoose==3)
		{	
			Hotel hotel;
			cin>>HotelRecord[currLineNum];
			
			currLineNum++;
		}
		//��������� �� �����
		else if(lshoose==4)
		{
			
		}
		//����������� �� ���� �������.
		else if(lshoose==5)
		{
			
		}
		else if(lshoose==6)
		{
			
		}	
		//���������� ����������� � ����
	    else if(lshoose==9)
		{
			for(int i =0;i<9;i++)
			{				
				Write(HotelRecord[i],FILENAME);
			}
		}


	}while(lshoose!=0);
	
	int a(10);

	cout<<"������� ����� ������ ��� ����������� ....";
	
	_getch();
	return 0;
}