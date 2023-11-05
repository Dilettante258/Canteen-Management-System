#include <windows.h>
#include <shellscalingapi.h>
#include <stdio.h>
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Shcore.lib")

#define IDC_LOGIN_BUTTON 1001
#define IDC_USERNAME_EDIT 1002
#define IDC_PASSWORD_EDIT 1003
#define IDC_REGISTER_BUTTON 1004
#define IDC_MENU_BUTTON  1005
#define IDC_STATISTICS_BUTTON 1006
#define IDC_LOGOUT_BUTTON 1007
#define ID_BUTTON 23232
#define ID_COMBOBOX 23233


LRESULT CALLBACK LoginWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AdminWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK StuWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK RegWndProc(HWND, UINT, WPARAM, LPARAM);//注册
LRESULT CALLBACK RecWndProc(HWND, UINT, WPARAM, LPARAM);//充值
LRESULT CALLBACK RplWndProc(HWND, UINT, WPARAM, LPARAM);//挂失
LRESULT CALLBACK UnRplWndProc(HWND, UINT, WPARAM, LPARAM);//解除挂失
LRESULT CALLBACK LgoWndProc(HWND, UINT, WPARAM, LPARAM);//注销
LRESULT CALLBACK EdsWndProc(HWND, UINT, WPARAM, LPARAM);//录入菜肴
LRESULT CALLBACK LdsWndProc(HWND, UINT, WPARAM, LPARAM);//菜肴列表
LRESULT CALLBACK MdsWndProc(HWND, UINT, WPARAM, LPARAM);//菜肴信息修改
LRESULT CALLBACK DdsWndProc(HWND, UINT, WPARAM, LPARAM);//删除菜肴
LRESULT CALLBACK SrdWndProc(HWND, UINT, WPARAM, LPARAM);//菜肴排序
LRESULT CALLBACK SpsWndProc(HWND, UINT, WPARAM, LPARAM);//消费情况查询
LRESULT CALLBACK CdsWndProc(HWND, UINT, WPARAM, LPARAM);//

//按钮打印栏目
#define MAX_SUB_BUTTONS 6

HWND subButtons[MAX_SUB_BUTTONS];
HWND hEdit1, hEdit2, hEdit3;
int subButtonCount = 0;
int choice = 0;
void CreateSubButtons(HWND hWnd, char* text)
{
    int i = subButtonCount;
    subButtons[i] = CreateWindow("button", text, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 50 + i * 50, 200, 30, hWnd, (HMENU)i, NULL, NULL);
    subButtonCount++;
}

void ClearSubButtons()
{
    for (int i = 0; i < subButtonCount; i++)
    {
        DestroyWindow(subButtons[i]);
    }
    subButtonCount = 0;
}
// 声明按钮句柄
HWND hLoginBtn, hCardRegBtn, hChargeBtn, hMenuBtn, hStatBtn, hLogoutBtn, hOrdBtn, hBaIqBtn, hConIqBtn;
// 全局变量
HWND g_hWndLogin, g_hWndMain, g_hWndSub;
char _Username[256], _Password[256];

