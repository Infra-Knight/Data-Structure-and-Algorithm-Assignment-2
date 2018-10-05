/*
* =========================================================================================
* Name        : dsaLib.h
* Author      : Duc Dung Nguyen
* Email       : nddung@hcmut.edu.vn
* Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
* Description : library for Assignment 2 - Data structures and Algorithms - Spring 2017
* =========================================================================================
*/

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
using namespace std;

class DSAException {
	int     _error;
	string  _text;
public:

	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
	T data;
	L1Item<T> *pNext;
	L1Item() : pNext(NULL) {};
	L1Item(T &a) : data(a), pNext(NULL) {};
};

template <class T>
class L1List {
	L1Item<T>   *_pHead;// The head pointer of linked list
	size_t      _size;// number of elements in this list
public:
	L1List() : _pHead(NULL), _size(0) {}
	~L1List() {};
	int removeHead();
	void    clean() {};
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	T&  at(int i) {
		L1Item<T>   *p = _pHead;
		for (int j = 0; j < i; j++) {
			p = p->pNext;
		}
		return p->data;
	};
	T&      operator[](int i) {
		return at(i);
	}
	bool    find(T& a, int& idx) {
		L1Item<T>   *p = _pHead;
		if (_pHead == NULL) {
			idx = -1;
			return false;
		}
		idx = 0;
		while (p->pNext != NULL && p->data != a) {
			p = p->pNext;
			idx++;
		}

		if (p->data == a) {
			return true;
		}
		idx = -1;
		return false;
	};
	int     insert(int i, T& a) {
		if (i == 0) {
			return insertHead(a);
		}
		else {
			L1Item<T>   *p = _pHead;
			for (int j = 1; j < i; j++) {
				p = p->pNext;
			}
			if (p->pNext == NULL) return push_back(a);

			L1Item<T> *temp = new L1Item<T>(a);
			temp->pNext = p->pNext;
			p->pNext = temp;
		}
		_size++;
		return 0;
	};
	int     remove(int i) {
		if (i == 0) return removeHead();
		if (i >= _size - 1) return removeLast();
		L1Item<T>   *p = _pHead;
		for (int j = 1; j < i; j++) {
			p = p->pNext;
		}
		L1Item<T> *temp = p->pNext;
		p->pNext = temp->pNext;
		delete temp;
		_size--;
		return 0;

	};

	int     push_back(T& a);
	int     insertHead(T& a);
	int     removeLast();

	void reverse() {

		L1Item<T> *p = this->_pHead;
		if (p == NULL) return;
		L1Item<T> *pTemp = NULL;
		while (p != NULL) {
			L1Item<T> *pNew = new L1Item<T>(p->data);
			if (pTemp == NULL) pTemp = pNew;
			else {
				pNew->pNext = pTemp;
				pTemp = pNew;
			}
			p = p->pNext;
		}
		this->_pHead = pTemp;
	};
	void    traverse(void(*op)(T&)) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, void*), void* pParam) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data, pParam);
			p = p->pNext;
		}
	}
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
	if (_pHead == NULL) {
		_pHead = new L1Item<T>(a);
	}
	else {
		L1Item<T>   *p = _pHead;
		while (p->pNext) p = p->pNext;
		p->pNext = new L1Item<T>(a);
	}

	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
	L1Item<T>   *p = new L1Item<T>(a);
	p->pNext = _pHead;
	_pHead = p;
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p = _pHead;
		_pHead = p->pNext;
		delete p;
		_size--;
		return 0;
	}
	return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		if (_pHead->pNext) {
			L1Item<T>* prev = _pHead;
			L1Item<T>* pcur = prev->pNext;
			while (pcur->pNext) {
				prev = pcur;
				pcur = pcur->pNext;
			}
			delete pcur;
			prev->pNext = NULL;
		}
		else {
			delete _pHead;
			_pHead = NULL;
		}
		_size--;
		return 0;
	}
	return -1;
}

/************************************************************************
* This section is for AVL tree
************************************************************************/
enum Balance { LEFT, EQUAL, RIGHT };
template <class T>
struct AVLNode {
	T           _data;
	AVLNode<T>   *_pLeft, *_pRight;
	int         _bFactor;
	AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(EQUAL) {}
};

template <class T>
class AVLTree {
	AVLNode<T> *_pRoot;
public:
	AVLTree() : _pRoot(NULL) {}
	~AVLTree() { destroy(_pRoot); }

