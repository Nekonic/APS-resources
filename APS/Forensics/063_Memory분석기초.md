# 메모리 포렌식
## 수집방법 & 분석방법
- 메모리 덤프
- 덤프파일을 Volatility 등의 메모리 분석 프로그램을 이용하여 분석

## Memory Dump
- Dumpit: .raw
- FTK imager: .mem

## Volatility
- imageinfo: 기본정보 확인
- --profile
- pslit: 작동중인 모든 프로세스의 리스트를 시간순으로 출력
- cmdline: 프로세스가 실행될 때의 인자값 확인
- dlllist -p [PID]: 프로세스가 사용하는 dll 리스트 확인