void record(LVITEM lvItem, HWND hListView, int line, char *a,char *b, char *c){
    lvItem.iItem = line;
    lvItem.iSubItem = 0;
    lvItem.pszText = a;
    ListView_InsertItem(hListView, &lvItem);
    ListView_SetItemText(hListView, line, 0, a);
    ListView_SetItemText(hListView, line, 1, b);
    ListView_SetItemText(hListView, line, 2, c);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 创建登录窗口
    WNDCLASS wcLogin = { 0 };
    wcLogin.lpfnWndProc = LoginWndProc;
    wcLogin.hInstance = hInstance;
    wcLogin.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcLogin.lpszClassName = "LoginClass";
    RegisterClass(&wcLogin);

    g_hWndLogin = CreateWindow("LoginClass", "食堂管理系统登录", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);

    // 消息循环
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK LoginWndProc(HWND hWndL, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

        case WM_CREATE:
        {
            // 创建控件
            HWND hRadioButton1 = CreateWindow("BUTTON", "管理员", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 50, 0, 100, 50, hWndL, (HMENU)1, NULL, NULL);
            HWND hRadioButton2 = CreateWindow("BUTTON", "学生", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_DEFPUSHBUTTON, 200, 0, 100, 50, hWndL, (HMENU)2 , NULL, NULL);
            SetFocus(GetDlgItem(hWndL, 2));
            CreateWindow("STATIC", "用户名：", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWndL, NULL, NULL, NULL);
            CreateWindow("STATIC", "密码：", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWndL, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 150, 30, hWndL, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 150, 100, 150, 30, hWndL, NULL, NULL, NULL);
            CreateWindow("BUTTON", "登录", WS_VISIBLE | WS_CHILD, 150, 150, 100, 30, hWndL, (HMENU)IDC_LOGIN_BUTTON, NULL, NULL);
        }
            break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_LOGIN_BUTTON:
                {
                    // 获取用户名和密码
                    GetWindowText(hEdit1,&_Username,sizeof(_Username));
                    GetWindowText(hEdit2,&_Password,sizeof(_Password));
                    if (IsDlgButtonChecked(hWndL, 1) == BST_CHECKED)
                    {
                        // 创建主窗口
                        WNDCLASS wcMain = { 0 };
                        wcMain.lpfnWndProc = AdminWndProc;
                        wcMain.hInstance = GetModuleHandle(NULL);
                        wcMain.hbrBackground = (HBRUSH)(COLOR_WINDOW);
                        wcMain.lpszClassName = "AdminClass";
                        RegisterClass(&wcMain);

                        g_hWndMain = CreateWindow("AdminClass", "管理员模块", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, wcMain.hInstance, NULL);
                        // 隐藏登录窗口
                        ShowWindow(hWndL, SW_HIDE);
                    }
                    else if (IsDlgButtonChecked(hWndL, 2) == BST_CHECKED)
                    {
                        // 创建主窗口
                        WNDCLASS wcMain = { 0 };
                        wcMain.lpfnWndProc = StuWndProc;
                        wcMain.hInstance = GetModuleHandle(NULL);
                        wcMain.hbrBackground = (HBRUSH)(COLOR_WINDOW);
                        wcMain.lpszClassName = "StuClass";
                        RegisterClass(&wcMain);

                        g_hWndMain = CreateWindow("StuClass", "学生模块", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 325, 350, NULL, NULL, wcMain.hInstance, NULL);
                        // 隐藏登录窗口
                        ShowWindow(hWndL, SW_HIDE);
                    }
                    // 验证用户名和密码是否正确
                    if ((strcmp(_Username, "") == 0 )&&(strcmp(_Password, "") == 0))
                    {
                        ;
                    }
                    else if ((strcmp(_Username, "") != 0 )&&(strcmp(_Password, "") != 0))
                    {
                        ;
                    }
                    else
                    {
                        MessageBox(hWndL, "用户名或密码错误！", "错误", MB_OK | MB_ICONERROR);
                    }
                }
                    break;
            }
        }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWndL, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK AdminWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            // 创建控件
            hCardRegBtn = CreateWindow("BUTTON", "就餐卡操作", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd,(HMENU) IDC_REGISTER_BUTTON, NULL, NULL);
            hMenuBtn = CreateWindow("BUTTON", "菜单管理", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, (HMENU) IDC_MENU_BUTTON, NULL, NULL);
            hStatBtn = CreateWindow("BUTTON", "统计查询", WS_VISIBLE | WS_CHILD, 50, 150, 100, 30, hWnd, (HMENU) IDC_STATISTICS_BUTTON, NULL, NULL);
            hLogoutBtn = CreateWindow("BUTTON", "注销登录", WS_VISIBLE | WS_CHILD, 50, 200, 100, 30, hWnd, (HMENU) IDC_LOGOUT_BUTTON, NULL, NULL);
            break;

        case WM_COMMAND: {

            //处理按钮点击事件
            if (lParam == (LPARAM) hCardRegBtn) {
                ClearSubButtons();
                choice = 1;
                // 显示新的按钮
                CreateSubButtons(hWnd, "注册");
                CreateSubButtons(hWnd, "充值");
                CreateSubButtons(hWnd, "挂失");
                CreateSubButtons(hWnd, "解挂");
                CreateSubButtons(hWnd, "注销");
                CreateSubButtons(hWnd, "返回");
            } else if (lParam == (LPARAM) hMenuBtn) {
                ClearSubButtons();
                choice = 2;
                /* 显示新的按钮 */
                CreateSubButtons(hWnd, "录入菜品");
                CreateSubButtons(hWnd, "菜品列表");
                CreateSubButtons(hWnd, "修改菜品");
                CreateSubButtons(hWnd, "删除菜品");
                CreateSubButtons(hWnd, "返回");
            } else if (lParam == (LPARAM) hStatBtn) {
                ClearSubButtons();
                choice = 3;
                /* 显示新的按钮 */
                CreateSubButtons(hWnd, "菜品排行");
                CreateSubButtons(hWnd, "统计个人");
                CreateSubButtons(hWnd, "统计菜品");
                CreateSubButtons(hWnd, "返回");
            }
            else if (LOWORD(wParam) == 0) {
                if (choice == 1){
                    WNDCLASS wcSub = { 0 };
                    wcSub.lpfnWndProc = RegWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH)(COLOR_WINDOW);
                    wcSub.lpszClassName = "RegSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("RegSubClass", "注册", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 2){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = EdsWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "EdsSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("EdsSubClass", "菜品录入", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 3){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = SrdWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "SrdSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("SrdSubClass", "菜肴排序", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);

                }
            }
            else if (LOWORD(wParam) == 1) {
                if (choice == 1) {
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = RecWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "RecSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("RecSubClass", "充值", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 2){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = LdsWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "LdsSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("LdsSubClass", "菜肴列表", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 3){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = SpsWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "SpsSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("SpsSubClass", "菜肴列表", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }

            }
            else if (LOWORD(wParam) == 2) {
                if (choice == 1){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = RplWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "RplSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("RplSubClass", "挂失", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 2){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = MdsWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "MdsSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("MdsSubClass", "修改菜品", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 3){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = CdsWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "CdsSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("CdsSubClass", "修改菜品", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
            }
            else if (LOWORD(wParam) == 3) {
                if (choice == 1){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = UnRplWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "UnRplSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("UnRplSubClass", "解挂", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 2){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = DdsWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "DdsSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("DdsSubClass", "删除菜品", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 3)
                    ClearSubButtons();
            }
            else if (LOWORD(wParam) == 4) {
                if (choice == 1){
                    WNDCLASS wcSub = {0};
                    wcSub.lpfnWndProc = LgoWndProc;
                    wcSub.hInstance = GetModuleHandle(NULL);
                    wcSub.hbrBackground = (HBRUSH) (COLOR_WINDOW);
                    wcSub.lpszClassName = "LgoSubClass";
                    RegisterClass(&wcSub);
                    g_hWndSub = CreateWindow("LgoSubClass", "注销", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 400, 300, NULL, NULL, wcSub.hInstance, NULL);
                }
                if (choice == 2)
                    ClearSubButtons();
            }
            else if (LOWORD(wParam) == 5) {
                if (choice == 1)
                    ClearSubButtons();
            }
            switch (LOWORD(wParam)) {
                case IDC_LOGOUT_BUTTON: {
                    // 显示登录窗口并销毁主窗口
                    ShowWindow(g_hWndLogin, SW_SHOW);
                    DestroyWindow(hWnd);
                }
                    break;
            }
        }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK StuWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            // 创建控件
            hOrdBtn = CreateWindow("BUTTON", "点餐", WS_VISIBLE | WS_CHILD, 100, 50, 100, 30, hWnd,(HMENU) 3001, NULL, NULL);
            hBaIqBtn = CreateWindow("BUTTON", "余额查询", WS_VISIBLE | WS_CHILD, 100, 100, 100, 30, hWnd, (HMENU) 3002, NULL, NULL);
            hConIqBtn = CreateWindow("BUTTON", "消费记录查询", WS_VISIBLE | WS_CHILD, 100, 150, 100, 30, hWnd, (HMENU) 3003, NULL, NULL);
            hLogoutBtn = CreateWindow("BUTTON", "注销登录", WS_VISIBLE | WS_CHILD, 100, 200, 100, 30, hWnd, (HMENU) 3004, NULL, NULL);
            break;

        case WM_COMMAND: {

            //处理按钮点击事件
            if (lParam == (LPARAM) hOrdBtn) {
                ;
            } else if (lParam == (LPARAM) hBaIqBtn) {
                int a;
                char buffer[10];

                sprintf(buffer, "当前余额%d元", a);
                MessageBox(NULL, buffer, "提示", MB_OK);
            } else if (lParam == (LPARAM) hConIqBtn) {
                ;
            }
            else if (lParam == (LPARAM) hLogoutBtn) {
                // 销毁主窗口
                DestroyWindow(hWnd);

            }
        }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK RegWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
        case WM_CREATE:
        {
            // 创建控件
            CreateWindow("STATIC", "用户名：", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "密码：", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "金额：", WS_VISIBLE | WS_CHILD, 50, 150, 100, 30, hWnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 150, 100, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit3 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 150, 150, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "确认", WS_VISIBLE | WS_CHILD, 150, 200, 100, 30, hWnd, (HMENU)2001, NULL, NULL);
        }
            break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 2001:
                {
                    char cardNumber[100];
                    char Password[100];
                    char balance[100];

                    GetWindowText(hEdit1,&cardNumber,sizeof(cardNumber));
                    GetWindowText(hEdit2,&Password,sizeof(Password));
                    GetWindowText(hEdit3,&balance,sizeof(balance));
                    //regist(cardNumber,name,balance);
                    if ((strcmp(_Username, "") == 0 )&&(strcmp(_Password, "") == 0))
                    {
                        MessageBox(NULL, "注册成功！", "提示", MB_OK);
                        // 隐藏登录窗口
                        ShowWindow(hWnd, SW_HIDE);
                    }
                    else
                    {
                        MessageBox(hWnd, "错误！", "错误", MB_OK | MB_ICONERROR);
                    }
                }
                    break;
            }
        }
            break;


        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK RecWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
        case WM_CREATE:
        {
            // 创建控件
            CreateWindow("STATIC", "用户名：", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "金额：", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 100, 150, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "确认", WS_VISIBLE | WS_CHILD, 150, 150, 100, 30, hWnd, (HMENU)2002, NULL, NULL);
        }
            break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 2002:
                {
                    char cardNumber[100];
                    char balance[100];

                    GetWindowText(hEdit1,&cardNumber,sizeof(cardNumber));
                    GetWindowText(hEdit2,&balance,sizeof(balance));
                    //regist(cardNumber,name,balance);
                    if ((strcmp(_Username, "") == 0 )&&(strcmp(_Password, "") == 0))
                    {
                        MessageBox(NULL, "充值成功！", "提示", MB_OK);
                        // 隐藏登录窗口
                        ShowWindow(hWnd, SW_HIDE);
                    }
                    else
                    {
                        MessageBox(hWnd, "错误！", "错误", MB_OK | MB_ICONERROR);
                    }
                }
                    break;
            }
        }
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK RplWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            // 创建控件
            CreateWindow("STATIC", "用户名：", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "密码：", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 150, 100, 150, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "确认", WS_VISIBLE | WS_CHILD, 150, 150, 100, 30, hWnd, (HMENU)2003, NULL, NULL);
        }
            break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 2003:
                {
                    char cardNumber[100];
                    char Password[100];

                    GetWindowText(hEdit1,&cardNumber,sizeof(cardNumber));
                    GetWindowText(hEdit2,&Password,sizeof(Password));
                    //regist(cardNumber,name,balance);
                    if ((strcmp(_Username, "") == 0 )&&(strcmp(_Password, "") == 0))
                    {
                        MessageBox(NULL, "挂失成功！", "提示", MB_OK);
                        // 隐藏登录窗口
                        ShowWindow(hWnd, SW_HIDE);
                    }
                    else
                    {
                        MessageBox(hWnd, "错误！", "错误", MB_OK | MB_ICONERROR);
                    }
                }
                    break;
            }
        }
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK UnRplWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            // 创建控件
            CreateWindow("STATIC", "用户名：", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "密码：", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER| ES_PASSWORD, 150, 100, 150, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "确认", WS_VISIBLE | WS_CHILD, 150, 150, 100, 30, hWnd, (HMENU)2004, NULL, NULL);
        }
            break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 2004:
                {
                    char cardNumber[100];
                    char Password[100];

                    GetWindowText(hEdit1,&cardNumber,sizeof(cardNumber));
                    GetWindowText(hEdit2,&Password,sizeof(Password));

                    //regist(cardNumber,name,balance);
                    if ((strcmp(_Username, "") == 0 )&&(strcmp(_Password, "") == 0))
                    {
                        MessageBox(NULL, "解除挂失成功！", "提示", MB_OK);
                        // 隐藏登录窗口
                        ShowWindow(hWnd, SW_HIDE);
                    }
                    else
                    {
                        MessageBox(hWnd, "错误！", "错误", MB_OK | MB_ICONERROR);
                    }
                }
                    break;
            }
        }
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK LgoWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            // 创建控件
            CreateWindow("STATIC", "用户名：", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "密码：", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER| ES_PASSWORD, 150, 100, 150, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "确认", WS_VISIBLE | WS_CHILD, 150, 150, 100, 30, hWnd, (HMENU)2003, NULL, NULL);
        }
            break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 2003:
                {
                    char cardNumber[100];
                    char Password[100];

                    GetWindowText(hEdit1,&cardNumber,sizeof(cardNumber));
                    GetWindowText(hEdit2,&Password,sizeof(Password));
                    //regist(cardNumber,name,balance);
                    if ((strcmp(_Username, "") == 0 )&&(strcmp(_Password, "") == 0))
                    {
                        MessageBox(NULL, "注销成功！", "提示", MB_OK);
                        // 隐藏登录窗口
                        ShowWindow(hWnd, SW_HIDE);
                    }
                    else
                    {
                        MessageBox(hWnd, "错误！", "错误", MB_OK | MB_ICONERROR);
                    }
                }
                    break;
            }
        }
            break;


        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK EdsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            // 创建控件
            CreateWindow("STATIC", "名称：", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "价格：", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 100, 150, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "确认", WS_VISIBLE | WS_CHILD, 150, 150, 100, 30, hWnd, (HMENU)2001, NULL, NULL);
        }
            break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 2001:
                {
                    char DNumber[100];
                    char DName[100];
                    char balance[100];

                    GetWindowText(hEdit2,&DName,sizeof(DName));
                    GetWindowText(hEdit3,&balance,sizeof(balance));
                    //regist(cardNumber,name,balance);
                    if ((strcmp(_Username, "") == 0 )&&(strcmp(_Password, "") == 0))
                    {
                        MessageBox(NULL, "菜品修改成功！", "提示", MB_OK);
                        // 隐藏登录窗口
                        ShowWindow(hWnd, SW_HIDE);
                    }
                    else
                    {
                        MessageBox(hWnd, "错误！", "错误", MB_OK | MB_ICONERROR);
                    }
                }
                    break;
            }
        }
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK LdsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hListView;
    switch (message) {
        case WM_CREATE:
            // 初始化 ListView 控件
            InitCommonControlsEx(NULL);

            // 创建 ListView 控件
            hListView = CreateWindow(WC_LISTVIEW, "", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 600, 400, hWnd, NULL, NULL, NULL);

            // 设置 ListView 列表视图
            ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

            // 添加 ListView 列表头
            LVCOLUMN lvColumn = {0};
            lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
            lvColumn.cx = 100;
            lvColumn.pszText = "名称";
            ListView_InsertColumn(hListView, 0, &lvColumn);

            lvColumn.cx = 100;
            lvColumn.pszText = "价格/元";
            ListView_InsertColumn(hListView, 1, &lvColumn);

            lvColumn.cx = 100;
            lvColumn.pszText = "备注";
            ListView_InsertColumn(hListView, 2, &lvColumn);


            // 添加 ListView 行数据
            LVITEM lvItem = {0};
            record(lvItem, hListView, 0, "茶", "29", "");
            record(lvItem, hListView, 1, "饭", "92", "");
            break;


        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }
    return 0;
}

