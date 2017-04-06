The following grammar is LR(1)? LALR(1)? or SLR(1)? Please justify your categorization.

<pre><code>S -> Id := A ;
A -> Id := A
A -> E
E -> E + P
E -> P
P -> Id
P -> ( Id ; Id )
P -> (A)
</code></pre>
