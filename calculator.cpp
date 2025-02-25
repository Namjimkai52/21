#include <windows.h>
#include <stdio.h>
HWND hoo, hee, hum;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    char T1[50], T2[50];
    double Num1, Num2, ANS;
    char ANST[100];
    
    switch (Message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        case WM_CREATE:
            hoo = CreateWindow("STATIC", "Please input your numbers:", WS_CHILD | WS_VISIBLE | SS_CENTER,
                               25, 20, 200, 20, hwnd, NULL, NULL, NULL);
            hee = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                               25, 50, 200, 20, hwnd, NULL, NULL, NULL);
            hum = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                               25, 80, 200, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE, 25, 120, 40, 25, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE, 75, 120, 40, 25, hwnd, (HMENU)2, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE, 125, 120, 40, 25, hwnd, (HMENU)3, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE, 175, 120, 40, 25, hwnd, (HMENU)4, NULL, NULL);
            break;
        
        case WM_COMMAND:
            GetWindowText(hee, T1, 50);
            GetWindowText(hum, T2, 50);
            Num1 = atof(T1);
            Num2 = atof(T2);
            
            switch (wParam) {
                case 1: ANS = Num1 + Num2; break;
                case 2: ANS = Num1 - Num2; break;
                case 3: ANS = Num1 * Num2; break;
                case 4:
                    if (Num2 == 0) {
                        MessageBox(hwnd, "Undefined", "Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                    ANS = Num1 / Num2;
                    break;
                default:
                    return 0;
            }
            sprintf(ANST, "Result: %.2f", ANS);
            MessageBox(hwnd, ANST, "Result", MB_OK);
            break;
        
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { 0 };
    HWND hwnd;
    MSG msg;
    
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = "CalculatorWindow";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    hwnd = CreateWindowEx(0, "CalculatorWindow", "My Calculator",
                           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                           CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
                           NULL, NULL, hInstance, NULL);
    
    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
