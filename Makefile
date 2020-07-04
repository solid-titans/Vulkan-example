all:
	g++ main.cpp -lglfw -LGL -o Vulkan

run: all
	./Vulkan

clean:
	rm Vulkan
