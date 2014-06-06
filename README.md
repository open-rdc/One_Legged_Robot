One Legged Robot
================
一脚ロボット用プログラム

## mbed(LPC1768)
* PCからシリアルで角度を受信し、RS485通信でサーボモータに角度情報を送信する
* ロボットに搭載されたエンコーダを読み込み、PCへシリアルで送信する

## PC
### 通信
* boostを使ってシリアル通信を行う
* mbedに対して角度とサーボ移動時間を送信する
* mbedに対してエンコーダの値を受信する

### GA
製作中