	bool findid(T& key) { return findid(_pRoot, key); }
	bool insertlat(T& key) { return insertlat(_pRoot, key); }
	bool insertlong(T& key) { return insertlong(_pRoot, key); }
	bool insertid(T& key) { return insertid(_pRoot, key); }
	bool remove(T& key) { return remove(_pRoot, key); }
	void traverseNLR(void(*op)(T&)) { traverseNLR(_pRoot, op); }
	void traverseLNR(void(*op)(T&)) { traverseLNR(_pRoot, op); }
	void traverseLRN(void(*op)(T&)) { traverseLRN(_pRoot, op); }
	void traverseNLRLat(T key, double delta, void(*op)(T&, void*), void *param) {
		traverseNLRLat(_pRoot, key, delta, op, param);
	}
	void traverseNLRLong(T key, double delta, void(*op)(T&, void*), void *param) {
		traverseNLRLong(_pRoot, key, delta, op, param);
	}
	AVLNode<T> *getRoot() {
		return _pRoot;
	}
	bool isEmpty() {
		return _pRoot == NULL;
	}
protected:
	void destroy(AVLNode<T>* &pR) {};
	bool findid(AVLNode<T> *pR, T& key) {
		if (!pR) {
			return 0;
		}
		else if (!ssid(pR->_data, key))
			return 1;
		else if (ssid(key, pR->_data) == -1)
			return findid(pR->_pLeft, key);
		else return findid(pR->_pRight, key);
	};
	bool insertlong(AVLNode<T>* &pR, AVLNode<T>* newNode, bool &taller);
	bool insertlong(AVLNode<T>* &pR, T& a) {
		bool taller;
		AVLNode<T> *newNode = new AVLNode<T>(a);
		return insertlong(pR, newNode, taller);
	};
	bool insertid(AVLNode<T>* &pR, AVLNode<T>* newNode, bool &taller);
	bool insertid(AVLNode<T>* &pR, T& a) {
		bool taller;
		AVLNode<T> *newNode = new AVLNode<T>(a);
		return insertid(pR, newNode, taller);
	};
	bool insertlat(AVLNode<T>* &pR, AVLNode<T>* newNode, bool &taller);
	bool insertlat(AVLNode<T>* &pR, T& a) {
		bool taller;
		AVLNode<T> *newNode = new AVLNode<T>(a);
		return insertlat(pR, newNode, taller);
	};
	bool remove(AVLNode<T>* &pR, T& a) {};
	void traverseNLR(AVLNode<T> *pR, void(*op)(T&)) {};
	void traverseLNR(AVLNode<T> *pR, void(*op)(T&)) {};
	void traverseLRN(AVLNode<T> *pR, void(*op)(T&)) {};

	void RotateLeft(AVLNode<T>* &pR);
	void RotateRight(AVLNode<T>* &pR);
	void rotLR(AVLNode<T>* &pR) {};
	void rotRL(AVLNode<T>* &pR) {};
	void LeftBalance(AVLNode<T>* &pR, bool &taller);
	bool balanceLeft(AVLNode<T>* &pR) {
		bool taller;
		LeftBalance(pR, taller);
		return 1;
	};
	void RightBalance(AVLNode<T>* &pR, bool &taller);
	bool balanceRight(AVLNode<T>* &pR) {
		bool taller;
		RightBalance(pR, taller);
		return 1;
	};
	void traverseNLRLat(AVLNode<T> *pR, T key, double delta, void(*op)(T&, void*), void *param);
	void traverseNLRLong(AVLNode<T> *pR, T key, double delta, void(*op)(T&, void*), void *param);
};

template <class T>
void AVLTree<T>::RotateRight(AVLNode<T>* &pR) {
	AVLNode<T> *tmpPtr = pR->_pLeft;
	pR->_pLeft = tmpPtr->_pRight;
	tmpPtr->_pRight = pR;
	pR = tmpPtr;
	return;
};

template <class T>
void AVLTree<T>::RotateLeft(AVLNode<T>* &pR) {
	AVLNode<T> *tmpPtr = pR->_pRight;
	pR->_pRight = tmpPtr->_pLeft;
	tmpPtr->_pLeft = pR;
	pR = tmpPtr;
	return;
};

template <class T>
void AVLTree<T>::LeftBalance(AVLNode<T>* &pR, bool &taller) {
	AVLNode<T> *leftTree = pR->_pLeft;
	if (leftTree->_bFactor == LEFT) {
		pR->_bFactor = EQUAL;
		leftTree->_bFactor = EQUAL;
		RotateRight(pR);
		taller = false;
	}
	else {
		AVLNode<T> *rightTree = leftTree->_pRight;
		if (rightTree->_bFactor == LEFT) {
			pR->_bFactor = RIGHT;
			leftTree->_bFactor = EQUAL;
		}
		else if (rightTree->_bFactor == EQUAL) {
			pR->_bFactor = EQUAL;
			leftTree->_bFactor = EQUAL;
		}
		else {
			pR->_bFactor = EQUAL;
			leftTree->_bFactor = LEFT;
		}
		rightTree->_bFactor = EQUAL;
		RotateLeft(pR->_pLeft);
		RotateRight(pR);
		taller = false;
	}
};

