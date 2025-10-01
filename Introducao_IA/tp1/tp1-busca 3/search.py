import heapq
from math import sqrt
from collections import deque

WALL = 'X'
START_STATE = 'S'
GOAL_STATE  = 'G'

def plan(map, algorithm='bfs', heuristic=None):
    """ Loads a level, searches for a path between the given waypoints, and displays the result.

    Args:
        filename: The name of the text file containing the level.
        src_waypoint: The character associated with the initial waypoint.
        dst_waypoint: The character associated with the destination waypoint.

    """
    print(map)
    print("Algorithm:", algorithm)
    print("Heuristic:", heuristic)

    # Load the level from the file
    level = parse_level(map)

    # Retrieve the source and destination coordinates from the level.
    start = level['start']
    goal = level['goal']

    # Search for and display the path from src to dst.
    path = []
    visited = {}

    if algorithm == 'bfs':
        path, visited = bfs(start, goal, level, transition_model)
    elif algorithm == 'dfs':
        path, visited = dfs(start, goal, level, transition_model)
    elif algorithm == 'ucs':
        path, visited = ucs(start, goal, level, transition_model)
    elif algorithm == 'greedy':
        if heuristic == 'euclidian':
            path, visited = greedy_best_first(start, goal, level, transition_model, h_euclidian)
        elif heuristic == 'manhattan':
            path, visited = greedy_best_first(start, goal, level, transition_model, h_manhattan)
    elif algorithm == 'astar':
        if heuristic == 'euclidian':
            path, visited = a_star(start, goal, level, transition_model, h_euclidian)
        elif heuristic == 'manhattan':
            path, visited = a_star(start, goal, level, transition_model, h_manhattan)

    return path, path_cost(path, level), visited

def parse_level(map):
    """ Parses a level from a string.

    Args:
        level_str: A string containing a level.

    Returns:
        The parsed level (dict) containing the locations of walls (set), the locations of spaces 
        (dict), and a mapping of locations to waypoints (dict).
    """
    start = None
    goal = None
    walls = set()
    spaces = {}

    for j, line in enumerate(map.split('\n')):
        for i, char in enumerate(line):
            if char == '\n':
                continue
            elif char == WALL:
                walls.add((i, j))
            elif char == START_STATE:
                start = (i, j)
                spaces[(i, j)] = 1.
            elif char == GOAL_STATE:
                goal = (i, j) 
                spaces[(i, j)] = 1.
            elif char.isnumeric():
                spaces[(i, j)] = float(char)

    level = {'walls': walls, 'spaces': spaces, 'start': start, 'goal': goal}

    return level

def path_cost(path, level):
    """ Returns the cost of the given path.

    Args:
        path: A list of cells from the source to the goal.
        level: A loaded level, containing walls, spaces, and waypoints.

    Returns:
        The cost of the given path.
    """
    cost = 0
    for i in range(len(path) - 1):
        cost += cost_function(level, path[i], path[i + 1], 
                              level['spaces'][path[i]], 
                              level['spaces'][path[i + 1]])

    return cost

# =============================
# Transition Model
# =============================

def cost_function(level, state1, state2, cost1, cost2):
    """ Returns the cost of the edge joining state1 and state2.

    Args:
        state1: A source location.
        state2: A target location.

    Returns:
        The cost of the edge joining state1 and state2.
    """
    dx = state1[0] - state2[0]
    dy = state1[1] - state2[1]
    dist = sqrt(dx * dx + dy * dy)

    avg_cost = (cost1 + cost2) / 2.0

    return dist * avg_cost

def transition_model(level, state1):
    """ Provides a list of adjacent states and their respective costs from the given state.

    Args:
        level: A loaded level, containing walls, spaces, and waypoints.
        state: A target location.

    Returns:
        A list of tuples containing an adjacent sates's coordinates and the cost of 
        the edge joining it and the originating state.

        E.g. from (0,0):
            [((0,1), 1),
             ((1,0), 1),
             ((1,1), 1.4142135623730951),
             ... ]
    """
    adj_states = {}
    neighbors_offsets = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]

    for dx, dy in neighbors_offsets:
        nx = state1[0] + dx
        ny = state1[1] + dy
        neighbor = (nx, ny)

        if neighbor in level['spaces']:
            cost1 = level['spaces'][state1]
            cost2 = level['spaces'][neighbor]
            edge_cost = cost_function(level, state1, neighbor, cost1, cost2)
            adj_states[neighbor] = edge_cost

    return adj_states.items()

