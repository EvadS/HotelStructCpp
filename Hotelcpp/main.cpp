#include <iostream>
#include <conio.h>
#include <fstream>

#include <Windows.h>
#include <iomanip>
#include <string>

#define FILENAME "PERSFILE.txt"
#define LISTNAME "LISTFILE.dat"
#define ROWNUM	 20 //максимально число строк в файле 

using namespace std;

/*
при запуске необходимо для консоли указать шрифт Lucida Console 
прав кнопкой мышы на форме -> настройка -> шрифты
*/
#pragma warning(disable : 4996)


///-------------------------------------------------------
/// длина типов данных
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
	/// название отеля 
	///---------------------
	char _name[ColumnLen::namelen];
	///---------------------
	/// адресс отеля 
	///---------------------
	char _adress[ColumnLen::namelen];

	///---------------------
	/// количетсво звезд
	///---------------------
	short  _starNum;

	///---------------------
	/// количетсво комнат
	///---------------------
	short  _placeNum;

	///---------------------
	/// стоимость
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
	/// конструктор с параметрами  
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
	/// установка имени 
	///---------------------
	void set_Name(char *pname)
	{
		int len = strlen(pname);
		///_name = new char[len+1];
		strcpy(_name,pname);
		_name[len] = '\0';
	}

	///---------------------
	/// установка адреса 
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
	/// конструктор копирования
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
	/// переопределения оператора присваивания
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
	/// переопределение операции меньше для сравнения элементов структур
	///--------------------------------------
	bool operator < ( Hotel& dec)
	{
		bool less = false;
		//<0 str1 меньше str2
		int len = strcmp(_name,dec._name);  
		if(id < dec._id  && len<0)	  
		{
			return true;
		}
		return less;
	}
	
	///--------------------------------------
	/// переопределение операции больше для сравнения элементов структур
	///--------------------------------------
    bool operator > (const Hotel& dec)
	{
		bool less = false;
		//<0 str1 меньше str2
		int len = strcmp(_name,dec._name);  
		
		if(id > dec._id && len>0)	  
		{
			return true;
		}

		return less;
	}
	///--------------------------------------
	/// переопределение операции равно для сравнения элементов структур
	///--------------------------------------
	bool operator == (const Hotel& dec)
	{
		bool less = false;
		//<0 str1 меньше str2
		int len = strcmp(_name,dec._name);  
		
		if(id == dec._id && len==0)	  
		{
			return true;
		}

		return less;
	}

	///---------------------
	/// деструктор
	///---------------------
	~Hotel()
	{
	
	}

    static int diskCount();  // Число человек в файле	
	
	///---------------------
	/// вывод данных
	///---------------------
	friend ostream &operator<< (ostream &stream,Hotel o);		
	
	///---------------------
	/// ввод данных
	///---------------------
	friend istream &operator>>(istream &stream,Hotel &o);

};

//----------------------------------------------//


// текущий  записей
//int currLineNum;

int size =0;
bool sizeList = 0;

///список отелей 
Hotel HotelRecord[ROWNUM];

// 
string HotelList[ROWNUM];

bool IsEmpty;

///---------------------
/// количество записей в файле
///---------------------
int Hotel::diskCount()
{
	ifstream infile;
    infile.open(FILENAME, ios::binary);
    infile.seekg(0, ios::end); // перейти на позицию «0 байт
                             // от конца файла»
                             // вычислить количество людей
   return (int)infile.tellg() / sizeof(Hotel);	
}

///------------------------------------------
/// выводит на экран имя и номер телефона
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

	// количество звезд
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
	cout<<"Название гостинницы";	
	cout<<"|";

	cout.width(ColumnLen::namelen);
	cout<<"Адресс";
	cout<<"|";

	// количество звезд
	cout.width(ColumnLen::starlen);
	cout<<"к-во звезд";
	cout<<"|";

	cout.width(ColumnLen::placeNumLen);
	cout<<"к-во мест";
	cout<<"|";
	
	cout.width(ColumnLen::costNumLen);
	cout<<"Стоимость";
	cout<<"|";
	cout<<endl;

	// 6 к - во разделеителей
	int len = 6+ ColumnLen::id+ColumnLen::adresslen+ColumnLen::namelen+ColumnLen::starlen+ColumnLen::placeNumLen+ColumnLen::costNumLen;
	cout.fill ('-');
	cout<<setw(len)<<'-'<<endl;

	cout.fill (' ');
}

