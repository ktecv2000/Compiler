在一個Shift-reduce Parsing中採用以下語法

<pre><code>A -> aB { print "0"; }
A -> c  { print "1"; }
B -> Ab { print "2"; }</code></pre>
當輸入為 <code>aacbb</code>時, 輸出應為?
