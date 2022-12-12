# バイナリのビルド
cmake -S . -B build;
cmake --build build;

# ベースディレクトリでzundamonコマンドを実行できるようにコピー
cp build/zundamon .

# Homebrew用のパッケージを生成
mkdir -p package
cp build/zundamon package
cp libcore.dylib package
cp libonnxruntime.1.10.0.dylib package
cp -r open_jtalk_dic_utf_8-1.11 package
tar cf package.tar package
gzip --best package.tar