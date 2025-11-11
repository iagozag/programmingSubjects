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
        # TODO: Implement this method!
        if exp.identifier in env:
            return env[exp.identifier]
        else:
            print(f"Variavel inexistente {exp.identifier}")
            sys.exit()

    def visit_bln(self, exp, env):
        # TODO: Implement this method!
        return exp.bln

    def visit_num(self, exp, env):
        # TODO: Implement this method!
        return exp.num

    def visit_eql(self, exp, env):
        # TODO: Implement this method!
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        return left_val == right_val


    def visit_add(self, exp, env):
        # TODO: Implement this method!
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        return left_val + right_val

    def visit_sub(self, exp, env):
        # TODO: Implement this method!
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        return left_val - right_val

    def visit_mul(self, exp, env):
        # TODO: Implement this method!
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        return left_val * right_val

    def visit_div(self, exp, env):
        # TODO: Implement this method!
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        return left_val // right_val

    def visit_leq(self, exp, env):
        # TODO: Implement this method!
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        return left_val <= right_val

    def visit_lth(self, exp, env):
        # TODO: Implement this method!
        left_val = exp.left.accept(self, env)
        right_val = exp.right.accept(self, env)
        return left_val < right_val

    def visit_neg(self, exp, env):
        # TODO: Implement this method!
        operand_val = exp.exp.accept(self, env)
        return -operand_val

    def visit_not(self, exp, env):
        # TODO: Implement this method!
        operand_val = exp.exp.accept(self, env)
        return not operand_val

    def visit_let(self, exp, env):
        # TODO: Implement this method!
        def_val = exp.exp_def.accept(self, env)
        new_env = env.copy()
        new_env[exp.identifier] = def_val
        return exp.exp_body.accept(self, new_env)

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

    >>> e1 = Let('v', Add(Num(40), Var('v')), Sub(Var('v'), Num(2)))
    >>> e0 = Let('v', Num(3), e1)
    >>> ev = UseDefVisitor()
    >>> len(e0.accept(ev, set()))
    0
    """
    # TODO: Implement all the 13 methods of the visitor.
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
        def_set = exp.exp_def.accept(self, defined_set)
        new_defined = defined_set | {exp.identifier}
        body_set = exp.exp_body.accept(self, new_defined)
        return def_set | body_set

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
    # TODO: Implement this method!
    use_def_visitor = UseDefVisitor()
    defined_set = set()
    undef_set = exp.accept(use_def_visitor, defined_set)
    
    if len(undef_set) > 0:
        print("Error: expression contains undefined variables.")
    else:
        eval_visitor = EvalVisitor()
        env = {}
        result = exp.accept(eval_visitor, env)
        print(f"Value is {result}")
