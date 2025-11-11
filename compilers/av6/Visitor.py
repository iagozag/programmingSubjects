import sys
from abc import ABC, abstractmethod
from Expression import *

class Visitor(ABC):
    """
    The visitor pattern consists of two abstract classes: the Expression and the
    Visitor. The Expression class defines on method: 'accept(visitor, args)'.
    This method takes in an implementation of a visitor, and the arguments that
    are passed from expression to expression. The Visitor class defines one
    specific method for each subclass of Expression. Each instance of such a
    subclasse will invoke the right visiting method.
    """
    @abstractmethod
    def visit_var(self, exp, arg):
        pass

    @abstractmethod
    def visit_bln(self, exp, arg):
        pass

    @abstractmethod
    def visit_num(self, exp, arg):
        pass

    @abstractmethod
    def visit_eql(self, exp, arg):
        pass

    @abstractmethod
    def visit_add(self, exp, arg):
        pass

    @abstractmethod
    def visit_sub(self, exp, arg):
        pass

    @abstractmethod
    def visit_mul(self, exp, arg):
        pass

    @abstractmethod
    def visit_div(self, exp, arg):
        pass

    @abstractmethod
    def visit_leq(self, exp, arg):
        pass

    @abstractmethod
    def visit_lth(self, exp, arg):
        pass

    @abstractmethod
    def visit_neg(self, exp, arg):
        pass

    @abstractmethod
    def visit_not(self, exp, arg):
        pass

    @abstractmethod
    def visit_let(self, exp, arg):
        pass

    @abstractmethod
    def visit_ifThenElse(self, exp, arg):
        pass

    @abstractmethod
    def visit_and(self, exp, arg):
        pass

    @abstractmethod
    def visit_or(self, exp, arg):
        pass

class EvalVisitor(Visitor):
    """
    The EvalVisitor class evaluates logical and arithmetic expressions. The
    result of evaluating an expression is the value of that expression. The
    inherited attribute propagated throughout visits is the environment that
    associates the names of variables with values.

    Examples:
    >>> e0 = Let('v', Add(Num(40), Num(2)), Mul(Var('v'), Var('v')))
    >>> e1 = Not(Eql(e0, Num(1764)))
    >>> ev = EvalVisitor()
    >>> e1.accept(ev, {})
    False

    >>> e0 = Let('v', Add(Num(40), Num(2)), Sub(Var('v'), Num(2)))
    >>> e1 = Lth(e0, Var('x'))
    >>> ev = EvalVisitor()
    >>> e1.accept(ev, {'x': 41})
    True
    """
    def visit_var(self, exp, env):
        if exp.identifier in env:
            return env[exp.identifier]
        else:
            sys.exit("Def error")

    def visit_bln(self, exp, env):
        return exp.bln

    def visit_num(self, exp, env):
        return exp.num

    def visit_eql(self, exp, env):
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        return left_val == right_val


    def visit_add(self, exp, env):
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        if type(left_val) == type(1) and type(right_val) == type(1):
            return left_val + right_val
        else:
            sys.exit("Type error")

    def visit_sub(self, exp, env):
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        if type(left_val) == type(1) and type(right_val) == type(1):
            return left_val - right_val
        else:
            sys.exit("Type error")

    def visit_mul(self, exp, env):
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        if type(left_val) == type(1) and type(right_val) == type(1):
            return left_val * right_val
        else:
            sys.exit("Type error")

    def visit_div(self, exp, env):
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        if type(left_val) == type(1) and type(right_val) == type(1):
            if right_val == 0:
                sys.exit("Type error") # Division by zero
            return left_val // right_val
        else:
            sys.exit("Type error")

    def visit_leq(self, exp, env):
        val_left = exp.left.accept(self, env)
        val_right = exp.right.accept(self, env)
        if type(val_left) == type(1) and type(val_right) == type(1):
            return val_left <= val_right
        else:
            sys.exit("Type error")

    def visit_lth(self, exp, env):
        val_left = exp.left.accept(self, env)
        val_right = exp.right.accept(self, env)
        if type(val_left) == type(1) and type(val_right) == type(1):
            return val_left < val_right
        else:
            sys.exit("Type error")

    def visit_neg(self, exp, env):
        operand_val = exp.exp.accept(self, env)
        if type(operand_val) == type(1):
            return -operand_val
        else:
            sys.exit("Type error")

    def visit_not(self, exp, env):
        operand_val = exp.exp.accept(self, env)
        if type(operand_val) == type(True):
            return not operand_val
        else:
            sys.exit("Type error")

    def visit_let(self, exp, env):
        def_val = exp.exp_def.accept(self, env)
        new_env = env.copy()
        new_env[exp.identifier] = def_val
        return exp.exp_body.accept(self, new_env)

    def visit_ifThenElse(self, exp, env):
        cond_val = exp.cond.accept(self, env)
        if type(cond_val) == type(True):
            if cond_val:
                return exp.e0.accept(self, env)
            else:
                return exp.e1.accept(self, env)
        else:
            sys.exit("Type error")

    def visit_and(self, exp, env):
        left_val = exp.left.accept(self, env)
        if type(left_val) == type(True):
            if not left_val:
                return False
            right_val = exp.right.accept(self, env)
            if type(right_val) == type(True):
                return left_val and right_val
            else:
                sys.exit("Type error")
        else:
            sys.exit("Type error")

    def visit_or(self, exp, env):
        left_val = exp.left.accept(self, env)
        if type(left_val) == type(True):
            if left_val:
                return True
            right_val = exp.right.accept(self, env)
            if type(right_val) == type(True):
                return left_val or right_val
            else:
                sys.exit("Type error")
        else:
            sys.exit("Type error")