///------------------------------------------
/// перегрузка вывода в поток
///------------------------------------------
istream &operator>>(istream &stream,Hotel &o)
{	
	cout<<"Введите id :"<<endl;
	cin.clear();
	//очищает поток от имеющихся в нем символов
	cin.sync();
	cin>>o._id;

	cout<<"Введите название :"<<endl;
	cin.clear();
	//очищает поток от имеющихся в нем символов
	cin.sync();

	char * ltemp = new char[ColumnLen::namelen];
	// максимальное количество символов
 	cin>>setw(ColumnLen::namelen)>>ltemp;
	//cin.getline(dessert, ColumnLen::namelen);
	o.set_Name(ltemp);	
	delete [] ltemp;

	cout<<"Введите адресс "<<endl;
	ltemp = new char[ColumnLen::adresslen];
	cin>>setw(ColumnLen::adresslen)>>ltemp;
	o.set_Address(ltemp);	

	//очищает поток от имеющихся в нем символов
	cin.clear();		
	cin.sync();
	delete [] ltemp;

	cout<<"Введите количество звезд"<<endl;
	cin.clear();
	//очищает поток от имеющихся в нем символов
	cin.sync();
	// бывает всего 5 звезд
	cin>>setw(5)>>o._starNum;
		
	cout<<"Введите количество мест "<<endl;
	cin.clear();
	//очищает поток от имеющихся в нем символов
	cin.sync();
	cin>>o._placeNum;
	
	cout<<"Стоимость "<<endl;
	cin.clear();
	//очищает поток от имеющихся в нем символов
	cin.sync();
	cin>>o._costRoom;	
		
	return stream;
}



///записать на диск 
/// <param = pValue>Элемент который необходимо сохранить в файл </param>
/// <param = fileName > указатель на строку содержащую имя файла</param>
void Write(Hotel pValue,char *pFileName)
{
	fstream file;
	file.open(pFileName, ios::app|ios::out);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	file.write((char*)&pValue,sizeof(Hotel));	
}

/// обновить данные на диск 
/// <param = fileName > указатель на строку содержащую имя файла</param>
void UpdateDate(char *pFileName)
{
	fstream file;
	file.open(pFileName, ios::out |ios::trunc);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }	
}

/// считать все записи из файла  
/// <param = fileName > указатель на строку содержащую имя файла</param>
void ReadInFile(char * pFileName)
{	
	size = 0;

	Hotel lhotel;
	IsEmpty = true;

	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in /*| ios::binary*/);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	int i =0;
	// установить позицию курсора в начало
	file.seekg(0);
	
	file.read((char*)&lhotel,sizeof(struct Hotel));
	
	while(!file.eof())
	{			
		// считать данные о следующем 
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
///запись в файл 
/// <param = fileName > указатель на строку содержащую имя файла</param>
void CreateTestRecord(char *fileName )
{
	//заново создаем файл 	
	ofstream out(fileName);  
    out.close();  
	

	// открываем для записи
	fstream file;
	//out Стирание и запись (файл создается, если его нет) “w”
	//app Дозапись (файл создается, если его нет) “a”
	//in|out Чтение и запись (файл должен существовать) “r+”
	file.open(fileName, ios::app| ios::out | ios::in/* | ios::binary*/);
 
    if(file == NULL)
    {
        cout << "Ошибка создания файла!";
		_getch();
        exit(1);
    }

    file.close(); 

}

///-------------------------------------------
/// отображение меню программы на дисплее
///-------------------------------------------
int  PrintMenu()
{
	int lshoose = 0;

	bool lfisrt = true;

	do
	{	
		//очишает состояние потока
		cin.clear();
		//очищает поток от имеющихся в нем символов
		cin.sync();

		if(!lfisrt)
		{
			cout<<"Некорректное значение - повторите попытку"<<endl;
		}
		
		cout<<"\n Выберите пункт меню :"<<endl;
		cout<<"1. Загрузить все записи."<<endl;
		cout<<"2. Просмотреть все текущие записи"<<endl;
		cout<<"3. Добавление новой записи "<<endl;
		cout<<"4. Удаление записи из базы данных"<<endl;
		cout<<"5. Редактировать запись в базе данных"<<endl;
		cout<<"6. Сортировка записей по числовому полю"<<endl;	
		cout<<"7. Сотировка записей по строковому полю"<<endl;	
		cout<<"8. Структурная сортировка записей"<<endl;	
		cout<<"9. Сохранение результатов в файл"<<endl;	
		cout<<"10. Поиск в базе данных"<<endl;	
		cout<<"11. Формирование перечня"<<endl;	
		cout<<"12. Просмотр перечня"<<endl;	
		cout<<"13. Сортировка перечня"<<endl;	
		cout<<"14. Сохранение перечня в файле"<<endl;	
		cout<<"0. Выход"<<endl;

		cin>>lshoose;

		lfisrt = false;

	}while(lshoose< 0 || lshoose> 14 );

	return lshoose;
}

///вывыести данные на экран
void PrintCurrRow()
{
	cout<<"Hello world!"<<endl;
}


///------------------------------------------
/// удаление записи из файла
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
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	int i =0;
	
	// установить позицию курсора в начало
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
			// считать данные о следующем 
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
			cout << "Ошибка чтения  файла!";
			_getch();
			exit(1);
		}
	// записать оставшееся данные
	for(int j = 0;j<i-1;j++)
	{	
		lfile.write((char*)&ltepArr[j],sizeof(Hotel));	
	}

	ReadInFile(pFileName);

	return lresult;
}


