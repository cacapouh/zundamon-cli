# バイナリのビルド
cmake -S . -B build;
cmake --build build;

# ベースディレクトリでzundamonコマンドを実行できるようにコピー
cp build/zundamon .

# Homebrew用のパッケージを生成
mkdir -p pkg
cp build/zundamon pkg
cp libcore.dylib pkg
cp libonnxruntime.1.10.0.dylib pkg
cp -r open_jtalk_dic_utf_8-1.11 pkg
tar czf pkg.tar.gz pkg