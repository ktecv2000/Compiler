Please rewrite the following left recursive grammar to right recursion.

<pre><code>S → Stmts $
Stmts → Stmts ; Stmt
      | Stmt
Stmt → func ( id )
</code></pre>
