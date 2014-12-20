#include <iostream>
#include <conio.h>
#include <fstream>

#include <Windows.h>
#include <iomanip>
#include <string>

#define FILENAME "PERSFILE.txt"
#define LISTNAME "LISTFILE.dat"
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
	id = 4,
	adresslen = 20,
	namelen  =20,
	starlen = 10,
	costNumLen = 10,
	placeNumLen = 10
};

class Hotel
{
	int _id;

	///---------------------
	/// �������� ����� 
	///---------------------
	char _name[ColumnLen::namelen];
	///---------------------
	/// ������ ����� 
	///---------------------
	char _adress[ColumnLen::namelen];

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
		_name[0] = '\0';		
		
		_adress[0] = '\0';
		
		_starNum = 1;
		
		_placeNum = 1;

		_costRoom = 0;
	}

	///---------------------
	/// ����������� � �����������  
	///---------------------
	Hotel(int pid, char* pname, char *padress,int pstarnum,int pleacenum,int pcost)
	{
		_id = pid;

		int len= 0;
		len = strlen(pname);
		//_name = new char[len+1];
		strcpy(_name,pname);
		_name[len] = '\0';

		len = strlen(padress);		
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
		///_name = new char[len+1];
		strcpy(_name,pname);
		_name[len] = '\0';
	}

	///---------------------
	/// ��������� ������ 
	///---------------------
	void set_Address(char *padress)
	{
		int len = strlen(padress);		
		strcpy(_adress,padress);
		_name[len] = '\0';
	}

	int get_Id()
	{
		return _id;
	}

	char * get_Name()
	{
		return _name;
	}

	int get_PleaceNum()
	{
		return _placeNum;
	}

	int get_StarNum()
	{
		return _starNum;
	}



	///---------------------
	/// ����������� �����������
	///---------------------
	Hotel(const Hotel & object)
	{
		_id =object._id;
		int len = strlen(object._name);
		///_name = new char[len+1];
		strcpy(_name,object._name);
		_name[len] = '\0';

		len = strlen(object._adress);
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
			_id =object._id;

			int len = strlen(object._name);
			//_name = new char[len+1];
			strcpy(_name,object._name);
			_name[len] = '\0';

			len = strlen(object._adress);
			strcpy(_adress,object._adress);
			_adress[len] = '\0';

			_starNum = object._starNum;

			_placeNum=object._placeNum;
			_costRoom=object._costRoom;
		}
	 
		return *this;	
	}
	///--------------------------------------
	/// ��������������� �������� ������ ��� ��������� ��������� ��������
	///--------------------------------------
	bool operator < ( Hotel& dec)
	{
		bool less = false;
		//<0 str1 ������ str2
		int len = strcmp(_name,dec._name);  
		if(id < dec._id  && len<0)	  
		{
			return true;
		}
		return less;
	}
	
	///--------------------------------------
	/// ��������������� �������� ������ ��� ��������� ��������� ��������
	///--------------------------------------
    bool operator > (const Hotel& dec)
	{
		bool less = false;
		//<0 str1 ������ str2
		int len = strcmp(_name,dec._name);  
		
		if(id > dec._id && len>0)	  
		{
			return true;
		}

		return less;
	}
	///--------------------------------------
	/// ��������������� �������� ����� ��� ��������� ��������� ��������
	///--------------------------------------
	bool operator == (const Hotel& dec)
	{
		bool less = false;
		//<0 str1 ������ str2
		int len = strcmp(_name,dec._name);  
		
		if(id == dec._id && len==0)	  
		{
			return true;
		}

		return less;
	}

	///---------------------
	/// ����������
	///---------------------
	~Hotel()
	{
	
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

//----------------------------------------------//


// �������  �������
//int currLineNum;

int size =0;
bool sizeList = 0;

///������ ������ 
Hotel HotelRecord[ROWNUM];

// 
string HotelList[ROWNUM];

bool IsEmpty;

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
	cout.width(ColumnLen::id);
	cout<<o._id;
	cout<<"|";

	cout.width(ColumnLen::adresslen);
	cout<<o._name;
	cout<<"|";

	cout.width(ColumnLen::namelen);
	cout<<o._adress;
	cout<<"|";

	// ���������� �����
	cout.width(ColumnLen::starlen);	
	cout<<o._starNum;	
	cout<<"|";

	cout.width(ColumnLen::placeNumLen);
	cout<<o._placeNum;
	cout<<"|";
	
	cout.width(ColumnLen::costNumLen);
	cout<<o._costRoom;
	cout<<"|";

	cout<<endl;
	return stream;
}