LRESULT CALLBACK MdsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
        case WM_CREATE:
        {
            // 创建控件
            CreateWindow("STATIC", "编号：", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "名称：", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "价格：", WS_VISIBLE | WS_CHILD, 50, 150, 100, 30, hWnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 100, 150, 30, hWnd, NULL, NULL, NULL);
            hEdit3 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 150, 150, 30, hWnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "确认", WS_VISIBLE | WS_CHILD, 150, 200, 100, 30, hWnd, (HMENU)2001, NULL, NULL);
        }
            break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 2001:
                {
                    char DNumber[100];
                    char DName[100];
                    char balance[100];

                    GetWindowText(hEdit1,&DNumber,sizeof(DNumber));
                    GetWindowText(hEdit2,&DName,sizeof(DName));
                    GetWindowText(hEdit3,&balance,sizeof(balance));
                    //regist(cardNumber,name,balance);
                    if ((strcmp(_Username, "") == 0 )&&(strcmp(_Password, "") == 0))
                    {
                        MessageBox(NULL, "菜品修改成功！", "提示", MB_OK);
                        // 隐藏登录窗口
                        ShowWindow(hWnd, SW_HIDE);
                    }
                    else
                    {
                        MessageBox(hWnd, "错误！", "错误", MB_OK | MB_ICONERROR);
                    }
                }
                    break;
            }
        }
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}


