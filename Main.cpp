#include <iostream>
#include <string>
#include <vector>

//explicit - запрещает вызывать конструктор (должен стоять перед)

//шаблоны классов
//создание шаблонного связного списка

//связный список - это структура данных в которой каждый элемент хранится
//  в памяти и знает где хранится следующий элемент в структуре списка

//при работе с нодами - геттеры и сеттеры не используются

template <typename Type>
class LinkedList {
public:
	//Задачи связного списка
 
	//конструктор по умолчанию - заполняет всё нулями
	LinkedList()
		:start_(nullptr),
		end_(nullptr),//NULL - лучше не использовать, может сломать сборку приложения
		size_(0)
	{ }


	//создаем список точек столько - сколько ввел пользователь
	LinkedList(int n){//лист с уже созданными n элементами
		:LinkedList() {
			if (n < 0)throw - 1;
			if (n == 0)return;
			Node* tmp{};//создаем место для хранения вновь создаваемых точек
		
			int count{ 0 };//счетчик о том сколько точек мы уже добавили
			tmp = new Node{};//создаем новую точку и записываем ее данные
			start_ = tmp;//поле начало списка
			end_ = tmp;//поле конца списка
			count += 1;
			while (count < n) {//сработает если мы получили больше 1 на вход
				tmp = new Node{};//создаём новую точку
				end_->Next(tmp);//старому концу списка говорим, что новый конечный элемент существует
				end_ = tmp;//запоминаем в списке какой элемент сейчас последний
				count += 1;
			}

			size_ = n;//когда завершим процесс - запомним сколько точек пользователь ввел
		}


		//конструктор копирования, копируем из одного списка в другой
		LinkedList(const Linkedlist& other)
			:LinkedList(){				
			if (other.size() == 0)return;
			start_ = new Node(other.start_->Data())//перенесли информацию из стартовой точки в стартовую точку, из старого списка в новый
				end_ = start_;
			for (Node* current = other.start_->Next(); current != nullptr;current=current->Next())//от нуля до того сколько хранилось элементов в коллекции
			{
				//Node* tmp = new Node(other[i]); так не делать!!!
				Node* tmp = new Node(current->Data());//возвращаем с помощью метода Data значение Node
				end_->Next(tmp);//Задаем новый элемент
				end_ = tmp;//запоминаем последний элемент
			}
			size_ = other.size_;
		}


		//конструктор переноса
		LinkedList(Linkedlist&& other) {//можно не делать но для оптимизации скорости работы программы полезно
			:LinkedList()							//тут не будет реализации конструктора от списка инициализации, внесём позже
				std::swap(start_, other.start_);
			std::swap(end_,other.end_);
			std::swap(size_,other.size_);//свапаем все что енадо перенести
		}
		~LinkedList() {//деструктор(~)
			Node* current =start_;
			while (current != nullptr) {
				Node* tmp = current->Next();//запомнили какой элемент будет следующим за текущим
				delete current;//освобождаем память от точки
				current = tmp;//делаем текущей точку ту которую мы запомнили
			}
			
			
		}


		//создаем clear для вызова в присваивании копированием
		void clear() {
			Node* current = start_;
			while (current != nullptr) {
				Node* tmp = current->Next();
				delete current;
				current = tmp;
			}
			start_ = nullptr;
			end_ = nullptr;
			size_ = 0;
		}

	//присваивание копированием 
		LinkedList& operator = (const LinkedList& other) {
			clear();
			
				if (other.size() == 0)return* this;
				start_ = new Node(other.start_->Data())//перенесли информацию из стартовой точки в стартовую точку, из старого списка в новый
					end_ = start_;
				for (Node* current = other.start_->Next(); current != nullptr; current = current->Next())//от нуля до того сколько хранилось элементов в коллекции
				{
					//Node* tmp = new Node(other[i]); так не делать!!!
					Node* tmp = new Node(current->Data());//возвращаем с помощью метода Data значение Node
					end_->Next(tmp);//Задаем новый элемент
					end_ = tmp;//запоминаем последний элемент
				}
				size_ = other.size_;
			return*this;
		}

	//присваивание переносом
		LinkedList& operator = (const LinkedList&& other) {
			clear();
			std::swap(start_, other.start_);
			std::swap(end_, other.end_);
			std::swap(size_, other.size_);
			return*this;
		}

		//оператор []для доступа к хранящимся в списке элементам
		Type& operator[](int i) {
			int count{};
			Node* tmp = start_;
			while (count < i) {
				tmp = tmp->NEXT();
				COUNT += 1;
			}
			return tmp->Data();
		}

		//константный метод для доступа к хранящимся в списке элементам
	const Type& operator[](int i)const {
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->NEXT();
			COUNT += 1;
		}
		return tmp->Data();
	}


	//то же что и []
	Type& at[](int i);
	const Type& at[](int i)const;//метод at - вместо []


	void push_back(const Type& obj);//добавить данные в конец списка
	void push_front(const Type& obj);//добавить данные в начало списка


	void pop_bask();//уничтожить данные в конце списка
	void pop_front();//уничтожить данные в начале списка

	/*
	emplace/insert - методы добавления новых данных в произвольное место коллекции
	erse - метод для уничтожения данных в произвольной точке коллекции

	*/

	int size()const;//метод - сообщить пользователю сколько в коллекции есть элементов

	/*
	методы для прохода по коллекции умными указателями
	мы пока сознательно опустим
	*/
private:
	class Node {
	public:
		Node()
			:Node(Type())//при делигации мы вызываем конструктор по умолчанию хранимого типа данных.
			//Данный синтаксис корректно отработает даже если прямой вызов такого метода
			// (например конструктора встроенных типов)
		{ }

		Node(const Type& data, Node* place = nullptr)
			:data_(data),
			next_(place)
		{ }

		typename& Data() {
			return data_;
		}

		const Type& Data()const {
			return data_;
		}

		Node* Next()const {//создали метод о местоположеннии точки следующей в списке
			return next_;
		}

		void Next(Node* next_) {//устанавливаем новое значение о следующей точке
			next_ = next;
		}

	private:
		Type data_;
		Node* next_;
	};
	Node* start_;
	Node* end_;
	int size_;

};


int main() {
	system("chcp 1251>nul");

	int arr[10];
	std::vector<int>vec(10);
	LinkedList<int>list;
	arr[5] = 34;
	vec[5] = 23;
	list[5] = 12;




	return 0;
}