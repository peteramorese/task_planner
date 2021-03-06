#include<string>
#include<vector>
#include<iostream>
#include "edge.h"
#include<map>


Edge::Edge(bool ordered_) : ordered(ordered_) {
	ind = 0;
	ind_checkout = 0;
	head = nullptr;
	prev = nullptr;
	heads.clear();
	prevs.clear();
	checking = false;

}

bool Edge::isOrdered() const {
	return ordered;
}

bool Edge::isEmpty() {
	if (head==nullptr) {
		return true;
	} else {
		return false;
	}
}

bool Edge::isListEmpty(Edge::node* head_) const {
	if (head_==nullptr) {
		return true;
	} else {
		return false;
	}
}

void Edge::append(unsigned int nodeind_, float weight_, std::string label_) {
	if (isEmpty()) {
		Edge::node* newNode = new Edge::node;
		//std::cout<<"PTR ADDED: "<<newNode<<std::endl;
		newNode->nodeind = nodeind_;
		newNode->weight = 0; 
		newNode->label = "none"; 
		head = newNode;
		//std::cout<<" IND CHECKOUT: "<<ind_checkout<<" IND: "<<ind<<std::endl;
		heads[ind_checkout] = head;
		prev = newNode;
		prevs[ind_checkout] = prev;
		newNode->adjptr = nullptr;
	} else {
		Edge::node* newNode = new Edge::node;
		//std::cout<<"PTR ADDED: "<<newNode<<std::endl;
		newNode->nodeind = nodeind_;
		newNode->weight = weight_;
		newNode->label = label_;

		prev->adjptr = newNode;
		prev = newNode;
		prevs[ind_checkout] = prev;
		newNode->adjptr = nullptr;	
	}
}

void Edge::checkout(int ind_checkout_) {
	if (ind_checkout_<=heads.size()){
		if (heads[ind_checkout] == head) {
			// reset the pointer keeping track of last node in list using the current checkout
			ind_checkout = ind_checkout_;
			head = heads[ind_checkout];
			prev = prevs[ind_checkout];	
			checking = true;
		} else {
			std::cout<<"Error: Heads are mismatched"<<std::endl;
		}

		//}
	} else {
		std::cout << "Index out of bounds for number of lists\n";
	}

}

void Edge::newlist(){
	if (checking) {
		//std::cout<< "checking head:"<<heads[ind_checkout]<< ", reset head:"<<head<<std::endl;
		if (heads[ind_checkout] == head) {
			// reset the pointer keeping track of last node in list
			ind_checkout = ind;
			checking = false;
		} else {
			std::cout<<"Error: Heads are mismatched"<<std::endl;
		}
	} else {
		heads.push_back(head);
		prevs.push_back(prev);
		ind = heads.size()-1;
		ind_checkout = ind;
		head = nullptr;
		prev = nullptr;
		append(ind, 0, "none");
	}
} 


int Edge::size() const {
	if (ind+1 == heads.size()){
		return ind+1;
	} else if (heads.size() == 0) {
		return 0;	
	} else {
		std::cout<<"Error: Number of heads does not match number of lists\n";
		return 0;
	}
}

const std::vector<Edge::node*> Edge::getHeads() const {
	const std::vector<Edge::node*> heads_out = heads;
	return heads_out;

}

bool Edge::connect(unsigned int ind_from, unsigned int ind_to, float weight_, std::string label_){
	// Add lists until ind_from and ind_to are included in the graph
	while (ind_from > ind){
		newlist();	
	}
	while (ind_to > ind){
		newlist();
	}
	if (heads.size() == 0) {
		newlist();
	}

	checkout(ind_from);
	append(ind_to, weight_, label_);
	if (!ordered){
		checkout(ind_to);
		append(ind_from, weight_, label_);
	}
	return true;
}

