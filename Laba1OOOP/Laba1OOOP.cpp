#include <iostream>
#include <vector>

template<typename T>
class priority_queue
{
private:
	class Node
	{
	public:
		T data;
		Node* left, * right, * parent;
		Node(T data = T(), Node* parent = nullptr, Node* right = nullptr, Node* left = nullptr)
		{
			this->data = data;
			this->left = left;
			this->right = right;
			this->parent = parent;
		}
	};
	Node* root;
	void balance(Node* current);
	int height(Node* node);
	void little_left_rotation(Node* node);
	void little_right_rotation(Node* node);
	void big_left_rotation(Node* node);
	void big_right_rotation(Node* node);

public:
	priority_queue();
	~priority_queue();
	void push(const T& data);
	void pop();
	const T& top() const;
	bool empty() const;
};

template<typename T>
priority_queue<T>::priority_queue()
{
	root = nullptr;
}

template<typename T>
priority_queue<T>::~priority_queue()
{
	while (root != nullptr) pop();
}

template<typename T>
void priority_queue<T>::balance(Node* current)
{
	while (current != nullptr)
	{
		if (height(current->right) - height(current->left) == 2)
		{
			if (height(current->right->right) >= height(current->right->left)) little_left_rotation(current);
			else big_left_rotation(current);
		}
		else if (height(current->left) - height(current->right) == 2)
		{
			if (height(current->left->right) <= height(current->left->left)) little_right_rotation(current);
			else big_right_rotation(current);
		}
		current = current->parent;
	}
}

template<typename T>
int priority_queue<T>::height(Node* node)
{
	if (node == nullptr) return 0;
	else if (node->left == nullptr && node->right == nullptr) return 1;
	else if (height(node->left) > height(node->right)) return height(node->left) + 1;
	else return height(node->right) + 1;
}

template<typename T>
void priority_queue<T>::little_left_rotation(Node* node)
{
	bool flag = (root == node), side = false;
	Node* tmp1 = node, * tmp2 = node->right;
	tmp1->right = node->right->left;
	tmp2->parent = node->parent;
	if (!flag && node->parent->right == node) side = true;
	tmp2->left = tmp1;
	tmp1->parent = tmp2;
	node = tmp2;
	node->left = tmp1;
	if (!flag)
		if (!side) node->parent->left = node;
		else node->parent->right = node;
	if (node->left->right != nullptr) node->left->right->parent = tmp1;
	if (flag) root = node;
}

template<typename T>
void priority_queue<T>::little_right_rotation(Node* node)
{
	bool flag = (root == node), side = false;
	Node* tmp1 = node, * tmp2 = node->left;
	tmp1->left = node->left->right;
	tmp2->parent = node->parent;
	if (!flag && node->parent->right == node) side = true;
	tmp2->right = tmp1;
	tmp1->parent = tmp2;
	node = tmp2;
	node->right = tmp1;
	if (!flag)
		if (!side) node->parent->left = node;
		else node->parent->right = node;
	if (node->right->left != nullptr)node->right->left->parent = tmp1;
	if (flag) root = node;
}

template<typename T>
void priority_queue<T>::big_left_rotation(Node* node)
{
	little_right_rotation(node->right);
	little_left_rotation(node);
}

template<typename T>
void priority_queue<T>::big_right_rotation(Node* node)
{
	little_left_rotation(node->left);
	little_right_rotation(node);
}

template<typename T>
void priority_queue<T>::push(const T& data)
{
	if (root == nullptr)
		root = new Node(data);
	else
	{
		Node* current = this->root;
		while (true)
		{
			if (data < current->data)
				if (current->left == nullptr)
				{
					Node* newNode = new Node(data, current);
					current->left = newNode;
					current = current->left;
					break;
				}
				else
					current = current->left;
			else
				if (current->right == nullptr)
				{
					Node* newNode = new Node(data, current);
					current->right = newNode;
					current = current->right;
					break;
				}
				else
					current = current->right;
		}
		balance(current);
	}
}

