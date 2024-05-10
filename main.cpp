#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits> // �������ͷ�ļ���ʹ��numeric_limits

using namespace std;

class ParkingLot;

// ��������
void ClearScreen() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/macOS
#endif
}

// ��������
class Vehicle {
public:
    string plateNumber;
    string brand;
    string model;
    string color;
    time_t entryTime;

    Vehicle(string plateNumber, string brand, string model, string color) {
        this->plateNumber = plateNumber;
        this->brand = brand;
        this->model = model;
        this->color = color;
        this->entryTime = time(nullptr);
    }
};

// �����࣬�̳��Գ�������
class Car : public Vehicle {
public:
    Car(string plateNumber, string brand, string model, string color)
        : Vehicle(plateNumber, brand, model, color) {}
};

// �û�����
class User {
public:
    virtual void displayInfo() const = 0;
    virtual void processModule(ParkingLot& parkingLot) = 0;
};

// ����Ա�û��࣬�̳����û�����
class AdminUser : public User {
private:
    string adminPassword;

public:
    AdminUser(string password) : adminPassword(password) {}

    void displayInfo() const override {
        cout << "����Ա�û�" << endl;
    }

    void processModule(ParkingLot& parkingLot) override {
        // ����Աģ���߼�
        // ...
        cout << "����Աģ���߼�" << endl;
    }
};

// ��ͨ�û��࣬�̳����û�����
class RegularUser : public User {
public:
    void displayInfo() const override {
        cout << "��ͨ�û�" << endl;
    }

    void processModule(ParkingLot& parkingLot) override {
        // ��ͨ�û�ģ���߼�
        // ...
        cout << "��ͨ�û�ģ���߼�" << endl;
    }
};

// �ο��û��࣬�̳����û�����
class GuestUser : public User {
public:
    void displayInfo() const override {
        cout << "�ο��û�" << endl;
    }

    void processModule(ParkingLot& parkingLot) override {
        // �ο��û�ģ���߼�

        cout << "�ο��û�ģ���߼�" << endl;
    }
};

// ͣ������
class ParkingLot {
private:
    vector<Car> cars;

public:
    void addCar(Car car) {
        cars.push_back(car);
    }

    void deleteCar(string plateNumber) {
        for (auto it = cars.begin(); it != cars.end(); ++it) {
            if (it->plateNumber == plateNumber) {
                cars.erase(it);
                break;
            }
        }
    }

    bool carExists(string plateNumber) {
        for (auto& car : cars) {
            if (car.plateNumber == plateNumber) {
                return true;
            }
        }
        return false;
    }

    Car* findCar(string plateNumber) {
        for (auto& car : cars) {
            if (car.plateNumber == plateNumber) {
                return &car;
            }
        }
        return nullptr;
    }

    void modifyCar(string plateNumber, string brand, string model, string color) {
        if (carExists(plateNumber)) {

            Car* car = findCar(plateNumber);
            if (car != nullptr) {
                car->plateNumber = plateNumber;
                car->brand = brand;
                car->model = model;
                car->color = color;
                cout << "������Ϣ���޸�" << endl;
            }
        }
        else {
            cout << "δ�ҵ����иó��ƺŵ��������޷��޸���Ϣ!" << endl;
        }
    }

    void displayAllCars() {
        if (cars.empty()) {
            cout << "��ͣ������δͣ���κγ�������ѯ��ϢΪ�գ�" << endl;
        }
        else {
            for (auto& car : cars) {
                cout << "���ƺ�: " << car.plateNumber << endl;
                cout << "Ʒ��: " << car.brand << endl;
                cout << "�ͺ�: " << car.model << endl;
                cout << "��ɫ: " << car.color << endl;
                cout << "�볡ʱ��: " << ctime(&car.entryTime);
                time_t currentTime = time(nullptr);
                double elapsedTime = difftime(currentTime, car.entryTime);
                cout << "ͣ��ʱ�� (��): " << elapsedTime << endl;
            }
        }
    }

    void saveToFile(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (auto& car : cars) {
                file << "���ƺ�: " << car.plateNumber << endl;
                file << "Ʒ��: " << car.brand << endl;
                file << "�ͺ�: " << car.model << endl;
                file << "��ɫ: " << car.color << endl;
                file << "�볡ʱ��: " << ctime(&car.entryTime) << endl;
            }
            file.close();
        }
        else {
            cerr << "�޷����ļ�����д�롣" << endl;
        }
    }

    bool empty() {
        return cars.empty();
    }
};