bool Edge::remove(unsigned int ind_) {
	for (int i=0; i<heads.size(); i++) {
		std::cout<<"i: "<<i<<std::endl;
		if (i == ind_) {
			std::cout<<"Deleting list: "<<ind_<<std::endl;
			deleteList(heads[ind_]);
			std::cout<<"done deleting list... "<<std::endl;
			//remove element from vector
		} else {
			auto prevptr = heads[i];
			auto currptr = heads[i]->adjptr;
			currptr = currptr->adjptr;
			std::cout<<"currptr: "<<currptr<<std::endl;
			while (currptr!=nullptr) {
				auto nextptr = currptr->adjptr;
				std::cout<<"Curr node: "<<currptr->nodeind<<std::endl;
				if (currptr->nodeind == ind_) {
					std::cout<<"Found node to delete: "<<currptr->nodeind<<std::endl;
					prevptr->adjptr = currptr->adjptr;
					std::cout<<"Deleted: "<<currptr<<std::endl;
					delete currptr;

				}
				prevptr = currptr;
				currptr = nextptr;
			}
		}
	}

}

void Edge::returnListNodes(unsigned int ind_, std::vector<int>& node_list) const {
	auto currptr = heads[ind_];
	node_list.clear();
	node_list.resize(0);
	if (!isListEmpty(currptr)) {
		currptr = currptr->adjptr;
		while (currptr!=nullptr) {
			auto nextptr = currptr->adjptr;
			node_list.push_back(currptr->nodeind);
			currptr = nextptr;
		}
	}
}

void Edge::returnListLabels(unsigned int ind_, std::vector<std::string>& label_list) const {
	auto currptr = heads[ind_];
	label_list.clear();
	label_list.resize(0);
	if (!isListEmpty(currptr)) {
		currptr = currptr->adjptr;
		while (currptr!=nullptr) {
			auto nextptr = currptr->adjptr;
			label_list.push_back(currptr->label);
			currptr = nextptr;
		}
	}
}

void Edge::returnListWeights(unsigned int ind_, std::vector<float>& weights_list) const {
	auto currptr = heads[ind_];
	weights_list.clear();
	if (!isListEmpty(currptr)) {
		currptr = currptr->adjptr;
		while (currptr!=nullptr) {
			auto nextptr = currptr->adjptr;
			weights_list.push_back(currptr->weight);
			currptr = nextptr;
		}
	}
}

void Edge::print() const {
	for (int i=0; i<heads.size(); i++) {
		auto currptr = heads[i];
		std::cout<<"Node: "<<currptr->nodeind<<" "<<currptr<<" connects to:\n";
		currptr = currptr->adjptr;
		while (currptr!=nullptr) {
			auto nextptr = currptr->adjptr;
			std::cout<<"  ~> "<<currptr->nodeind<<"     with label: "<<currptr->label<<"     and weight: "<<currptr->weight<<"\n";

			currptr = nextptr;
		}
	}

}

float Edge::getWeight(unsigned int ind_from, unsigned int ind_to) const {
	if (ind_from < heads.size()) {
		auto currptr = heads[ind_from]->adjptr;
		//std::cout<<"Node: "<<currptr->nodeind<<" "<<currptr<<" connects to:\n";
		bool found = false;
		float ret_weight;
		while (currptr!=nullptr) {
			if (currptr->nodeind == ind_to) {
				found = true;
				ret_weight = currptr->weight;
				break; 
				// REMOVE THIS BREAK STATEMENT TO UPDATE ALL
				// EDGES THAT CONNECT TWO STATES. THIS WILL 
				// DECREASE THE EFFICIENCY
			}
			currptr = currptr->adjptr;
		}
		if (!found) {
			std::cout<<"Error: Update ind_to not found within list\n";
			return 0;
		} else {
			return ret_weight;
		}
	} else {
		std::cout<<"Error: Update ind_from out of bounds\n";
		return 0;
	}
}

