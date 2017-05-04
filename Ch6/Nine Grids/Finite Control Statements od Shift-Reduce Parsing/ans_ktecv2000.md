* shift: shift input tape to next one  
* reduce: apply some production on the stack to substitute symbols into non-terminal symbols. 
* accept: if stack is empty and input stream is over, then accept(syntax correct).
* error: if error state is matched (maybe empty entry in the transition table), or either stack is not empty and input stream is not over, then report error.
