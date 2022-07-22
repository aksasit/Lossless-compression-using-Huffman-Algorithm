// C++ program to encode and decode a string using Huffman Coding

#include <bits/stdc++.h>
using namespace std;
#define MAX_TREE_HT 256

// to map each character its huffman value
map<char, string> codes;

// to store the frequency of character of the input data
map<char, int> freq;

// A Huffman tree node
struct MinHeapNode
{
	char data;								 // One of the input characters
	int freq;									 // Frequency of the character
	MinHeapNode *left, *right; // Left and right child

	MinHeapNode(char data, int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// utility function for the priority queue
struct compare
{
	bool operator()(MinHeapNode *l, MinHeapNode *r)
	{
		return (l->freq > r->freq);
	}
};

// utility function to print characters along with
// there huffman value
void print_codes(struct MinHeapNode *root, string str)
{
	if (!root)
		return;
	if (root->data != '$')
		cout << root->data << ": " << str << "\n";
	print_codes(root->left, str + "0");
	print_codes(root->right, str + "1");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void store_codes(struct MinHeapNode *root, string str)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	store_codes(root->left, str + "0");
	store_codes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

// function to build the Huffman tree and store it
// in minHeap
void huffman_codes(int size)
{
	struct MinHeapNode *left, *right, *top;
	for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
		minHeap.push(new MinHeapNode(v->first, v->second));
	while (minHeap.size() != 1)
	{
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	store_codes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calc_freq(string str, int n)
{
	for (int i = 0; i < str.size(); i++)
		freq[str[i]]++;
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode *root, string s)
{
	string ans = "";
	struct MinHeapNode *curr = root;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node
		if (curr->left == NULL and curr->right == NULL)
		{
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl;
	return ans + '\0';
}

// Driver program to test above functions
int main()
{
	string str = "asit_huffman_code";
	string encoded_string, decoded_string;
	calc_freq(str, str.length());
	huffman_codes(str.length());
	cout << "Character With there Frequencies:\n";
	for (auto v = codes.begin(); v != codes.end(); v++)
		cout << v->first << ' ' << v->second << endl;

	for (auto i : str)
		encoded_string += codes[i];

	cout << "\nEncoded Huffman Data:\n"
			 << encoded_string << endl;

	decoded_string = decode_file(minHeap.top(), encoded_string);
	cout << "\nDecoded Huffman Data:\n"
			 << decoded_string << endl;
	return 0;
}
