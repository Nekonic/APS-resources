# Timeline(Windows 10)
- 윈도우10부터 새로 제공된 기능
- 사용자의 최근 활동 내역을 최대 30일까지 확인가능

## 분석을 통해 알 수 있는 것들
- 시간에 따른 사용자 행위추적
- 응용프로그램의 구체적 사용시간 확인

## ActivitiesCache.db
- 타임라인의 정보가 저장되는 파일로, SQLite 포맷의 DB파일
- 저장위치:<br>%UserProfile%\AppData\Local\ConnectedDevicesPlatform\FOLDER(Account)\ActivitiesCache.db
- 계정구분
    - L.계정명: Windows10 loacl 계정
    - 16자리 영문숫자혼합: MS 계정

## 분석 - Activity Table
### App ID
- 실행됐던 응용프로그램과 플랫폼을 JSON 포멧으로 기록
- Platform 유형
    - host: 특정행위가 호스트에서 이뤄진 경우
    - x_exe_path: 독립실행파일인 경우
    - windows_win32: 설치된 응용프로그램인 경우
    - windows_universal: UWP 응용프로그램인 경우
    - 그 외 android / ios / web 등

### AppActivityID
- 실행됐던 파일명 / 접속했던 URL 주소 확인가능

### Activity Type
- 파일과 프로그램의 실행 등 활동유형을 숫자로 기록
- 5: 파일 및 프로그램 실행
- 6: 응용프로그램이 활성화되어 사용중
- 16: 복사/붙여넣기 작업

### Activity Status
- 1: 응용프로그램이 열려있음
- 2: 이전의 Active Entry가 없데이트 됨
- 3: 타임라인에서 타일이 제거됨

### Start Time
- 5: 응용프로그램을 실행한 시간
- 6: 활성화된 시간

### End Time
- 5: 종료한 시간
- 6: 비활성화된 시간

### Expiration Time
- 타임라인의 작업기록이 만료되는 시간, Last Modified Time + 30일

### Payload
- 실행한 응용프로그램 및 파일에 대한 세부정보를 기록
- 5: 타임라인에 보여지는 정보 확인
    - Displaytext: 열었던 파일명 또는 URL
    - appDisplayName: 응용프로그램 이름
    - Description: 열었던 파일/URL의 전체경로
- 6:
    - Type: 활동 유형
    - activeDurationSeconds: 활동 지속 시간(초)
    - userTimezone: 타임존 정보

