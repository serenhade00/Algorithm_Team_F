#include "Huff.h"                                               // 허프만 헤더 포함

using namespace std;

char text[200000000];                                           // 원본 파일 저장할 문자형 배열

bool Node::operator()(const Node* l_c, const Node* r_c){        // 우선순위 큐 정렬, 빈도수가 적을수록 우선순위(위쪽)가 높음
	return l_c->cnt > r_c->cnt;
}

int size(const string& input)                                   // 원본 파일 크기 반환(문자 하나에 1바이트)
{
	return input.size();
}
string Huffman::get_huff(){                                     // Huffman 클래스에 있는 허프만 코드를 저장할 최종 변수 s를 리턴
	return s;
}

void Huffman::encoding(const string& input) {                   // 원본 파일 기반으로 우선순위 큐 및 허프만 트리 생성
	
	map<char, int> m;                                           // 문자별 빈도수 저장 위한 map
	for (auto& c : input) {
		m[c]++;                                                 // 문자별 빈도수 갱신
	}
	
	priority_queue<Node*, vector<Node*>, Node> pq;              // 우선 순위 큐, 기존 정의한 정렬 함수에 의해 빈도수가 적을수록 top에 배치된다.
	for (auto& e : m) {
		pq.push(new Node(e.first, e.second));                   // 문자별로 문자와 빈도수를 저장한 노드를 생성하여 우선순위큐에 넣음
	}
	while (pq.size() > 1) {                                     // 우선순위큐의 크기가 1개보다 클 동안(두개 이상의 노드가 있을때)
		Node* left = pq.top();                                  // top에 있는 노드(최소 빈도 노드)를 받음 -> left
		pq.pop();                                               // 노드를 가져왔으므로 우선순위큐에서는 제거
		Node* right = pq.top();                                 // 그 다음 top에 있는 (최소 빈도 노드)를 받음 -> right
		pq.pop();                                               // 노드를 가져왔으므로 우선순위큐에서는 제거
		Node* newNode = new Node(left, right);                  // newNode 생성후 왼쪽, 오른쪽 자식노드를 left노드, right노드에 연결, 빈도수는 합친 값
		pq.push(newNode);                                       // 그 newNode 역시 우선순위큐에 push
	}
	huffTree = pq.top();                                        // huffTree 노드에 우선순위큐 헤드 노드를 할당
	pq.pop();                                                   // 우선순위큐 모두 pop 완료
	to_huff(input);                                             // 만든 허프만 트리를 이용한 허프만 코드 생성을 위해 to_huff 함수 실행
	return;                                                     // 함수 종료
}

void Huffman::to_huff(const string& input) {                    // 인코딩 후 생성된 허프만 트리에 코드 부여 후 최종 허프만 코드 리턴
	string s = "";                                              // 허프만 코드 저장할 string
	stack<pair<Node*, string>> st;                              // 허프만 트리를 모두 탐색하기 위해 stack에 넣고 노드를 하나씩 빼냄
	map<char, string> a;                                        // 문자별로 허프만 코드를 저장하기 위한 map
	
	st.push({huffTree, ""});                                    // 허프만 트리의 헤드 노드를 스택에 push한다. 탐색 시작전이므로 허프만 코드는 공백
	while (!st.empty()) {                                       // 스택이 비어있지 않는 동안(노드가 존재하는 동안)
		Node* cur = st.top().first;                             // 스택 top의 노드를 가져옴
		string tmp = st.top().second;                           // 스택 top의 노드의 허프만 코드를 가져옴
		st.pop();        
		                                                        // 노드를 탐색하고 제거할것이므로 pop
		if (cur->right != nullptr) {                            // 만약 cur 노드의 오른쪽 자식 노드가 존재하면
			st.push({ cur->right, tmp + "1" });                 // 그 자식 노드 역시 stack(탐색 대상)에 push, 허프만 코드는 "부모노드의 코드+1" 
		}
		if (cur->left != nullptr) {                             // 만약 cur 노드의 왼쪽 자식 노드가 존재하면
			st.push({ cur->left, tmp + "0" });                  // 그 자식 노드 역시 stack(탐색 대상)에 push, 허프만 코드는 "부모노드의 코드+0"
		}
		if (cur->left == nullptr && cur->right == nullptr) {    // 만약 cur 노드가 리프 노드라면(자식 노드 x)
			a[cur->ch] = tmp;                                   // cur 노드의 문자와 생성한 허프만 코드를 mapping 시킴
		}
	}
	for (const char& c : input)                                 // 원본 파일에 존재하는 문자들에 대해 허프만 코드를 각각 mapping 시켜 하나의 코드로 연결
		s += a[c];

	this->s = s;                                                // Huffman 클래스에 있던 's'에 68번째 줄에서 만든 허프만 코드를 넣음
	return;                                                     // 함수 종료
}

int main(void) {
	Huffman h;                                                  // Huffman 클래스 객체 생성
	FILE* f = 0;                                                // 원본 파일 입력을 받기 위한 파일 포인터
	f = fopen("test.txt", "r");                                 // "test.txt"라는 텍스트 파일을 입력받기 위해 접근
	int tmp_size;                                               // 원본 파일 크기 저장 변수
	
	fgets(text, 199999999, f);                                  // f 파일 포인터를 통해 문자열을 읽어와 전역 배열 text에 저장
	tmp_size = size(text);                                      // 원본 파일 크기 리턴
	h.encoding(text);                                           // 원본 파일을 인코딩 함수로 넘겨줌
	
	double original = (double)tmp_size;                                           // 원본 크기
	double compress = (double)(h.get_huff().size()/8);                            // 압축된 허프만 코드의 크기(bits)/8 -> 압축된 크기(바이트) 
	cout << "Original File size: " << original/1000 << "KBs\n";                   // 원본 크기를 KB단위로 표현
	cout << "Compress File size: " << compress/1000 << "KBs\n";                   // 압축 크기를 KB단위로 표현
	
	cout << "Encoding Result : " << compress / original * 100 << '%' << '\n';;    // 압축/원본*100 -> 압축률(백분율)
	return 0;                                                                     // 함수 종료
}

