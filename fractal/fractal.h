#pragma once
void InputCheck(bool& Input—heck, int& n);
void InputCheck(bool& Input—heck, double& scale);
void ShowKochCurve(long long* size, double* Arr_out_x, double* Arr_out_y);

void CalculateKochCurve(int n, double*& Arr_x, double*& Arr_y, double*& Arr_out_x, double*& Arr_out_y, double*& Arr_calculations_x, double*& Arr_calculations_y, double  rotation_matrixA1_A4[2][2], double  rotation_matrixA2[2][2], double  stepA2[2], double  rotation_matrixA3[2][2], double  stepA3[2], double  stepA4[2]);

void WriteToFile(long long* size, double* Arr_out_x, double* Arr_out_y, double b);

void ZoomIn(long long* size, double* Arr_out_x, double scale, double* Arr_out_y);

void DrawKochCurve(long long* size, double* Arr_out_x, double* Arr_out_y);