void PrintHeader()
{
	cout.width(ColumnLen::id);
	cout<<"Id";
	cout<<"|";

	cout.width(ColumnLen::adresslen);
	cout<<"�������� ����������";	
	cout<<"|";

	cout.width(ColumnLen::namelen);
	cout<<"������";
	cout<<"|";

	// ���������� �����
	cout.width(ColumnLen::starlen);
	cout<<"�-�� �����";
	cout<<"|";

	cout.width(ColumnLen::placeNumLen);
	cout<<"�-�� ����";
	cout<<"|";
	
	cout.width(ColumnLen::costNumLen);
	cout<<"���������";
	cout<<"|";
	cout<<endl;

	// 6 � - �� �������������
	int len = 6+ ColumnLen::id+ColumnLen::adresslen+ColumnLen::namelen+ColumnLen::starlen+ColumnLen::placeNumLen+ColumnLen::costNumLen;
	cout.fill ('-');
	cout<<setw(len)<<'-'<<endl;

	cout.fill (' ');
}

///------------------------------------------
/// ���������� ������ � �����
///------------------------------------------
istream &operator>>(istream &stream,Hotel &o)
{	
	cout<<"������� id :"<<endl;
	cin.clear();
	//������� ����� �� ��������� � ��� ��������
	cin.sync();
	cin>>o._id;

	cout<<"������� �������� :"<<endl;
	cin.clear();
	//������� ����� �� ��������� � ��� ��������
	cin.sync();

	char * ltemp = new char[ColumnLen::namelen];
	// ������������ ���������� ��������
 	cin>>setw(ColumnLen::namelen)>>ltemp;
	//cin.getline(dessert, ColumnLen::namelen);
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
	file.open(pFileName, ios::app|ios::out);

	if(file == NULL)
    {
        cout << "������ ������  �����!";
		_getch();
        exit(1);
    }

	file.write((char*)&pValue,sizeof(Hotel));	
}

/// �������� ������ �� ���� 
/// <param = fileName > ��������� �� ������ ���������� ��� �����</param>
void UpdateDate(char *pFileName)
{
	fstream file;
	file.open(pFileName, ios::out |ios::trunc);

	if(file == NULL)
    {
        cout << "������ ������  �����!";
		_getch();
        exit(1);
    }	
}

/// ������� ��� ������ �� �����  
/// <param = fileName > ��������� �� ������ ���������� ��� �����</param>
void ReadInFile(char * pFileName)
{	
	size = 0;

	Hotel lhotel;
	IsEmpty = true;

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
	
	file.read((char*)&lhotel,sizeof(struct Hotel));
	
	while(!file.eof())
	{			
		// ������� ������ � ��������� 
		HotelRecord[i] = lhotel;
		i++;
		IsEmpty =false;
		file.read((char*)&lhotel,sizeof(struct Hotel));
		size++;
	}

	IsEmpty = size == 0;
	
    size;
}


//--------------------------------------
///������ � ���� 
/// <param = fileName > ��������� �� ������ ���������� ��� �����</param>
void CreateTestRecord(char *fileName )
{
	//������ ������� ���� 	
	ofstream out(fileName);  
    out.close();  
	

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

}

