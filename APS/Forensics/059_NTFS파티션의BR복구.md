total sector(3번째 줄 뒤에서 8자리)

NTFS 섹터는 MBR 수보다 적음 +2하면 원래 섹터수 나옴

현재섹터 - 토탈섹터 -> 부트레코더로 의심되는 섹터 주소가 나옴.

![img](image/059/1.png)

![img](image/059/2.png)

NTFS는 이런식으로 에러메세지가 나와야함

![img](image/059/3.png)

![img](image/059/4.png)