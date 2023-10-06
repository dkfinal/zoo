#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>

//������� ����� ��������, ������ �������� ���������
class Mammal {
public:
    Mammal(std::string name, int weight_in_gm, int height_in_cm) {
        this->weight_in_gm = weight_in_gm;
        this->height_in_cm = height_in_cm;
    }
    virtual ~Mammal() {}

    //��������� ��� � ��/�^2
    double getBMI() {
        double weight_in_kg = weight_in_gm / 1000.0;
        double height_in_m = height_in_cm / 100.0;
        return weight_in_kg / (height_in_m * height_in_m);
    }

private:
    std::string name;
    int weight_in_gm;
    double height_in_cm;
};


//��������� ����� ����, ������ ������ �������
class Bird : public Mammal
{
public:
    Bird(std::string name, int weight_in_gm, int height_in_cm, int wingspan_in_cm) : Mammal(name, weight_in_gm, height_in_cm) {
        this->wingspan_in_cm = wingspan_in_cm;
    }
	~Bird() {}

    double getWingspan() {
        return wingspan_in_cm;
    }

private:
    int wingspan_in_cm;
};

//�������� ��������������� ��������� �� ������
void rmPrevParam(std::string &paramsStr) {
    if (paramsStr.find(' ') != -1) {
        paramsStr = paramsStr.substr(paramsStr.find_first_of(' ') + 1, paramsStr.size() - 1);
    }
    else {
        paramsStr.clear();
    }
}

//��������� ���������� ��������� ��� ������������� �������
std::string getNextParam(std::string &paramsStr) {
    std::string param = paramsStr.substr(0, paramsStr.find_first_of(' '));
    rmPrevParam(paramsStr);
    return param;
}

//���������� ����� ��� �������� � ����������
double getBMISum(std::vector<Mammal> animals) {
    double bmiSum = 0.0;
    for (auto animal : animals) {
        bmiSum += animal.getBMI();
    }
    return bmiSum;
}

//���������� �������
double getMidOfParams(int amount, std::function<double(int)> getCB) {
    if (amount > 0) {
        std::vector<double> vec;
        for (int i = 0; i < amount; i++) {
            vec.push_back(getCB(i));
        }
        std::sort(vec.begin(), vec.end());
        if (vec.size() % 2 == 0) {
            return (vec[vec.size() / 2 - 1] + vec[vec.size() / 2]) / 2.0;
        }
        else {
            return vec[vec.size() / 2];
        }
    }
    else {
        return 0.0;
    }
}

//����� ��������� �����, �� ����� �� ���������
Mammal initMammal(std::string mammalParams) {
    auto name = getNextParam(mammalParams);
    auto w = std::atoi(getNextParam(mammalParams).c_str());
    auto h = std::atoi(getNextParam(mammalParams).c_str());
    Mammal newMammal(name, w, h);
    return newMammal;
}

Bird initBird(std::string birdParams) {
    auto name = getNextParam(birdParams);
    auto w = std::atoi(getNextParam(birdParams).c_str());
    auto h = std::atoi(getNextParam(birdParams).c_str());
    auto wsp = std::atoi(getNextParam(birdParams).c_str());
    Bird newBird(name, w, h, wsp);
    return newBird;
}

//����� ���������� ���������� �� main
void initZoo(std::vector<Mammal> &zoo, std::vector<Bird> &aviary) {
    //���� ��������
    static const std::string mammalType = "0";
    static const std::string birdType = "1";

    int amount = 0;
    std::string amountStr = "";
    std::getline(std::cin, amountStr);
    amount = std::atoi(amountStr.c_str());

    for (int i = 0; i < amount; i++) {
        std::string animalParams;
        std::getline(std::cin, animalParams);
        if (animalParams.length() > 0) {
            std::string animaltype = getNextParam(animalParams);
            if (animaltype == birdType) {
                aviary.push_back(initBird(animalParams));
            }
            zoo.push_back(initMammal(animalParams));
        }
    }
}

int main()
{
    //���������� ��������
    std::vector<Mammal> zoo;
    std::vector<Bird> aviary;

    initZoo(zoo, aviary);   //���������� �����������

    std::string result = "";
    result += std::to_string(getBMISum(zoo) / zoo.size()) + " ";    //������� ��� ���� �������� �����/����������
    result += std::to_string(getMidOfParams(zoo.size(), [&zoo](int n) -> double { return zoo[n].getBMI(); })) + " ";    //������� ��� ��������
    result += std::to_string(getMidOfParams(aviary.size(), [&aviary](int n) -> double {return aviary[n].getWingspan(); })) + " ";   //������� ������� ������� ����
    std::cout << result << std::endl;

    getchar(); //����� ����� ���������
    return 0;
}