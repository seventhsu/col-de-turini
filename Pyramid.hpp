#pragma once

#include <iostream>
#include <string>

typedef struct MoveTreeNode {
	bool both_pyramid;
	int row1;
	int col1;
} MoveNode;

class Pyramid {
	public:
		void initPyramid(std::string fileloc);
	private:
		MoveNode *moveTree;
		int *pyramidArr[];
		int deck[];
};
