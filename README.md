# NA_MultiInt
多重積分に対する数値アルゴリズムの実装．

## 構成
```
NA_MultiInt
│
├ README.md
│
├ GL .. Gauss--Legendre 積分に関連するプログラム
│  └ GL.cpp
│
├ MC .. Monte Carlo 法に関連するプログラム
│  ├ MC.cpp
│  └ MC_density.cpp .. 提案手法（積分領域を分割し分点を割り振るもの）の実装
│
└ SpectralTest .. スペクトル検定のプログラム
   └ SpectralTest.cpp
```
