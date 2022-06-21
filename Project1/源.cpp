#pragma warning(disable:6031)

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>

// 题目的数据结构
struct Question
{
	std::string question;
	std::string a;
	std::string b;
	std::string c;
	std::string d;
	std::string ans;
};

// 把问题写到文件中，事实证明没啥用，已弃用
void writeFile(std::ofstream& os) {
	os.open("data.txt", std::ios::app);
	Question question;
	while (true)
	{
		std::cout << "请输入问题:" << std::endl;
		std::cin >> question.question;
		os << question.question << std::endl;

		std::cout << "A:" << std::endl;
		std::cin >> question.a;
		os << question.a << std::endl;

		std::cout << "B:" << std::endl;
		std::cin >> question.b;
		os << question.b << std::endl;

		std::cout << "C:" << std::endl;
		std::cin >> question.c;
		os << question.c << std::endl;

		std::cout << "D:" << std::endl;
		std::cin >> question.d;
		os << question.d << std::endl;

		std::cout << "答案:" << std::endl;
		std::cin >> question.ans;
		os << question.ans << std::endl;
	}
	os.close();
}

bool judge(const Question& q, const std::string& ans) {
	return _strcmpi(q.ans.c_str(), ans.c_str()) == 0;
}

void readFile(std::ifstream& is, std::vector<Question>& vec) {
	Question question;
	std::string str;
	is.open("data.txt", std::ios::in);
	int i = 0;
	while (getline(is, str))
	{
		switch (i)
		{
		case 0: question.question = str; break;
		case 1: question.a = str; break;
		case 2: question.b = str; break;
		case 3: question.c = str; break;
		case 4: question.d = str; break;
		case 5: question.ans = str; break;
		}

		if (i == 5) {
			i = -1;
			vec.push_back(question);
		}
		i++;
	}
	is.close();
}

// 刷题
void training(std::vector<Question>& vec) {
	std::string ans;
	int index = 0;
	for (Question& i : vec) {
		index++;
		std::cout << i.question << std::endl;
		std::cout << i.a << std::endl;
		std::cout << i.b << std::endl;
		std::cout << i.c << std::endl;
		std::cout << i.d << std::endl;
		std::cout << "请输入答案：" << std::endl;
		std::cin >> ans;
		if (judge(i, ans)) {
			std::cout << "答案正确!" << std::endl;
		}
		else {
			std::cout << "正确答案为：" << i.ans << std::endl;
		}
		_getch();
		system("cls");
	}
}

void training(std::vector<Question>& vec, std::vector<Question>& vec2) {
	std::string ans;
	int index = 0;
	for (Question& i : vec) {
		index++;
		std::cout << i.question << std::endl;
		std::cout << i.a << std::endl;
		std::cout << i.b << std::endl;
		std::cout << i.c << std::endl;
		std::cout << i.d << std::endl;
		std::cout << "请输入答案：" << std::endl;
		std::cin >> ans;
		if (judge(i, ans)) {
			std::cout << "答案正确!" << std::endl;
		}
		else
		{
			std::cout << "正确答案为：" << i.ans << std::endl;
			vec2.push_back(i);
		}
		_getch();
		system("cls");
	}
}

// 洗牌算法，用来打乱题目顺序
void suffle(std::vector<Question>& vec) {
	srand(time(0));

	for (size_t i = vec.size(); i > 1; i--) {
		int key = rand() % i;
		std::swap(vec[i - 1], vec[key]);
	}
}

void menu() {
	std::cout << "------------------------------------------------------------------" << std::endl;
	std::cout << "                   1 刷题                                         " << std::endl;
	std::cout << "                   2 刷错题（需要先刷一遍题）                     " << std::endl;
	std::cout << "                   3 没想好                                       " << std::endl;
	std::cout << "------------------------------------------------------------------" << std::endl;
}

void checkBadQuestion(std::vector<Question>& vec) {
	if (vec.size() == 0) {
		std::cout << "无错题！" << std::endl;
		return;
	}

	training(vec);
}

int main()
{
	std::ofstream os;
	std::ifstream is;
	std::vector<Question> vec;
	std::vector<Question> badVec;
	int key;

	readFile(is, vec);

	while (true) {
		menu();

		std::cin >> key;

		system("cls");

		switch (key) {
		case 1: suffle(vec);  training(vec, badVec); break;
		case 2: checkBadQuestion(badVec); break;
		default:
			std::cout << "都说了没想好" << std::endl;
			break;
		}	
	}

	return 0;
}