///-------------------------------
/// удаление элементов из массива
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
/// флаг - существует ли флаг 
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
/// флаг - существует запись по id
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
/// поиск записей по id
///-----------------------------------------
bool isExistFilebyId(int pId,char *pfileName)
{
	bool lresult = true;
	Hotel lhotel;

	fstream file;
	file.open(pfileName, ios::app| ios::out | ios::in /*| ios::binary*/);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	int rowNum=0;
	// установить позицию курсора в начало
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
/// получить расположение редактируемого в массиве
///--------------------------------------------------
int getHotelArrayPositionById(int pid,char *pFileName)
{
	Hotel lhotel;

	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in );

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	// установить позицию курсора в начало
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
/// поиск по id и количеству мест
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
				cout<<"Результат поиска :" <<endl;
				isEnableRes = true;
			}

			cout<<HotelRecord[i];
			lresult = true;
		}
	}
	
	if(!lresult)
	{
		cout<<"не удалось найти данные по указанным параметрам "<<endl;
	}
}
///--------------------------------------------------------
/// редактирование записи
///--------------------------------------------------------
void EditHotelData(int pId,char * pFileName,Hotel &photel)
{	
	Hotel ltemp;
	Hotel ltepArr[ROWNUM];

	fstream file;
	file.open(pFileName, ios::app| ios::out | ios::in);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	int i =0;
	// установить позицию курсора в начало
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
			// считать данные о следующем 
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
			cout << "Ошибка чтения  файла!";
			_getch();
			exit(1);
		}
	
	// записать оставшееся данные
	for(int j = 0;j<i;j++)
	{	
		lfile.write((char*)&ltepArr[j],sizeof(Hotel));	
	}

	ReadInFile(pFileName);	
}

/// -------------------------------
/// структурная сортировка  
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
/// редактирование 
///-----------------------------
bool EditHotel(int pid,char *pfileName)
{
	bool lresult = false;



	return lresult;
}

///---------------------------------------
/// просмотр перечня
///----------------------------------------
void PrintList()
{
	cout<<"Текущее содержимое перечня :"<<endl;

	if(sizeList<1)
	{
		cout<<"Перечень пуст"<<endl;
	}
	else
	{
		cout<<"Текущее содержимое перечня"<<endl;
		for(int i = 0; i<size;i++)
		{
			cout<<(i+1)<<".	";
			cout<<HotelList[i]<<endl;
		}
	}
}

bool IsListEmpty =true;
///----------------------------------------
/// создание перечня
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
		cout<<"Перечень пуст "<<endl;
	}

}



