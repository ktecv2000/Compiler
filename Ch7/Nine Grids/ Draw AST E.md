<pre><code>lparen = "("
rparen = ")"
assign = "="
plus = "+"
semi = ";"

id = [a-zA-Z]+
num = [0-9]</code></pre>
Given the grammar:

<pre><code>Start -> Stmt $

Stmt  -> id assign E
       | if lparen E rparen Stmt else Stmt
       | begin Stmts end

Stmts -> Stmts semi Stmt
       | Stmt

E     -> E plus T
       | T

T     -> id
       | num</code></pre>
Show the AST for expression:

<code>if (x + y) a = 5 else a = a + y</code>
