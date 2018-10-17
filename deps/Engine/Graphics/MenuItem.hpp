#ifndef MENUITEM_H_DEFINED
#define MENUITEM_H_DEFINED

#include <Engine/Graphics/Window.hpp>

#include <string>

struct MenuItem
{

	// các loại item của menu.
	enum MenuItemType
	{
		ITEM, LABEL, CHECKBOX, NUMBERBOX, TEXTBOX, TEXTLIST
	};

	// Tạo một item của menu với nhãn và id.
	MenuItem(std::string label, int id);

	virtual ~MenuItem() { };

	// vẽ item menu tại vị trí x, y của menu.
	// Nếu như item đang được chọn thì đặt isCurrentItem = True
	virtual void draw(Window* window, int x, int y, int width, bool isCurrentItem=false);

	// Xử lí input của người dùng.
	virtual void handleInput();


	MenuItemType type;

	// Nhãn của item. Nhãn sẽ được in trên màn hình.
	std::string label;

	// Id của item.
	int id;
};

#endif //MENUITEM_H_DEFINED