class UseDefVisitor(Visitor):
    """
    The UseDefVisitor class reports the use of undefined variables. It takes
    as input an environment of defined variables, and produces, as output,
    the set of all the variables that are used without being defined.

    Examples:
    >>> e0 = Let('v', Add(Num(40), Num(2)), Mul(Var('v'), Var('v')))
    >>> e1 = Not(Eql(e0, Num(1764)))
    >>> ev = UseDefVisitor()
    >>> len(e1.accept(ev, set()))
    0

    >>> e0 = Let('v', Add(Num(40), Num(2)), Sub(Var('v'), Num(2)))
    >>> e1 = Lth(e0, Var('x'))
    >>> ev = UseDefVisitor()
    >>> len(e1.accept(ev, set()))
    1

    >>> e = Let('v', Add(Num(40), Var('v')), Sub(Var('v'), Num(2)))
    >>> ev = UseDefVisitor()
    >>> len(e.accept(ev, set()))
    1
    """
    def visit_var(self, exp, defined_set):
        if exp.identifier in defined_set:
            return set()
        else:
            return {exp.identifier}

    def visit_bln(self, exp, defined_set):
        return set()

    def visit_num(self, exp, defined_set):
        return set()

    def visit_eql(self, exp, defined_set):
        left_set = exp.left.accept(self, defined_set)
        right_set = exp.right.accept(self, defined_set)
        return left_set | right_set

    def visit_add(self, exp, defined_set):
        left_set = exp.left.accept(self, defined_set)
        right_set = exp.right.accept(self, defined_set)
        return left_set | right_set

    def visit_sub(self, exp, defined_set):
        left_set = exp.left.accept(self, defined_set)
        right_set = exp.right.accept(self, defined_set)
        return left_set | right_set

    def visit_mul(self, exp, defined_set):
        left_set = exp.left.accept(self, defined_set)
        right_set = exp.right.accept(self, defined_set)
        return left_set | right_set

    def visit_div(self, exp, defined_set):
        left_set = exp.left.accept(self, defined_set)
        right_set = exp.right.accept(self, defined_set)
        return left_set | right_set

    def visit_leq(self, exp, defined_set):
        left_set = exp.left.accept(self, defined_set)
        right_set = exp.right.accept(self, defined_set)
        return left_set | right_set

    def visit_lth(self, exp, defined_set):
        left_set = exp.left.accept(self, defined_set)
        right_set = exp.right.accept(self, defined_set)
        return left_set | right_set

    def visit_neg(self, exp, defined_set):
        return exp.exp.accept(self, defined_set)

    def visit_not(self, exp, defined_set):
        return exp.exp.accept(self, defined_set)

    def visit_let(self, exp, defined_set):
        undef_in_def = exp.exp_def.accept(self, defined_set)
        new_defined_set = defined_set | {exp.identifier}
        undef_in_body = exp.exp_body.accept(self, new_defined_set)
        return undef_in_def | undef_in_body

    def visit_ifThenElse(self, exp, defined_set):
        cond_undef = exp.cond.accept(self, defined_set)
        then_undef = exp.e0.accept(self, defined_set)
        else_undef = exp.e1.accept(self, defined_set)
        return cond_undef | then_undef | else_undef

    def visit_and(self, exp, defined_set):
        left_undef = exp.left.accept(self, defined_set)
        right_undef = exp.right.accept(self, defined_set)
        return left_undef | right_undef

    def visit_or(self, exp, defined_set):
        left_undef = exp.left.accept(self, defined_set)
        right_undef = exp.right.accept(self, defined_set)
        return left_undef | right_undef

def safe_eval(exp):
    """
    This method applies one simple semantic analysis onto an expression, before
    evaluating it: it checks if the expression contains free variables, there
    is, variables used without being defined.

    Example:
    >>> e0 = Let('v', Add(Num(40), Num(2)), Mul(Var('v'), Var('v')))
    >>> e1 = Not(Eql(e0, Num(1764)))
    >>> safe_eval(e1)
    Value is False

    >>> e0 = Let('v', Add(Num(40), Num(2)), Sub(Var('v'), Num(2)))
    >>> e1 = Lth(e0, Var('x'))
    >>> safe_eval(e1)
    Error: expression contains undefined variables.
    """
    use_def_visitor = UseDefVisitor()
    undef_set = exp.accept(use_def_visitor, set()) 
    
    if len(undef_set) > 0:
        print("Error: expression contains undefined variables.")
    else:
        eval_visitor = EvalVisitor()
        env = {}
        result = exp.accept(eval_visitor, env)
        print(f"Value is {result}")