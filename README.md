One Legged Robot
================
### 一脚ロボット用プログラム
* mbed用のプログラムはmbed\mbed.cppになります。
* 詳細は次項にあります。
* PC用はsamplesに入っているものが動作します。


# mbed(LPC1768)
* PCからシリアルで角度を受信し、RS485通信でサーボモータに角度情報を送信する
* ロボットに搭載されたエンコーダを読み込み、PCへシリアルで送信する
* mbed\mbed.cppはこれらの機能を統合したものになります。
* 送るデータは「（1つ目のサーボの角度）,（1つ目のサーボの移動時間）,（2つ目のサーボの角度）,（2つ目のサーボの移動時間）,（sleepの時間）"\n"」です。
* **文字列の最後に"\n"をつけ忘れ無いようにしてください。（忘れるとエラーチェックが飛ばされ、正しく受信出来ません）**
* シリアルを読み込む前と読み込む後にエラーチェックが入っているため、読みこぼしたり、ずれたりすることはありません。

# PC(Windows/Linux)
### 通信
* boostを使ってシリアル通信を行う
* mbedに対して角度とサーボ移動時間を送信する
* mbedからエンコーダの値を受信する
* CMakeでビルドしてください


### GA
* 現在はサンプルプログラムが入っています。
* CMakeでビルドしてください。
