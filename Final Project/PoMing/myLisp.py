import sys
import re


# --------------------- parser ---------------------

def tokenize(chars):
    # Convert a string of characters into a list of tokens.
    return chars.replace('(', ' ( ').replace(')', ' ) ').split()

def parse(s):
	def parse_tokens(tokens, inner):
		res = []
		while len(tokens) > 0:
			current = tokens.pop(0)
			if current == '(':
				res.append(parse_tokens(tokens, True))
			elif current == ')':
				if inner:
					return res
				else:
					raise SyntaxError('Unmatched close parenthese \')\'')
			else:
				res.append(current)

		if inner:
			raise SyntaxError('Unmatched open parenthese \'(\'')
		else:
			return res

	return parse_tokens(tokenize(s), False)

# --------------------- interpreter ---------------------

class Procedure:
	def __init__(self, params, body, env):
		self.params = params
		self.body = body
		self.env = env
	def getParams(self): 
		return self.params
	def getBody(self): 
		return self.body
	def getEnvironment(self): 
		return self.env

class Environment:
	def __init__(self, parent):
		self.parent = parent
		self.frame = {}

	def add_variable(self, name, value):
		self.frame[name] = value
	def lookup_variable(self, name):
		if self.frame.has_key(name): 
			return self.frame[name]
		elif(self.parent): 
			return self.parent.lookup_variable(name)
		else: 
			raise NameError('Undefined name: %s' % (name))

def eval(expr, env):
	if is_primitive(expr):
		return eval_primitive(expr)
	elif is_if(expr):
		return eval_if(expr, env)
	elif is_definition(expr):
		eval_definition(expr, env)
	elif is_name(expr):
		return eval_name(expr, env)
	elif is_fun(expr):
		return eval_fun(expr, env)
	elif is_list(expr):
		return eval_list(expr, env)
	else:
		raise SyntaxError('Unexpected syntax in form: ' + str(expr))


def is_primitive(expr):
	return is_const(expr) or is_procedure(expr)

def eval_primitive(expr):
	if is_const(expr):
		if expr == '#t':
			return True
		elif expr == '#f':
			return False
		else:
			return int(expr)
	else:		
		# procedure
		return expr

def is_const(expr):
	if isinstance(expr, str):
		if expr == '#t' or expr == '#f':
			return True
		else:
			try:
				int(expr)
			except ValueError:
				return False
		return True
	return False

def is_procedure(expr):
	return callable(expr)



def is_reserved(expr, keyword):
	return isinstance(expr, list) and len(expr) > 0 and expr[0] == keyword

def is_if(expr):
	return is_reserved(expr, 'if')

def eval_if(expr,env):
	test = eval(expr[1], env)
	if len(expr) > 4:
		raise SyntaxError('\'if\' expected 3 arguments')
	if type(test) == type(True):
		if test == True: 
			return eval(expr[2],env)
		elif test == False: 
			return eval(expr[3],env)
	else:
		raise TypeError('\'if\' condiction expected \'boolean\'')


def is_definition(expr): 
	return is_reserved(expr, 'define')

def eval_definition(expr, env):
	if len(expr) > 3:
		raise SyntaxError('\'define\' expected 2 arguments')
	name = expr[1]

	pattern = re.compile(r'[a-zA-Z]([a-zA-Z]|[0-9]|\-)*')
	match = pattern.match(name)

	if not (match and len(match.group(0)) == len(name)):
		raise SyntaxError('Illegal id: %s' % name)
	value = eval(expr[2], env)
	env.add_variable(name, value)

def is_name(expr): 
	return isinstance(expr, str)

def eval_name(expr, env):
	return env.lookup_variable(expr)

def is_fun(expr): 
	return is_reserved(expr, 'fun')
def eval_fun(expr,env):
	return Procedure(expr[1], expr[2:], env)


def is_list(expr): 
	return isinstance(expr, list) and len(expr) 
def eval_list(expr, env):
	subexprs = expr
	subexprvals = map(lambda sexpr: eval(sexpr, env), subexprs)
	return map_list(subexprvals[0], subexprvals[1:])

def map_list(proc, op):
	if is_procedure(proc): 
		return proc(op)
	elif isinstance(proc, Procedure):
		params = proc.getParams()
		newenv = Environment(proc.getEnvironment())
		if len(params) != len(op):
			raise TypeError('Parameter length mismatch: %s expected %s, but given %s' % (str(proc), str(params), str(op)))
		for i in range(0, len(params)):
			newenv.add_variable(params[i], op[i])

		
		define_ahead = False				
		for fun_exp in proc.getBody():
			res = eval(fun_exp, newenv)
			if res != None:
				define_ahead = True
			elif define_ahead:
				raise TypeError('Wrong format of function body')
		return res
	else: 
		raise NameError('Unknown procedure: %s' % (proc))


