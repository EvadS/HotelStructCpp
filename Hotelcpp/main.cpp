#include <iostream>
#include <conio.h>
#include <fstream>

#include <Windows.h>

#include <iomanip>

#define FILENAME "PERSFILE.txt"
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
// количество записей
int currLineNum;

///список отелей 
Hotel HotelRecord[ROWNUM];


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
	file.open(pFileName,/* ios::app|*/ ios::out| ios::trunc);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	file.write((char*)&pValue,sizeof(Hotel));	
}

/// обновить данные на диск 
/// <param = pValue>Элемент который необходимо сохранить в файл </param>
/// <param = fileName > указатель на строку содержащую имя файла</param>
void UpdateDate(Hotel pValue,char *pFileName)
{
	fstream file;
	file.open(pFileName, ios::app|ios::out/* ios::trunc*/);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	file.write((char*)&pValue,sizeof(Hotel));	
}

/// считать все записи из файла  
/// <param = fileName > указатель на строку содержащую имя файла</param>
void ReadInFile(char * pFileName)
{	
	Hotel lhotel;

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
	//file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));
	file.read((char*)&lhotel,sizeof(struct Hotel));

	currLineNum =0;
	while(!file.eof())
	{			
		// считать данные о следующем 
		HotelRecord[i] = lhotel;
		i++;

		file.read((char*)&lhotel,sizeof(struct Hotel));
		currLineNum++;
	}

    currLineNum--;
}


//--------------------------------------
///запись в файл 
/// <param = fileName > указатель на строку содержащую имя файла</param>
void CreateTestRecord(char *fileName )
{
	//заново создаем файл 	
	ofstream out(fileName);  
    out.close();  
	
	Hotel hotel(0,"Интурист","Ленина 1 ",4,5,300);

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

	 Write(hotel,FILENAME);
}


/// отображение меню программы на дисплее
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
		cout<<"3. Добавлениеновой записи "<<endl;
		cout<<"4. Удаление записи из базы данных"<<endl;
		cout<<"5. Редактировать запись в базе данных"<<endl;
		cout<<"6. Сортировка записей по числовому полю"<<endl;	
		cout<<"7. Сотировка записей по строковому полю"<<endl;	
		cout<<"8. Структурная сортировказаписей"<<endl;	
		cout<<"9. Сохранение результатов в файл"<<endl;	
		cout<<"0. Выход"<<endl;

		cin>>lshoose;

		lfisrt = false;

	}while(lshoose< 0 || lshoose> 9 );

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
bool RemoveRecord(int pId,char * pFileName)
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
	//file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));
	file.read((char*)&ltemp,sizeof(struct Hotel));

	currLineNum =0;
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
bool RemoveRecord(int pId)
{
	bool  lresult = false;
	
	int j= 0;
	for(int i = 0; i< currLineNum;i++)
	{
		if(i != pId)
		{

			HotelRecord[i] = HotelRecord[j];
			j++;
		}
	}
	

	return lresult;
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

	currLineNum =0;
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

	for(int i = 0; i< currLineNum;i++)
	{
		if((i != pid) && (HotelRecord[i].get_PleaceNum() == pleaceNum))
		{
			cout<<HotelRecord[i];
		}
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
	//file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));
	file.read((char*)&ltemp,sizeof(struct Hotel));

	currLineNum =0;
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

///-----------------------------
/// редактирование 
///-----------------------------
bool EditHotel(int pid,char *pfileName)
{
	bool lresult = false;



	return lresult;
}

int main ()
{
	setlocale(LC_ALL,"Russian");		
	setlocale(LC_CTYPE, ".1251");
       
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
			ReadInFile(FILENAME);
		}
		//вывести на экран 
		else if(lshoose==2)
		{	
			if(currLineNum >= 0)
			{
				PrintHeader();
				for(int i =0 ; i<=currLineNum;i++)
				{
					cout<<HotelRecord[i];
				}
			}			
		}

		// Добавить запись
		else if(lshoose==3)
		{	
			Hotel hotel;
			cin>>hotel;
			currLineNum++;
			HotelRecord[currLineNum] = hotel;
			
		}
		else if(lshoose==4)
		{	
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
			
			//если запись существует
			if(isExistFilebyId(lid,FILENAME))
			{
				if(RemoveRecord(lid))
				{
					cout<<"запись по id удалена"<<endl;
				}
			}
			else
			{
				cout<<"Не удалось найти запись по id = "<< lid<<endl;

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
				cout<<HotelRecord[currLineNum];

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
			//сортировка по id 
			Hotel ltest; 

			for(int j = 1;j<=currLineNum;j++)
			{
				for(int i = 0;i<=currLineNum-1;i++)
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
			
			for(int i =0 ; i<=currLineNum;i++)
			{
				cout<<HotelRecord[i];
			}
		}	
		else if(lshoose==7)
		{
			//сортировка по имени отеля
			for (int i=1;  i<currLineNum  ;  i++)
			{            
				for (int j=0;  j<currLineNum-1;  j++)
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
		}

		else if(lshoose==8)
		{
			
		}	
		//Сохранение результатов в файл
	    else if(lshoose==9)
		{
			fstream file;
			file.open(FILENAME, ios::out| ios::trunc);file.close();
			for(int i =0;i<=currLineNum;i++)
			{				
				UpdateDate(HotelRecord[i],FILENAME);
			}
		}


	}while(lshoose!=0);

	cout<<"Введите любой символ для продолжения ....";
	
	_getch();
	return 0;
}