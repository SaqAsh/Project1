all: InputHandler.cpp ResizeableArray.cpp TimeSeries.cpp
	g++ -g -std=c++17 InputHandler.cpp ResizeableArray.cpp TimeSeries.cpp