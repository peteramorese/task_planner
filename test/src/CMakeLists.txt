
add_executable(test_preference_planner_grid_robot_heuristic test_preference_planner_grid_robot_heuristic.cpp)
target_link_libraries(test_preference_planner_grid_robot_heuristic 
	LexSetClass
	GraphClass
	ConditionClass
	StateClass
	SymbSearchClass
	TransitionSystemClass
	BenchmarkClass
	)

