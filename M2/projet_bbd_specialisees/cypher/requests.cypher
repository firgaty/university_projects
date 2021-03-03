MATCH (g:Game)-[:published_by]->(s:Studio)
WHERE s.name = "Nintendo"
AND g.rank <= 100
RETURN g.name, g.rank
LIMIT 50

MATCH (g:Game)-[:published_by]->(s:Studio)
MATCH (g:Game)-[:on]->(p:Platform)
WHERE p.name = "PS3" AND g.global_sales >= 20
RETURN s.name

MATCH (g:Game)-[:published_by]->(s:Studio)-[:published]->(games:Game)
WHERE g.name = "The Elder Scrolls V: Skyrim"
AND games.year > 2000
RETURN games

MATCH (g:Game)-[:published_by]->(:Studio)-[:published]->(:Game)-[:on]->(p:Platform)
WHERE g.name = "Super Mario Bros."
RETURN p

MATCH (s:Studio)-[:published]->(g:Game)
WHERE s.name = "Capcom"
RETURN avg(g.global_sales)

MATCH (g:Game) 
WHERE g.name STARTS WITH "Grand Theft Auto"
RETURN AVG(g.global_sales)

MATCH (g:Game)-[:on]->(p:Platform)
WITH p.name as plateform, avg(g.global_sales) as avg_sales
RETURN plateform, avg_sales

MATCH (g:Game)
WHERE g.name STARTS WITH "Z"
RETURN min(g.rank)

MATCH (g:Game)-[:on]->(p:Platform)
MATCH (g:Game)-[:published_by]->(s:Studio)
WHERE p.name = "PS3"
WITH s.name AS studio, count(g) AS nb
WHERE nb > 100
RETURN studio, nb

MATCH (g:Game)-[:published_by]->(s:Studio)
WHERE s.name = "Ubisoft"
RETURN max(g.global_sales)

MATCH (g:Game)-[:on]->(p:Plateform)
MATCH (g:Game)-[:belong_to]->(genre:Genre)
WHERE p.name = "DS"
RETURN genre

CALL gds.graph.create.cypher(
    'games-platform',
    'MATCH (g:Game) RETURN id(g) as id',
    'MATCH (g1:Game)-[:on]->(:Platform)<-[:on]-(g2:Game)
     RETURN id(g1) as source, id(g2) as target, "SAME" as type'
)

MATCH (start: Game{name: "Grand Theft Auto V"}), (end: Game{name: "Call of Duty: Black Ops II"})
CALL gds.alpha.shortestPath.stream('games-platform', {
    startNode: start,
    endNode: end
})
YIELD nodeId, cost
RETURN gds.util.asNode(nodeId).name AS name, cost

CALL gds.alpha.degree.stream('games-platform')
YIELD nodeId, score
RETURN gds.util.asNode(nodeId).name as name, score

CALL gds.graph.create.cypher(
   'games-studio',
   'MATCH (g:Game) RETURN id(g) as id',
   'MATCH (g1:Game)-[:published_by]->(:Studio)<-[:published_by]-(g2:Game)
    RETURN id(g1) as source, id(g2) as target, "SAME" as type'
)

CALL gds.wcc.stream('games-studio')
YIELD nodeId, componentId
RETURN gds.util.asNode(nodeId).name as name, componentId as component

CALL gds.wcc.stats('games-studio')
YIELD  componentCount,  createMillis,  computeMillis,  postProcessingMillis,
componentDistribution, configuration

CALL gds.pageRank.stream('games-studio') YIELD nodeId, score
RETURN gds.util.asNode(nodeId) as game, score
ORDER BY score
LIMIT 10