///-------------------------------------------
/// ����������� ���� ��������� �� �������
///-------------------------------------------
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
		cout<<"3. ���������� ����� ������ "<<endl;
		cout<<"4. �������� ������ �� ���� ������"<<endl;
		cout<<"5. ������������� ������ � ���� ������"<<endl;
		cout<<"6. ���������� ������� �� ��������� ����"<<endl;	
		cout<<"7. ��������� ������� �� ���������� ����"<<endl;	
		cout<<"8. ����������� ���������� �������"<<endl;	
		cout<<"9. ���������� ����������� � ����"<<endl;	
		cout<<"10. ����� � ���� ������"<<endl;	
		cout<<"11. ������������ �������"<<endl;	
		cout<<"12. �������� �������"<<endl;	
		cout<<"13. ���������� �������"<<endl;	
		cout<<"14. ���������� ������� � �����"<<endl;	
		cout<<"0. �����"<<endl;

		cin>>lshoose;

		lfisrt = false;

	}while(lshoose< 0 || lshoose> 14 );

	return lshoose;
}

///�������� ������ �� �����
void PrintCurrRow()
{
	cout<<"Hello world!"<<endl;
}


///------------------------------------------
/// �������� ������ �� �����
///------------------------------------------
bool RemoveRecordFromFile(int pId,char * pFileName)
{
	bool  lresult = false;
	Hotel ltemp;
	Hotel ltepArr[ROWNUM];

	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in);

	if(file == NULL)
    {
        cout << "������ ������  �����!";
		_getch();
        exit(1);
    }

	int i =0;
	
	// ���������� ������� ������� � ������
	file.seekg(0);
	file.read((char*)&ltemp,sizeof(struct Hotel));
	
	while(!file.eof())
	{	
		if(ltemp.get_Id() ==pId  )
		{			
			lresult = true;
		}
		else
		{
			// ������� ������ � ��������� 
			ltepArr[i] = ltemp;
			i++;
		}

		file.read((char*)&ltemp,sizeof(struct Hotel));		
	}   	

	file.close();

	fstream lfile;
	lfile.open(pFileName, ios::trunc| ios::out/* | ios::in /*| ios::binary*/);
	if(lfile == NULL)
		{
			cout << "������ ������  �����!";
			_getch();
			exit(1);
		}
	// �������� ���������� ������
	for(int j = 0;j<i-1;j++)
	{	
		lfile.write((char*)&ltepArr[j],sizeof(Hotel));	
	}

	ReadInFile(pFileName);

	return lresult;
}


///-------------------------------
/// �������� ��������� �� �������
///-------------------------------
void RemoveRecord(int pId)
{	
	static int j= 0;

	Hotel TempArr[20];

	for(int i = 0; i< size;i++)
	{
		if(HotelRecord[i].get_Id() != pId)
		{

			TempArr[j] = HotelRecord[i];
			j++;
		}
	}	
	cout<<j<<endl;
	for(int i = 0;i<j;i++)
	{
		HotelRecord[i] = TempArr[i];
	}	

	size = j;
}

///-----------------------------------
/// ���� - ���������� �� ���� 
///-----------------------------------
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

///-----------------------------------
/// ���� - ���������� ������ �� id
///-----------------------------------
bool isExistById(int pId)
{
   for(int i = 0; i< size;i++)
	{
		if(HotelRecord[i].get_Id() == pId)
		{
			return true;			
		}
	}

	return false;
}

///-----------------------------------------
/// ����� ������� �� id
///-----------------------------------------
bool isExistFilebyId(int pId,char *pfileName)
{
	bool lresult = true;
	Hotel lhotel;

	fstream file;
	file.open(pfileName, ios::app| ios::out | ios::in /*| ios::binary*/);

	if(file == NULL)
    {
        cout << "������ ������  �����!";
		_getch();
        exit(1);
    }

	int rowNum=0;
	// ���������� ������� ������� � ������
	file.seekg(0);
	file.read((char*)&lhotel,sizeof(struct Hotel));

	while(!file.eof())
	{	
		if(pId==lhotel.get_Id())
		{
			rowNum++;
		}
		file.read((char*)&lhotel,sizeof(struct Hotel));	
	}

	return rowNum>0;
}

