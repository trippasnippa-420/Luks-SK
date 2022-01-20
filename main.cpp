#include <iostream>
#include <iomanip>
#include <memory.h>
#include <yubikey.h>
#include <ykdef.h>
#include <ykcore.h>
#include <ykstatus.h>


int main()
{
	YK_KEY* onlykey;
	unsigned char buffer[64] = {0};
	unsigned char *challenge = new unsigned char[64]();
	unsigned char *outputbuf = new unsigned char[64]();
	const int pid[1] = { 0x60fc };

	memset(challenge, 0x42, 64);
	// for (int i = 0; i < 64; i++) {
		
	// }

	yk_init();
	onlykey = yk_open_key_vid_pid(0x1d50, pid, sizeof(pid), 0);

	

	std::cout << "OK opened" << std::endl;

	yk_challenge_response(onlykey, SLOT_CHAL_HMAC1, 1, 64, challenge, sizeof(buffer), buffer);


	for (int i = 0; i < 20; i++) {
		std::cout << std::setfill('0') << std::setw(2) << std::hex << int(buffer[i]);
	}
}