#ifndef SCAN_IMAGE_H
#define SCAN_IMAGE_H

#include <fstream>
#include <iostream>

void save() {
	std::ofstream output("IMAGE.PPM", std::ios::binary);

	if (output.is_open()) {
		output << "P3" << std::endl;
		output << 255 << std::endl;
		output << 255 << std::endl;
		output << 255 << std::endl;

		for (int i = 0; i < 255; i++) {
			for (int j = 0; j < 255; j++) {
				output << i << ' ';
				output << j << ' ';
				output << 0 << '\n';
			}
		}
	}
}

#endif