LRESULT CALLBACK DdsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInst;
    HWND hComboBox;
    char *Name[] = {"茄子", "B", "C"};
    switch(message)
    {
        case WM_CREATE:{
            HWND hComboBox = CreateWindowEx(0, "COMBOBOX", NULL,
                                            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
                                            10, 10, 200, 100,
                                            hWnd, (HMENU)ID_COMBOBOX, hInst, NULL);
            // 添加一些选项到ComboBox控件

            int len = sizeof(Name) / sizeof(Name[0]);
            for (int i = 0; i < len; i++)
                SendMessage(hComboBox,CB_ADDSTRING ,0 ,(LPARAM)Name[i]);
            // 创建一个Button控件
            HWND hButton = CreateWindowEx(0,"BUTTON","确定",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,220 ,10 ,100 ,24 ,hWnd,(HMENU)ID_BUTTON,hInst,NULL);}
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_BUTTON:{
                    // 获取ComboBox控件的当前选择项的索引
                    int index = SendMessage(GetDlgItem(hWnd,ID_COMBOBOX),CB_GETCURSEL ,0 ,0);
                    // 如果有选择的项
                    if (index != CB_ERR)
                    {
                        char *text[20];
                        char *buffer[40];
                        // 获取选择的项的内容
                        //SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)text);
                        // 打印或处理内容
                        sprintf(buffer, "菜肴%s已删除。", Name[index]);
                        MessageBox(NULL,buffer,"通知",MB_OK|MB_ICONINFORMATION);break;
                    }
                    else
                    {
                        printf("No item selected.\n");
                    }
                }
                    break;
            }
            break;
        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}


