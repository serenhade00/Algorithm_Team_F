#ifndef HUFFMAN             // 헤더파일 중복 포함 방지
#define HUFFMAN             // 헤더파일 중복 포함 방지
#include <bits/stdc++.h>    // 프로그램에 쓰일 기능 포함 종합 헤더

using namespace std;       

class Node {                // 이진트리 생성을 위한 노드 구조 정하기
public:
	Node* left;             // 왼쪽 자식 노드 포인터
	Node* right;            // 오른쪽 자식 노드 포인터
	int cnt;                // 문자 빈도수 저장
	char ch;                // 문자 저장
	
	bool operator()(const Node* l_c, const Node* r_c);           // 우선순위 큐 값 저장시 정렬 함수, 빈도수가 많을수록 트리에 top에 형성
	Node() : left(nullptr), right(nullptr), cnt(0), ch(0) {}     // 노드끼리 연결 x, 노드에 값 저장 x 한 기본 노드 형태
	Node(char ch, int cnt) : left(nullptr), right(nullptr), cnt(cnt), ch(ch) {} // 노드끼리 연결 x, 노드에 값 저장 o
	Node(Node* left, Node* right) : left(left), right(right), cnt(left->cnt + right->cnt), ch(0) {} // 노드 연결 o, 값 저장 o
};

class Huffman {
private:
	Node* huffTree;                                              // 허프만 트리를 저장
	string s;                                                    // 허프만 압축을 통한 허프만 코드
	void to_huff(const string& input);                           // 생성된 허프만 트리를 통해 원본을 허프만 코드로 변경
public:
	void encoding(const std::string& input);                     // 허프만 트리를 생성. 문자 빈도수를 계산 후 그에 따른 허프만 트리를 만듬
	string get_huff();                                           // 허프만 코드 리턴
};
#endif                                                           // 헤더파일 끝