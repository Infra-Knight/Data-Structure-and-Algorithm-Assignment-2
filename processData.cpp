/*
* ==========================================================================================
* Name        : processData.cpp
* Description : student code for Assignment 2 - Data structures and Algorithms - Spring 2017
* ==========================================================================================
*/
#include <iostream>

#include "requestLib.h"
#include "dbLib.h"

using namespace std;

#define GPS_DISTANCE_ERROR 0.005
bool initBusGlobalData(void** pGData) {
	return 1;
}
void releaseBusGlobalData(void* pGData) {
	return;
}
int cmpDelta(double a, double b, double delta) {
	if (a >= b - delta && a <= b + delta) {
		return 0;
	}
	if (a < b - delta) return -1;
	if (a > b + delta) return 1;
}
int cmpDeltaLat(VRecord a, VRecord b, double delta) {
	return cmpDelta(a.latitude, b.latitude, delta);
}
int cmpDeltaLong(VRecord a, VRecord b, double delta) {
	return cmpDelta(a.longitude, b.longitude, delta);
}
AVLTree<VRecord> *latTree = new AVLTree<VRecord>();
AVLTree<VRecord> *longTree = new AVLTree<VRecord>();
bool sslat(VRecord a, VRecord b) {
	return (a.latitude < b.latitude);
};
bool sslong(VRecord a, VRecord b) {
	return (a.longitude < b.longitude);
};
bool ssid(VRecord a, VRecord b) {
	return strcmp(a.id, b.id);
};
int ispass(double t, double y, double delta) {
	if (t < y - delta) {
		return 1;
	}
	else if (t > y + delta) {
		return -1;
	}
	else return 0;
}
void taocayAVL(VRecord &node) {
	latTree->insertlat(node);
	longTree->insertlong(node);
};
void print(AVLNode<VRecord> *root) {
	if (root) {
		print(root->_pLeft);
		cout << (int)root->_data.longitude << " ";

		print(root->_pRight);
	}
}
void traverse1A(AVLNode<VRecord>* root, char *id, double y, double Delta, int &param) {
	if (root) {
		//cout << root->_data.latitude << " ";
		if (ispass(root->_data.latitude, y, Delta) == -1) {

			traverse1A(root->_pLeft, id, y, Delta, param);
		}
		else if (ispass(root->_data.latitude, y, Delta) == 1) {
			//cout << "aaa";
			traverse1A(root->_pRight, id, y, Delta, param);
		}
		else {

			if (!strcmp(root->_data.id, id)) {
				param++;
			}
			traverse1A(root->_pLeft, id, y, Delta, param);
			traverse1A(root->_pRight, id, y, Delta, param);
		}
	}
};

void Event1A(AVLTree<VRecord>* latTree, char* id, double y_lat, double Delta_lat) {
	AVLNode<VRecord> *root = latTree->getRoot();
	//print(root);
	//cout << endl;
	int size = 0;
	traverse1A(root, id, y_lat, Delta_lat, size);
	if (!size)
		cout << "No" << endl;
	else
		cout << "Yes" << endl;
	return;
}
void traverse1B(AVLNode<VRecord> *root, char *id, double y, double Delta, int &param) {
	if (root) {
		if (ispass(root->_data.longitude, y, Delta) == -1) {
			traverse1B(root->_pLeft, id, y, Delta, param);
		}
		else if (ispass(root->_data.longitude, y, Delta) == 1) {
			traverse1B(root->_pRight, id, y, Delta, param);
		}
		else {
			if (!strcmp(root->_data.id, id)) {
				param++;
			}
			traverse1B(root->_pLeft, id, y, Delta, param);
			traverse1B(root->_pRight, id, y, Delta, param);
		}
	}
};
void Event1B(AVLTree<VRecord> *longTree, char* id, double y_long, double Delta_long) {
	AVLNode<VRecord> *root = longTree->getRoot();
	int size = 0;
	traverse1B(root, id, y_long, Delta_long, size);
	if (!size)
		cout << "No" << endl;
	else
		cout << "Yes" << endl;
	return;
};

