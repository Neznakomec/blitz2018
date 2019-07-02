#include <iostream>
#include <stdio.h>
#include <set>
#include <math.h>
#include <utility>      // std::pair

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	int n,m,p;
	cin >> n >> m;


	set< std::pair<int,int> > edges(m);
	for (int i = 0; i < m; i++) {
		int m1,m2;
		cin >> m1 >> m2;
		edges.insert( pair<int,int>(m1,m2) );
	}

	cin >> p;
//
	PriorityQueue<WaveInfo> waves = new PriorityQueue<WaveInfo>(n, new Comparator<WaveInfo>() {

		@Override
		public int compare(WaveInfo o1, WaveInfo o2) {
			return o1.distanceFromStart - o2.distanceFromStart;
		}
	});
	for (int vertex = 1; vertex <= n; vertex++) {
		waves.add(new WaveInfo(vertex, vertex != p ? Integer.MAX_VALUE : 0));
	}

	PriorityQueue<WaveInfo> answer = new PriorityQueue<>(n, new Comparator<WaveInfo>() {

		@Override
		public int compare(WaveInfo o1, WaveInfo o2) {
			return o1.vertexNumber - o2.vertexNumber;
		}
	});

	//
	int currentWave = 0;
	while (waves.isEmpty() == false) {
		List<WaveInfo> processing = new LinkedList<>();
		while (waves.isEmpty() == false && waves.peek().distanceFromStart == currentWave) {
			processing.add(waves.poll());
		}

		if (processing.isEmpty()) {
			// write answer for unaccessible vertexes
			while (waves.isEmpty() == false) {
				WaveInfo info = waves.poll();
				info.distanceFromStart = -1;
				answer.add(info);
			}
		}

		for (WaveInfo currentVertex : processing) {
			Iterator<WaveInfo> it = waves.iterator();
			List<WaveInfo> toProcess = new LinkedList<>();
			while (it.hasNext()) {
				WaveInfo info = it.next();
				if (info.distanceFromStart == Integer.MAX_VALUE) {
					Pair edge;
					if (info.vertexNumber < currentVertex.vertexNumber) {
						edge = new Pair(info.vertexNumber, currentVertex.vertexNumber);
					} else {
						edge = new Pair(currentVertex.vertexNumber, info.vertexNumber);
					}

					if (rebra.contains(edge) == false) {
						info.distanceFromStart = currentWave + 1;
						toProcess.add(info);
						it.remove();
					}
				}
			}
			waves.addAll(toProcess);

			answer.add(currentVertex);
		}

		currentWave++;
	}

	answer.poll(); // this is "p" vertex
	while (answer.isEmpty() == false) {
		out.print(answer.poll().distanceFromStart);
		out.print(" ");
	}

	return 0;
}
