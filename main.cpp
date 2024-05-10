#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits> // 包含这个头文件以使用numeric_limits

using namespace std;

class ParkingLot;

// 清屏函数
void ClearScreen() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/macOS
#endif
}

// 汽车基类
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

// 汽车类，继承自车辆基类
class Car : public Vehicle {
public:
    Car(string plateNumber, string brand, string model, string color)
        : Vehicle(plateNumber, brand, model, color) {}
};

// 用户基类
class User {
public:
    virtual void displayInfo() const = 0;
    virtual void processModule(ParkingLot& parkingLot) = 0;
};

// 管理员用户类，继承自用户基类
class AdminUser : public User {
private:
    string adminPassword;

public:
    AdminUser(string password) : adminPassword(password) {}

    void displayInfo() const override {
        cout << "管理员用户" << endl;
    }

    void processModule(ParkingLot& parkingLot) override {
        // 管理员模块逻辑
        // ...
        cout << "管理员模块逻辑" << endl;
    }
};

// 普通用户类，继承自用户基类
class RegularUser : public User {
public:
    void displayInfo() const override {
        cout << "普通用户" << endl;
    }

    void processModule(ParkingLot& parkingLot) override {
        // 普通用户模块逻辑
        // ...
        cout << "普通用户模块逻辑" << endl;
    }
};

// 游客用户类，继承自用户基类
class GuestUser : public User {
public:
    void displayInfo() const override {
        cout << "游客用户" << endl;
    }

    void processModule(ParkingLot& parkingLot) override {
        // 游客用户模块逻辑

        cout << "游客用户模块逻辑" << endl;
    }
};

// 停车场类
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
                cout << "汽车信息已修改" << endl;
            }
        }
        else {
            cout << "未找到具有该车牌号的汽车，无法修改信息!" << endl;
        }
    }

    void displayAllCars() {
        if (cars.empty()) {
            cout << "该停车场暂未停放任何车辆，查询信息为空！" << endl;
        }
        else {
            for (auto& car : cars) {
                cout << "车牌号: " << car.plateNumber << endl;
                cout << "品牌: " << car.brand << endl;
                cout << "型号: " << car.model << endl;
                cout << "颜色: " << car.color << endl;
                cout << "入场时间: " << ctime(&car.entryTime);
                time_t currentTime = time(nullptr);
                double elapsedTime = difftime(currentTime, car.entryTime);
                cout << "停车时长 (秒): " << elapsedTime << endl;
            }
        }
    }

    void saveToFile(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (auto& car : cars) {
                file << "车牌号: " << car.plateNumber << endl;
                file << "品牌: " << car.brand << endl;
                file << "型号: " << car.model << endl;
                file << "颜色: " << car.color << endl;
                file << "入场时间: " << ctime(&car.entryTime) << endl;
            }
            file.close();
        }
        else {
            cerr << "无法打开文件进行写入。" << endl;
        }
    }

    bool empty() {
        return cars.empty();
    }
};

