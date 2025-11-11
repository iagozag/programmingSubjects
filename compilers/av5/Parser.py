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
        if tk.kind == TokenType.NEG or tk.kind == TokenType.LPR or tk.kind == TokenType.RPR or tk.kind == TokenType.LET or tk.kind == TokenType.INX or tk.kind == TokenType.END:
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
        elif token.kind == TokenType.NEG:
            self.consume()
            operand = self.parse_primary()
            return Neg(operand)
        elif token.kind == TokenType.NOT:
            self.consume()
            operand = self.parse_expression(1)
            return Not(operand)
        return None
    
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
    
    def parse_expression(self, min_precedence=0):
        left = self.parse_primary()
        
        while True:
            token = self.current_token()
            if token is None:
                break
            
            if token.kind not in [TokenType.ADD, TokenType.SUB, TokenType.MUL, 
                                 TokenType.DIV, TokenType.LEQ, TokenType.LTH, 
                                 TokenType.EQL, TokenType.NOT]:
                break
                
            precedence = self.precedence(token)
            if precedence < min_precedence:
                break
                
            self.consume()
            
            if token.kind in [TokenType.ADD, TokenType.SUB, TokenType.MUL,
                             TokenType.DIV, TokenType.LEQ, TokenType.LTH, TokenType.EQL]:
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
            elif token.kind == TokenType.NOT:
                pass
        
        return left

    def parse(self):
        return self.parse_expression()