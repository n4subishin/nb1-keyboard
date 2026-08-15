# Nb.1

*[English version](README.md)*

12ポジションのプログラマブル入力デバイスです。各ポジションには
**Cherry MX 互換スイッチかロータリーエンコーダのどちらか**を実装できます。
2つは同じフットプリントを共有しているため、12キー構成でも12ノブ構成でも、
その中間の任意の組み合わせでも作れます。ファームウェアは1種類で全構成に対応します。

| | |
|---|---|
| MCU | STM32F405RGT6 (Cortex-M4F, 168 MHz, Flash 1 MB, RAM 192 KB) |
| マトリクス | 3行 × 4列、COL2ROW |
| エンコーダ | 最大12個、GPIO直結 |
| 接続 | USB Type-C、USB 2.0 Full Speed |
| ファームウェア | QMK Firmware (ChibiOS) |
| 設定ツール | Remap / VIA |

---

## キーマップの変更

プログラミングの知識は不要です。すべてブラウザ上で完結します。

1. **Chrome または Edge** で https://remap-keys.app/ を開く
   (Firefox と Safari は WebHID 非対応のため接続できません)
2. 「キーボードをカスタマイズ」を選び、Nb.1 に接続する
3. 変更したい位置にキーコードをドラッグ&ドロップする
4. 「flash」ボタンを押す

エンコーダはノブをクリックすると、時計回りと反時計回りを個別に設定できます。

Remap のカタログに未登録の間は、先に
[`Nb1_remap_definition.json`](Nb1_remap_definition.json) を読み込ませてください。

---

## ファームウェアのビルド

QMK の開発環境が必要です。未構築の場合は
[QMK 公式のセットアップガイド](https://docs.qmk.fm/newbs_getting_started)を参照してください。

```sh
git clone https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
qmk setup

# このリポジトリの keyboards/nb1 を QMK のツリーに配置する
cp -r /path/to/nb1-keyboard/keyboards/nb1 keyboards/

qmk compile -kb nb1 -km via
```

キーマップは2種類あります。`default` はプレーンな QMK 用、`via` は Remap / VIA
対応版です。出荷時は `via` が書き込まれています。

### クロック設定について

Y1 は **16 MHz** の水晶振動子です。QMK の `GENERIC_STM32_F405XG` は 12 MHz を
前提としているため、`board.h` と `mcuconf.h` で上書きしています。

```
PFD 2 MHz -> VCO 336 MHz -> SYSCLK 168 MHz, USB 48 MHz
```

**この2ファイルを削除すると USB がまったく動作しなくなります。** USB クロックが
必要な 48 MHz ではなく 64 MHz になり、コアも上限 168 MHz を大きく超える
224 MHz で動作してしまうためです。

### EEPROM の永続化について

STM32F405 には EEPROM が内蔵されておらず、QMK のフラッシュエミュレーションも
このチップを標準ではカバーしていません。何も指定しないと RAM 上の偽 EEPROM に
フォールバックし、**USB を抜くたびにユーザーの変更が消えます。**
`keymaps/via/rules.mk` で wear-leveling ドライバを明示的に指定して回避しています。
この行は削除しないでください。

---

## ファームウェアの書き込み

書き込みモードに入る方法は2つあります。

**キー操作** — ポジション12(右下)を長押ししてレイヤー1に入り、ポジション1を
押します。出荷時キーマップではここが `QK_BOOT` です。

**BOOT0 ボタン** — USB を抜き、基板上の BOOT0 ボタンを押したまま USB を挿します。
ファームウェアがまったく起動しない状態でも確実に書き込みモードへ入れます。

```sh
qmk flash -kb nb1 -km via
```

---

## ハードウェア

| | |
|---|---|
| 基板 | 96.72 × 95.00 mm、2層 |
| キーピッチ | 19.2 mm |
| スイッチ | Cherry MX 互換、Kailh ホットスワップソケット |
| エンコーダ | Alps EC12E2440301 (24 detent / 24 pulse、プッシュスイッチなし) |
| 水晶振動子 | 16 MHz、CL = 20 pF、HC-49/S |

詳細は [`docs/SPECIFICATION.md`](docs/SPECIFICATION.md) を参照してください。

### 既知の制限

- **SWD 端子が未実装です。** デバッグには MCU の 46 番・49 番ピンへの直接配線が
  必要です。
- **リセットボタンがありません。** C8 に並列でタクトスイッチを追加すれば
  後付けできます。
- **マトリクスの行が J16–J17 のケーブルを経由しています。** このケーブルが
  外れると、エンコーダは動くのにキーが1つも反応しなくなります。キーが効かなく
  なったときは、まずここを疑ってください。
- **エンコーダにプッシュスイッチがありません。** エンコーダを実装した位置は
  回転のみに反応します。

### JTAG ピンについて

PA15 (JTDI)、PB3 (JTDO)、PB4 (NJTRST) をインジケータ LED とマトリクスの
行3・列1に使用しています。設計上 SWD 専用であり、JTAG デバッガは使えません。

---

## ライセンス

QMK Firmware をベースにしているため **GPL v2** です。
詳細は [`LICENSE`](LICENSE) を参照してください。

USB VID `0x1209` は [pid.codes](https://pid.codes/) がオープンソース
ハードウェア向けに割り当てている ID です。この VID を使用するプロジェクトは
認知されたオープンソースライセンスで公開する必要があり、本リポジトリは
その条件を満たしています。
