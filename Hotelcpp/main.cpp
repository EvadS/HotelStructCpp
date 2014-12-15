#include <iostream>
#include <conio.h>
#include <fstream>

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
	adresslen = 20,
	namelen  =20,
	starlen = 5,
	costNumLen = 10,
	placeNumLen = 5
};

class Hotel
{
	///---------------------
	/// название отеля 
	///---------------------
	char *_name;
	///---------------------
	/// адресс отеля 
	///---------------------
	char *_adress;

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
		_name = new char[1];
		_name[0] = '\0';		
	
		_adress = new char[1];
		_adress[0] = '\0';
		
		_starNum = 1;
		
		_placeNum = 1;

		_costRoom = 0;
	}

	///---------------------
	/// конструктор с параметрами  
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
	/// установка имени 
	///---------------------
	void set_Name(char *pname)
	{
		int len = strlen(pname);
		_name = new char[len+1];
		strcpy(_name,pname);
		_name[len] = '\0';
	}

	///---------------------
	/// установка адреса 
	///---------------------
	void set_Address(char *padress)
	{
		int len = strlen(padress);
		_adress = new char[len+1];
		strcpy(_adress,padress);
		_name[len] = '\0';
	}

	///---------------------
	/// конструктор копирования
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
	/// переопределения оператора присваивания
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
	/// деструктор
	///---------------------
	~Hotel()
	{
		// если память была выделена
		if(_name != NULL)
		{
			// освободить
			delete []_name;
		}

		if(_adress != NULL)
		{
			delete []_adress;
		}
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
	cout.width(ColumnLen::adresslen);
	cout<<o._name;
	cout<<"|";

	cout.width(ColumnLen::namelen);
	cout<<o._adress;
	cout<<"|";

	// количество звезд
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
/// перегрузка вывода в поток
///------------------------------------------
istream &operator>>(istream &stream,Hotel &o)
{
	//Hotel o;
	cout<<"Введите название :"<<endl;
		cin.clear();
		//очищает поток от имеющихся в нем символов
		cin.sync();

		char * ltemp = new char[ColumnLen::namelen];
		// максимальное количество символов
	    cin>>setw(ColumnLen::namelen)>>ltemp;
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
	file.open(pFileName, ios::app| ios::out/* | ios::in /*| ios::binary*/);

	if(file == NULL)
    {
        cout << "Ошибка чтения  файла!";
		_getch();
        exit(1);
    }

	file.write((char*)&pValue,sizeof(pValue));
	//fwrite(&m, sizeof(struct Medicazos), 1, f);
}


/// считать все записи из файла  
/// <param = fileName > указатель на строку содержащую имя файла</param>
void ReadInFile(char * pFileName)
{	
	Hotel lplane;

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
	file.read((char*)&lplane,sizeof(struct Hotel));

	currLineNum =0;
	while(!file.eof())
	{			
		// считать данные о следующем 
		HotelRecord[i] = lplane;
		i++;
		currLineNum++;

		file.read(reinterpret_cast<char*>(&lplane),sizeof(lplane));
					
		cout<<"\n";
	}
}


//--------------------------------------
///запись в файл 
/// <param = fileName > указатель на строку содержащую имя файла</param>
void CreateTestRecord(char *fileName )
{
	//заново создаем файл 	
	ofstream out(fileName);  
    out.close();  
	
	Hotel hotel("Интурист","Ленина 1 ",4,5,300);

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
		cout<<"3. Добавить запись "<<endl;
		cout<<"4. Загрузить из файла"<<endl;
		cout<<"5. Сортировать по году выпуска."<<endl;
		cout<<"6. Поиск данных по году выпуска."<<endl;	
		cout<<"9. Сохранение результатов в файл"<<endl;	
		cout<<"0. Выход"<<endl;

		cin>>lshoose;

		lfisrt = false;

	}while(lshoose< 0 || lshoose> 6 );

	return lshoose;
}

///вывыести данные на экран
void PrintCurrRow()
{
	cout<<"Hello world!"<<endl;
}



/// флаг - существует ли флаг 
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
			PrintCurrRow();
		}

		// Добавить запись
		else if(lshoose==3)
		{	
			Hotel hotel;
			cin>>HotelRecord[currLineNum];
			
			currLineNum++;
		}
		//Загрузить из файла
		else if(lshoose==4)
		{
			
		}
		//Сортировать по году выпуска.
		else if(lshoose==5)
		{
			
		}
		else if(lshoose==6)
		{
			
		}	
		//Сохранение результатов в файл
	    else if(lshoose==9)
		{
			for(int i =0;i<9;i++)
			{				
				Write(HotelRecord[i],FILENAME);
			}
		}


	}while(lshoose!=0);
	
	int a(10);

	cout<<"Введите любой символ для продолжения ....";
	
	_getch();
	return 0;
}