template <class T>
void AVLTree<T>::RightBalance(AVLNode<T>* &pR, bool &taller) {
	AVLNode<T> *rightTree = pR->_pRight;
	if (rightTree->_bFactor == RIGHT) {
		pR->_bFactor = EQUAL;
		rightTree->_bFactor = EQUAL;
		RotateLeft(pR);
		taller = false;
	}
	else {
		AVLNode<T> *leftTree = rightTree->_pLeft;
		if (leftTree->_bFactor == RIGHT) {
			pR->_bFactor = LEFT;
			rightTree->_bFactor = EQUAL;
		}
		else if (leftTree->_bFactor == EQUAL) {
			pR->_bFactor = EQUAL;
			rightTree->_bFactor = EQUAL;
		}
		else {
			pR->_bFactor = EQUAL;
			rightTree->_bFactor = RIGHT;
		}
		leftTree->_bFactor = EQUAL;
		RotateRight(pR->_pRight);
		RotateLeft(pR);
		taller = false;
	}
};
template <class T>
void AVLTree<T>::traverseNLRLat(AVLNode<T> *pR, T key, double delta, void(*op)(T&, void*), void* param) {
	if (pR) {
		if (cmpDeltaLat(key, pR->_data, delta) == 0) {
			op(pR->_data, param);
			traverseNLRLat(pR->_pLeft, key, delta, op, param);
			traverseNLRLat(pR->_pRight, key, delta, op, param);
		}
		else if (cmpDeltaLat(key, pR->_data, delta) == -1) {
			traverseNLRLat(pR->_pLeft, key, delta, op, param);
		}
		else if (cmpDeltaLat(key, pR->_data, delta) == 1) {
			traverseNLRLat(pR->_pRight, key, delta, op, param);
		}
	}
}
template <class T>
void AVLTree<T>::traverseNLRLong(AVLNode<T> *pR, T key, double delta, void(*op)(T&, void*), void* param) {
	if (pR) {
		if (!cmpDeltaLong(key, pR->_data, delta)) {
			op(pR->_data, param);
			traverseNLRLong(pR->_pLeft, key, delta, op, param);
			traverseNLRLong(pR->_pRight, key, delta, op, param);
		}
		else if (cmpDeltaLong(key, pR->_data, delta) == -1) {
			traverseNLRLong(pR->_pLeft, key, delta, op, param);
		}
		else if (cmpDeltaLong(key, pR->_data, delta) == 1) {
			traverseNLRLong(pR->_pRight, key, delta, op, param);
		}
	}
};
template <class T>
bool AVLTree<T>::insertlong(AVLNode<T>* &pR, AVLNode<T>* newNode, bool &taller) {
	if (pR == NULL) {
		pR = newNode;
		taller = true;
	}
	else if (sslong(newNode->_data, pR->_data)) {
		insertlong(pR->_pLeft, newNode, taller);
		if (taller) {
			if (pR->_bFactor == LEFT) {
				LeftBalance(pR, taller);
			}
			else if (pR->_bFactor == EQUAL) {
				pR->_bFactor = LEFT;
			}
			else {
				pR->_bFactor = EQUAL;
				taller = false;
			}
		}
	}
	else {
		insertlong(pR->_pRight, newNode, taller);
		if (taller) {
			if (pR->_bFactor == LEFT) {
				pR->_bFactor = EQUAL;
				taller = false;
			}
			else if (pR->_bFactor == EQUAL) {
				pR->_bFactor = RIGHT;
			}
			else {
				RightBalance(pR, taller);
			}
		}
	}
	return 1;
};
template <class T>
bool AVLTree<T>::insertlat(AVLNode<T>* &pR, AVLNode<T>* newNode, bool &taller) {
	if (pR == NULL) {
		pR = newNode;
		taller = true;
	}
	else if (sslat(newNode->_data, pR->_data)) {

		insertlat(pR->_pLeft, newNode, taller);
		if (taller) {
			if (pR->_bFactor == LEFT) {
				LeftBalance(pR, taller);
			}
			else if (pR->_bFactor == EQUAL) {
				pR->_bFactor = LEFT;
			}
			else {
				pR->_bFactor = EQUAL;
				taller = false;
			}
		}
	}
	else {
		insertlat(pR->_pRight, newNode, taller);
		if (taller) {
			if (pR->_bFactor == LEFT) {
				pR->_bFactor = EQUAL;
				taller = false;
			}
			else if (pR->_bFactor == EQUAL) {
				pR->_bFactor = RIGHT;
			}
			else {
				RightBalance(pR, taller);
			}
		}
	}
	return 1;
};
template <class T>
bool AVLTree<T>::insertid(AVLNode<T>* &pR, AVLNode<T>* newNode, bool &taller) {
	if (pR == NULL) {
		pR = newNode;
		taller = true;
	}
	else if (ssid(newNode->_data, pR->_data) == -1) {
		insertid(pR->_pLeft, newNode, taller);
		if (taller) {
			if (pR->_bFactor == LEFT) {
				LeftBalance(pR, taller);
			}
			else if (pR->_bFactor == EQUAL) {
				pR->_bFactor = LEFT;
			}
			else {
				pR->_bFactor = EQUAL;
				taller = false;
			}
		}
	}
	else {
		insertid(pR->_pRight, newNode, taller);
		if (taller) {
			if (pR->_bFactor == LEFT) {
				pR->_bFactor = EQUAL;
				taller = false;
			}
			else if (pR->_bFactor == EQUAL) {
				pR->_bFactor = RIGHT;
			}
			else {
				RightBalance(pR, taller);
			}
		}
	}
	return 1;
};

#endif //A01_LISTLIB_H