template<typename T>
void priority_queue<T>::pop()
{
	if (root == nullptr)
		return;
	Node* current = this->root;
	while (current->right != nullptr) current = current->right;
	if (current == root && current->left == nullptr && current->right == nullptr)
	{
		delete current;
		root = nullptr;
		return;
	}
	if (current->right == nullptr)
	{
		Node* tmp = current->parent;
		if (current->left != nullptr)
		{
			current->data = current->left->data;
			current->parent = tmp;
			delete current->left;
			current->left = nullptr;
		}
		else
		{
			if (current->parent->right != nullptr && current->parent->right == current)
				current->parent->right = nullptr;
			if (current->parent->left != nullptr && current->parent->left == current)
				current->parent->left = nullptr;
			delete current;
		}
		balance(tmp);
	}
	else
	{
		Node* min = current->right;
		while (min->left != nullptr)
			min = min->left;
		current->data = min->data;
		Node* tmp = min->parent;
		if (min->right != nullptr)
		{
			min->data = min->right->data;
			min->parent = tmp;
			delete min->right;
			min->right = nullptr;
		}
		else
		{
			if (min->parent->right != nullptr && min->parent->right == min)
				min->parent->right = nullptr;
			if (min->parent->left != nullptr && min->parent->left == min)
				min->parent->left = nullptr;
			delete min;
		}
		balance(tmp);
	}
}

template<typename T>
const T& priority_queue<T>::top() const
{
	Node* current = root;
	while (current->right != nullptr) current = current->right;
	return current->data;
}

template<typename T>
bool priority_queue<T>::empty() const
{
	if (root == nullptr) return true;
	else return false;
}

class Date
{
private:
	int m_year;
	int m_month;
	int m_day;
	int m_hour;
	int m_minute;
	int m_second;
	void add_aux(int&, int&, int, int&);
	int days_number(int, bool);
public:
	Date(int year = 0, int month = 0, int day = 0, int hour = 0, int minute = 0, int second = 0)
		: m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute), m_second(second) {}
	bool check();
	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend bool operator> (const Date&, const Date&);
	friend Date& difference(Date, Date);
	void add(Date&);
	void subtract(Date&);
	int which_day();
	int number_of_weak_in_month();
	int number_of_weak_in_year();
	void set(int, int, int, int, int, int);
};

void Date::set(int year, int month, int day, int hour, int minute, int second)
{
	m_year = year, m_month = month, m_day = day, m_hour = hour, m_minute = minute, m_second = second;
}

bool is_leap_year(int year)
{
	if (!(year % 4) && (year % 100) || !(year % 400)) return true;
	else return false;
}

bool Date::check()
{
	if (m_year < 0 || m_month <= 0 || m_month > 12 || m_hour < 0 || m_hour > 23 || m_minute < 0 || m_minute > 59 || m_second < 0 || m_second > 59)
		return false;
	bool leap_year = is_leap_year(m_year);
	if (m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10 || m_month == 12)
		if (m_day > 31)
			return false;
	if (m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11)
		if (m_day > 30)
			return false;
	if (m_month == 2)
		if (leap_year && m_day > 29)
			return false;
		else if (!leap_year && m_day > 28)
			return false;
	return true;
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << "Year: " << date.m_year << "\nMonth: " << date.m_month << "\nDay: " << date.m_day << "\nHour: " << date.m_hour << "\nMinute: " << date.m_minute << "\nSecond: " << date.m_second << "\n";
	return out;
}

int Date::days_number(int number, bool leap_year)
{
	if (number == 1 || number == 3 || number == 5 || number == 7 || number == 8 || number == 10 || number == 12) return 31;
	if (number == 4 || number == 6 || number == 9 || number == 11) return 30;
	if (leap_year) return 29;
	return 28;
}

int count_leap_years(int year1, int year2)
{
	if (year2 < year1) return count_leap_years(year2, year1);
	int c = 0;
	for (int i = year1; i < year2; ++i) c += is_leap_year(i);
	return c;
}