void Edge::updateWeight(unsigned int ind_from, unsigned int ind_to, float weight_) {
	if (ind_from < heads.size()) {
		auto currptr = heads[ind_from]->adjptr;
		//std::cout<<"Node: "<<currptr->nodeind<<" "<<currptr<<" connects to:\n";
		bool found = false;
		while (currptr!=nullptr) {
			if (currptr->nodeind == ind_to) {
				found = true;
				currptr->weight = weight_;
				break; 
				// REMOVE THIS BREAK STATEMENT TO UPDATE ALL
				// EDGES THAT CONNECT TWO STATES. THIS WILL 
				// DECREASE THE EFFICIENCY
			}
			currptr = currptr->adjptr;
		}
		if (!found) {
			std::cout<<"Error: Update ind_to not found within list\n";
		}
	} else {
		std::cout<<"Error: Update ind_from out of bounds\n";
	}
}

int Edge::augmentedStateFunc(int i, int j, int n, int m) {
	int ret_int;
	ret_int = m*i+j;
	if (ret_int<=n*m){
		return ret_int;
	} else {
		std::cout<<"Error: augmentedStateFunc mapping out of bounds\n";
		return -1;
	}
}

void Edge::compose(const Edge &mult_graph, Edge& product_graph){
	int n = heads.size();
	int m = mult_graph.size();
	auto mult_heads = mult_graph.getHeads();
	int ind_from, ind_to;
	for (int i = 0; i<n; i++){
		for (int j = 0; j<m; j++){
			auto currptr_i = heads[i]->adjptr;	
			auto currptr_j = mult_heads[j]->adjptr;	
			ind_from = augmentedStateFunc(i, j, n, m);
			while (currptr_i!=nullptr){
				int i_to = currptr_i->nodeind;
				while (currptr_j!=nullptr){
					int j_to = currptr_j->nodeind;
					ind_to = augmentedStateFunc(i_to, j_to, n, m);

					// Edge weights on composed graph are just the sum of the
					// corresponding edge weights. This line below can be
					// changed if the composition edge weight operator is
					// defined to be something else
					float prod_weight = currptr_i->weight + currptr_j->weight;

					// Edge labels on composed are just the edge labels of the
					// "this" graph. This line below can be edited if the 
					// composition labeling rules needs to be customized/changed
					std::string prod_label = currptr_i->label;
					product_graph.connect(ind_from, ind_to, prod_weight, prod_label);
					currptr_j = currptr_j->adjptr;
				}
				currptr_i = currptr_i->adjptr;
			}
		}
	}
}


void Edge::augmentedStateMap(unsigned int ind_product, int n, int m, std::pair<unsigned int, unsigned int>& ret_indices) {
	unsigned int i = 0;
	unsigned int j;
	while (m*(i+1)<(ind_product+1)){
		i++; 
	}
	j = ind_product % m; 	
	ret_indices.first = i;
	ret_indices.second = j;
}

void Edge::clear() {
	std::cout<< "Clearing " << heads.size() << " lists...\n";

	for (int i=0; i<heads.size(); i++) {
		auto currptr = heads[i];
		while (currptr!=nullptr) {
			auto nextptr = currptr->adjptr;
			//std::cout<<"PTR DELETE: "<<currptr<<std::endl;
			delete currptr;
			currptr = nextptr;
		}
	}
	prevs.clear();
	heads.clear();
	head = nullptr;
	prev = nullptr;
	ind = 0;
	ind_checkout = 0;
	checking = false;
}

void Edge::deleteList(node* head) {
	auto currptr = head;
	while (currptr!=nullptr) {
		auto nextptr = currptr->adjptr;
		//std::cout<<"PTR DELETE: "<<currptr<<std::endl;
		delete currptr;
		currptr = nextptr;
	}
}

Edge::~Edge() {
	std::cout<< "Deconstructing " << heads.size() << " lists...\n";
	for (int i=0; i<heads.size(); i++) {
		deleteList(heads[i]);
		//auto currptr = heads[i];
		//while (currptr!=nullptr) {
		//	auto nextptr = currptr->adjptr;
		//	//std::cout<<"PTR DELETE: "<<currptr<<std::endl;
		//	delete currptr;
		//	currptr = nextptr;
		//}
	}
}



//PrioQueue