void CarInformation() {
    cout << "\n" << endl;
    cout << "                                                         ������Ϣģ�飺" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *      1. ���������Ϣ      *" << endl;
    cout << "                                                *      2. ɾ��������Ϣ      *" << endl;
    cout << "                                                *      3. ����������Ϣ      *" << endl;
    cout << "                                                *      4. �޸�������Ϣ      *" << endl;
    cout << "                                                *      5. ͣ��ʱ��ͳ��      *" << endl;
    cout << "                                                *      6. ͣ������Ϣ��ʾ    *" << endl;
    cout << "                                                *      7. ������Ϣ����      *" << endl;
    cout << "                                                *      8. ������һ���˵�    *" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void User() {
    cout << "\n" << endl;
    cout << "                                                        ��ͨ�û�ģ�飺" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *     1. ��ʾ������Ϣ       *" << endl;
    cout << "                                                *     2. ��ѯ������Ϣ       *" << endl;
    cout << "                                                *     3. ͣ��ʱ��ͳ��       *" << endl;
    cout << "                                                *     4. �˳���ͨ�û���¼   *" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void AdminUser() {
    cout << "\n" << endl;
    cout << "                                                          ����Ա�û�ģ�飺" << endl;
    cout << "                                                * * * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *      1. ���������Ϣ          *" << endl;
    cout << "                                                *      2. ��ѯ������Ϣ          *" << endl;
    cout << "                                                *      3. �޸�������Ϣ          *" << endl;
    cout << "                                                *      4. ɾ��������Ϣ          *" << endl;
    cout << "                                                *      5. ������Ϣͳ��          *" << endl;
    cout << "                                                *      6. �޸Ĺ���Ա����        *" << endl;
    cout << "                                                *      7. �˳�����Ա�û���¼    *" << endl;
    cout << "                                                * * * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void GuestUser() {
    cout << "\n" << endl;
    cout << "                                                         �ο��û�ģ�飺" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *      1. ��ʾ������Ϣ       *" << endl;
    cout << "                                                *      2. ��ѯ������Ϣ       *" << endl;
    cout << "                                                *      3. ͣ��ʱ��ͳ��       *" << endl;
    cout << "                                                *      4. �������˵�         *" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void Home() {
    cout << "\n" << endl;
    cout << "                                                           ���˵���" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *      1. ������Ϣģ��      *" << endl;
    cout << "                                                *      2. ��ͨ�û�ģ��      *" << endl;
    cout << "                                                *      3. ����Ա�û�ģ��    *" << endl;
    cout << "                                                *      4. �ο��û�ģ��      *" << endl;
    cout << "                                                *      5. �˳�����          *" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void CarInformationModule(ParkingLot& parkingLot) {
    ClearScreen();
    while (true) {
        CarInformation();
        int carModuleChoice;

        if (!(cin >> carModuleChoice)) {
            cin.clear(); // ��������־
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������Ч����
            cout << "��Ч�����룬������" << endl;
            continue; // ����ѭ�������ಿ�֣����¿�ʼ
        }

        switch (carModuleChoice) {
        case 1: {
            string plateNumber, brand, model, color;
            cout << "�����복�ƺ�: ";
            cin >> plateNumber;
            cout << "������Ʒ��: ";
            cin >> brand;
            cout << "�������ͺ�: ";
            cin >> model;
            cout << "��������ɫ: ";
            cin >> color;
            Car car(plateNumber, brand, model, color);
            parkingLot.addCar(car);
            cout << "������Ϣ�����" << endl;
            break;
        }
        case 2: {
            string plateNumber;
            cout << "������Ҫɾ���ĳ��ƺ�: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr)
            {
                parkingLot.deleteCar(plateNumber);
                cout << "������Ϣ��ɾ��!" << endl;
            }
            else
            {
                cout << "δ��ѯ���ó�����ɾ��ʧ��!";
            }
            break;
        }
        case 3: {
            string plateNumber;
            cout << "������Ҫ���ҵĳ��ƺ�: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                cout << "���ƺ�: " << car->plateNumber << endl;
                cout << "Ʒ��: " << car->brand << endl;
                cout << "�ͺ�: " << car->model << endl;
                cout << "��ɫ: " << car->color << endl;
                cout << "�볡ʱ��: " << ctime(&car->entryTime) << endl;
            }
            else {
                cout << "δ���ҵ��ó���!" << endl;
            }
            break;
        }
        case 4: {
            string plateNumber, brand, model, color;
            cout << "������Ҫ�޸ĵĳ��ƺ�: ";
            cin >> plateNumber;
            if (parkingLot.carExists(plateNumber)) {
                cout << "�������µ�Ʒ��: ";
                cin >> brand;
                cout << "�������µ��ͺ�: ";
                cin >> model;
                cout << "�������µ���ɫ: ";
                cin >> color;
                parkingLot.modifyCar(plateNumber, brand, model, color);
            }
            else {
                cout << "δ�ҵ����иó��ƺŵ��������޷��޸���Ϣ!" << endl;
            }
            break;
        }
        case 5: {
            // ����ͣ��ʱ��
            string plateNumber;
            cout << "������Ҫ���ҵĳ��ƺ�: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                time_t currentTime = time(nullptr);
                double elapsedTime = difftime(currentTime, car->entryTime);
                cout << "ͣ��ʱ�� (��): " << elapsedTime << endl;
            }
            else {
                cout << "δ���ҵ��ó���!" << endl;
            }
            break;
        }
        case 6: {
            // ��ʾͣ��������������Ϣ
            parkingLot.displayAllCars();
            break;
        }
        case 7: {
            // ����������Ϣ���ļ�
            string filename;
            cout << "�������ļ���: ";
            cin >> filename;
            parkingLot.saveToFile(filename);
            cout << "������Ϣ�ѱ��浽�ļ�" << endl;
            break;
        }
        case 8:
            // �������˵�
            ClearScreen();
            break;
        default:
            cout << "��Ч��ѡ�������" << endl;
        }

        if (carModuleChoice == 8) {
            break;
        }
    }
}

void UserModule(ParkingLot& parkingLot) {
    ClearScreen();
    int userModuleChoice;
    while (true) {
        User();

        if (!(cin >> userModuleChoice)) {
            cin.clear(); // ��������־
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������Ч����
            cout << "��Ч�����룬������" << endl;
            continue; // ����ѭ�������ಿ�֣����¿�ʼ
        }

        switch (userModuleChoice) {
        case 1:
            // ��ʾ������Ϣ
            parkingLot.displayAllCars();
            break;
        case 2: {
            // ��ѯ������Ϣ
            string plateNumber;
            cout << "������Ҫ��ѯ�ĳ��ƺ�: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                cout << "���ƺ�: " << car->plateNumber << endl;
                cout << "Ʒ��: " << car->brand << endl;
                cout << "�ͺ�: " << car->model << endl;
                cout << "��ɫ: " << car->color << endl;
                cout << "�볡ʱ��: " << ctime(&car->entryTime) << endl;
            }
            else {
                cout << "δ���ҵ��ó���!" << endl;
            }
            break;
        }
        case 3: {
            // ͣ��ʱ��ͳ��
            string plateNumber;
            cout << "������Ҫ���ҵĳ��ƺ�: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                time_t currentTime = time(nullptr);
                double elapsedTime = difftime(currentTime, car->entryTime);
                cout << "ͣ��ʱ�� (��): " << elapsedTime << endl;
            }
            else {
                cout << "δ���ҵ��ó���!" << endl;
            }
            break;
        }
        case 4:
            // �������˵�
            ClearScreen();
            break;
        default:
            cout << "��Ч��ѡ�������" << endl;
        }

        if (userModuleChoice == 4) {
            break;
        }
    }
}

