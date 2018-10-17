#ifndef MENU_H_DEFINED
#define MENU_H_DEFINED

#include <Display/Window.hpp>
#include <Display/MenuItem.hpp>

#include <vector>
#include <string>

class Menu
{
public:

	// tạo ra một menu tại (y, x) với width, height
	// Lưu ý phải draw() mới vẽ menu ra màn hình
	Menu(int x, int y, int width, int height);

	virtual ~Menu();

	// Thêm item cho menu
	void add(MenuItem* item);

	// vẽ Menu ra màn hình
	void draw(Window* window);

	// Xử lí input trên menu
	void handleInput();

	// Di chuyển trên menu
	void goNext();
	void goPrevious();

	// true nếu như user chọn một nhãn làm thoát menu hiện t
	bool willQuit();

	// trả về nhãn của item đang được chọn
	std::string currentLabel();

	// trả về id của item đang được chọn
	int currentID();

	void reset();

	//  vector lưu trữ item của menu
	std::vector<MenuItem*> item;

	// current cho biết item nào đang được chọn
	MenuItem* current;

protected:
	/// chỉ số của item đang được chọn trong vector.
	unsigned int currentIndex;

	int x;
	int y;
	int width;
	int height;

	// true nếu như user nhấn chọn một item .
	bool selected;

	/// cho biết item nào user đang nhấn chọn.
	MenuItem* selectedItem;
};

#endif //MENU_H_DEFINED
