# VHD(Virtual Hard Disk)
- .vhd / .vhdx
- 윈도우즈 내의 디스크 관리 기능을 이용하여 생성 및 관리

## 파일확인
- 용량
- 확장자 변조(시그니처 확인)
    - .**vhd**: <br>header `cxsparse`(동적일 경우에만)<br> footer `conectix`
    - .**vhdx**: <br>header `vhdxfile`

읽기전용으로 연결, 필요시 FTK imager로 이미징, 파일만 확인해도 되면 간단하게

# Veracrypt
- TrueCrypt에서 포크된 오픈소스 암호화 소프트웨어
- .hc
- standard volume과 hidden volume선택 가능