void CarInformation() {
    cout << "\n" << endl;
    cout << "                                                         汽车信息模块：" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *      1. 添加汽车信息      *" << endl;
    cout << "                                                *      2. 删除汽车信息      *" << endl;
    cout << "                                                *      3. 查找汽车信息      *" << endl;
    cout << "                                                *      4. 修改汽车信息      *" << endl;
    cout << "                                                *      5. 停车时长统计      *" << endl;
    cout << "                                                *      6. 停车场信息显示    *" << endl;
    cout << "                                                *      7. 汽车信息保存      *" << endl;
    cout << "                                                *      8. 返回上一级菜单    *" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void User() {
    cout << "\n" << endl;
    cout << "                                                        普通用户模块：" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *     1. 显示汽车信息       *" << endl;
    cout << "                                                *     2. 查询汽车信息       *" << endl;
    cout << "                                                *     3. 停车时间统计       *" << endl;
    cout << "                                                *     4. 退出普通用户登录   *" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void AdminUser() {
    cout << "\n" << endl;
    cout << "                                                          管理员用户模块：" << endl;
    cout << "                                                * * * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *      1. 添加汽车信息          *" << endl;
    cout << "                                                *      2. 查询汽车信息          *" << endl;
    cout << "                                                *      3. 修改汽车信息          *" << endl;
    cout << "                                                *      4. 删除汽车信息          *" << endl;
    cout << "                                                *      5. 汽车信息统计          *" << endl;
    cout << "                                                *      6. 修改管理员密码        *" << endl;
    cout << "                                                *      7. 退出管理员用户登录    *" << endl;
    cout << "                                                * * * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void GuestUser() {
    cout << "\n" << endl;
    cout << "                                                         游客用户模块：" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *      1. 显示汽车信息       *" << endl;
    cout << "                                                *      2. 查询汽车信息       *" << endl;
    cout << "                                                *      3. 停车时间统计       *" << endl;
    cout << "                                                *      4. 返回主菜单         *" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void Home() {
    cout << "\n" << endl;
    cout << "                                                           主菜单：" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "                                                *      1. 汽车信息模块      *" << endl;
    cout << "                                                *      2. 普通用户模块      *" << endl;
    cout << "                                                *      3. 管理员用户模块    *" << endl;
    cout << "                                                *      4. 游客用户模块      *" << endl;
    cout << "                                                *      5. 退出程序          *" << endl;
    cout << "                                                * * * * * * * * * * * * * * *" << endl;
    cout << "\n" << endl;
}

void CarInformationModule(ParkingLot& parkingLot) {
    ClearScreen();
    while (true) {
        CarInformation();
        int carModuleChoice;

        if (!(cin >> carModuleChoice)) {
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃无效输入
            cout << "无效的输入，请重试" << endl;
            continue; // 跳过循环的其余部分，重新开始
        }

        switch (carModuleChoice) {
        case 1: {
            string plateNumber, brand, model, color;
            cout << "请输入车牌号: ";
            cin >> plateNumber;
            cout << "请输入品牌: ";
            cin >> brand;
            cout << "请输入型号: ";
            cin >> model;
            cout << "请输入颜色: ";
            cin >> color;
            Car car(plateNumber, brand, model, color);
            parkingLot.addCar(car);
            cout << "汽车信息已添加" << endl;
            break;
        }
        case 2: {
            string plateNumber;
            cout << "请输入要删除的车牌号: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr)
            {
                parkingLot.deleteCar(plateNumber);
                cout << "汽车信息已删除!" << endl;
            }
            else
            {
                cout << "未查询到该车辆，删除失败!";
            }
            break;
        }
        case 3: {
            string plateNumber;
            cout << "请输入要查找的车牌号: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                cout << "车牌号: " << car->plateNumber << endl;
                cout << "品牌: " << car->brand << endl;
                cout << "型号: " << car->model << endl;
                cout << "颜色: " << car->color << endl;
                cout << "入场时间: " << ctime(&car->entryTime) << endl;
            }
            else {
                cout << "未查找到该车辆!" << endl;
            }
            break;
        }
        case 4: {
            string plateNumber, brand, model, color;
            cout << "请输入要修改的车牌号: ";
            cin >> plateNumber;
            if (parkingLot.carExists(plateNumber)) {
                cout << "请输入新的品牌: ";
                cin >> brand;
                cout << "请输入新的型号: ";
                cin >> model;
                cout << "请输入新的颜色: ";
                cin >> color;
                parkingLot.modifyCar(plateNumber, brand, model, color);
            }
            else {
                cout << "未找到具有该车牌号的汽车，无法修改信息!" << endl;
            }
            break;
        }
        case 5: {
            // 计算停车时长
            string plateNumber;
            cout << "请输入要查找的车牌号: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                time_t currentTime = time(nullptr);
                double elapsedTime = difftime(currentTime, car->entryTime);
                cout << "停车时长 (秒): " << elapsedTime << endl;
            }
            else {
                cout << "未查找到该车辆!" << endl;
            }
            break;
        }
        case 6: {
            // 显示停车场所有汽车信息
            parkingLot.displayAllCars();
            break;
        }
        case 7: {
            // 保存汽车信息到文件
            string filename;
            cout << "请输入文件名: ";
            cin >> filename;
            parkingLot.saveToFile(filename);
            cout << "汽车信息已保存到文件" << endl;
            break;
        }
        case 8:
            // 返回主菜单
            ClearScreen();
            break;
        default:
            cout << "无效的选项，请重试" << endl;
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
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃无效输入
            cout << "无效的输入，请重试" << endl;
            continue; // 跳过循环的其余部分，重新开始
        }

        switch (userModuleChoice) {
        case 1:
            // 显示汽车信息
            parkingLot.displayAllCars();
            break;
        case 2: {
            // 查询汽车信息
            string plateNumber;
            cout << "请输入要查询的车牌号: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                cout << "车牌号: " << car->plateNumber << endl;
                cout << "品牌: " << car->brand << endl;
                cout << "型号: " << car->model << endl;
                cout << "颜色: " << car->color << endl;
                cout << "入场时间: " << ctime(&car->entryTime) << endl;
            }
            else {
                cout << "未查找到该车辆!" << endl;
            }
            break;
        }
        case 3: {
            // 停车时间统计
            string plateNumber;
            cout << "请输入要查找的车牌号: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                time_t currentTime = time(nullptr);
                double elapsedTime = difftime(currentTime, car->entryTime);
                cout << "停车时长 (秒): " << elapsedTime << endl;
            }
            else {
                cout << "未查找到该车辆!" << endl;
            }
            break;
        }
        case 4:
            // 返回主菜单
            ClearScreen();
            break;
        default:
            cout << "无效的选项，请重试" << endl;
        }

        if (userModuleChoice == 4) {
            break;
        }
    }
}

