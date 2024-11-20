# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

#ビルドターゲット

set TARGET_FILES{
    main.c,
    mtr.c
  }

# ライブラリ追加
add_library(src STATIC ${TARGET_FILES})


# インクルードパス


#読み込みライブラリ指定