void AdminModule(ParkingLot& parkingLot, string& adminPassword) {
    ClearScreen();
    cout << "���������Ա����: ";
    string adminPasswordInput;
    cin >> adminPasswordInput;
    if (adminPasswordInput == adminPassword) {
        int adminModuleChoice;
        while (true) {
            AdminUser();

            if (!(cin >> adminModuleChoice)) {
                cin.clear(); // ��������־
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������Ч����
                cout << "��Ч�����룬������" << endl;
                continue; // ����ѭ�������ಿ�֣����¿�ʼ
            }

            switch (adminModuleChoice) {
            case 1: {
                string plateNumber, brand, model, color;
                cout << "�����복�ƺ�: ";
                cin >> plateNumber;
                cout << "������Ʒ��: ";
                cin >> brand;
                cout << "�������ͺ�: ";
                cin >> model;
                cout << "��������ɫ: ";
                cin >> color;
                Car car(plateNumber, brand, model, color);
                parkingLot.addCar(car);
                cout << "������Ϣ�����" << endl;
                break;
            }
            case 2: {
                // ��ѯ������Ϣ
                string plateNumber;
                cout << "������Ҫ��ѯ�ĳ��ƺ�: ";
                cin >> plateNumber;
                Car* car = parkingLot.findCar(plateNumber);
                if (car != nullptr) {
                    cout << "���ƺ�: " << car->plateNumber << endl;
                    cout << "Ʒ��: " << car->brand << endl;
                    cout << "�ͺ�: " << car->model << endl;
                    cout << "��ɫ: " << car->color << endl;
                    cout << "�볡ʱ��: " << ctime(&car->entryTime) << endl;
                }
                else {
                    cout << "δ���ҵ��ó���!" << endl;
                }
                break;
            }
            case 3: {
                string plateNumber, brand, model, color;
                cout << "������Ҫ�޸ĵĳ��ƺ�: ";
                cin >> plateNumber;
                if (parkingLot.carExists(plateNumber)) {
                    cout << "�������µ�Ʒ��: ";
                    cin >> brand;
                    cout << "�������µ��ͺ�: ";
                    cin >> model;
                    cout << "�������µ���ɫ: ";
                    cin >> color;
                    parkingLot.modifyCar(plateNumber, brand, model, color);
                }
                else {
                    cout << "δ�ҵ����иó��ƺŵ��������޷��޸���Ϣ!" << endl;
                }
                break;
            }
            case 4: {
                string plateNumber;
                cout << "������Ҫɾ���ĳ��ƺ�: ";
                cin >> plateNumber;
                Car* car = parkingLot.findCar(plateNumber);
                if (car != nullptr)
                {
                    parkingLot.deleteCar(plateNumber);
                    cout << "������Ϣ��ɾ��!" << endl;
                }
                else
                {
                    cout << "δ��ѯ���ó�����ɾ��ʧ��!";
                }
                break;
            }


            case 5:
                // ��ʾͣ��������������ͣ��ʱ��
                parkingLot.displayAllCars();
                break;
            case 6: {
                // �޸Ĺ���Ա����
                string oldPassword, newPassword, newPasswordConfirm;
                cout << "�����������: ";
                cin >> oldPassword;
                if (oldPassword == adminPassword) {
                    cout << "������������: ";
                    cin >> newPassword;
                    cout << "���ٴ�����������: ";
                    cin >> newPasswordConfirm;
                    if (newPassword == newPasswordConfirm) {
                        adminPassword = newPassword;
                        cout << "����Ա�������޸�" << endl;
                    }
                    else {
                        cout << "������ǰ��һ�£������ԣ�" << endl;
                    }
                }
                else {
                    cout << "����Ա�������" << endl;
                }
                break;
            }
            case 7:
                // �������˵�
                ClearScreen();
                break;
            default:
                cout << "��Ч��ѡ�������" << endl;
            }

            if (adminModuleChoice == 7) {
                break;
            }
        }
    }
    else {
        cout << "����Ա�������" << endl;
    }
}

