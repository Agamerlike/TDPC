# Typical DP Contest

# A
i問目までの問題を解いた時に取ることができる得点を記録する。一度取ることができることが分かった得点がその後の全ての問題を解いた時に取れなくなってしまうというケースはこの問題では存在しないため0番目（何も解かない）から出発して順番に解いていった場合の得点を記録していけばよい。

ここで1次元のDPを考えた。dp[i]は得点iを取ることができる問題の組み合わせが存在するかどうかの真理値である。ここでk問目までの問題を解いたとき（つまりこの時点での得点の最大値はk問目まですべて解けた場合）のdp[]についての処理を詳しく考えると、dp[]の中身を0からたどるか最大値からたどるかの2通りの処理が考えられる。

しかし、前者の場合、そのループ内でfalseからtrueに変わった（つまり直前のループでは作ることのできなかった）得点を再度参照してしまい間違った値をtrueにしてしまうので、不適切である。このことを防ぐためにもdp[j][i]として、j番目までの問題を解いた時に得点iを取ることができる問題の組み合わせが存在するかどうかの真理値とし、一度更新してしまったところを参照しないようにする（更新の際には過去の情報のみ参照する）などが考えられる。また、このような問題が見えにくくなってしまうので**DPにおいてはソートなどによって入力値の順序を変えてはいけない。（これは他のプログラムの場合についても同様で、計算量がO記法で少なくなるようなことがない場合にむやみにいじってはいけない）**

後者の場合では、1次元DPによってきれいに記述できる。この問題においては新しくfalseからtrueになる得点は派生元よりも常に点数が高くなるためである。例えば問題の得点に負の数も考えられるケースにおいては、1次元DPでの記述は不可能である。

# B
2つの山がそれぞれ残りi個、j個のときの先手が取るスコアを記録する。ただし0番目を0として山に追加しておく（これに限らずDPは0番目の0を置いておいたほうが何かとうまくいくことが多い）。逆からDPを進めていくのであらかじめ山a[],b[]を逆転させておく。

残りi個、j個のとき、先手が取れる手は次の2通りに限られる。

1. Aの山の一番上、すなわちa[i]を取る。
2. Bの山の一番上、すなわちb[j]を取る。

これは後手についても同じことが言えるのでこの状態で先手の取るスコアは、現在両方の山にあるスコアの合計をsとするとs-dp\[i-1\][j]とs-dp\[i\]\[j-1\]のうち大きい方であることが分かる。したがって漸化式は以下の通りである。

> dp[i][j]=max(s-dp[i-1][j],s-dp[i][j-1])

こう書いてしまうと簡単だが、実際には先手の取るパターンにだけ注目して（合計から求めるのめんどくさかった）2ターン前のパターン4通りについて考えたり、そもそも逆転させずにDPしようとしたりした。前者は同じシチュエーションにおいて先手と後手で取るものが被る場合が存在するためダメで、後者はそもそもダメである（がんばればできそう）。

この時点でDPテーブルを回す部分でO(AB)だが、下手な実装をしてしまうとO(A^2*B)となってしまいあまり良くない。これはsを求める作業に起因しているのでこの部分を累積和を使って高速化しておいた。ただ、制約上下手な実装でも間に合いそうではある。

# C
比較的楽に解けたが（解説見ずに済んだ）、DPと言われたら微妙なところではある。

制約上たかだかk回戦までしか行われないこと、そしてシードなどは存在しないので優勝するならk回勝つしかないことが分かる。そこで、iがj回戦を勝ち残る確率でdpテーブルを構成した。このdpテーブルにおいて遷移条件はおおよそ以下のようになるだろうということが予想できる。

dp[i][j]=dp[i][j-1]\(iがj-1回戦を勝ち残る確率\)\*hogehoge\(iとj回戦で戦う可能性がある人が勝ち残る確率\)

最もこれは非常におおざっぱな評価で、iが個々の人と対戦して勝つ確率が一切考慮されていないのでまだまだ改善の余地は大きい。しかし目下問題となるのは上記hogehogeの部分である。hogehogeをどう求めるかが、このDPの鍵と言える。

実際にトーナメント木を描くと分かるが、iがj回戦で対戦することになる可能性のある相手は、j回戦目、つまりトーナメントの部分木の一番上の部分からみてiの所属していないほうに所属する葉すべてである。

```
       |
    -------
   |       |
  ---     ---
 |   |   |   |
 -   -   -   -
| | | | | | | |
0 1 2 3 4 5 6 7
```

分かりにくいのでトーナメントを描いた。図の1番上（3回戦目）において、たとえばiを6とするとiは右側の部分木に所属する葉なのでiと3回戦目で対戦することなる人は左側の部分木に属する0,1,2,3となる。

問題はこれをどうやってコードに落とし込むかだが、かなり強引にやったので、参考にならないと思う。

j回戦目において、j回戦目の部分木を取ってくるとそこに所属する葉の総数は2^j個である。右側に所属するか、左側に所属するかは、2^j/2=2^j-1以上か未満かで分けることができる。ただし、実際には何番目の部分木を持ってきたかで補正する(+k\*2^j)必要がある。

ここまで来ると何とかコードに落とし込めるので、無理やり記述する（きたない）。

これでhogehogeの部分は解決した。あとは問題文に示されているレーティングの定義にしたがって勝率を求め加算していく（それぞれが勝ち残る確率は独立なので加算していい）だけである。

DPというかhogehogeを求めている部分が最も深くO(K2^K)である。一見間に合わなさそうだが制約が緩いので間に合う。かなり全探索に近い方法だと思うのだが（というか逆に全探索で求める方法が思いつかない）、これは果たしてDPなのだろうか。。。


# D
最初目の和と誤読していて大量に時間を消費。その後積で書き直すもこちらもgoogleに突っ込んだ計算式を誤読してRE（6^100<10^8になるわけないだろボケカス）。力尽きた。

### 追記（解説見た）
素因数分解。倍数と来たら素因数分解は基本（できない）。

とはいっても迷走しまくった。桁数の見積もり甘くて初めてMLE出したり。無限にバグらせたり。MLEが出た場合はi番目の部分を削るのではなく問題条件から使わない部分を削っていくほうが賢い。i番目削って次元減らすとなぜかどこかバグるので。

# E
桁DPなるものらしい。が、一切分からない。

### 追記（解説見た）
dの倍数という部分が最大のネックになってくることは確実なので、mod dをひとつのパラメータとして持つことにする。下から見ていく桁DPとすると、DPテーブルは以下のようになりそうだ。

> dp\[桁数\]\[mod d\]

遷移条件を考える。ある桁の数字（この場合は常に現在時点での最上位の数字のみを確定させる）を確定させることを考えたとき、それまでの桁の数字がそれぞれどのくらいの数あったかはdp\[現在の桁-1\]\[mod d\]で知ることができる。mod dの部分は+n(0<=n<=9)してmod dすればよいので、これでDPできそうなことが分かる。

ただしn以下という制約に注意したい。とりあえずnの桁数-1分だけは上のようにして調べ、残りの分は全探索すればいいか。