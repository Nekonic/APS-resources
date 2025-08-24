# Prefetch
- 자주 사용되는 프로그램들을 미리 메모리에 로드
- .pf 최대1024개의 pf파일 생성가능

## Superfetch(=Sysmain)
- Prefetch의 메모리 페이징 아웃으로 인한 문제를 개선
- Prefetch와 별개로 사용자의 프로그램 사용 패턴을 추가적으로 기록

## Prefetch의 분류
- Boot Prefetch:<br>부팅되는 속도를 더 빠르게 하기 위한 것<br>NTOSBOOD-BOODFAAD.pf
- Application Prefetch:<br>프로그램 실행파일명-4Byte hash값.pf 형식으로 저장

## 분석으로 확인가능한 내용
- 실행한 응용프로그램의 이름
- 실행 횟수
- 실행 시각
- 실행되면서 참조한 목록(DLL 등)

## Prefetch 상태확인
- HKEY_LOCAL_MACHINE|SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management\PrefetchParameters (값이 3이여야 활성화 상태)
- 서비스 확인(SysMain)<br>services.msc -> SysMain 검색 -> 시작유형이 자동인지 체크

## 도구
https://www.nirsoft.net/utils/win_prefetch_view.html