all:
	g++ main.cpp -lglfw -lvulkan -o Vulkan

run: all
	./Vulkan

clean:
	rm Vulkan
