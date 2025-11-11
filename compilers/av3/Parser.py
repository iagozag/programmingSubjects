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
    
    @staticmethod
    def precedence(tk):
        if tk.kind == TokenType.NEG:
            return 5
        if tk.kind == TokenType.MUL or tk.kind == TokenType.DIV:
            return 4
        if tk.kind == TokenType.ADD or tk.kind == TokenType.SUB:
            return 3
        if tk.kind == TokenType.LEQ or tk.kind == TokenType.LTH or tk.kind == TokenType.EQL:
            return 2
        if tk.kind == TokenType.NOT:
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
        elif token.kind == TokenType.LPR:
            self.consume()
            expr = self.parse_expression()
            self.consume()
            return expr
        elif token.kind == TokenType.NEG:
            self.consume()
            operand = self.parse_primary()
            return Neg(operand)
        elif token.kind == TokenType.NOT:
            self.consume()
            operand = self.parse_expression(1)
            return Not(operand)
    
    def parse_expression(self, min_precedence=0):
        left = self.parse_primary()
        
        while True:
            token = self.current_token()
            if token is None:
                break
            
            if token.kind not in [TokenType.ADD, TokenType.SUB, TokenType.MUL, 
                                 TokenType.DIV, TokenType.LEQ, TokenType.LTH, TokenType.EQL]:
                break
                
            precedence = self.precedence(token)
            if precedence < min_precedence:
                break
                
            self.consume()
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
        
        return left
    
    def parse(self):
        return self.parse_expression()
