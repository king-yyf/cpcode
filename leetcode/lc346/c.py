class Solution:
    def punishmentNumber(self, n: int) -> int:

        s = str(n)
        p = n

        def dfs(i: int, strset: set):
            if i == n:
                return len(strset)
            ans = 0
            for j in range(i + 1, n + 1):
                if s[i:j] not in strset:
                    strset.add(s[i:j])
                    ans = max(ans, dfs(j, strset))
                    strset.remove(s[i:j])
            return ans



def shortestPath(edges, n, source, destination, target):
    # Identify source and destination nodes
    sourceNode = source
    destNode = destination
    
    # Initialize distance array and modified array
    distance = [float('inf')]*n
    distance[sourceNode] = 0
    modified = [0]*len(edges)
    
    # Create adjacency list
    adjList = [[] for _ in range(n)]
    for i, (a, b, w) in enumerate(edges):
        adjList[a].append((b, w, i))
        adjList[b].append((a, w, i))
    
    # Priority queue for Dijkstra's
    pq = [(0, sourceNode)]
    
    # Dijkstra's algorithm with modifications for -1 weights
    while pq:
        currDist, currNode = heapq.heappop(pq)
        if currNode == destNode:
            break
        if currDist > distance[currNode]:
            continue
        for adjNode, weight, idx in adjList[currNode]:
            if weight == -1:
                for mod in range(1, 2*10**9):
                    newDist = distance[currNode] + mod
                    if newDist <= target + distance[sourceNode]:
                        adjDist = distance[adjNode]
                        if adjDist > newDist:
                            distance[adjNode] = newDist
                            heapq.heappush(pq, (newDist, adjNode))
                            modified[idx] = 1
                        break
            else:
                adjDist = distance[adjNode]
                newDist = currDist + weight
                if adjDist > newDist:
                    distance[adjNode] = newDist
                    heapq.heappush(pq, (newDist, adjNode))
    
    # Check if target distance was achieved
    if distance[destNode] == target + distance[sourceNode]:
        return [[a, b, target + abs(distance[b] - distance[a])] if status==1 else [a, b, w] for ([a, b, w], status) in zip(edges, modified)]
    else:
       return []