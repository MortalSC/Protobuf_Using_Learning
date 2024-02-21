All:write read

read: read.cc contacts2.pb.cc
	g++ -o read read.cc contacts2.pb.cc -std=c++11 -lprotobuf

write: write.cc contacts2.pb.cc
	g++ -o write write.cc contacts2.pb.cc -std=c++11 -lprotobuf

PHONY:clean
clean:
	rm -rf write read