void AdminModule(ParkingLot& parkingLot, string& adminPassword) {
    ClearScreen();
    cout << "请输入管理员密码: ";
    string adminPasswordInput;
    cin >> adminPasswordInput;
    if (adminPasswordInput == adminPassword) {
        int adminModuleChoice;
        while (true) {
            AdminUser();

            if (!(cin >> adminModuleChoice)) {
                cin.clear(); // 清除错误标志
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃无效输入
                cout << "无效的输入，请重试" << endl;
                continue; // 跳过循环的其余部分，重新开始
            }

            switch (adminModuleChoice) {
            case 1: {
                string plateNumber, brand, model, color;
                cout << "请输入车牌号: ";
                cin >> plateNumber;
                cout << "请输入品牌: ";
                cin >> brand;
                cout << "请输入型号: ";
                cin >> model;
                cout << "请输入颜色: ";
                cin >> color;
                Car car(plateNumber, brand, model, color);
                parkingLot.addCar(car);
                cout << "汽车信息已添加" << endl;
                break;
            }
            case 2: {
                // 查询汽车信息
                string plateNumber;
                cout << "请输入要查询的车牌号: ";
                cin >> plateNumber;
                Car* car = parkingLot.findCar(plateNumber);
                if (car != nullptr) {
                    cout << "车牌号: " << car->plateNumber << endl;
                    cout << "品牌: " << car->brand << endl;
                    cout << "型号: " << car->model << endl;
                    cout << "颜色: " << car->color << endl;
                    cout << "入场时间: " << ctime(&car->entryTime) << endl;
                }
                else {
                    cout << "未查找到该车辆!" << endl;
                }
                break;
            }
            case 3: {
                string plateNumber, brand, model, color;
                cout << "请输入要修改的车牌号: ";
                cin >> plateNumber;
                if (parkingLot.carExists(plateNumber)) {
                    cout << "请输入新的品牌: ";
                    cin >> brand;
                    cout << "请输入新的型号: ";
                    cin >> model;
                    cout << "请输入新的颜色: ";
                    cin >> color;
                    parkingLot.modifyCar(plateNumber, brand, model, color);
                }
                else {
                    cout << "未找到具有该车牌号的汽车，无法修改信息!" << endl;
                }
                break;
            }
            case 4: {
                string plateNumber;
                cout << "请输入要删除的车牌号: ";
                cin >> plateNumber;
                Car* car = parkingLot.findCar(plateNumber);
                if (car != nullptr)
                {
                    parkingLot.deleteCar(plateNumber);
                    cout << "汽车信息已删除!" << endl;
                }
                else
                {
                    cout << "未查询到该车辆，删除失败!";
                }
                break;
            }


            case 5:
                // 显示停车场中所有汽车停留时长
                parkingLot.displayAllCars();
                break;
            case 6: {
                // 修改管理员密码
                string oldPassword, newPassword, newPasswordConfirm;
                cout << "请输入旧密码: ";
                cin >> oldPassword;
                if (oldPassword == adminPassword) {
                    cout << "请输入新密码: ";
                    cin >> newPassword;
                    cout << "请再次输入新密码: ";
                    cin >> newPasswordConfirm;
                    if (newPassword == newPasswordConfirm) {
                        adminPassword = newPassword;
                        cout << "管理员密码已修改" << endl;
                    }
                    else {
                        cout << "新密码前后不一致，请重试！" << endl;
                    }
                }
                else {
                    cout << "管理员密码错误！" << endl;
                }
                break;
            }
            case 7:
                // 返回主菜单
                ClearScreen();
                break;
            default:
                cout << "无效的选项，请重试" << endl;
            }

            if (adminModuleChoice == 7) {
                break;
            }
        }
    }
    else {
        cout << "管理员密码错误" << endl;
    }
}