///--------------------------------------------------
/// �������� ������������ �������������� � �������
///--------------------------------------------------
int getHotelArrayPositionById(int pid,char *pFileName)
{
	Hotel lhotel;

	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in );

	if(file == NULL)
    {
        cout << "������ ������  �����!";
		_getch();
        exit(1);
    }

	// ���������� ������� ������� � ������
	file.seekg(0);
	//file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));
	file.read((char*)&lhotel,sizeof(struct Hotel));

    int lpositionNum;
	while(!file.eof())
	{	

		if(lhotel.get_Id() == pid )
		{
			break;
		}		

		file.read((char*)&lhotel,sizeof(struct Hotel));
		lpositionNum++;
	}

    lpositionNum--;

	return lpositionNum;
}


///----------------------------------------------
/// ����� �� id � ���������� ����
///----------------------------------------------
void FindByIdAndRoomNum(int pid,int pleaceNum)
{
	bool  lresult = false;
	bool  isEnableRes = false;

	for(int i = 0; i< size;i++)
	{
		if((HotelRecord[i].get_Id() == pid) && (HotelRecord[i].get_PleaceNum() == pleaceNum))
		{
			if(!isEnableRes)
			{
				cout<<"��������� ������ :" <<endl;
				isEnableRes = true;
			}

			cout<<HotelRecord[i];
			lresult = true;
		}
	}
	
	if(!lresult)
	{
		cout<<"�� ������� ����� ������ �� ��������� ���������� "<<endl;
	}
}
///--------------------------------------------------------
/// �������������� ������
///--------------------------------------------------------
void EditHotelData(int pId,char * pFileName,Hotel &photel)
{	
	Hotel ltemp;
	Hotel ltepArr[ROWNUM];

	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in);

	if(file == NULL)
    {
        cout << "������ ������  �����!";
		_getch();
        exit(1);
    }

	int i =0;
	// ���������� ������� ������� � ������
	file.seekg(0);
	file.read((char*)&ltemp,sizeof(struct Hotel));

	
	while(!file.eof())
	{	
		if(ltemp.get_Id() ==pId  )
		{			
			ltepArr[i] = photel;
		}
		else
		{
			// ������� ������ � ��������� 
			ltepArr[i] = ltemp;			
		}

		i++;
		file.read((char*)&ltemp,sizeof(struct Hotel));		
	}   	

	file.close();

	fstream lfile;
	lfile.open(pFileName, ios::trunc| ios::out/* | ios::in /*| ios::binary*/);
	if(lfile == NULL)
		{
			cout << "������ ������  �����!";
			_getch();
			exit(1);
		}
	
	// �������� ���������� ������
	for(int j = 0;j<i;j++)
	{	
		lfile.write((char*)&ltepArr[j],sizeof(Hotel));	
	}

	ReadInFile(pFileName);	
}

/// -------------------------------
/// ����������� ����������  
///--------------------------------
void SortByStruct()
{
	Hotel temp;	

	for(int j =1; j < size;j++)
	{
		for(int i = 0; i<size;i++)
		{
			if(strcmp(HotelRecord[i].get_Name(),HotelRecord[i].get_Name())>0   
				&& HotelRecord[i].get_StarNum() >HotelRecord[i+1].get_StarNum())
			{
				temp= HotelRecord[i];
				HotelRecord[i] = HotelRecord[i+1];
				HotelRecord[i+1] = temp;
			}
		}
	}

}

///-----------------------------
/// �������������� 
///-----------------------------
bool EditHotel(int pid,char *pfileName)
{
	bool lresult = false;



	return lresult;
}

