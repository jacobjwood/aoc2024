.phony: day_setup

day_setup:
	if ! [ -d day${day} ]; \
	then \
		mkdir day${day}; \
	fi

	./build/get_input_day_x ${day}

	if ! [ -f day$(day)/solution.cpp ]; \
	then \
		cp templates/day{x}.cpp day${day}/solution.cpp; \
		sed -i 's/<DAY>/${day}/g' day${day}/solution.cpp; \
		echo "add_executable(day${day} day${day}/solution.cpp helpers/helpers.cpp)" >> CMakeLists.txt; \
	else \
		echo "Solution file already created. Skipping..."; \
	fi


run:
	clang-format day${day}/*.cpp 
	cd build && cmake && make
	build/day${day}
