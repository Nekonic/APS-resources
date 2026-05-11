# Gomoku (오목)

C++ + raylib 으로 만든 2인용 오목 게임입니다.
**어느 시스템에서 빌드하든 출력은 항상 `gomoku.exe` (Windows 실행 파일)** 입니다.

---

## 빌드 방법

### Ubuntu (x86_64 / ARM) — 스크립트 한 줄

```bash
bash build.sh
# → build/gomoku.exe
```

내부적으로 `mingw-w64` 크로스 컴파일러를 사용해 Windows exe를 생성합니다.

---

### Ubuntu (수동)

```bash
# 1. 크로스 컴파일러 설치
sudo apt-get install -y cmake git build-essential mingw-w64

# 2. 빌드
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake \
         -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j$(nproc)

# → build/gomoku.exe
```

---

### Windows (MinGW-w64)

```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
mingw32-make

# → build/gomoku.exe
```

---

## 파일 구성

```
gomoku/
├── CMakeLists.txt          # 빌드 설정
├── toolchain-mingw.cmake   # Linux→Windows 크로스 컴파일 툴체인
├── build.sh                # Ubuntu 원클릭 빌드 스크립트
└── src/
    └── main.cpp
```

---

## 조작 방법

| 입력 | 동작 |
|------|------|
| 마우스 좌클릭 | 해당 격자에 돌 놓기 |
| Restart 버튼 | 게임 초기화 |

- 흑돌(Black) 선공
- 가로·세로·대각선 방향으로 5개 연속 → 승리
