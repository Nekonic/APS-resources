# Jumplist
- 윈도우에서 최근 사용한 파일 및 폴더에 빠르게 접근하기 위한 구조
- 최근에 사용한 파일 및 폴더를 .lnk(링크파일)로 관리

## Jumplist 분류
- Recent(최근)
- Frequent(자주)
- Tasks(작업)
- Pinned(고정)

## Jumplist 종류
- AutomaticDestination:<br>운영체제가 자동으로 남기는 항목(`recent`,`pinned`)
- CustomDestination:<br>응용프로그램이 자체적으로 관리(`Freqent`,`Tasks`)
- 각 파일의 이름은 응용프로그램별 고유한 값(AppID)으로 저장<br>ccba5a5986c77e43.automaticDestination-ms = 마소엣지

## 관련 파일 경로
- %UserProfile%\AppData\Roaming\Microsoft\Windows\Recent\
- %UserProfile%\AppData\Roaming\Microsoft\Windows\Recent\AutomaticDestinations\
- %UserProfile%\AppData\Roaming\Microsoft\Windows\Recent\CustomDestinations\

## 도구
https://github.com/woanware/JumpLister