Please rewrite the following grammar to handle the common prefix problem.

<pre><code>S → Stmts $
Stmts → Stmt ; Stmts
      | λ
Stmt → func ( id )
     | for ( Declaration ; Condition ; Stmt ) { Stmts }
     | for ( var id in id ) { Stmts }
Declaration → …
Condition → …
</code></pre>
