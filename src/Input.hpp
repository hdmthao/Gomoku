#ifndef Input_H_DEFINED
#define Input_H_DEFINED

#include <string>
#include <map>

	// Xử lí các thao tác phím cho toàn bộ game

	// lưu ý chạy `Input::update()` cho mỗi frame



	// Map một phím bất kì cho một giá trị bất kì.
	//  khi khởi tạo game.
	// Input::bind("jump", 'w');
	// Input::bind("jump", KEY_UP);
	// Sau đó có thể dùng
	// if (Input::isPressed("jump"))

namespace Input
{

	// True nếu không có phím nào được bấm
	bool noKeyPressed();

	// True nếu phím #key được bấm
	bool isPressed(int key);

	// True nếu phím #name được bấm
	bool isPressed(std::string key);

	// Lấy dữ liệu từ user

	int getInput(int delay_ms=-1);
	// Nếu delay_ms = -1 thì sẽ đợi cho đến khi user bấm phím
	// Nếu delay_ms = 0 thì sẽ return dù user có bấm hay không
	// Nếu delay_ms > 0 thì sẽ đợi user bấm phím trong delay_ms milisecond.
	void update(int delay_ms=0);

	char getAlphabet();
	// phím nào đã được nhấn
	extern int pressedKey;

	// một cái map để  map các key
	extern std::map<std::string, int> binds;

};

#endif //Input_H_DEFINED