LRESULT CALLBACK SrdWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hListView;
    switch (message) {
        case WM_CREATE:
            // 初始化 ListView 控件
            InitCommonControlsEx(NULL);

            // 创建 ListView 控件
            hListView = CreateWindow(WC_LISTVIEW, "", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 600, 400, hWnd, NULL, NULL, NULL);

            // 设置 ListView 列表视图
            ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

            // 添加 ListView 列表头
            LVCOLUMN lvColumn = {0};
            lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
            lvColumn.cx = 100;
            lvColumn.pszText = "名称";
            ListView_InsertColumn(hListView, 0, &lvColumn);

            lvColumn.cx = 100;
            lvColumn.pszText = "价格/元";
            ListView_InsertColumn(hListView, 1, &lvColumn);

            lvColumn.cx = 100;
            lvColumn.pszText = "销售量";
            ListView_InsertColumn(hListView, 2, &lvColumn);


            // 添加 ListView 行数据
            LVITEM lvItem = {0};
            record(lvItem, hListView, 0, "茶", "29", "114514");
            record(lvItem, hListView, 1, "饭", "92", "1919810");
            break;


        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }
    return 0;
}

LRESULT CALLBACK SpsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hListView;
    switch (message) {
        case WM_CREATE:
            // 初始化 ListView 控件
            InitCommonControlsEx(NULL);

            // 创建 ListView 控件
            hListView = CreateWindow(WC_LISTVIEW, "", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 600, 400, hWnd, NULL, NULL, NULL);

            // 设置 ListView 列表视图
            ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

            // 添加 ListView 列表头
            LVCOLUMN lvColumn = {0};
            lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
            lvColumn.cx = 100;
            lvColumn.pszText = "名称";
            ListView_InsertColumn(hListView, 0, &lvColumn);

            lvColumn.cx = 100;
            lvColumn.pszText = "价格/元";
            ListView_InsertColumn(hListView, 1, &lvColumn);

            lvColumn.cx = 100;
            lvColumn.pszText = "销售量";
            ListView_InsertColumn(hListView, 2, &lvColumn);


            // 添加 ListView 行数据
            LVITEM lvItem = {0};
            record(lvItem, hListView, 0, "茶", "29", "114514");
            record(lvItem, hListView, 1, "饭", "92", "1919810");
            break;


        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }
    return 0;
}

LRESULT CALLBACK CdsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hListView;
    switch (message) {
        case WM_CREATE:
            // 初始化 ListView 控件
            InitCommonControlsEx(NULL);

            // 创建 ListView 控件
            hListView = CreateWindow(WC_LISTVIEW, "", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 600, 400, hWnd, NULL, NULL, NULL);

            // 设置 ListView 列表视图
            ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

            // 添加 ListView 列表头
            LVCOLUMN lvColumn = {0};
            lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
            lvColumn.cx = 100;
            lvColumn.pszText = "名称";
            ListView_InsertColumn(hListView, 0, &lvColumn);

            lvColumn.cx = 100;
            lvColumn.pszText = "价格/元";
            ListView_InsertColumn(hListView, 1, &lvColumn);

            lvColumn.cx = 100;
            lvColumn.pszText = "销售量";
            ListView_InsertColumn(hListView, 2, &lvColumn);


            // 添加 ListView 行数据
            LVITEM lvItem = {0};
            record(lvItem, hListView, 0, "茶", "29", "114514");
            record(lvItem, hListView, 1, "饭", "92", "1919810");
            break;


        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }
    return 0;
}