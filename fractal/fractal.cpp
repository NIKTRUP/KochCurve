#include <iostream>
#include <fstream>
#include <cmath>
#include "fractal.h"
#include <GLFW/glfw3.h>
using namespace std;
int main()
{
    system("chcp 1251>nul");
    int n; bool InputСheck = false;
    double coefficient = 1 , scale = 1;
    double rotation_matrixA1_A4[2][2] = { 1.0/3.0 , 0 , 0 , 1.0 / 3.0 };
	double rotation_matrixA2[2][2] = { 1.0/6.0 , -1.0/(2*sqrt(3.0)) , 1.0 / (2 * sqrt(3.0)) , 1.0 / 6.0 };
	double rotation_matrixA3[2][2] = { 1.0 / 6.0 , 1.0 / (2 * sqrt(3.0)) , -1.0 / (2 * sqrt(3.0)) , 1.0 / 6.0 };
	double stepA2[2] = { 1.0/3.0 , 0}; 
    double stepA3[2] = { 0.5 , 1.0/(2.0* sqrt(3.0)) };
    double stepA4[2] = { 2.0/3.0 ,0 };
    cout << "Введите количество итераций кривой Коха: ";
    InputCheck(InputСheck, n);
    unsigned int start_time = clock(); // начало отсчёта
    double b = pow(4.0, n) + 1.0;
    long long int* size;
    size = new long long int;
    *size = pow(4, n) + 1;
    double* Arr_x; double* Arr_y;
    Arr_x = new double[2]{ 0 , 1 };
    Arr_y = new double[2]{ 0 , 0 };
    double* Arr_out_x; double* Arr_out_y;
    Arr_out_x = new double[2]{ 0 , 1 };
    Arr_out_y = new double[2]{ 0 , 0 };
    double* Arr_calculations_x; double* Arr_calculations_y;
    cout <<"Количество точек: " << b << endl;
    CalculateKochCurve(n, Arr_x, Arr_y, Arr_out_x, Arr_out_y, Arr_calculations_x, Arr_calculations_y, rotation_matrixA1_A4, rotation_matrixA2, stepA2, rotation_matrixA3, stepA3, stepA4);
    unsigned int end_time = clock(); // конец отсчёта
    unsigned int search_time = end_time - start_time;
    cout << search_time / 1000.00 << " в секундах " << endl;// вывод в секундах 
    WriteToFile(size, Arr_out_x, Arr_out_y, b);
    delete[] Arr_x;
    delete[] Arr_y;
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(1200, 700, "Koch Curve", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        DrawKochCurve(size, Arr_out_x, Arr_out_y);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor(0.2, 0.2, 0.2, 1.0);
    }
    glfwTerminate(); 
    delete[] Arr_out_x;
    delete[] Arr_out_y;
    delete size;
}
//отрисовывает кривую коха
void DrawKochCurve(long long* size, double* Arr_out_x, double* Arr_out_y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1.0, 1.0, 1.0); 
    glLineWidth(1.0); 
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < *size; i++)
    {
        glVertex2d(1.4*Arr_out_x[i]-0.7, 2.6*Arr_out_y[i]);
    }
    glEnd();
}
//Записывает точки (и их количество) двух массивов (по x и y соответственно) в txt файл.
void WriteToFile(long long* size, double* Arr_out_x, double* Arr_out_y, double b)
{
    ofstream out("PointOutput.txt");
    if (out.is_open())
    {
        for (int i = 0; i < *size; i++) {
            out << Arr_out_x[i] << " " << Arr_out_y[i] << "\n";
        }
        out << "/ Количество точек: " << b << endl;
        cout << "Запись в файл произошла";
    }
}
// Вычисляет Кривую Коха относительно n операций
void CalculateKochCurve(int n, double*& Arr_x, double*& Arr_y, double*& Arr_out_x, double*& Arr_out_y, double*& Arr_calculations_x, double*& Arr_calculations_y, double  rotation_matrixA1_A4[2][2], double  rotation_matrixA2[2][2], double  stepA2[2], double  rotation_matrixA3[2][2], double  stepA3[2], double  stepA4[2])
{
    for (int i = 0; i < n; i++) {
        Arr_x = new double[pow(4.0, i) + 1.0]();
        Arr_y = new double[pow(4.0, i) + 1.0]();
        for (int m = 0; m < pow(4.0, i) + 1.0; m++) {
            Arr_x[m] = Arr_out_x[m];
            Arr_y[m] = Arr_out_y[m];
        }
        Arr_calculations_x = new double[pow(4, i + 1) + 1]();
        Arr_calculations_y = new double[pow(4, i + 1) + 1]();
        int end_x = _msize(Arr_x) / sizeof(double) - 1;
        int end_y = _msize(Arr_y) / sizeof(double) - 1;
        Arr_x[end_x] = 1; Arr_y[end_y] = 0;
        long long int* coefficient;
        coefficient = new long long int;
        *coefficient = pow(4, i);
        for (int j = 1, k = 1; j < pow(4, i) + 1; j++, k++) {
            Arr_calculations_x[k] = rotation_matrixA1_A4[0][0] * Arr_x[j] + rotation_matrixA1_A4[0][1] * Arr_y[j];
            Arr_calculations_y[k] = rotation_matrixA1_A4[1][0] * Arr_x[j] + rotation_matrixA1_A4[1][1] * Arr_y[j];

            Arr_calculations_x[k + 1 * (*coefficient)] = rotation_matrixA2[0][0] * Arr_x[j] + rotation_matrixA2[0][1] * Arr_y[j] + stepA2[0];
            Arr_calculations_y[k + 1 * (*coefficient)] = rotation_matrixA2[1][0] * Arr_x[j] + rotation_matrixA2[1][1] * Arr_y[j] + stepA2[1];

            Arr_calculations_x[k + 2 * (*coefficient)] = rotation_matrixA3[0][0] * Arr_x[j] + rotation_matrixA3[0][1] * Arr_y[j] + stepA3[0];
            Arr_calculations_y[k + 2 * (*coefficient)] = rotation_matrixA3[1][0] * Arr_x[j] + rotation_matrixA3[1][1] * Arr_y[j] + stepA3[1];

            Arr_calculations_x[k + 3 * (*coefficient)] = rotation_matrixA1_A4[0][0] * Arr_x[j] + rotation_matrixA1_A4[0][1] * Arr_y[j] + stepA4[0];
            Arr_calculations_y[k + 3 * (*coefficient)] = rotation_matrixA1_A4[1][0] * Arr_x[j] + rotation_matrixA1_A4[1][1] * Arr_y[j] + stepA4[1];
        }
        Arr_out_x = new double[pow(4, i + 1) + 1]();
        Arr_out_y = new double[pow(4, i + 1) + 1]();
        for (int m = 0; m < pow(4, i + 1) + 1; m++) {
            Arr_out_x[m] = Arr_calculations_x[m];
            Arr_out_y[m] = Arr_calculations_y[m];
        }
        delete[] Arr_calculations_x;
        delete[] Arr_calculations_y;
        delete coefficient;
    }
}
// Выводит в консоль все точки из массивов координат 
void ShowKochCurve(long long* size, double* Arr_out_x, double* Arr_out_y)
{
    for (int i = 0; i < *size; i++) {
        cout << Arr_out_x[i] << " " << Arr_out_y[i] << "\n";
    }
}
// проверка на входные значения
void InputCheck(bool& InputСheck, int& n)
{
    while (!InputСheck) {

        cin >> n;
        if (cin.fail()) // если предыдущее извлечение было неудачным,
        {
            cout << "Ошибка ввода! Вы ввели некорректный символ, попробуйте снова: " << endl;
            cin.clear(); // то возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        }
        else if(n>=0) { InputСheck = true; }
        else { cout << "Ошибка ввода! Порядок фрактала не может быть отрицательным, попробуйте снова: " << endl; }
    }
    InputСheck = false;
}
// проверка на входные значения
void InputCheck(bool& InputСheck, double& scale) {
    while (!InputСheck) {

        cin >> scale;
        if (cin.fail()) 
        {
            cout << "Ошибка ввода! Вы ввели некорректный символ, попробуйте снова: " << endl;
            cin.clear(); 
            cin.ignore(32767, '\n');
        }
        else if (scale >= 0) { InputСheck = true; }
        else { cout << "Ошибка ввода! Порядок фрактала не может быть отрицательным, попробуйте снова: " << endl; }
    }
    InputСheck = false;
}