///---------------------------------------
/// сортировка перечня
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
		cout<<"Перечень пуст "<<endl;
	}
}
///----------------------------------
/// сохранение перечня в файле
///----------------------------------
void WriteList()
{
	if(sizeList>0)
	{
		fstream file;
		file.open(LISTNAME, ios::out| ios::app);

		if(file == NULL)
		{
			cout << "Ошибка чтения  файла!";
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
		cout<<"Перечень пуст "<<endl;
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
			cout<<"Список пуст"<<endl;
		}
}

int main ()
{
	setlocale(LC_ALL,"Russian");		
	setlocale(LC_CTYPE, ".1251");

	IsEmpty = true;
	sizeList = 0;
       
	 // если файла нету
	 if(!isExist(FILENAME))
	 {
		 //создаем файл с одной записью	
		 CreateTestRecord(FILENAME);	
	 }	

	// выбранный пункт меню
	int lshoose  =0;
	do
	{
		lshoose = PrintMenu();
		cout<<endl;
		//загружаем данные из файла
		if(lshoose==1)
		{
			IsEmpty = true;			
			ReadInFile(FILENAME);
			
			if(size > 0)
			{
				cout<<"Загруженые данные : "<<endl;
				PrintData();
			}
			else
			{
				cout<<"Загруженный список является пустым"<<endl;
			}
		}
		//вывести на экран 
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
				cout<<"Список пуст"<<endl;
			}
		}

		// Добавить запись
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
				cout<<"Список пуст "<<endl;
				continue;
			}
			int lid;
			cout<<"введите id удаляемой записи: ";
			cin>>lid;

			char answ;
			cout<<"Вы действительно хотите удалить запись ? (y/n)" <<endl;
			cin>>answ;

			if(answ !='y')
			{
				continue;
			}
			

			if(isExistById(lid))
			{			
				//если запись существует			
				RemoveRecord(lid);
				cout<<"Запись по указанной id была удалена"<<endl;
			}
			else
			{
				cout<<"Запись по указанной id не найдена"<<endl;
			}
		}
		//Сортировать по году выпуска.
		else if(lshoose==5)
		{
			int lid;
			cout<<"введите id редактируемой записи: ";
			cin>>lid;
			

			//если запись существует
			if(isExistFilebyId(lid,FILENAME))
			{
				cout<<"Текущие данные :"<<endl;
				cout<<HotelRecord[lid];

				Hotel ltemp;
				cin>>ltemp;

				EditHotelData(lid,FILENAME,ltemp);

			}
			else
			{
				cout<<"Не удалось найти запись по id = "<< lid<<endl;
			}
		}
		else if(lshoose==6)
		{
			if(size<1)
			{
				cout<<"Список пуст"<<endl;
				continue;
			}
			//сортировка по id 
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

			cout<<"После выполнения сортировки :" <<endl;
			
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
				cout<<"Список пуст"<<endl;
				continue;
			}

			//сортировка по имени отеля
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

			cout<<"После выполнения сортировки :" <<endl;
			
			PrintHeader();
			for(int i =0 ; i<size;i++)
			{
				cout<<HotelRecord[i];
			}
		}
		// сортировка над элементами структур
		else if(lshoose==8)
		{	
			if(size<1)
			{
				cout<<"Список пуст"<<endl;
				continue;
			}

			//сортировка по имени отеля
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

			cout<<"После выполнения сортировки :" <<endl;
			
			PrintHeader();
			for(int i =0 ; i<size;i++)
			{
				cout<<HotelRecord[i];
			}

		}
	
		//Сохранение результатов в файл
	    else if(lshoose==9)
		{			
			UpdateDate(FILENAME);

			for(int i =0;i<size;i++)
			{				
				Write(HotelRecord[i],FILENAME);			
			}

			cout<<"Данные сохранены"<<endl;

		}
		else if(lshoose==10)
		{
			cout<<"------------------------------------------------"<<endl;
			// поиск 
			int id;
			cout<<"введите ID записи :";
			cin>>id;

			int pleaceNum;
			cout<<"Введите количество мест	:";
			cin>>pleaceNum;

			FindByIdAndRoomNum(id,pleaceNum);
		}
	    // формирование перечня 
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

	cout<<"Введите любой символ для продолжения ....";
	
	_getch();
	return 0;
}