//void Event2A(AVLTree<VRecord> *latTree, char* id, double y_lat, double Delta_lat) {
//	AVLNode<VRecord> *root = latTree->getRoot();
//	int size = 0;
//	traverse1A(root, id, y_lat, Delta_lat, size);
//	cout << size;
//	return;
//}
//void Event2B(AVLTree<VRecord> *longTree, char* id, double y_long, double Delta_long) {
//	AVLNode<VRecord> *root = longTree->getRoot();
//	int size = 0;
//	traverse1B(root, id, y_long, Delta_long, size);
//	cout << size;
//	return;
//};
struct infoRecord {
	char _ID[16];
	double _lat, _long, _Deltalat, _Deltalong;
	bool _exist;
	int _size;
	infoRecord() {
		strcpy(_ID, "");
		_lat = 0;
		_long = 0;
		_exist = 0;
		_size = 0;
	}
	infoRecord(const char *s) {
		strcpy(_ID, s);
		_lat = 0;
		_long = 0;
		_exist = 0;
		_size = 0;
	}
};
void isPass(VRecord &bus, void* yTree) {
	infoRecord* tempTree = (infoRecord*)yTree;
	if (!strcmp(bus.id, tempTree->_ID)) {
		tempTree->_exist = 1;
		tempTree->_size++;
	}
}
int Event2A(AVLTree<VRecord> *avlTree, char* id, double yLat, double dLat) {
	infoRecord *yLatTree = new infoRecord(id);
	VRecord a;
	a.latitude = yLat;
	avlTree->traverseNLRLat(a, dLat, &isPass, yLatTree);
	return yLatTree->_size;
}
int Event2B(AVLTree<VRecord> *avlTree, char* id, double yLong, double dLong) {
	infoRecord *yLongTree = new infoRecord(id);
	VRecord a;
	a.longitude = yLong;
	avlTree->traverseNLRLong(a, dLong, &isPass, yLongTree);
	return yLongTree->_size;
}
void Event3() {
	int a = 0;
	cout << a;
	return;
}
void travese4(AVLNode<VRecord> *root, double Y_lat, double Y_long, double Delta_lat, double Delta_long, int &param, AVLTree<VRecord> *idTree) {
	if (root) {
		if (ispass(root->_data.latitude, Y_lat, Delta_lat) == -1) {
			travese4(root->_pLeft, Y_lat, Y_long, Delta_lat, Delta_long, param, idTree);
		}
		else if (ispass(root->_data.latitude, Y_lat, Delta_lat) == 1) {
			travese4(root->_pRight, Y_lat, Y_long, Delta_lat, Delta_long, param, idTree);
		}
		else {
			if (!ispass(root->_data.longitude, Y_long, Delta_long)) {
				if (idTree->isEmpty() || !idTree->findid(root->_data)) {
					idTree->insertid(root->_data);
					param++;
				}
			}
			travese4(root->_pLeft, Y_lat, Y_long, Delta_lat, Delta_long, param, idTree);
			travese4(root->_pRight, Y_lat, Y_long, Delta_lat, Delta_long, param, idTree);
		}
	}
}
void Event4(AVLTree<VRecord> *latTree, double Y_lat, double Y_long, double Delta_lat, double Delta_long) {
	AVLNode<VRecord> *root = latTree->getRoot();
	AVLTree<VRecord> *idTree = new AVLTree<VRecord>();
	int size = 0;
	travese4(root, Y_lat, Y_long, Delta_lat, Delta_long, size, idTree);
	cout << size;
	return;
}
void travese5(AVLNode<VRecord> *root, double Y_lat, double Y_long,
	double Delta_lat, double Delta_long, int &param) {
	if (root) {
		if (ispass(root->_data.latitude, Y_lat, Delta_lat) == -1) {
			travese5(root->_pLeft, Y_lat, Y_long, Delta_lat, Delta_long, param);
		}
		else if (ispass(root->_data.latitude, Y_lat, Delta_lat) == 1) {
			travese5(root->_pRight, Y_lat, Y_long, Delta_lat, Delta_long, param);
		}
		else {
			if (!ispass(root->_data.longitude, Y_long, Delta_long)) {
				param++;
			};
			travese5(root->_pLeft, Y_lat, Y_long, Delta_lat, Delta_long, param);
			travese5(root->_pRight, Y_lat, Y_long, Delta_lat, Delta_long, param);
		}
	}
	return;
}
void Event5(AVLTree<VRecord> *latTree, double Y_lat, double Y_long, double Delta_lat, double Delta_long) {
	AVLNode<VRecord> *root = latTree->getRoot();
	int size = 0;
	travese5(root, Y_lat, Y_long, Delta_lat, Delta_long, size);
	cout << size;
	return;
};
void traverse6(AVLNode<VRecord> *root, char *id, double Y_lat, double Y_long,
	double Delta_lat, double Delta_long, int &param) {
	if (root) {
		if (ispass(root->_data.latitude, Y_lat, Delta_lat) == -1) {
			traverse6(root->_pLeft, id, Y_lat, Y_long, Delta_lat, Delta_long, param);
		}
		else if (ispass(root->_data.latitude, Y_lat, Delta_lat) == 1) {
			traverse6(root->_pRight, id, Y_lat, Y_long, Delta_lat, Delta_long, param);
		}
		else {
			if (!ispass(root->_data.longitude, Y_long, Delta_long) && !strcmp(id, root->_data.id)) {
				param++;
			};
			traverse6(root->_pLeft, id, Y_lat, Y_long, Delta_lat, Delta_long, param);
			traverse6(root->_pRight, id, Y_lat, Y_long, Delta_lat, Delta_long, param);
		}
	}
	return;
}
void Event6(AVLTree<VRecord> *latTree, char *id, double Y_lat, double Y_long, double Delta_lat, double Delta_long) {
	AVLNode<VRecord> *root = latTree->getRoot();
	int size = 0;
	traverse6(root, id, Y_lat, Y_long, Delta_lat, Delta_long, size);
	if (size == 0)
		cout << "No\n";
	else
		cout << "Yes\n";
	return;
}
void Event7(AVLTree<VRecord> *latTree, char *id, double Y_lat, double Y_long, double Delta_lat, double Delta_long) {
	AVLNode<VRecord> *root = latTree->getRoot();
	int size = 0;
	traverse6(root, id, Y_lat, Y_long, Delta_lat, Delta_long, size);
	cout << size;
	return;
}
char *getId(VRequest &event, int n) {
	char *res = (char *)event.code;
	res = res + n;
	return res;
};
bool a = 0;
bool initVGlobalData(void** pGData) {
	// TODO: allocate global data if you think it is necessary.
	/// pGData contains the address of a pointer. You should allocate data for the global data
	/// and then assign its address to *pGData
	return true;
}
void releaseVGlobalData(void* pGData) {
	// TODO: release the data if you finish using it
}
bool processRequest(VRequest& request, L1List<VRecord>& bList, void* pGData) {
	if (!a) {
		bList.traverse(&taocayAVL);
		a = 1;
	}

	if (request.code[0] == 'C' && request.code[1] == 'Y' && request.code[2] == 'R')
	{
		cout << request.code << ": ";
		int i = 3;
		int j = 3;
		int count = 0;
		double x;
		double Delta_x;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					x = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_x = atof(distance);
			}
			i++;
		}
		Event1A(latTree, id, x, Delta_x);
	}

	if (request.code[0] == 'C' && request.code[1] == 'X' && request.code[2] == 'R')
	{
		cout << request.code << ": ";
		int i = 3;
		int j = 3;
		int count = 0;
		double x;
		double Delta_x;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					x = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_x = atof(distance);
			}
			i++;
		}
		Event1B(longTree, id, x, Delta_x);
	}

	//if (request.code[0] == 'N' && request.code[1] == 'Y' && request.code[2] == 'R')
	//{
	//	cout << request.code << ": ";
	//	int i = 3;
	//	int j = 3;
	//	int count = 0;
	//	double y;
	//	double Delta_y;
	//	char *id;
	//	while (request.code[i] != '\0')
	//	{
	//		if (request.code[i] == '_') {
	//			switch (count) {
	//			case 0: {
	//				char*ID = new char[i - j + 1];
	//				memcpy(ID, request.code + j, i - j);
	//				ID[i - j] = '\0';
	//				id = ID;
	//				break;
	//			}
	//			case 1: {
	//				char*lat = new char[i - j + 1];
	//				memcpy(lat, request.code + j, i - j);
	//				lat[i - j] = '\0';
	//				y = atof(lat);
	//				break;
	//			}
	//			default: {
	//				break;
	//			}
	//			}
	//			j = i + 1;
	//			++count;
	//		}
	//		if (request.code[i + 1] == '\0') {
	//			char*distance = new char[i - j + 2];
	//			memcpy(distance, request.code + j, i - j + 1);
	//			distance[i - j + 1] = '\0';
	//			Delta_y = atof(distance);
	//		}
	//		i++;
	//	}
	//	Event2A(longTree, id, y, Delta_y);
	//	cout << endl;
	//}

	//if (request.code[0] == 'N' && request.code[1] == 'X' && request.code[2] == 'R')
	//{
	//	cout << request.code << ": ";
	//	int i = 3;
	//	int j = 3;
	//	int count = 0;
	//	double x;
	//	double Delta_x;
	//	char *id;
	//	while (request.code[i] != '\0')
	//	{
	//		if (request.code[i] == '_') {
	//			switch (count) {
	//			case 0: {
	//				char*ID = new char[i - j + 1];
	//				memcpy(ID, request.code + j, i - j);
	//				ID[i - j] = '\0';
	//				id = ID;
	//				break;
	//			}
	//			case 1: {
	//				char*lat = new char[i - j + 1];
	//				memcpy(lat, request.code + j, i - j);
	//				lat[i - j] = '\0';
	//				x = atof(lat);
	//				break;
	//			}
	//			default: {
	//				break;
	//			}
	//			}
	//			j = i + 1;
	//			++count;
	//		}
	//		if (request.code[i + 1] == '\0') {
	//			char*distance = new char[i - j + 2];
	//			memcpy(distance, request.code + j, i - j + 1);
	//			distance[i - j + 1] = '\0';
	//			Delta_x = atof(distance);
	//		}
	//		i++;
	//	}
	//	Event2B(latTree, id, x, Delta_x);
	//	cout << endl;
	//}

	if (request.code[0] == 'N' && request.code[1] == 'Y' && request.code[2] == 'R')
	{
		cout << request.code << ": ";
		int i = 3;
		int j = 3;
		int count = 0;
		double y;
		double Delta_y;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					y = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_y = atof(distance);
			}
			i++;
		}
		cout << Event2A(latTree, id, y, Delta_y) << endl;
	}

	if (request.code[0] == 'N' && request.code[1] == 'X' && request.code[2] == 'R')
	{
		cout << request.code << ": ";
		int i = 3;
		int j = 3;
		int count = 0;
		double x;
		double Delta_x;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					x = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_x = atof(distance);
			}
			i++;
		}
		cout << Event2B(latTree, id, x, Delta_x) << endl;
	}


	if (request.code[0] == 'N' && request.code[1] == 'P' && request.code[2] == 'R')
	{
		int i = 3;
		int j = 3;
		int count = 0;
		double x;
		double Delta_x;
		double y;
		double Delta_y;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					y = atof(lat);
					break;
				}
				case 2: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					x = atof(lat);
					break;
				}
				case 3: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					Delta_y = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_x = atof(distance);
			}
			i++;
		}
		cout << request.code << ": ";
		Event7(latTree, id, y, x, Delta_y, Delta_x);
		cout << endl;
	}

	if (request.code[0] == 'N' && request.code[1] == 'V' && request.code[2] == 'R')
	{
		int i = 3;
		int j = 3;
		int count = 0;
		double x;
		double Delta_x;
		double y;
		double Delta_y;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					y = atof(lat);
					break;
				}
				case 2: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					x = atof(lat);
					break;
				}
				case 3: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					Delta_y = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_x = atof(distance);
			}
			i++;
		}
		cout << request.code << ": ";
		Event4(latTree, y, x, Delta_y, Delta_x);
		cout << endl;
	}

	if (request.code[0] == 'N' && request.code[1] == 'R' && request.code[2] == 'R')
	{
		int i = 3;
		int j = 3;
		int count = 0;
		double x;
		double Delta_x;
		double y;
		double Delta_y;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					y = atof(lat);
					break;
				}
				case 2: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					x = atof(lat);
					break;
				}
				case 3: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					Delta_y = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_x = atof(distance);
			}
			i++;
		}
		cout << request.code << ": ";
		Event5(latTree, y, x, Delta_y, Delta_x);
		cout << endl;
	}

	if (request.code[0] == 'C' && request.code[1] == 'V' && request.code[2] == 'P')
	{
		int i = 3;
		int j = 3;
		int count = 0;
		double x;
		double Delta_x;
		double y;
		double Delta_y;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					y = atof(lat);
					break;
				}
				case 2: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					x = atof(lat);
					break;
				}
				case 3: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					Delta_y = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_x = atof(distance);
			}
			i++;
		}
		cout << request.code << ": ";
		Event6(latTree, id, y, x, Delta_y, Delta_x);

	}

	if (request.code[0] == 'N' && request.code[1] == 'R' && request.code[2] == 'P')
	{
		cout << request.code << ": ";
		int i = 3;
		int j = 3;
		int count = 0;
		double x;
		double Delta_x;
		double y;
		double Delta_y;
		char *id;
		while (request.code[i] != '\0')
		{
			if (request.code[i] == '_') {
				switch (count) {
				case 0: {
					char*ID = new char[i - j + 1];
					memcpy(ID, request.code + j, i - j);
					ID[i - j] = '\0';
					id = ID;
					break;
				}
				case 1: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					y = atof(lat);
					break;
				}
				case 2: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					x = atof(lat);
					break;
				}
				case 3: {
					char*lat = new char[i - j + 1];
					memcpy(lat, request.code + j, i - j);
					lat[i - j] = '\0';
					Delta_y = atof(lat);
					break;
				}
				default: {
					break;
				}
				}
				j = i + 1;
				++count;
			}
			if (request.code[i + 1] == '\0') {
				char*distance = new char[i - j + 2];
				memcpy(distance, request.code + j, i - j + 1);
				distance[i - j + 1] = '\0';
				Delta_x = atof(distance);
			}
			i++;
		}
		Event7(latTree, id, y, x, Delta_y, Delta_x);
			cout << endl;
	}
	return true;
}


