import sys
import enum


class Token:
    """
    This class contains the definition of Tokens. A token has two fields: its
    text and its kind. The "kind" of a token is a constant that identifies it
    uniquely. See the TokenType to know the possible identifiers (if you want).
    You don't need to change this class.
    """
    def __init__(self, tokenText, tokenKind):
        # The token's actual text. Used for identifiers, strings, and numbers.
        self.text = tokenText
        # The TokenType that this token is classified as.
        self.kind = tokenKind


class TokenType(enum.Enum):
    """
    These are the possible tokens. You don't need to change this class at all.
    """
    EOF = -1  # End of file
    NLN = 0   # New line
    WSP = 1   # White Space
    COM = 2   # Comment
    NUM = 3   # Number (integers)
    STR = 4   # Strings
    TRU = 5  # The constant true
    FLS = 6  # The constant false
    VAR = 7  # An identifier
    LET = 8  # The 'let' of the let expression
    INX = 9  # The 'in' of the let expression
    END = 10  # The 'end' of the let expression
    IFX = 11   # The 'if' of the if-then-else expression
    THN = 12 # The 'then' of the if-then-else expression
    ELS = 13 # The 'else' of the if-then-else expression
    ORX = 14   # The 'or' logical operator
    AND = 15  # The 'and' logical operator
    EQL = 201
    ADD = 202
    SUB = 203
    MUL = 204
    DIV = 205
    LEQ = 206
    LTH = 207
    NEG = 208
    NOT = 209
    LPR = 210
    RPR = 211
    ASN = 212 # The assignment '<-' operator


class Lexer:
    def __init__(self, source):
        """
        The constructor of the lexer. It receives the string that shall be
        scanned.
        TODO: You will need to implement this method.
        """
        self.source = source
        self.curPos = -1
        self.curChar  = None
        self.advance()

    def advance(self):
        self.curPos += 1
        if self.curPos < len(self.source):
            self.curChar = self.source[self.curPos]
        else:
            self.curChar = None
    
    def peek(self):
        peek_pos = self.curPos + 1
        return self.source[peek_pos] if peek_pos < len(self.source) else None
    
    def skip_whitespace(self):
        while self.curChar is not None and self.curChar.isspace() and self.curChar != '\n':
            self.advance()
    
    def skip_line_comment(self):
        while self.curChar is not None and self.curChar != '\n':
            self.advance()
    
    def skip_block_comment(self):
        depth = 1
        while depth > 0 and self.curChar is not None:
            if self.curChar == '(' and self.peek() == '*':
                self.advance()
                self.advance()
                depth += 1
            elif self.curChar == '*' and self.peek() == ')':
                self.advance()
                self.advance()
                depth -= 1
            else:
                self.advance()
    
    def get_number(self):
        num_str = ''
        while self.curChar is not None and self.curChar.isdigit():
            num_str += self.curChar
            self.advance()
        return Token(num_str, TokenType.NUM)
    
    def get_var_or_keyword(self):
        var_str = ''
        while self.curChar is not None and (self.curChar.isalpha() or self.curChar.isdigit()):
            var_str += self.curChar
            self.advance()
        
        if var_str == 'let':
            return Token(var_str, TokenType.LET)
        elif var_str == 'in':
            return Token(var_str, TokenType.INX)
        elif var_str == 'end':
            return Token(var_str, TokenType.END)
        elif var_str == 'true':
            return Token(var_str, TokenType.TRU)
        elif var_str == 'false':
            return Token(var_str, TokenType.FLS)
        elif var_str == 'not':
            return Token(var_str, TokenType.NOT)
        elif var_str == 'if':
            return Token(var_str, TokenType.IFX)
        elif var_str == 'then':
            return Token(var_str, TokenType.THN)
        elif var_str == 'else':
            return Token(var_str, TokenType.ELS)
        elif var_str == 'or':
            return Token(var_str, TokenType.ORX)
        elif var_str == 'and':
            return Token(var_str, TokenType.AND)
        else:
            return Token(var_str, TokenType.VAR)
    

    def tokens(self):
        """
        This method is a token generator: it converts the string encapsulated
        into this object into a sequence of Tokens. Examples:

        >>> l = Lexer("1 + 3")
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.ADD: 202>, <TokenType.NUM: 3>]

        >>> l = Lexer('1 * 2 -- 3\\n')
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.MUL: 204>, <TokenType.NUM: 3>]

        >>> l = Lexer("1 + var")
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.ADD: 202>, <TokenType.VAR: 7>]

        >>> l = Lexer("let v <- 2 in v end")
        >>> [tk.kind.name for tk in l.tokens()]
        ['LET', 'VAR', 'ASN', 'NUM', 'INX', 'VAR', 'END']
        """
        token = self.getToken()
        while token.kind != TokenType.EOF:
            if token.kind != TokenType.WSP and token.kind != TokenType.COM and token.kind != TokenType.NLN:
                yield token
            token = self.getToken()

    def getToken(self):
        """
        Return the next token.
        TODO: Implement this method!
        """
        while self.curChar is not None:
            if self.curChar.isspace() and self.curChar != '\n':
                start_pos = self.curPos
                self.skip_whitespace()
                return Token(self.source[start_pos:self.curPos], TokenType.WSP)
            
            if self.curChar == '\n':
                self.advance()
                return Token('', TokenType.NLN)
            
            if self.curChar == '-' and self.peek() == '-':
                start_pos = self.curPos
                self.advance()
                self.advance()
                self.skip_line_comment()
                self.advance()
                return Token(self.source[start_pos:self.curPos], TokenType.COM)
            
            if self.curChar == '(' and self.peek() == '*':
                start_pos = self.curPos
                self.advance()
                self.advance()
                self.skip_block_comment()
                return Token(self.source[start_pos:self.curPos], TokenType.COM)
            
            if self.curChar.isdigit():
                return self.get_number()
            
            if self.curChar.isalpha():
                return self.get_var_or_keyword()
            
            if self.curChar == '<' and self.peek() == '-':
                self.advance()
                self.advance()
                return Token('<-', TokenType.ASN)
            
            if self.curChar == '=':
                self.advance()
                return Token('=', TokenType.EQL)
            elif self.curChar == '+':
                self.advance()
                return Token('+', TokenType.ADD)
            elif self.curChar == '-':
                self.advance()
                return Token('-', TokenType.SUB)
            elif self.curChar == '*':
                self.advance()
                return Token('*', TokenType.MUL)
            elif self.curChar == '/':
                self.advance()
                return Token('/', TokenType.DIV)
            elif self.curChar == '<':
                self.advance()
                if self.curChar == '=':
                    self.advance()
                    return Token('<=', TokenType.LEQ)
                else:
                    return Token('<', TokenType.LTH)
            elif self.curChar == '~':
                self.advance()
                return Token('~', TokenType.NEG)
            elif self.curChar == '(':
                self.advance()
                return Token('(', TokenType.LPR)
            elif self.curChar == ')':
                self.advance()
                return Token(')', TokenType.RPR)
            
            self.advance()
        
        return Token('', TokenType.EOF)