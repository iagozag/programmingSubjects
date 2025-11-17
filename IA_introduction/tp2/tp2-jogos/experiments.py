import time
import search
from typing import Dict, List, Callable

# Configurações Globais
NUM_GAMES = 10  # Quantidade de jogos por par (quanto mais jogos, mais preciso, mas demora mais)

def init_board():
    return [[0]*7 for _ in range(6)]

def play_match(p1_func, p1_config, p2_func, p2_config):
    """
    Simula uma partida.
    Retorna:
    - winner: 1 (P1), 2 (P2), 0 (Empate)
    - stats_p1: {'time': [], 'nodes': [], 'depth': []}
    - stats_p2: {'time': [], 'nodes': [], 'depth': []}
    """
    board = init_board()
    turn = 1
    
    stats = {
        1: {'time': [], 'nodes': [], 'depth': []},
        2: {'time': [], 'nodes': [], 'depth': []}
    }
    
    funcs = {1: p1_func, 2: p2_func}
    configs = {1: p1_config, 2: p2_config}

    while True:
        is_term, win_player = search.terminal(board)
        if is_term:
            return win_player, stats[1], stats[2]

        start_t = time.time()
        move, info = funcs[turn](board, turn, configs[turn])
        end_t = time.time()
        
        elapsed = end_t - start_t
        
        # Coleta estatísticas
        stats[turn]['time'].append(elapsed)
        stats[turn]['nodes'].append(info.get('nodes', 0))
        stats[turn]['depth'].append(info.get('depth', 0))
        
        board = search.make_move(board, move, turn)
        turn = search.other(turn)

def print_results(title, p1_name, p2_name, results):
    p1_wins = results.count(1)
    p2_wins = results.count(2)
    draws = results.count(0)
    total = len(results)
    
    print(f"\n--- {title} ---")
    print(f"Total Jogos: {total}")
    print(f"{p1_name} (P1) Vitórias: {p1_wins} ({p1_wins/total*100:.1f}%)")
    print(f"{p2_name} (P2) Vitórias: {p2_wins} ({p2_wins/total*100:.1f}%)")
    print(f"Empates: {draws}")

def calculate_avg(stats_list, key):
    values = []
    for s in stats_list:
        values.extend(s[key])
    return sum(values) / len(values) if values else 0

def run_experiment_1():
    print("\n========================================")
    print("EXPERIMENTO 1: Minimax vs Aleatório")
    print("========================================")
    
    depths = [2, 3, 4, 5]
    
    print(f"{'Depth':<6} | {'WinRate(%)':<10} | {'AvgTime(s)':<10} | {'AvgNodes':<10}")
    print("-" * 45)
    
    for d in depths:
        results = []
        all_p1_stats = []
        
        for _ in range(NUM_GAMES):
            w, s1, s2 = play_match(
                search.choose_move_minimax, {"max_depth": d},
                search.choose_move, {} # Random
            )
            results.append(w)
            all_p1_stats.append(s1)
            
        win_rate = (results.count(1) / NUM_GAMES) * 100
        avg_time = calculate_avg(all_p1_stats, 'time')
        avg_nodes = calculate_avg(all_p1_stats, 'nodes')
        
        print(f"{d:<6} | {win_rate:<10.1f} | {avg_time:<10.4f} | {avg_nodes:<10.1f}")

def run_experiment_2():
    print("\n========================================")
    print("EXPERIMENTO 2: Alfa-Beta vs Minimax")
    print("========================================")
    
    depths = [2, 3, 4, 5]
    
    print(f"{'Depth':<6} | {'AB Win(%)':<10} | {'AB Time':<10} | {'Mini Time':<10} | {'AB Nodes':<10} | {'Mini Nodes':<10}")
    print("-" * 80)
    
    for d in depths:
        results = []
        stats_ab = []
        stats_mm = []
        
        games = 5 if d == 5 else NUM_GAMES 
        
        for _ in range(games):
            w, s1, s2 = play_match(
                search.choose_move_minimax_alpha_beta, {"max_depth": d},
                search.choose_move_minimax, {"max_depth": d}
            )
            results.append(w)
            stats_ab.append(s1)
            stats_mm.append(s2)
            
        ab_win_rate = (results.count(1) / games) * 100
        
        avg_time_ab = calculate_avg(stats_ab, 'time')
        avg_nodes_ab = calculate_avg(stats_ab, 'nodes')
        
        avg_time_mm = calculate_avg(stats_mm, 'time')
        avg_nodes_mm = calculate_avg(stats_mm, 'nodes')
        
        print(f"{d:<6} | {ab_win_rate:<10.1f} | {avg_time_ab:<10.4f} | {avg_time_mm:<10.4f} | {avg_nodes_ab:<10.1f} | {avg_nodes_mm:<10.1f}")

def run_experiment_3():
    print("\n========================================")
    print("EXPERIMENTO 3: Iterative Deepening vs Alfa-Beta (Fixed Time)")
    print("========================================")
    
    times = [1000, 2000] # ms
    
    print(f"{'Time(ms)':<8} | {'ID Win(%)':<10} | {'ID Depth':<10} | {'AB Depth':<10} | {'ID Nodes':<10} | {'AB Nodes':<10}")
    print("-" * 85)
    
    for t in times:
        results = []
        stats_id = []
        stats_ab = []
        
        for _ in range(NUM_GAMES):
            w, s1, s2 = play_match(
                search.choose_move_iterative_deepening, {"max_time_ms": t, "max_depth": 10},
                search.choose_move_minimax_alpha_beta, {"max_time_ms": t, "max_depth": 10} # AB tenta ir até 10 mas tem timeout
            )
            results.append(w)
            stats_id.append(s1)
            stats_ab.append(s2)
            
        id_win_rate = (results.count(1) / NUM_GAMES) * 100
        
        avg_depth_id = calculate_avg(stats_id, 'depth')
        avg_nodes_id = calculate_avg(stats_id, 'nodes')
        
        avg_depth_ab = calculate_avg(stats_ab, 'depth') # AB retorna profundidade máxima tentada
        avg_nodes_ab = calculate_avg(stats_ab, 'nodes')
        
        print(f"{t:<8} | {id_win_rate:<10.1f} | {avg_depth_id:<10.1f} | {avg_depth_ab:<10.1f} | {avg_nodes_id:<10.1f} | {avg_nodes_ab:<10.1f}")

if __name__ == "__main__":
    run_experiment_3()