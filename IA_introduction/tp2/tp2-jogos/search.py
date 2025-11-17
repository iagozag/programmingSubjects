from typing import List, Tuple, Optional, Dict
import time
import math
import random

ROWS, COLS = 6, 7
EMPTY, P1, P2 = 0, 1, 2

# -----------------------------------------------------------------------------
# Utilidades de tabuleiro (PRONTAS)
# -----------------------------------------------------------------------------
def copy_board(board: List[List[int]]) -> List[List[int]]:
    return [row[:] for row in board]

def valid_moves(board: List[List[int]]) -> List[int]:
    """Retorna as colunas ainda jogáveis (topo vazio)."""
    return [c for c in range(COLS) if board[0][c] == EMPTY]

def make_move(board: List[List[int]], col: int, player: int) -> Optional[List[List[int]]]:
    """Retorna um novo tabuleiro aplicando a gravidade na coluna col; None se inválido."""
    if col < 0 or col >= COLS or board[0][col] != EMPTY:
        return None
    nb = copy_board(board)
    for r in reversed(range(ROWS)):
        if nb[r][col] == EMPTY:
            nb[r][col] = player
            return nb
    return None

def other(player: int) -> int:
    return P1 if player == P2 else P2

def winner(board: List[List[int]]) -> int:
    """0 se ninguém venceu; 1 ou 2 se há 4 em linha."""
    # Horizontais
    for r in range(ROWS):
        for c in range(COLS - 3):
            x = board[r][c]
            if x != EMPTY and x == board[r][c+1] == board[r][c+2] == board[r][c+3]:
                return x
    # Verticais
    for c in range(COLS):
        for r in range(ROWS - 3):
            x = board[r][c]
            if x != EMPTY and x == board[r+1][c] == board[r+2][c] == board[r+3][c]:
                return x
    # Diag ↘
    for r in range(ROWS - 3):
        for c in range(COLS - 3):
            x = board[r][c]
            if x != EMPTY and x == board[r+1][c+1] == board[r+2][c+2] == board[r+3][c+3]:
                return x
    # Diag ↗
    for r in range(3, ROWS):
        for c in range(COLS - 3):
            x = board[r][c]
            if x != EMPTY and x == board[r-1][c+1] == board[r-2][c+2] == board[r-3][c+3]:
                return x
    return 0

'''
def heuristic(board: List[List[int]], p: int) -> int:
    """0 se ninguém venceu; 1 ou 2 se há 4 em linha."""
    # Horizontais
    total = 0
    for r in range(ROWS):
        for c in range(COLS - 2):
            x = board[r][c]
            if x != EMPTY and x == board[r][c+1]:
                total += (1 if x == p else -1)*(2 + (5 if x == board[r][c+2] else 0))
    # Verticais
    for c in range(COLS):
        for r in range(ROWS - 2):
            x = board[r][c]
            if x != EMPTY and x == board[r+1][c]:
                total += (1 if x == p else -1)*(2 + (5 if x == board[r+2][c] else 0))
    # Diag ↘
    for r in range(ROWS - 2):
        for c in range(COLS - 2):
            x = board[r][c]
            if x != EMPTY and x == board[r+1][c+1]:
                total += (1 if x == p else -1)*(2 + (5 if x == board[r+2][c+2] else 0))
    # Diag ↗
    for r in range(2, ROWS):
        for c in range(COLS - 2):
            x = board[r][c]
            if x != EMPTY and x == board[r-1][c+1]:
                total += (1 if x == p else -1)*(2 + (5 if x == board[r-2][c+2] else 0))

    return total
'''

# Defina isso fora da função (constante)
POSITION_SCORE = [
    [10, 25, 50, 100, 50, 25, 10],
    [10, 25, 50, 100, 50, 25, 10],
    [10, 25, 50, 100, 50, 25, 10],
    [10, 25, 50, 100, 50, 25, 10],
    [10, 25, 50, 100, 50, 25, 10],
    [10, 25, 50, 100, 50, 25, 10],
]

# Função auxiliar para pontuar uma única janela de 4
def evaluate_window(window: List[int], p: int) -> int:
    score = 0
    opp = other(p) # Oponente

    my_pieces = window.count(p)
    opp_pieces = window.count(opp)
    empty = window.count(EMPTY)

    if my_pieces == 3 and empty == 1:
        score += 1000
    elif my_pieces == 2 and empty == 2:
        score += 50
    
    if opp_pieces == 3 and empty == 1:
        score -= 2000
    elif opp_pieces == 2 and empty == 2:
        score -= 50

    return score

