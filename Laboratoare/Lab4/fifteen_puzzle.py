from search import FifteenPuzzle


class FifteenPuzzleMiss(FifteenPuzzle):
    def h(self, node):
        """ Return the heuristic value for a given state. Default heuristic function used is
        h(n) = number of misplaced tiles """
        return sum(s != g for (s, g) in zip(node.state, self.goal))
    
        
class FifteenPuzzleMht(FifteenPuzzle):
    def h(self, node):
        """ implement Manhattan distance. Hint! Look at
        Missplaced Tiles heuristic function above """
        return sum((abs(self.goal.index(s)/4 - node.state.index(s)/4) + abs(self.goal.index(s)%4 - node.state.index(s)%4)) for(s) in self.goal)