#include <iostream>
#include <fstream>
#include <iomanip>
#include <ykdef.h>
#include <ykcore.h>


int main()
{
	YK_KEY* onlykey;
	std::ifstream challengefile("challenge");
	unsigned char buffer[64] = {0};
	unsigned char* challenge = new unsigned char[64];
	const int pid[1] = { 0x60fc };

	challengefile.read((char *)challenge, 64);
	challengefile.close();

	yk_init();
	onlykey = yk_open_key_vid_pid(0x1d50, pid, sizeof(pid), 0);

	if (!onlykey) {
		std::cout << yk_strerror(yk_errno) << std::endl;
		return 1;
	}

	yk_challenge_response(onlykey, SLOT_CHAL_HMAC1, 1, 64, challenge, sizeof(buffer), buffer);
	delete[] challenge;


	for (int i = 0; i < 20; i++) {
		std::cout << std::setfill('0') << std::setw(2) << std::hex << int(buffer[i]);
	}

	return 0;
}