def heuristic(board: List[List[int]], p: int) -> int:
    total_score = 0

    for c in range(COLS):
        for r in range(ROWS-1, -1, -1):
            if board[r][c] == EMPTY:
                break
            
            total_score += (1 if board[r][c] == p else -1)*POSITION_SCORE[r][c]

    # Horizontais
    for r in range(ROWS):
        for c in range(COLS - 3):
            window = [board[r][c], board[r][c+1], board[r][c+2], board[r][c+3]]
            total_score += evaluate_window(window, p)

    # Verticais
    for c in range(COLS):
        for r in range(ROWS - 3):
            window = [board[r][c], board[r+1][c], board[r+2][c], board[r+3][c]]
            total_score += evaluate_window(window, p)

    # Diag ↘
    for r in range(ROWS - 3):
        for c in range(COLS - 3):
            window = [board[r][c], board[r+1][c+1], board[r+2][c+2], board[r+3][c+3]]
            total_score += evaluate_window(window, p)

    # Diag ↗
    for r in range(3, ROWS):
        for c in range(COLS - 3):
            window = [board[r][c], board[r-1][c+1], board[r-2][c+2], board[r-3][c+3]]
            total_score += evaluate_window(window, p)

    return total_score


def is_full(board: List[List[int]]) -> bool:
    return all(board[0][c] != EMPTY for c in range(COLS))

def terminal(board: List[List[int]]) -> Tuple[bool, int]:
    """(é_terminal, vencedor) com vencedor=0 para empate/indefinido."""
    w = winner(board)
    if w != 0:
        return True, w
    if is_full(board):
        return True, 0
    return False, 0

# -----------------------------------------------------------------------------
# ÚNICO PONTO A SER IMPLEMENTADO PELOS ALUNOS
# -----------------------------------------------------------------------------
def choose_move(board: List[List[int]], turn: int, config: Dict) -> Tuple[int, Dict]:
    """
    Decide a coluna (0..6) para jogar agora.

    Parâmetros:
      - board: matriz 6x7 com valores {0,1,2}
      - turn: 1 ou 2
      - config: {"max_time_ms": int, "max_depth": int}

    Retorna:
      - col: int (0..6)
    """
    max_time_ms = int(config.get("max_time_ms"))
    max_depth = int(config.get("max_depth"))
    turn = int(turn)

    print(f"AI choose_move called with max_time_ms={max_time_ms}, max_depth={max_depth}, player={turn}")
    
    start = time.time()

    # Função auxiliar para checar tempo decorrido   
    def time_exceeded():
        return max_time_ms > 0 and (time.time() - start) * 1000.0 >= max_time_ms
    
    legal = valid_moves(board)

    move = 0
    if not legal:
        # Sem jogadas: devolve 0 por convenção (servidor lida com isso)
        return move
    
    # VERSÃO INICIAL: escolhe aleatoriamente entre as jogadas legais
    move = random.choice(legal)

    return move

def choose_move_infinity(board: List[List[int]], turn: int, config: Dict) -> Tuple[int, Dict]:
    """
    Decide a coluna (0..6) para jogar agora.

    Parâmetros:
      - board: matriz 6x7 com valores {0,1,2}
      - turn: 1 ou 2
      - config: {"max_time_ms": int, "max_depth": int}

    Retorna:
      - col: int (0..6)
    """
    max_time_ms = int(config.get("max_time_ms"))
    max_depth = int(config.get("max_depth"))
    turn = int(turn)

    print(f"AI choose_move called with max_time_ms={max_time_ms}, max_depth={max_depth}, player={turn}")
    
    start = time.time()

    # Função auxiliar para checar tempo decorrido   
    def time_exceeded():
        return max_time_ms > 0 and (time.time() - start) * 1000.0 >= max_time_ms
    
    legal = valid_moves(board)

    move = 0
    if not legal:
        # Sem jogadas: devolve 0 por convenção (servidor lida com isso)
        return move
    
    # VERSÃO INICIAL: escolhe aleatoriamente entre as jogadas legais
    i = 0
    while True:
        i += 1

    return move

def choose_move_minimax(board: List[List[int]], turn: int, config: Dict) -> Tuple[int, Dict]:
    """
    Decide a coluna (0..6) para jogar agora.

    Parâmetros:
      - board: matriz 6x7 com valores {0,1,2}
      - turn: 1 ou 2
      - config: {"max_time_ms": int, "max_depth": int}

    Retorna:
      - col: int (0..6)
    """
    max_time_ms = int(config.get("max_time_ms"))
    max_depth = int(config.get("max_depth"))
    turn = int(turn)

    print(f"AI choose_move called with max_time_ms={max_time_ms}, max_depth={max_depth}, player={turn}")
    
    start = time.time()

    # Função auxiliar para checar tempo decorrido   
    def time_exceeded():
        return max_time_ms > 0 and (time.time() - start) * 1000.0 >= max_time_ms
    
    legal = valid_moves(board)

    move = 0
    if not legal:
        # Sem jogadas: devolve 0 por convenção (servidor lida com isso)
        return move

    
    def minimax(s, depth, player):
        win = winner(s)
        if win != 0:
            return 1000000*(1 if win == turn else -1)

        if is_full(s):
            return 0

        if depth == 0 or time_exceeded():
            return heuristic(s, turn)

        # MAX
        if player == turn:
            best_val = -math.inf
            for mv in valid_moves(s):
                child = make_move(s, mv, player)
                best_val = max(best_val, minimax(child, depth-1, other(player)))
            return best_val

        # MIN
        best_val = math.inf
        for mv in valid_moves(s):
            child = make_move(s, mv, player)
            best_val = min(best_val, minimax(child, depth-1, other(player)))
        return best_val


    best_val = -math.inf
    best_move = -1
    for mv in legal:
        child = make_move(board, mv, turn)
        val = minimax(child, max_depth-1, other(turn))
        if val > best_val:
            best_val = val
            best_move = mv

    return best_move