void GuestModule(ParkingLot& parkingLot) {
    ClearScreen();
    int guestModuleChoice;
    while (true) {
        GuestUser();

        if (!(cin >> guestModuleChoice)) {
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃无效输入
            cout << "无效的输入，请重试" << endl;
            continue; // 跳过循环的其余部分，重新开始
        }

        switch (guestModuleChoice) {
        case 1:
            // 显示汽车信息
            parkingLot.displayAllCars();
            break;
        case 2: {
            // 查询汽车信息
            string plateNumber;
            cout << "请输入要查询的车牌号: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                cout << "车牌号: " << car->plateNumber << endl;
                cout << "品牌: " << car->brand << endl;
                cout << "型号: " << car->model << endl;
                cout << "颜色: " << car->color << endl;
                cout << "入场时间: " << ctime(&car->entryTime) << endl;
            }
            else {
                cout << "未查找到该车辆!" << endl;
            }
            break;
        }
        case 3: {
            // 停车时间统计
            string plateNumber;
            cout << "请输入要查找的车牌号: ";
            cin >> plateNumber;
            Car* car = parkingLot.findCar(plateNumber);
            if (car != nullptr) {
                time_t currentTime = time(nullptr);
                double elapsedTime = difftime(currentTime, car->entryTime);
                cout << "停车时长 (秒): " << elapsedTime << endl;
            }
            else {
                cout << "未查找到该车辆!" << endl;
            }
            break;
        }
        case 4:
            // 返回主菜单    
            ClearScreen();
            break;
        default:
            cout << "无效的选项，请重试" << endl;
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
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃无效输入
            cout << "无效的输入，请重试" << endl;
            continue; // 跳过循环的其余部分，重新开始
        }

        switch (choice)
        {
        case 1:
            // 汽车信息模块
            CarInformationModule(parkingLot);
            break;

        case 2:
            // 普通用户模块
            UserModule(parkingLot);
            break;

        case 3:
            // 管理员用户模块
            AdminModule(parkingLot, adminPassword);
            break;

        case 4:
            // 游客用户模块
            GuestModule(parkingLot);
            break;

        case 5:
            // 退出程序
            return 0;
        }
    }
    return 0;
}

