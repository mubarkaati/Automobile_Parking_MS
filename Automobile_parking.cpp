#include <bits/stdc++.h>
using namespace std;
class EarnedMoney
{
private:
    int carType;
    int busType;
    int trcukType;
    int bikeType;
    int cycleType;
    int total;

public:
    EarnedMoney()
    {
        this->carType = 0;
        this->busType = 0;
        this->trcukType = 0;
        this->bikeType = 0;
        this->cycleType = 0;
        this->total = 0;
    }
    void setEarnedMoney(int carType, int busType, int trcukType, int bikeType, int cycleType, int total)
    {
        this->carType = carType;
        this->busType = busType;
        this->trcukType = trcukType;
        this->bikeType = bikeType;
        this->cycleType = cycleType;
        this->total = total;
    }
    void showEarnedMoney()
    {
        cout << "\n--------------------------------------------------------------\n";
        cout << setw(10) << "Car|" << setw(10) << "Bus|" << setw(10) << "Truck|" << setw(10) << "Bike|" << setw(10) << "Cycle|" << setw(10) << "Total|";
        cout << "\n--------------------------------------------------------------\n";
        cout << setw(9) << this->carType << "|" << setw(9) << this->busType << "|" << setw(9) << this->trcukType << "|" << setw(9) << this->bikeType << "|" << setw(9) << this->cycleType << "|" << setw(9) << this->total << "|";
        cout << "\n--------------------------------------------------------------\n";
    }
    void getAllEarnedMoney();
    friend void addTwoMoney(EarnedMoney, EarnedMoney &);
};
void EarnedMoney::getAllEarnedMoney()
{
    ifstream fin;
    fin.open("aaEarnedMonry.txt", ios_base::in | ios_base::binary);
    if (!fin)
    {
        cout << "\nFile Not Found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
    }
}
void addTwoMoney(EarnedMoney oldMoney, EarnedMoney &newMoney)
{
    newMoney.carType += oldMoney.carType;
    newMoney.busType += oldMoney.busType;
    newMoney.trcukType += oldMoney.trcukType;
    newMoney.bikeType += oldMoney.bikeType;
    newMoney.cycleType += oldMoney.cycleType;
    newMoney.total += oldMoney.total;
}
class VehicleType
{
private:
    char vehicleTypeName[50];

public:
    VehicleType()
    {
        strcpy(vehicleTypeName, "Vehicle");
    }
    void setVehivleType(EarnedMoney &earnedMoney)
    {
        while (1)
        {
            cout << "\nSelect Vehicle Type:";
            cout << "\n1. Car  2. Bus  3. Truck  4. Bike  5. Cycle\n";
            int vehicleType;
            cin >> vehicleType;
            if (vehicleType == 1)
            {
                strcpy(this->vehicleTypeName, "Car");
                earnedMoney.setEarnedMoney(100, 0, 0, 0, 0, 100);
                break;
            }
            else if (vehicleType == 2)
            {
                strcpy(vehicleTypeName, "Bus");
                earnedMoney.setEarnedMoney(0, 200, 0, 0, 0, 200);
                break;
            }
            else if (vehicleType == 3)
            {
                strcpy(vehicleTypeName, "Truck");
                earnedMoney.setEarnedMoney(0, 0, 400, 0, 0, 400);
                break;
            }
            else if (vehicleType == 4)
            {
                strcpy(vehicleTypeName, "Bike");
                earnedMoney.setEarnedMoney(0, 0, 0, 50, 0, 50);
                break;
            }
            else if (vehicleType == 5)
            {
                strcpy(vehicleTypeName, "Cycle");
                earnedMoney.setEarnedMoney(0, 0, 0, 0, 20, 20);
                break;
            }
            else
            {
                cout << "\nInvalid Choice:";
            }
        }
    }
    void showVehicleType() { cout << vehicleTypeName << "  "; }
};
class Vehicle : public VehicleType
{
private:
    int vehicleNo;
    char description[100];
    char createdBy[50];
    char createdDateTime[50];
    EarnedMoney earnedMoney;

public:
    Vehicle()
    {
        this->vehicleNo = 0;
        strcpy(this->description, "default");
        time_t tt;
        time(&tt);
        strcpy(this->createdDateTime, asctime(localtime(&tt)));
    }
    void setVehicle()
    {
        cout << "\nEnter The Vehicle Number: ";
        cin >> vehicleNo;
        cin.ignore();
        cout << "\nEnter The Vehicle Description: ";
        cin.getline(description, 100);
        setVehivleType(earnedMoney);
        time_t tt;
        time(&tt);
        strcpy(createdDateTime, asctime(localtime(&tt)));
    }
    void showVehicle()
    {
        cout << vehicleNo << "  ";
        cout << description << "  ";
        showVehicleType();
        cout << createdDateTime << endl;
    }
    void addVehicle();
    void getAllVehicleList();
    void deleteVehicle(int vno);
};
void Vehicle::addVehicle()
{
    ofstream fout;
    fout.open("aaVehivleData.txt", ios_base::app | ios_base::binary);
    fout.write((char *)this, sizeof(*this));
    fout.close();

    EarnedMoney em;
    em.getAllEarnedMoney();
    addTwoMoney(em, this->earnedMoney);
    fout.open("aaEarnedMonry.txt", ios_base::out | ios_base::binary);
    fout.write((char *)(&this->earnedMoney), sizeof(this->earnedMoney));
    fout.close();
    cout << "\nRecord Added Successfully\n";
}
void Vehicle::getAllVehicleList()
{
    ifstream fin;
    int nor = 0;
    fin.open("aaVehivleData.txt", ios_base::in | ios_base::binary);
    if (!fin)
    {
        cout << "\nFile Not Found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            this->showVehicle();
            nor++;
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        if (nor == 0)
        {
            cout << "\nFile Has No Record:";
        }
    }
}
void Vehicle::deleteVehicle(int vno)
{
    ifstream fin;
    ofstream fout;
    int flag = 0;
    fin.open("aaVehivleData.txt", ios_base::in | ios_base::binary);
    if (!fin)
    {
        cout << "\nFile Not Found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        fout.open("aaTempVehivleData.txt", ios_base::out | ios_base::binary);
        while (!fin.eof())
        {
            if (this->vehicleNo == vno)
            {
                flag = 1;
            }
            else
            {
                fout.write((char *)this, sizeof(*this));
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        if (flag == 0)
        {
            cout << "\nRecord Not Found: Hence Can Not delete";
            remove("aaTempVehivleData.txt");
        }
        else
        {
            cout << "\nRecord Deleted:";
            remove("aaVehivleData.txt");
            rename("aaTempVehivleData.txt", "aaVehivleData.txt");
        }
    }
}
int menu()
{
    int ch;
    printf("\n1. Add Vehicle");
    printf("\n2. Delete Vehicle");
    printf("\n3. List All Vehicle");
    printf("\n4. Check Earned Money");
    printf("\n5. Exit");
    printf("\nEnter Your Choice: ");
    scanf("%d", &ch);
    return (ch);
}
int main()
{
    Vehicle vehicle;
    EarnedMoney earnedMoney;
    int breakInfiniteloop = 0, vno;
    while (1)
    {
        switch (menu())
        {
        case 1:
            vehicle.setVehicle();
            vehicle.addVehicle();
            break;
        case 2:
            cout << "\nEnter The Vehicle Number To Deleted: ";
            cin >> vno;
            vehicle.deleteVehicle(vno);
            break;
        case 3:
            vehicle.getAllVehicleList();
            break;
        case 4:
            earnedMoney.getAllEarnedMoney();
            earnedMoney.showEarnedMoney();
            break;
        case 5:
            breakInfiniteloop = 1;
            break;
        default:
            cout << "\nInvalid Choice:";
        }
        if (breakInfiniteloop == 1)
        {
            break;
        }
    }
    return 0;
}
