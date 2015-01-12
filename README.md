﻿One Legged Robot
================
### 一脚ロボット用プログラム
* mbed用のプログラムはmbed\mbed.cppになります。
* pc用の遺伝的アルゴリズムはgenetic_algorithm\five_parametersになります。

# mbed(LPC1768)
* PCからシリアルで角度を受信し、TTL半二重通信でサーボモータに角度情報を送信する
* ロボットに搭載されたエンコーダを読み込み、PCへシリアルで送信する
* mbed\mbed.cppはこれらの機能を統合したものになります。
* データを送るとデフォルトでは30秒間動き続け、その後次のデータを待ちます。（defineで時間の指定可能）
* 送るデータは「（1つ目のサーボの角度）,（1つ目のサーボの移動時間）,（2つ目のサーボの角度）,（2つ目のサーボの移動時間）,（sleepの時間）,"\n"」です。
* シリアルを読み込む前にエラーチェックが入っているため、読みこぼしたり、ずれたりすることはありません。
* **文字列の最後に"\n"をつけ忘れ無いようにしてください。（忘れるとエラーチェックが飛ばされ、正しく受信出来ません）**

# PC(Windows/Linux)
### 通信
* Serialクラスがboostのシリアル通信クラスです。
* mbedに対して角度とサーボ移動時間とsleepの時間を送信する。
* mbedからエンコーダの値を受信する。
* CMakeでビルドしてください。


### GA
* GA自体はSGAです。
* ロボットへ学習したデータを送信し、動作終了次第、pcへ進んだ距離を返す。
* 進んだ距離を元にランキングを付け、交叉、突然変異をする。