///---------------------------------------
/// �������� �������
///----------------------------------------
void PrintList()
{
	cout<<"������� ���������� ������� :"<<endl;

	if(sizeList<1)
	{
		cout<<"�������� ����"<<endl;
	}
	else
	{
		cout<<"������� ���������� �������"<<endl;
		for(int i = 0; i<size;i++)
		{
			cout<<(i+1)<<".	";
			cout<<HotelList[i]<<endl;
		}
	}
}

bool IsListEmpty =true;
///----------------------------------------
/// �������� �������
///----------------------------------------
void CreateList()
{
	if(size > 0)
	{
		IsListEmpty = false;
		for(int i = 0; i<size;i++)
		{
			HotelList[i] = HotelRecord[i].get_Name();
		}
		sizeList = size;
		PrintList();
	}
	else 
	{
		cout<<"�������� ���� "<<endl;
	}

}



///---------------------------------------
/// ���������� �������
///----------------------------------------
void SortList()
{	
	string temp;
	if(sizeList>0)
	{
		for(int j=1;j<=size-1;j++)
		{
			for(int i = 0; i<=size;i++)
			{
				if((HotelList[i]>HotelList[i+1])) ;
				{
					temp = HotelList[i];
					HotelList[i] = HotelList[i+1];
					HotelList[i] = temp; 			
				}
			}
		}

		PrintList();
	}
	else 
	{
		cout<<"�������� ���� "<<endl;
	}
}
///----------------------------------
/// ���������� ������� � �����
///----------------------------------
void WriteList()
{
	if(sizeList>0)
	{
		fstream file;
		file.open(LISTNAME, ios::out| ios::app);

		if(file == NULL)
		{
			cout << "������ ������  �����!";
			_getch();
			exit(1);
		}

		for(int i = 0; i<=size;i++)
		{
			file.write((char*)&HotelList[i] ,sizeof(HotelList[i]));
		}
	}
	else 
	{
		cout<<"�������� ���� "<<endl;
	}
}


void PrintData()
{
	if(size>0)
		{
			PrintHeader();
			for(int i =0 ; i<size;i++)
			{
				cout<<HotelRecord[i];
			}
		}
		else 
		{
			cout<<"������ ����"<<endl;
		}
}

