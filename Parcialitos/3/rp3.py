

# 1- Implementar un algoritmo que reciba un grafo no dirigido y un valor K,
# y nos devuelva el K-core de dicho grafo.
#
def kCores(grafo, k):

    kcore = grafo.copy()
    orden = {}
    vertices = kcore.obtener_vertices()

    for v in vertices:
        orden[v] = len(kcore.adyacentes(v))
    for v in vertices:
        if orden[v] < k:
            for w in kcore.adyacentes(v):
                orden[w] -= 1
            kcore.delete(v)

    return kcore


# 3- Un grupo de estudiantes de computación ha decidido jugar un partido de paintball.
# Para que sea más divertido, decidieron que cada uno debería jugar contra sus más  íntimos amigos.
# Es por eso que armaron un grafo no dirigido, sin peso, en el que cada vértice es un jugador,
# y cada arista(u, v) representa
# que u es mejor amigo de v y viceversa. Considerar que las relaciones de “mejor amistad” son simétricas.
# Escribir un algoritmo que devuelva true o false de acuerdo a si es posible crear dos equipos en dónde
# no haya dos mejores
# amigos del mismo lado(más allá de si los equipos quedan con la misma cantidad de jugadores o no).
# ¿Cuál es el orden del algoritmo? ¿Qué tipo de recorrido utiliza?

def equipo(grafo):
    visitados = set()
    equipo = {}

    for v in grafo:
        if v not in visitados:
            equipo[v] = 1
            if not _equipos(grafo, v, visitados, equipo):
                return False
    return True


def _equipos(grafo, v, visitados, equipo):
    visitados.add(v)
    for w in grafo.adyacentes(v):
        if w in visitados:
            if equipo[w] == equipo[v]:  # esten en el mismo equipo
                return False
        else:
            equipo[w] = equipo[v]*-1
            if not _equipos(grafo, w, visitados, equipo):  # DFS
                return False
    return True

# El orden es O(V+E) Donde V son los vertices y E las aristas del grafo.
# El recorrido utilizado fue DFS ya que en cada vertice se realiza una visita recursiva a sus adyacencias.
# El orden de realizar solamente DFS es O(V) y este se hace en un ciclo de adyacentes (E) sin contar los visitados.