int count_day(int month, int day, bool leap)
{
	switch (month)
	{
	case 1:
		return day;
		break;
	case 2:
		return 31 + day;
		break;
	case 3:
		return 59 + day + leap;
		break;
	case 4:
		return 90 + day + leap;
		break;
	case 5:
		return 120 + day + leap;
		break;
	case 6:
		return 151 + day + leap;
		break;
	case 7:
		return 181 + day + leap;
		break;
	case 8:
		return 212 + day + leap;
		break;
	case 9:
		return 243 + day + leap;
		break;
	case 10:
		return 273 + day + leap;
		break;
	case 11:
		return 304 + day + leap;
		break;
	case 12:
		return 334 + day + leap;
		break;
	}
}

std::string day_from_number(int day)
{
	switch (day)
	{
	case 1:
		return "Monday";
		break;
	case 2:
		return "Tuesday";
		break;
	case 3:
		return "Wednesday";
		break;
	case 4:
		return "Thursday";
		break;
	case 5:
		return "Friday";
		break;
	case 6:
		return "Saturday";
		break;
	case 7:
		return "Sunday";
		break;
	}
}

int Date::which_day()
{
	int leap_years = count_leap_years(m_year, 2021);
	int diff = abs(2021 - m_year);
	int normal_years = diff - leap_years;
	int tmp = normal_years + 2 * leap_years, curr;
	if (m_year > 2021) curr = (4 + tmp) % 7;
	else curr = (tmp * 7 + 4 - tmp) % 7;
	return (curr + count_day(m_month, m_day, is_leap_year(m_year)) - 1) % 7 + 1;
}

int Date::number_of_weak_in_month()
{
	Date temp(m_year, m_month, 1, 0, 0, 0);
	int tmp = temp.which_day(), curr = 1;
	if (tmp != 1) curr += (8 - tmp);
	if (curr == 1) return m_day / 7 + 1;
	else if (m_day - curr < 0) return 1;
	else return (m_day - curr) / 7 + 2;
}

int Date::number_of_weak_in_year()
{
	int c = 0;
	for (int i = 1; i < m_month; ++i)
	{
		Date tmp(m_year, i, days_number(i, is_leap_year(m_year)), 0, 0, 0);
		c += tmp.number_of_weak_in_month();
	}
	c += number_of_weak_in_month();
	return c;
}

void Date::add_aux(int& this_par, int& date_par, int par, int& buf)
{
	this_par += date_par + buf;
	buf = 0;
	if (this_par > par)
	{
		buf = 1;
		this_par -= par;
	}
}

void Date::add(Date& date)
{
	int buf = 0, a = 60;
	add_aux(this->m_second, date.m_second, 60, buf);
	add_aux(this->m_minute, date.m_minute, 60, buf);
	add_aux(this->m_hour, date.m_hour, 24, buf);
	add_aux(this->m_day, date.m_day, days_number(this->m_month, is_leap_year(this->m_year)), buf);
	add_aux(this->m_month, date.m_month, 12, buf);
	this->m_year += date.m_year + buf;
}

void Date::subtract(Date& date)
{
	*this = difference(*this, date);
}

void difference_aux(int& date1_par, int& date2_par, int& answer_par, int par, int& buf)
{
	date1_par -= buf, buf = 0;
	if (date1_par < date2_par)
	{
		answer_par += par;
		buf = 1;
	}
	answer_par += date1_par - date2_par;
}

Date& difference(Date date1, Date date2)
{
	if (date2 > date1) return difference(date2, date1);
	Date answer;
	int buf = 0;
	difference_aux(date1.m_second, date2.m_second, answer.m_second, 60, buf);
	difference_aux(date1.m_minute, date2.m_minute, answer.m_minute, 60, buf);
	difference_aux(date1.m_hour, date2.m_hour, answer.m_hour, 24, buf);
	difference_aux(date1.m_day, date2.m_day, answer.m_day, 31, buf);
	difference_aux(date1.m_month, date2.m_month, answer.m_month, 12, buf);
	answer.m_year += date1.m_year - date2.m_year;
	return answer;
}

