#include <iostream>
#include <iomanip> 
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// Глобальные константы для конфигурации поезда
const int NUM_COACHES = 18;
const int SEATS_PER_COACH = 36;

// Прототипы функций
void createTrain(int train[][SEATS_PER_COACH]);
void fillTrainRandomly(int train[][SEATS_PER_COACH]);
void printTrain(int train[][SEATS_PER_COACH]);
void reserveSeat(int train[][SEATS_PER_COACH]);
void freeSeat(int train[][SEATS_PER_COACH]);
int getFreeSeatsInCoach(int train[][SEATS_PER_COACH], int coachNum);
int getTotalFreeSeats(int train[][SEATS_PER_COACH]);
int getValidInput(const std::string& prompt, int minVal, int maxVal);
void clearScreen();
void showMessage(const std::string& message);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    int train[NUM_COACHES][SEATS_PER_COACH];
    int choice;

    std::cout << "=== СИСТЕМА УПРАВЛЕНИЯ БРОНИРОВАНИЕМ МЕСТ ===" << std::endl;

    // Выбор режима заполнения
    std::cout << "\nВыберите режим заполнения:" << std::endl;
    std::cout << "1 - Рандомное заполнение" << std::endl;
    std::cout << "2 - Все места пустые" << std::endl;
    std::cout << "Ваш выбор: ";
    std::cin >> choice;

    clearScreen();

    if (choice == 1)
    {
        fillTrainRandomly(train);
        showMessage("Поезд заполнен случайным образом.");
    }
    else
    {
        createTrain(train);
        showMessage("Все места установлены как пустые.");
    }

    // Основное меню
    do
    {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
        std::cout << "1 - Показать схему поезда" << std::endl;
        std::cout << "2 - Забронировать место" << std::endl;
        std::cout << "3 - Освободить место" << std::endl;
        std::cout << "4 - Количество свободных мест в вагоне" << std::endl;
        std::cout << "5 - Общее количество свободных мест" << std::endl;
        std::cout << "0 - Выход" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        clearScreen();

        switch (choice)
        {
        case 1:
            printTrain(train);
            break;
        case 2:
            reserveSeat(train);
            break;
        case 3:
            freeSeat(train);
            break;
        case 4:
        {
            int coachNum = getValidInput("Введите номер вагона", 1, NUM_COACHES);
            int freeSeats = getFreeSeatsInCoach(train, coachNum - 1);
            std::cout << "Свободных мест в вагоне " << coachNum << ": " << freeSeats << std::endl;
            break;
        }
        case 5:
        {
            int totalFree = getTotalFreeSeats(train);
            std::cout << "Общее количество свободных мест: " << totalFree << std::endl;
            break;
        }
        case 0:
            std::cout << "Выход из программы..." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
        }

        if (choice != 0)
        {
            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.ignore();
            std::cin.get();
            clearScreen();
        }

    } while (choice != 0);

    return 0;
}

void createTrain(int train[][SEATS_PER_COACH])
{
    // Инициализация всех мест как свободных (0)
    for (int i = 0; i < NUM_COACHES; i++)
    {
        for (int j = 0; j < SEATS_PER_COACH; j++)
        {
            train[i][j] = 0;
        }
    }
}

void fillTrainRandomly(int train[][SEATS_PER_COACH])
{
    // Заполнение случайными значениями 0 или 1
    for (int i = 0; i < NUM_COACHES; i++)
    {
        for (int j = 0; j < SEATS_PER_COACH; j++)
        {
            train[i][j] = rand() % 2; // 0 или 1
        }
    }
}

void printTrain(int train[][SEATS_PER_COACH])
{
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "ТЕКУЩЕЕ СОСТОЯНИЕ МЕСТ В ПОЕЗДЕ" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    // Заголовок с номерами мест
    std::cout << std::setw(14) << std::left << "Вагон\\Место";
    for (int seat = 1; seat <= SEATS_PER_COACH; seat++)
    {
        std::cout << std::setw(3) << seat;
    }
    std::cout << std::endl;

    // Вывод каждого вагона
    for (int i = 0; i < NUM_COACHES; i++)
    {
        std::cout << "Вагон " << std::setw(2) << std::left << i + 1 << "     ";
        for (int j = 0; j < SEATS_PER_COACH; j++)
        {
            if (train[i][j] == 1)
            {
                std::cout << " X "; // Занято
            }
            else
            {
                std::cout << " . "; // Свободно
            }
        }
        std::cout << std::endl;
    }
}

void reserveSeat(int train[][SEATS_PER_COACH])
{
    std::cout << "\n--- БРОНИРОВАНИЕ МЕСТА ---" << std::endl;

    int coachNum = getValidInput("Введите номер вагона", 1, NUM_COACHES) - 1;
    int seatNum = getValidInput("Введите номер места", 1, SEATS_PER_COACH) - 1;

    if (train[coachNum][seatNum] == 1)
    {
        std::cout << "ОШИБКА: Это место уже занято!" << std::endl;
    }
    else
    {
        train[coachNum][seatNum] = 1;
        std::cout << "Место успешно забронировано! Вагон " << coachNum + 1
            << ", Место " << seatNum + 1 << std::endl;
    }
}

void freeSeat(int train[][SEATS_PER_COACH])
{
    std::cout << "\n--- ОСВОБОЖДЕНИЕ МЕСТА ---" << std::endl;

    int coachNum = getValidInput("Введите номер вагона", 1, NUM_COACHES) - 1;
    int seatNum = getValidInput("Введите номер места", 1, SEATS_PER_COACH) - 1;

    if (train[coachNum][seatNum] == 0)
    {
        std::cout << "ОШИБКА: Это место и так свободно!" << std::endl;
    }
    else
    {
        train[coachNum][seatNum] = 0;
        std::cout << "Место успешно освобождено! Вагон " << coachNum + 1
            << ", Место " << seatNum + 1 << std::endl;
    }
}

int getFreeSeatsInCoach(int train[][SEATS_PER_COACH], int coachNum)
{
    int count = 0;
    for (int j = 0; j < SEATS_PER_COACH; j++)
    {
        if (train[coachNum][j] == 0) {
            count++;
        }
    }
    return count;
}

int getTotalFreeSeats(int train[][SEATS_PER_COACH])
{
    int total = 0;
    for (int i = 0; i < NUM_COACHES; i++)
    {
        total += getFreeSeatsInCoach(train, i);
    }
    return total;
}

int getValidInput(const std::string& prompt, int minVal, int maxVal)
{
    int value;
    while (true)
    {
        std::cout << prompt << " (" << minVal << "-" << maxVal << "): ";
        std::cin >> value;

        if (value >= minVal && value <= maxVal)
        {
            return value;
        }
        else
        {
            std::cout << "ОШИБКА: Введите число от " << minVal << " до " << maxVal << "!" << std::endl;
        }
    }
}

void clearScreen()
{
    system("cls");
}

void showMessage(const std::string& message)
{
    std::cout << message << std::endl;
    Sleep(1500);
}