# =============================
# Uninformed Search Algorithms
# =============================

def reconstruct_path(parents, start, goal):
    """Helper to rebuild path from parents dict. Returns list from start to goal (inclusive)."""
    if goal not in parents:
        return []
    path = []
    node = goal

    while node is not None:
        path.append(node)
        node = parents.get(node)
    path.reverse()

    if len(path) == 0 or path[0] != start:
        return []
    return path

def bfs(s, g, level, adj):
    """ Searches for a path from the source to the goal using the Breadth-First Search algorithm.
    """
    visited = {s: None}
    queue = deque()
    queue.append(s)

    while queue:
        current = queue.popleft()
        if current == g:
            path = reconstruct_path(visited, s, g)
            return path, visited
        for neighbor, _cost in adj(level, current):
            if neighbor not in visited:
                visited[neighbor] = current
                queue.append(neighbor)

    return [], visited

def dfs(s, g, level, adj):
    """ Searches for a path from the source to the goal using the Depth-First Search algorithm.
    """
    visited = {s: None}
    stack = [s]

    while stack:
        current = stack.pop()
        if current == g:
            path = reconstruct_path(visited, s, g)
            return path, visited
        for neighbor, _cost in adj(level, current):
            if neighbor not in visited:
                visited[neighbor] = current
                stack.append(neighbor)

    return [], visited

def ucs(s, g, level, adj):
    """ Searches for a path from the source to the goal using the Uniform-Cost Search algorithm.
    """
    visited = {s: None}
    cost_so_far = {s: 0.0}
    heap = []
    heapq.heappush(heap, (0.0, s))

    while heap:
        current_cost, current = heapq.heappop(heap)

        if current_cost > cost_so_far.get(current, float('inf')):
            continue
        if current == g:
            path = reconstruct_path(visited, s, g)
            return path, visited
        for neighbor, edge_cost in adj(level, current):
            new_cost = current_cost + edge_cost
            if neighbor not in cost_so_far or new_cost < cost_so_far[neighbor]:
                cost_so_far[neighbor] = new_cost
                visited[neighbor] = current
                heapq.heappush(heap, (new_cost, neighbor))

    return [], visited

# ======================================
# Informed (Heuristic) Search Algorithms
# ======================================
def greedy_best_first(s, g, level, adj, h):
    """ Searches for a path from the source to the goal using the Greedy Best-First Search algorithm.
    """
    visited = {s: None}
    heap = []

    heapq.heappush(heap, (h(s, g), s))
    closed = set()

    while heap:
        _, current = heapq.heappop(heap)
        if current in closed:
            continue
        closed.add(current)
        if current == g:
            path = reconstruct_path(visited, s, g)
            return path, visited
        for neighbor, _edge_cost in adj(level, current):
            if neighbor not in closed and neighbor not in visited:
                visited[neighbor] = current
                heapq.heappush(heap, (h(neighbor, g), neighbor))

    return [], visited

def a_star(s, g, level, adj, h):
    """ Searches for a path from the source to the goal using the A* algorithm.
    """
    visited = {s: None}
    g_cost = {s: 0.0}
    heap = []
    heapq.heappush(heap, (h(s, g), s))

    while heap:
        f_current, current = heapq.heappop(heap)

        if current == g:
            path = reconstruct_path(visited, s, g)
            return path, visited

        if f_current > g_cost.get(current, float('inf')) + h(current, g):
            continue
        for neighbor, edge_cost in adj(level, current):
            tentative_g = g_cost[current] + edge_cost
            if neighbor not in g_cost or tentative_g < g_cost[neighbor]:
                g_cost[neighbor] = tentative_g
                visited[neighbor] = current
                heapq.heappush(heap, (tentative_g + h(neighbor, g), neighbor))

    return [], visited

# ======================================
# Heuristic functions
# ======================================
def h_euclidian(s, g):
    """ Estimates the cost from the current cell to the goal using the Euclidian distance.
    """
    dx = s[0] - g[0]
    dy = s[1] - g[1]
    return sqrt(dx * dx + dy * dy)

def h_manhattan(s, g):
    """ Estimates the cost from the current cell to the goal using the Manhattan distance.
    """
    return abs(s[0] - g[0]) + abs(s[1] - g[1])