# ------------------ define primitive procedure ------------------

def primitive_add(op):
	check_op(op, 'add')
	res = 0
	for x in op:
		res += x
	return res
def primitive_sub(op):
	check_op(op, 'sub')
	return op[0] - op[1]
def primitive_mul(op):
	check_op(op, 'mul')
	res = 1
	for x in op:
		res *= x
	return res
def primitive_div(op):			
	check_op(op, 'div')
	return op[0] / op[1]
def primitive_mod(op):
	check_op(op, 'mod')
	return op[0] % op[1]
def primitive_gt(op):
	check_op(op, 'gt')
	return op[0] > op[1]
def primitive_lt(op):
	check_op(op, 'lt')
	return op[0] < op[1]
def primitive_eq(op):
	check_op(op, 'eq')
	for x in op[1:]:
		if x != op[0]:
			return False
	return True
def primitive_and(op):
	check_op(op, 'and')
	for x in op:
		if x == False:
			return False
	return True
def primitive_or(op):
	check_op(op, 'or')
	for x in op:
		if x == True:
			return True
	return False
def primitive_not(op):
	check_op(op, 'not')
	return not op[0]

def primitive_print_num(op):
	check_op(op, 'print-num')
	print op[0]

def primitive_print_bool(op):
	check_op(op, 'print-bool')
	if op[0]:
		print '#t'
	else:
		print '#f'


def check_op(ops, opt):
	if opt in ['add', 'sub', 'mul', 'div', 'mod']:
		for op in ops:
			if(type(op) == type(True)):
				raise TypeError('Procedure \'%s\' expected argument type \'number\', but given \'boolean\'' % opt)

	
	if opt in ['not', 'print-num', 'print-bool']:
		if len(ops) > 1:
			raise TypeError('Procedure \'%s\' expected 1 operand, but given \'%s\'' % (opt, ops))
		elif opt == 'print-num':
			if type(ops[0]) != type(0):
				raise TypeError('Procedure \'print-num\' expected argument \'number\'')
		else:
			if type(ops[0]) != type(True):
				raise TypeError('Procedure \'%s\' expected argument \'boolean\'' % opt)

	elif opt in ['add', 'mul', 'eq', 'and', 'or']:
		if len(ops) < 2:
			raise TypeError('Procedure \'%s\' expected 2 or more operands, but given \'%s\'' % (opt, ops))
	else:
		if len(ops) > 2:
			raise TypeError('Procedure \'%s\' expected 2 operands, but given \'%s\'' % (opt, ops))

	if opt in ['div', 'mod']:
		for op in ops[1:]:
			if op == 0:
				raise ZeroDivisionError('Cannot apply \'%s\' by operands 0' % opt)

# ---------------------------------------------------------------------------------

def ini_env(genv):
	genv.add_variable('+', primitive_add)
	genv.add_variable('-', primitive_sub)
	genv.add_variable('*', primitive_mul)
	genv.add_variable('/', primitive_div)
	genv.add_variable('mod', primitive_mod)
	genv.add_variable('>', primitive_gt)
	genv.add_variable('<', primitive_lt)
	genv.add_variable('=', primitive_eq)
	genv.add_variable('and', primitive_and)
	genv.add_variable('or', primitive_or)
	genv.add_variable('not', primitive_not)
	genv.add_variable('print-num', primitive_print_num)
	genv.add_variable('print-bool', primitive_print_bool)


def repl():
	genv = Environment(None)
	ini_env(genv)
	
	if len(sys.argv) < 2:			# command line prompt
		while True:
			inv = raw_input('>> ')
			try:
				for expr in parse(inv):
					res = eval(expr, genv)
					if type(res) == type(True):
						if res == True:
							print '#t'
						elif res == False:
							print '#f'
					elif res != None:
						print res
			except Exception as e:
				print '%s: %s' % (type(e).__name__, e)
	else:							# source file
		f = open(sys.argv[1], 'r')
		inv = f.read()
		try:
			for expr in parse(inv):
				res = eval(expr, genv)
		except Exception as e:
			print '%s: %s' % (type(e).__name__, e)


repl()