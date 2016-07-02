#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <math.h>

//#define dimacs_mode
//#define mtx_mode
#define howard_mode

//#define edge_modular_weight_mode

using namespace std;

class Vertex
{
private:
	int *neighbors;
	int *adj_edges;
	int degree;
public:
	Vertex()
	{
		neighbors = NULL;
		adj_edges = NULL;
		degree = 0;
	}
	~Vertex()
	{
		free_neighborhood_space();
	}
	void allocate_neighborhood_space(int dgr)
	{
		neighbors = new int[dgr];
		adj_edges = new int[dgr];
	}
	void free_neighborhood_space()
	{
		delete[] neighbors;
		delete[] adj_edges;
	}
	void add_neighbor(int name, int index)
	{
		neighbors[index] = name;
	}
	void add_adj_edge(int name, int index)
	{
		adj_edges[index] = name;
	}
	int *get_neighbors()
	{
		return neighbors;
	}
	int *get_adj_edges()
	{
		return adj_edges;
	}
	void set_degree(int d)
	{
		degree = d;
	}
	int get_degree()
	{
		return degree;
	}
	void show_neighbors()
	{
		cout << "neighbors: ";
		for(int i = 0; i < degree; i++)
		{
			cout << neighbors[i] << '\t';
		}
		cout << endl;
	}
};

class Edge
{
private:
	int v1, v2;
	long double weight;
public:
	Edge(){}
	void set_vertices(int u1, int u2)
	{
		v1 = u1;
		v2 = u2;
	}
	void get_vertices(int &u1, int &u2)
	{
		u1 = v1;
		u2 = v2;
	}
	void set_weight(long double w)
	{
		weight = w;
	}
	long double get_weight()
	{
		return weight;
	}
	~Edge(){}
};

class Graph
{
protected:
	Vertex *vertices;
	Edge	*edges;
	int v_num;
	int e_num;
	int max_degree;
	unordered_set<long> edge_hash_id_set;
	unordered_map< long, int> edge_hash_id_to_its_index;
private:
	void encode_pairID(long &pairID, long n1, long n2)
	{
		pairID = ((n1 + n2 + 1) * (n1 + n2) >> 1) + n2;
	}
	void decode_pairID(long pairID, long &n1, long &n2)
	{
		int w = int((sqrt(double((pairID << 3) + 1)) - 1) / 2);
		int t = (w * w + w) >> 1;
		n2 = pairID - t;
		n1 = w - n2; 
	}
	void insertEdgeHashIDToSet(int n1, int n2)
	{
		long edge_hash_id;
		long u, v;
		if(n1 < n2)
		{
			u = long(n1); v = long(n2);
		}
		else
		{
			u = long(n2); v = long(n1);
		}
		encode_pairID(edge_hash_id, u, v);
		edge_hash_id_set.insert(edge_hash_id);
	}
	void insert_vertex_pair_to_edge_into_map(int v1, int v2, int e)
	{
		long pairID;
		int u1, u2;
		if(v1 < v2)
		{
			u1 = v1; u2 = v2;
		}
		else
		{
			u1 = v2; u2 = v1;
		}
		encode_pairID(pairID, u1, u2);
		edge_hash_id_to_its_index[pairID] = e;
	}
public:
	Graph(char *filename)
	{

		ifstream infile(filename);
		if(infile == NULL)
		{
			cout << "File " << filename << " cannot be opened" << endl;
			exit(1);
		}

		char line[1024];
		infile.getline(line, 1024);

#ifdef howard_mode
		sscanf(line, "%d %d", &v_num, &e_num);
#endif
#ifdef dimacs_mode
		while(line[0] != 'p')
			infile.getline(line, 1024);
#endif
#ifdef mtx_mode
		while(line[0] == '%')
			infile.getline(line, 1024);
#endif


#ifdef dimacs_mode		
		char tempstr1[1024], tempstr2[1024];
		sscanf(line, "%s %s %d %d", tempstr1, tempstr2, &v_num, &e_num);
#endif

#ifdef mtx_mode
		int tmp_int;
		sscanf(line, "%d %d %d", &tmp_int, &v_num, &e_num);
#endif

		vertices = new Vertex[v_num + 2];
		edges = new Edge[e_num + 2];
#ifdef dimacs_mode
		char ch_tmp;
#endif

#ifdef howard_mode
		int e_index;
		long double e_weight;
#endif

		int v1, v2;
		int *v_degree_tmp = new int[v_num + 2];
		memset(v_degree_tmp, 0, sizeof(int) * (v_num + 2));

		int e;
		for(e = 0; e < e_num; e++)
		{
#ifdef howard_mode
			infile >> e_index >> v1 >> v2 >> e_weight;
			if(e_index != e)
			{
				cout << "e_index read incorrectly" << endl;
				exit(1);
			}
			edges[e].set_weight(e_weight);
#endif
#ifdef dimacs_mode
			infile >> ch_tmp >> v1 >> v2;
#endif
#ifdef mtx_mode
			infile >> v1 >> v2;
#endif
			edges[e].set_vertices(v1, v2);
			v_degree_tmp[v1]++;
			v_degree_tmp[v2]++;
			insertEdgeHashIDToSet(v1, v2);
			insert_vertex_pair_to_edge_into_map(v1, v2, e);
		}

		int v;
		for(v = 1; v <= v_num; v++)
		{
			vertices[v].allocate_neighborhood_space(v_degree_tmp[v]);
			vertices[v].set_degree(v_degree_tmp[v]);
		}
		max_degree = v_degree_tmp[1];
		for(int i = 2; i <= v_num; i++)
		{
			if(v_degree_tmp[i] > max_degree)
				max_degree = v_degree_tmp[i];
		}

#ifdef edge_modular_weight_mode
		for(e = 0; e < e_num; e++)
		{
			int v1, v2;
			edges[e].get_vertices(v1, v2);
			edges[e].set_weight(((v1 + v2) % 200) + 1);
		}
#endif
		memset(v_degree_tmp, 0, sizeof(int) * (v_num + 2));
		for(e = 0; e < e_num; e++)
		{
			edges[e].get_vertices(v1, v2);
			vertices[v1].add_neighbor(v2, v_degree_tmp[v1]);
			vertices[v2].add_neighbor(v1, v_degree_tmp[v2]);
			vertices[v1].add_adj_edge(e, v_degree_tmp[v1]);
			vertices[v2].add_adj_edge(e, v_degree_tmp[v2]);
			v_degree_tmp[v1]++;
			v_degree_tmp[v2]++;
		}

		delete[] v_degree_tmp;
		infile.close();
	}
	Vertex* get_vertices()
	{
		return vertices;
	}
	int get_max_degree()
	{
		return max_degree;
	}
	int isConnected(int n1, int n2)
	{
		long edge_hash_id;
		long u, v;
		if(n1 < n2)
		{
			u = long(n1); v = long(n2);
		}
		else
		{
			u = long(n2); v = long(n1);
		}
		encode_pairID(edge_hash_id, u, v);
		return edge_hash_id_set.count(edge_hash_id);
	}
	int edge_index_of(int n1, int n2)
	{
		long pairID;
		int m1, m2;
		if(n1 < n2)
		{
			m1 = n1; m2 = n2;
		}
		else
		{
			m1 = n2; m2 = n1;
		}
		encode_pairID(pairID, m1, m2);
		return edge_hash_id_to_its_index[pairID];
	}
	~Graph()
	{
		delete[] vertices;
		delete[] edges;
	}
};
#endif
