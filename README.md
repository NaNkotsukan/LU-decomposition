# LU-decomposition
C言語によるLU分解による逆行列の計算の実装

# Setup
git clone   https://github.com/NaNkotsukan/LU-decomposition  
cd LU-decomposition  
gcc matrix.c -lm main.c  
./a.out


# Description
## main.c
サンプルコード．
## A.txt B.txt
入力行列例
## matrix.c
### sqmx
正方行列を表す構造体  
Nは縦と横の大きさ．  
dataは行列のポインタ．  

### sqmx createMatrix(int N)
正方行列の作成．
#### 引数
N：行列の大きさ．
#### 返り値
初期化された正方行列．

### void deleteMatrix(sqmx a);
行列の破壊．
#### 引数
a：消去する正方行列．
#### 返り値
なし．

### void showArray(sqmx a);
行列の標準出力による表示．
#### 引数
a：表示する正方行列．
#### 返り値
なし．

### sqmx dot(sqmx a, sqmx b);
行列積A*Bの計算．
#### 引数
a：正方行列A．  
b：正方行列B．  
#### 返り値
A*Bの正方行列．

### sqmx loadMatrix(char *filepass);
行列のファイルからの読み込み，形式は以下．  
N  
A<sub>1_1</sub>, A<sub>1_2</sub>, ......A<sub>1_N</sub>  
A<sub>2_1</sub>, A<sub>2_2</sub>, ......A<sub>2_N</sub>  
............  
............  
............  
A<sub>N_1</sub>, A<sub>N_2</sub>, ......A<sub>N_N</sub>  
#### 引数
filepass：ファイルパス．
#### 返り値
読み込んだ正方行列．

### void saveMatrix(char *filepass, sqmx a);
行列のファイル書き出し．  
#### 引数
filepass：ファイルパス．  
sqmx：正方行列．  
#### 返り値
なし

### void calcLU(sqmx A, sqmx *L, sqmx *U);
LU分解A=L*Uの計算．
#### 引数
A：元の正方行列．  
L：Lのポインタ．  
U：Uのポインタ．  
#### 返り値
なし

### sqmx inverseL(sqmx L);
対角成分がすべて1の下三角行列の逆行列を求める．
#### 引数
L：入力の正方行列．
#### 返り値
Lの逆行列．

### sqmx inverseU(sqmx);
上三角行列の逆行列を求める．
#### 引数
U：入力の正方行列．
#### 返り値
Uの逆行列．
