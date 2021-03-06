#pragma once
#include<vector>
#include "state.h"
#include<string>
#include<unordered_map>

class Condition {
	protected:
	 	const bool tautology;
	 	bool excl_equals;
		struct subCondition {
			bool TAUT;
			bool LOGICAL;
			int ARG_1_TYPE;
			std::string arg_1;
			int OPERATOR;
			int ARG_2_TYPE;
			std::string arg_2;
			std::string condition_label;
		} cond_struct;
		struct arg_V_struct {
			std::string var;
			std::string label;
			bool is_set;
		};
		std::vector<subCondition> pr_c;
		std::vector<subCondition> ps_c;
		int pre_cond_junct;
		int post_cond_junct;
		std::vector<std::pair<bool, std::string>> arg_L;
		std::unordered_map<std::string, int> arg_L_labels;
		std::vector<arg_V_struct> arg_V;
		std::unordered_map<std::string, int> arg_V_labels;
		std::pair<bool, std::string> arg_L_i;
		arg_V_struct arg_V_i;
		void sub_print(const std::vector<subCondition>& p_c) const;
		std::string action_label;
		float action_cost;
		std::string label;
	public:	
		static const bool TRUE;
		static const bool NEGATE;
		static const std::string FILLER;
		static const int NONE;
		static const int LABEL;
		static const int VAR;	
		static const int DOM;	
		static const int GROUP;
		static const int ARG_L;	
		static const int ARG_V;	
		static const int EQUALS;	
		static const int IN_DOM;	
		static const int ARG_FIND;	
		static const int ARG_EQUALS;	
		static const int CONJUNCTION;	
		static const int DISJUNCTION;
		static const int PRE;
		static const int POST;
		static const int SIMPLE;

		Condition(bool tautology_ = false);
		virtual void addCondition(int COND_TYPE_, int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_);
		virtual void addCondition(int COND_TYPE_, int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_, bool LOGICAL_);
		virtual void addCondition(int COND_TYPE_, int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_, bool LOGICAL_, std::string condition_label_);
		virtual void setCondJunctType(int COND_TYPE_, int LOGICAL_OPERATOR);
		void setExclEq(bool excl_equal_);
		//void addPostCondition(int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_);
		//void addPostCondition(int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_, bool LOGICAL_);
		//void addPostCondition(int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_, bool LOGICAL_, std::string condition_label_);
		//void setPostCondJunctType(int LOGICAL_OPERATOR);
		void setActionLabel(const std::string& action_label_);
		std::string getActionLabel();
		void setActionCost(float action_cost_);
		float getActionCost();
		void setLabel(const std::string& label_);
		std::string getLabel();
		bool subEvaluate(const State* state, const subCondition& cond);
		bool evaluate(const State* pre_state, const State* post_state);
		void print() const;
};


class SimpleCondition : public Condition {
	private:
		std::vector<subCondition> s_c;
		int simple_cond_junct;
	public:
		void addCondition(int COND_TYPE_, int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_);
		void addCondition(int COND_TYPE_, int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_, bool LOGICAL_);
		void addCondition(int COND_TYPE_, int ARG_1_TYPE_, std::string arg_1_, int OPERATOR_, int ARG_2_TYPE_, std::string arg_2_, bool LOGICAL_, std::string condition_label_);
		void setCondJunctType(int COND_TYPE_, int LOGICAL_OPERATOR);
		bool evaluate(const State* state);
};