void GuestModule(ParkingLot& parkingLot) {
    ClearScreen();
    int guestModuleChoice;
    while (true) {
        GuestUser();

        if (!(cin >> guestModuleChoice)) {
            cin.clear(); // ��������־
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������Ч����
            cout << "��Ч�����룬������" << endl;
            continue; // ����ѭ�������ಿ�֣����¿�ʼ
        }

        switch (guestModuleChoice) {
        case 1:
            // ��ʾ������Ϣ
            parkingLot.displayAllCars();
            break;
        case 2: {
            // ��ѯ������Ϣ
            string plateNumber;
            cout << "������Ҫ��ѯ�ĳ��ƺ�: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                cout << "���ƺ�: " << car->plateNumber << endl;
                cout << "Ʒ��: " << car->brand << endl;
                cout << "�ͺ�: " << car->model << endl;
                cout << "��ɫ: " << car->color << endl;
                cout << "�볡ʱ��: " << ctime(&car->entryTime) << endl;
            }
            else {
                cout << "δ���ҵ��ó���!" << endl;
            }
            break;
        }
        case 3: {
            // ͣ��ʱ��ͳ��
            string plateNumber;
            cout << "������Ҫ���ҵĳ��ƺ�: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                time_t currentTime = time(nullptr);
                double elapsedTime = difftime(currentTime, car->entryTime);
                cout << "ͣ��ʱ�� (��): " << elapsedTime << endl;
            }
            else {
                cout << "δ���ҵ��ó���!" << endl;
            }
            break;
        }
        case 4:
            // �������˵�    
            ClearScreen();
            break;
        default:
            cout << "��Ч��ѡ�������" << endl;
        }

        if (guestModuleChoice == 4) {
            break;
        }
    }
}

int main() {
    ParkingLot parkingLot;
    int choice;
    string adminPassword = "admin";

    while (true) 
    {
        Home();

        if (!(cin >> choice)) {
            cin.clear(); // ��������־
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������Ч����
            cout << "��Ч�����룬������" << endl;
            continue; // ����ѭ�������ಿ�֣����¿�ʼ
        }

        switch (choice)
        {
        case 1:
            // ������Ϣģ��
            CarInformationModule(parkingLot);
            break;

        case 2:
            // ��ͨ�û�ģ��
            UserModule(parkingLot);
            break;

        case 3:
            // ����Ա�û�ģ��
            AdminModule(parkingLot, adminPassword);
            break;

        case 4:
            // �ο��û�ģ��
            GuestModule(parkingLot);
            break;

        case 5:
            // �˳�����
            return 0;
        }
    }
    return 0;
}

