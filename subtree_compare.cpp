#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

using namespace std;

// basic node struct used in tree
struct node {
	node * left;
	node * right;

	int value;

	node( int val ) : value(val), left(NULL), right(NULL) {}
	node( int val, node * l, node * r ) : value(val), left(l), right(r) {}
};

// basic struct for holding tree
struct Tree {
	
	node * root;
	
	Tree() : root(NULL) {}
	void populate( int * num_arr, int n);
};

// recursively compares tree sub branches
bool compare( node * t, node * s ) {
	if ( t == NULL && s == NULL ) 
		return true;
	if( (t == NULL && s != NULL) || (t != NULL && s == NULL) )
		return false;
	
	if ( t->value == s->value )
		return compare( t->left, s->left ) && compare( t->right, s->right );
	else 
		return false;
}

// build binary tree from list of numbers
void Tree::populate( int * num_arr, int n ) {
	
	node * old_p = NULL;
	node * p = root;
	bool went_left = false;

	for (int i = 0; i < n; i++ ) {
		
		old_p = NULL;
		p = root;
		went_left = false;

		if ( p == NULL ) {
			root = new node( num_arr[i] );
			continue;
		}
		
		while( p != NULL ) {
			
			old_p = p;
			if ( num_arr[i] < p->value ) {
				went_left = true;
				p = p->left;
			}	
			else {
				went_left = false;
				p = p->right;
			}
		}
		
		if ( went_left ) {
			old_p->left = new node( num_arr[i] );
		}
		else  {
			old_p->right = new node( num_arr[i] );
		}
	}
	
	 
}

// prints out tree in-order
void print_tree( node * n, int depth ) {
	
	if ( n != NULL ) {
		
		print_tree( n->left, depth+1 );
		
		for (int i = 0; i < depth; i++ ) { cout << "    "; }
		cout << n->value << endl;

		print_tree( n->right, depth+1 );
		
	}
}

TEST_CASE( "null inputs" ) {
	Tree t;
	Tree s;
	
	REQUIRE( compare( t.root, s.root ) == true );
	REQUIRE( compare( s.root, t.root ) == true );
}

TEST_CASE( "partial null inputs" ) {

	int nums[] = { 1, 2, 3};
	
	Tree t;
	Tree s;
	Tree not_empty;

	not_empty.populate( nums, 3 );
	
	REQUIRE( compare( t.root, not_empty.root ) == false );
	REQUIRE( compare( s.root, not_empty.root ) == false );
}

TEST_CASE( "sub-trees NOT equal" ) {

	int a1[] = { 1, 2, 3 };
	int a2[] = { 4, 5, 6 };
	int a3[] = { 30, 15, 10, 13, 11, 40, 55, 31, 33, 59, 58, 60 };

	Tree t1; t1.populate( a1, 3 );
	Tree t2; t2.populate( a2, 3 );
	Tree t3; t3.populate( a3, 12 );

	REQUIRE( compare( t1.root, t2.root ) == false );
	REQUIRE( compare( t1.root, t3.root->left->right ) == false );
	REQUIRE( compare( t2.root, t3.root ) == false );
}

TEST_CASE( "sub-trees are equal" ) {
	int a1[] = { 2, 1, 3 };
	int a2[] = { 5, 2, 1, 3, 8, 6, 10};
	int a3[] = { 8, 6, 10 };
	int a4[] = { 6 };

	Tree t1; t1.populate( a1, 3 );
	Tree t2; t2.populate( a2, 7 );
	Tree t3; t3.populate( a3, 3 );
	Tree t4; t4.populate( a4, 1 );

	REQUIRE( compare( t1.root, t2.root->left ) == true );
	REQUIRE( compare( t3.root, t2.root->right ) == true );
	REQUIRE( compare( t4.root, t2.root->right->left ) == true );
	
}

