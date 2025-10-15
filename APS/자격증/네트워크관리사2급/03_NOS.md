# NOS
## 1. File/Print, IIS, DNS, FTP
### IIS (Internet Information Services)
- Windows Server의 웹 서버 소프트웨어
- 설정 가능한 서비스: HTTP(WWW), FTP, SMTP
- httpd.conf: Apache 웹 서버 설정 파일 (리눅스)
### DNS (Domain Name System)
- 도메인 이름 ↔ IP 주소 변환
- 정방향 조회: 도메인 → IP 주소
- 역방향 조회: IP 주소 → 도메인 (PTR 레코드 사용)
- DHCP와 연동 가능 (DDNS)
- 주 영역(Primary Zone)과 보조 영역(Secondary Zone)
### DNS 레코드 종류
- A 레코드: 도메인 → IP 주소 매핑
- PTR 레코드: IP 주소 → 도메인 역매핑
- CNAME: 도메인 별칭
- MX: 메일 서버 지정
- NS: 네임서버 지정

## 2. Active Directory
### Active Directory 개념
- 사용자, 그룹, 네트워크 리소스를 통합 관리하는 디렉터리 서비스
- LDAP(Lightweight Directory Access Protocol) 기반
- DNS 기반 네임스페이스 사용
- 인터넷을 통한 로그온 인증 가능
### AD 논리적 구조
- 도메인(Domain): 관리 단위
- 트리(Tree): 여러 도메인이 계층 구조로 연결
- 포리스트(Forest): 두 개 이상의 트리가 연결된 구조
### AD 인증서 서비스
- 공개 키 인증서를 생성, 배포, 관리하는 서비스
- 디지털 서명, 암호화 등 보안 기능 제공


## 3. 사용자관리 및 권한
### Linux 사용자/권한 관리 명령어
| 명령어 | 설명 |
| - | - |
| useradd: | 사용자 추가 |
| userdel: | 사용자 삭제 |
| usermod: | 사용자 정보 수정 |
| passwd: | 비밀번호 설정/변경 |
| chage: | 비밀번호 만료 기간 설정 |
### Linux 권한 관리
- chmod: 파일 접근 권한 변경
- chown: 파일 소유자 변경
- chgrp: 파일 그룹 소유권 변경

## 4. 시스템 운영 관리
### DHCP (Dynamic Host Configuration Protocol)
- 클라이언트에게 IP 주소 자동 할당
- 장점: IP 주소 중앙 관리, 사용 추적 용이
- 최소 하나의 DHCP 범위(Scope) 필요
- 정적 할당 주소는 범위에서 제외
- **Windows Server DHCP 구성**:
  - 임대 기간: 일, 시간, 분 단위 설정 가능 (초 단위 불가)
  - WINS 서버 구성 여전히 가능
  - 예약 유형: DHCP, BOOTP, Both 지원
  - `주소 분배 지연시간: ms(밀리초) 단위 지정*`

### Hyper-V (가상화)
- Windows Server의 가상화 기술
- 하나의 물리 서버에 여러 가상 서버 실행
- 장점: 하드웨어 효율 증대, 비용 절감
- 스냅샷 기능으로 특정 시점 기록 가능
- 하드웨어 데이터 실행 방지(DEP) 필요
### SAMBA
- Linux와 Windows 간 파일/프린터 공유
- SMB/CIFS 프로토콜 사용
- 기능: 파일 시스템 공유, 프린터 공유, 네트워크 브라우징
- RPM으로 설치 가능

## 5. Linux 디렉터리 구조
| 디렉터리   |  용도 |
| - | - |
| /bin   |  기본 명령어 (ls, cp, mv 등) |
| /etc   |  시스템 설정 파일 |
| /var   |  로그 파일, 메일 데이터 |
| /tmp   |  임시 파일 |
| /boot  |  부팅 커널 이미지 |
| /lib   |  라이브러리 파일 |
| /dev   |  디바이스 드라이버 |
| /usr   |  사용자 프로그램, 매뉴얼 |
| /root  |  root 사용자 홈 디렉터리 |
| /home  |  일반 사용자 홈 디렉터리 |

## 6. Linux 명령어 (필기/실기 빈출)
### 파일/디렉터리 관리
| 명령어 | 설명 |
| - | - |
| ls | 파일 목록 표시 (ls -l: 상세 정보) |
| cd | 디렉터리 이동 |
| pwd | 현재 디렉터리 경로 표시 |
| mkdir | 디렉터리 생성 |
| rmdir | `빈 디렉터리 삭제` |
| rm | 파일/디렉터리 삭제 (rm -rf: 강제 삭제) |
| cp | 파일 복사 |
| mv | 파일 이동/이름 변경 |
| find | 파일 검색 |
| file | 파일 타입 확인 |
### 시스템 정보
| 명령어 | 설명 |
| - | - |
| ps | 프로세스 상태 확인 |
| top | CPU/메모리 사용률 실시간 확인 |
| free | 메모리 사용량 확인 |
| df | 디스크 사용량 확인 |
| du | 디렉터리 크기 확인 |
### 네트워크 관련
- ifconfig: IP 주소 설정/확인 (Windows의 ipconfig)
- netstat: 네트워크 연결 상태, 라우팅 테이블 확인
    - netstat -r: 라우팅 테이블
    - netstat -a: 모든 연결/포트
- ping: 네트워크 연결 테스트
- nslookup: DNS 조회
### 기타 명령어
- man: 명령어 매뉴얼 확인
- grep: 텍스트 검색
- cat: 파일 내용 출력
- tail: 파일 끝부분 출력
- shutdown: 시스템 종료
    - shutdown -r now: 즉시 재부팅
    - shutdown -h now: 즉시 종료
- reboot: 재부팅
- init 0: 시스템 종료
- init 6: 시스템 재부팅
### 리다이렉션 (Redirection)
- **`>`** : 출력을 파일로 저장 (덮어쓰기/overwrite)
  - 예: `ls -al > output.txt`
- **`>>`** : 출력을 파일 끝에 추가 (append)
  - 예: `ls -al >> output.txt`
- **`<`** : 파일에서 입력 받기
- **`<<`** : Here Document (여러 줄 입력)


## 7. 기타
### Daemon (데몬)
- 백그라운드에서 실행되는 시스템 서비스 프로세스
- 이벤트 발생 시 자동 실행
### netstat 주요 정보
- TCP/UDP 연결 상태
- 라우팅 테이블
- 네트워크 인터페이스 통계
- 포트 사용 현황
### RPM (Red Hat Package Manager)
- Linux 패키지 설치 도구
- 미리 컴파일된 바이너리 패키지
