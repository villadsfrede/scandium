#ifndef SCAN_IMAGE_H
#define SCAN_IMAGE_H

#include <fstream>
#include <iostream>

void save(int width, int height, Vector3f* film) {
	std::ofstream output("IMAGE.PPM", std::ios::binary);

	if (output.is_open()) {
		output << "P3" << std::endl;
		output << width << std::endl;
		output << height << std::endl;
		output << 255 << std::endl;

		for (int i = 0; i < width * height; ++i) {
			//std::cout << film[i].x << ' ' << film[i].y << ' ' << film[i].z << std::endl;
			output << (int)film[i].x << ' ';
			output << (int)film[i].y << ' ';
			output << (int)film[i].z << '\n';
		}
	}
}

#endif
