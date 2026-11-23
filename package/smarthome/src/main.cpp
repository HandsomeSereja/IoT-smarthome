#include <gpiod.h>
#include <iostream>
#include <unistd.h>

int main(){
	const char *chipname = "gpiochip0";
	unsigned int line_num = 17;
	struct gpiod_chip  *chip;
	struct gpiod_line *line;
	int ret;

	chip = gpiod_chip_open_by_name(chipname);
	if(!chip){
		std::cerr << "Failed to open gpiochip" <<  std::endl;
		return 1;
	}

	line = gpiod_chip_get_line(chip, line_num);
	if(!line) {
		std::cerr << "Failed to get line" << std::endl;
		gpiod_chip_close(chip);
	}

	ret = gpiod_line_request_output(line, "smarthome", 0);
	if(ret < 0){
		std::cerr << "Failed too request line as outpuut" << std::endl;
		gpiod_chip_close(chip);
		return 1;
	}

	std::cout << "Smarthome app started, blinking GPIO17" << std::endl;
	for(int i = 0; i < 40; i++){
		gpiod_line_set_value(line, 1);
		usleep(500000);
		gpiod_line_set_value(line, 0);
		usleep(500000);
	}
	
	gpiod_line_release(line);
	gpiod_chip_close(chip);
	return 0;
}