int main ()
{
	setlocale(LC_ALL,"Russian");		
	setlocale(LC_CTYPE, ".1251");

	IsEmpty = true;
	sizeList = 0;
       
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
			IsEmpty = true;			
			ReadInFile(FILENAME);
			
			if(size > 0)
			{
				cout<<"���������� ������ : "<<endl;
				PrintData();
			}
			else
			{
				cout<<"����������� ������ �������� ������"<<endl;
			}
		}
		//������� �� ����� 
		else if(lshoose==2)
		{	
			if(size>0)
			{
				PrintHeader();
				for(int i =0 ; i<size;i++)
				{
					cout<<HotelRecord[i];
				}
			}
			else 
			{
				cout<<"������ ����"<<endl;
			}
		}

		// �������� ������
		else if(lshoose==3)
		{	
			Hotel hotel;
			cin>>hotel;	
			size++;
			HotelRecord[size-1] = hotel;
				
			IsEmpty = false;			
		}
		else if(lshoose==4)
		{	
			if(size<1)
			{
				cout<<"������ ���� "<<endl;
				continue;
			}
			int lid;
			cout<<"������� id ��������� ������: ";
			cin>>lid;

			char answ;
			cout<<"�� ������������� ������ ������� ������ ? (y/n)" <<endl;
			cin>>answ;

			if(answ !='y')
			{
				continue;
			}
			

			if(isExistById(lid))
			{			
				//���� ������ ����������			
				RemoveRecord(lid);
				cout<<"������ �� ��������� id ���� �������"<<endl;
			}
			else
			{
				cout<<"������ �� ��������� id �� �������"<<endl;
			}
		}
		//����������� �� ���� �������.
		else if(lshoose==5)
		{
			int lid;
			cout<<"������� id ������������� ������: ";
			cin>>lid;
			

			//���� ������ ����������
			if(isExistFilebyId(lid,FILENAME))
			{
				cout<<"������� ������ :"<<endl;
				cout<<HotelRecord[lid];

				Hotel ltemp;
				cin>>ltemp;

				EditHotelData(lid,FILENAME,ltemp);

			}
			else
			{
				cout<<"�� ������� ����� ������ �� id = "<< lid<<endl;
			}
		}
		else if(lshoose==6)
		{
			if(size<1)
			{
				cout<<"������ ����"<<endl;
				continue;
			}
			//���������� �� id 
			Hotel ltest; 

			for(int j = 1;j<size;j++)
			{
				for(int i = 0;i<size-1;i++)
				{
					if(HotelRecord[i].get_Id() > HotelRecord[i+1].get_Id())
					{
						ltest= HotelRecord[i];
						HotelRecord[i] = HotelRecord[i+1];
						HotelRecord[i+1] = ltest;
					}
				}
			}

			cout<<"����� ���������� ���������� :" <<endl;
			
			PrintHeader();
			
			for(int i =0 ; i<size;i++)
			{
				cout<<HotelRecord[i];
			}
		}	
		else if(lshoose==7)
		{
			if(size<1)
			{
				cout<<"������ ����"<<endl;
				continue;
			}

			//���������� �� ����� �����
			for (int i=1;  i<size  ;  i++)
			{            
				for (int j=0;  j<size-1;  j++)
				{ 
					Hotel ltest; 

					int len = strcmp(HotelRecord[j].get_Name(),HotelRecord[j+1].get_Name());    
					if(len>0 )
					{     
						ltest = HotelRecord[j];           
						HotelRecord[j] = HotelRecord[j+1];
						HotelRecord[j+1] = ltest;
	
					}			
				}   
			}	

			cout<<"����� ���������� ���������� :" <<endl;
			
			PrintHeader();
			for(int i =0 ; i<size;i++)
			{
				cout<<HotelRecord[i];
			}
		}
		// ���������� ��� ���������� ��������
		else if(lshoose==8)
		{	
			if(size<1)
			{
				cout<<"������ ����"<<endl;
				continue;
			}

			//���������� �� ����� �����
			for (int i=1;  i<size  ;  i++)
			{            
				for (int j=0;  j<size-1;  j++)
				{ 
					Hotel ltest; 
					   
					if(HotelRecord[j] >HotelRecord[j+1] )
					{     
						ltest = HotelRecord[j];           
						HotelRecord[j] = HotelRecord[j+1];
						HotelRecord[j+1] = ltest;	
					}			
				}   
			}	

			cout<<"����� ���������� ���������� :" <<endl;
			
			PrintHeader();
			for(int i =0 ; i<size;i++)
			{
				cout<<HotelRecord[i];
			}

		}
	
		//���������� ����������� � ����
	    else if(lshoose==9)
		{			
			UpdateDate(FILENAME);

			for(int i =0;i<size;i++)
			{				
				Write(HotelRecord[i],FILENAME);			
			}

			cout<<"������ ���������"<<endl;

		}
		else if(lshoose==10)
		{
			cout<<"------------------------------------------------"<<endl;
			// ����� 
			int id;
			cout<<"������� ID ������ :";
			cin>>id;

			int pleaceNum;
			cout<<"������� ���������� ����	:";
			cin>>pleaceNum;

			FindByIdAndRoomNum(id,pleaceNum);
		}
	    // ������������ ������� 
		else if(lshoose==11)
		{
			CreateList();
		}
		else if(lshoose ==12)
		{
			PrintList();
		}
		else if(lshoose ==13)
		{
			SortList();
		}
		else if(lshoose ==14)
		{
			WriteList();
		}

	}while(lshoose!=0);

	cout<<"������� ����� ������ ��� ����������� ....";
	
	_getch();
	return 0;
}