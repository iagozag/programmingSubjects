import sys

from Expression import *
from Lexer import Token, TokenType

class Parser:
    def __init__(self, tokens):
        self.tokens = list(tokens)
        self.cur_token_idx = 0

    def current_token(self):
        return self.tokens[self.cur_token_idx] if self.cur_token_idx < len(self.tokens) else None
    
    def consume(self):
        self.cur_token_idx += 1
    
    def match(self, expected_kind):
        if self.current_token() and self.current_token().kind == expected_kind:
            self.consume()
            return True
        return False
    
    @staticmethod
    def precedence(tk):
        if tk.kind == TokenType.NEG or tk.kind == TokenType.LPR or tk.kind == TokenType.RPR or tk.kind == TokenType.NOT or tk.kind == TokenType.LET or tk.kind == TokenType.INX or tk.kind == TokenType.END:
            return 8
        if tk.kind == TokenType.MUL or tk.kind == TokenType.DIV:
            return 7
        if tk.kind == TokenType.ADD or tk.kind == TokenType.SUB:
            return 6
        if tk.kind == TokenType.LEQ or tk.kind == TokenType.LTH:
            return 5
        if tk.kind == TokenType.EQL:
            return 4
        if tk.kind == TokenType.AND:
            return 3
        if tk.kind == TokenType.ORX:
            return 2
        if tk.kind == TokenType.IFX or tk.kind == TokenType.THN or tk.kind == TokenType.ELS:
            return 1
        return 0

    def parse_primary(self):
        token = self.current_token()
        
        if token.kind == TokenType.NUM:
            self.consume()
            return Num(int(token.text))
        elif token.kind == TokenType.TRU:
            self.consume()
            return Bln(True)
        elif token.kind == TokenType.FLS:
            self.consume()
            return Bln(False)
        elif token.kind == TokenType.VAR:
            var_name = token.text
            self.consume()
            return Var(var_name)
        elif token.kind == TokenType.LPR:
            self.consume()
            expr = self.parse_expression()
            self.match(TokenType.RPR)
            return expr
        elif token.kind == TokenType.LET:
            return self.parse_let()
        elif token.kind == TokenType.IFX:
            return self.parse_if_then_else()
        elif token.kind == TokenType.NEG:
            self.consume()
            operand = self.parse_expression(self.precedence(token) + 1)
            return Neg(operand)
        elif token.kind == TokenType.NOT:
            self.consume()
            operand = self.parse_expression(self.precedence(token) + 1)
            return Not(operand)

        else:
            sys.exit("Parse error")
    
    def parse_let(self):
        self.match(TokenType.LET)
        
        var_name = self.current_token().text
        self.consume()
        
        self.match(TokenType.ASN)
        exp0 = self.parse_expression()
        self.match(TokenType.INX)
        exp1 = self.parse_expression()
        self.match(TokenType.END)
        
        return Let(var_name, exp0, exp1)

    def parse_if_then_else(self):
        self.match(TokenType.IFX)
        cond = self.parse_expression()
        self.match(TokenType.THN)
        exp_then = self.parse_expression()
        self.match(TokenType.ELS)
        exp_else = self.parse_expression()
        return IfThenElse(cond, exp_then, exp_else)
    
    def parse_expression(self, min_precedence=0):
        left = self.parse_primary()
        
        while True:
            token = self.current_token()
            if token is None:
                break
            
            if token.kind not in [TokenType.ADD, TokenType.SUB, TokenType.MUL, 
                                 TokenType.DIV, TokenType.LEQ, TokenType.LTH, 
                                 TokenType.EQL, TokenType.AND, TokenType.ORX]:
                break
                
            precedence = self.precedence(token)
            if precedence < min_precedence:
                break
                
            self.consume()
            
            if token.kind in [TokenType.ADD, TokenType.SUB, TokenType.MUL,
                             TokenType.DIV, TokenType.LEQ, TokenType.LTH, 
                             TokenType.EQL, TokenType.AND, TokenType.ORX]:
                right = self.parse_expression(precedence + 1)
                
                if token.kind == TokenType.ADD:
                    left = Add(left, right)
                elif token.kind == TokenType.SUB:
                    left = Sub(left, right)
                elif token.kind == TokenType.MUL:
                    left = Mul(left, right)
                elif token.kind == TokenType.DIV:
                    left = Div(left, right)
                elif token.kind == TokenType.LEQ:
                    left = Leq(left, right)
                elif token.kind == TokenType.LTH:
                    left = Lth(left, right)
                elif token.kind == TokenType.EQL:
                    left = Eql(left, right)
                elif token.kind == TokenType.AND:
                    left = And(left, right)
                elif token.kind == TokenType.ORX:
                    left = Or(left, right)
            else:
                sys.exit("Parse error")
        
        return left

    def parse(self):
        """
        Returns the expression associated with the stream of tokens.

        Examples:
        >>> parser = Parser([Token('123', TokenType.NUM)])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        123

        >>> parser = Parser([Token('True', TokenType.TRU)])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> parser = Parser([Token('False', TokenType.FLS)])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        False

        >>> tk0 = Token('~', TokenType.NEG)
        >>> tk1 = Token('123', TokenType.NUM)
        >>> parser = Parser([tk0, tk1])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        -123

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        12

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('~', TokenType.NEG)
        >>> tk3 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        -12

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('/', TokenType.DIV)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        7

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('+', TokenType.ADD)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        7

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('-', TokenType.SUB)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        26

        >>> tk0 = Token('2', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('(', TokenType.LPR)
        >>> tk3 = Token('3', TokenType.NUM)
        >>> tk4 = Token('+', TokenType.ADD)
        >>> tk5 = Token('4', TokenType.NUM)
        >>> tk6 = Token(')', TokenType.RPR)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        14

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('==', TokenType.EQL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<=', TokenType.LEQ)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<', TokenType.LTH)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        False

        >>> tk0 = Token('not', TokenType.NOT)
        >>> tk1 = Token('(', TokenType.LPR)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> tk3 = Token('<', TokenType.LTH)
        >>> tk4 = Token('4', TokenType.NUM)
        >>> tk5 = Token(')', TokenType.RPR)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> tk0 = Token('true', TokenType.TRU)
        >>> tk1 = Token('or', TokenType.ORX)
        >>> tk2 = Token('false', TokenType.FLS)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> tk0 = Token('true', TokenType.TRU)
        >>> tk1 = Token('and', TokenType.AND)
        >>> tk2 = Token('false', TokenType.FLS)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        False

        >>> tk0 = Token('let', TokenType.LET)
        >>> tk1 = Token('v', TokenType.VAR)
        >>> tk2 = Token('<-', TokenType.ASN)
        >>> tk3 = Token('42', TokenType.NUM)
        >>> tk4 = Token('in', TokenType.INX)
        >>> tk5 = Token('v', TokenType.VAR)
        >>> tk6 = Token('end', TokenType.END)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, {})
        42

        >>> tk0 = Token('let', TokenType.LET)
        >>> tk1 = Token('v', TokenType.VAR)
        >>> tk2 = Token('<-', TokenType.ASN)
        >>> tk3 = Token('21', TokenType.NUM)
        >>> tk4 = Token('in', TokenType.INX)
        >>> tk5 = Token('v', TokenType.VAR)
        >>> tk6 = Token('+', TokenType.ADD)
        >>> tk7 = Token('v', TokenType.VAR)
        >>> tk8 = Token('end', TokenType.END)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6, tk7, tk8])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, {})
        42

        >>> tk0 = Token('if', TokenType.IFX)
        >>> tk1 = Token('2', TokenType.NUM)
        >>> tk2 = Token('<', TokenType.LTH)
        >>> tk3 = Token('3', TokenType.NUM)
        >>> tk4 = Token('then', TokenType.THN)
        >>> tk5 = Token('1', TokenType.NUM)
        >>> tk6 = Token('else', TokenType.ELS)
        >>> tk7 = Token('2', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6, tk7])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        1

        >>> tk0 = Token('if', TokenType.IFX)
        >>> tk1 = Token('false', TokenType.FLS)
        >>> tk2 = Token('then', TokenType.THN)
        >>> tk3 = Token('1', TokenType.NUM)
        >>> tk4 = Token('else', TokenType.ELS)
        >>> tk5 = Token('2', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        2
        """
        return self.parse_expression()