# 1. 레지스터(Registers) 구조

## 주요 범용 레지스터 (General-Purpose Registers, GPR)
| x86(32bit) | x86_64(64bit) | Description |
| ---------- | ------------- | --- |
| EAX | RAX | 누산기(Accumulator). 산술 연산, 함수 반환값 저장, 곱셈·나눗셈 등에서 사용됨 |
| EBX | RBX | 베이스(Base) 레지스터. 과거에는 메모리 접근 시 베이스 주소로 사용, x64에선 주 용도 없음 |
| ECX | RCX | 카운터(Counter) 레지스터. 반복문 루프 횟수, shift/rotate 연산 등에서 사용 |
| EDX | RDX | 데이터(Data) 레지스터. 곱셈/나눗셈의 중간값, 입출력, 함수 인자 전달 등 |
| ESI | RSI | 소스 인덱스(Source Index). 메모리 복사 등에서 원본 데이터 위치를 지정 |
| EDI | RDI | 목적지 인덱스(Destination Index). 메모리 복사 등에서 목적지 데이터 위치를 지정 |
| EBP | RBP | 스택 포인터(Stack Pointer). 현재 스택의 최상단 위치를 가리킴. 함수 호출·복귀, push/pop 등에서 사용 |
| ESP | RSP | 베이스 포인터(Base Pointer). 현재 함수(스택 프레임)의 기준점 역할, 지역 변수/매개변수 접근에 사용 |

---

# 2. 명령어 집합(Instruction Set)

- **명령어**(Instruction)는 기본적으로 Opcode와 **피연산자**(Operands)로 구성
- x86-64 명령어는 최대 15바이트까지 길어질 수 있고, 구성요소는 다음과 같음
    - Prefix(접두사): 명령어의 동작을 변경하는 1~4바이트(옵션)
    - Opcode: 실제 연산을 지정하는 1~4바이트(필수)
    - ModR/M: 레지스터와 메모리 주소 지정(필요시 1바이트)
    - SIB: Scale-Index-Base, 메모리 주소 계산에 사용(필요시 1바이트)
    - Displacement: 주소 변위(필요시 1, 2, 4, 8바이트)
    - Immediate: 즉시값(필요시 1, 2, 4, 8바이트)

## 명령어의 종류



# 요약
| 레지스터 | 용도 (한글) | 용도 (영문) |
|--------|----------|-----------|
| RAX | 누산기, 반환값 | Accumulator, Return value |
| RBX | 베이스, 임시 저장 | Base, Temporary storage |
| RCX | 카운터, 반복/시프트 | Counter, Loop/Shift |
| RDX | 데이터, 곱셈/나눗셈 | Data, Multiplication/Division |
| RSI | 소스 인덱스 | Source Index |
| RDI | 목적지 인덱스 | Destination Index |
| RSP | 스택 포인터 | Stack Pointer |
| RBP| 베이스 포인터 | Base Pointer |
| R8 ~ R15 | 추가 범용 | Additional General Purpose |
| RIP | 명령어 포인터 | Instruction Pointer |
| RFLAGS | 플래그 | Flags (Status) |
| CS/DS/SS/ES/FS/GS | 세그먼트 | Segment Registers |