bool operator> (const Date& date1, const Date& date2)
{
	if (date1.m_year > date2.m_year) return true;
	else if (date1.m_year < date2.m_year) return false;
	else if (date1.m_month > date2.m_month) return true;
	else if (date1.m_month < date2.m_month) return false;
	else if (date1.m_day > date2.m_day) return true;
	else if (date1.m_day < date2.m_day) return false;
	else if (date1.m_hour > date2.m_hour) return true;
	else if (date1.m_hour < date2.m_hour) return false;
	else if (date1.m_minute > date2.m_minute) return true;
	else if (date1.m_minute < date2.m_minute) return false;
	else if (date1.m_second > date2.m_second) return true;
	else return false;
}

bool operator< (const Date& date1, const Date& date2)
{
	return (date2 > date1);
}

void interface()
{
	do
	{
		int tmp;
		std::cout << "1.Test priority_queue class\n2.Test date class\n3.Close program\n";
		std::cin >> tmp;
		if (tmp == 1)
		{
			std::cout << "You would like to test:\n1.int\n2.double\n3.string\n4.vector of ints\n5.Date\n";
			int number;
			std::cin >> number;
			if (number == 1)
			{
				priority_queue<int> pr_q;
				do
				{
					std::cout << "1.Push element\n2.Pop element\n3.Print top\n4.Back\n";
					int a;
					std::cin >> a;
					if (a == 1)
					{
						int temp;
						std::cout << "Enter: \n";
						std::cin >> temp;
						pr_q.push(temp);
					}
					else if (a == 2) pr_q.pop();
					else if (a == 3)
					{
						if (pr_q.empty())
							std::cout << "Empty\n";
						else
							std::cout << "Top: " << (pr_q.top()) << "\n";
					}
					else if (a == 4) break;
					else std::cout << "Incorrect input\n";
				} while (true);
			}
			else if (number == 2)
			{
				priority_queue<double> pr_q;
				do
				{
					std::cout << "1.Push element\n2.Pop element\n3.Print top\n4.Back\n";
					int a;
					std::cin >> a;
					if (a == 1)
					{
						double temp;
						std::cout << "Enter: \n";
						std::cin >> temp;
						pr_q.push(temp);
					}
					else if (a == 2) pr_q.pop();
					else if (a == 3)
					{
						if (pr_q.empty())
							std::cout << "Empty\n";
						else
							std::cout << "Top: " << (pr_q.top()) << "\n";
					}
					else if (a == 4) break;
					else std::cout << "Incorrect input\n";
				} while (true);
			}
			else if (number == 3)
			{
				priority_queue<std::string> pr_q;
				do
				{
					std::cout << "1.Push element\n2.Pop element\n3.Print top\n4.Back\n";
					int a;
					std::cin >> a;
					if (a == 1)
					{
						std::string temp;
						std::cout << "Enter: \n";
						std::cin >> temp;
						pr_q.push(temp);
					}
					else if (a == 2) pr_q.pop();
					else if (a == 3)
					{
						if (pr_q.empty())
							std::cout << "Empty\n";
						else
							std::cout << "Top: " << (pr_q.top()) << "\n";
					}
					else if (a == 4) break;
					else std::cout << "Incorrect input\n";
				} while (true);
			}
			else if (number == 4)
			{
				priority_queue<std::vector<int> > pr_q;
				do
				{
					std::cout << "1.Push element\n2.Pop element\n3.Print top\n4.Back\n";
					int a;
					std::cin >> a;
					if (a == 1)
					{
						std::vector<int> temp;
						std::cout << "Enter the number of elements:\n";
						int co;
						std::cin >> co;
						std::cout << "Enter the elements:\n";
						while (co--)
						{
							int tempo;
							std::cin >> tempo;
							temp.push_back(tempo);
						}
						pr_q.push(temp);
					}
					else if (a == 2) pr_q.pop();
					else if (a == 3)
					{
						if (pr_q.empty())
							std::cout << "Empty\n";
						else
						{
							std::cout << "Top: ";
							for (const auto& elem : pr_q.top())
								std::cout << elem << " ";
							std::cout << "\n";
						}
					}
					else if (a == 4) break;
					else std::cout << "Incorrect input\n";
				} while (true);
			}
			else if (number == 5)
			{
				priority_queue<Date> pr_q;
				do
				{
					std::cout << "1.Push element\n2.Pop element\n3.Print top\n4.Back\n";
					int a;
					std::cin >> a;
					if (a == 1)
					{
						Date temp;
						do
						{
							std::cout << "Enter the date:\n";
							int n2, y2, mo2, d2, h2, mi2, s2;
							std::cout << "Year: ";
							std::cin >> y2;
							std::cout << "Month: ";
							std::cin >> mo2;
							std::cout << "Day: ";
							std::cin >> d2;
							std::cout << "Hour: ";
							std::cin >> h2;
							std::cout << "Minute: ";
							std::cin >> mi2;
							std::cout << "Second: ";
							std::cin >> s2;
							temp.set(y2, mo2, d2, h2, mi2, s2);
							if (!temp.check())
							{
								std::cout << "Incorrect date\n";
								continue;
							}
							break;
						} while (true);
						pr_q.push(temp);
					}
					else if (a == 2) pr_q.pop();
					else if (a == 3)
					{
						if (pr_q.empty())
							std::cout << "Empty\n";
						else
							std::cout << "Top: " << (pr_q.top()) << "\n";
					}
					else if (a == 4) break;
					else std::cout << "Incorrect input\n";
				} while (true);
			}
			else std::cout << "Incorrect input\n";
		}
		else if (tmp == 2)
		{
			std::cout << "Enter the date you would like to work with:\n";
			int n, y, mo, d, h, mi, s;
			std::cout << "Year: ";
			std::cin >> y;
			std::cout << "Month: ";
			std::cin >> mo;
			std::cout << "Day: ";
			std::cin >> d;
			std::cout << "Hour: ";
			std::cin >> h;
			std::cout << "Minute: ";
			std::cin >> mi;
			std::cout << "Second: ";
			std::cin >> s;
			Date date(y, mo, d, h, mi, s);
			bool cont = true;
			do
			{
				std::cout << "1.Add another date to this\n2.Subtract another date from this\n3.Check if the date is correct\n4.Find out which day of the week it is\n5.Find out what is the number of the weak in month\n6.Find out what is the number of the weak in year\n7.Print the date\n8.Back\n";
				int input;
				std::cin >> input;
				if (input == 1 || input == 2)
					do
					{
						std::cout << "Enter the date:\n";
						int n1, y1, mo1, d1, h1, mi1, s1;
						std::cout << "Year: ";
						std::cin >> y1;
						std::cout << "Month: ";
						std::cin >> mo1;
						std::cout << "Day: ";
						std::cin >> d1;
						std::cout << "Hour: ";
						std::cin >> h1;
						std::cout << "Minute: ";
						std::cin >> mi1;
						std::cout << "Second: ";
						std::cin >> s1;
						Date date2(y1, mo1, d1, h1, mi1, s1);
						if (!date2.check())
						{
							std::cout << "Incorrect date\n";
							continue;
						}
						if (input == 1)
							date.add(date2);
						else
							date.subtract(date2);
						break;
					} while (true);
					switch (input)
					{
					case 1:
						break;
					case 2:
						break;
					case 3:
						if (date.check())
							std::cout << "Correct\n";
						else
							std::cout << "Wrong\n";
						break;
					case 4:
						std::cout << day_from_number(date.which_day()) << "\n";
						break;
					case 5:
						std::cout << date.number_of_weak_in_month() << "\n";
						break;
					case 6:
						std::cout << date.number_of_weak_in_year() << "\n";
						break;
					case 7:
						std::cout << date << "\n";
						break;
					case 8:
						cont = false;
						break;
					default:
						std::cout << "Wrong input\n";
					}
			} while (cont);
		}
		else if (tmp == 3)
			return;
		else
			std::cout << "Wrong input\n";
	} while (true);
}

int main()
{
	interface();
	return 0;
}