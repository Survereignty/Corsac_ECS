init:
	git submodule update --init; cd lib/EASTL; git submodule update --init; mkdir build; cd build; cmake ..; cmake --build .; cd ..; cd ..; cd ..; ls; mkdir build; cd build; cmake ..;

clear:
	rm -rf build; cd lib; rm -rf EASTL;

re:
	rm -rf build; mkdir build; cd build; cmake ..;

dev:
	cd build; cmake --build .;