def choose_move_minimax_alpha_beta(board: List[List[int]], turn: int, config: Dict) -> Tuple[int, Dict]:
    """
    Decide a coluna (0..6) para jogar agora.

    Parâmetros:
      - board: matriz 6x7 com valores {0,1,2}
      - turn: 1 ou 2
      - config: {"max_time_ms": int, "max_depth": int}

    Retorna:
      - col: int (0..6)
    """
    max_time_ms = int(config.get("max_time_ms"))
    max_depth = int(config.get("max_depth"))
    turn = int(turn)

    print(f"AI choose_move called with max_time_ms={max_time_ms}, max_depth={max_depth}, player={turn}")
    
    start = time.time()

    # Função auxiliar para checar tempo decorrido   
    def time_exceeded():
        return max_time_ms > 0 and (time.time() - start) * 1000.0 >= max_time_ms
    
    legal = valid_moves(board)

    move = 0
    if not legal:
        # Sem jogadas: devolve 0 por convenção (servidor lida com isso)
        return move
    

    def minimax2(s, alpha, beta, depth, player):
        win = winner(s)
        if win != 0:
            return 1000000*(1 if win == turn else -1)

        if is_full(s):
            return 0

        if depth == 0 or time_exceeded():
            return heuristic(s, turn)

        # MAX
        if player == turn:
            best_val = -math.inf
            for mv in valid_moves(s):
                child = make_move(s, mv, player)
                best_val = max(best_val, minimax2(child, alpha, beta, depth-1, other(player)))

                if best_val >= beta:
                    return best_val

                alpha = max(alpha, best_val)

            return best_val

        # MIN
        best_val = math.inf
        for mv in valid_moves(s):
            child = make_move(s, mv, player)
            best_val = min(best_val, minimax2(child, alpha, beta, depth-1, other(player)))

            if best_val <= alpha:
                return best_val
            
            beta = min(beta, best_val)

        return best_val


    best_val = -math.inf
    best_move = -1
    for mv in legal:
        child = make_move(board, mv, turn)
        val = minimax2(child, -math.inf, math.inf, max_depth-1, other(turn))
        if val > best_val:
            best_val = val
            best_move = mv

    return best_move

def choose_move_iterative_deepening(board: List[List[int]], turn: int, config: Dict) -> Tuple[int, Dict]:
    """
    Decide a coluna (0..6) para jogar agora.

    Parâmetros:
      - board: matriz 6x7 com valores {0,1,2}
      - turn: 1 ou 2
      - config: {"max_time_ms": int, "max_depth": int}

    Retorna:
      - col: int (0..6)
    """
    max_time_ms = int(config.get("max_time_ms"))
    max_depth = int(config.get("max_depth"))
    turn = int(turn)

    print(f"AI choose_move called with max_time_ms={max_time_ms}, max_depth={max_depth}, player={turn}")
    
    start = time.time()

    # Função auxiliar para checar tempo decorrido   
    def time_exceeded():
        return max_time_ms > 0 and (time.time() - start) * 1000.0 >= max_time_ms
    
    legal = valid_moves(board)

    move = 0
    if not legal:
        # Sem jogadas: devolve 0 por convenção (servidor lida com isso)
        return move
    

    def minimax2(s, alpha, beta, depth, player):
        win = winner(s)
        if win != 0:
            return 1000000*(1 if win == turn else -1)

        if is_full(s):
            return 0

        if depth == 0 or time_exceeded():
            return heuristic(s, turn)

        # MAX
        if player == turn:
            best_val = -math.inf
            for mv in valid_moves(s):
                child = make_move(s, mv, player)
                best_val = max(best_val, minimax2(child, alpha, beta, depth-1, other(player)))

                if best_val >= beta:
                    return best_val

                alpha = max(alpha, best_val)

            return best_val

        # MIN
        best_val = math.inf
        for mv in valid_moves(s):
            child = make_move(s, mv, player)
            best_val = min(best_val, minimax2(child, alpha, beta, depth-1, other(player)))

            if best_val <= alpha:
                return best_val
            
            beta = min(beta, best_val)

        return best_val


    best_val = -math.inf
    best_move = -1

    for i in range(1, max_depth+1):
        for mv in legal:
            child = make_move(board, mv, turn)
            val = minimax2(child, -math.inf, math.inf, i-1, other(turn))
            if val > best_val:
                best_val = val
                best_move = mv

    return best_move