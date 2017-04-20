給定語法如下

<pre><code>E -> E + T | T
T -> T * F | F
F -> i | (E)</code></pre>
請寫出 <code>i+i+(i*i)*i</code> 的 post-order 表示
